/*
 * test_performance_optimization.cpp
 * Тест для оптимізатора продуктивності
 * Test for performance optimizer
 * Тест для оптимизатора производительности
 */

#include "../performance_optimization/PerformanceOptimizer.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <thread>
#include <chrono>

using namespace NeuroSync::Performance;

// Тестова реалізація спостерігача
// Test observer implementation
// Тестовая реализация наблюдателя
class TestObserver : public PerformanceObserver {
public:
    int statsUpdates = 0;
    int optimizations = 0;
    int issues = 0;
    
    void onPerformanceStatsUpdated(const PerformanceStats& stats) override {
        statsUpdates++;
        std::cout << "[TEST] Performance stats updated" << std::endl;
    }
    
    void onOptimizationCompleted(const OptimizationResults& results) override {
        optimizations++;
        std::cout << "[TEST] Optimization completed with " 
                  << (results.overallPerformanceGain * 100) << "% gain" << std::endl;
    }
    
    void onPerformanceIssueDetected(const std::string& issue, double severity) override {
        issues++;
        std::cout << "[TEST] Performance issue detected: " << issue 
                  << " (severity: " << severity << ")" << std::endl;
    }
};

int main() {
    std::cout << "=== Running Performance Optimization Tests ===" << std::endl;
    
    try {
        // Тест 1: Створення та ініціалізація оптимізатора
        // Test 1: Creating and initializing optimizer
        // Тест 1: Создание и инициализация оптимизатора
        std::cout << "\nTest 1: Creating and initializing optimizer..." << std::endl;
        
        PerformanceOptimizer optimizer;
        
        OptimizerConfig config;
        config.strategy = OptimizationStrategy::BALANCED;
        config.autoOptimization = true;
        config.optimizationInterval = 1000; // 1 секунда для тесту / 1 second for test / 1 секунда для теста
        config.cpuThreshold = 0.8;
        config.memoryThreshold = 50 * 1024 * 1024; // 50 MB
        config.threadCount = 2;
        
        bool initSuccess = optimizer.initialize(config);
        assert(initSuccess);
        std::cout << "Optimizer initialized successfully" << std::endl;
        
        // Тест 2: Додавання спостерігача
        // Test 2: Adding observer
        // Тест 2: Добавление наблюдателя
        std::cout << "\nTest 2: Adding observer..." << std::endl;
        
        auto observer = std::make_shared<TestObserver>();
        optimizer.addObserver(observer);
        std::cout << "Observer added successfully" << std::endl;
        
        // Тест 3: Отримання конфігурації
        // Test 3: Getting configuration
        // Тест 3: Получение конфигурации
        std::cout << "\nTest 3: Getting configuration..." << std::endl;
        
        OptimizerConfig retrievedConfig = optimizer.getConfiguration();
        assert(retrievedConfig.strategy == OptimizationStrategy::BALANCED);
        assert(retrievedConfig.threadCount == 2);
        std::cout << "Configuration retrieved successfully" << std::endl;
        
        // Тест 4: Запуск автоматичної оптимізації
        // Test 4: Starting automatic optimization
        // Тест 4: Запуск автоматической оптимизации
        std::cout << "\nTest 4: Starting automatic optimization..." << std::endl;
        
        bool autoOptStarted = optimizer.startAutoOptimization();
        assert(autoOptStarted);
        std::cout << "Automatic optimization started successfully" << std::endl;
        
        // Тест 5: Отримання статистики продуктивності
        // Test 5: Getting performance statistics
        // Тест 5: Получение статистики производительности
        std::cout << "\nTest 5: Getting performance statistics..." << std::endl;
        
        PerformanceStats stats = optimizer.getPerformanceStats();
        std::cout << "Performance stats retrieved successfully" << std::endl;
        std::cout << "  CPU Usage: " << stats.cpuUsage << std::endl;
        std::cout << "  Memory Usage: " << stats.memoryUsage << " bytes" << std::endl;
        std::cout << "  Active Threads: " << stats.activeThreads << std::endl;
        
        // Тест 6: Ручна оптимізація
        // Test 6: Manual optimization
        // Тест 6: Ручная оптимизация
        std::cout << "\nTest 6: Performing manual optimization..." << std::endl;
        
        OptimizationResults results = optimizer.optimize();
        std::cout << "Manual optimization completed successfully" << std::endl;
        std::cout << "  Overall Performance Gain: " << (results.overallPerformanceGain * 100) << "%" << std::endl;
        std::cout << "  Optimization Time: " << results.optimizationTime << " ms" << std::endl;
        
        // Тест 7: Перевірка рекомендацій
        // Test 7: Checking recommendations
        // Тест 7: Проверка рекомендаций
        std::cout << "\nTest 7: Checking recommendations..." << std::endl;
        
        std::string recommendations = optimizer.getRecommendations();
        assert(!recommendations.empty());
        std::cout << "Recommendations retrieved successfully" << std::endl;
        std::cout << "  Recommendations length: " << recommendations.length() << " characters" << std::endl;
        
        // Тест 8: Оновлення порогів
        // Test 8: Updating thresholds
        // Тест 8: Обновление порогов
        std::cout << "\nTest 8: Updating thresholds..." << std::endl;
        
        optimizer.setCpuThreshold(0.9);
        optimizer.setMemoryThreshold(100 * 1024 * 1024); // 100 MB
        std::cout << "Thresholds updated successfully" << std::endl;
        
        // Тест 9: Очікування деякого часу для автоматичної оптимізації
        // Test 9: Waiting for some time for automatic optimization
        // Тест 9: Ожидание некоторого времени для автоматической оптимизации
        std::cout << "\nTest 9: Waiting for automatic optimization cycles..." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        // Тест 10: Перевірка спостерігача
        // Test 10: Checking observer
        // Тест 10: Проверка наблюдателя
        std::cout << "\nTest 10: Checking observer statistics..." << std::endl;
        
        std::cout << "  Stats Updates: " << observer->statsUpdates << std::endl;
        std::cout << "  Optimizations: " << observer->optimizations << std::endl;
        std::cout << "  Issues: " << observer->issues << std::endl;
        
        // Тест 11: Зупинка автоматичної оптимізації
        // Test 11: Stopping automatic optimization
        // Тест 11: Остановка автоматической оптимизации
        std::cout << "\nTest 11: Stopping automatic optimization..." << std::endl;
        
        optimizer.stopAutoOptimization();
        std::cout << "Automatic optimization stopped successfully" << std::endl;
        
        // Тест 12: Видалення спостерігача
        // Test 12: Removing observer
        // Тест 12: Удаление наблюдателя
        std::cout << "\nTest 12: Removing observer..." << std::endl;
        
        optimizer.removeObserver(observer);
        std::cout << "Observer removed successfully" << std::endl;
        
        std::cout << "\n=== All Performance Optimization Tests Passed! ===" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}