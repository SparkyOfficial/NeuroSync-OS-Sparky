#include "WeightedFairQueuingScheduling.h"
#include <algorithm>
#include <limits>

// WeightedFairQueuingScheduling.cpp
// Реализация алгоритма планирования Weighted Fair Queuing
// Implementation of Weighted Fair Queuing scheduling algorithm
// Реалізація алгоритму планування Weighted Fair Queuing

namespace NeuroSync {
namespace Core {
namespace Algorithms {

    WeightedFairQueuingScheduling::WeightedFairQueuingScheduling() 
        : systemVirtualTime(0.0), timestampCounter(0), initialized(false) {
        // Конструктор алгоритма планирования Weighted Fair Queuing
        // Constructor of Weighted Fair Queuing scheduling algorithm
        // Конструктор алгоритму планування Weighted Fair Queuing
    }

    WeightedFairQueuingScheduling::~WeightedFairQueuingScheduling() {
        // Деструктор алгоритма планирования Weighted Fair Queuing
        // Destructor of Weighted Fair Queuing scheduling algorithm
        // Деструктор алгоритму планування Weighted Fair Queuing
    }

    void WeightedFairQueuingScheduling::initialize() {
        // Инициализация алгоритма планирования Weighted Fair Queuing
        // Initialize Weighted Fair Queuing scheduling algorithm
        // Ініціалізація алгоритму планування Weighted Fair Queuing
        
        // Очистка существующих данных
        // Clear existing data
        // Очищення існуючих даних
        while (!taskQueue.empty()) {
            taskQueue.pop();
        }
        taskMap.clear();
        systemVirtualTime = 0.0;
        timestampCounter = 0;
        
        initialized = true;
    }

    int WeightedFairQueuingScheduling::selectNextTask() {
        // Выбор следующей задачи для выполнения по алгоритму Weighted Fair Queuing
        // Select the next task to execute using Weighted Fair Queuing algorithm
        // Вибір наступного завдання для виконання за алгоритмом Weighted Fair Queuing
        
        if (!initialized || taskQueue.empty()) {
            return -1; // Нет доступных задач / No available tasks / Немає доступних завдань
        }
        
        WFQTask nextTask = taskQueue.top();
        taskQueue.pop();
        
        // Обновление виртуального времени системы
        // Update system virtual time
        // Оновлення віртуального часу системи
        systemVirtualTime = nextTask.virtualFinishTime;
        
        // Удаление задачи из карты
        // Remove task from map
        // Видалення завдання з карти
        taskMap.erase(nextTask.taskId);
        
        return nextTask.taskId;
    }

    void WeightedFairQueuingScheduling::addTask(int taskId, int priority) {
        // Добавление задачи в очередь Weighted Fair Queuing
        // Add a task to the Weighted Fair Queuing queue
        // Додавання завдання до черги Weighted Fair Queuing
        
        if (!initialized) {
            return;
        }
        
        // Проверка, существует ли задача с таким ID
        // Check if a task with this ID already exists
        // Перевірка, чи існує завдання з таким ID
        if (taskMap.find(taskId) != taskMap.end()) {
            return; // Задача уже существует / Task already exists / Завдання вже існує
        }
        
        // Создание новой задачи с виртуальным временем завершения
        // Create a new task with virtual finish time
        // Створення нового завдання з віртуальним часом завершення
        WFQTask newTask;
        newTask.taskId = taskId;
        newTask.priority = priority;
        newTask.weight = DEFAULT_WEIGHT;
        newTask.timestamp = timestampCounter++;
        
        // Вычисление виртуального времени завершения
        // Calculate virtual finish time
        // Обчислення віртуального часу завершення
        double serviceTime = 1.0 / newTask.weight; // Время обслуживания / Service time / Час обслуговування
        newTask.virtualFinishTime = systemVirtualTime + serviceTime;
        
        // Добавление задачи в очередь и карту
        // Add task to queue and map
        // Додавання завдання до черги та карти
        taskQueue.push(newTask);
        taskMap[taskId] = newTask;
    }

