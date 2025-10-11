#include "NetworkCommunication.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cstring>

// NetworkCommunication.cpp
// Реалізація мережевої комунікації для NeuroSync OS Sparky
// Network communication implementation for NeuroSync OS Sparky
// Реализация сетевой коммуникации для NeuroSync OS Sparky

namespace NeuroSync {

    // Конструктор
    // Constructor
    // Конструктор
    NetworkCommunication::NetworkCommunication() 
        : status(NetworkStatus::DISCONNECTED), 
          incomingMessageCount(0), 
          outgoingMessageCount(0),
          sequenceCounter(0),
          serverRunning(false) {
        // Генерація унікального ідентифікатора вузла
        // Generate unique node ID
        // Генерация уникального идентификатора узла
        nodeId = generateNodeId();
    }

    // Деструктор
    // Destructor
    // Деструктор
    NetworkCommunication::~NetworkCommunication() {
        stopServer();
        disconnectAll();
    }

    // Ініціалізація мережевої комунікації
    // Initialize network communication
    // Инициализация сетевой коммуникации
    bool NetworkCommunication::initialize(const NetworkConfig& config) {
        std::lock_guard<std::mutex> lock(networkMutex);
        
        this->config = config;
        
        // Валідація конфігурації
        // Validate configuration
        // Валидация конфигурации
        if (config.host.empty()) {
            std::cerr << "Invalid host in network configuration" << std::endl;
            return false;
        }
        
        if (config.port == 0) {
            std::cerr << "Invalid port in network configuration" << std::endl;
            return false;
        }
        
        status = NetworkStatus::CONNECTING;
        return true;
    }

    // Підключення до віддаленого вузла
    // Connect to remote node
    // Подключение к удаленному узлу
    bool NetworkCommunication::connect(const std::string& host, uint16_t port) {
        std::lock_guard<std::mutex> lock(networkMutex);
        
        // Імітація підключення (в реальній реалізації тут буде справжнє підключення)
        // Simulate connection (in real implementation there would be actual connection)
        // Имитация подключения (в реальной реализации здесь будет настоящее подключение)
        std::string nodeId = host + ":" + std::to_string(port);
        connectedNodes[nodeId] = true;
        
        std::cout << "Connected to node: " << nodeId << std::endl;
        status = NetworkStatus::CONNECTED;
        
        return true;
    }

    // Від'єднання від віддаленого вузла
    // Disconnect from remote node
    // Отключение от удаленного узла
    void NetworkCommunication::disconnect(const std::string& nodeId) {
        std::lock_guard<std::mutex> lock(networkMutex);
        
        auto it = connectedNodes.find(nodeId);
        if (it != connectedNodes.end()) {
            connectedNodes.erase(it);
            std::cout << "Disconnected from node: " << nodeId << std::endl;
            
            // Якщо більше немає підключених вузлів, змінюємо статус
            // If no more connected nodes, change status
            // Если больше нет подключенных узлов, изменяем статус
            if (connectedNodes.empty()) {
                status = NetworkStatus::DISCONNECTED;
            }
        }
    }

    // Від'єднання від усіх вузлів
    // Disconnect from all nodes
    // Отключение от всех узлов
    void NetworkCommunication::disconnectAll() {
        std::lock_guard<std::mutex> lock(networkMutex);
        
        connectedNodes.clear();
        status = NetworkStatus::DISCONNECTED;
        std::cout << "Disconnected from all nodes" << std::endl;
    }

