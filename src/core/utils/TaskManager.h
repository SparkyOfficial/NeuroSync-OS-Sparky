#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <vector>
#include <memory>

// TaskManager.h
// Менеджер задач для планировщика
// Task manager for scheduler
// Менеджер завдань для планувальника

namespace NeuroSync {
namespace Core {
namespace Utils {

    // Тип задачи
    // Task type
    // Тип завдання
    enum class TaskType {
        NEURON_PROCESS,     // Обработка нейрона / Neuron processing / Обробка нейрона
        SYSTEM_MAINTENANCE, // Системное обслуживание / System maintenance / Системне обслуговування
        COMMUNICATION,      // Коммуникация / Communication / Комунікація
        DIAGNOSTICS,        // Диагностика / Diagnostics / Діагностика
        CUSTOM              // Пользовательская задача / Custom task / Користувацьке завдання
    };

    // Статус задачи
    // Task status
    // Статус завдання
    enum class TaskStatus {
        PENDING,    // Ожидание / Pending / Очікування
        RUNNING,    // Выполняется / Running / Виконується
        COMPLETED,  // Завершена / Completed / Завершена
        FAILED,     // Ошибка / Failed / Помилка
        CANCELLED   // Отменена / Cancelled / Скасована
    };

    // Структура для представления задачи
    // Structure to represent a task
    // Структура для представлення завдання
    struct Task {
        int id;                          // Уникальный идентификатор задачи / Unique task identifier / Унікальний ідентифікатор завдання
        std::string name;                // Имя задачи / Task name / Ім'я завдання
        TaskType type;                   // Тип задачи / Task type / Тип завдання
        TaskStatus status;               // Статус задачи / Task status / Статус завдання
        int priority;                    // Приоритет задачи / Task priority / Пріоритет завдання
        int weight;                      // Вес задачи / Task weight / Вага завдання
        long long creationTime;          // Время создания задачи / Task creation time / Час створення завдання
        long long startTime;             // Время начала выполнения / Start time / Час початку виконання
        long long endTime;               // Время завершения / End time / Час завершення
        long long executionTime;         // Время выполнения / Execution time / Час виконання
        std::vector<int> dependencies;   // Зависимости задачи / Task dependencies / Залежності завдання
        void (*function)();              // Функция для выполнения / Function to execute / Функція для виконання
        void* userData;                  // Пользовательские данные / User data / Користувацькі дані
    };

    // Менеджер задач для планировщика
    // Task manager for scheduler
    // Менеджер завдань для планувальника
    class TaskManager {
    public:
        TaskManager();
        ~TaskManager();
        
        // Создание новой задачи
        // Create a new task
        // Створення нового завдання
        int createTask(const std::string& name, TaskType type, int priority, int weight, void (*function)(), void* userData = nullptr);
        
        // Удаление задачи
        // Delete a task
        // Видалення завдання
        bool deleteTask(int taskId);
        
        // Получение задачи по ID
        // Get task by ID
        // Отримання завдання за ID
        Task* getTask(int taskId);
        
        // Обновление статуса задачи
        // Update task status
        // Оновлення статусу завдання
        bool updateTaskStatus(int taskId, TaskStatus status);
        
        // Обновление приоритета задачи
        // Update task priority
        // Оновлення пріоритету завдання
        bool updateTaskPriority(int taskId, int priority);
        
        // Обновление веса задачи
        // Update task weight
        // Оновлення ваги завдання
        bool updateTaskWeight(int taskId, int weight);
        
        // Добавление зависимости задачи
        // Add task dependency
        // Додавання залежності завдання
        bool addTaskDependency(int taskId, int dependencyId);
        
        // Удаление зависимости задачи
        // Remove task dependency
        // Видалення залежності завдання
        bool removeTaskDependency(int taskId, int dependencyId);
        
        // Получение всех задач
        // Get all tasks
        // Отримання всіх завдань
        const std::vector<std::shared_ptr<Task>>& getAllTasks() const;
        
        // Получение задач по типу
        // Get tasks by type
        // Отримання завдань за типом
        std::vector<std::shared_ptr<Task>> getTasksByType(TaskType type) const;
        
        // Получение задач по статусу
        // Get tasks by status
        // Отримання завдань за статусом
        std::vector<std::shared_ptr<Task>> getTasksByStatus(TaskStatus status) const;
        
        // Получение количества задач
        // Get task count
        // Отримання кількості завдань
        size_t getTaskCount() const;
        
        // Очистка всех задач
        // Clear all tasks
        // Очищення всіх завдань
        void clearAllTasks();
        
    private:
        // Вектор задач
        // Vector of tasks
        // Вектор завдань
        std::vector<std::shared_ptr<Task>> tasks;
        
        // Счетчик ID задач
        // Task ID counter
        // Лічильник ID завдань
        int taskIdCounter;
        
        // Получение времени в миллисекундах
        // Get time in milliseconds
        // Отримання часу в мілісекундах
        long long getCurrentTimeMillis() const;
    };

} // namespace Utils
} // namespace Core
} // namespace NeuroSync

#endif // TASK_MANAGER_H