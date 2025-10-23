#include "PriorityMessageQueue.h"
#include <chrono>
#include <algorithm>
#include <iostream>

// PriorityMessageQueue.cpp
// Реалізація черги повідомлень з пріоритетом для SynapseBus
// Implementation of priority message queue for SynapseBus
// Реализация очереди сообщений с приоритетом для SynapseBus
// Author: Андрій Будильников

namespace NeuroSync {
namespace Synapse {
namespace Priority {

    PriorityMessageQueue::PriorityMessageQueue() 
        : maxSize(1000), messageIdCounter(1), initialized(false), stopping(false) {
        // Конструктор черги повідомлень з пріоритетом
        // Constructor of priority message queue
        // Конструктор очереди сообщений с приоритетом
        
        // Ініціалізація статистики
        // Initialize statistics
        // Инициализация статистики
        stats.totalMessages = 0;
        stats.droppedMessages = 0;
        stats.lowPriorityMessages = 0;
        stats.normalPriorityMessages = 0;
        stats.highPriorityMessages = 0;
        stats.criticalPriorityMessages = 0;
        stats.averageWaitTime = 0.0;
    }

    PriorityMessageQueue::~PriorityMessageQueue() {
        // Деструктор черги повідомлень з пріоритетом
        // Destructor of priority message queue
        // Деструктор очереди сообщений с приоритетом
        clear();
    }

    bool PriorityMessageQueue::initialize() {
        // Ініціалізація черги
        // Initialize queue
        // Инициализация очереди
        
        if (initialized) {
            return true; // Вже ініціалізовано / Already initialized / Уже инициализировано
        }
        
        // Скидання лічильника ID
        // Reset ID counter
        // Сброс счетчика ID
        messageIdCounter = 1;
        
        // Очищення черги
        // Clear queue
        // Очистка очереди
        clear();
        
        initialized = true;
        stopping = false;
        return true;
    }

    bool NeuroSync::Synapse::Priority::PriorityMessageQueue::enqueue(const PriorityMessage& message) {
        // Додавання повідомлення до черги
        // Add message to queue
        // Добавление сообщения в очередь

        // перевірка чи черга ініціалізована і не зупиняється
        // check if queue is initialized and not stopping
        // проверка инициализации очереди и что она не останавливается
        if (!initialized || stopping) {
            return false;
        }

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            
            // Перевірка, чи черга не переповнена
            // Check if queue is not full
            // Проверка, не переполнена ли очередь
            if (isFull()) {
                return false; // Черга переповнена / Queue is full / Очередь переполнена
            }
            
            // Додавання повідомлення до черги
            // Add message to queue
            // Добавление сообщения в очередь
            messageQueue.push(message);
        } // блокування звільняється тут / lock released here / блокировка освобождается здесь
        
        // Сповіщення очікуючих потоків
        // Notify waiting threads
        // Уведомление ожидающих потоков
        queueCondition.notify_one();
        
        return true;
    }

    bool NeuroSync::Synapse::Priority::PriorityMessageQueue::dequeue(PriorityMessage& message) {
        // Вилучення повідомлення з черги
        // Dequeue message from queue
        // Извлечение сообщения из очереди

        // перевірка ініціалізації
        // check initialization
        // проверка инициализации
        if (!initialized) {
            return false;
        }

        std::unique_lock<std::mutex> lock(queueMutex);

        // Очікування, поки черга не стане непорожньою з таймаутом
        // Wait until queue is not empty with timeout
        // Ожидание, пока очередь не станет непустой с таймаутом
        // якщо черга вже не порожня, не чекаємо
        // if queue is already not empty, don't wait
        // если очередь уже не пуста, не ждем
        if (messageQueue.empty() && initialized && !stopping) {
            auto waitResult = queueCondition.wait_for(lock, std::chrono::milliseconds(100), [this]() {
                return !messageQueue.empty() || !initialized || stopping;
            });
            
            // Якщо після очікування черга все ще порожня, або система не ініціалізована, або зупиняється, повертаємо false
            // If after waiting the queue is still empty, or system is not initialized, or stopping, return false
            // Если после ожидания очередь все еще пуста, или система не инициализирована, или останавливается, возвращаем false
            if (messageQueue.empty() || !initialized || stopping) {
                return false;
            }
        } else if (messageQueue.empty() || !initialized || stopping) {
            // Якщо черга порожня, або система не ініціалізована, або зупиняється, повертаємо false
            // If queue is empty, or system is not initialized, or stopping, return false
            // Если очередь пуста, или система не инициализирована, или останавливается, возвращаем false
            return false;
        }

        // Вилучення повідомлення з черги
        // Dequeue message from queue
        // Извлечение сообщения из очереди
        message = messageQueue.top();
        messageQueue.pop();

        return true;
    }