    // Надсилання повідомлення
    // Send message
    // Отправка сообщения
    bool NetworkCommunication::sendMessage(const NetworkMessage& message) {
        // Валідація повідомлення
        // Validate message
        // Валидация сообщения
        if (!validateMessage(message)) {
            std::cerr << "Invalid message" << std::endl;
            return false;
        }
        
        // Додавання повідомлення до черги вихідних повідомлень
        // Add message to outgoing message queue
        // Добавление сообщения в очередь исходящих сообщений
        {
            std::lock_guard<std::mutex> lock(outgoingMutex);
            outgoingMessages.push(message);
            outgoingMessageCount++;
        }
        
        // Надсилання даних (в реальній реалізації тут буде справжнє надсилання)
        // Send data (in real implementation there would be actual sending)
        // Отправка данных (в реальной реализации здесь будет настоящее отправление)
        std::vector<uint8_t> serializedData = serializeMessage(message);
        bool result = sendRawData(message.destinationId, serializedData);
        
        if (result) {
            std::cout << "Sent message to " << message.destinationId << std::endl;
        } else {
            std::cerr << "Failed to send message to " << message.destinationId << std::endl;
        }
        
        return result;
    }

    // Отримання повідомлення
    // Receive message
    // Получение сообщения
    bool NetworkCommunication::receiveMessage(NetworkMessage& message) {
        std::lock_guard<std::mutex> lock(incomingMutex);
        
        if (incomingMessages.empty()) {
            return false;
        }
        
        message = incomingMessages.front();
        incomingMessages.pop();
        incomingMessageCount--;
        
        return true;
    }

    // Надсилання сигналу життя
    // Send heartbeat
    // Отправка сигнала жизни
    void NetworkCommunication::sendHeartbeat() {
        NetworkMessage heartbeatMsg(MessageType::HEARTBEAT, nodeId, "broadcast", {});
        sendMessage(heartbeatMsg);
        std::cout << "Heartbeat sent" << std::endl;
    }

    // Отримання статусу мережі
    // Get network status
    // Получение статуса сети
    NetworkStatus NetworkCommunication::getStatus() const {
        std::lock_guard<std::mutex> lock(networkMutex);
        return status;
    }

    // Отримання ідентифікатора вузла
    // Get node ID
    // Получение идентификатора узла
    std::string NetworkCommunication::getNodeId() const {
        std::lock_guard<std::mutex> lock(networkMutex);
        return nodeId;
    }

    // Встановлення ідентифікатора вузла
    // Set node ID
    // Установка идентификатора узла
    void NetworkCommunication::setNodeId(const std::string& nodeId) {
        std::lock_guard<std::mutex> lock(networkMutex);
        this->nodeId = nodeId;
    }

    // Отримання кількості підключених вузлів
    // Get connected node count
    // Получение количества подключенных узлов
    size_t NetworkCommunication::getConnectedNodeCount() const {
        std::lock_guard<std::mutex> lock(networkMutex);
        return connectedNodes.size();
    }

    // Перевірка, чи підключений вузол
    // Check if node is connected
    // Проверка, подключен ли узел
    bool NetworkCommunication::isNodeConnected(const std::string& nodeId) const {
        std::lock_guard<std::mutex> lock(networkMutex);
        auto it = connectedNodes.find(nodeId);
        return it != connectedNodes.end() && it->second;
    }

    // Отримання списку підключених вузлів
    // Get list of connected nodes
    // Получение списка подключенных узлов
    std::vector<std::string> NetworkCommunication::getConnectedNodes() const {
        std::lock_guard<std::mutex> lock(networkMutex);
        std::vector<std::string> nodes;
        for (const auto& pair : connectedNodes) {
            if (pair.second) {
                nodes.push_back(pair.first);
            }
        }
        return nodes;
    }

    // Запуск сервера
    // Start server
    // Запуск сервера
    bool NetworkCommunication::startServer() {
        std::lock_guard<std::mutex> lock(networkMutex);
        
        if (serverRunning.load()) {
            std::cerr << "Server is already running" << std::endl;
            return false;
        }
        
        serverRunning.store(true);
        serverThread = std::make_unique<std::thread>(&NetworkCommunication::serverLoop, this);
        
        std::cout << "Server started on " << config.host << ":" << config.port << std::endl;
        return true;
    }

    // Зупинка сервера
    // Stop server
    // Остановка сервера
    void NetworkCommunication::stopServer() {
        serverRunning.store(false);
        
        if (serverThread && serverThread->joinable()) {
            serverThread->join();
        }
        
        serverThread.reset();
        std::cout << "Server stopped" << std::endl;
    }

