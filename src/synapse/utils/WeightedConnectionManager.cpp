#include "WeightedConnectionManager.h"
#include <chrono>
#include <algorithm>
#include <sstream>

// WeightedConnectionManager.cpp
// Реалізація менеджера зважених з'єднань для SynapseBus
// Implementation of weighted connection manager for SynapseBus
// Реализация менеджера взвешенных соединений для SynapseBus

namespace NeuroSync {
namespace Synapse {
namespace Utils {

    WeightedConnectionManager::WeightedConnectionManager() : initialized(false) {
        // Конструктор менеджера зважених з'єднань
        // Constructor of weighted connection manager
        // Конструктор менеджера взвешенных соединений
        
        // Ініціалізація статистики
        // Initialize statistics
        // Инициализация статистики
        stats.totalConnections = 0;
        stats.activeConnections = 0;
        stats.inactiveConnections = 0;
        stats.averageWeight = 0.0;
        stats.totalUsage = 0;
        stats.averageUsagePerConnection = 0.0;
    }

    WeightedConnectionManager::~WeightedConnectionManager() {
        // Деструктор менеджера зважених з'єднань
        // Destructor of weighted connection manager
        // Деструктор менеджера взвешенных соединений
        clearAllConnections();
    }

    bool WeightedConnectionManager::initialize() {
        // Ініціалізація менеджера
        // Initialize manager
        // Инициализация менеджера
        
        if (initialized) {
            return true; // Вже ініціалізовано / Already initialized / Уже инициализировано
        }
        
        // Очищення існуючих з'єднань
        // Clear existing connections
        // Очистка существующих соединений
        clearAllConnections();
        
        initialized = true;
        return true;
    }

