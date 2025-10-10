#include "../NeuroSync.h"
#include "../core/AdvancedScheduler.h"
#include <iostream>
#include <thread>
#include <chrono>

// advanced_scheduler_example.cpp
// Пример использования расширенного планировщика NeuroSync OS Sparky
// Example of using advanced scheduler in NeuroSync OS Sparky
// Приклад використання розширеного планувальника NeuroSync OS Sparky

using namespace NeuroSync::Core;
using namespace NeuroSync::Core::Utils;

// Функции для демонстрационных задач
// Functions for demonstration tasks
// Функції для демонстраційних завдань

void neuronProcessingTask1() {
    std::cout << "[NEURON 1] Starting processing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "[NEURON 1] Processing complete." << std::endl;
}

void neuronProcessingTask2() {
    std::cout << "[NEURON 2] Starting processing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::cout << "[NEURON 2] Processing complete." << std::endl;
}

void neuronProcessingTask3() {
    std::cout << "[NEURON 3] Starting processing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "[NEURON 3] Processing complete." << std::endl;
}

void systemMaintenanceTask() {
    std::cout << "[SYSTEM] Starting maintenance..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "[SYSTEM] Maintenance complete." << std::endl;
}

void communicationTask() {
    std::cout << "[COMM] Starting communication..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    std::cout << "[COMM] Communication complete." << std::endl;
}

void diagnosticsTask() {
    std::cout << "[DIAG] Starting diagnostics..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    std::cout << "[DIAG] Diagnostics complete." << std::endl;
}

