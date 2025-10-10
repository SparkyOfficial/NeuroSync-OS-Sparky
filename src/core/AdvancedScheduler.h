#ifndef ADVANCED_SCHEDULER_H
#define ADVANCED_SCHEDULER_H

#include "interfaces/SchedulingAlgorithm.h"
#include "utils/TaskManager.h"
#include "algorithms/PriorityBasedScheduling.h"
#include "algorithms/RoundRobinScheduling.h"
#include "algorithms/WeightedFairQueuingScheduling.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <map>

// AdvancedScheduler.h
// Расширенный планировщик задач для NeuroSync OS Sparky
// Advanced task scheduler for NeuroSync OS Sparky
// Розширений планувальник завдань для NeuroSync OS Sparky

namespace NeuroSync {
namespace Core {

    // Тип алгоритма планирования
    // Scheduling algorithm type
    // Тип алгоритму планування
    enum class SchedulingAlgorithmType {
        PRIORITY_BASED,         // На основе приоритетов / Priority-based / На основі пріоритетів
        ROUND_ROBIN,            // Round Robin / Round Robin / Round Robin
        WEIGHTED_FAIR_QUEUING   // Weighted Fair Queuing / Weighted Fair Queuing / Weighted Fair Queuing
    };

    // Расширенный планировщик задач
    // Advanced task scheduler
    // Розширений планувальник завдань
    class AdvancedScheduler {
    public:
        AdvancedScheduler();
        ~AdvancedScheduler();
        
        // Инициализация планировщика
        // Initialize the scheduler
        // Ініціалізація планувальника
        bool initialize(SchedulingAlgorithmType algorithmType = SchedulingAlgorithmType::PRIORITY_BASED);
        
        // Запуск планировщика
        // Start the scheduler
        // Запуск планувальника
        void start();
        
        // Остановка планировщика
        // Stop the scheduler
        // Зупинка планувальника
        void stop();
        
        // Добавление задачи в планировщик
        // Add a task to the scheduler
        // Додавання завдання до планувальника
        int addTask(const std::string& name, Utils::TaskType type, int priority, int weight, void (*function)(), void* userData = nullptr);
        
        // Удаление задачи из планировщика
        // Remove a task from the scheduler
        // Видалення завдання з планувальника
        bool removeTask(int taskId);
        
        // Обновление приоритета задачи
        // Update task priority
        // Оновлення пріоритету завдання
        bool updateTaskPriority(int taskId, int priority);
        
        // Обновление веса задачи
        // Update task weight
        // Оновлення ваги завдання
        bool updateTaskWeight(int taskId, int weight);
        
        // Получение статуса задачи
        // Get task status
        // Отримання статусу завдання
        Utils::TaskStatus getTaskStatus(int taskId) const;
        
        // Установка алгоритма планирования
        // Set scheduling algorithm
        // Встановлення алгоритму планування
        bool setSchedulingAlgorithm(SchedulingAlgorithmType algorithmType);
        
        // Получение текущего алгоритма планирования
        // Get current scheduling algorithm
        // Отримання поточного алгоритму планування
        SchedulingAlgorithmType getCurrentAlgorithmType() const;
        
        // Получение количества задач
        // Get task count
        // Отримання кількості завдань
        size_t getTaskCount() const;
        
        // Получение количества выполняемых задач
        // Get running task count
        // Отримання кількості виконуваних завдань
        size_t getRunningTaskCount() const;
        
        // Получение количества ожидающих задач
        // Get pending task count
        // Отримання кількості очікуючих завдань
        size_t getPendingTaskCount() const;
        
        // Получение статистики планировщика
        // Get scheduler statistics
        // Отримання статистики планувальника
        struct SchedulerStatistics {
            size_t totalTasks;
            size_t runningTasks;
            size_t pendingTasks;
            size_t completedTasks;
            size_t failedTasks;
            size_t cancelledTasks;
            double averageExecutionTime;
            long long totalExecutionTime;
        };
        
        SchedulerStatistics getStatistics() const;
        
    private:
        // Менеджер задач
        // Task manager
        // Менеджер завдань
        std::unique_ptr<Utils::TaskManager> taskManager;
        
        // Алгоритм планирования
        // Scheduling algorithm
        // Алгоритм планування
        std::unique_ptr<SchedulingAlgorithm> schedulingAlgorithm;
        
        // Тип текущего алгоритма планирования
        // Current scheduling algorithm type
        // Тип поточного алгоритму планування
        SchedulingAlgorithmType currentAlgorithmType;
        
        // Флаг работы планировщика
        // Scheduler running flag
        // Прапор роботи планувальника
        std::atomic<bool> running;
        
        // Поток планировщика
        // Scheduler thread
        // Потік планувальника
        std::thread schedulerThread;
        
        // Мьютекс для синхронизации
        // Mutex for synchronization
        // М'ютекс для синхронізації
        mutable std::mutex schedulerMutex;
        
        // Условная переменная для уведомлений
        // Condition variable for notifications
        // Умовна змінна для сповіщень
        std::condition_variable schedulerCondition;
        
        // Карта выполняемых задач
        // Map of running tasks
        // Карта виконуваних завдань
        std::map<int, std::thread> runningTasks;
        
        // Статистика выполнения задач
        // Task execution statistics
        // Статистика виконання завдань
        mutable std::mutex statisticsMutex;
        long long totalExecutionTime;
        size_t completedTaskCount;
        size_t failedTaskCount;
        size_t cancelledTaskCount;
        
        // Основной цикл планировщика
        // Main scheduler loop
        // Основний цикл планувальника
        void schedulerLoop();
        
        // Выполнение задачи
        // Execute a task
        // Виконання завдання
        void executeTask(int taskId);
        
        // Обновление статистики
        // Update statistics
        // Оновлення статистики
        void updateStatistics(int taskId, Utils::TaskStatus status, long long executionTime);
        
        // Создание алгоритма планирования
        // Create scheduling algorithm
        // Створення алгоритму планування
        std::unique_ptr<SchedulingAlgorithm> createSchedulingAlgorithm(SchedulingAlgorithmType type);
    };

} // namespace Core
} // namespace NeuroSync

#endif // ADVANCED_SCHEDULER_H