    bool WeightedConnectionManager::createConnection(int sourceNeuronId, int targetNeuronId, double weight) {
        // Створення зваженого з'єднання
        // Create weighted connection
        // Создание взвешенного соединения
        
        if (!initialized) {
            return false;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Перевірка, чи з'єднання вже існує
        // Check if connection already exists
        // Проверка, существует ли соединение
        if (connections.find(key) != connections.end()) {
            return false; // З'єднання вже існує / Connection already exists / Соединение уже существует
        }
        
        // Створення нового з'єднання
        // Create new connection
        // Создание нового соединения
        WeightedConnection connection;
        connection.sourceNeuronId = sourceNeuronId;
        connection.targetNeuronId = targetNeuronId;
        connection.weight = weight;
        connection.creationTime = getCurrentTimeMillis();
        connection.lastUsedTime = connection.creationTime;
        connection.usageCount = 0;
        connection.active = true;
        
        // Додавання з'єднання до карт
        // Add connection to maps
        // Добавление соединения в карты
        connections[key] = connection;
        incomingConnections[targetNeuronId].push_back(key);
        outgoingConnections[sourceNeuronId].push_back(key);
        
        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        updateConnectionStatistics(connection);
        
        return true;
    }

    bool WeightedConnectionManager::removeConnection(int sourceNeuronId, int targetNeuronId) {
        // Видалення зваженого з'єднання
        // Remove weighted connection
        // Удаление взвешенного соединения
        
        if (!initialized) {
            return false;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Пошук з'єднання
        // Find connection
        // Поиск соединения
        auto it = connections.find(key);
        if (it == connections.end()) {
            return false; // З'єднання не знайдено / Connection not found / Соединение не найдено
        }
        
        // Отримання з'єднання для оновлення статистики
        // Get connection for statistics update
        // Получение соединения для обновления статистики
        WeightedConnection connection = it->second;
        
        // Видалення з'єднання з карт
        // Remove connection from maps
        // Удаление соединения из карт
        connections.erase(it);
        removeConnectionFromMaps(sourceNeuronId, targetNeuronId);
        
        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        // Тут можна оновити статистику, якщо потрібно
        // Here we can update statistics if needed
        // Тут можно обновить статистику, если нужно
        
        return true;
    }

    bool WeightedConnectionManager::updateConnectionWeight(int sourceNeuronId, int targetNeuronId, double weight) {
        // Оновлення ваги з'єднання
        // Update connection weight
        // Обновление веса соединения
        
        if (!initialized) {
            return false;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Пошук з'єднання
        // Find connection
        // Поиск соединения
        auto it = connections.find(key);
        if (it == connections.end()) {
            return false; // З'єднання не знайдено / Connection not found / Соединение не найдено
        }
        
        // Оновлення ваги
        // Update weight
        // Обновление веса
        it->second.weight = weight;
        
        // Оновлення часу останнього використання
        // Update last used time
        // Обновление времени последнего использования
        it->second.lastUsedTime = getCurrentTimeMillis();
        
        return true;
    }

    double WeightedConnectionManager::getConnectionWeight(int sourceNeuronId, int targetNeuronId) const {
        // Отримання ваги з'єднання
        // Get connection weight
        // Получение веса соединения
        
        if (!initialized) {
            return 0.0;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Пошук з'єднання
        // Find connection
        // Поиск соединения
        auto it = connections.find(key);
        if (it == connections.end()) {
            return 0.0; // З'єднання не знайдено / Connection not found / Соединение не найдено
        }
        
        return it->second.weight;
    }

    bool WeightedConnectionManager::connectionExists(int sourceNeuronId, int targetNeuronId) const {
        // Перевірка існування з'єднання
        // Check if connection exists
        // Проверка существования соединения
        
        if (!initialized) {
            return false;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        return connections.find(key) != connections.end();
    }

    bool WeightedConnectionManager::activateConnection(int sourceNeuronId, int targetNeuronId) {
        // Активація з'єднання
        // Activate connection
        // Активация соединения
        
        if (!initialized) {
            return false;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Пошук з'єднання
        // Find connection
        // Поиск соединения
        auto it = connections.find(key);
        if (it == connections.end()) {
            return false; // З'єднання не знайдено / Connection not found / Соединение не найдено
        }
        
        // Активація з'єднання
        // Activate connection
        // Активация соединения
        it->second.active = true;
        
        return true;
    }

    bool WeightedConnectionManager::deactivateConnection(int sourceNeuronId, int targetNeuronId) {
        // Деактивація з'єднання
        // Deactivate connection
        // Деактивация соединения
        
        if (!initialized) {
            return false;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Пошук з'єднання
        // Find connection
        // Поиск соединения
        auto it = connections.find(key);
        if (it == connections.end()) {
            return false; // З'єднання не знайдено / Connection not found / Соединение не найдено
        }
        
        // Деактивація з'єднання
        // Deactivate connection
        // Деактивация соединения
        it->second.active = false;
        
        return true;
    }

    std::vector<WeightedConnection> WeightedConnectionManager::getConnectionsForNeuron(int neuronId) const {
        // Отримання всіх з'єднань для нейрона
        // Get all connections for neuron
        // Получение всех соединений для нейрона
        
        std::vector<WeightedConnection> result;
        
        if (!initialized) {
            return result;
        }
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Отримання вхідних з'єднань
        // Get incoming connections
        // Получение входящих соединений
        auto incomingIt = incomingConnections.find(neuronId);
        if (incomingIt != incomingConnections.end()) {
            for (const std::string& key : incomingIt->second) {
                auto connIt = connections.find(key);
                if (connIt != connections.end()) {
                    result.push_back(connIt->second);
                }
            }
        }
        
        // Отримання вихідних з'єднань
        // Get outgoing connections
        // Получение исходящих соединений
        auto outgoingIt = outgoingConnections.find(neuronId);
        if (outgoingIt != outgoingConnections.end()) {
            for (const std::string& key : outgoingIt->second) {
                auto connIt = connections.find(key);
                if (connIt != connections.end() && 
                    std::find_if(result.begin(), result.end(), 
                                [&connIt](const WeightedConnection& conn) {
                                    return conn.sourceNeuronId == connIt->second.sourceNeuronId && 
                                           conn.targetNeuronId == connIt->second.targetNeuronId;
                                }) == result.end()) {
                    result.push_back(connIt->second);
                }
            }
        }
        
        return result;
    }

    std::vector<WeightedConnection> WeightedConnectionManager::getIncomingConnections(int neuronId) const {
        // Отримання всіх вхідних з'єднань для нейрона
        // Get all incoming connections for neuron
        // Получение всех входящих соединений для нейрона
        
        std::vector<WeightedConnection> result;
        
        if (!initialized) {
            return result;
        }
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Отримання вхідних з'єднань
        // Get incoming connections
        // Получение входящих соединений
        auto incomingIt = incomingConnections.find(neuronId);
        if (incomingIt != incomingConnections.end()) {
            for (const std::string& key : incomingIt->second) {
                auto connIt = connections.find(key);
                if (connIt != connections.end()) {
                    result.push_back(connIt->second);
                }
            }
        }
        
        return result;
    }

    std::vector<WeightedConnection> WeightedConnectionManager::getOutgoingConnections(int neuronId) const {
        // Отримання всіх вихідних з'єднань для нейрона
        // Get all outgoing connections for neuron
        // Получение всех исходящих соединений для нейрона
        
        std::vector<WeightedConnection> result;
        
        if (!initialized) {
            return result;
        }
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Отримання вихідних з'єднань
        // Get outgoing connections
        // Получение исходящих соединений
        auto outgoingIt = outgoingConnections.find(neuronId);
        if (outgoingIt != outgoingConnections.end()) {
            for (const std::string& key : outgoingIt->second) {
                auto connIt = connections.find(key);
                if (connIt != connections.end()) {
                    result.push_back(connIt->second);
                }
            }
        }
        
        return result;
    }

    size_t WeightedConnectionManager::getConnectionCount() const {
        // Отримання кількості з'єднань
        // Get connection count
        // Получение количества соединений
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        return connections.size();
    }

    size_t WeightedConnectionManager::getIncomingConnectionCount(int neuronId) const {
        // Отримання кількості вхідних з'єднань для нейрона
        // Get incoming connection count for neuron
        // Получение количества входящих соединений для нейрона
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        auto it = incomingConnections.find(neuronId);
        if (it != incomingConnections.end()) {
            return it->second.size();
        }
        return 0;
    }

    size_t WeightedConnectionManager::getOutgoingConnectionCount(int neuronId) const {
        // Отримання кількості вихідних з'єднань для нейрона
        // Get outgoing connection count for neuron
        // Получение количества исходящих соединений для нейрона
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        auto it = outgoingConnections.find(neuronId);
        if (it != outgoingConnections.end()) {
            return it->second.size();
        }
        return 0;
    }

    void WeightedConnectionManager::clearAllConnections() {
        // Очищення всіх з'єднань
        // Clear all connections
        // Очистка всех соединений
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        connections.clear();
        incomingConnections.clear();
        outgoingConnections.clear();
    }

    WeightedConnectionManager::ConnectionStatistics WeightedConnectionManager::getStatistics() const {
        // Отримання статистики з'єднань
        // Get connection statistics
        // Получение статистики соединений
        
        std::lock_guard<std::mutex> lock(statisticsMutex);
        return stats;
    }

    void WeightedConnectionManager::updateUsageStatistics(int sourceNeuronId, int targetNeuronId) {
        // Оновлення статистики використання
        // Update usage statistics
        // Обновление статистики использования
        
        if (!initialized) {
            return;
        }
        
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Пошук з'єднання
        // Find connection
        // Поиск соединения
        auto it = connections.find(key);
        if (it != connections.end()) {
            // Оновлення статистики використання
            // Update usage statistics
            // Обновление статистики использования
            it->second.usageCount++;
            it->second.lastUsedTime = getCurrentTimeMillis();
        }
    }

    std::vector<WeightedConnection> WeightedConnectionManager::getConnectionsSortedByWeight(bool descending) const {
        // Отримання з'єднань, відсортованих за вагою
        // Get connections sorted by weight
        // Получение соединений, отсортированных по весу
        
        std::vector<WeightedConnection> result;
        
        if (!initialized) {
            return result;
        }
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Копіювання всіх з'єднань
        // Copy all connections
        // Копирование всех соединений
        for (const auto& pair : connections) {
            result.push_back(pair.second);
        }
        
        // Сортування за вагою
        // Sort by weight
        // Сортировка по весу
        if (descending) {
            std::sort(result.begin(), result.end(), 
                     [](const WeightedConnection& a, const WeightedConnection& b) {
                         return a.weight > b.weight;
                     });
        } else {
            std::sort(result.begin(), result.end(), 
                     [](const WeightedConnection& a, const WeightedConnection& b) {
                         return a.weight < b.weight;
                     });
        }
        
        return result;
    }

    std::vector<WeightedConnection> WeightedConnectionManager::getConnectionsSortedByUsageTime(bool descending) const {
        // Отримання з'єднань, відсортованих за часом використання
        // Get connections sorted by usage time
        // Получение соединений, отсортированных по времени использования
        
        std::vector<WeightedConnection> result;
        
        if (!initialized) {
            return result;
        }
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Копіювання всіх з'єднань
        // Copy all connections
        // Копирование всех соединений
        for (const auto& pair : connections) {
            result.push_back(pair.second);
        }
        
        // Сортування за часом використання
        // Sort by usage time
        // Сортировка по времени использования
        if (descending) {
            std::sort(result.begin(), result.end(), 
                     [](const WeightedConnection& a, const WeightedConnection& b) {
                         return a.lastUsedTime > b.lastUsedTime;
                     });
        } else {
            std::sort(result.begin(), result.end(), 
                     [](const WeightedConnection& a, const WeightedConnection& b) {
                         return a.lastUsedTime < b.lastUsedTime;
                     });
        }
        
        return result;
    }

    std::vector<WeightedConnection> WeightedConnectionManager::getConnectionsSortedByUsageCount(bool descending) const {
        // Отримання з'єднань, відсортованих за кількістю використань
        // Get connections sorted by usage count
        // Получение соединений, отсортированных по количеству использований
        
        std::vector<WeightedConnection> result;
        
        if (!initialized) {
            return result;
        }
        
        std::lock_guard<std::mutex> lock(connectionsMutex);
        
        // Копіювання всіх з'єднань
        // Copy all connections
        // Копирование всех соединений
        for (const auto& pair : connections) {
            result.push_back(pair.second);
        }
        
        // Сортування за кількістю використань
        // Sort by usage count
        // Сортировка по количеству использований
        if (descending) {
            std::sort(result.begin(), result.end(), 
                     [](const WeightedConnection& a, const WeightedConnection& b) {
                         return a.usageCount > b.usageCount;
                     });
        } else {
            std::sort(result.begin(), result.end(), 
                     [](const WeightedConnection& a, const WeightedConnection& b) {
                         return a.usageCount < b.usageCount;
                     });
        }
        
        return result;
    }

    std::string WeightedConnectionManager::generateConnectionKey(int sourceNeuronId, int targetNeuronId) const {
        // Генерація ключа з'єднання
        // Generate connection key
        // Генерация ключа соединения
        
        std::ostringstream keyStream;
        keyStream << sourceNeuronId << "_" << targetNeuronId;
        return keyStream.str();
    }

    long long WeightedConnectionManager::getCurrentTimeMillis() const {
        // Отримання поточного часу в мілісекундах
        // Get current time in milliseconds
        // Получение текущего времени в миллисекундах
        
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return millis;
    }

    void WeightedConnectionManager::updateConnectionStatistics(const WeightedConnection& connection) {
        // Оновлення статистики з'єднання
        // Update connection statistics
        // Обновление статистики соединения
        
        std::lock_guard<std::mutex> lock(statisticsMutex);
        stats.totalConnections++;
        if (connection.active) {
            stats.activeConnections++;
        } else {
            stats.inactiveConnections++;
        }
        
        // Оновлення середньої ваги
        // Update average weight
        // Обновление среднего веса
        stats.averageWeight = (stats.averageWeight * (stats.totalConnections - 1) + connection.weight) / stats.totalConnections;
    }

    void WeightedConnectionManager::removeConnectionFromMaps(int sourceNeuronId, int targetNeuronId) {
        // Видалення з'єднання з карт
        // Remove connection from maps
        // Удаление соединения из карт
        
        // Видалення з вхідних з'єднань
        // Remove from incoming connections
        // Удаление из входящих соединений
        auto incomingIt = incomingConnections.find(targetNeuronId);
        if (incomingIt != incomingConnections.end()) {
            auto& keys = incomingIt->second;
            std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
            keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
        }
        
        // Видалення з вихідних з'єднань
        // Remove from outgoing connections
        // Удаление из исходящих соединений
        auto outgoingIt = outgoingConnections.find(sourceNeuronId);
        if (outgoingIt != outgoingConnections.end()) {
            auto& keys = outgoingIt->second;
            std::string key = generateConnectionKey(sourceNeuronId, targetNeuronId);
            keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
        }
    }

} // namespace Utils
} // namespace Synapse
} // namespace NeuroSync