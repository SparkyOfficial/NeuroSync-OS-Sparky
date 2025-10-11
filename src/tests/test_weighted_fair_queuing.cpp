// test_weighted_fair_queuing.cpp
// Тест для алгоритму Weighted Fair Queuing / Weighted Fair Queuing test / Тест для алгоритму Weighted Fair Queuing
// NeuroSync OS Sparky

#include "../core/AdvancedScheduler.h"
#include "../core/algorithms/WeightedFairQueuingScheduling.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <cassert>

using namespace NeuroSync::Core;

std::atomic<int> taskExecutionCount(0);
std::vector<int> executionOrder;

void simpleTask(int taskId) {
    std::cout << "Task " << taskId << " executed\n";
    executionOrder.push_back(taskId);
    taskExecutionCount.fetch_add(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

int main() {
    std::cout << "=== Running Weighted Fair Queuing Tests ===\n";
    
    try {
        AdvancedScheduler scheduler;
        
        // Ініціалізація планувальника з алгоритмом Weighted Fair Queuing
        // Initialize scheduler with Weighted Fair Queuing algorithm
        // Инициализация планувальника с алгоритмом Weighted Fair Queuing
        if (!scheduler.initialize(SchedulingAlgorithmType::WEIGHTED_FAIR_QUEUING)) {
            std::cerr << "Failed to initialize scheduler\n";
            return 1;
        }
        
        std::cout << "Scheduler initialized with Weighted Fair Queuing algorithm\n";
        
        // Запуск планувальника
        // Start scheduler
        // Запуск планувальника
        scheduler.start();
        
        // Додавання задач з різними вагами
        // Add tasks with different weights
        // Додавання завдань з різними вагами
        int taskId1 = scheduler.addTask("Task1", Utils::TaskType::CUSTOM, 1, 1, []() { simpleTask(1); });
        int taskId2 = scheduler.addTask("Task2", Utils::TaskType::CUSTOM, 1, 3, []() { simpleTask(2); });
        int taskId3 = scheduler.addTask("Task3", Utils::TaskType::CUSTOM, 1, 2, []() { simpleTask(3); });
        
        std::cout << "Added tasks with IDs: " << taskId1 << ", " << taskId2 << ", " << taskId3 << "\n";
        
        // Оновлення ваги задачі
        // Update task weight
        // Оновлення ваги завдання
        if (scheduler.updateTaskWeight(taskId1, 5)) {
            std::cout << "Updated weight of task " << taskId1 << " to 5\n";
        } else {
            std::cerr << "Failed to update weight of task " << taskId1 << "\n";
        }
        
        // Очікування завершення задач
        // Wait for tasks to complete
        // Очікування завершення завдань
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        // Отримання статистики
        // Get statistics
        // Отримання статистики
        auto stats = scheduler.getStatistics();
        
        std::cout << "\nScheduler Statistics:\n";
        std::cout << "  Total Tasks: " << stats.totalTasks << "\n";
        std::cout << "  Completed Tasks: " << stats.completedTasks << "\n";
        std::cout << "  Failed Tasks: " << stats.failedTasks << "\n";
        std::cout << "  Average Execution Time: " << stats.averageExecutionTime << " ms\n";
        
        // Зупинка планувальника
        // Stop scheduler
        // Зупинка планувальника
        scheduler.stop();
        
        // Перевірка результатів
        // Check results
        // Проверка результатов
        assert(taskExecutionCount == 3);
        assert(stats.completedTasks == 3);
        assert(stats.totalTasks == 3);
        
        std::cout << "\nWeighted Fair Queuing test passed!\n";
        std::cout << "Execution order: ";
        for (size_t i = 0; i < executionOrder.size(); ++i) {
            std::cout << executionOrder[i];
            if (i < executionOrder.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << "\n";
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}