#include "TaskManager.h"
#include <chrono>
#include <algorithm>
#include <iostream>

// TaskManager.cpp
// Реализация менеджера задач для планировщика
// Implementation of task manager for scheduler
// Реалізація менеджера завдань для планувальника

namespace NeuroSync {
namespace Core {
namespace Utils {

    TaskManager::TaskManager() : taskIdCounter(1) {
        // Конструктор менеджера задач
        // Constructor of task manager
        // Конструктор менеджера завдань
    }

    TaskManager::~TaskManager() {
        // Деструктор менеджера задач
        // Destructor of task manager
        // Деструктор менеджера завдань
        clearAllTasks();
    }

    int TaskManager::createTask(const std::string& name, TaskType type, int priority, int weight, void (*function)(), void* userData) {
        // Создание новой задачи
        // Create a new task
        // Створення нового завдання
        
        // Создание новой задачи
        // Create a new task
        // Створення нового завдання
        std::shared_ptr<Task> task = std::make_shared<Task>();
        task->id = taskIdCounter++;
        task->name = name;
        task->type = type;
        task->status = TaskStatus::PENDING;
        task->priority = priority;
        task->weight = weight;
        task->creationTime = getCurrentTimeMillis();
        task->startTime = 0;
        task->endTime = 0;
        task->executionTime = 0;
        task->function = function;
        task->userData = userData;
        
        // Добавление задачи в вектор
        // Add task to vector
        // Додавання завдання до вектора
        tasks.push_back(task);
        
        return task->id;
    }

    bool TaskManager::deleteTask(int taskId) {
        // Удаление задачи
        // Delete a task
        // Видалення завдання
        
        // Поиск задачи по ID
        // Find task by ID
        // Пошук завдання за ID
        auto it = std::find_if(tasks.begin(), tasks.end(),
            [taskId](const std::shared_ptr<Task>& task) {
                return task->id == taskId;
            });
        
        if (it != tasks.end()) {
            // Удаление задачи из вектора
            // Remove task from vector
            // Видалення завдання з вектора
            tasks.erase(it);
            return true;
        }
        
        return false; // Задача не найдена / Task not found / Завдання не знайдено
    }

    Task* TaskManager::getTask(int taskId) {
        // Получение задачи по ID
        // Get task by ID
        // Отримання завдання за ID
        
        // Поиск задачи по ID
        // Find task by ID
        // Пошук завдання за ID
        auto it = std::find_if(tasks.begin(), tasks.end(),
            [taskId](const std::shared_ptr<Task>& task) {
                return task->id == taskId;
            });
        
        if (it != tasks.end()) {
            return it->get();
        }
        
        return nullptr; // Задача не найдена / Task not found / Завдання не знайдено
    }

    bool TaskManager::updateTaskStatus(int taskId, TaskStatus status) {
        // Обновление статуса задачи
        // Update task status
        // Оновлення статусу завдання
        
        Task* task = getTask(taskId);
        if (task != nullptr) {
            // Обновление времени в зависимости от статуса
            // Update time based on status
            // Оновлення часу залежно від статусу
            long long currentTime = getCurrentTimeMillis();
            
            switch (status) {
                case TaskStatus::RUNNING:
                    task->startTime = currentTime;
                    break;
                case TaskStatus::COMPLETED:
                case TaskStatus::FAILED:
                case TaskStatus::CANCELLED:
                    task->endTime = currentTime;
                    if (task->startTime > 0) {
                        task->executionTime = task->endTime - task->startTime;
                    }
                    break;
                default:
                    break;
            }
            
            task->status = status;
            return true;
        }
        
        return false; // Задача не найдена / Task not found / Завдання не знайдено
    }

    bool TaskManager::updateTaskPriority(int taskId, int priority) {
        // Обновление приоритета задачи
        // Update task priority
        // Оновлення пріоритету завдання
        
        Task* task = getTask(taskId);
        if (task != nullptr) {
            task->priority = priority;
            return true;
        }
        
        return false; // Задача не найдена / Task not found / Завдання не знайдено
    }

    bool TaskManager::updateTaskWeight(int taskId, int weight) {
        // Обновление веса задачи
        // Update task weight
        // Оновлення ваги завдання
        
        Task* task = getTask(taskId);
        if (task != nullptr) {
            task->weight = weight;
            return true;
        }
        
        return false; // Задача не найдена / Task not found / Завдання не знайдено
    }

    bool TaskManager::addTaskDependency(int taskId, int dependencyId) {
        // Добавление зависимости задачи
        // Add task dependency
        // Додавання залежності завдання
        
        Task* task = getTask(taskId);
        if (task != nullptr) {
            // Проверка, существует ли зависимость
            // Check if dependency exists
            // Перевірка, чи існує залежність
            auto it = std::find(task->dependencies.begin(), task->dependencies.end(), dependencyId);
            if (it == task->dependencies.end()) {
                // Добавление зависимости
                // Add dependency
                // Додавання залежності
                task->dependencies.push_back(dependencyId);
                return true;
            }
        }
        
        return false; // Задача не найдена / Task not found / Завдання не знайдено
    }

    bool TaskManager::removeTaskDependency(int taskId, int dependencyId) {
        // Удаление зависимости задачи
        // Remove task dependency
        // Видалення залежності завдання
        
        Task* task = getTask(taskId);
        if (task != nullptr) {
            // Поиск зависимости
            // Find dependency
            // Пошук залежності
            auto it = std::find(task->dependencies.begin(), task->dependencies.end(), dependencyId);
            if (it != task->dependencies.end()) {
                // Удаление зависимости
                // Remove dependency
                // Видалення залежності
                task->dependencies.erase(it);
                return true;
            }
        }
        
        return false; // Задача не найдена или зависимость не существует / Task not found or dependency doesn't exist / Завдання не знайдено або залежність не існує
    }

    const std::vector<std::shared_ptr<Task>>& TaskManager::getAllTasks() const {
        // Получение всех задач
        // Get all tasks
        // Отримання всіх завдань
        
        return tasks;
    }

    std::vector<std::shared_ptr<Task>> TaskManager::getTasksByType(TaskType type) const {
        // Получение задач по типу
        // Get tasks by type
        // Отримання завдань за типом
        
        std::vector<std::shared_ptr<Task>> result;
        
        for (const auto& task : tasks) {
            if (task->type == type) {
                result.push_back(task);
            }
        }
        
        return result;
    }

    std::vector<std::shared_ptr<Task>> TaskManager::getTasksByStatus(TaskStatus status) const {
        // Получение задач по статусу
        // Get tasks by status
        // Отримання завдань за статусом
        
        std::vector<std::shared_ptr<Task>> result;
        
        for (const auto& task : tasks) {
            if (task->status == status) {
                result.push_back(task);
            }
        }
        
        return result;
    }

    size_t TaskManager::getTaskCount() const {
        // Получение количества задач
        // Get task count
        // Отримання кількості завдань
        
        return tasks.size();
    }

    void TaskManager::clearAllTasks() {
        // Очистка всех задач
        // Clear all tasks
        // Очищення всіх завдань
        
        tasks.clear();
        taskIdCounter = 1;
    }

    long long TaskManager::getCurrentTimeMillis() const {
        // Получение времени в миллисекундах
        // Get time in milliseconds
        // Отримання часу в мілісекундах
        
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return millis;
    }

} // namespace Utils
} // namespace Core
} // namespace NeuroSync