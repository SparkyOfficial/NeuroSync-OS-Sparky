// weighted_fair_queuing_example.cpp
// Приклад використання алгоритму Weighted Fair Queuing / Weighted Fair Queuing usage example / Пример использования алгоритма Weighted Fair Queuing
// NeuroSync OS Sparky

#include "../core/AdvancedScheduler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace NeuroSync::Core;

std::atomic<int> taskCounter(0);

void taskFunction(int taskId, int weight, int durationMs) {
    std::cout << "Task " << taskId << " (weight: " << weight << ") started\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    std::cout << "Task " << taskId << " (weight: " << weight << ") completed\n";
    taskCounter.fetch_add(1);
}

int main() {
    std::cout << "NeuroSync OS Sparky - Weighted Fair Queuing Example\n";
    std::cout << "==================================================\n";
    
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
    
    std::cout << "Scheduler started\n";
    
    // Додавання задач з різними вагами
    // Add tasks with different weights
    // Додавання завдань з різними вагами
    std::cout << "Adding tasks with different weights...\n";
    
    // Задача з низькою вагою (низький пріоритет обслуговування)
    // Task with low weight (low service priority)
    // Задача с низким весом (низкий приоритет обслуживания)
    int taskId1 = scheduler.addTask("LowWeightTask", Utils::TaskType::CUSTOM, 1, 1, []() {
        taskFunction(1, 1, 50);
    });
    
    // Задача з високою вагою (високий пріоритет обслуговування)
    // Task with high weight (high service priority)
    // Задача с высоким весом (высокий приоритет обслуживания)
    int taskId2 = scheduler.addTask("HighWeightTask", Utils::TaskType::CUSTOM, 1, 5, []() {
        taskFunction(2, 5, 30);
    });
    
    // Задача з середньою вагою
    // Task with medium weight
    // Задача со средним весом
    int taskId3 = scheduler.addTask("MediumWeightTask", Utils::TaskType::CUSTOM, 1, 3, []() {
        taskFunction(3, 3, 40);
    });
    
    // Додавання ще однієї задачі з високою вагою
    // Add another task with high weight
    // Добавление еще одной задачи с высоким весом
    int taskId4 = scheduler.addTask("HighWeightTask2", Utils::TaskType::CUSTOM, 1, 4, []() {
        taskFunction(4, 4, 25);
    });
    
    std::cout << "Tasks added with IDs: " << taskId1 << ", " << taskId2 << ", " << taskId3 << ", " << taskId4 << "\n";
    
    // Оновлення ваги існуючої задачі
    // Update weight of existing task
    // Обновление веса существующей задачи
    std::cout << "Updating weight of task " << taskId1 << " from 1 to 6\n";
    if (scheduler.updateTaskWeight(taskId1, 6)) {
        std::cout << "Weight updated successfully\n";
    } else {
        std::cerr << "Failed to update weight\n";
    }
    
    // Очікування завершення всіх задач
    // Wait for all tasks to complete
    // Ожидание завершения всех задач
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    // Отримання статистики
    // Get statistics
    // Получение статистики
    auto stats = scheduler.getStatistics();
    
    std::cout << "\nScheduler Statistics:\n";
    std::cout << "  Total Tasks: " << stats.totalTasks << "\n";
    std::cout << "  Running Tasks: " << stats.runningTasks << "\n";
    std::cout << "  Pending Tasks: " << stats.pendingTasks << "\n";
    std::cout << "  Completed Tasks: " << stats.completedTasks << "\n";
    std::cout << "  Failed Tasks: " << stats.failedTasks << "\n";
    std::cout << "  Cancelled Tasks: " << stats.cancelledTasks << "\n";
    std::cout << "  Total Execution Time: " << stats.totalExecutionTime << " ms\n";
    std::cout << "  Average Execution Time: " << stats.averageExecutionTime << " ms\n";
    
    // Зміна алгоритму планування
    // Change scheduling algorithm
    // Смена алгоритма планирования
    std::cout << "\nChanging scheduling algorithm to Priority Based...\n";
    if (scheduler.setSchedulingAlgorithm(SchedulingAlgorithmType::PRIORITY_BASED)) {
        std::cout << "Algorithm changed successfully\n";
        
        // Додавання нової задачі після зміни алгоритму
        // Add new task after algorithm change
        // Добавление новой задачи после смены алгоритма
        int taskId5 = scheduler.addTask("NewTask", Utils::TaskType::CUSTOM, 1, 2, []() {
            taskFunction(5, 2, 20);
        });
        
        std::cout << "Added new task with ID: " << taskId5 << "\n";
        
        // Очікування завершення нової задачі
        // Wait for new task to complete
        // Ожидание завершения новой задачи
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
        std::cerr << "Failed to change algorithm\n";
    }
    
    // Зупинка планувальника
    // Stop scheduler
    // Остановка планувальника
    scheduler.stop();
    
    std::cout << "\nScheduler stopped\n";
    std::cout << "Total tasks completed: " << taskCounter.load() << "\n";
    
    std::cout << "\nWeighted Fair Queuing example completed successfully!\n";
    
    return 0;
}