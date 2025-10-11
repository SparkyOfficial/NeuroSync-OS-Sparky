#include "DistributedComputing.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <iomanip>

// DistributedManager.cpp
// Реалізація менеджера розподілених обчислень для NeuroSync OS Sparky
// Implementation of distributed computing manager for NeuroSync OS Sparky
// Реализация менеджера распределенных вычислений для NeuroSync OS Sparky

namespace NeuroSync {
namespace Distributed {

    // Конструктор менеджера розподілених обчислень
    // Distributed manager constructor
    // Конструктор менеджера распределенных вычислений
    DistributedManager::DistributedManager() 
        : isRunning(false), nodeType(NodeType::WORKER) {
        // Ініціалізація компонентів
        // Initialize components
        // Инициализация компонентов
    }

    // Деструктор менеджера розподілених обчислень
    // Distributed manager destructor
    // Деструктор менеджера распределенных вычислений
    DistributedManager::~DistributedManager() {
        stopNode();
        
        if (heartbeatThread.joinable()) {
            heartbeatThread.join();
        }
        
        if (taskProcessorThread.joinable()) {
            taskProcessorThread.join();
        }
    }

    // Ініціалізація менеджера
    // Initialize manager
    // Инициализация менеджера
    bool DistributedManager::initialize(const DistributedConfig& config) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        configuration = config;
        
        // Ініціалізація компонентів
        // Initialize components
        // Инициализация компонентов
        networkManager = std::make_unique<Network::NetworkManager>();
        scheduler = std::make_unique<Core::Scheduler>();
        threadPool = std::make_unique<NeuroSync::ThreadPool>(4); // 4 потоки за замовчуванням / 4 threads by default / 4 потока по умолчанию
        
        if (configuration.enableEncryption) {
            securityManager = std::make_unique<Security::SecurityManager>();
        }
        
        // Ініціалізація компонентів
        // Initialize components
        // Инициализация компонентов
        if (networkManager) {
            NeuroSync::NetworkConfig netConfig;  // Fixed: Use correct namespace
            netConfig.port = static_cast<uint16_t>(configuration.workerPort);  // Fixed: Cast to uint16_t
            netConfig.maxConnections = configuration.maxWorkers;
            networkManager->initialize(netConfig);
        }
        
        if (scheduler) {
            scheduler->initialize();
        }
        
        if (threadPool) {
            threadPool->initialize();
        }
        
        if (securityManager && configuration.enableEncryption) {
            securityManager->initialize();
        }
        
        // Генерація ID локального вузла
        // Generate local node ID
        // Генерация ID локального узла
        localNodeId = generateNodeId();
        
        return true;
    }

