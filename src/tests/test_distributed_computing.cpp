/*
 * test_distributed_computing.cpp
 * Тест для розподілених обчислень
 * Test for distributed computing
 * Тест для распределенных вычислений
 */

#include "../distributed_computing/DistributedComputing.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <thread>
#include <chrono>

using namespace NeuroSync::Distributed;

// Тестова реалізація спостерігача
// Test observer implementation
// Тестовая реализация наблюдателя
class TestObserver : public ClusterObserver {
public:
    int nodeStatusChanges = 0;
    int tasksSubmitted = 0;
    int tasksCompleted = 0;
    int tasksFailed = 0;
    int statsUpdates = 0;
    
    void onNodeStatusChanged(const NodeInfo& node, NodeStatus oldStatus, NodeStatus newStatus) override {
        nodeStatusChanges++;
        std::cout << "[TEST] Node status changed: " << node.nodeId << std::endl;
    }
    
    void onTaskSubmitted(const DistributedTask& task) override {
        tasksSubmitted++;
        std::cout << "[TEST] Task submitted: " << task.taskId << std::endl;
    }
    
    void onTaskCompleted(const DistributedTask& task) override {
        tasksCompleted++;
        std::cout << "[TEST] Task completed: " << task.taskId << std::endl;
    }
    
    void onTaskFailed(const DistributedTask& task, const std::string& error) override {
        tasksFailed++;
        std::cout << "[TEST] Task failed: " << task.taskId << std::endl;
    }
    
    void onClusterStatsUpdated(const ClusterStats& stats) override {
        statsUpdates++;
        std::cout << "[TEST] Cluster stats updated" << std::endl;
    }
};

