#include "NetworkManager.h"
#include <iostream>

namespace NeuroSync {
namespace Network {

    // Конструктор мережевого менеджера
    // Network manager constructor
    // Конструктор сетевого менеджера
    NetworkManager::NetworkManager() {
        // Ініціалізація мережевого менеджера
        // Initialize network manager
        // Инициализация сетевого менеджера
    }

    // Деструктор мережевого менеджера
    // Network manager destructor
    // Деструктор сетевого менеджера
    NetworkManager::~NetworkManager() {
        // Очищення ресурсів мережевого менеджера
        // Clean up network manager resources
        // Очистка ресурсов сетевого менеджера
    }

    // Ініціалізація мережевого менеджера
    // Initialize network manager
    // Инициализация сетевого менеджера
    bool NetworkManager::initialize(const NetworkConfig& config) {
        // Виклик батьківського методу ініціалізації
        // Call parent initialization method
        // Вызов родительского метода инициализации
        if (!NetworkCommunication::initialize(config)) {
            return false;
        }
        
        std::cout << "[NETWORK] Network manager initialized" << std::endl;
        return true;
    }

    // Підключення до сервера
    // Connect to server
    // Подключение к серверу
    bool NetworkManager::connectToServer(const std::string& host, uint16_t port) {
        // Підключення до віддаленого сервера
        // Connect to remote server
        // Подключение к удаленному серверу
        bool result = NetworkCommunication::connect(host, port);
        
        if (result) {
            std::cout << "[NETWORK] Connected to server at " << host << ":" << port << std::endl;
        } else {
            std::cout << "[NETWORK] Failed to connect to server at " << host << ":" << port << std::endl;
        }
        
        return result;
    }

    // Надсилання повідомлення вузлу
    // Send message to node
    // Отправка сообщения узлу
    bool NetworkManager::sendMessage(const std::string& nodeId, const std::string& message) {
        // Створення мережевого повідомлення
        // Create network message
        // Создание сетевого сообщения
        NetworkMessage netMessage(MessageType::CUSTOM_DATA, getNodeId(), nodeId, 
                                 std::vector<uint8_t>(message.begin(), message.end()));
        
        // Надсилання повідомлення
        // Send message
        // Отправка сообщения
        bool result = NetworkCommunication::sendMessage(netMessage);
        
        if (result) {
            std::cout << "[NETWORK] Message sent to node " << nodeId << std::endl;
        } else {
            std::cout << "[NETWORK] Failed to send message to node " << nodeId << std::endl;
        }
        
        return result;
    }

    // Надсилання повідомлення серверу
    // Send message to server
    // Отправка сообщения серверу
    bool NetworkManager::sendMessageToServer(const std::string& message) {
        // Надсилання повідомлення серверу
        // Send message to server
        // Отправка сообщения серверу
        return sendMessage("server", message);
    }

} // namespace Network
} // namespace NeuroSync