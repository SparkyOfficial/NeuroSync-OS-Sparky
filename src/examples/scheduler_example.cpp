// scheduler_example.cpp
// Приклад використання планувальника задач / Scheduler usage example / Пример использования планувальника завдань
// NeuroSync OS Sparky

#include "../core/Scheduler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace Core;

std::atomic<int> taskCounter(0);

void taskFunction(int taskId, int durationMs) {
    std::cout << "Task " << taskId << " started\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    std::cout << "Task " << taskId << " completed\n";
    taskCounter.fetch_add(1);
}

int main() {
    std::cout << "NeuroSync OS Sparky - Scheduler Example\n";
    std::cout << "========================================\n";
    
    Scheduler scheduler;
    
    // Запуск планувальника
    // Start scheduler
    // Запуск планувальника
    scheduler.start();
    
    std::cout << "Scheduler started\n";
    
    // Додавання задач з різними пріоритетами
    // Add tasks with different priorities
    // Додавання завдань з різними пріоритетами
    std::cout << "Adding tasks with different priorities...\n";
    
    scheduler.addTask([]() {
        taskFunction(1, 100);
    }, 3); // Найнижчий пріоритет / Lowest priority / Найнижчий пріоритет
    
    scheduler.addTask([]() {
        taskFunction(2, 50);
    }, 1); // Найвищий пріоритет / Highest priority / Найвищий пріоритет
    
    scheduler.addTask([]() {
        taskFunction(3, 75);
    }, 2); // Середній пріоритет / Medium priority / Середній пріоритет
    
    // Додавання відкладених задач
    // Add delayed tasks
    // Додавання відкладених завдань
    std::cout << "Adding delayed tasks...\n";
    
    scheduler.addDelayedTask([]() {
        taskFunction(4, 30);
    }, std::chrono::milliseconds(200), 1); // Виконати через 200 мс з високим пріоритетом
    
    scheduler.addDelayedTask([]() {
        taskFunction(5, 20);
    }, std::chrono::milliseconds(100), 2); // Виконати через 100 мс з середнім пріоритетом
    
    // Очікування завершення всіх задач
    // Wait for all tasks to complete
    // Очікування завершення всіх завдань
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Отримання статистики
    // Get statistics
    // Отримання статистики
    auto stats = scheduler.getStatistics();
    
    std::cout << "\nScheduler Statistics:\n";
    std::cout << "  Tasks Added: " << stats.tasksAdded << "\n";
    std::cout << "  Tasks Completed: " << stats.tasksCompleted << "\n";
    std::cout << "  Tasks Failed: " << stats.tasksFailed << "\n";
    std::cout << "  Total Execution Time: " << stats.totalExecutionTime.count() << " ms\n";
    std::cout << "  Average Execution Time: " << stats.averageExecutionTime << " ms\n";
    
    // Зупинка планувальника
    // Stop scheduler
    // Зупинка планувальника
    scheduler.stop();
    
    std::cout << "\nScheduler stopped\n";
    std::cout << "Total tasks completed: " << taskCounter.load() << "\n";
    
    std::cout << "\nScheduler example completed successfully!\n";
    
    return 0;
}