    // Отримання кількості вхідних повідомлень
    // Get incoming message count
    // Получение количества входящих сообщений
    size_t NetworkCommunication::getIncomingMessageCount() const {
        return incomingMessageCount.load();
    }

    // Отримання кількості вихідних повідомлень
    // Get outgoing message count
    // Получение количества исходящих сообщений
    size_t NetworkCommunication::getOutgoingMessageCount() const {
        return outgoingMessageCount.load();
    }

    // Очищення статистики
    // Clear statistics
    // Очистка статистики
    void NetworkCommunication::clearStatistics() {
        incomingMessageCount.store(0);
        outgoingMessageCount.store(0);
        sequenceCounter.store(0);
        
        std::lock_guard<std::mutex> lockIncoming(incomingMutex);
        std::lock_guard<std::mutex> lockOutgoing(outgoingMutex);
        
        while (!incomingMessages.empty()) {
            incomingMessages.pop();
        }
        
        while (!outgoingMessages.empty()) {
            outgoingMessages.pop();
        }
        
        std::cout << "Statistics cleared" << std::endl;
    }

    // Внутрішні методи
    // Internal methods
    // Внутренние методы
    
    // Надсилання необроблених даних
    // Send raw data
    // Отправка необработанных данных
    bool NetworkCommunication::sendRawData(const std::string& nodeId, const std::vector<uint8_t>& data) {
        // Імітація надсилання даних (в реальній реалізації тут буде справжнє надсилання)
        // Simulate sending data (in real implementation there would be actual sending)
        // Имитация отправки данных (в реальной реализации здесь будет настоящее отправление)
        
        // Імітуємо затримку мережі
        // Simulate network delay
        // Имитируем задержку сети
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
        // Імітуємо отримання відповіді
        // Simulate receiving response
        // Имитируем получение ответа
        std::vector<uint8_t> responseData = data;
        receiveRawData(nodeId, responseData);
        
        return true;
    }

    // Отримання необроблених даних
    // Receive raw data
    // Получение необработанных данных
    bool NetworkCommunication::receiveRawData(const std::string& nodeId, std::vector<uint8_t>& data) {
        // Імітація отримання даних (в реальній реалізації тут буде справжнє отримання)
        // Simulate receiving data (in real implementation there would be actual receiving)
        // Имитация получения данных (в реальной реализации здесь будет настоящее получение)
        
        // Імітуємо затримку мережі
        // Simulate network delay
        // Имитируем задержку сети
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        
        // Імітуємо обробку отриманих даних
        // Simulate processing received data
        // Имитируем обработку полученных данных
        NetworkMessage message = deserializeMessage(data);
        processIncomingMessage(message);
        
        return true;
    }

    // Серіалізація повідомлення
    // Serialize message
    // Сериализация сообщения
    std::vector<uint8_t> NetworkCommunication::serializeMessage(const NetworkMessage& message) const {
        std::vector<uint8_t> data;
        
        // Серіалізація типу повідомлення
        // Serialize message type
        // Сериализация типа сообщения
        data.push_back(static_cast<uint8_t>(message.type));
        
        // Серіалізація ідентифікаторів
        // Serialize identifiers
        // Сериализация идентификаторов
        uint32_t sourceLen = static_cast<uint32_t>(message.sourceId.length());
        data.insert(data.end(), reinterpret_cast<uint8_t*>(&sourceLen), 
                   reinterpret_cast<uint8_t*>(&sourceLen) + sizeof(sourceLen));
        data.insert(data.end(), message.sourceId.begin(), message.sourceId.end());
        
        uint32_t destLen = static_cast<uint32_t>(message.destinationId.length());
        data.insert(data.end(), reinterpret_cast<uint8_t*>(&destLen), 
                   reinterpret_cast<uint8_t*>(&destLen) + sizeof(destLen));
        data.insert(data.end(), message.destinationId.begin(), message.destinationId.end());
        
        // Серіалізація даних
        // Serialize data
        // Сериализация данных
        uint32_t dataLen = static_cast<uint32_t>(message.data.size());
        data.insert(data.end(), reinterpret_cast<uint8_t*>(&dataLen), 
                   reinterpret_cast<uint8_t*>(&dataLen) + sizeof(dataLen));
        data.insert(data.end(), message.data.begin(), message.data.end());
        
        // Серіалізація мітки часу
        // Serialize timestamp
        // Сериализация метки времени
        auto duration = message.timestamp.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        uint64_t timestamp = static_cast<uint64_t>(millis);
        const uint8_t* timestampPtr = reinterpret_cast<const uint8_t*>(&timestamp);
        data.insert(data.end(), timestampPtr, timestampPtr + sizeof(timestamp));
        
        // Серіалізація номера послідовності
        // Serialize sequence number
        // Сериализация номера последовательности
        const uint8_t* sequencePtr = reinterpret_cast<const uint8_t*>(&message.sequenceNumber);
        data.insert(data.end(), sequencePtr, sequencePtr + sizeof(message.sequenceNumber));
        
        return data;
    }

