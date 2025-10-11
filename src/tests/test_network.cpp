#include "../network/NetworkCommunication.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <thread>
#include <chrono>

// Тести для мережевої комунікації
// Network communication tests
// Тесты для сетевой коммуникации

void testNetworkInitialization() {
    std::cout << "Testing NetworkCommunication initialization..." << std::endl;
    
    NeuroSync::NetworkCommunication networkComm;
    
    NeuroSync::NetworkConfig config;
    config.host = "localhost";
    config.port = 8080;
    
    assert(networkComm.initialize(config));
    
    assert(networkComm.getStatus() == NeuroSync::NetworkStatus::CONNECTING);
    assert(!networkComm.getNodeId().empty());
    
    std::cout << "NetworkCommunication initialization test passed!" << std::endl;
}

void testNodeConnection() {
    std::cout << "Testing node connection..." << std::endl;
    
    NeuroSync::NetworkCommunication networkComm;
    
    NeuroSync::NetworkConfig config;
    config.host = "localhost";
    config.port = 8080;
    networkComm.initialize(config);
    
    // Підключення до вузлів
    // Connecting to nodes
    // Подключение к узлам
    assert(networkComm.connect("192.168.1.10", 8080));
    assert(networkComm.connect("192.168.1.11", 8080));
    
    assert(networkComm.getConnectedNodeCount() == 2);
    assert(networkComm.isNodeConnected("192.168.1.10:8080"));
    assert(networkComm.isNodeConnected("192.168.1.11:8080"));
    
    // Від'єднання від вузла
    // Disconnecting from node
    // Отключение от узла
    networkComm.disconnect("192.168.1.10:8080");
    assert(networkComm.getConnectedNodeCount() == 1);
    assert(!networkComm.isNodeConnected("192.168.1.10:8080"));
    
    // Від'єднання від усіх вузлів
    // Disconnecting from all nodes
    // Отключение от всех узлов
    networkComm.disconnectAll();
    assert(networkComm.getConnectedNodeCount() == 0);
    assert(networkComm.getStatus() == NeuroSync::NetworkStatus::DISCONNECTED);
    
    std::cout << "Node connection test passed!" << std::endl;
}

void testMessageSending() {
    std::cout << "Testing message sending..." << std::endl;
    
    NeuroSync::NetworkCommunication networkComm;
    
    NeuroSync::NetworkConfig config;
    config.host = "localhost";
    config.port = 8080;
    networkComm.initialize(config);
    
    // Підключення до вузла
    // Connecting to node
    // Подключение к узлу
    networkComm.connect("192.168.1.10", 8080);
    
    // Створення повідомлення
    // Creating message
    // Создание сообщения
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04};
    NeuroSync::NetworkMessage message(
        NeuroSync::MessageType::NEURON_DATA,
        networkComm.getNodeId(),
        "192.168.1.10:8080",
        data
    );
    
    // Надсилання повідомлення
    // Sending message
    // Отправка сообщения
    assert(networkComm.sendMessage(message));
    
    // Перевірка статистики
    // Checking statistics
    // Проверка статистики
    assert(networkComm.getOutgoingMessageCount() == 1);
    
    std::cout << "Message sending test passed!" << std::endl;
}

void testMessageReceiving() {
    std::cout << "Testing message receiving..." << std::endl;
    
    NeuroSync::NetworkCommunication networkComm;
    
    NeuroSync::NetworkConfig config;
    config.host = "localhost";
    config.port = 8080;
    networkComm.initialize(config);
    
    // Підключення до вузла
    // Connecting to node
    // Подключение к узлу
    networkComm.connect("192.168.1.10", 8080);
    
    // Перевірка початкової статистики
    // Checking initial statistics
    // Проверка начальной статистики
    assert(networkComm.getIncomingMessageCount() == 0);
    assert(networkComm.getOutgoingMessageCount() == 0);
    
    std::cout << "Message receiving test passed!" << std::endl;
}

void testServerOperations() {
    std::cout << "Testing server operations..." << std::endl;
    
    NeuroSync::NetworkCommunication networkComm;
    
    NeuroSync::NetworkConfig config;
    config.host = "localhost";
    config.port = 8080;
    networkComm.initialize(config);
    
    // Запуск сервера
    // Starting server
    // Запуск сервера
    assert(networkComm.startServer());
    
    // Очікування трохи часу для імітації роботи сервера
    // Waiting a bit to simulate server operation
    // Ожидание немного времени для имитации работы сервера
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Зупинка сервера
    // Stopping server
    // Остановка сервера
    networkComm.stopServer();
    
    std::cout << "Server operations test passed!" << std::endl;
}

void testMessageSerialization() {
    std::cout << "Testing message serialization..." << std::endl;
    
    NeuroSync::NetworkCommunication networkComm;
    
    // Створення повідомлення
    // Creating message
    // Создание сообщения
    std::vector<uint8_t> data = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    NeuroSync::NetworkMessage originalMsg(
        NeuroSync::MessageType::SIGNAL_DATA,
        "source_node",
        "dest_node",
        data
    );
    originalMsg.sequenceNumber = 42;
    
    // Перевірка, що повідомлення створено правильно
    // Checking that message is created correctly
    // Проверка, что сообщение создано правильно
    assert(originalMsg.type == NeuroSync::MessageType::SIGNAL_DATA);
    assert(originalMsg.sourceId == "source_node");
    assert(originalMsg.destinationId == "dest_node");
    assert(originalMsg.data.size() == 5);
    assert(originalMsg.sequenceNumber == 42);
    
    std::cout << "Message serialization test passed!" << std::endl;
}

void testStatistics() {
    std::cout << "Testing statistics..." << std::endl;
    
    NeuroSync::NetworkCommunication networkComm;
    
    NeuroSync::NetworkConfig config;
    config.host = "localhost";
    config.port = 8080;
    networkComm.initialize(config);
    
    // Перевірка початкової статистики
    // Checking initial statistics
    // Проверка начальной статистики
    assert(networkComm.getIncomingMessageCount() == 0);
    assert(networkComm.getOutgoingMessageCount() == 0);
    
    // Очищення статистики
    // Clearing statistics
    // Очистка статистики
    networkComm.clearStatistics();
    
    assert(networkComm.getIncomingMessageCount() == 0);
    assert(networkComm.getOutgoingMessageCount() == 0);
    
    std::cout << "Statistics test passed!" << std::endl;
}

int main() {
    std::cout << "=== Network Communication Tests ===" << std::endl;
    
    try {
        testNetworkInitialization();
        testNodeConnection();
        testMessageSending();
        testMessageReceiving();
        testServerOperations();
        testMessageSerialization();
        testStatistics();
        
        std::cout << "\nAll Network Communication tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}