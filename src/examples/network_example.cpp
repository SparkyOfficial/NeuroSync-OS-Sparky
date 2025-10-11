#include "../network/NetworkCommunication.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Приклад використання мережевої комунікації
// Network communication usage example
// Пример использования сетевой коммуникации

int main() {
    std::cout << "=== Network Communication Example ===" << std::endl;
    
    // Ініціалізація мережевої комунікації
    // Initializing network communication
    // Инициализация сетевой коммуникации
    NeuroSync::gNetworkComm = std::make_unique<NeuroSync::NetworkCommunication>();
    
    NeuroSync::NetworkConfig config;
    config.host = "localhost";
    config.port = 8080;
    config.maxConnections = 10;
    config.bufferSize = 4096;
    config.timeoutMs = 5000;
    
    if (!NeuroSync::gNetworkComm->initialize(config)) {
        std::cerr << "Failed to initialize network communication" << std::endl;
        return 1;
    }
    
    std::cout << "Network communication initialized with node ID: " 
              << NeuroSync::gNetworkComm->getNodeId() << std::endl;
    
    // Запуск сервера
    // Starting server
    // Запуск сервера
    if (!NeuroSync::gNetworkComm->startServer()) {
        std::cerr << "Failed to start server" << std::endl;
        return 1;
    }
    
    // Імітація підключення до віддалених вузлів
    // Simulating connection to remote nodes
    // Имитация подключения к удаленным узлам
    std::cout << "\nConnecting to remote nodes..." << std::endl;
    NeuroSync::gNetworkComm->connect("192.168.1.10", 8080);
    NeuroSync::gNetworkComm->connect("192.168.1.11", 8080);
    NeuroSync::gNetworkComm->connect("192.168.1.12", 8080);
    
    std::cout << "Connected nodes: " << NeuroSync::gNetworkComm->getConnectedNodeCount() << std::endl;
    
    // Надсилання повідомлень нейронних даних
    // Sending neuron data messages
    // Отправка сообщений нейронных данных
    std::cout << "\nSending neuron data messages..." << std::endl;
    
    std::vector<uint8_t> neuronData1 = {0x01, 0x02, 0x03, 0x04, 0x05};
    NeuroSync::NetworkMessage neuronMsg1(
        NeuroSync::MessageType::NEURON_DATA,
        NeuroSync::gNetworkComm->getNodeId(),
        "192.168.1.10:8080",
        neuronData1
    );
    
    if (NeuroSync::gNetworkComm->sendMessage(neuronMsg1)) {
        std::cout << "Sent neuron data message to 192.168.1.10:8080" << std::endl;
    }
    
    std::vector<uint8_t> neuronData2 = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
    NeuroSync::NetworkMessage neuronMsg2(
        NeuroSync::MessageType::NEURON_DATA,
        NeuroSync::gNetworkComm->getNodeId(),
        "192.168.1.11:8080",
        neuronData2
    );
    
    if (NeuroSync::gNetworkComm->sendMessage(neuronMsg2)) {
        std::cout << "Sent neuron data message to 192.168.1.11:8080" << std::endl;
    }
    
    // Надсилання повідомлень даних синапса
    // Sending synapse data messages
    // Отправка сообщений данных синапса
    std::cout << "\nSending synapse data messages..." << std::endl;
    
    std::vector<uint8_t> synapseData = {0xA0, 0xB0, 0xC0, 0xD0};
    NeuroSync::NetworkMessage synapseMsg(
        NeuroSync::MessageType::SYNAPSE_DATA,
        NeuroSync::gNetworkComm->getNodeId(),
        "192.168.1.12:8080",
        synapseData
    );
    
    if (NeuroSync::gNetworkComm->sendMessage(synapseMsg)) {
        std::cout << "Sent synapse data message to 192.168.1.12:8080" << std::endl;
    }
    
    // Надсилання сигналів життя
    // Sending heartbeat signals
    // Отправка сигналов жизни
    std::cout << "\nSending heartbeat signals..." << std::endl;
    NeuroSync::gNetworkComm->sendHeartbeat();
    
    // Отримання статистики
    // Getting statistics
    // Получение статистики
    std::cout << "\nNetwork statistics:" << std::endl;
    std::cout << "  Connected nodes: " << NeuroSync::gNetworkComm->getConnectedNodeCount() << std::endl;
    std::cout << "  Incoming messages: " << NeuroSync::gNetworkComm->getIncomingMessageCount() << std::endl;
    std::cout << "  Outgoing messages: " << NeuroSync::gNetworkComm->getOutgoingMessageCount() << std::endl;
    std::cout << "  Node ID: " << NeuroSync::gNetworkComm->getNodeId() << std::endl;
    
    // Отримання списку підключених вузлів
    // Getting list of connected nodes
    // Получение списка подключенных узлов
    std::cout << "\nConnected nodes:" << std::endl;
    auto nodes = NeuroSync::gNetworkComm->getConnectedNodes();
    for (const auto& node : nodes) {
        std::cout << "  " << node << std::endl;
    }
    
    // Імітація отримання повідомлень
    // Simulating receiving messages
    // Имитация получения сообщений
    std::cout << "\nReceiving messages..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    NeuroSync::NetworkMessage receivedMsg;
    while (NeuroSync::gNetworkComm->receiveMessage(receivedMsg)) {
        std::cout << "Received message from " << receivedMsg.sourceId << std::endl;
        std::cout << "  Type: " << static_cast<int>(receivedMsg.type) << std::endl;
        std::cout << "  Data size: " << receivedMsg.data.size() << " bytes" << std::endl;
    }
    
    // Від'єднання від вузлів
    // Disconnecting from nodes
    // Отключение от узлов
    std::cout << "\nDisconnecting from nodes..." << std::endl;
    NeuroSync::gNetworkComm->disconnect("192.168.1.10:8080");
    NeuroSync::gNetworkComm->disconnect("192.168.1.11:8080");
    
    std::cout << "Connected nodes after disconnection: " 
              << NeuroSync::gNetworkComm->getConnectedNodeCount() << std::endl;
    
    // Зупинка сервера
    // Stopping server
    // Остановка сервера
    std::cout << "\nStopping server..." << std::endl;
    NeuroSync::gNetworkComm->stopServer();
    
    // Очищення статистики
    // Clearing statistics
    // Очистка статистики
    NeuroSync::gNetworkComm->clearStatistics();
    
    std::cout << "\nNetwork communication example completed!" << std::endl;
    
    return 0;
}