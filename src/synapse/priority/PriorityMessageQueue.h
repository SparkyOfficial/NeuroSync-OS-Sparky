#ifndef PRIORITY_MESSAGE_QUEUE_H
#define PRIORITY_MESSAGE_QUEUE_H

#include <queue>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <atomic>

// PriorityMessageQueue.h
// Черга повідомлень з пріоритетом для SynapseBus
// Priority message queue for SynapseBus
// Очередь сообщений с приоритетом для SynapseBus

namespace NeuroSync {
namespace Synapse {
namespace Priority {

    // Тип пріоритету повідомлення
    // Message priority type
    // Тип приоритета сообщения
    enum class MessagePriority {
        LOW = 0,        // Низький пріоритет / Low priority / Низкий приоритет
        NORMAL = 1,     // Нормальний пріоритет / Normal priority / Нормальный приоритет
        HIGH = 2,       // Високий пріоритет / High priority / Высокий приоритет
        CRITICAL = 3    // Критичний пріоритет / Critical priority / Критический приоритет
    };

    // Структура повідомлення з пріоритетом
    // Priority message structure
    // Структура сообщения с приоритетом
    struct PriorityMessage {
        int messageId;              // Унікальний ID повідомлення / Unique message ID / Уникальный ID сообщения
        int senderId;               // ID відправника / Sender ID / ID отправителя
        int receiverId;             // ID отримувача / Receiver ID / ID получателя
        MessagePriority priority;    // Пріоритет повідомлення / Message priority / Приоритет сообщения
        int weight;                 // Вага повідомлення / Message weight / Вес сообщения
        long long timestamp;         // Часова мітка створення / Creation timestamp / Временная метка создания
        long long deadline;          // Кінцевий термін / Deadline / Крайний срок
        std::vector<char> data;     // Дані повідомлення / Message data / Данные сообщения
        size_t dataSize;            // Розмір даних / Data size / Размер данных
        
        // Оператор порівняння для черги з пріоритетом
        // Comparison operator for priority queue
        // Оператор сравнения для очереди с приоритетом
        bool operator<(const PriorityMessage& other) const {
            // Спочатку порівнюємо за пріоритетом (вищий пріоритет = менше значення)
            // First compare by priority (higher priority = lower value)
            // Сначала сравниваем по приоритету (высший приоритет = меньшее значение)
            if (priority != other.priority) {
                return priority < other.priority;
            }
            
            // Якщо пріоритети однакові, порівнюємо за терміном
            // If priorities are equal, compare by deadline
            // Если приоритеты равны, сравниваем по сроку
            if (deadline != other.deadline) {
                return deadline > other.deadline;
            }
            
            // Якщо терміни однакові, порівнюємо за часовою міткою (FIFO)
            // If deadlines are equal, compare by timestamp (FIFO)
            // Если сроки равны, сравниваем по временной метке (FIFO)
            return timestamp > other.timestamp;
        }
    };

    // Черга повідомлень з пріоритетом
    // Priority message queue
    // Очередь сообщений с приоритетом
    class PriorityMessageQueue {
    public:
        PriorityMessageQueue();
        ~PriorityMessageQueue();
        
        // Ініціалізація черги
        // Initialize queue
        // Инициализация очереди
        bool initialize();
        
        // Додавання повідомлення до черги
        // Add message to queue
        // Добавление сообщения в очередь
        bool enqueue(const PriorityMessage& message);
        
        // Вилучення повідомлення з черги
        // Dequeue message from queue
        // Извлечение сообщения из очереди
        bool dequeue(PriorityMessage& message);
        
        // Перегляд першого повідомлення без вилучення
        // Peek at first message without dequeuing
        // Просмотр первого сообщения без извлечения
        bool peek(PriorityMessage& message) const;
        
        // Отримання кількості повідомлень у черзі
        // Get number of messages in queue
        // Получение количества сообщений в очереди
        size_t size() const;
        
        // Перевірка, чи черга порожня
        // Check if queue is empty
        // Проверка, пуста ли очередь
        bool isEmpty() const;
        
        // Очищення черги
        // Clear queue
        // Очистка очереди
        void clear();
        
        // Встановлення максимального розміру черги
        // Set maximum queue size
        // Установка максимального размера очереди
        void setMaxSize(size_t maxSize);
        
        // Отримання максимального розміру черги
        // Get maximum queue size
        // Получение максимального размера очереди
        size_t getMaxSize() const;
        
        // Перевірка, чи черга досягла максимального розміру
        // Check if queue has reached maximum size
        // Проверка, достигла ли очередь максимального размера
        bool isFull() const;
        
        // Отримання статистики черги
        // Get queue statistics
        // Получение статистики очереди
        struct QueueStatistics {
            size_t totalMessages;       // Загальна кількість повідомлень / Total messages / Общее количество сообщений
            size_t droppedMessages;     // Кількість відкинутих повідомлень / Dropped messages / Количество отброшенных сообщений
            size_t lowPriorityMessages;  // Кількість повідомлень низького пріоритету / Low priority messages / Количество сообщений низкого приоритета
            size_t normalPriorityMessages; // Кількість повідомлень нормального пріоритету / Normal priority messages / Количество сообщений нормального приоритета
            size_t highPriorityMessages;   // Кількість повідомлень високого пріоритету / High priority messages / Количество сообщений высокого приоритета
            size_t criticalPriorityMessages; // Кількість повідомлень критичного пріоритету / Critical priority messages / Количество сообщений критического приоритета
            double averageWaitTime;      // Середній час очікування / Average wait time / Среднее время ожидания
        };
        
        QueueStatistics getStatistics() const;
        
        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        void updateStatistics(const PriorityMessage& message, bool dropped);
        
    private:
        // Внутрішня черга з пріоритетом
        // Internal priority queue
        // Внутренняя очередь с приоритетом
        std::priority_queue<PriorityMessage> messageQueue;
        
        // Мьютекс для синхронізації
        // Mutex for synchronization
        // Мьютекс для синхронизации
        mutable std::mutex queueMutex;
        
        // Умовна змінна для очікування
        // Condition variable for waiting
        // Условная переменная для ожидания
        std::condition_variable queueCondition;
        
        // Максимальний розмір черги
        // Maximum queue size
        // Максимальный размер очереди
        size_t maxSize;
        
        // Статистика
        // Statistics
        // Статистика
        mutable std::mutex statisticsMutex;
        QueueStatistics stats;
        
        // Лічильник ID повідомлень
        // Message ID counter
        // Счетчик ID сообщений
        std::atomic<int> messageIdCounter;
        
        // Флаг ініціалізації
        // Initialization flag
        // Флаг инициализации
        std::atomic<bool> initialized;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        int generateMessageId();
        long long getCurrentTimeMillis() const;
        void updatePriorityStatistics(const PriorityMessage& message);
    };

} // namespace Priority
} // namespace Synapse
} // namespace NeuroSync

#endif // PRIORITY_MESSAGE_QUEUE_H