    // Десеріалізація повідомлення
    // Deserialize message
    // Десериализация сообщения
    NetworkMessage NetworkCommunication::deserializeMessage(const std::vector<uint8_t>& data) const {
        NetworkMessage message;
        
        if (data.size() < sizeof(uint8_t) + sizeof(uint32_t) * 2 + sizeof(uint64_t) + sizeof(uint32_t)) {
            std::cerr << "Invalid message data size" << std::endl;
            return message;
        }
        
        size_t offset = 0;
        
        // Десеріалізація типу повідомлення
        // Deserialize message type
        // Десериализация типа сообщения
        message.type = static_cast<MessageType>(data[offset]);
        offset += sizeof(uint8_t);
        
        // Десеріалізація ідентифікатора джерела
        // Deserialize source ID
        // Десериализация идентификатора источника
        uint32_t sourceLen;
        std::memcpy(&sourceLen, &data[offset], sizeof(sourceLen));
        offset += sizeof(sourceLen);
        
        if (offset + sourceLen > data.size()) {
            std::cerr << "Invalid source ID length" << std::endl;
            return message;
        }
        
        message.sourceId.assign(data.begin() + offset, data.begin() + offset + sourceLen);
        offset += sourceLen;
        
        // Десеріалізація ідентифікатора призначення
        // Deserialize destination ID
        // Десериализация идентификатора назначения
        uint32_t destLen;
        std::memcpy(&destLen, &data[offset], sizeof(destLen));
        offset += sizeof(destLen);
        
        if (offset + destLen > data.size()) {
            std::cerr << "Invalid destination ID length" << std::endl;
            return message;
        }
        
        message.destinationId.assign(data.begin() + offset, data.begin() + offset + destLen);
        offset += destLen;
        
        // Десеріалізація даних
        // Deserialize data
        // Десериализация данных
        uint32_t dataLen;
        std::memcpy(&dataLen, &data[offset], sizeof(dataLen));
        offset += sizeof(dataLen);
        
        if (offset + dataLen > data.size()) {
            std::cerr << "Invalid data length" << std::endl;
            return message;
        }
        
        message.data.assign(data.begin() + offset, data.begin() + offset + dataLen);
        offset += dataLen;
        
        // Десеріалізація мітки часу
        // Deserialize timestamp
        // Десериализация метки времени
        uint64_t timestamp;
        std::memcpy(&timestamp, &data[offset], sizeof(timestamp));
        offset += sizeof(timestamp);
        
        message.timestamp = std::chrono::system_clock::time_point(
            std::chrono::milliseconds(timestamp));
        
        // Десеріалізація номера послідовності
        // Deserialize sequence number
        // Десериализация номера последовательности
        std::memcpy(&message.sequenceNumber, &data[offset], sizeof(message.sequenceNumber));
        
        return message;
    }

