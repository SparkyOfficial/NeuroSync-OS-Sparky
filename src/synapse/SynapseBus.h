#ifndef SYNAPSE_BUS_H
#define SYNAPSE_BUS_H

#include "priority/PriorityMessageQueue.h"
#include "utils/WeightedConnectionManager.h"
#include <memory>
#include <atomic>

// SynapseBus.h
// Шина синапсів для NeuroSync OS Sparky
// Synapse bus for NeuroSync OS Sparky
// Шина синапсів для NeuroSync OS Sparky

class SynapseBus {
public:
    SynapseBus();
    ~SynapseBus();
    
    // Ініціалізація шини синапсів
    // Initialize synapse bus
    // Ініціалізація шини синапсів
    bool initialize();
    
    // Надіслати повідомлення
    // Send a message
    // Надіслати повідомлення
    bool sendMessage(int senderId, int receiverId, const void* data, size_t dataSize, 
                    NeuroSync::Synapse::Priority::MessagePriority priority = NeuroSync::Synapse::Priority::MessagePriority::NORMAL,
                    int weight = 1);
    
    // Отримати повідомлення
    // Receive a message
    // Отримати повідомлення
    bool receiveMessage(int& senderId, int& receiverId, void*& data, size_t& dataSize, 
                       NeuroSync::Synapse::Priority::MessagePriority& priority, int& weight);
    
    // Створити зв'язок між нейронами
    // Create connection between neurons
    // Створити зв'язок між нейронами
    bool createConnection(int neuronA, int neuronB, double weight);
    
    // Видалити зв'язок між нейронами
    // Remove connection between neurons
    // Видалити зв'язок між нейронами
    bool removeConnection(int neuronA, int neuronB);
    
    // Оновити вагу зв'язку
    // Update connection weight
    // Оновити вагу зв'язку
    bool updateConnectionWeight(int neuronA, int neuronB, double weight);
    
    // Отримати вагу зв'язку
    // Get connection weight
    // Отримати вагу зв'язку
    double getConnectionWeight(int neuronA, int neuronB) const;
    
    // Активувати зв'язок
    // Activate connection
    // Активувати зв'язок
    bool activateConnection(int neuronA, int neuronB);
    
    // Деактивувати зв'язок
    // Deactivate connection
    // Деактивувати зв'язок
    bool deactivateConnection(int neuronA, int neuronB);
    
    // Отримати кількість з'єднань
    // Get connection count
    // Отримати кількість з'єднань
    size_t getConnectionCount() const;
    
    // Отримати кількість повідомлень у черзі
    // Get message queue size
    // Отримати кількість повідомлень у черзі
    size_t getMessageQueueSize() const;
    
    // Отримати статистику шини
    // Get bus statistics
    // Отримати статистику шини
    struct BusStatistics {
        NeuroSync::Synapse::Priority::PriorityMessageQueue::QueueStatistics messageStats;
        NeuroSync::Synapse::Utils::WeightedConnectionManager::ConnectionStatistics connectionStats;
    };
    
    BusStatistics getStatistics() const;
    
private:
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
};

#endif // SYNAPSE_BUS_H