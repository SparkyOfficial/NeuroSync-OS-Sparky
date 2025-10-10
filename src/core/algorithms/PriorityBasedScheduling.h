#ifndef PRIORITY_BASED_SCHEDULING_H
#define PRIORITY_BASED_SCHEDULING_H

#include "../interfaces/SchedulingAlgorithm.h"
#include <queue>
#include <vector>
#include <map>

// PriorityBasedScheduling.h
// Алгоритм планирования на основе приоритетов
// Priority-based scheduling algorithm
// Алгоритм планування на основі пріоритетів

namespace NeuroSync {
namespace Core {
namespace Algorithms {

    // Структура для представления задачи в очереди с приоритетом
    // Structure to represent a task in the priority queue
    // Структура для представлення завдання у черзі з пріоритетом
    struct PriorityTask {
        int taskId;
        int priority;
        long long timestamp; // Для обеспечения стабильности сортировки / For stable sorting / Для забезпечення стабільності сортування
        
        // Оператор сравнения для очереди с приоритетом
        // Comparison operator for priority queue
        // Оператор порівняння для черги з пріоритетом
        bool operator<(const PriorityTask& other) const {
            if (priority == other.priority) {
                return timestamp > other.timestamp; // FIFO для задач с одинаковым приоритетом / FIFO for tasks with the same priority / FIFO для завдань з однаковим пріоритетом
            }
            return priority < other.priority; // Высший приоритет имеет меньшее значение / Higher priority has a lower value / Вищий пріоритет має менше значення
        }
    };

    // Алгоритм планирования на основе приоритетов
    // Priority-based scheduling algorithm
    // Алгоритм планування на основі пріоритетів
    class PriorityBasedScheduling : public SchedulingAlgorithm {
    public:
        PriorityBasedScheduling();
        ~PriorityBasedScheduling() override;
        
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
        
    private:
        // Очередь с приоритетом для задач
        // Priority queue for tasks
        // Черга з пріоритетом для завдань
        std::priority_queue<PriorityTask> taskQueue;
        
        // Карта для отслеживания задач по ID
        // Map to track tasks by ID
        // Карта для відстеження завдань за ID
        std::map<int, PriorityTask> taskMap;
        
        // Счетчик времени для обеспечения стабильности сортировки
        // Time counter for stable sorting
        // Лічильник часу для забезпечення стабільності сортування
        long long timestampCounter;
        
        // Флаг инициализации
        // Initialization flag
        // Прапор ініціалізації
        bool initialized;
    };

} // namespace Algorithms
} // namespace Core
} // namespace NeuroSync

#endif // PRIORITY_BASED_SCHEDULING_H