int main() {
    std::cout << "=== NeuroSync OS Sparky Advanced Scheduler Example ===" << std::endl;
    std::cout << "=== Приклад розширеного планувальника NeuroSync OS Sparky ===" << std::endl;
    std::cout << "=== Пример расширенного планировщика NeuroSync OS Sparky ===" << std::endl;
    
    // Создание расширенного планировщика
    // Creating advanced scheduler
    // Створення розширеного планувальника
    AdvancedScheduler scheduler;
    
    // Инициализация планировщика с алгоритмом на основе приоритетов
    // Initialize scheduler with priority-based algorithm
    // Ініціалізація планувальника з алгоритмом на основі пріоритетів
    if (!scheduler.initialize(SchedulingAlgorithmType::PRIORITY_BASED)) {
        std::cerr << "Failed to initialize scheduler!" << std::endl;
        return 1;
    }
    
    std::cout << "Scheduler initialized with Priority-Based algorithm." << std::endl;
    std::cout << "Планувальник ініціалізовано з алгоритмом на основі пріоритетів." << std::endl;
    std::cout << "Планировщик инициализирован с алгоритмом на основе приоритетов." << std::endl;
    
    // Запуск планировщика
    // Start scheduler
    // Запуск планувальника
    scheduler.start();
    std::cout << "Scheduler started." << std::endl;
    std::cout << "Планувальник запущено." << std::endl;
    std::cout << "Планировщик запущен." << std::endl;
    
    // Добавление задач различного типа и приоритета
    // Adding tasks of different types and priorities
    // Додавання завдань різного типу та пріоритету
    std::cout << "\nAdding tasks..." << std::endl;
    std::cout << "Додавання завдань..." << std::endl;
    std::cout << "Добавление задач..." << std::endl;
    
    int neuronTask1 = scheduler.addTask("Neuron Processing 1", TaskType::NEURON_PROCESS, 1, 10, neuronProcessingTask1);
    int neuronTask2 = scheduler.addTask("Neuron Processing 2", TaskType::NEURON_PROCESS, 2, 15, neuronProcessingTask2);
    int neuronTask3 = scheduler.addTask("Neuron Processing 3", TaskType::NEURON_PROCESS, 3, 20, neuronProcessingTask3);
    int maintenanceTask = scheduler.addTask("System Maintenance", TaskType::SYSTEM_MAINTENANCE, 5, 5, systemMaintenanceTask);
    int commTask = scheduler.addTask("Communication", TaskType::COMMUNICATION, 4, 12, communicationTask);
    int diagTask = scheduler.addTask("Diagnostics", TaskType::DIAGNOSTICS, 1, 8, diagnosticsTask);
    
    std::cout << "Created tasks with IDs: " << neuronTask1 << ", " << neuronTask2 << ", " << neuronTask3 
              << ", " << maintenanceTask << ", " << commTask << ", " << diagTask << std::endl;
    
    // Ожидание некоторое время для выполнения задач
    // Wait for some time to allow tasks to execute
    // Очікування деякий час для виконання завдань
    std::cout << "\nWaiting for tasks to execute..." << std::endl;
    std::cout << "Очікування виконання завдань..." << std::endl;
    std::cout << "Ожидание выполнения задач..." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Получение статистики
    // Get statistics
    // Отримання статистики
    auto stats = scheduler.getStatistics();
    std::cout << "\n=== Scheduler Statistics ===" << std::endl;
    std::cout << "=== Статистика планувальника ===" << std::endl;
    std::cout << "=== Статистика планировщика ===" << std::endl;
    std::cout << "Total Tasks: " << stats.totalTasks << std::endl;
    std::cout << "Загальна кількість завдань: " << stats.totalTasks << std::endl;
    std::cout << "Общее количество задач: " << stats.totalTasks << std::endl;
    std::cout << "Running Tasks: " << stats.runningTasks << std::endl;
    std::cout << "Виконувані завдання: " << stats.runningTasks << std::endl;
    std::cout << "Выполняемые задачи: " << stats.runningTasks << std::endl;
    std::cout << "Pending Tasks: " << stats.pendingTasks << std::endl;
    std::cout << "Очікуючі завдання: " << stats.pendingTasks << std::endl;
    std::cout << "Ожидающие задачи: " << stats.pendingTasks << std::endl;
    std::cout << "Completed Tasks: " << stats.completedTasks << std::endl;
    std::cout << "Завершені завдання: " << stats.completedTasks << std::endl;
    std::cout << "Завершенные задачи: " << stats.completedTasks << std::endl;
    std::cout << "Average Execution Time: " << stats.averageExecutionTime << " ms" << std::endl;
    std::cout << "Середній час виконання: " << stats.averageExecutionTime << " мс" << std::endl;
    std::cout << "Среднее время выполнения: " << stats.averageExecutionTime << " мс" << std::endl;
    
    // Остановка планировщика
    // Stop scheduler
    // Зупинка планувальника
    std::cout << "\nStopping scheduler..." << std::endl;
    std::cout << "Зупинка планувальника..." << std::endl;
    std::cout << "Остановка планировщика..." << std::endl;
    scheduler.stop();
    
    std::cout << "Scheduler stopped." << std::endl;
    std::cout << "Планувальник зупинено." << std::endl;
    std::cout << "Планировщик остановлен." << std::endl;
    
    // Пример с другим алгоритмом планирования
    // Example with different scheduling algorithm
    // Приклад з іншим алгоритмом планування
    std::cout << "\n=== Testing Round Robin Algorithm ===" << std::endl;
    std::cout << "=== Тестування алгоритму Round Robin ===" << std::endl;
    std::cout << "=== Тестирование алгоритма Round Robin ===" << std::endl;
    
    if (scheduler.initialize(SchedulingAlgorithmType::ROUND_ROBIN)) {
        std::cout << "Scheduler initialized with Round Robin algorithm." << std::endl;
        std::cout << "Планувальник ініціалізовано з алгоритмом Round Robin." << std::endl;
        std::cout << "Планировщик инициализирован с алгоритмом Round Robin." << std::endl;
        
        scheduler.start();
        
        // Добавление тех же задач
        // Adding the same tasks
        // Додавання тих самих завдань
        scheduler.addTask("Neuron Processing 1", TaskType::NEURON_PROCESS, 1, 10, neuronProcessingTask1);
        scheduler.addTask("Neuron Processing 2", TaskType::NEURON_PROCESS, 2, 15, neuronProcessingTask2);
        scheduler.addTask("System Maintenance", TaskType::SYSTEM_MAINTENANCE, 5, 5, systemMaintenanceTask);
        
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        scheduler.stop();
        
        std::cout << "Round Robin scheduler test completed." << std::endl;
        std::cout << "Тест планувальника Round Robin завершено." << std::endl;
        std::cout << "Тестирование планировщика Round Robin завершено." << std::endl;
    }
    
    std::cout << "\nAdvanced Scheduler Example completed!" << std::endl;
    std::cout << "Приклад розширеного планувальника завершено!" << std::endl;
    std::cout << "Пример расширенного планировщика завершен!" << std::endl;
    
    return 0;
}