    // Додати спостерігача
    // Add observer
    // Добавить наблюдателя
    void DistributedManager::addObserver(std::shared_ptr<ClusterObserver> observer) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        if (observer) {
            observers.push_back(observer);
        }
    }

    // Видалити спостерігача
    // Remove observer
    // Удалить наблюдателя
    void DistributedManager::removeObserver(std::shared_ptr<ClusterObserver> observer) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        if (observer) {
            observers.erase(
                std::remove(observers.begin(), observers.end(), observer), 
                observers.end()
            );
        }
    }

    // Запустити головний вузол
    // Start master node
    // Запустить главный узел
    bool DistributedManager::startMasterNode() {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        if (isRunning) {
            return false;
        }
        
        nodeType = NodeType::MASTER;
        isRunning = true;
        
        // Запуск мережевого менеджера
        // Start network manager
        // Запуск сетевого менеджера
        if (networkManager) {
            NeuroSync::NetworkConfig netConfig;  // Fixed: Use correct namespace
            netConfig.port = static_cast<uint16_t>(configuration.masterPort);  // Fixed: Cast to uint16_t
            netConfig.maxConnections = configuration.maxWorkers;
            networkManager->initialize(netConfig);
            networkManager->startServer();
        }
        
        // Запуск потоку серцебитів
        // Start heartbeat thread
        // Запуск потока сердцебиений
        heartbeatThread = std::thread(&DistributedManager::heartbeatLoop, this);
        
        // Запуск потоку обробки завдань
        // Start task processor thread
        // Запуск потока обработки заданий
        taskProcessorThread = std::thread(&DistributedManager::taskProcessorLoop, this);
        
        // Додавання локального вузла до кластера
        // Add local node to cluster
        // Добавление локального узла в кластер
        NodeInfo masterNode;
        masterNode.nodeId = localNodeId;
        masterNode.address = configuration.masterAddress;
        masterNode.port = configuration.masterPort;
        masterNode.type = NodeType::MASTER;
        masterNode.status = NodeStatus::ONLINE;
        masterNode.cpuCores = std::thread::hardware_concurrency();
        masterNode.memory = 1024 * 1024 * 1024; // 1 GB для демонстрації / 1 GB for demonstration / 1 ГБ для демонстрации
        masterNode.activeTasks = 0;
        masterNode.lastHeartbeat = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        
        nodes[localNodeId] = masterNode;
        
        std::cout << "[DISTRIBUTED] Master node started with ID: " << localNodeId << std::endl;
        
        return true;
    }

    // Запустити робочий вузол
    // Start worker node
    // Запустить рабочий узел
    bool DistributedManager::startWorkerNode() {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        if (isRunning) {
            return false;
        }
        
        nodeType = NodeType::WORKER;
        isRunning = true;
        
        // Запуск мережевого менеджера
        // Start network manager
        // Запуск сетевого менеджера
        if (networkManager) {
            NeuroSync::NetworkConfig netConfig;  // Fixed: Use correct namespace
            netConfig.port = static_cast<uint16_t>(configuration.workerPort);  // Fixed: Cast to uint16_t
            netConfig.maxConnections = 10; // Обмеження для робочого вузла / Limit for worker node / Ограничение для рабочего узла
            networkManager->initialize(netConfig);
        }
        
        // Запуск потоку серцебитів
        // Start heartbeat thread
        // Запуск потока сердцебиений
        heartbeatThread = std::thread(&DistributedManager::heartbeatLoop, this);
        
        // Запуск потоку обробки завдань
        // Start task processor thread
        // Запуск потока обработки заданий
        taskProcessorThread = std::thread(&DistributedManager::taskProcessorLoop, this);
        
        // Підключення до головного вузла
        // Connect to master node
        // Подключение к главному узлу
        if (networkManager) {
            networkManager->connectToServer(configuration.masterAddress, static_cast<uint16_t>(configuration.masterPort));  // Fixed: Cast to uint16_t
        }
        
        // Додавання локального вузла до кластера
        // Add local node to cluster
        // Добавление локального узла в кластер
        NodeInfo workerNode;
        workerNode.nodeId = localNodeId;
        workerNode.address = "localhost"; // Для демонстрації / For demonstration / Для демонстрации
        workerNode.port = configuration.workerPort;
        workerNode.type = NodeType::WORKER;
        workerNode.status = NodeStatus::ONLINE;
        workerNode.cpuCores = std::thread::hardware_concurrency();
        workerNode.memory = 512 * 1024 * 1024; // 512 MB для демонстрації / 512 MB for demonstration / 512 МБ для демонстрации
        workerNode.activeTasks = 0;
        workerNode.lastHeartbeat = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        
        nodes[localNodeId] = workerNode;
        
        std::cout << "[DISTRIBUTED] Worker node started with ID: " << localNodeId << std::endl;
        
        return true;
    }

    // Зупинити вузол
    // Stop node
    // Остановить узел
    void DistributedManager::stopNode() {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        isRunning = false;
        
        // Зупинка мережевого менеджера
        // Stop network manager
        // Остановка сетевого менеджера
        if (networkManager) {
            networkManager->stopServer();
        }
        
        // Оновлення статусу локального вузла
        // Update local node status
        // Обновление статуса локального узла
        auto it = nodes.find(localNodeId);
        if (it != nodes.end()) {
            NodeStatus oldStatus = it->second.status;
            it->second.status = NodeStatus::OFFLINE;
            it->second.lastHeartbeat = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
            
            notifyNodeStatusChanged(it->second, oldStatus, NodeStatus::OFFLINE);
        }
        
        std::cout << "[DISTRIBUTED] Node stopped" << std::endl;
    }

    // Додати вузол до кластера
    // Add node to cluster
    // Добавить узел в кластер
    bool DistributedManager::addNode(const NodeInfo& node) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        // Перевірка, чи вузол вже існує
        // Check if node already exists
        // Проверка, существует ли узел уже
        if (nodes.find(node.nodeId) != nodes.end()) {
            return false;
        }
        
        nodes[node.nodeId] = node;
        
        std::cout << "[DISTRIBUTED] Node added to cluster: " << node.nodeId << std::endl;
        
        return true;
    }

    // Видалити вузол з кластера
    // Remove node from cluster
    // Удалить узел из кластера
    bool DistributedManager::removeNode(const std::string& nodeId) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        auto it = nodes.find(nodeId);
        if (it == nodes.end()) {
            return false;
        }
        
        NodeStatus oldStatus = it->second.status;
        nodes.erase(it);
        
        // Сповіщення про зміну статусу
        // Notify about status change
        // Уведомление об изменении статуса
        NodeInfo removedNode;
        removedNode.nodeId = nodeId;
        removedNode.status = NodeStatus::OFFLINE;
        notifyNodeStatusChanged(removedNode, oldStatus, NodeStatus::OFFLINE);
        
        std::cout << "[DISTRIBUTED] Node removed from cluster: " << nodeId << std::endl;
        
        return true;
    }

    // Надіслати завдання
    // Submit task
    // Отправить задание
    std::string DistributedManager::submitTask(const std::string& taskData) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        // Генерація ID завдання
        // Generate task ID
        // Генерация ID задания
        std::string taskId = generateTaskId();
        
        // Створення завдання
        // Create task
        // Создание задания
        DistributedTask task;
        task.taskId = taskId;
        task.taskData = taskData;
        task.createdAt = std::chrono::steady_clock::now();
        task.completed = false;
        task.failed = false;
        
        // Додавання завдання до списку
        // Add task to list
        // Добавление задания в список
        tasks[taskId] = task;
        
        // Надсилання завдання до найкращого вузла
        // Send task to best node
        // Отправка задания на лучший узел
        NodeInfo bestNode = getBestNodeForTask();
        if (!bestNode.nodeId.empty() && networkManager) {
            // Надсилання завдання через мережу
            // Send task through network
            // Отправка задания через сеть
            std::string message = "TASK:" + taskId + ":" + taskData;
            networkManager->sendMessage(bestNode.nodeId, message);
            
            // Оновлення інформації про вузол
            // Update node information
            // Обновление информации об узле
            auto it = nodes.find(bestNode.nodeId);
            if (it != nodes.end()) {
                it->second.activeTasks++;
            }
        }
        
        // Сповіщення про нове завдання
        // Notify about new task
        // Уведомление о новом задании
        notifyTaskSubmitted(task);
        
        std::cout << "[DISTRIBUTED] Task submitted with ID: " << taskId << std::endl;
        
        return taskId;
    }

    // Отримати результат завдання
    // Get task result
    // Получить результат задания
    std::string DistributedManager::getTaskResult(const std::string& taskId) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        auto it = tasks.find(taskId);
        if (it == tasks.end()) {
            return "";
        }
        
        return it->second.result;
    }

    // Перевірити статус завдання
    // Check task status
    // Проверить статус задания
    bool DistributedManager::isTaskCompleted(const std::string& taskId) {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        auto it = tasks.find(taskId);
        if (it == tasks.end()) {
            return false;
        }
        
        return it->second.completed;
    }

    // Отримати інформацію про вузол
    // Get node information
    // Получить информацию об узле
    NodeInfo DistributedManager::getNodeInfo(const std::string& nodeId) const {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        auto it = nodes.find(nodeId);
        if (it != nodes.end()) {
            return it->second;
        }
        
        return NodeInfo(); // Повертає порожню інформацію / Returns empty information / Возвращает пустую информацию
    }

    // Отримати список всіх вузлів
    // Get all nodes
    // Получить список всех узлов
    std::vector<NodeInfo> DistributedManager::getAllNodes() const {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        std::vector<NodeInfo> nodeList;
        nodeList.reserve(nodes.size());
        
        for (const auto& pair : nodes) {
            nodeList.push_back(pair.second);
        }
        
        return nodeList;
    }

    // Отримати статистику кластера
    // Get cluster statistics
    // Получить статистику кластера
    ClusterStats DistributedManager::getClusterStats() const {
        std::lock_guard<std::mutex> lock(managerMutex);
        return calculateClusterStats();
    }

    // Отримати конфігурацію
    // Get configuration
    // Получить конфигурацию
    DistributedConfig DistributedManager::getConfiguration() const {
        std::lock_guard<std::mutex> lock(managerMutex);
        return configuration;
    }

    // Встановити адресу головного вузла
    // Set master address
    // Установить адрес главного узла
    void DistributedManager::setMasterAddress(const std::string& address) {
        std::lock_guard<std::mutex> lock(managerMutex);
        configuration.masterAddress = address;
    }

    // Встановити порт головного вузла
    // Set master port
    // Установить порт главного узла
    void DistributedManager::setMasterPort(int port) {
        std::lock_guard<std::mutex> lock(managerMutex);
        configuration.masterPort = port;
    }

    // Перевірити з'єднання з кластером
    // Check cluster connection
    // Проверить соединение с кластером
    bool DistributedManager::isConnected() const {
        std::lock_guard<std::mutex> lock(managerMutex);
        
        // У реальній реалізації тут би була перевірка з'єднання
        // In real implementation, there would be connection check
        // В реальной реализации здесь была бы проверка соединения
        
        // Для демонстрації повертаємо true, якщо мережевий менеджер ініціалізований
        // For demonstration, return true if network manager is initialized
        // Для демонстрации возвращаем true, если сетевой менеджер инициализирован
        return networkManager != nullptr;
    }

    // Цикл серцебитів
    // Heartbeat loop
    // Цикл сердцебиений
    void DistributedManager::heartbeatLoop() {
        while (isRunning) {
            // Надсилання серцебиту
            // Send heartbeat
            // Отправка сердцебиения
            sendHeartbeat();
            
            // Очікування перед наступним серцебитом
            // Wait before next heartbeat
            // Ожидание перед следующим сердцебиением
            std::this_thread::sleep_for(std::chrono::milliseconds(configuration.heartbeatInterval));
        }
    }

    // Цикл обробки завдань
    // Task processor loop
    // Цикл обработки заданий
    void DistributedManager::taskProcessorLoop() {
        while (isRunning) {
            // Обробка вхідних завдань
            // Process incoming tasks
            // Обработка входящих заданий
            processIncomingTasks();
            
            // Оновлення статистики кластера
            // Update cluster statistics
            // Обновление статистики кластера
            updateClusterStats();
            
            // Очікування перед наступною ітерацією
            // Wait before next iteration
            // Ожидание перед следующей итерацией
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1 секунда / 1 second / 1 секунда
        }
    }

    // Надсилання серцебиту
    // Send heartbeat
    // Отправка сердцебиения
    void DistributedManager::sendHeartbeat() {
        if (!networkManager) {
            return;
        }
        
        // Оновлення інформації про локальний вузол
        // Update local node information
        // Обновление информации о локальном узле
        auto it = nodes.find(localNodeId);
        if (it != nodes.end()) {
            it->second.lastHeartbeat = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
            
            // Надсилання серцебиту через мережу
            // Send heartbeat through network
            // Отправка сердцебиения через сеть
            std::string message = "HEARTBEAT:" + localNodeId;
            if (nodeType == NodeType::MASTER) {
                // Головний вузол надсилає серцебити всім вузлам
                // Master node sends heartbeats to all nodes
                // Главный узел отправляет сердцебиения всем узлам
                for (const auto& pair : nodes) {
                    if (pair.first != localNodeId) {
                        networkManager->sendMessage(pair.first, message);
                    }
                }
            } else {
                // Робочий вузол надсилає серцебит головному вузлу
                // Worker node sends heartbeat to master node
                // Рабочий узел отправляет сердцебиение главному узлу
                networkManager->sendMessage(configuration.masterAddress, message);
            }
        }
    }

    // Обробка вхідних завдань
    // Process incoming tasks
    // Обработка входящих заданий
    void DistributedManager::processIncomingTasks() {
        if (!networkManager) {
            return;
        }
        
        // У реальній реалізації тут би була обробка вхідних повідомлень
        // In real implementation, there would be processing of incoming messages
        // В реальной реализации здесь была бы обработка входящих сообщений
        
        // Для демонстрації імітуємо обробку завдань
        // For demonstration, simulate task processing
        // Для демонстрации имитируем обработку заданий
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(100, 1000); // 100-1000 мс / 100-1000 ms / 100-1000 мс
        
        for (auto& pair : tasks) {
            DistributedTask& task = pair.second;
            if (!task.completed && !task.failed) {
                // Імітація обробки завдання
                // Simulate task processing
                // Имитация обработки задания
                std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
                
                // Позначення завдання як завершеного
                // Mark task as completed
                // Пометка задания как завершенного
                task.completed = true;
                task.completedAt = std::chrono::steady_clock::now();
                task.result = "Task " + task.taskId + " completed successfully";
                
                // Сповіщення про завершення завдання
                // Notify about task completion
                // Уведомление о завершении задания
                notifyTaskCompleted(task);
                
                // Оновлення інформації про вузол
                // Update node information
                // Обновление информации об узле
                auto nodeIt = nodes.find(localNodeId);
                if (nodeIt != nodes.end()) {
                    nodeIt->second.activeTasks = std::max(0, nodeIt->second.activeTasks - 1);
                }
                
                std::cout << "[DISTRIBUTED] Task processed: " << task.taskId << std::endl;
                break; // Обробляємо одне завдання за ітерацію / Process one task per iteration / Обрабатываем одно задание за итерацию
            }
        }
    }

    // Сповіщення про зміну статусу вузла
    // Notify about node status change
    // Уведомление об изменении статуса узла
    void DistributedManager::notifyNodeStatusChanged(const NodeInfo& node, NodeStatus oldStatus, NodeStatus newStatus) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        managerMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onNodeStatusChanged(node, oldStatus, newStatus);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        managerMutex.lock();
    }

    // Сповіщення про нове завдання
    // Notify about new task
    // Уведомление о новом задании
    void DistributedManager::notifyTaskSubmitted(const DistributedTask& task) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        managerMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onTaskSubmitted(task);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        managerMutex.lock();
    }

    // Сповіщення про завершення завдання
    // Notify about task completion
    // Уведомление о завершении задания
    void DistributedManager::notifyTaskCompleted(const DistributedTask& task) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        managerMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onTaskCompleted(task);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        managerMutex.lock();
    }

    // Сповіщення про помилку завдання
    // Notify about task error
    // Уведомление об ошибке задания
    void DistributedManager::notifyTaskFailed(const DistributedTask& task, const std::string& error) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        managerMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onTaskFailed(task, error);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        managerMutex.lock();
    }

    // Сповіщення про статистику кластера
    // Notify about cluster statistics
    // Уведомление о статистике кластера
    void DistributedManager::notifyClusterStatsUpdated(const ClusterStats& stats) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        managerMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onClusterStatsUpdated(stats);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        managerMutex.lock();
    }

    // Генерація ID вузла
    // Generate node ID
    // Генерация ID узла
    std::string DistributedManager::generateNodeId() {
        // Генерація випадкового ID
        // Generate random ID
        // Генерация случайного ID
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100000, 999999);
        
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        
        return "node_" + std::to_string(dis(gen)) + "_" + std::to_string(timestamp % 1000000);
    }

    // Генерація ID завдання
    // Generate task ID
    // Генерация ID задания
    std::string DistributedManager::generateTaskId() {
        // Генерація випадкового ID
        // Generate random ID
        // Генерация случайного ID
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100000, 999999);
        
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        
        return "task_" + std::to_string(dis(gen)) + "_" + std::to_string(timestamp % 1000000);
    }

    // Отримання найкращого вузла для завдання
    // Get best node for task
    // Получение лучшего узла для задания
    NodeInfo DistributedManager::getBestNodeForTask() {
        NodeInfo bestNode;
        int minActiveTasks = std::numeric_limits<int>::max();
        
        // Пошук вузла з мінімальною кількістю активних завдань
        // Find node with minimum active tasks
        // Поиск узла с минимальным количеством активных заданий
        for (const auto& pair : nodes) {
            const NodeInfo& node = pair.second;
            if (node.status == NodeStatus::ONLINE && node.activeTasks < minActiveTasks) {
                minActiveTasks = node.activeTasks;
                bestNode = node;
            }
        }
        
        return bestNode;
    }

    // Оновлення статистики кластера
    // Update cluster statistics
    // Обновление статистики кластера
    void DistributedManager::updateClusterStats() {
        ClusterStats stats = calculateClusterStats();
        notifyClusterStatsUpdated(stats);
    }

    // Обчислення статистики кластера
    // Calculate cluster statistics
    // Вычисление статистики кластера
    ClusterStats DistributedManager::calculateClusterStats() const {
        ClusterStats stats;
        
        // Обчислення статистики вузлів
        // Calculate node statistics
        // Вычисление статистики узлов
        for (const auto& pair : nodes) {
            const NodeInfo& node = pair.second;
            stats.totalNodes++;
            
            switch (node.status) {
                case NodeStatus::ONLINE:
                    stats.onlineNodes++;
                    break;
                case NodeStatus::BUSY:
                    stats.busyNodes++;
                    break;
                default:
                    break;
            }
            
            stats.totalMemory += node.memory;
            stats.totalCpuCores += node.cpuCores;
        }
        
        // Обчислення статистики завдань
        // Calculate task statistics
        // Вычисление статистики заданий
        for (const auto& pair : tasks) {
            const DistributedTask& task = pair.second;
            stats.totalTasks++;
            
            if (task.completed) {
                stats.completedTasks++;
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                    task.completedAt - task.createdAt).count();
                stats.averageTaskTime += duration;
            } else if (task.failed) {
                stats.failedTasks++;
            }
        }
        
        // Обчислення середнього часу виконання
        // Calculate average task time
        // Вычисление среднего времени выполнения
        if (stats.completedTasks > 0) {
            stats.averageTaskTime /= stats.completedTasks;
        }
        
        stats.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        
        return stats;
    }

    // Шифрування даних
    // Encrypt data
    // Шифрование данных
    bool DistributedManager::encryptData(const std::string& data, std::string& encryptedData) {
        if (!securityManager || !configuration.enableEncryption) {
            encryptedData = data; // Без шифрування / Without encryption / Без шифрования
            return true;
        }
        
        // У реальній реалізації тут би було шифрування
        // In real implementation, there would be encryption
        // В реальной реализации здесь было бы шифрование
        
        // Для демонстрації просто додаємо префікс
        // For demonstration, just add a prefix
        // Для демонстрации просто добавляем префикс
        encryptedData = "[ENCRYPTED]" + data;
        return true;
    }

    // Розшифрування даних
    // Decrypt data
    // Расшифровка данных
    bool DistributedManager::decryptData(const std::string& encryptedData, std::string& data) {
        if (!securityManager || !configuration.enableEncryption) {
            data = encryptedData; // Без шифрування / Without encryption / Без шифрования
            return true;
        }
        
        // У реальній реалізації тут би було розшифрування
        // In real implementation, there would be decryption
        // В реальной реализации здесь было бы расшифрование
        
        // Для демонстрації просто видаляємо префікс
        // For demonstration, just remove the prefix
        // Для демонстрации просто удаляем префикс
        if (encryptedData.substr(0, 11) == "[ENCRYPTED]") {
            data = encryptedData.substr(11);
        } else {
            data = encryptedData;
        }
        
        return true;
    }

    // Обробка повідомлення від вузла
    // Handle node message
    // Обработка сообщения от узла
    void DistributedManager::handleNodeMessage(const std::string& nodeId, const std::string& message) {
        // У реальній реалізації тут би була обробка повідомлень від вузлів
        // In real implementation, there would be processing of messages from nodes
        // В реальной реализации здесь была бы обработка сообщений от узлов
        
        std::cout << "[DISTRIBUTED] Received message from node " << nodeId << ": " << message << std::endl;
    }

    // Обробка повідомлення про завдання
    // Handle task message
    // Обработка сообщения о задании
    void DistributedManager::handleTaskMessage(const std::string& taskId, const std::string& message) {
        // У реальній реалізації тут би була обробка повідомлень про завдання
        // In real implementation, there would be processing of task messages
        // В реальной реализации здесь была бы обработка сообщений о заданиях
        
        std::cout << "[DISTRIBUTED] Received task message for task " << taskId << ": " << message << std::endl;
    }

} // namespace Distributed
} // namespace NeuroSync