    void WeightedFairQueuingScheduling::removeTask(int taskId) {
        // Удаление задачи из очереди Weighted Fair Queuing
        // Remove a task from the Weighted Fair Queuing queue
        // Видалення завдання з черги Weighted Fair Queuing
        
        if (!initialized) {
            return;
        }
        
        // Поиск задачи в карте
        // Find task in map
        // Пошук завдання в карті
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            // Удаление задачи из карты
            // Remove task from map
            // Видалення завдання з карти
            taskMap.erase(it);
            
            // Перестройка очереди без удаленной задачи
            // Rebuild queue without the removed task
            // Перебудова черги без видаленого завдання
            std::priority_queue<WFQTask> newQueue;
            std::vector<WFQTask> tempTasks;
            
            // Извлечение всех задач из очереди
            // Extract all tasks from queue
            // Вилучення всіх завдань з черги
            while (!taskQueue.empty()) {
                WFQTask task = taskQueue.top();
                taskQueue.pop();
                if (task.taskId != taskId) {
                    tempTasks.push_back(task);
                }
            }
            
            // Повторная вставка задач в очередь
            // Re-insert tasks into queue
            // Повторне вставлення завдань до черги
            for (const auto& task : tempTasks) {
                newQueue.push(task);
            }
            
            // Замена старой очереди новой
            // Replace old queue with new queue
            // Заміна старої черги новою
            taskQueue = newQueue;
        }
    }

    void WeightedFairQueuingScheduling::updateTaskPriority(int taskId, int newPriority) {
        // Обновление приоритета задачи в алгоритме Weighted Fair Queuing
        // Update task priority in Weighted Fair Queuing algorithm
        // Оновлення пріоритету завдання в алгоритмі Weighted Fair Queuing
        
        if (!initialized) {
            return;
        }
        
        // Поиск задачи в карте
        // Find task in map
        // Пошук завдання в карті
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            // Удаление старой задачи
            // Remove old task
            // Видалення старого завдання
            removeTask(taskId);
            
            // Добавление задачи с новым приоритетом
            // Add task with new priority
            // Додавання завдання з новим пріоритетом
            addTask(taskId, newPriority);
        }
    }

    int WeightedFairQueuingScheduling::getTaskCount() const {
        // Получение количества задач в очереди
        // Get the number of tasks in the queue
        // Отримання кількості завдань у черзі
        
        return static_cast<int>(taskMap.size());
    }

    bool WeightedFairQueuingScheduling::isEmpty() const {
        // Проверка, пуста ли очередь
        // Check if the queue is empty
        // Перевірка, чи черга порожня
        
        return taskMap.empty();
    }

    void WeightedFairQueuingScheduling::setTaskWeight(int taskId, int weight) {
        // Установка веса задачи в алгоритме Weighted Fair Queuing
        // Set task weight in Weighted Fair Queuing algorithm
        // Встановлення ваги завдання в алгоритмі Weighted Fair Queuing
        
        if (!initialized) {
            return;
        }
        
        // Поиск задачи в карте
        // Find task in map
        // Пошук завдання в карті
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            // Обновление веса задачи
            // Update task weight
            // Оновлення ваги завдання
            WFQTask& task = it->second;
            int oldWeight = task.weight;
            task.weight = weight;
            
            // Пересчет виртуального времени завершения
            // Recalculate virtual finish time
            // Перерахунок віртуального часу завершення
            double serviceTime = 1.0 / task.weight;
            task.virtualFinishTime = systemVirtualTime + serviceTime;
            
            // Удаление и повторное добавление задачи для пересортировки
            // Remove and re-add task for resorting
            // Видалення та повторне додавання завдання для пересортування
            removeTask(taskId);
            taskQueue.push(task);
            taskMap[taskId] = task;
        }
    }

} // namespace Algorithms
} // namespace Core
} // namespace NeuroSync