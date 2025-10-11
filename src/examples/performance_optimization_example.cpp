/*
 * performance_optimization_example.cpp
 * Приклад використання оптимізатора продуктивності
 * Example of using performance optimizer
 * Пример использования оптимизатора производительности
 */

#include "../performance_optimization/PerformanceOptimizer.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using namespace NeuroSync::Performance;

// Реалізація спостерігача для відображення статистики
// Observer implementation for displaying statistics
// Реализация наблюдателя для отображения статистики
class StatsObserver : public PerformanceObserver {
public:
    void onPerformanceStatsUpdated(const PerformanceStats& stats) override {
        std::cout << "[STATS] Performance Stats Update:" << std::endl;
        std::cout << "  CPU Usage: " << (stats.cpuUsage * 100) << "%" << std::endl;
        std::cout << "  Memory Usage: " << (stats.memoryUsage / (1024 * 1024)) << " MB" << std::endl;
        std::cout << "  Active Threads: " << stats.activeThreads << std::endl;
        std::cout << "  Thread Pool Size: " << stats.threadPoolSize << std::endl;
        std::cout << "  Timestamp: " << stats.timestamp << std::endl;
        std::cout << std::endl;
    }
    
    void onOptimizationCompleted(const OptimizationResults& results) override {
        std::cout << "[OPTIMIZATION] Optimization Completed:" << std::endl;
        std::cout << "  Overall Performance Gain: " << (results.overallPerformanceGain * 100) << "%" << std::endl;
        std::cout << "  Optimization Time: " << results.optimizationTime << " ms" << std::endl;
        std::cout << "  CPU Improvement: " << (results.improvements.at(OptimizationType::CPU) * 100) << "%" << std::endl;
        std::cout << "  Memory Improvement: " << (results.improvements.at(OptimizationType::MEMORY) * 100) << "%" << std::endl;
        std::cout << "  Threading Improvement: " << (results.improvements.at(OptimizationType::THREADING) * 100) << "%" << std::endl;
        std::cout << "  Recommendations: " << results.recommendations << std::endl;
        std::cout << std::endl;
    }
    
    void onPerformanceIssueDetected(const std::string& issue, double severity) override {
        std::cout << "[ISSUE] Performance Issue Detected:" << std::endl;
        std::cout << "  Issue: " << issue << std::endl;
        std::cout << "  Severity: " << (severity * 100) << "%" << std::endl;
        std::cout << std::endl;
    }
};

// Симуляція навантаження на ЦП
// CPU load simulation
// Симуляция нагрузки на ЦП
void simulateCPULoad(int durationSeconds) {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::seconds(durationSeconds);
    
    while (std::chrono::high_resolution_clock::now() < end) {
        // Інтенсивні обчислення
        // Intensive calculations
        volatile double result = 0;
        for (int i = 0; i < 1000000; ++i) {
            result += std::sin(i) * std::cos(i);
        }
    }
}

