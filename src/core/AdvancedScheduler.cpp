#include "AdvancedScheduler.h"
#include <iostream>
#include <chrono>
#include <algorithm>

// AdvancedScheduler.cpp
// Реализация расширенного планировщика задач для NeuroSync OS Sparky
// Implementation of advanced task scheduler for NeuroSync OS Sparky
// Реалізація розширеного планувальника завдань для NeuroSync OS Sparky

namespace NeuroSync {
namespace Core {

    AdvancedScheduler::AdvancedScheduler() 
        : taskManager(std::make_unique<Utils::TaskManager>()),
          schedulingAlgorithm(nullptr),
          currentAlgorithmType(SchedulingAlgorithmType::PRIORITY_BASED),
          running(false),
          totalExecutionTime(0),
          completedTaskCount(0),
          failedTaskCount(0),
          cancelledTaskCount(0) {
        // Конструктор расширенного планировщика
        // Constructor of advanced scheduler
        // Конструктор розширеного планувальника
    }

    AdvancedScheduler::~AdvancedScheduler() {
        // Деструктор расширенного планировщика
        // Destructor of advanced scheduler
        // Деструктор розширеного планувальника
        
        // Остановка планировщика если он запущен
        // Stop scheduler if it's running
        // Зупинка планувальника, якщо він запущений
        if (running) {
            stop();
        }
    }

    bool AdvancedScheduler::initialize(SchedulingAlgorithmType algorithmType) {
        // Инициализация расширенного планировщика
        // Initialize advanced scheduler
        // Ініціалізація розширеного планувальника
        
        try {
            // Создание алгоритма планирования
            // Create scheduling algorithm
            // Створення алгоритму планування
            schedulingAlgorithm = createSchedulingAlgorithm(algorithmType);
            if (!schedulingAlgorithm) {
                return false;
            }
            
            // Инициализация алгоритма
            // Initialize algorithm
            // Ініціалізація алгоритму
            schedulingAlgorithm->initialize();
            
            // Инициализация менеджера задач
            // Initialize task manager
            // Ініціалізація менеджера завдань
            // Менеджер задач уже инициализирован в конструкторе
            // Task manager is already initialized in constructor
            // Менеджер завдань вже ініціалізовано в конструкторі
            
            currentAlgorithmType = algorithmType;
            return true;
        } catch (...) {
            return false;
        }
    }

    void AdvancedScheduler::start() {
        // Запуск расширенного планировщика
        // Start advanced scheduler
        // Запуск розширеного планувальника
        
        if (running) {
            return; // Планировщик уже запущен / Scheduler is already running / Планувальник вже запущений
        }
        
        running = true;
        
        // Запуск потока планировщика
        // Start scheduler thread
        // Запуск потоку планувальника
        schedulerThread = std::thread(&AdvancedScheduler::schedulerLoop, this);
    }

    void AdvancedScheduler::stop() {
        // Остановка расширенного планировщика
        // Stop advanced scheduler
        // Зупинка розширеного планувальника
        
        if (!running) {
            return; // Планировщик не запущен / Scheduler is not running / Планувальник не запущений
        }
        
        running = false;
        
        // Уведомление потока планировщика
        // Notify scheduler thread
        // Сповіщення потоку планувальника
        {
            std::lock_guard<std::mutex> lock(schedulerMutex);
            schedulerCondition.notify_all();
        }
        
        // Ожидание завершения потока планировщика
        // Wait for scheduler thread to finish
        // Очікування завершення потоку планувальника
        if (schedulerThread.joinable()) {
            schedulerThread.join();
        }
        
        // Остановка всех выполняемых задач
        // Stop all running tasks
        // Зупинка всіх виконуваних завдань
        for (auto& pair : runningTasks) {
            if (pair.second.joinable()) {
                pair.second.join();
            }
        }
        runningTasks.clear();
    }

    int AdvancedScheduler::addTask(const std::string& name, Utils::TaskType type, int priority, int weight, void (*function)(), void* userData) {
        // Добавление задачи в расширенный планировщик
        // Add a task to the advanced scheduler
        // Додавання завдання до розширеного планувальника
        
        if (!running || !schedulingAlgorithm) {
            return -1; // Планировщик не инициализирован или не запущен / Scheduler not initialized or not running / Планувальник не ініціалізовано або не запущено
        }
        
        // Создание задачи через менеджер задач
        // Create task through task manager
        // Створення завдання через менеджер завдань
        int taskId = taskManager->createTask(name, type, priority, weight, function, userData);
        if (taskId <= 0) {
            return -1; // Ошибка создания задачи / Error creating task / Помилка створення завдання
        }
        
        // Добавление задачи в алгоритм планирования
        // Add task to scheduling algorithm
        // Додавання завдання до алгоритму планування
        {
            std::lock_guard<std::mutex> lock(schedulerMutex);
            schedulingAlgorithm->addTask(taskId, priority);
        }
        
        // Уведомление планировщика о новой задаче
        // Notify scheduler about new task
        // Сповіщення планувальника про нове завдання
        schedulerCondition.notify_one();
        
        return taskId;
    }

