#include "PriorityBasedScheduling.h"
#include <algorithm>
#include <chrono>

// PriorityBasedScheduling.cpp
// Реализация алгоритма планирования на основе приоритетов
// Implementation of priority-based scheduling algorithm
// Реалізація алгоритму планування на основі пріоритетів

namespace NeuroSync {
namespace Core {
namespace Algorithms {

    PriorityBasedScheduling::PriorityBasedScheduling() 
        : timestampCounter(0), initialized(false) {
        // Конструктор алгоритма планирования на основе приоритетов
        // Constructor of priority-based scheduling algorithm
        // Конструктор алгоритму планування на основі пріоритетів
    }

    PriorityBasedScheduling::~PriorityBasedScheduling() {
        // Деструктор алгоритма планирования на основе приоритетов
        // Destructor of priority-based scheduling algorithm
        // Деструктор алгоритму планування на основі пріоритетів
    }

    void PriorityBasedScheduling::initialize() {
        // Инициализация алгоритма планирования на основе приоритетов
        // Initialize priority-based scheduling algorithm
        // Ініціалізація алгоритму планування на основі пріоритетів
        
        // Очистка существующих данных
        // Clear existing data
        // Очищення існуючих даних
        while (!taskQueue.empty()) {
            taskQueue.pop();
        }
        taskMap.clear();
        timestampCounter = 0;
        
        initialized = true;
    }

    int PriorityBasedScheduling::selectNextTask() {
        // Выбор следующей задачи для выполнения на основе приоритетов
        // Select the next task to execute based on priorities
        // Вибір наступного завдання для виконання на основі пріоритетів
        
        if (!initialized || taskQueue.empty()) {
            return -1; // Нет доступных задач / No available tasks / Немає доступних завдань
        }
        
        PriorityTask nextTask = taskQueue.top();
        taskQueue.pop();
        
        // Удаление задачи из карты
        // Remove task from map
        // Видалення завдання з карти
        taskMap.erase(nextTask.taskId);
        
        return nextTask.taskId;
    }

    void PriorityBasedScheduling::addTask(int taskId, int priority) {
        // Добавление задачи в очередь с приоритетом
        // Add a task to the priority queue
        // Додавання завдання до черги з пріоритетом
        
        if (!initialized) {
            return;
        }
        
        // Проверка, существует ли задача с таким ID
        // Check if a task with this ID already exists
        // Перевірка, чи існує завдання з таким ID
        if (taskMap.find(taskId) != taskMap.end()) {
            return; // Задача уже существует / Task already exists / Завдання вже існує
        }
        
        // Создание новой задачи с временной меткой
        // Create a new task with timestamp
        // Створення нового завдання з тимчасовою міткою
        PriorityTask newTask;
        newTask.taskId = taskId;
        newTask.priority = priority;
        newTask.timestamp = timestampCounter++;
        
        // Добавление задачи в очередь и карту
        // Add task to queue and map
        // Додавання завдання до черги та карти
        taskQueue.push(newTask);
        taskMap[taskId] = newTask;
    }

    void PriorityBasedScheduling::removeTask(int taskId) {
        // Удаление задачи из очереди с приоритетом
        // Remove a task from the priority queue
        // Видалення завдання з черги з пріоритетом
        
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
            std::priority_queue<PriorityTask> newQueue;
            std::vector<PriorityTask> tempTasks;
            
            // Извлечение всех задач из очереди
            // Extract all tasks from queue
            // Вилучення всіх завдань з черги
            while (!taskQueue.empty()) {
                PriorityTask task = taskQueue.top();
                taskQueue.pop();
                if (task.taskId != taskId) {
                    tempTasks.push_back(task);
                }
            }
            
            // Повторная вставка задач в очередь
            // Re-insert tasks into queue
            // Повторне вставлення завдань до черги
            for (const auto& task : tempTasks) {
                taskQueue.push(task);
            }
        }
    }

    void PriorityBasedScheduling::updateTaskPriority(int taskId, int newPriority) {
        // Обновление приоритета задачи
        // Update task priority
        // Оновлення пріоритету завдання
        
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

    int PriorityBasedScheduling::getTaskCount() const {
        // Получение количества задач в очереди
        // Get the number of tasks in the queue
        // Отримання кількості завдань у черзі
        
        return static_cast<int>(taskMap.size());
    }

    bool PriorityBasedScheduling::isEmpty() const {
        // Проверка, пуста ли очередь
        // Check if the queue is empty
        // Перевірка, чи черга порожня
        
        return taskMap.empty();
    }

} // namespace Algorithms
} // namespace Core
} // namespace NeuroSync