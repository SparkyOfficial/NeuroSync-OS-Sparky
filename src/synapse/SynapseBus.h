#ifndef SYNAPSE_BUS_H
#define SYNAPSE_BUS_H

#include "priority/PriorityMessageQueue.h"
#include "utils/WeightedConnectionManager.h"
#include <memory>
#include <atomic>
#include <thread>
#include <functional>

// SynapseBus.h
// Шина синапсів для NeuroSync OS Sparky
// Synapse bus for NeuroSync OS Sparky
// Шина синапсов для NeuroSync OS Sparky

namespace NeuroSync {
namespace Synapse {

    // Шина синапсів
    // Synapse bus
    // Шина синапсов
    class SynapseBus {
    public:
        SynapseBus();
        ~SynapseBus();
        
        // Ініціалізація шини синапсів
        // Initialize synapse bus
        // Инициализация шины синапсов
        bool initialize();
        
        // Запуск обробки повідомлень
        // Start message processing
        // Запуск обработки сообщений
        void start();
        
        // Зупинка обробки повідомлень
        // Stop message processing
        // Остановка обработки сообщений
        void stop();
        
        // Надіслати повідомлення
        // Send message
        // Отправить сообщение
        bool sendMessage(int senderId, int receiverId, const void* data, size_t dataSize, 
                        NeuroSync::Synapse::Priority::MessagePriority priority = NeuroSync::Synapse::Priority::MessagePriority::NORMAL,
                        int weight = 1);
        
        // Отримати повідомлення
        // Receive message
        // Получить сообщение
        bool receiveMessage(int& senderId, int& receiverId, void*& data, size_t& dataSize, 
                           NeuroSync::Synapse::Priority::MessagePriority& priority, int& weight);
        
        // Створити зв'язок між нейронами
        // Create connection between neurons
        // Создать связь между нейронами
        bool createConnection(int neuronA, int neuronB, double weight);
        
        // Видалити зв'язок між нейронами
        // Remove connection between neurons
        // Удалить связь между нейронами
        bool removeConnection(int neuronA, int neuronB);
        
        // Оновити вагу зв'язку
        // Update connection weight
        // Обновить вес связи
        bool updateConnectionWeight(int neuronA, int neuronB, double weight);
        
        // Отримати вагу зв'язку
        // Get connection weight
        // Получить вес связи
        double getConnectionWeight(int neuronA, int neuronB) const;
        
        // Активувати зв'язок
        // Activate connection
        // Активировать связь
        bool activateConnection(int neuronA, int neuronB);
        
        // Деактивувати зв'язок
        // Deactivate connection
        // Деактивировать связь
        bool deactivateConnection(int neuronA, int neuronB);
        
        // Отримати кількість з'єднань
        // Get connection count
        // Отримати кількість з'єднань
        size_t getConnectionCount() const;
        
        // Отримати кількість повідомлень у черзі
        // Get message queue size
        // Отримати кількість повідомлень у черзі
        size_t getMessageQueueSize() const;
        
        // Встановити callback для обробки повідомлень
        // Set callback for message processing
        // Установить callback для обработки сообщений
        void setMessageCallback(std::function<void(const NeuroSync::Synapse::Priority::PriorityMessage&)> callback);
        
        // Отримати статистику шини
        // Get bus statistics
        // Отримати статистику шини
        struct BusStatistics {
            NeuroSync::Synapse::Priority::PriorityMessageQueue::QueueStatistics messageStats;
            NeuroSync::Synapse::Utils::WeightedConnectionManager::ConnectionStatistics connectionStats;
        };
        
        BusStatistics getStatistics() const;
        
    private:
        // Цикл обробки повідомлень
        // Message processing loop
        // Цикл обробки повідомлень
        void messageProcessingLoop();
        
        // Обробити повідомлення
        // Process message
        // Обробити повідомлення
        void processMessage(const NeuroSync::Synapse::Priority::PriorityMessage& message);
        
        // Черга повідомлень з пріоритетом
        // Priority message queue
        // Очередь сообщений с приоритетом
        std::unique_ptr<NeuroSync::Synapse::Priority::PriorityMessageQueue> messageQueue;
        
        // Менеджер зважених з'єднань
        // Weighted connection manager
        // Менеджер взвешенных соединений
        std::unique_ptr<NeuroSync::Synapse::Utils::WeightedConnectionManager> connectionManager;
        
        // Флаг ініціалізації
        // Initialization flag
        // Флаг инициализации
        std::atomic<bool> initialized;
        
        // Флаг запуску обробки повідомлень
        // Message processing start flag
        // Флаг запуска обработки сообщений
        std::atomic<bool> processing;
        
        // Потік обробки повідомлень
        // Message processing thread
        // Поток обработки сообщений
        std::thread processingThread;
        
        // Callback для обробки отриманих повідомлень
        // Callback for processing received messages
        // Callback для обработки полученных сообщений
        std::function<void(const NeuroSync::Synapse::Priority::PriorityMessage&)> messageCallback;
    };

} // namespace Synapse
} // namespace NeuroSync

#endif // SYNAPSE_BUS_H