#include "RoundRobinScheduling.h"
#include <algorithm>

// RoundRobinScheduling.cpp
// Реализация алгоритма планирования Round Robin
// Implementation of Round Robin scheduling algorithm
// Реалізація алгоритму планування Round Robin

namespace NeuroSync {
namespace Core {
namespace Algorithms {

    RoundRobinScheduling::RoundRobinScheduling(int defaultTimeQuantum)
        : defaultTimeQuantum(defaultTimeQuantum), currentTaskIndex(0), initialized(false) {
        // Конструктор алгоритма планирования Round Robin
        // Constructor of Round Robin scheduling algorithm
        // Конструктор алгоритму планування Round Robin
    }

    RoundRobinScheduling::~RoundRobinScheduling() {
        // Деструктор алгоритма планирования Round Robin
        // Destructor of Round Robin scheduling algorithm
        // Деструктор алгоритму планування Round Robin
    }

    void RoundRobinScheduling::initialize() {
        // Инициализация алгоритма планирования Round Robin
        // Initialize Round Robin scheduling algorithm
        // Ініціалізація алгоритму планування Round Robin
        
        // Очистка существующих данных
        // Clear existing data
        // Очищення існуючих даних
        taskQueue.clear();
        taskMap.clear();
        currentTaskIndex = 0;
        
        initialized = true;
    }

    int RoundRobinScheduling::selectNextTask() {
        // Выбор следующей задачи для выполнения по алгоритму Round Robin
        // Select the next task to execute using Round Robin algorithm
        // Вибір наступного завдання для виконання за алгоритмом Round Robin
        
        if (!initialized || taskQueue.empty()) {
            return -1; // Нет доступных задач / No available tasks / Немає доступних завдань
        }
        
        // Если индекс вышел за границы, сбросить его
        // If index is out of bounds, reset it
        // Якщо індекс вийшов за межі, скинути його
        if (currentTaskIndex >= taskQueue.size()) {
            currentTaskIndex = 0;
        }
        
        // Получение текущей задачи
        // Get current task
        // Отримання поточного завдання
        RoundRobinTask currentTask = taskQueue[currentTaskIndex];
        
        // Уменьшение оставшегося времени
        // Decrease remaining time
        // Зменшення залишкового часу
        currentTask.remainingTime -= 1;
        
        // Обновление задачи в очереди
        // Update task in queue
        // Оновлення завдання в черзі
        taskQueue[currentTaskIndex] = currentTask;
        
        // Обновление задачи в карте
        // Update task in map
        // Оновлення завдання в карті
        taskMap[currentTask.taskId] = currentTask;
        
        // Переход к следующей задаче
        // Move to next task
        // Перехід до наступного завдання
        currentTaskIndex = (currentTaskIndex + 1) % taskQueue.size();
        
        return currentTask.taskId;
    }

    void RoundRobinScheduling::addTask(int taskId, int priority) {
        // Добавление задачи в циклическую очередь
        // Add a task to the circular queue
        // Додавання завдання до циклічної черги
        
        if (!initialized) {
            return;
        }
        
        // Проверка, существует ли задача с таким ID
        // Check if a task with this ID already exists
        // Перевірка, чи існує завдання з таким ID
        if (taskMap.find(taskId) != taskMap.end()) {
            return; // Задача уже существует / Task already exists / Завдання вже існує
        }
        
        // Создание новой задачи
        // Create a new task
        // Створення нового завдання
        RoundRobinTask newTask;
        newTask.taskId = taskId;
        newTask.priority = priority;
        newTask.timeQuantum = defaultTimeQuantum;
        newTask.remainingTime = defaultTimeQuantum;
        
        // Добавление задачи в очередь и карту
        // Add task to queue and map
        // Додавання завдання до черги та карти
        taskQueue.push_back(newTask);
        taskMap[taskId] = newTask;
    }

    void RoundRobinScheduling::removeTask(int taskId) {
        // Удаление задачи из циклической очереди
        // Remove a task from the circular queue
        // Видалення завдання з циклічної черги
        
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
            
            // Поиск и удаление задачи из очереди
            // Find and remove task from queue
            // Пошук та видалення завдання з черги
            auto queueIt = std::find_if(taskQueue.begin(), taskQueue.end(),
                [taskId](const RoundRobinTask& task) {
                    return task.taskId == taskId;
                });
            
            if (queueIt != taskQueue.end()) {
                // Сохранение индекса для корректировки currentTaskIndex
                // Save index for currentTaskIndex adjustment
                // Збереження індексу для коригування currentTaskIndex
                size_t removedIndex = std::distance(taskQueue.begin(), queueIt);
                
                // Удаление задачи из очереди
                // Remove task from queue
                // Видалення завдання з черги
                taskQueue.erase(queueIt);
                
                // Корректировка индекса текущей задачи
                // Adjust current task index
                // Коригування індексу поточного завдання
                if (currentTaskIndex > removedIndex) {
                    currentTaskIndex--;
                } else if (currentTaskIndex == removedIndex && !taskQueue.empty()) {
                    currentTaskIndex = currentTaskIndex % taskQueue.size();
                } else if (taskQueue.empty()) {
                    currentTaskIndex = 0;
                }
            }
        }
    }

    void RoundRobinScheduling::updateTaskPriority(int taskId, int newPriority) {
        // Обновление приоритета задачи в алгоритме Round Robin
        // Update task priority in Round Robin algorithm
        // Оновлення пріоритету завдання в алгоритмі Round Robin
        
        if (!initialized) {
            return;
        }
        
        // Поиск задачи в карте
        // Find task in map
        // Пошук завдання в карті
        auto it = taskMap.find(taskId);
        if (it != taskMap.end()) {
            // Обновление приоритета задачи
            // Update task priority
            // Оновлення пріоритету завдання
            RoundRobinTask& task = it->second;
            task.priority = newPriority;
            
            // Поиск и обновление задачи в очереди
            // Find and update task in queue
            // Пошук та оновлення завдання в черзі
            auto queueIt = std::find_if(taskQueue.begin(), taskQueue.end(),
                [taskId](const RoundRobinTask& task) {
                    return task.taskId == taskId;
                });
            
            if (queueIt != taskQueue.end()) {
                queueIt->priority = newPriority;
            }
        }
    }

    int RoundRobinScheduling::getTaskCount() const {
        // Получение количества задач в очереди
        // Get the number of tasks in the queue
        // Отримання кількості завдань у черзі
        
        return static_cast<int>(taskMap.size());
    }

    bool RoundRobinScheduling::isEmpty() const {
        // Проверка, пуста ли очередь
        // Check if the queue is empty
        // Перевірка, чи черга порожня
        
        return taskMap.empty();
    }

    void RoundRobinScheduling::setDefaultTimeQuantum(int quantum) {
        // Установка кванта времени по умолчанию
        // Set default time quantum
        // Встановлення кванта часу за замовчуванням
        
        defaultTimeQuantum = quantum;
    }

} // namespace Algorithms
} // namespace Core
} // namespace NeuroSync