    bool PriorityMessageQueue::peek(PriorityMessage& message) const {
        // Перегляд першого повідомлення без вилучення
        // Peek at first message without dequeuing
        // Просмотр первого сообщения без извлечения
        
        if (!initialized) {
            return false;
        }
        
        std::lock_guard<std::mutex> lock(queueMutex);
        
        // Перевірка, чи черга не порожня
        // Check if queue is not empty
        // Проверка, не пуста ли очередь
        if (messageQueue.empty()) {
            return false;
        }
        
        // Перегляд першого повідомлення
        // Peek at first message
        // Просмотр первого сообщения
        message = messageQueue.top();
        return true;
    }

    size_t PriorityMessageQueue::size() const {
        // Отримання кількості повідомлень у черзі
        // Get number of messages in queue
        // Получение количества сообщений в очереди
        
        std::lock_guard<std::mutex> lock(queueMutex);
        return messageQueue.size();
    }

    bool PriorityMessageQueue::isEmpty() const {
        // Перевірка, чи черга порожня
        // Check if queue is empty
        // Проверка, пуста ли очередь
        
        std::lock_guard<std::mutex> lock(queueMutex);
        return messageQueue.empty();
    }

    void PriorityMessageQueue::clear() {
        // Очищення черги
        // Clear queue
        // Очистка очереди
        
        std::lock_guard<std::mutex> lock(queueMutex);
        while (!messageQueue.empty()) {
            messageQueue.pop();
        }
        
        // Сповіщення очікуючих потоків
        // Notify waiting threads
        // Уведомление ожидающих потоков
        queueCondition.notify_all();
    }

    void PriorityMessageQueue::setMaxSize(size_t maxSize) {
        // Встановлення максимального розміру черги
        // Set maximum queue size
        // Установка максимального размера очереди
        
        std::lock_guard<std::mutex> lock(queueMutex);
        this->maxSize = maxSize;
    }

    size_t PriorityMessageQueue::getMaxSize() const {
        // Отримання максимального розміру черги
        // Get maximum queue size
        // Получение максимального размера очереди
        
        std::lock_guard<std::mutex> lock(queueMutex);
        return maxSize;
    }

    bool PriorityMessageQueue::isFull() const {
        // Перевірка, чи черга досягла максимального розміру
        // Check if queue has reached maximum size
        // Проверка, достигла ли очередь максимального размера
        
        std::lock_guard<std::mutex> lock(queueMutex);
        return messageQueue.size() >= maxSize;
    }

    PriorityMessageQueue::QueueStatistics PriorityMessageQueue::getStatistics() const {
        // Отримання статистики черги
        // Get queue statistics
        // Получение статистики очереди
        
        std::lock_guard<std::mutex> lock(statisticsMutex);
        return stats;
    }

    void PriorityMessageQueue::updateStatistics(const PriorityMessage& message, bool dropped) {
        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        
        std::lock_guard<std::mutex> lock(statisticsMutex);
        
        stats.totalMessages++;
        if (dropped) {
            stats.droppedMessages++;
        }
        
        // Оновлення статистики за пріоритетом
        // Update priority statistics
        // Обновление статистики по приоритету
        updatePriorityStatistics(message);
        
        // Оновлення середнього часу очікування
        // Update average wait time
        // Обновление среднего времени ожидания
        long long currentTime = getCurrentTimeMillis();
        long long waitTime = currentTime - message.timestamp;
        stats.averageWaitTime = (stats.averageWaitTime * (stats.totalMessages - 1) + waitTime) / stats.totalMessages;
    }

    int PriorityMessageQueue::generateMessageId() {
        // Генерація ID повідомлення
        // Generate message ID
        // Генерация ID сообщения
        
        return messageIdCounter++;
    }

    long long PriorityMessageQueue::getCurrentTimeMillis() const {
        // Отримання поточного часу в мілісекундах
        // Get current time in milliseconds
        // Получение текущего времени в миллисекундах
        
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return millis;
    }

    void PriorityMessageQueue::updatePriorityStatistics(const PriorityMessage& message) {
        // Оновлення статистики за пріоритетом
        // Update priority statistics
        // Обновление статистики по приоритету
        
        switch (message.priority) {
            case MessagePriority::LOW:
                stats.lowPriorityMessages++;
                break;
            case MessagePriority::NORMAL:
                stats.normalPriorityMessages++;
                break;
            case MessagePriority::HIGH:
                stats.highPriorityMessages++;
                break;
            case MessagePriority::CRITICAL:
                stats.criticalPriorityMessages++;
                break;
        }
    }

    void NeuroSync::Synapse::Priority::PriorityMessageQueue::setStopping(bool stopping) {
        // Встановлення флагу зупинки
        // Set stopping flag
        // Установка флага остановки

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            this->stopping = stopping;
        } // блокування звільняється тут / lock released here / блокировка освобождается здесь

        // Сповіщення очікуючих потоків
        // Notify waiting threads
        // Уведомление ожидающих потоков
        queueCondition.notify_all();
    }

} // namespace Priority
} // namespace Synapse
} // namespace NeuroSync