#include "diagnostics/Diagnostics.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using namespace NeuroSync::Diagnostics;

// Функція для симуляції активності нейронів
// Function to simulate neuron activity
// Функція для симуляції активності нейронів
void simulateNeuronActivity(Diagnostics& diagnostics, int neuronId) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    // Симулювати різні типи активності
    // Simulate different types of activity
    // Симулювати різні типи активності
    std::vector<std::string> activities = {"ACTIVATION", "DEACTIVATION", "SIGNAL_SEND", "SIGNAL_RECEIVE", "LEARNING"};
    
    for (int i = 0; i < 5; ++i) {
        int activityIndex = dis(gen) % activities.size();
        std::string activity = activities[activityIndex];
        
        diagnostics.logEvent(neuronId, activity, "Neuron activity simulation");
        
        // Симулювати деяку роботу
        // Simulate some work
        // Симулювати деяку роботу
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen) % 100));
    }
}

// Функція для симуляції профілювання
// Function to simulate profiling
// Функція для симуляції профілювання
void simulateProfiling(Diagnostics& diagnostics) {
    // Почати профілювання
    // Start profiling
    // Почати профілювання
    diagnostics.beginProfile("neuron_processing", 1);
    
    // Симулювати обробку
    // Simulate processing
    // Симулювати обробку
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Завершити профілювання
    // End profiling
    // Завершити профілювання
    diagnostics.endProfile("neuron_processing");
    
    // Почати інше профілювання
    // Start another profiling
    // Почати інше профілювання
    diagnostics.beginProfile("synapse_transmission", 1);
    
    // Симулювати передачу сигналу
    // Simulate signal transmission
    // Симулювати передачу сигналу
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    // Завершити профілювання
    // End profiling
    // Завершити профілювання
    diagnostics.endProfile("synapse_transmission");
}

// Функція для симуляції оновлення метрик продуктивності
// Function to simulate performance metrics update
// Функція для симуляції оновлення метрик продуктивності
void simulatePerformanceMetrics(Diagnostics& diagnostics) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> cpuDis(0.0, 100.0);
    std::uniform_int_distribution<> memoryDis(1000000, 2000000);
    std::uniform_int_distribution<> neuronDis(100, 1000);
    std::uniform_int_distribution<> synapseDis(1000, 5000);
    std::uniform_int_distribution<> messageDis(100, 1000);
    
    // Оновити метрики кілька разів
    // Update metrics several times
    // Оновити метрики кілька разів
    for (int i = 0; i < 5; ++i) {
        double cpu = cpuDis(gen);
        size_t memory = memoryDis(gen);
        size_t neurons = neuronDis(gen);
        size_t synapses = synapseDis(gen);
        size_t messages = messageDis(gen);
        
        diagnostics.updatePerformanceMetrics(cpu, memory, neurons, synapses, messages);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::cout << "=== Advanced Diagnostics Example for NeuroSync OS Sparky ===" << std::endl;
    
    try {
        // Створити модуль діагностики
        // Create diagnostics module
        // Створити модуль діагностики
        Diagnostics diagnostics;
        
        // Почати трасування
        // Start tracing
        // Почати трасування
        diagnostics.startTracing();
        
        // Почати моніторинг продуктивності
        // Start performance monitoring
        // Почати моніторинг продуктивності
        diagnostics.startPerformanceMonitoring();
        
        // Створити кілька потоків для симуляції активності нейронів
        // Create multiple threads to simulate neuron activity
        // Створити кілька потоків для симуляції активності нейронів
        std::vector<std::thread> threads;
        
        for (int i = 1; i <= 3; ++i) {
            threads.emplace_back(simulateNeuronActivity, std::ref(diagnostics), i);
        }
        
        // Симулювати профілювання
        // Simulate profiling
        // Симулювати профілювання
        threads.emplace_back(simulateProfiling, std::ref(diagnostics));
        
        // Симулювати оновлення метрик продуктивності
        // Simulate performance metrics update
        // Симулювати оновлення метрик продуктивності
        threads.emplace_back(simulatePerformanceMetrics, std::ref(diagnostics));
        
        // Очікувати завершення всіх потоків
        // Wait for all threads to complete
        // Очікувати завершення всіх потоків
        for (auto& thread : threads) {
            thread.join();
        }
        
        // Зупинити трасування
        // Stop tracing
        // Зупинити трасування
        diagnostics.stopTracing();
        
        // Зупинити моніторинг продуктивності
        // Stop performance monitoring
        // Зупинити моніторинг продуктивності
        diagnostics.stopPerformanceMonitoring();
        
        // Вивести звіти
        // Print reports
        // Вивести звіти
        std::cout << "\n=== Text Report ===" << std::endl;
        std::cout << diagnostics.getTextReport() << std::endl;
        
        std::cout << "\n=== Performance Check ===" << std::endl;
        std::cout << "Thresholds OK: " << (diagnostics.checkThresholds() ? "Yes" : "No") << std::endl;
        
        std::cout << "\n=== CSV Export ===" << std::endl;
        std::cout << diagnostics.exportToCSV() << std::endl;
        
        std::cout << "\n=== JSON Export ===" << std::endl;
        std::cout << diagnostics.exportToJSON() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nAdvanced diagnostics example completed successfully!" << std::endl;
    return 0;
}