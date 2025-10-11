#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "NetworkCommunication.h"
#include <string>
#include <memory>

namespace NeuroSync {
namespace Network {

    // Менеджер мережі
    // Network manager
    // Менеджер сети
    class NetworkManager : public NetworkCommunication {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        NetworkManager();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~NetworkManager();
        
        // Ініціалізація мережевого менеджера
        // Initialize network manager
        // Инициализация сетевого менеджера
        bool initialize(const NetworkConfig& config = NetworkConfig());
        
        // Підключення до сервера
        // Connect to server
        // Подключение к серверу
        bool connectToServer(const std::string& host, uint16_t port);
        
        // Надсилання повідомлення вузлу
        // Send message to node
        // Отправка сообщения узлу
        bool sendMessage(const std::string& nodeId, const std::string& message);
        
        // Надсилання повідомлення серверу
        // Send message to server
        // Отправка сообщения серверу
        bool sendMessageToServer(const std::string& message);
    };

} // namespace Network
} // namespace NeuroSync

#endif // NETWORK_MANAGER_H