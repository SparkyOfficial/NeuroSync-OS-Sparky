#include "Scheduler.h"
#include <iostream>
#include <algorithm>

// Scheduler.cpp
// Реалізація планувальника задач для NeuroSync OS Sparky
// Implementation of the task scheduler for NeuroSync OS Sparky
// Реалізація планувальника завдань для NeuroSync OS Sparky

namespace Core {

    Scheduler::Scheduler() : running(false), stopping(false), taskIdCounter(0) {
        // Ініціалізація планувальника
        // Initialize the scheduler
        // Ініціалізувати планувальник
    }

    bool Scheduler::initialize() {
        // Ініціалізація планувальника
        // Initialize the scheduler
        // Ініціалізувати планувальник
        std::lock_guard<std::mutex> lock(queueMutex);
        // Нічого спеціального не потрібно ініціалізувати
        // Nothing special needs to be initialized
        // Ничего специального не нужно инициализировать
        return true;
    }

    Scheduler::~Scheduler() {
        // Очищення ресурсів планувальника
        // Clean up scheduler resources
        // Очистити ресурси планувальника
        stop();
    }

    void Scheduler::start() {
        // Запустити цикл планувальника
        // Start the scheduler loop
        // Запустити цикл планувальника
        if (!running.exchange(true)) {
            schedulerThread = std::thread(&Scheduler::schedulerLoop, this);
        }
    }

    void Scheduler::stop() {
        // Зупинити цикл планувальника
        // Stop the scheduler loop
        // Зупинити цикл планувальника
        if (running.exchange(false)) {
            stopping = true;
            condition.notify_all();
            
            if (schedulerThread.joinable()) {
                schedulerThread.join();
            }
        }
    }

    void Scheduler::addTask(std::function<void()> task, int priority) {
        // Додати задачу до черги задач з відповідним пріоритетом
        // Add a task to the task queue with appropriate priority
        // Додати завдання до черги завдань з відповідним пріоритетом
        if (!running) {
            return;
        }
        
        int taskId = generateTaskId();
        Utils::Task newTask(taskId, task, priority);
        
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            taskQueue.emplace(newTask);
            statistics.tasksAdded++;
        }
        
        condition.notify_one();
    }

    void Scheduler::addDelayedTask(std::function<void()> task, std::chrono::milliseconds delay, int priority) {
        // Додати задачу з відкладеним виконанням
        // Add a task with delayed execution
        // Додати завдання з відкладеним виконанням
        if (!running) {
            return;
        }
        
        int taskId = generateTaskId();
        Utils::Task newTask(taskId, task, priority);
        newTask.scheduledTime = std::chrono::high_resolution_clock::now() + delay;
        
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            taskQueue.emplace(newTask);
            statistics.tasksAdded++;
        }
        
        condition.notify_one();
    }

    size_t Scheduler::getTaskCount() const {
        // Отримати кількість задач у черзі
        // Get the number of tasks in the queue
        // Отримати кількість завдань у черзі
        std::lock_guard<std::mutex> lock(queueMutex);
        return taskQueue.size();
    }

    Scheduler::Statistics Scheduler::getStatistics() const {
        // Отримати статистику планувальника
        // Get scheduler statistics
        // Отримати статистику планувальника
        std::lock_guard<std::mutex> lock(statsMutex);
        return statistics;
    }

    void Scheduler::schedulerLoop() {
        // Основний цикл планувальника
        // Main scheduler loop
        // Основний цикл планувальника
        while (running || !taskQueue.empty()) {
            Utils::Task currentTask(-1, nullptr, 0);
            bool hasTask = false;
            
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                
                // Очікування задачі або сигналу зупинки
                // Waiting for task or stop signal
                // Очікування завдання або сигналу зупинки
                condition.wait(lock, [this]() {
                    return !running || stopping || !taskQueue.empty();
                });
                
                // Перевірка чи є задачі для виконання
                // Check if there are tasks to execute
                // Перевірка чи є завдання для виконання
                while (!taskQueue.empty()) {
                    auto now = std::chrono::high_resolution_clock::now();
                    const auto& topTask = taskQueue.top();
                    
                    // Якщо задача готова до виконання
                    // If task is ready to execute
                    // Якщо завдання готове до виконання
                    if (topTask.scheduledTime <= now) {
                        currentTask = topTask;
                        taskQueue.pop();
                        hasTask = true;
                        break;
                    } else {
                        // Очікування до часу виконання задачі
                        // Wait until task execution time
                        // Очікування до часу виконання завдання
                        condition.wait_until(lock, topTask.scheduledTime);
                    }
                }
            }
            
            // Виконання задачі
            // Execute task
            // Виконання завдання
            if (hasTask && currentTask.function) {
                executeTask(currentTask);
            }
            
            // Якщо планувальник зупиняється і немає задач
            // If scheduler is stopping and no tasks
            // Якщо планувальник зупиняється і немає завдань
            if (stopping && taskQueue.empty()) {
                break;
            }
        }
    }

    void Scheduler::executeTask(const Utils::Task& task) {
        // Виконати задачу
        // Execute task
        // Виконати завдання
        auto startTime = std::chrono::high_resolution_clock::now();
        
        try {
            if (task.function) {
                task.function();
                
                // Оновлення статистики успішного виконання
                // Update successful execution statistics
                // Оновлення статистики успішного виконання
                {
                    std::lock_guard<std::mutex> lock(statsMutex);
                    statistics.tasksCompleted++;
                }
            }
        } catch (const std::exception& e) {
            // Обробка помилок виконання задачі
            // Handle task execution errors
            // Обробка помилок виконання завдання
            std::cerr << "Task " << task.id << " execution failed: " << e.what() << std::endl;
            
            // Оновлення статистики невдалого виконання
            // Update failed execution statistics
            // Оновлення статистики невдалого виконання
            {
                std::lock_guard<std::mutex> lock(statsMutex);
                statistics.tasksFailed++;
            }
        } catch (...) {
            // Обробка невідомих помилок
            // Handle unknown errors
            // Обробка невідомих помилок
            std::cerr << "Task " << task.id << " execution failed with unknown error" << std::endl;
            
            // Оновлення статистики невдалого виконання
            // Update failed execution statistics
            // Оновлення статистики невдалого виконання
            {
                std::lock_guard<std::mutex> lock(statsMutex);
                statistics.tasksFailed++;
            }
        }
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        
        // Оновлення загального часу виконання
        // Update total execution time
        // Оновлення загального часу виконання
        {
            std::lock_guard<std::mutex> lock(statsMutex);
            statistics.totalExecutionTime += executionTime;
            
            size_t totalCompleted = statistics.tasksCompleted + statistics.tasksFailed;
            if (totalCompleted > 0) {
                statistics.averageExecutionTime = static_cast<double>(statistics.totalExecutionTime.count()) / totalCompleted;
            }
        }
    }

    int Scheduler::generateTaskId() {
        // Генерувати унікальний ID для задачі
        // Generate unique ID for task
        // Згенерувати унікальний ID для завдання
        return taskIdCounter.fetch_add(1);
    }

}