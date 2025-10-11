#ifndef DISTRIBUTED_COMPUTING_H
#define DISTRIBUTED_COMPUTING_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include "../network/NetworkManager.h"
#include "../core/Scheduler.h"
#include "../threadpool/ThreadPool.h"
#include "../security/SecurityManager.h"

// DistributedComputing.h
// Розподілені обчислення для NeuroSync OS Sparky
// Distributed computing for NeuroSync OS Sparky
// Распределенные вычисления для NeuroSync OS Sparky

namespace NeuroSync {
// Forward declaration
class ThreadPool;

namespace Distributed {

    // Статус вузла
    // Node status
    // Статус узла
    enum class NodeStatus {
        OFFLINE,        // Офлайн / Offline / Офлайн
        ONLINE,         // Онлайн / Online / Онлайн
        BUSY,           // Зайнятий / Busy / Занят
        MAINTENANCE,    // Обслуговування / Maintenance / Обслуживание
        ERROR           // Помилка / Error / Ошибка
    };

    // Тип вузла
    // Node type
    // Тип узла
    enum class NodeType {
        MASTER,         // Головний вузол / Master node / Главный узел
        WORKER,         // Робочий вузол / Worker node / Рабочий узел
        COORDINATOR     // Координатор / Coordinator / Координатор
    };

    // Конфігурація розподіленої системи
    // Distributed system configuration
    // Конфигурация распределенной системы
    struct DistributedConfig {
        std::string clusterName;                    // Ім'я кластера / Cluster name / Имя кластера
        int masterPort;                            // Порт головного вузла / Master port / Порт главного узла
        std::string masterAddress;                 // Адреса головного вузла / Master address / Адрес главного узла
        int workerPort;                            // Порт робочих вузлів / Worker port / Порт рабочих узлов
        int maxWorkers;                            // Максимальна кількість робочих вузлів / Max worker nodes / Максимальное количество рабочих узлов
        int heartbeatInterval;                     // Інтервал серцебитів (мс) / Heartbeat interval (ms) / Интервал сердцебиений (мс)
        int taskTimeout;                           // Таймаут завдання (мс) / Task timeout (ms) / Таймаут задания (мс)
        bool enableEncryption;                     // Увімкнути шифрування / Enable encryption / Включить шифрование
        std::string encryptionKey;                 // Ключ шифрування / Encryption key / Ключ шифрования
        int maxRetries;                            // Максимальна кількість спроб / Max retries / Максимальное количество попыток
        bool enableLoadBalancing;                  // Увімкнути балансування навантаження / Enable load balancing / Включить балансировку нагрузки
        
        DistributedConfig() 
            : clusterName("NeuroSyncCluster"), masterPort(8080), masterAddress("localhost"),
              workerPort(8081), maxWorkers(10), heartbeatInterval(5000), taskTimeout(30000),
              enableEncryption(false), maxRetries(3), enableLoadBalancing(true) {}
    };

    // Інформація про вузол
    // Node information
    // Информация об узле
    struct NodeInfo {
        std::string nodeId;                         // ID вузла / Node ID / ID узла
        std::string address;                        // Адреса вузла / Node address / Адрес узла
        int port;                                   // Порт вузла / Node port / Порт узла
        NodeType type;                             // Тип вузла / Node type / Тип узла
        NodeStatus status;                         // Статус вузла / Node status / Статус узла
        int cpuCores;                              // Кількість ядер ЦП / CPU cores / Количество ядер ЦП
        size_t memory;                             // Обсяг пам'яті / Memory size / Объем памяти
        int activeTasks;                           // Активні завдання / Active tasks / Активные задания
        long long lastHeartbeat;                   // Останній серцебит / Last heartbeat / Последнее сердцебиение
        std::map<std::string, std::string> metadata; // Метадані / Metadata / Метаданные
        
        NodeInfo() 
            : port(0), type(NodeType::WORKER), status(NodeStatus::OFFLINE),
              cpuCores(0), memory(0), activeTasks(0), lastHeartbeat(0) {}
    };