// Симуляція використання пам'яті
// Memory usage simulation
// Симуляция использования памяти
void simulateMemoryUsage(size_t memorySizeMB) {
    size_t memorySizeBytes = memorySizeMB * 1024 * 1024;
    std::vector<char> memoryBlock(memorySizeBytes, 0);
    
    // Заповнення блоку пам'яті
    // Filling memory block
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 255);
    
    for (size_t i = 0; i < memorySizeBytes; ++i) {
        memoryBlock[i] = static_cast<char>(dis(gen));
    }
    
    // Утримання блоку в пам'яті на деякий час
    // Holding block in memory for some time
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  NeuroSync Performance Optimization Example" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        // 1. Створення оптимізатора продуктивності
        // 1. Creating performance optimizer
        // 1. Создание оптимизатора производительности
        std::cout << "\n1. Creating Performance Optimizer..." << std::endl;
        
        PerformanceOptimizer optimizer;
        
        // 2. Налаштування конфігурації
        // 2. Setting up configuration
        // 2. Настройка конфигурации
        std::cout << "\n2. Setting up configuration..." << std::endl;
        
        OptimizerConfig config;
        config.strategy = OptimizationStrategy::BALANCED;
        config.autoOptimization = true;
        config.optimizationInterval = 2000; // 2 секунди / 2 seconds / 2 секунды
        config.cpuThreshold = 0.7; // 70% поріг / 70% threshold / 70% порог
        config.memoryThreshold = 100 * 1024 * 1024; // 100 MB поріг / 100 MB threshold / 100 MB порог
        config.threadCount = 4;
        config.enableProfiling = true;
        
        // 3. Ініціалізація оптимізатора
        // 3. Initializing optimizer
        // 3. Инициализация оптимизатора
        std::cout << "\n3. Initializing optimizer..." << std::endl;
        
        if (!optimizer.initialize(config)) {
            std::cerr << "Failed to initialize Performance Optimizer" << std::endl;
            return 1;
        }
        
        std::cout << "Performance Optimizer initialized successfully!" << std::endl;
        
        // 4. Додавання спостерігача
        // 4. Adding observer
        // 4. Добавление наблюдателя
        std::cout << "\n4. Adding statistics observer..." << std::endl;
        
        auto observer = std::make_shared<StatsObserver>();
        optimizer.addObserver(observer);
        
        std::cout << "Statistics observer added!" << std::endl;
        
        // 5. Запуск автоматичної оптимізації
        // 5. Starting automatic optimization
        // 5. Запуск автоматической оптимизации
        std::cout << "\n5. Starting automatic optimization..." << std::endl;
        
        if (!optimizer.startAutoOptimization()) {
            std::cerr << "Failed to start automatic optimization" << std::endl;
            return 1;
        }
        
        std::cout << "Automatic optimization started!" << std::endl;
        
        // 6. Симуляція навантаження на систему
        // 6. Simulating system load
        // 6. Симуляция нагрузки на систему
        std::cout << "\n6. Simulating system load..." << std::endl;
        
        // Запуск потоків для симуляції навантаження
        // Starting threads to simulate load
        // Запуск потоков для симуляции нагрузки
        std::vector<std::thread> loadThreads;
        
        // Потік для навантаження на ЦП
        // Thread for CPU load
        // Поток для нагрузки на ЦП
        loadThreads.emplace_back(simulateCPULoad, 5);
        
        // Потік для використання пам'яті
        // Thread for memory usage
        // Поток для использования памяти
        loadThreads.emplace_back(simulateMemoryUsage, 50); // 50 MB
        
        // Додаткові потоки
        // Additional threads
        // Дополнительные потоки
        for (int i = 0; i < 2; ++i) {
            loadThreads.emplace_back(simulateCPULoad, 3);
        }
        
        // Очікування завершення потоків
        // Waiting for threads to complete
        // Ожидание завершения потоков
        for (auto& t : loadThreads) {
            if (t.joinable()) {
                t.join();
            }
        }
        
        std::cout << "System load simulation completed!" << std::endl;
        
        // 7. Ручна оптимізація
        // 7. Manual optimization
        // 7. Ручная оптимизация
        std::cout << "\n7. Performing manual optimization..." << std::endl;
        
        OptimizationResults results = optimizer.optimize();
        
        std::cout << "Manual optimization completed!" << std::endl;
        
        // 8. Відображення результатів
        // 8. Displaying results
        // 8. Отображение результатов
        std::cout << "\n8. Displaying optimization results..." << std::endl;
        
        std::cout << "Optimization Results:" << std::endl;
        std::cout << "  Overall Performance Gain: " << (results.overallPerformanceGain * 100) << "%" << std::endl;
        std::cout << "  Optimization Time: " << results.optimizationTime << " ms" << std::endl;
        std::cout << "  Recommendations: " << std::endl << results.recommendations << std::endl;
        
        // 9. Отримання статистики
        // 9. Getting statistics
        // 9. Получение статистики
        std::cout << "\n9. Getting performance statistics..." << std::endl;
        
        PerformanceStats stats = optimizer.getPerformanceStats();
        std::cout << "Current Performance Statistics:" << std::endl;
        std::cout << "  CPU Usage: " << (stats.cpuUsage * 100) << "%" << std::endl;
        std::cout << "  Memory Usage: " << (stats.memoryUsage / (1024 * 1024)) << " MB" << std::endl;
        std::cout << "  Available Memory: " << (stats.memoryAvailable / (1024 * 1024)) << " MB" << std::endl;
        std::cout << "  Active Threads: " << stats.activeThreads << std::endl;
        std::cout << "  Thread Pool Size: " << stats.threadPoolSize << std::endl;
        
        // 10. Отримання рекомендацій
        // 10. Getting recommendations
        // 10. Получение рекомендаций
        std::cout << "\n10. Getting recommendations..." << std::endl;
        
        std::string recommendations = optimizer.getRecommendations();
        std::cout << "Recommendations:" << std::endl << recommendations << std::endl;
        
        // 11. Зупинка автоматичної оптимізації
        // 11. Stopping automatic optimization
        // 11. Остановка автоматической оптимизации
        std::cout << "\n11. Stopping automatic optimization..." << std::endl;
        
        optimizer.stopAutoOptimization();
        
        std::cout << "Automatic optimization stopped!" << std::endl;
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Performance Optimization Example Completed!" << std::endl;
        std::cout << "========================================" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}