int main() {
    std::cout << "=== Running Distributed Computing Tests ===" << std::endl;
    
    try {
        // Тест 1: Створення та ініціалізація менеджера
        // Test 1: Creating and initializing manager
        // Тест 1: Создание и инициализация менеджера
        std::cout << "\nTest 1: Creating and initializing manager..." << std::endl;
        
        DistributedManager manager;
        
        DistributedConfig config;
        config.clusterName = "TestCluster";
        config.masterPort = 8090;
        config.masterAddress = "localhost";
        config.workerPort = 8091;
        config.maxWorkers = 3;
        config.heartbeatInterval = 1000; // 1 секунда для тесту / 1 second for test / 1 секунда для теста
        config.taskTimeout = 10000; // 10 секунд / 10 seconds / 10 секунд
        
        bool initSuccess = manager.initialize(config);
        assert(initSuccess);
        std::cout << "Manager initialized successfully" << std::endl;
        
        // Тест 2: Додавання спостерігача
        // Test 2: Adding observer
        // Тест 2: Добавление наблюдателя
        std::cout << "\nTest 2: Adding observer..." << std::endl;
        
        auto observer = std::make_shared<TestObserver>();
        manager.addObserver(observer);
        std::cout << "Observer added successfully" << std::endl;
        
        // Тест 3: Отримання конфігурації
        // Test 3: Getting configuration
        // Тест 3: Получение конфигурации
        std::cout << "\nTest 3: Getting configuration..." << std::endl;
        
        DistributedConfig retrievedConfig = manager.getConfiguration();
        assert(retrievedConfig.clusterName == "TestCluster");
        assert(retrievedConfig.masterPort == 8090);
        std::cout << "Configuration retrieved successfully" << std::endl;
        
        // Тест 4: Запуск головного вузла
        // Test 4: Starting master node
        // Тест 4: Запуск главного узла
        std::cout << "\nTest 4: Starting master node..." << std::endl;
        
        bool masterStarted = manager.startMasterNode();
        assert(masterStarted);
        std::cout << "Master node started successfully" << std::endl;
        
        // Тест 5: Запуск робочого вузла
        // Test 5: Starting worker node
        // Тест 5: Запуск рабочего узла
        std::cout << "\nTest 5: Starting worker node..." << std::endl;
        
        bool workerStarted = manager.startWorkerNode();
        assert(workerStarted);
        std::cout << "Worker node started successfully" << std::endl;
        
        // Тест 6: Очікування ініціалізації
        // Test 6: Waiting for initialization
        // Тест 6: Ожидание инициализации
        std::cout << "\nTest 6: Waiting for initialization..." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Тест 7: Перевірка з'єднання
        // Test 7: Checking connection
        // Тест 7: Проверка соединения
        std::cout << "\nTest 7: Checking connection..." << std::endl;
        
        bool connected = manager.isConnected();
        assert(connected);
        std::cout << "Connection check passed" << std::endl;
        
        // Тест 8: Отримання інформації про вузли
        // Test 8: Getting node information
        // Тест 8: Получение информации об узлах
        std::cout << "\nTest 8: Getting node information..." << std::endl;
        
        auto nodes = manager.getAllNodes();
        assert(!nodes.empty());
        std::cout << "Retrieved " << nodes.size() << " nodes" << std::endl;
        
        // Тест 9: Надсилання завдання
        // Test 9: Submitting task
        // Тест 9: Отправка задания
        std::cout << "\nTest 9: Submitting task..." << std::endl;
        
        std::string taskId = manager.submitTask("TestTaskData");
        assert(!taskId.empty());
        std::cout << "Task submitted with ID: " << taskId << std::endl;
        
        // Тест 10: Перевірка статусу завдання
        // Test 10: Checking task status
        // Тест 10: Проверка статуса задания
        std::cout << "\nTest 10: Checking task status..." << std::endl;
        
        bool taskCompleted = manager.isTaskCompleted(taskId);
        std::cout << "Task completed: " << (taskCompleted ? "Yes" : "No") << std::endl;
        
        // Тест 11: Очікування завершення завдання
        // Test 11: Waiting for task completion
        // Тест 11: Ожидание завершения задания
        std::cout << "\nTest 11: Waiting for task completion..." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Тест 12: Отримання результату завдання
        // Test 12: Getting task result
        // Тест 12: Получение результата задания
        std::cout << "\nTest 12: Getting task result..." << std::endl;
        
        std::string result = manager.getTaskResult(taskId);
        std::cout << "Task result: " << result << std::endl;
        
        // Тест 13: Отримання статистики кластера
        // Test 13: Getting cluster statistics
        // Тест 13: Получение статистики кластера
        std::cout << "\nTest 13: Getting cluster statistics..." << std::endl;
        
        ClusterStats stats = manager.getClusterStats();
        std::cout << "Cluster statistics:" << std::endl;
        std::cout << "  Total Nodes: " << stats.totalNodes << std::endl;
        std::cout << "  Online Nodes: " << stats.onlineNodes << std::endl;
        std::cout << "  Total Tasks: " << stats.totalTasks << std::endl;
        std::cout << "  Completed Tasks: " << stats.completedTasks << std::endl;
        
        // Тест 14: Перевірка спостерігача
        // Test 14: Checking observer
        // Тест 14: Проверка наблюдателя
        std::cout << "\nTest 14: Checking observer statistics..." << std::endl;
        
        std::cout << "  Node Status Changes: " << observer->nodeStatusChanges << std::endl;
        std::cout << "  Tasks Submitted: " << observer->tasksSubmitted << std::endl;
        std::cout << "  Tasks Completed: " << observer->tasksCompleted << std::endl;
        std::cout << "  Tasks Failed: " << observer->tasksFailed << std::endl;
        std::cout << "  Stats Updates: " << observer->statsUpdates << std::endl;
        
        // Тест 15: Зупинка вузла
        // Test 15: Stopping node
        // Тест 15: Остановка узла
        std::cout << "\nTest 15: Stopping node..." << std::endl;
        
        manager.stopNode();
        std::cout << "Node stopped successfully" << std::endl;
        
        // Тест 16: Видалення спостерігача
        // Test 16: Removing observer
        // Тест 16: Удаление наблюдателя
        std::cout << "\nTest 16: Removing observer..." << std::endl;
        
        manager.removeObserver(observer);
        std::cout << "Observer removed successfully" << std::endl;
        
        std::cout << "\n=== All Distributed Computing Tests Passed! ===" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}