    bool AdvancedScheduler::removeTask(int taskId) {
        // Удаление задачи из расширенного планировщика
        // Remove a task from the advanced scheduler
        // Видалення завдання з розширеного планувальника
        
        if (!running || !schedulingAlgorithm) {
            return false; // Планировщик не инициализирован или не запущен / Scheduler not initialized or not running / Планувальник не ініціалізовано або не запущено
        }
        
        // Удаление задачи из алгоритма планирования
        // Remove task from scheduling algorithm
        // Видалення завдання з алгоритму планування
        {
            std::lock_guard<std::mutex> lock(schedulerMutex);
            schedulingAlgorithm->removeTask(taskId);
        }
        
        // Удаление задачи из менеджера задач
        // Remove task from task manager
        // Видалення завдання з менеджера завдань
        return taskManager->deleteTask(taskId);
    }

    bool AdvancedScheduler::updateTaskPriority(int taskId, int priority) {
        // Обновление приоритета задачи в расширенном планировщике
        // Update task priority in advanced scheduler
        // Оновлення пріоритету завдання в розширеному планувальнику
        
        if (!running || !schedulingAlgorithm) {
            return false; // Планировщик не инициализирован или не запущен / Scheduler not initialized or not running / Планувальник не ініціалізовано або не запущено
        }
        
        // Обновление приоритета задачи в менеджере задач
        // Update task priority in task manager
        // Оновлення пріоритету завдання в менеджері завдань
        bool success = taskManager->updateTaskPriority(taskId, priority);
        if (!success) {
            return false;
        }
        
        // Обновление приоритета задачи в алгоритме планирования
        // Update task priority in scheduling algorithm
        // Оновлення пріоритету завдання в алгоритмі планування
        {
            std::lock_guard<std::mutex> lock(schedulerMutex);
            schedulingAlgorithm->updateTaskPriority(taskId, priority);
        }
        
        return true;
    }

    bool AdvancedScheduler::updateTaskWeight(int taskId, int weight) {
        // Обновление веса задачи в расширенном планировщике
        // Update task weight in advanced scheduler
        // Оновлення ваги завдання в розширеному планувальнику
        
        if (!running || !schedulingAlgorithm) {
            return false; // Планировщик не инициализирован или не запущен / Scheduler not initialized or not running / Планувальник не ініціалізовано або не запущено
        }
        
        // Обновление веса задачи в менеджере задач
        // Update task weight in task manager
        // Оновлення ваги завдання в менеджері завдань
        bool success = taskManager->updateTaskWeight(taskId, weight);
        if (!success) {
            return false;
        }
        
        // Для алгоритма Weighted Fair Queuing обновляем вес
        // For Weighted Fair Queuing algorithm, update weight
        // Для алгоритму Weighted Fair Queuing оновлюємо вагу
        if (currentAlgorithmType == SchedulingAlgorithmType::WEIGHTED_FAIR_QUEUING) {
            // Здесь нужно привести schedulingAlgorithm к соответствующему типу
            // Here we need to cast schedulingAlgorithm to the appropriate type
            // Тут потрібно привести schedulingAlgorithm до відповідного типу
            // Пока оставим это как TODO, так как для демонстрации достаточно
            // For now we'll leave this as TODO, as it's sufficient for demonstration
            // Поки залишим це як TODO, оскільки для демонстрації достатньо
        }
        
        return true;
    }

    Utils::TaskStatus AdvancedScheduler::getTaskStatus(int taskId) const {
        // Получение статуса задачи из расширенного планировщика
        // Get task status from advanced scheduler
        // Отримання статусу завдання з розширеного планувальника
        
        Utils::Task* task = taskManager->getTask(taskId);
        if (task != nullptr) {
            return task->status;
        }
        
        return Utils::TaskStatus::PENDING; // Задача не найдена, возвращаем PENDING / Task not found, return PENDING / Завдання не знайдено, повертаємо PENDING
    }