    // Завдання для розподілених обчислень
    // Distributed computing task
    // Задание для распределенных вычислений
    struct DistributedTask {
        std::string taskId;                         // ID завдання / Task ID / ID задания
        std::string nodeId;                         // ID вузла / Node ID / ID узла
        std::string taskData;                       // Дані завдання / Task data / Данные задания
        std::string result;                         // Результат / Result / Результат
        std::chrono::steady_clock::time_point createdAt;  // Час створення / Creation time / Время создания
        std::chrono::steady_clock::time_point startedAt;  // Час початку / Start time / Время начала
        std::chrono::steady_clock::time_point completedAt; // Час завершення / Completion time / Время завершения
        bool completed;                            // Завершено / Completed / Завершено
        bool failed;                               // Помилка / Failed / Ошибка
        std::string errorMessage;                  // Повідомлення про помилку / Error message / Сообщение об ошибке
        
        DistributedTask() 
            : completed(false), failed(false) {}
    };

    // Статистика кластера
    // Cluster statistics
    // Статистика кластера
    struct ClusterStats {
        int totalNodes;                             // Загальна кількість вузлів / Total nodes / Общее количество узлов
        int onlineNodes;                            // Онлайн вузли / Online nodes / Онлайн узлы
        int busyNodes;                              // Зайняті вузли / Busy nodes / Занятые узлы
        int totalTasks;                             // Загальна кількість завдань / Total tasks / Общее количество заданий
        int completedTasks;                         // Завершені завдання / Completed tasks / Завершенные задания
        int failedTasks;                            // Невдалі завдання / Failed tasks / Неудавшиеся задания
        double averageTaskTime;                     // Середній час виконання / Average task time / Среднее время выполнения
        size_t totalMemory;                         // Загальна пам'ять / Total memory / Общая память
        int totalCpuCores;                          // Загальні ядра ЦП / Total CPU cores / Общие ядра ЦП
        long long timestamp;                        // Часова мітка / Timestamp / Временная метка
        
        ClusterStats() 
            : totalNodes(0), onlineNodes(0), busyNodes(0), totalTasks(0),
              completedTasks(0), failedTasks(0), averageTaskTime(0.0),
              totalMemory(0), totalCpuCores(0), timestamp(0) {}
    };

    // Інтерфейс спостерігача за кластером
    // Cluster observer interface
    // Интерфейс наблюдателя за кластером
    class ClusterObserver {
    public:
        virtual ~ClusterObserver() = default;
        
        // Сповіщення про зміну статусу вузла
        // Node status change notification
        // Уведомление об изменении статуса узла
        virtual void onNodeStatusChanged(const NodeInfo& node, NodeStatus oldStatus, NodeStatus newStatus) = 0;
        
        // Сповіщення про нове завдання
        // New task notification
        // Уведомление о новом задании
        virtual void onTaskSubmitted(const DistributedTask& task) = 0;
        
        // Сповіщення про завершення завдання
        // Task completion notification
        // Уведомление о завершении задания
        virtual void onTaskCompleted(const DistributedTask& task) = 0;
        
        // Сповіщення про помилку завдання
        // Task error notification
        // Уведомление об ошибке задания
        virtual void onTaskFailed(const DistributedTask& task, const std::string& error) = 0;
        
        // Сповіщення про статистику кластера
        // Cluster statistics notification
        // Уведомление о статистике кластера
        virtual void onClusterStatsUpdated(const ClusterStats& stats) = 0;
    };

    // Менеджер розподілених обчислень
    // Distributed computing manager
    // Менеджер распределенных вычислений
    class DistributedManager {
    public:
        DistributedManager();
        ~DistributedManager();
        
        // Ініціалізація менеджера
        // Initialize manager
        // Инициализация менеджера
        bool initialize(const DistributedConfig& config = DistributedConfig());
        
        // Додати спостерігача
        // Add observer
        // Добавить наблюдателя
        void addObserver(std::shared_ptr<ClusterObserver> observer);
        
        // Видалити спостерігача
        // Remove observer
        // Удалить наблюдателя
        void removeObserver(std::shared_ptr<ClusterObserver> observer);
        
        // Запустити головний вузол
        // Start master node
        // Запустить главный узел
        bool startMasterNode();
        
        // Запустити робочий вузол
        // Start worker node
        // Запустить рабочий узел
        bool startWorkerNode();
        
        // Зупинити вузол
        // Stop node
        // Остановить узел
        void stopNode();
        
