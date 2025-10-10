#include "diagnostics/Diagnostics.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>

using namespace NeuroSync::Diagnostics;

void testBasicDiagnostics() {
    std::cout << "Testing basic diagnostics functionality..." << std::endl;
    
    Diagnostics diagnostics;
    
    // Тестування трасування
    // Testing tracing
    // Тестування трасування
    diagnostics.startTracing();
    
    // Запис подій
    // Logging events
    // Запис подій
    diagnostics.logEvent(1, "TEST_EVENT", "Test message");
    diagnostics.logEvent(2, "ANOTHER_EVENT", "Another test message");
    
    // Перевірка, що події були записані
    // Checking that events were logged
    // Перевірка, що події були записані
    std::string report = diagnostics.getTextReport();
    assert(report.find("TEST_EVENT") != std::string::npos);
    assert(report.find("ANOTHER_EVENT") != std::string::npos);
    
    diagnostics.stopTracing();
    
    std::cout << "Basic diagnostics test passed!" << std::endl;
}

void testProfiler() {
    std::cout << "Testing profiler functionality..." << std::endl;
    
    Diagnostics diagnostics;
    
    // Тестування профілювання
    // Testing profiling
    // Тестування профілювання
    diagnostics.beginProfile("test_function", 1);
    
    // Симулювати деяку роботу
    // Simulate some work
    // Симулювати деяку роботу
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    diagnostics.endProfile("test_function");
    
    // Експорт даних профілювання
    // Export profiling data
    // Експорт даних профілювання
    std::string json = diagnostics.exportToJSON();
    assert(!json.empty());
    
    std::cout << "Profiler test passed!" << std::endl;
}

void testVisualizer() {
    std::cout << "Testing visualizer functionality..." << std::endl;
    
    Diagnostics diagnostics;
    
    // Додати активність нейронів
    // Add neuron activities
    // Додати активність нейронів
    diagnostics.logEvent(1, "ACTIVATION", "Neuron activated");
    diagnostics.logEvent(2, "SIGNAL_SEND", "Signal sent");
    diagnostics.logEvent(1, "DEACTIVATION", "Neuron deactivated");
    
    // Генерувати звіти
    // Generate reports
    // Генерувати звіти
    std::string textReport = diagnostics.getTextReport();
    assert(!textReport.empty());
    
    std::string htmlReport = diagnostics.getHTMLReport();
    assert(!htmlReport.empty());
    
    std::string csvExport = diagnostics.exportToCSV();
    assert(!csvExport.empty());
    
    std::cout << "Visualizer test passed!" << std::endl;
}

void testPerformanceMonitor() {
    std::cout << "Testing performance monitor functionality..." << std::endl;
    
    Diagnostics diagnostics;
    
    // Почати моніторинг
    // Start monitoring
    // Почати моніторинг
    diagnostics.startPerformanceMonitoring();
    
    // Оновити метрики
    // Update metrics
    // Оновити метрики
    diagnostics.updatePerformanceMetrics(45.5, 1024000, 500, 2000, 100);
    diagnostics.updatePerformanceMetrics(52.3, 1048576, 550, 2200, 120);
    
    // Отримати останні метрики
    // Get latest metrics
    // Отримати останні метрики
    auto latestMetrics = diagnostics.getLatestMetrics();
    assert(latestMetrics.cpuUsage == 52.3);
    assert(latestMetrics.memoryUsage == 1048576);
    
    // Перевірити порогові значення
    // Check threshold values
    // Перевірити порогові значення
    bool thresholdsOK = diagnostics.checkThresholds();
    assert(thresholdsOK);
    
    // Зупинити моніторинг
    // Stop monitoring
    // Зупинити моніторинг
    diagnostics.stopPerformanceMonitoring();
    
    std::cout << "Performance monitor test passed!" << std::endl;
}

int main() {
    std::cout << "=== Running Diagnostics Tests ===" << std::endl;
    
    try {
        testBasicDiagnostics();
        testProfiler();
        testVisualizer();
        testPerformanceMonitor();
        
        std::cout << "\n=== All Diagnostics Tests Passed! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with error: " << e.what() << std::endl;
        return 1;
    }
}