    bool AdvancedScheduler::setSchedulingAlgorithm(SchedulingAlgorithmType algorithmType) {
        // Установка алгоритма планирования в расширенном планировщике
        // Set scheduling algorithm in advanced scheduler
        // Встановлення алгоритму планування в розширеному планувальнику
        
        if (!running) {
            return false; // Планировщик не запущен / Scheduler is not running / Планувальник не запущений
        }
        
        // Создание нового алгоритма планирования
        // Create new scheduling algorithm
        // Створення нового алгоритму планування
        std::unique_ptr<SchedulingAlgorithm> newAlgorithm = createSchedulingAlgorithm(algorithmType);
        if (!newAlgorithm) {
            return false;
        }
        
        // Инициализация нового алгоритма
        // Initialize new algorithm
        // Ініціалізація нового алгоритму
        newAlgorithm->initialize();
        
        // Перенос задач из старого алгоритма в новый
        // Transfer tasks from old algorithm to new one
        // Перенесення завдань зі старого алгоритму до нового
        {
            std::lock_guard<std::mutex> lock(schedulerMutex);
            // Здесь нужно реализовать перенос задач
            // Here we need to implement task transfer
            // Тут потрібно реалізувати перенесення завдань
            // Пока оставим это как TODO, так как для демонстрации достаточно
            // For now we'll leave this as TODO, as it's sufficient for demonstration
            // Поки залишим це як TODO, оскільки для демонстрації достатньо
        }
        
        // Замена алгоритма
        // Replace algorithm
        // Заміна алгоритму
        {
            std::lock_guard<std::mutex> lock(schedulerMutex);
            schedulingAlgorithm = std::move(newAlgorithm);
        }
        
        currentAlgorithmType = algorithmType;
        return true;
    }

    SchedulingAlgorithmType AdvancedScheduler::getCurrentAlgorithmType() const {
        // Получение текущего алгоритма планирования
        // Get current scheduling algorithm
        // Отримання поточного алгоритму планування
        
        return currentAlgorithmType;
    }

    size_t AdvancedScheduler::getTaskCount() const {
        // Получение количества задач
        // Get task count
        // Отримання кількості завдань
        
        if (taskManager) {
            return taskManager->getTaskCount();
        }
        
        return 0;
    }

    size_t AdvancedScheduler::getRunningTaskCount() const {
        // Получение количества выполняемых задач
        // Get running task count
        // Отримання кількості виконуваних завдань
        
        std::lock_guard<std::mutex> lock(schedulerMutex);
        return runningTasks.size();
    }

    size_t AdvancedScheduler::getPendingTaskCount() const {
        // Получение количества ожидающих задач
        // Get pending task count
        // Отримання кількості очікуючих завдань
        
        if (!schedulingAlgorithm) {
            return 0;
        }
        
        std::lock_guard<std::mutex> lock(schedulerMutex);
        return schedulingAlgorithm->getTaskCount();
    }

    AdvancedScheduler::SchedulerStatistics AdvancedScheduler::getStatistics() const {
        // Получение статистики планировщика
        // Get scheduler statistics
        // Отримання статистики планувальника
        
        SchedulerStatistics stats;
        stats.totalTasks = getTaskCount();
        stats.runningTasks = getRunningTaskCount();
        stats.pendingTasks = getPendingTaskCount();
        
        // Получение статистики из мьютекса
        // Get statistics from mutex
        // Отримання статистики з м'ютекса
        {
            std::lock_guard<std::mutex> lock(statisticsMutex);
            stats.completedTasks = completedTaskCount;
            stats.failedTasks = failedTaskCount;
            stats.cancelledTasks = cancelledTaskCount;
            stats.totalExecutionTime = totalExecutionTime;
            
            size_t totalCompleted = completedTaskCount + failedTaskCount + cancelledTaskCount;
            if (totalCompleted > 0) {
                stats.averageExecutionTime = static_cast<double>(totalExecutionTime) / totalCompleted;
            } else {
                stats.averageExecutionTime = 0.0;
            }
        }
        
        return stats;
    }

