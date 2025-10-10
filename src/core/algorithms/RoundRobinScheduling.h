#ifndef ROUND_ROBIN_SCHEDULING_H
#define ROUND_ROBIN_SCHEDULING_H

#include "../interfaces/SchedulingAlgorithm.h"
#include <deque>
#include <map>

// RoundRobinScheduling.h
// Алгоритм планирования Round Robin
// Round Robin scheduling algorithm
// Алгоритм планування Round Robin

namespace NeuroSync {
namespace Core {
namespace Algorithms {

    // Структура для представления задачи в циклической очереди
    // Structure to represent a task in the circular queue
    // Структура для представлення завдання у циклічній черзі
    struct RoundRobinTask {
        int taskId;
        int priority;
        int timeQuantum; // Квант времени для задачи / Time quantum for the task / Квант часу для завдання
        int remainingTime; // Оставшееся время выполнения / Remaining execution time / Залишковий час виконання
    };

    // Алгоритм планирования Round Robin
    // Round Robin scheduling algorithm
    // Алгоритм планування Round Robin
    class RoundRobinScheduling : public SchedulingAlgorithm {
    public:
        RoundRobinScheduling(int defaultTimeQuantum = 10);
        ~RoundRobinScheduling() override;
        
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
        
        // Установка кванта времени по умолчанию
        // Set default time quantum
        // Встановлення кванта часу за замовчуванням
        void setDefaultTimeQuantum(int quantum);
        
    private:
        // Циклическая очередь для задач
        // Circular queue for tasks
        // Циклічна черга для завдань
        std::deque<RoundRobinTask> taskQueue;
        
        // Карта для отслеживания задач по ID
        // Map to track tasks by ID
        // Карта для відстеження завдань за ID
        std::map<int, RoundRobinTask> taskMap;
        
        // Квант времени по умолчанию
        // Default time quantum
        // Квант часу за замовчуванням
        int defaultTimeQuantum;
        
        // Индекс текущей задачи
        // Current task index
        // Індекс поточного завдання
        size_t currentTaskIndex;
        
        // Флаг инициализации
        // Initialization flag
        // Прапор ініціалізації
        bool initialized;
    };

} // namespace Algorithms
} // namespace Core
} // namespace NeuroSync

#endif // ROUND_ROBIN_SCHEDULING_H