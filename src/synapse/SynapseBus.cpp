#include "SynapseBus.h"
#include <cstring>
#include <iostream>
#include <chrono>

// SynapseBus.cpp
// Реалізація шини синапсів для NeuroSync OS Sparky
// Implementation of synapse bus for NeuroSync OS Sparky
// Реалізація шини синапсів для NeuroSync OS Sparky

SynapseBus::SynapseBus() : initialized(false) {
    // Ініціалізація шини синапсів
    // Initialize synapse bus
    // Ініціалізація шини синапсів
    
    // Створення черги повідомлень
    // Create message queue
    // Создание очереди сообщений
    messageQueue = std::make_unique<NeuroSync::Synapse::Priority::PriorityMessageQueue>();
    
    // Створення менеджера з'єднань
    // Create connection manager
    // Создание менеджера соединений
    connectionManager = std::make_unique<NeuroSync::Synapse::Utils::WeightedConnectionManager>();
}

SynapseBus::~SynapseBus() {
    // Очищення ресурсів шини синапсів
    // Clean up synapse bus resources
    // Очистка ресурсов шины синапсов
}

bool SynapseBus::initialize() {
    // Ініціалізація шини синапсів
    // Initialize synapse bus
    // Ініціалізація шини синапсів
    
    if (initialized) {
        return true; // Вже ініціалізовано / Already initialized / Уже инициализировано
    }
    
    // Ініціалізація компонентів
    // Initialize components
    // Инициализация компонентов
    if (!messageQueue->initialize()) {
        return false;
    }
    
    if (!connectionManager->initialize()) {
        return false;
    }
    
    initialized = true;
    return true;
}

bool SynapseBus::sendMessage(int senderId, int receiverId, const void* data, size_t dataSize, 
                           NeuroSync::Synapse::Priority::MessagePriority priority, int weight) {
    // Надіслати повідомлення через шину синапсів
    // Send message through synapse bus
    // Отправить сообщение через шину синапсов
    
    if (!initialized) {
        return false;
    }
    
    // Створення повідомлення
    // Create message
    // Создание сообщения
    NeuroSync::Synapse::Priority::PriorityMessage message;
    message.messageId = 0; // Буде встановлено в черзі / Will be set in queue / Будет установлено в очереди
    message.senderId = senderId;
    message.receiverId = receiverId;
    message.priority = priority;
    message.weight = weight;
    message.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    message.deadline = message.timestamp + 10000; // 10 секунд терміну / 10 seconds deadline / 10 секунд крайнего срока
    
    // Копіювання даних
    // Copy data
    // Копирование данных
    if (data && dataSize > 0) {
        message.data.resize(dataSize);
        std::memcpy(message.data.data(), data, dataSize);
        message.dataSize = dataSize;
    } else {
        message.dataSize = 0;
    }
    
    // Надсилання повідомлення
    // Send message
    // Отправка сообщения
    return messageQueue->enqueue(message);
}

bool SynapseBus::receiveMessage(int& senderId, int& receiverId, void*& data, size_t& dataSize, 
                               NeuroSync::Synapse::Priority::MessagePriority& priority, int& weight) {
    // Отримати повідомлення з шини синапсів
    // Receive message from synapse bus
    // Получить сообщение из шины синапсов
    
    if (!initialized) {
        return false;
    }
    
    // Отримання повідомлення
    // Receive message
    // Получение сообщения
    NeuroSync::Synapse::Priority::PriorityMessage message;
    if (!messageQueue->dequeue(message)) {
        return false;
    }
    
    // Заповнення вихідних параметрів
    // Fill output parameters
    // Заполнение выходных параметров
    senderId = message.senderId;
    receiverId = message.receiverId;
    priority = message.priority;
    weight = message.weight;
    dataSize = message.dataSize;
    
    // Копіювання даних
    // Copy data
    // Копирование данных
    if (message.dataSize > 0) {
        data = new char[message.dataSize];
        std::memcpy(data, message.data.data(), message.dataSize);
    } else {
        data = nullptr;
    }
    
    return true;
}

bool SynapseBus::createConnection(int neuronA, int neuronB, double weight) {
    // Створити зв'язок між двома нейронами
    // Create connection between two neurons
    // Создать связь между двумя нейронами
    
    if (!initialized) {
        return false;
    }
    
    return connectionManager->createConnection(neuronA, neuronB, weight);
}

bool SynapseBus::removeConnection(int neuronA, int neuronB) {
    // Видалити зв'язок між двома нейронами
    // Remove connection between two neurons
    // Удалить связь между двумя нейронами
    
    if (!initialized) {
        return false;
    }
    
    return connectionManager->removeConnection(neuronA, neuronB);
}

bool SynapseBus::updateConnectionWeight(int neuronA, int neuronB, double weight) {
    // Оновити вагу зв'язку
    // Update connection weight
    // Обновить вес связи
    
    if (!initialized) {
        return false;
    }
    
    return connectionManager->updateConnectionWeight(neuronA, neuronB, weight);
}

double SynapseBus::getConnectionWeight(int neuronA, int neuronB) const {
    // Отримати вагу зв'язку
    // Get connection weight
    // Получить вес связи
    
    if (!initialized) {
        return 0.0;
    }
    
    return connectionManager->getConnectionWeight(neuronA, neuronB);
}

bool SynapseBus::activateConnection(int neuronA, int neuronB) {
    // Активувати зв'язок
    // Activate connection
    // Активировать связь
    
    if (!initialized) {
        return false;
    }
    
    return connectionManager->activateConnection(neuronA, neuronB);
}

bool SynapseBus::deactivateConnection(int neuronA, int neuronB) {
    // Деактивувати зв'язок
    // Deactivate connection
    // Деактивировать связь
    
    if (!initialized) {
        return false;
    }
    
    return connectionManager->deactivateConnection(neuronA, neuronB);
}

size_t SynapseBus::getConnectionCount() const {
    // Отримати кількість з'єднань
    // Get connection count
    // Получить количество соединений
    
    if (!initialized) {
        return 0;
    }
    
    return connectionManager->getConnectionCount();
}

size_t SynapseBus::getMessageQueueSize() const {
    // Отримати кількість повідомлень у черзі
    // Get message queue size
    // Получить количество сообщений в очереди
    
    if (!initialized) {
        return 0;
    }
    
    return messageQueue->size();
}

SynapseBus::BusStatistics SynapseBus::getStatistics() const {
    // Отримати статистику шини
    // Get bus statistics
    // Получить статистику шины
    
    BusStatistics stats;
    
    if (initialized) {
        stats.messageStats = messageQueue->getStatistics();
        stats.connectionStats = connectionManager->getStatistics();
    }
    
    return stats;
}