    // Цикл сервера
    // Server loop
    // Цикл сервера
    void NetworkCommunication::serverLoop() {
        while (serverRunning.load()) {
            // Імітація обробки підключень
            // Simulate connection processing
            // Имитация обработки подключений
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // Імітуємо отримання вхідного повідомлення
            // Simulate receiving incoming message
            // Имитируем получение входящего сообщения
            if (connectedNodes.size() > 0) {
                // Вибираємо випадковий підключений вузол
                // Select random connected node
                // Выбираем случайный подключенный узел
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, static_cast<int>(connectedNodes.size()) - 1);
                
                auto it = connectedNodes.begin();
                std::advance(it, dis(gen));
                
                // Створюємо вхідне повідомлення
                // Create incoming message
                // Создаем входящее сообщение
                std::vector<uint8_t> dummyData = {0x01, 0x02, 0x03, 0x04};
                NetworkMessage msg(MessageType::SIGNAL_DATA, it->first, nodeId, dummyData);
                
                // Додаємо повідомлення до черги вхідних повідомлень
                // Add message to incoming message queue
                // Добавляем сообщение в очередь входящих сообщений
                {
                    std::lock_guard<std::mutex> lock(incomingMutex);
                    incomingMessages.push(msg);
                    incomingMessageCount++;
                }
                
                messageCondition.notify_one();
            }
        }
    }

    // Обробка вхідного підключення
    // Handle incoming connection
    // Обработка входящего подключения
    void NetworkCommunication::handleIncomingConnection(const std::string& nodeId) {
        std::lock_guard<std::mutex> lock(networkMutex);
        connectedNodes[nodeId] = true;
        std::cout << "Incoming connection from node: " << nodeId << std::endl;
    }

    // Обробка відключення
    // Handle disconnection
    // Обработка отключения
    void NetworkCommunication::handleDisconnection(const std::string& nodeId) {
        disconnect(nodeId);
    }

    // Обробка вхідного повідомлення
    // Process incoming message
    // Обработка входящего сообщения
    void NetworkCommunication::processIncomingMessage(const NetworkMessage& message) {
        // Додаємо повідомлення до черги вхідних повідомлень
        // Add message to incoming message queue
        // Добавляем сообщение в очередь входящих сообщений
        {
            std::lock_guard<std::mutex> lock(incomingMutex);
            incomingMessages.push(message);
            incomingMessageCount++;
        }
        
        messageCondition.notify_one();
        
        std::cout << "Processed incoming message from " << message.sourceId << std::endl;
    }

    // Валідація повідомлення
    // Validate message
    // Валидация сообщения
    bool NetworkCommunication::validateMessage(const NetworkMessage& message) const {
        // Перевірка на порожні ідентифікатори
        // Check for empty identifiers
        // Проверка на пустые идентификаторы
        if (message.sourceId.empty() || message.destinationId.empty()) {
            return false;
        }
        
        // Перевірка типу повідомлення
        // Check message type
        // Проверка типа сообщения
        if (message.type < MessageType::NEURON_DATA || message.type > MessageType::CUSTOM_DATA) {
            return false;
        }
        
        // Перевірка мітки часу
        // Check timestamp
        // Проверка метки времени
        auto now = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(now - message.timestamp).count();
        
        // Повідомлення не повинні бути старішими за 10 секунд
        // Messages should not be older than 10 seconds
        // Сообщения не должны быть старше 10 секунд
        if (diff > 10) {
            return false;
        }
        
        return true;
    }

    // Генерація ідентифікатора вузла
    // Generate node ID
    // Генерация идентификатора узла
    std::string NetworkCommunication::generateNodeId() {
        // Генерація унікального ідентифікатора
        // Generate unique identifier
        // Генерация уникального идентификатора
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        
        std::stringstream ss;
        ss << "node_";
        
        for (int i = 0; i < 8; ++i) {
            ss << std::hex << std::setfill('0') << std::setw(2) << dis(gen);
        }
        
        return ss.str();
    }

    // Глобальна мережева комунікація
    // Global network communication
    // Глобальная сетевая коммуникация
    std::unique_ptr<NetworkCommunication> gNetworkComm = nullptr;

} // namespace NeuroSync