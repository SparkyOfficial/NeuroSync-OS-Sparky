#ifndef SCHEDULING_ALGORITHM_H
#define SCHEDULING_ALGORITHM_H

// SchedulingAlgorithm.h
// Интерфейс алгоритма планирования
// Scheduling algorithm interface
// Інтерфейс алгоритму планування

namespace NeuroSync {
namespace Core {

    // Базовый интерфейс для алгоритмов планирования
    // Base interface for scheduling algorithms
    // Базовий інтерфейс для алгоритмів планування
    class SchedulingAlgorithm {
    public:
        virtual ~SchedulingAlgorithm() = default;
        
        // Инициализация алгоритма
        // Initialize the algorithm
        // Ініціалізація алгоритму
        virtual void initialize() = 0;
        
        // Выбор следующей задачи для выполнения
        // Select the next task to execute
        // Вибір наступного завдання для виконання
        virtual int selectNextTask() = 0;
        
        // Добавление задачи в очередь
        // Add a task to the queue
        // Додавання завдання до черги
        virtual void addTask(int taskId, int priority) = 0;
        
        // Удаление задачи из очереди
        // Remove a task from the queue
        // Видалення завдання з черги
        virtual void removeTask(int taskId) = 0;
        
        // Обновление приоритета задачи
        // Update task priority
        // Оновлення пріоритету завдання
        virtual void updateTaskPriority(int taskId, int newPriority) = 0;
        
        // Получение количества задач в очереди
        // Get the number of tasks in the queue
        // Отримання кількості завдань у черзі
        virtual int getTaskCount() const = 0;
        
        // Проверка, пуста ли очередь
        // Check if the queue is empty
        // Перевірка, чи черга порожня
        virtual bool isEmpty() const = 0;
    };

} // namespace Core
} // namespace NeuroSync

#endif // SCHEDULING_ALGORITHM_H