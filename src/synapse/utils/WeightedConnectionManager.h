#ifndef WEIGHTED_CONNECTION_MANAGER_H
#define WEIGHTED_CONNECTION_MANAGER_H

#include <map>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>

// WeightedConnectionManager.h
// Менеджер зважених з'єднань для SynapseBus
// Weighted connection manager for SynapseBus
// Менеджер взвешенных соединений для SynapseBus

namespace NeuroSync {
namespace Synapse {
namespace Utils {

    // Структура зваженого з'єднання
    // Weighted connection structure
    // Структура взвешенного соединения
    struct WeightedConnection {
        int sourceNeuronId;     // ID вихідного нейрона / Source neuron ID / ID исходного нейрона
        int targetNeuronId;     // ID цільового нейрона / Target neuron ID / ID целевого нейрона
        double weight;          // Вага з'єднання / Connection weight / Вес соединения
        long long creationTime;  // Час створення / Creation time / Время создания
        long long lastUsedTime;  // Час останнього використання / Last used time / Время последнего использования
        int usageCount;         // Кількість використань / Usage count / Количество использований
        bool active;            // Активність з'єднання / Connection activity / Активность соединения
    };

    // Менеджер зважених з'єднань
    // Weighted connection manager
    // Менеджер взвешенных соединений
    class WeightedConnectionManager {
    public:
        WeightedConnectionManager();
        ~WeightedConnectionManager();
        
        // Ініціалізація менеджера
        // Initialize manager
        // Инициализация менеджера
        bool initialize();
        
        // Створення зваженого з'єднання
        // Create weighted connection
        // Создание взвешенного соединения
        bool createConnection(int sourceNeuronId, int targetNeuronId, double weight);
        
        // Видалення зваженого з'єднання
        // Remove weighted connection
        // Удаление взвешенного соединения
        bool removeConnection(int sourceNeuronId, int targetNeuronId);
        
        // Оновлення ваги з'єднання
        // Update connection weight
        // Обновление веса соединения
        bool updateConnectionWeight(int sourceNeuronId, int targetNeuronId, double weight);
        
        // Отримання ваги з'єднання
        // Get connection weight
        // Получение веса соединения
        double getConnectionWeight(int sourceNeuronId, int targetNeuronId) const;
        
        // Перевірка існування з'єднання
        // Check if connection exists
        // Проверка существования соединения
        bool connectionExists(int sourceNeuronId, int targetNeuronId) const;
        
        // Активація з'єднання
        // Activate connection
        // Активация соединения
        bool activateConnection(int sourceNeuronId, int targetNeuronId);
        
        // Деактивація з'єднання
        // Deactivate connection
        // Деактивация соединения
        bool deactivateConnection(int sourceNeuronId, int targetNeuronId);
        
        // Отримання всіх з'єднань для нейрона
        // Get all connections for neuron
        // Получение всех соединений для нейрона
        std::vector<WeightedConnection> getConnectionsForNeuron(int neuronId) const;
        
        // Отримання всіх вхідних з'єднань для нейрона
        // Get all incoming connections for neuron
        // Получение всех входящих соединений для нейрона
        std::vector<WeightedConnection> getIncomingConnections(int neuronId) const;
        
        // Отримання всіх вихідних з'єднань для нейрона
        // Get all outgoing connections for neuron
        // Получение всех исходящих соединений для нейрона
        std::vector<WeightedConnection> getOutgoingConnections(int neuronId) const;
        
        // Отримання кількості з'єднань
        // Get connection count
        // Получение количества соединений
        size_t getConnectionCount() const;
        
        // Отримання кількості вхідних з'єднань для нейрона
        // Get incoming connection count for neuron
        // Получение количества входящих соединений для нейрона
        size_t getIncomingConnectionCount(int neuronId) const;
        
        // Отримання кількості вихідних з'єднань для нейрона
        // Get outgoing connection count for neuron
        // Получение количества исходящих соединений для нейрона
        size_t getOutgoingConnectionCount(int neuronId) const;
        
        // Очищення всіх з'єднань
        // Clear all connections
        // Очистка всех соединений
        void clearAllConnections();
        
        // Отримання статистики з'єднань
        // Get connection statistics
        // Получение статистики соединений
        struct ConnectionStatistics {
            size_t totalConnections;        // Загальна кількість з'єднань / Total connections / Общее количество соединений
            size_t activeConnections;       // Кількість активних з'єднань / Active connections / Количество активных соединений
            size_t inactiveConnections;     // Кількість неактивних з'єднань / Inactive connections / Количество неактивных соединений
            double averageWeight;           // Середня вага з'єднань / Average connection weight / Средний вес соединений
            size_t totalUsage;              // Загальна кількість використань / Total usage / Общее количество использований
            double averageUsagePerConnection; // Середнє використання на з'єднання / Average usage per connection / Среднее использование на соединение
        };
        
        ConnectionStatistics getStatistics() const;
        
        // Оновлення статистики використання
        // Update usage statistics
        // Обновление статистики использования
        void updateUsageStatistics(int sourceNeuronId, int targetNeuronId);
        
        // Отримання з'єднань, відсортованих за вагою
        // Get connections sorted by weight
        // Получение соединений, отсортированных по весу
        std::vector<WeightedConnection> getConnectionsSortedByWeight(bool descending = true) const;
        
        // Отримання з'єднань, відсортованих за часом використання
        // Get connections sorted by usage time
        // Получение соединений, отсортированных по времени использования
        std::vector<WeightedConnection> getConnectionsSortedByUsageTime(bool descending = true) const;
        
        // Отримання з'єднань, відсортованих за кількістю використань
        // Get connections sorted by usage count
        // Получение соединений, отсортированных по количеству использований
        std::vector<WeightedConnection> getConnectionsSortedByUsageCount(bool descending = true) const;
        
    private:
        // Карта зважених з'єднань (ключ: sourceId_targetId, значення: з'єднання)
        // Map of weighted connections (key: sourceId_targetId, value: connection)
        // Карта взвешенных соединений (ключ: sourceId_targetId, значение: соединение)
        std::map<std::string, WeightedConnection> connections;
        
        // Карта вхідних з'єднань для кожного нейрона
        // Map of incoming connections for each neuron
        // Карта входящих соединений для каждого нейрона
        std::map<int, std::vector<std::string>> incomingConnections;
        
        // Карта вихідних з'єднань для кожного нейрона
        // Map of outgoing connections for each neuron
        // Карта исходящих соединений для каждого нейрона
        std::map<int, std::vector<std::string>> outgoingConnections;
        
        // Мьютекс для синхронізації
        // Mutex for synchronization
        // Мьютекс для синхронизации
        mutable std::mutex connectionsMutex;
        
        // Статистика
        // Statistics
        // Статистика
        mutable std::mutex statisticsMutex;
        ConnectionStatistics stats;
        
        // Флаг ініціалізації
        // Initialization flag
        // Флаг инициализации
        std::atomic<bool> initialized;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        std::string generateConnectionKey(int sourceNeuronId, int targetNeuronId) const;
        long long getCurrentTimeMillis() const;
        void updateConnectionStatistics(const WeightedConnection& connection);
        void removeConnectionFromMaps(int sourceNeuronId, int targetNeuronId);
    };

} // namespace Utils
} // namespace Synapse
} // namespace NeuroSync

#endif // WEIGHTED_CONNECTION_MANAGER_H