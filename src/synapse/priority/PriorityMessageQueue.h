#ifndef PRIORITY_MESSAGE_QUEUE_H
#define PRIORITY_MESSAGE_QUEUE_H

#include <queue>
#include <vector>
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

    // Пріоритет повідомлення
    // Message priority
    // Приоритет сообщения
    enum class MessagePriority {
        LOW = 0,
        NORMAL = 1,
        HIGH = 2,
        CRITICAL = 3
    };

    // Структура повідомлення з пріоритетом
    // Priority message structure
    // Структура сообщения с приоритетом
    struct PriorityMessage {
        int messageId;
        int senderId;
        int receiverId;
        MessagePriority priority;
        int weight;
        long long timestamp;
        long long deadline;
        std::vector<char> data;
        size_t dataSize;
        
        // Оператор порівняння для черги з пріоритетом
        // Comparison operator for priority queue
        // Оператор сравнения для очереди с приоритетом
        bool operator<(const PriorityMessage& other) const {
            // Спочатку повідомлення з вищим пріоритетом
            // First messages with higher priority
            // Сначала сообщения с более высоким приоритетом
            if (priority != other.priority) {
                return priority < other.priority;
            }
            
            // Потім повідомлення з більшою вагою
            // Then messages with greater weight
            // Затем сообщения с большим весом
            if (weight != other.weight) {
                return weight < other.weight;
            }
            
            // Нарешті, повідомлення з більш раннім терміном
            // Finally, messages with earlier deadline
            // Наконец, сообщения с более ранним сроком
            return deadline > other.deadline;
        }
    };

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
        
        // Статистика черги
        // Queue statistics
        // Статистика очереди
        struct QueueStatistics {
            size_t totalMessages;
            size_t droppedMessages;
            size_t lowPriorityMessages;
            size_t normalPriorityMessages;
            size_t highPriorityMessages;
            size_t criticalPriorityMessages;
            double averageWaitTime;
        };
        
        // Отримання статистики черги
        // Get queue statistics
        // Получение статистики очереди
        QueueStatistics getStatistics() const;
        
        // Встановлення флагу зупинки
        // Set stopping flag
        // Установка флага остановки
        void setStopping(bool stopping);
        
    private:
        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        void updateStatistics(const PriorityMessage& message, bool dropped);
        
        // Генерація ID повідомлення
        // Generate message ID
        // Генерация ID сообщения
        int generateMessageId();
        
        // Отримання поточного часу в мілісекундах
        // Get current time in milliseconds
        // Получение текущего времени в миллисекундах
        long long getCurrentTimeMillis() const;
        
        // Оновлення статистики за пріоритетом
        // Update priority statistics
        // Обновление статистики по приоритету
        void updatePriorityStatistics(const PriorityMessage& message);
        
        // Черга повідомлень з пріоритетом
        // Priority message queue
        // Очередь сообщений с приоритетом
        std::priority_queue<PriorityMessage> messageQueue;
        
        // Мьютекс для синхронізації доступу до черги
        // Mutex for synchronizing access to queue
        // Мьютекс для синхронизации доступа к очереди
        mutable std::mutex queueMutex;
        
        // Умова для очікування повідомлень
        // Condition for waiting for messages
        // Условие для ожидания сообщений
        std::condition_variable queueCondition;
        
        // Мьютекс для синхронізації доступу до статистики
        // Mutex for synchronizing access to statistics
        // Мьютекс для синхронизации доступа к статистике
        mutable std::mutex statisticsMutex;
        
        // Статистика черги
        // Queue statistics
        // Статистика очереди
        QueueStatistics stats;
        
        // Максимальний розмір черги
        // Maximum queue size
        // Максимальный размер очереди
        size_t maxSize;
        
        // Лічильник ID повідомлень
        // Message ID counter
        // Счетчик ID сообщений
        std::atomic<int> messageIdCounter;
        
        // Флаг ініціалізації
        // Initialization flag
        // Флаг инициализации
        std::atomic<bool> initialized;
        
        // Флаг зупинки
        // Stopping flag
        // Флаг остановки
        std::atomic<bool> stopping;
    };

} // namespace Priority
} // namespace Synapse
} // namespace NeuroSync

#endif // PRIORITY_MESSAGE_QUEUE_H