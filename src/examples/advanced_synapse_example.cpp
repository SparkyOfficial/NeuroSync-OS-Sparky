#include "../NeuroSync.h"
#include "../synapse/SynapseBus.h"
#include "../synapse/priority/PriorityMessageQueue.h"
#include "../synapse/utils/WeightedConnectionManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

// advanced_synapse_example.cpp
// Пример использования расширенной шины синапсів NeuroSync OS Sparky
// Example of using advanced synapse bus in NeuroSync OS Sparky
// Приклад використання розширеної шини синапсів NeuroSync OS Sparky

using namespace NeuroSync::Synapse;
using namespace NeuroSync::Synapse::Priority;
using namespace NeuroSync::Synapse::Utils;

// Функції для демонстрації
// Functions for demonstration
// Функции для демонстрации

void demonstratePriorityQueue() {
    std::cout << "\n=== Priority Message Queue Demonstration ===" << std::endl;
    std::cout << "=== Демонстрація черги повідомлень з пріоритетом ===" << std::endl;
    std::cout << "=== Демонстрация очереди сообщений с приоритетом ===" << std::endl;
    
    // Створення черги повідомлень
    // Creating message queue
    // Создание очереди сообщений
    PriorityMessageQueue queue;
    queue.initialize();
    
    // Створення повідомлень різного пріоритету
    // Creating messages with different priorities
    // Создание сообщений с разными приоритетами
    PriorityMessage criticalMsg;
    criticalMsg.messageId = 1;
    criticalMsg.senderId = 100;
    criticalMsg.receiverId = 200;
    criticalMsg.priority = MessagePriority::CRITICAL;
    criticalMsg.weight = 10;
    criticalMsg.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    criticalMsg.deadline = criticalMsg.timestamp + 5000;
    criticalMsg.data = {'C', 'R', 'I', 'T', 'I', 'C', 'A', 'L'};
    criticalMsg.dataSize = 8;
    
    PriorityMessage highMsg;
    highMsg.messageId = 2;
    highMsg.senderId = 101;
    highMsg.receiverId = 201;
    highMsg.priority = MessagePriority::HIGH;
    highMsg.weight = 8;
    highMsg.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    highMsg.deadline = highMsg.timestamp + 10000;
    highMsg.data = {'H', 'I', 'G', 'H'};
    highMsg.dataSize = 4;
    
    PriorityMessage normalMsg;
    normalMsg.messageId = 3;
    normalMsg.senderId = 102;
    normalMsg.receiverId = 202;
    normalMsg.priority = MessagePriority::NORMAL;
    normalMsg.weight = 5;
    normalMsg.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    normalMsg.deadline = normalMsg.timestamp + 15000;
    normalMsg.data = {'N', 'O', 'R', 'M', 'A', 'L'};
    normalMsg.dataSize = 6;
    
    PriorityMessage lowMsg;
    lowMsg.messageId = 4;
    lowMsg.senderId = 103;
    lowMsg.receiverId = 203;
    lowMsg.priority = MessagePriority::LOW;
    lowMsg.weight = 2;
    lowMsg.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    lowMsg.deadline = lowMsg.timestamp + 20000;
    lowMsg.data = {'L', 'O', 'W'};
    lowMsg.dataSize = 3;
    
    // Додавання повідомлень до черги
    // Adding messages to queue
    // Добавление сообщений в очередь
    queue.enqueue(criticalMsg);
    queue.enqueue(highMsg);
    queue.enqueue(normalMsg);
    queue.enqueue(lowMsg);
    
    std::cout << "Added 4 messages to queue. Queue size: " << queue.size() << std::endl;
    std::cout << "Додано 4 повідомлення до черги. Розмір черги: " << queue.size() << std::endl;
    std::cout << "Добавлено 4 сообщения в очередь. Размер очереди: " << queue.size() << std::endl;
    
    // Вилучення повідомлень з черги (вони повинні бути в порядку пріоритету)
    // Dequeueing messages from queue (they should be in priority order)
    // Извлечение сообщений из очереди (они должны быть в порядке приоритета)
    PriorityMessage receivedMsg;
    while (!queue.isEmpty()) {
        if (queue.dequeue(receivedMsg)) {
            std::string priorityStr;
            switch (receivedMsg.priority) {
                case MessagePriority::CRITICAL:
                    priorityStr = "CRITICAL";
                    break;
                case MessagePriority::HIGH:
                    priorityStr = "HIGH";
                    break;
                case MessagePriority::NORMAL:
                    priorityStr = "NORMAL";
                    break;
                case MessagePriority::LOW:
                    priorityStr = "LOW";
                    break;
            }
            
            std::cout << "Received message with priority: " << priorityStr 
                      << ", Sender: " << receivedMsg.senderId 
                      << ", Receiver: " << receivedMsg.receiverId << std::endl;
        }
    }
    
    // Отримання статистики
    // Get statistics
    // Получение статистики
    auto stats = queue.getStatistics();
    std::cout << "Queue Statistics:" << std::endl;
    std::cout << "Статистика черги:" << std::endl;
    std::cout << "Статистика очереди:" << std::endl;
    std::cout << "  Total Messages: " << stats.totalMessages << std::endl;
    std::cout << "  Загальна кількість повідомлень: " << stats.totalMessages << std::endl;
    std::cout << "  Общее количество сообщений: " << stats.totalMessages << std::endl;
    std::cout << "  Critical Priority: " << stats.criticalPriorityMessages << std::endl;
    std::cout << "  Критичний пріоритет: " << stats.criticalPriorityMessages << std::endl;
    std::cout << "  Критический приоритет: " << stats.criticalPriorityMessages << std::endl;
    std::cout << "  High Priority: " << stats.highPriorityMessages << std::endl;
    std::cout << "  Високий пріоритет: " << stats.highPriorityMessages << std::endl;
    std::cout << "  Высокий приоритет: " << stats.highPriorityMessages << std::endl;
}