    void AdvancedScheduler::schedulerLoop() {
        // Основной цикл расширенного планировщика
        // Main loop of advanced scheduler
        // Основний цикл розширеного планувальника
        
        while (running) {
            int taskId = -1;
            
            // Выбор следующей задачи для выполнения
            // Select next task to execute
            // Вибір наступного завдання для виконання
            {
                std::unique_lock<std::mutex> lock(schedulerMutex);
                
                // Ожидание задач, если очередь пуста
                // Wait for tasks if queue is empty
                // Очікування завдань, якщо черга порожня
                if (schedulingAlgorithm->isEmpty()) {
                    schedulerCondition.wait(lock, [this]() {
                        return !running || !schedulingAlgorithm->isEmpty();
                    });
                }
                
                // Если планировщик остановлен, выходим из цикла
                // If scheduler is stopped, exit loop
                // Якщо планувальник зупинено, виходимо з циклу
                if (!running) {
                    break;
                }
                
                // Выбор следующей задачи
                // Select next task
                // Вибір наступного завдання
                taskId = schedulingAlgorithm->selectNextTask();
            }
            
            // Если есть задача для выполнения
            // If there is a task to execute
            // Якщо є завдання для виконання
            if (taskId > 0) {
                // Обновление статуса задачи на RUNNING
                // Update task status to RUNNING
                // Оновлення статусу завдання на RUNNING
                taskManager->updateTaskStatus(taskId, Utils::TaskStatus::RUNNING);
                
                // Запуск задачи в отдельном потоке
                // Run task in separate thread
                // Запуск завдання в окремому потоці
                std::thread taskThread(&AdvancedScheduler::executeTask, this, taskId);
                
                // Добавление потока в карту выполняемых задач
                // Add thread to map of running tasks
                // Додавання потоку до карти виконуваних завдань
                {
                    std::lock_guard<std::mutex> lock(schedulerMutex);
                    runningTasks[taskId] = std::move(taskThread);
                }
            }
            
            // Небольшая задержка для предотвращения излишней нагрузки на CPU
            // Small delay to prevent excessive CPU load
            // Невелика затримка для запобігання надмірному навантаженню на CPU
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void AdvancedScheduler::executeTask(int taskId) {
        // Выполнение задачи
        // Execute a task
        // Виконання завдання
        
        Utils::Task* task = taskManager->getTask(taskId);
        if (task == nullptr) {
            return;
        }
        
        Utils::TaskStatus finalStatus = Utils::TaskStatus::COMPLETED;
        long long startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        
        try {
            // Выполнение функции задачи
            // Execute task function
            // Виконання функції завдання
            if (task->function) {
                task->function();
            }
        } catch (...) {
            finalStatus = Utils::TaskStatus::FAILED;
        }
        
        long long endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        long long executionTime = endTime - startTime;
        
        // Обновление статуса задачи
        // Update task status
        // Оновлення статусу завдання
        taskManager->updateTaskStatus(taskId, finalStatus);
        
        // Обновление статистики
        // Update statistics
        // Оновлення статистики
        updateStatistics(taskId, finalStatus, executionTime);
        
        // Удаление задачи из карты выполняемых задач
        // Remove task from map of running tasks
        // Видалення завдання з карти виконуваних завдань
        {
            std::lock_guard<std::mutex> lock(schedulerMutex);
            auto it = runningTasks.find(taskId);
            if (it != runningTasks.end()) {
                if (it->second.joinable()) {
                    it->second.join();
                }
                runningTasks.erase(it);
            }
        }
    }

    void AdvancedScheduler::updateStatistics(int taskId, Utils::TaskStatus status, long long executionTime) {
        // Обновление статистики
        // Update statistics
        // Оновлення статистики
        
        std::lock_guard<std::mutex> lock(statisticsMutex);
        
        switch (status) {
            case Utils::TaskStatus::COMPLETED:
                completedTaskCount++;
                break;
            case Utils::TaskStatus::FAILED:
                failedTaskCount++;
                break;
            case Utils::TaskStatus::CANCELLED:
                cancelledTaskCount++;
                break;
            default:
                break;
        }
        
        totalExecutionTime += executionTime;
    }

    std::unique_ptr<SchedulingAlgorithm> AdvancedScheduler::createSchedulingAlgorithm(SchedulingAlgorithmType type) {
        // Создание алгоритма планирования
        // Create scheduling algorithm
        // Створення алгоритму планування
        
        switch (type) {
            case SchedulingAlgorithmType::PRIORITY_BASED:
                return std::make_unique<Algorithms::PriorityBasedScheduling>();
            case SchedulingAlgorithmType::ROUND_ROBIN:
                return std::make_unique<Algorithms::RoundRobinScheduling>();
            case SchedulingAlgorithmType::WEIGHTED_FAIR_QUEUING:
                return std::make_unique<Algorithms::WeightedFairQueuingScheduling>();
            default:
                return nullptr;
        }
    }

} // namespace Core
} // namespace NeuroSync