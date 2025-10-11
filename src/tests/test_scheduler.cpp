// test_scheduler.cpp
// Тест для планувальника задач / Scheduler test / Тест для планувальника завдань
// NeuroSync OS Sparky

#include "../core/Scheduler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <cassert>

using namespace Core;

void testBasicScheduler() {
    std::cout << "Testing basic scheduler functionality...\n";
    
    Scheduler scheduler;
    std::atomic<int> counter(0);
    
    // Запуск планувальника
    // Start scheduler
    // Запуск планувальника
    scheduler.start();
    
    // Додавання простих задач
    // Add simple tasks
    // Додавання простих завдань
    for (int i = 0; i < 5; ++i) {
        scheduler.addTask([&counter]() {
            counter.fetch_add(1);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        });
    }
    
    // Очікування завершення задач
    // Wait for tasks to complete
    // Очікування завершення завдань
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Зупинка планувальника
    // Stop scheduler
    // Зупинка планувальника
    scheduler.stop();
    
    assert(counter == 5);
    std::cout << "Basic scheduler test passed!\n";
}

void testPriorityScheduler() {
    std::cout << "Testing priority scheduler functionality...\n";
    
    Scheduler scheduler;
    std::vector<int> executionOrder;
    std::mutex orderMutex;
    
    // Запуск планувальника
    // Start scheduler
    // Запуск планувальника
    scheduler.start();
    
    // Додавання задач з різними пріоритетами
    // Add tasks with different priorities
    // Додавання завдань з різними пріоритетами
    scheduler.addTask([&executionOrder, &orderMutex]() {
        std::lock_guard<std::mutex> lock(orderMutex);
        executionOrder.push_back(3); // Найнижчий пріоритет / Lowest priority / Найнижчий пріоритет
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }, 3);
    
    scheduler.addTask([&executionOrder, &orderMutex]() {
        std::lock_guard<std::mutex> lock(orderMutex);
        executionOrder.push_back(1); // Найвищий пріоритет / Highest priority / Найвищий пріоритет
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }, 1);
    
    scheduler.addTask([&executionOrder, &orderMutex]() {
        std::lock_guard<std::mutex> lock(orderMutex);
        executionOrder.push_back(2); // Середній пріоритет / Medium priority / Середній пріоритет
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }, 2);
    
    // Очікування завершення задач
    // Wait for tasks to complete
    // Очікування завершення завдань
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Зупинка планувальника
    // Stop scheduler
    // Зупинка планувальника
    scheduler.stop();
    
    // Перевірка порядку виконання
    // Check execution order
    // Перевірка порядку виконання
    assert(executionOrder.size() == 3);
    assert(executionOrder[0] == 1); // Найвищий пріоритет виконується першим
    assert(executionOrder[1] == 2); // Середній пріоритет виконується другим
    assert(executionOrder[2] == 3); // Найнижчий пріоритет виконується третім
    
    std::cout << "Priority scheduler test passed!\n";
}

void testDelayedScheduler() {
    std::cout << "Testing delayed scheduler functionality...\n";
    
    Scheduler scheduler;
    std::atomic<int> counter(0);
    auto startTime = std::chrono::high_resolution_clock::now();
    
    // Запуск планувальника
    // Start scheduler
    // Запуск планувальника
    scheduler.start();
    
    // Додавання відкладених задач
    // Add delayed tasks
    // Додавання відкладених завдань
    scheduler.addDelayedTask([&counter]() {
        counter.fetch_add(1);
    }, std::chrono::milliseconds(50));
    
    // Очікування завершення задач
    // Wait for tasks to complete
    // Очікування завершення завдань
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Зупинка планувальника
    // Stop scheduler
    // Зупинка планувальника
    scheduler.stop();
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    assert(counter == 1);
    assert(duration >= std::chrono::milliseconds(50));
    
    std::cout << "Delayed scheduler test passed!\n";
}

void testSchedulerStatistics() {
    std::cout << "Testing scheduler statistics...\n";
    
    Scheduler scheduler;
    std::atomic<int> counter(0);
    
    // Запуск планувальника
    // Start scheduler
    // Запуск планувальника
    scheduler.start();
    
    // Додавання задач
    // Add tasks
    // Додавання завдань
    for (int i = 0; i < 3; ++i) {
        scheduler.addTask([&counter]() {
            counter.fetch_add(1);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        });
    }
    
    // Очікування завершення задач
    // Wait for tasks to complete
    // Очікування завершення завдань
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    // Отримання статистики
    // Get statistics
    // Отримання статистики
    auto stats = scheduler.getStatistics();
    
    // Зупинка планувальника
    // Stop scheduler
    // Зупинка планувальника
    scheduler.stop();
    
    assert(stats.tasksAdded == 3);
    assert(stats.tasksCompleted == 3);
    assert(stats.tasksFailed == 0);
    assert(stats.totalExecutionTime.count() > 0);
    assert(stats.averageExecutionTime > 0.0);
    
    std::cout << "Scheduler statistics test passed!\n";
}

int main() {
    std::cout << "=== Running Scheduler Tests ===\n";
    
    try {
        testBasicScheduler();
        testPriorityScheduler();
        testDelayedScheduler();
        testSchedulerStatistics();
        
        std::cout << "\nAll scheduler tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}