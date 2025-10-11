/*
 * distributed_computing_example.cpp
 * Приклад використання розподілених обчислень
 * Example of using distributed computing
 * Пример использования распределенных вычислений
 */

#include "../distributed_computing/DistributedComputing.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using namespace NeuroSync::Distributed;

// Реалізація спостерігача для відображення статистики кластера
// Observer implementation for displaying cluster statistics
// Реализация наблюдателя для отображения статистики кластера
class ClusterObserverExample : public ClusterObserver {
public:
    void onNodeStatusChanged(const NodeInfo& node, NodeStatus oldStatus, NodeStatus newStatus) override {
        std::cout << "[CLUSTER] Node " << node.nodeId << " status changed from " 
                  << static_cast<int>(oldStatus) << " to " << static_cast<int>(newStatus) << std::endl;
    }
    
    void onTaskSubmitted(const DistributedTask& task) override {
        std::cout << "[CLUSTER] Task submitted: " << task.taskId << std::endl;
    }
    
    void onTaskCompleted(const DistributedTask& task) override {
        std::cout << "[CLUSTER] Task completed: " << task.taskId << std::endl;
        std::cout << "  Result: " << task.result << std::endl;
        std::cout << "  Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>(
            task.completedAt - task.createdAt).count() << " ms" << std::endl;
    }
    
    void onTaskFailed(const DistributedTask& task, const std::string& error) override {
        std::cout << "[CLUSTER] Task failed: " << task.taskId << std::endl;
        std::cout << "  Error: " << error << std::endl;
    }
    
    void onClusterStatsUpdated(const ClusterStats& stats) override {
        std::cout << "[CLUSTER] Statistics updated:" << std::endl;
        std::cout << "  Total Nodes: " << stats.totalNodes << std::endl;
        std::cout << "  Online Nodes: " << stats.onlineNodes << std::endl;
        std::cout << "  Busy Nodes: " << stats.busyNodes << std::endl;
        std::cout << "  Total Tasks: " << stats.totalTasks << std::endl;
        std::cout << "  Completed Tasks: " << stats.completedTasks << std::endl;
        std::cout << "  Failed Tasks: " << stats.failedTasks << std::endl;
        std::cout << "  Average Task Time: " << stats.averageTaskTime << " ms" << std::endl;
        std::cout << std::endl;
    }
};

