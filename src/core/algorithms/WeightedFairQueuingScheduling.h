#ifndef WEIGHTED_FAIR_QUEUING_SCHEDULING_H
#define WEIGHTED_FAIR_QUEUING_SCHEDULING_H

#include "../interfaces/SchedulingAlgorithm.h"
#include <queue>
#include <map>
#include <vector>

// WeightedFairQueuingScheduling.h
// Алгоритм планирования Weighted Fair Queuing
// Weighted Fair Queuing scheduling algorithm
// Алгоритм планування Weighted Fair Queuing

namespace NeuroSync {
namespace Core {
namespace Algorithms {

    // Структура для представления задачи в алгоритме Weighted Fair Queuing
    // Structure to represent a task in Weighted Fair Queuing algorithm
    // Структура для представлення завдання в алгоритмі Weighted Fair Queuing
    struct WFQTask {
        int taskId;
        int priority;
        int weight;
        double virtualFinishTime; // Виртуальное время завершения / Virtual finish time / Віртуальний час завершення
        long long timestamp; // Временная метка для стабильности / Timestamp for stability / Тимчасова мітка для стабільності
        
        // Оператор сравнения для очереди с приоритетом
        // Comparison operator for priority queue
        // Оператор порівняння для черги з пріоритетом
        bool operator<(const WFQTask& other) const {
            if (virtualFinishTime == other.virtualFinishTime) {
                return timestamp > other.timestamp; // FIFO для задач с одинаковым временем / FIFO for tasks with the same time / FIFO для завдань з однаковим часом
            }
            return virtualFinishTime > other.virtualFinishTime; // Минимальное время завершения первое / Minimum finish time first / Мінімальний час завершення перший
        }
    };

    // Алгоритм планирования Weighted Fair Queuing
    // Weighted Fair Queuing scheduling algorithm
    // Алгоритм планування Weighted Fair Queuing
    class WeightedFairQueuingScheduling : public SchedulingAlgorithm {
    public:
        WeightedFairQueuingScheduling();
        ~WeightedFairQueuingScheduling() override;
        
        // Инициализация алгоритма
        // Initialize the algorithm
        // Ініціалізація алгоритму
        void initialize() override;
        
        // Выбор следующей задачи для выполнения
        // Select the next task to execute
        // Вибір наступного завдання для виконання
        int selectNextTask() override;
        
        // Добавление задачи в очередь
        // Add a task to the queue
        // Додавання завдання до черги
        void addTask(int taskId, int priority) override;
        
        // Удаление задачи из очереди
        // Remove a task from the queue
        // Видалення завдання з черги
        void removeTask(int taskId) override;
        
        // Обновление приоритета задачи
        // Update task priority
        // Оновлення пріоритету завдання
        void updateTaskPriority(int taskId, int newPriority) override;
        
        // Получение количества задач в очереди
        // Get the number of tasks in the queue
        // Отримання кількості завдань у черзі
        int getTaskCount() const override;
        
        // Проверка, пуста ли очередь
        // Check if the queue is empty
        // Перевірка, чи черга порожня
        bool isEmpty() const override;
        
        // Установка веса задачи
        // Set task weight
        // Встановлення ваги завдання
        void setTaskWeight(int taskId, int weight);
        
    private:
        // Очередь с приоритетом для задач WFQ
        // Priority queue for WFQ tasks
        // Черга з пріоритетом для завдань WFQ
        std::priority_queue<WFQTask> taskQueue;
        
        // Карта для отслеживания задач по ID
        // Map to track tasks by ID
        // Карта для відстеження завдань за ID
        std::map<int, WFQTask> taskMap;
        
        // Виртуальное время системы
        // System virtual time
        // Віртуальний час системи
        double systemVirtualTime;
        
        // Счетчик времени для обеспечения стабильности сортировки
        // Time counter for stable sorting
        // Лічильник часу для забезпечення стабільності сортування
        long long timestampCounter;
        
        // Флаг инициализации
        // Initialization flag
        // Прапор ініціалізації
        bool initialized;
        
        // Вес по умолчанию
        // Default weight
        // Вага за замовчуванням
        static const int DEFAULT_WEIGHT = 1;
    };

} // namespace Algorithms
} // namespace Core
} // namespace NeuroSync

#endif // WEIGHTED_FAIR_QUEUING_SCHEDULING_H