        // Додати вузол до кластера
        // Add node to cluster
        // Добавить узел в кластер
        bool addNode(const NodeInfo& node);
        
        // Видалити вузол з кластера
        // Remove node from cluster
        // Удалить узел из кластера
        bool removeNode(const std::string& nodeId);
        
        // Надіслати завдання
        // Submit task
        // Отправить задание
        std::string submitTask(const std::string& taskData);
        
        // Отримати результат завдання
        // Get task result
        // Получить результат задания
        std::string getTaskResult(const std::string& taskId);
        
        // Перевірити статус завдання
        // Check task status
        // Проверить статус задания
        bool isTaskCompleted(const std::string& taskId);
        
        // Отримати інформацію про вузол
        // Get node information
        // Получить информацию об узле
        NodeInfo getNodeInfo(const std::string& nodeId) const;
        
        // Отримати список всіх вузлів
        // Get all nodes
        // Получить список всех узлов
        std::vector<NodeInfo> getAllNodes() const;
        
        // Отримати статистику кластера
        // Get cluster statistics
        // Получить статистику кластера
        ClusterStats getClusterStats() const;
        
        // Отримати конфігурацію
        // Get configuration
        // Получить конфигурацию
        DistributedConfig getConfiguration() const;
        
        // Встановити адресу головного вузла
        // Set master address
        // Установить адрес главного узла
        void setMasterAddress(const std::string& address);
        
        // Встановити порт головного вузла
        // Set master port
        // Установить порт главного узла
        void setMasterPort(int port);
        
        // Перевірити з'єднання з кластером
        // Check cluster connection
        // Проверить соединение с кластером
        bool isConnected() const;
        
    private:
        DistributedConfig configuration;                          // Конфігурація / Configuration / Конфигурация
        mutable std::mutex managerMutex;                         // М'ютекс для потокобезпеки / Mutex for thread safety / Мьютекс для потокобезопасности
        std::unique_ptr<Network::NetworkManager> networkManager;  // Менеджер мережі / Network manager / Менеджер сети
        std::unique_ptr<Core::Scheduler> scheduler;               // Планувальник / Scheduler / Планировщик
        std::unique_ptr<NeuroSync::ThreadPool> threadPool;       // Пул потоків / Thread pool / Пул потоков
        std::unique_ptr<Security::SecurityManager> securityManager; // Менеджер безпеки / Security manager / Менеджер безопасности
        std::map<std::string, NodeInfo> nodes;                    // Вузли кластера / Cluster nodes / Узлы кластера
        std::map<std::string, DistributedTask> tasks;             // Завдання / Tasks / Задания
        std::vector<std::shared_ptr<ClusterObserver>> observers;  // Спостерігачі / Observers / Наблюдатели
        std::atomic<bool> isRunning;                             // Прапор роботи / Running flag / Флаг работы
        std::atomic<NodeType> nodeType;                          // Тип вузла / Node type / Тип узла
        std::string localNodeId;                                 // ID локального вузла / Local node ID / ID локального узла
        std::thread heartbeatThread;                             // Потік серцебитів / Heartbeat thread / Поток сердцебиений
        std::thread taskProcessorThread;                         // Потік обробки завдань / Task processor thread / Поток обработки заданий
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void heartbeatLoop();
        void taskProcessorLoop();
        void sendHeartbeat();
        void processIncomingTasks();
        void notifyNodeStatusChanged(const NodeInfo& node, NodeStatus oldStatus, NodeStatus newStatus);
        void notifyTaskSubmitted(const DistributedTask& task);
        void notifyTaskCompleted(const DistributedTask& task);
        void notifyTaskFailed(const DistributedTask& task, const std::string& error);
        void notifyClusterStatsUpdated(const ClusterStats& stats);
        std::string generateNodeId();
        std::string generateTaskId();
        NodeInfo getBestNodeForTask();
        void updateClusterStats();
        ClusterStats calculateClusterStats() const;
        bool encryptData(const std::string& data, std::string& encryptedData);
        bool decryptData(const std::string& encryptedData, std::string& data);
        void handleNodeMessage(const std::string& nodeId, const std::string& message);
        void handleTaskMessage(const std::string& taskId, const std::string& message);
    };

} // namespace Distributed
} // namespace NeuroSync

#endif // DISTRIBUTED_COMPUTING_H