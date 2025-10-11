#ifndef NETWORK_COMMUNICATION_H
#define NETWORK_COMMUNICATION_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <chrono>

// NetworkCommunication.h
// Мережева комунікація для NeuroSync OS Sparky
// Network communication for NeuroSync OS Sparky
// Сетевая коммуникация для NeuroSync OS Sparky

namespace NeuroSync {

    // Типи повідомлень
    // Message types
    // Типы сообщений
    enum class MessageType {
        NEURON_DATA,        // Дані нейрона
        // Neuron data
        // Данные нейрона
        
        SYNAPSE_DATA,       // Дані синапса
        // Synapse data
        // Данные синапса
        
        SIGNAL_DATA,        // Сигнальні дані
        // Signal data
        // Сигнальные данные
        
        CONFIG_DATA,        // Дані конфігурації
        // Configuration data
        // Данные конфигурации
        
        COMMAND_DATA,       // Командні дані
        // Command data
        // Командные данные
        
        HEARTBEAT,          // Сигнал життя
        // Heartbeat signal
        // Сигнал жизни
        
        DISCOVERY,          // Повідомлення виявлення
        // Discovery message
        // Сообщение обнаружения
        
        CUSTOM_DATA         // Користувацькі дані
        // Custom data
        // Пользовательские данные
    };

    // Структура повідомлення
    // Message structure
    // Структура сообщения
    struct NetworkMessage {
        MessageType type;
        std::string sourceId;
        std::string destinationId;
        std::vector<uint8_t> data;
        std::chrono::system_clock::time_point timestamp;
        uint32_t sequenceNumber;
        
        NetworkMessage() : type(MessageType::CUSTOM_DATA), sequenceNumber(0) {}
        
        NetworkMessage(MessageType t, const std::string& src, const std::string& dest, 
                      const std::vector<uint8_t>& d)
            : type(t), sourceId(src), destinationId(dest), data(d), 
              timestamp(std::chrono::system_clock::now()), sequenceNumber(0) {}
    };

    // Статус мережі
    // Network status
    // Статус сети
    enum class NetworkStatus {
        DISCONNECTED,       // Від'єднано
        // Disconnected
        // Отключено
        
        CONNECTING,         // Підключення
        // Connecting
        // Подключение
        
        CONNECTED,          // Підключено
        // Connected
        // Подключено
        
        ERROR               // Помилка
        // Error
        // Ошибка
    };

    // Конфігурація мережі
    // Network configuration
    // Конфигурация сети
    struct NetworkConfig {
        std::string host;
        uint16_t port;
        uint32_t maxConnections;
        uint32_t bufferSize;
        uint32_t timeoutMs;
        bool enableEncryption;
        std::string encryptionKey;
        
        NetworkConfig() : port(0), maxConnections(100), bufferSize(4096), 
                         timeoutMs(5000), enableEncryption(false) {}
    };

    // Інтерфейс мережевої комунікації
    // Network communication interface
    // Интерфейс сетевой коммуникации
    class NetworkCommunication {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        NetworkCommunication();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~NetworkCommunication();
        
        // Ініціалізація мережевої комунікації
        // Initialize network communication
        // Инициализация сетевой коммуникации
        virtual bool initialize(const NetworkConfig& config);
        
        // Підключення до віддаленого вузла
        // Connect to remote node
        // Подключение к удаленному узлу
        virtual bool connect(const std::string& host, uint16_t port);
        
        // Від'єднання від віддаленого вузла
        // Disconnect from remote node
        // Отключение от удаленного узла
        virtual void disconnect(const std::string& nodeId);
        
        // Від'єднання від усіх вузлів
        // Disconnect from all nodes
        // Отключение от всех узлов
        virtual void disconnectAll();
        
        // Надсилання повідомлення
        // Send message
        // Отправка сообщения
        virtual bool sendMessage(const NetworkMessage& message);
        
        // Отримання повідомлення
        // Receive message
        // Получение сообщения
        virtual bool receiveMessage(NetworkMessage& message);
        
        // Надсилання сигналу життя
        // Send heartbeat
        // Отправка сигнала жизни
        virtual void sendHeartbeat();
        
        // Отримання статусу мережі
        // Get network status
        // Получение статуса сети
        NetworkStatus getStatus() const;
        
        // Отримання ідентифікатора вузла
        // Get node ID
        // Получение идентификатора узла
        std::string getNodeId() const;
        
        // Встановлення ідентифікатора вузла
        // Set node ID
        // Установка идентификатора узла
        void setNodeId(const std::string& nodeId);
        
        // Отримання кількості підключених вузлів
        // Get connected node count
        // Получение количества подключенных узлов
        size_t getConnectedNodeCount() const;
        
        // Перевірка, чи підключений вузол
        // Check if node is connected
        // Проверка, подключен ли узел
        bool isNodeConnected(const std::string& nodeId) const;
        
        // Отримання списку підключених вузлів
        // Get list of connected nodes
        // Получение списка подключенных узлов
        std::vector<std::string> getConnectedNodes() const;
        
        // Запуск сервера
        // Start server
        // Запуск сервера
        virtual bool startServer();
        
        // Зупинка сервера
        // Stop server
        // Остановка сервера
        virtual void stopServer();
        
        // Отримання кількості вхідних повідомлень
        // Get incoming message count
        // Получение количества входящих сообщений
        size_t getIncomingMessageCount() const;
        
        // Отримання кількості вихідних повідомлень
        // Get outgoing message count
        // Получение количества исходящих сообщений
        size_t getOutgoingMessageCount() const;
        
        // Очищення статистики
        // Clear statistics
        // Очистка статистики
        void clearStatistics();
        
    protected:
        NetworkConfig config;
        NetworkStatus status;
        std::string nodeId;
        std::map<std::string, bool> connectedNodes;
        std::queue<NetworkMessage> incomingMessages;
        std::queue<NetworkMessage> outgoingMessages;
        std::atomic<uint64_t> incomingMessageCount;
        std::atomic<uint64_t> outgoingMessageCount;
        std::atomic<uint32_t> sequenceCounter;
        mutable std::mutex networkMutex;
        mutable std::mutex incomingMutex;
        mutable std::mutex outgoingMutex;
        std::condition_variable messageCondition;
        std::atomic<bool> serverRunning;
        std::unique_ptr<std::thread> serverThread;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        virtual bool sendRawData(const std::string& nodeId, const std::vector<uint8_t>& data);
        virtual bool receiveRawData(const std::string& nodeId, std::vector<uint8_t>& data);
        virtual std::vector<uint8_t> serializeMessage(const NetworkMessage& message) const;
        virtual NetworkMessage deserializeMessage(const std::vector<uint8_t>& data) const;
        virtual void serverLoop();
        virtual void handleIncomingConnection(const std::string& nodeId);
        virtual void handleDisconnection(const std::string& nodeId);
        virtual void processIncomingMessage(const NetworkMessage& message);
        virtual bool validateMessage(const NetworkMessage& message) const;
        virtual std::string generateNodeId();
    };

    // Глобальна мережева комунікація
    // Global network communication
    // Глобальная сетевая коммуникация
    extern std::unique_ptr<NetworkCommunication> gNetworkComm;

} // namespace NeuroSync

#endif // NETWORK_COMMUNICATION_H