void demonstrateWeightedConnections() {
    std::cout << "\n=== Weighted Connection Manager Demonstration ===" << std::endl;
    std::cout << "=== Демонстрація менеджера зважених з'єднань ===" << std::endl;
    std::cout << "=== Демонстрация менеджера взвешенных соединений ===" << std::endl;
    
    // Створення менеджера зважених з'єднань
    // Creating weighted connection manager
    // Создание менеджера взвешенных соединений
    WeightedConnectionManager connManager;
    connManager.initialize();
    
    // Створення зважених з'єднань
    // Creating weighted connections
    // Создание взвешенных соединений
    connManager.createConnection(1, 2, 0.8);
    connManager.createConnection(1, 3, 0.6);
    connManager.createConnection(2, 4, 0.9);
    connManager.createConnection(3, 4, 0.7);
    connManager.createConnection(2, 5, 0.5);
    connManager.createConnection(3, 5, 0.4);
    
    std::cout << "Created 6 weighted connections." << std::endl;
    std::cout << "Створено 6 зважених з'єднань." << std::endl;
    std::cout << "Создано 6 взвешенных соединений." << std::endl;
    std::cout << "Total connections: " << connManager.getConnectionCount() << std::endl;
    std::cout << "Загальна кількість з'єднань: " << connManager.getConnectionCount() << std::endl;
    std::cout << "Общее количество соединений: " << connManager.getConnectionCount() << std::endl;
    
    // Отримання з'єднань для нейрона
    // Getting connections for neuron
    // Получение соединений для нейрона
    auto connectionsForNeuron2 = connManager.getConnectionsForNeuron(2);
    std::cout << "Neuron 2 has " << connectionsForNeuron2.size() << " connections:" << std::endl;
    std::cout << "Нейрон 2 має " << connectionsForNeuron2.size() << " з'єднань:" << std::endl;
    std::cout << "Нейрон 2 имеет " << connectionsForNeuron2.size() << " соединений:" << std::endl;
    
    for (const auto& conn : connectionsForNeuron2) {
        std::cout << "  Connection from " << conn.sourceNeuronId 
                  << " to " << conn.targetNeuronId 
                  << " with weight " << conn.weight << std::endl;
    }
    
    // Отримання вхідних з'єднань
    // Getting incoming connections
    // Получение входящих соединений
    auto incomingToNeuron4 = connManager.getIncomingConnections(4);
    std::cout << "Neuron 4 has " << incomingToNeuron4.size() << " incoming connections:" << std::endl;
    std::cout << "Нейрон 4 має " << incomingToNeuron4.size() << " вхідних з'єднань:" << std::endl;
    std::cout << "Нейрон 4 имеет " << incomingToNeuron4.size() << " входящих соединений:" << std::endl;
    
    for (const auto& conn : incomingToNeuron4) {
        std::cout << "  Connection from " << conn.sourceNeuronId 
                  << " to " << conn.targetNeuronId 
                  << " with weight " << conn.weight << std::endl;
    }
    
    // Отримання з'єднань, відсортованих за вагою
    // Getting connections sorted by weight
    // Получение соединений, отсортированных по весу
    auto sortedByWeight = connManager.getConnectionsSortedByWeight(true);
    std::cout << "Connections sorted by weight (descending):" << std::endl;
    std::cout << "З'єднання, відсортовані за вагою (за спаданням):" << std::endl;
    std::cout << "Соединения, отсортированные по весу (по убыванию):" << std::endl;
    
    for (const auto& conn : sortedByWeight) {
        std::cout << "  Connection from " << conn.sourceNeuronId 
                  << " to " << conn.targetNeuronId 
                  << " with weight " << conn.weight << std::endl;
    }
    
    // Отримання статистики
    // Get statistics
    // Получение статистики
    auto connStats = connManager.getStatistics();
    std::cout << "Connection Statistics:" << std::endl;
    std::cout << "Статистика з'єднань:" << std::endl;
    std::cout << "Статистика соединений:" << std::endl;
    std::cout << "  Total Connections: " << connStats.totalConnections << std::endl;
    std::cout << "  Загальна кількість з'єднань: " << connStats.totalConnections << std::endl;
    std::cout << "  Общее количество соединений: " << connStats.totalConnections << std::endl;
    std::cout << "  Average Weight: " << connStats.averageWeight << std::endl;
    std::cout << "  Середня вага: " << connStats.averageWeight << std::endl;
    std::cout << "  Средний вес: " << connStats.averageWeight << std::endl;
}

