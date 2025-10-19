#include "SynapseBus.h"
#include <iostream>
#include <chrono>

// SynapseBus.cpp
// Реалізація шини синапсів для NeuroSync OS Sparky
// Implementation of synapse bus for NeuroSync OS Sparky
// Реалізація шини синапсів для NeuroSync OS Sparky

namespace NeuroSync {
namespace Synapse {

SynapseBus::SynapseBus() : initialized(false), processing(false) {
    // Ініціалізація шини синапсів
    // Initialize synapse bus
    // Ініціалізація шини синапсів
    
    std::cout << "[SynapseBus] Constructor called" << std::endl;
    
    // Створення черги повідомлень
    // Create message queue
    // Создание очереди сообщений
    messageQueue = std::make_unique<NeuroSync::Synapse::Priority::PriorityMessageQueue>();
    
    // Створення менеджера з'єднань
    // Create connection manager
    // Создание менеджера соединений
    connectionManager = std::make_unique<NeuroSync::Synapse::Utils::WeightedConnectionManager>();
    
    std::cout << "[SynapseBus] Constructor completed" << std::endl;
}

SynapseBus::~SynapseBus() {
    // Очищення ресурсів шини синапсів
    // Clean up synapse bus resources
    // Очистка ресурсов шины синапсов
    std::cout << "[SynapseBus] Destructor called" << std::endl;
    stop();
    std::cout << "[SynapseBus] Destructor completed" << std::endl;
}

bool SynapseBus::initialize() {
    // Ініціалізація шини синапсів
    // Initialize synapse bus
    // Ініціалізація шини синапсів
    
    std::cout << "[SynapseBus] Initializing..." << std::endl;
    
    if (initialized) {
        std::cout << "[SynapseBus] Already initialized" << std::endl;
        return true; // Вже ініціалізовано / Already initialized / Уже инициализировано
    }
    
    // Ініціалізація компонентів
    // Initialize components
    // Инициализация компонентов
    std::cout << "[SynapseBus] Initializing message queue" << std::endl;
    if (!messageQueue->initialize()) {
        std::cout << "[SynapseBus] Failed to initialize message queue" << std::endl;
        return false;
    }
    
    std::cout << "[SynapseBus] Initializing connection manager" << std::endl;
    if (!connectionManager->initialize()) {
        std::cout << "[SynapseBus] Failed to initialize connection manager" << std::endl;
        return false;
    }
    
    initialized = true;
    std::cout << "[SynapseBus] Initialization completed successfully" << std::endl;
    return true;
}

void SynapseBus::start() {
    // Запуск обробки повідомлень
    // Start message processing
    // Запуск обробки повідомлень
    
    std::cout << "[SynapseBus] Starting message processing..." << std::endl;
    
    if (!initialized || processing) {
        std::cout << "[SynapseBus] Not starting - initialized=" << initialized 
                  << ", processing=" << processing << std::endl;
        return;
    }
    
    processing = true;
    std::cout << "[SynapseBus] Creating processing thread" << std::endl;
    processingThread = std::thread(&SynapseBus::messageProcessingLoop, this);
    std::cout << "[SynapseBus] Processing thread created" << std::endl;
}

void NeuroSync::Synapse::SynapseBus::stop() {
    // Зупинка обробки повідомлень
    // Stop message processing
    // Зупинка обробки повідомлень
    
    std::cout << "[SynapseBus] Stopping message processing..." << std::endl;
    
    if (processing) {
        std::cout << "[SynapseBus] Processing is active, stopping..." << std::endl;
        processing = false;
        
        // Send a dummy message to wake up the processing thread immediately
        // Only send if the queue is still initialized
        if (messageQueue && initialized) {
            std::cout << "[SynapseBus] Sending dummy message..." << std::endl;
            NeuroSync::Synapse::Priority::PriorityMessage dummyMessage;
            dummyMessage.messageId = 0;
            dummyMessage.senderId = -1;
            dummyMessage.receiverId = -1;
            dummyMessage.priority = NeuroSync::Synapse::Priority::MessagePriority::LOW;
            dummyMessage.weight = 0;
            dummyMessage.timestamp = 0;
            dummyMessage.deadline = 0;
            dummyMessage.dataSize = 0;
            messageQueue->enqueue(dummyMessage);
        }
        
        // Set stopping flag to wake up any waiting threads
        if (messageQueue) {
            std::cout << "[SynapseBus] Setting stopping flag..." << std::endl;
            messageQueue->setStopping(true);
        }
        
        std::cout << "[SynapseBus] Checking if processing thread is joinable..." << std::endl;
        if (processingThread.joinable()) {
            std::cout << "[SynapseBus] Joining processing thread..." << std::endl;
            processingThread.join();
            std::cout << "[SynapseBus] Processing thread joined." << std::endl;
        } else {
            std::cout << "[SynapseBus] Processing thread is not joinable." << std::endl;
        }
    } else {
        std::cout << "[SynapseBus] Processing is not active." << std::endl;
    }
    
    std::cout << "[SynapseBus] Message processing stopped." << std::endl;
}

bool NeuroSync::Synapse::SynapseBus::sendMessage(int senderId, int receiverId, const void* data, size_t dataSize, 
                           NeuroSync::Synapse::Priority::MessagePriority priority, int weight) {
    // Надіслати повідомлення через шину синапсів
    // Send message through synapse bus
    // Отправить сообщение через шину синапсов
    
    std::cout << "[SynapseBus] Sending message from " << senderId << " to " << receiverId << std::endl;
    
    if (!initialized) {
        std::cout << "[SynapseBus] Not initialized, cannot send message" << std::endl;
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
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();
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
    bool result = messageQueue->enqueue(message);
    std::cout << "[SynapseBus] Message enqueue result: " << result << std::endl;
    return result;
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
    // Отримання кількості повідомлень у черзі
    // Get message queue size
    // Получение количества сообщений в очереди
    
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

void NeuroSync::Synapse::SynapseBus::messageProcessingLoop() {
    // Цикл обробки повідомлень
    // Message processing loop
    // Цикл обработки сообщений
    
    std::cout << "[SynapseBus] Message processing loop started" << std::endl;
    
    while (processing && initialized) {
        std::cout << "[SynapseBus] Processing loop iteration - processing=" << processing 
                  << ", initialized=" << initialized << std::endl;
        
        // Додаткова перевірка прапора обробки
        // Additional processing flag check
        // Дополнительная проверка флага обработки
        if (!processing) {
            std::cout << "[SynapseBus] Processing flag is false, breaking loop" << std::endl;
            break;
        }
        
        // Отримання повідомлення
        // Receive message
        // Получение сообщения
        NeuroSync::Synapse::Priority::PriorityMessage message;
        std::cout << "[SynapseBus] Attempting to dequeue message" << std::endl;
        if (messageQueue && messageQueue->dequeue(message)) {
            std::cout << "[SynapseBus] Dequeued message, processing..." << std::endl;
            // Обробка повідомлення
            // Process message
            // Обработка сообщения
            processMessage(message);
        } else {
            std::cout << "[SynapseBus] Failed to dequeue message" << std::endl;
            // If dequeue returns false, check if we should continue
            // Якщо dequeue повертає false, перевірити, чи потрібно продовжувати
            // Если dequeue возвращает false, проверить, нужно ли продолжать
            if (!processing || !initialized) {
                std::cout << "[SynapseBus] Breaking loop - processing=" << processing 
                          << ", initialized=" << initialized << std::endl;
                break;
            }
        }
    }
    
    std::cout << "[SynapseBus] Message processing loop ended" << std::endl;
}

void NeuroSync::Synapse::SynapseBus::processMessage(const NeuroSync::Synapse::Priority::PriorityMessage& message) {
    // Обробити повідомлення
    // Process message
    // Обработать сообщение
    
    std::cout << "[SynapseBus] Processing message from neuron " << message.senderId 
              << " to neuron " << message.receiverId << std::endl;
    
    // Викликати callback, якщо він встановлений
    // Call callback if set
    // Вызвать callback, если он установлен
    if (messageCallback) {
        messageCallback(message);
    }
    
    // Тут можна додати логіку обробки повідомлення
    // Here you can add message processing logic
    // Здесь можно добавить логику обработки сообщения
    
    // Для тестів просто виводимо повідомлення
    // For tests just output the message
    // Для тестов просто выводим сообщение
    // std::cout << "Processing message from neuron " << message.senderId 
    //           << " to neuron " << message.receiverId << std::endl;
}

void SynapseBus::setMessageCallback(std::function<void(const NeuroSync::Synapse::Priority::PriorityMessage&)> callback) {
    // Встановити callback для обробки повідомлень
    // Set callback for message processing
    // Установить callback для обработки сообщений
    
    messageCallback = callback;
}

} // namespace Synapse
} // namespace NeuroSync