// Симуляція обчислювального завдання
// Computational task simulation
// Симуляция вычислительного задания
std::string simulateComputationalTask(const std::string& taskData) {
    // Імітація обчислень
    // Simulate computations
    // Имитация вычислений
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100, 1000); // 100-1000 мс / 100-1000 ms / 100-1000 мс
    
    int delay = dis(gen);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    
    return "Processed: " + taskData + " (delay: " + std::to_string(delay) + " ms)";
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  NeuroSync Distributed Computing Example" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        // 1. Створення менеджера розподілених обчислень
        // 1. Creating distributed computing manager
        // 1. Создание менеджера распределенных вычислений
        std::cout << "\n1. Creating Distributed Computing Manager..." << std::endl;
        
        DistributedManager manager;
        
        // 2. Налаштування конфігурації
        // 2. Setting up configuration
        // 2. Настройка конфигурации
        std::cout << "\n2. Setting up configuration..." << std::endl;
        
        DistributedConfig config;
        config.clusterName = "ExampleCluster";
        config.masterPort = 8080;
        config.masterAddress = "localhost";
        config.workerPort = 8081;
        config.maxWorkers = 5;
        config.heartbeatInterval = 3000; // 3 секунди / 3 seconds / 3 секунды
        config.taskTimeout = 30000; // 30 секунд / 30 seconds / 30 секунд
        config.enableEncryption = false;
        config.maxRetries = 3;
        config.enableLoadBalancing = true;
        
        // 3. Ініціалізація менеджера
        // 3. Initializing manager
        // 3. Инициализация менеджера
        std::cout << "\n3. Initializing manager..." << std::endl;
        
        if (!manager.initialize(config)) {
            std::cerr << "Failed to initialize Distributed Manager" << std::endl;
            return 1;
        }
        
        std::cout << "Distributed Manager initialized successfully!" << std::endl;
        
        // 4. Додавання спостерігача
        // 4. Adding observer
        // 4. Добавление наблюдателя
        std::cout << "\n4. Adding cluster observer..." << std::endl;
        
        auto observer = std::make_shared<ClusterObserverExample>();
        manager.addObserver(observer);
        
        std::cout << "Cluster observer added!" << std::endl;
        
        // 5. Запуск головного вузла
        // 5. Starting master node
        // 5. Запуск главного узла
        std::cout << "\n5. Starting master node..." << std::endl;
        
        if (!manager.startMasterNode()) {
            std::cerr << "Failed to start master node" << std::endl;
            return 1;
        }
        
        std::cout << "Master node started successfully!" << std::endl;
        
        // 6. Запуск робочих вузлів
        // 6. Starting worker nodes
        // 6. Запуск рабочих узлов
        std::cout << "\n6. Starting worker nodes..." << std::endl;
        
        // Для демонстрації створимо додаткові менеджери як робочі вузли
        // For demonstration, create additional managers as worker nodes
        // Для демонстрации создадим дополнительные менеджеры как рабочие узлы
        std::vector<std::unique_ptr<DistributedManager>> workerManagers;
        
        for (int i = 0; i < 2; ++i) {
            auto workerManager = std::make_unique<DistributedManager>();
            DistributedConfig workerConfig = config;
            workerConfig.workerPort = 8082 + i; // Різні порти для робочих вузлів / Different ports for worker nodes / Разные порты для рабочих узлов
            
            if (workerManager->initialize(workerConfig)) {
                if (workerManager->startWorkerNode()) {
                    workerManagers.push_back(std::move(workerManager));
                    std::cout << "Worker node " << i << " started successfully!" << std::endl;
                } else {
                    std::cerr << "Failed to start worker node " << i << std::endl;
                }
            } else {
                std::cerr << "Failed to initialize worker node " << i << std::endl;
            }
        }
        
        // 7. Очікування ініціалізації вузлів
        // 7. Waiting for node initialization
        // 7. Ожидание инициализации узлов
        std::cout << "\n7. Waiting for nodes to initialize..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // 8. Відображення інформації про вузли
        // 8. Displaying node information
        // 8. Отображение информации об узлах
        std::cout << "\n8. Displaying node information..." << std::endl;
        
        auto nodes = manager.getAllNodes();
        std::cout << "Cluster nodes:" << std::endl;
        for (const auto& node : nodes) {
            std::cout << "  Node ID: " << node.nodeId << std::endl;
            std::cout << "  Address: " << node.address << ":" << node.port << std::endl;
            std::cout << "  Type: " << static_cast<int>(node.type) << std::endl;
            std::cout << "  Status: " << static_cast<int>(node.status) << std::endl;
            std::cout << "  CPU Cores: " << node.cpuCores << std::endl;
            std::cout << "  Memory: " << (node.memory / (1024 * 1024)) << " MB" << std::endl;
            std::cout << "  Active Tasks: " << node.activeTasks << std::endl;
            std::cout << std::endl;
        }
        
        // 9. Надсилання завдань
        // 9. Submitting tasks
        // 9. Отправка заданий
        std::cout << "\n9. Submitting computational tasks..." << std::endl;
        
        std::vector<std::string> taskIds;
        
        // Надсилання кількох завдань
        // Submitting multiple tasks
        // Отправка нескольких заданий
        for (int i = 0; i < 5; ++i) {
            std::string taskData = "TaskData_" + std::to_string(i);
            std::string taskId = manager.submitTask(taskData);
            taskIds.push_back(taskId);
            std::cout << "Submitted task " << i << " with ID: " << taskId << std::endl;
        }
        
        // 10. Очікування завершення завдань
        // 10. Waiting for task completion
        // 10. Ожидание завершения заданий
        std::cout << "\n10. Waiting for tasks to complete..." << std::endl;
        
        bool allCompleted = false;
        int waitCount = 0;
        const int maxWaitCount = 20; // Максимум 20 ітерацій / Maximum 20 iterations / Максимум 20 итераций
        
        while (!allCompleted && waitCount < maxWaitCount) {
            allCompleted = true;
            
            for (const auto& taskId : taskIds) {
                if (!manager.isTaskCompleted(taskId)) {
                    allCompleted = false;
                    break;
                }
            }
            
            if (!allCompleted) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                waitCount++;
            }
        }
        
        // 11. Отримання результатів завдань
        // 11. Getting task results
        // 11. Получение результатов заданий
        std::cout << "\n11. Getting task results..." << std::endl;
        
        for (const auto& taskId : taskIds) {
            std::string result = manager.getTaskResult(taskId);
            std::cout << "Task " << taskId << " result: " << result << std::endl;
        }
        
        // 12. Відображення статистики кластера
        // 12. Displaying cluster statistics
        // 12. Отображение статистики кластера
        std::cout << "\n12. Displaying final cluster statistics..." << std::endl;
        
        ClusterStats stats = manager.getClusterStats();
        std::cout << "Final Cluster Statistics:" << std::endl;
        std::cout << "  Total Nodes: " << stats.totalNodes << std::endl;
        std::cout << "  Online Nodes: " << stats.onlineNodes << std::endl;
        std::cout << "  Busy Nodes: " << stats.busyNodes << std::endl;
        std::cout << "  Total Tasks: " << stats.totalTasks << std::endl;
        std::cout << "  Completed Tasks: " << stats.completedTasks << std::endl;
        std::cout << "  Failed Tasks: " << stats.failedTasks << std::endl;
        std::cout << "  Average Task Time: " << stats.averageTaskTime << " ms" << std::endl;
        
        // 13. Зупинка вузлів
        // 13. Stopping nodes
        // 13. Остановка узлов
        std::cout << "\n13. Stopping nodes..." << std::endl;
        
        // Зупинка робочих вузлів
        // Stopping worker nodes
        // Остановка рабочих узлов
        for (auto& workerManager : workerManagers) {
            workerManager->stopNode();
        }
        
        // Зупинка головного вузла
        // Stopping master node
        // Остановка главного узла
        manager.stopNode();
        
        std::cout << "All nodes stopped successfully!" << std::endl;
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Distributed Computing Example Completed!" << std::endl;
        std::cout << "========================================" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}