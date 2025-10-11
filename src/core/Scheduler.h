#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <chrono>

// Scheduler.h
// Планувальник задач для NeuroSync OS Sparky
// Task scheduler for NeuroSync OS Sparky
// Планувальник завдань для NeuroSync OS Sparky

// Реалізувати планировник задач який працює з нейронами
// Implement a task scheduler that works with neurons
// Реалізувати планувальник завдань, який працює з нейронами

namespace Core {
    namespace Utils {
        // Структура задачі
        // Task structure
        // Структура завдання
        struct Task {
            int id;
            std::function<void()> function;
            int priority;
            std::chrono::high_resolution_clock::time_point creationTime;
            std::chrono::high_resolution_clock::time_point scheduledTime;
            
            Task(int taskId, std::function<void()> func, int prio)
                : id(taskId), function(std::move(func)), priority(prio),
                  creationTime(std::chrono::high_resolution_clock::now()),
                  scheduledTime(creationTime) {}
        };
        
        // Компаратор для пріоритетної черги
        // Comparator for priority queue
        // Компаратор для пріоритетної черги
        struct TaskComparator {
            bool operator()(const Task& a, const Task& b) const {
                // Вищий пріоритет має менше значення
                // Higher priority has lower value
                // Вищий пріоритет має менше значення
                if (a.priority != b.priority) {
                    return a.priority > b.priority;
                }
                // Якщо пріоритети однакові, то за часом створення
                // If priorities are equal, then by creation time
                // Якщо пріоритети однакові, то за часом створення
                return a.creationTime > b.creationTime;
            }
        };
    }
    
    class Scheduler {
    public:
        Scheduler();
        ~Scheduler();
        
        // Ініціалізація планувальника
        // Initialize the scheduler
        // Инициализация планувальника
        bool initialize();
        
        // Запустити планувальник
        // Start the scheduler
        // Запустити планувальник
        void start();
        
        // Зупинити планувальник
        // Stop the scheduler
        // Зупинити планувальник
        void stop();
        
        // Додати задачу до планувальника
        // Add a task to the scheduler
        // Додати завдання до планувальника
        void addTask(std::function<void()> task, int priority = 0);
        
        // Додати задачу з відкладеним виконанням
        // Add a task with delayed execution
        // Додати завдання з відкладеним виконанням
        void addDelayedTask(std::function<void()> task, std::chrono::milliseconds delay, int priority = 0);
        
        // Отримати кількість задач у черзі
        // Get the number of tasks in the queue
        // Отримати кількість завдань у черзі
        size_t getTaskCount() const;
        
        // Отримати статистику планувальника
        // Get scheduler statistics
        // Отримати статистику планувальника
        struct Statistics {
            size_t tasksAdded;
            size_t tasksCompleted;
            size_t tasksFailed;
            std::chrono::milliseconds totalExecutionTime;
            double averageExecutionTime;
            
            Statistics() : tasksAdded(0), tasksCompleted(0), tasksFailed(0), 
                          totalExecutionTime(0), averageExecutionTime(0.0) {}
        };
        
        Statistics getStatistics() const;
        
    private:
        // Основний цикл планувальника
        // Main scheduler loop
        // Основний цикл планувальника
        void schedulerLoop();
        
        // Виконати задачу
        // Execute task
        // Виконати завдання
        void executeTask(const Utils::Task& task);
        
        // Генерувати унікальний ID для задачі
        // Generate unique ID for task
        // Згенерувати унікальний ID для завдання
        int generateTaskId();
        
        // Черга задач
        // Task queue
        // Черга завдань
        std::priority_queue<Utils::Task, std::vector<Utils::Task>, Utils::TaskComparator> taskQueue;
        
        // Потік планувальника
        // Scheduler thread
        // Потік планувальника
        std::thread schedulerThread;
        
        // М'ютекс для синхронізації
        // Mutex for synchronization
        // М'ютекс для синхронізації
        mutable std::mutex queueMutex;
        mutable std::mutex statsMutex;
        
        // Змінна умови для сповіщення
        // Condition variable for notification
        // Змінна умови для сповіщення
        std::condition_variable condition;
        
        // Атомарні прапорці
        // Atomic flags
        // Атомарні прапорці
        std::atomic<bool> running;
        std::atomic<bool> stopping;
        
        // Лічильники
        // Counters
        // Лічильники
        std::atomic<int> taskIdCounter;
        Statistics statistics;
    };
}

#endif // SCHEDULER_H