void demonstrateSynapseBus() {
    std::cout << "\n=== SynapseBus Demonstration ===" << std::endl;
    std::cout << "=== Демонстрація шини синапсів ===" << std::endl;
    std::cout << "=== Демонстрация шины синапсов ===" << std::endl;
    
    // Створення шини синапсів
    // Creating synapse bus
    // Создание шины синапсов
    SynapseBus synapseBus;
    if (!synapseBus.initialize()) {
        std::cerr << "Failed to initialize SynapseBus!" << std::endl;
        std::cerr << "Не вдалося ініціалізувати SynapseBus!" << std::endl;
        std::cerr << "Не удалось инициализировать SynapseBus!" << std::endl;
        return;
    }
    
    std::cout << "SynapseBus initialized successfully." << std::endl;
    std::cout << "SynapseBus успішно ініціалізовано." << std::endl;
    std::cout << "SynapseBus успешно инициализирован." << std::endl;
    
    // Створення з'єднань
    // Creating connections
    // Создание соединений
    synapseBus.createConnection(100, 200, 0.9);
    synapseBus.createConnection(100, 300, 0.7);
    synapseBus.createConnection(200, 400, 0.8);
    synapseBus.createConnection(300, 400, 0.6);
    
    std::cout << "Created 4 connections. Total connections: " << synapseBus.getConnectionCount() << std::endl;
    std::cout << "Створено 4 з'єднання. Загальна кількість з'єднань: " << synapseBus.getConnectionCount() << std::endl;
    std::cout << "Создано 4 соединения. Общее количество соединений: " << synapseBus.getConnectionCount() << std::endl;
    
    // Надсилання повідомлень різного пріоритету
    // Sending messages with different priorities
    // Отправка сообщений с разными приоритетами
    const char* criticalData = "CRITICAL_DATA";
    const char* highData = "HIGH_PRIORITY_DATA";
    const char* normalData = "NORMAL_DATA";
    const char* lowData = "LOW_PRIORITY_DATA";
    
    synapseBus.sendMessage(100, 200, criticalData, strlen(criticalData), MessagePriority::CRITICAL, 10);
    synapseBus.sendMessage(100, 300, highData, strlen(highData), MessagePriority::HIGH, 8);
    synapseBus.sendMessage(200, 400, normalData, strlen(normalData), MessagePriority::NORMAL, 5);
    synapseBus.sendMessage(300, 400, lowData, strlen(lowData), MessagePriority::LOW, 2);
    
    std::cout << "Sent 4 messages. Queue size: " << synapseBus.getMessageQueueSize() << std::endl;
    std::cout << "Надіслано 4 повідомлення. Розмір черги: " << synapseBus.getMessageQueueSize() << std::endl;
    std::cout << "Отправлено 4 сообщения. Размер очереди: " << synapseBus.getMessageQueueSize() << std::endl;
    
    // Отримання повідомлень
    // Receiving messages
    // Получение сообщений
    int senderId, receiverId, weight;
    void* receivedData;
    size_t dataSize;
    MessagePriority priority;
    
    while (synapseBus.getMessageQueueSize() > 0) {
        if (synapseBus.receiveMessage(senderId, receiverId, receivedData, dataSize, priority, weight)) {
            std::string priorityStr;
            switch (priority) {
                case MessagePriority::CRITICAL:
                    priorityStr = "CRITICAL";
                    break;
                case MessagePriority::HIGH:
                    priorityStr = "HIGH";
                    break;
                case MessagePriority::NORMAL:
                    priorityStr = "NORMAL";
                    break;
                case MessagePriority::LOW:
                    priorityStr = "LOW";
                    break;
            }
            
            std::cout << "Received message from " << senderId << " to " << receiverId 
                      << " with priority " << priorityStr 
                      << " and weight " << weight << std::endl;
            std::cout << "Отримано повідомлення від " << senderId << " до " << receiverId 
                      << " з пріоритетом " << priorityStr 
                      << " та вагою " << weight << std::endl;
            std::cout << "Получено сообщение от " << senderId << " к " << receiverId 
                      << " с приоритетом " << priorityStr 
                      << " и весом " << weight << std::endl;
            
            // Звільнення пам'яті
            // Free memory
            // Освобождение памяти
            delete[] static_cast<char*>(receivedData);
        }
    }
    
    // Отримання статистики
    // Get statistics
    // Получение статистики
    auto busStats = synapseBus.getStatistics();
    std::cout << "SynapseBus Statistics:" << std::endl;
    std::cout << "Статистика SynapseBus:" << std::endl;
    std::cout << "Статистика SynapseBus:" << std::endl;
    std::cout << "  Total Messages: " << busStats.messageStats.totalMessages << std::endl;
    std::cout << "  Загальна кількість повідомлень: " << busStats.messageStats.totalMessages << std::endl;
    std::cout << "  Общее количество сообщений: " << busStats.messageStats.totalMessages << std::endl;
    std::cout << "  Dropped Messages: " << busStats.messageStats.droppedMessages << std::endl;
    std::cout << "  Відкинуті повідомлення: " << busStats.messageStats.droppedMessages << std::endl;
    std::cout << "  Отброшенные сообщения: " << busStats.messageStats.droppedMessages << std::endl;
    std::cout << "  Total Connections: " << busStats.connectionStats.totalConnections << std::endl;
    std::cout << "  Загальна кількість з'єднань: " << busStats.connectionStats.totalConnections << std::endl;
    std::cout << "  Общее количество соединений: " << busStats.connectionStats.totalConnections << std::endl;
}

int main() {
    std::cout << "=== NeuroSync OS Sparky Advanced Synapse Example ===" << std::endl;
    std::cout << "=== Приклад розширеної шини синапсів NeuroSync OS Sparky ===" << std::endl;
    std::cout << "=== Пример расширенной шины синапсов NeuroSync OS Sparky ===" << std::endl;
    
    // Демонстрація черги повідомлень з пріоритетом
    // Demonstrate priority message queue
    // Демонстрация очереди сообщений с приоритетом
    demonstratePriorityQueue();
    
    // Демонстрація менеджера зважених з'єднань
    // Demonstrate weighted connection manager
    // Демонстрация менеджера взвешенных соединений
    demonstrateWeightedConnections();
    
    // Демонстрація шини синапсів
    // Demonstrate synapse bus
    // Демонстрация шины синапсов
    demonstrateSynapseBus();
    
    std::cout << "\nAdvanced Synapse Example completed!" << std::endl;
    std::cout << "Приклад розширеної шини синапсів завершено!" << std::endl;
    std::cout << "Пример расширенной шины синапсов завершен!" << std::endl;
    
    return 0;
}