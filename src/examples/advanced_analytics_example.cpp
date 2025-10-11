#include "../advanced_analytics/AdvancedAnalytics.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <chrono>

// Приклад використання модуля розширеної аналітики
// Advanced analytics module usage example
// Пример использования модуля расширенной аналитики

int main() {
    std::cout << "=== Advanced Analytics Example ===" << std::endl;
    
    // Створення екземпляра модуля розширеної аналітики
    // Create an instance of the advanced analytics module
    // Создание экземпляра модуля расширенной аналитики
    NeuroSync::Analytics::AdvancedAnalytics analytics;
    
    // Ініціалізація модуля
    // Initialize the module
    // Инициализация модуля
    if (!analytics.initialize()) {
        std::cerr << "Failed to initialize advanced analytics module" << std::endl;
        return 1;
    }
    
    std::cout << "Advanced analytics module initialized successfully" << std::endl;
    
    // Створення прикладових даних для аналітики
    // Create sample data for analytics
    // Создание примерных данных для аналитики
    NeuroSync::Analytics::AnalyticsData data;
    data.dataSource = "Sample Data Source";
    data.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    
    // Генерація прикладових метрик
    // Generate sample metrics
    // Генерация примерных метрик
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);
    
    // Додавання метрик
    // Add metrics
    // Добавление метрик
    for (int i = 0; i < 5; ++i) {
        std::vector<double> values;
        for (int j = 0; j < 10; ++j) {
            values.push_back(dis(gen));
        }
        data.metrics["metric_" + std::to_string(i)] = values;
    }
    
    // Виконання різних типів аналітики
    // Perform different types of analytics
    // Выполнение разных типов аналитики
    
    std::cout << "\n--- Performing Predictive Analytics ---" << std::endl;
    auto predictiveResult = analytics.performAnalytics(data, NeuroSync::Analytics::AnalyticsType::PREDICTIVE);
    std::cout << "Predictive analytics completed with confidence: " << predictiveResult.confidence << std::endl;
    std::cout << "Processing time: " << predictiveResult.processingTime << " ms" << std::endl;
    
    std::cout << "\n--- Performing Prescriptive Analytics ---" << std::endl;
    auto prescriptiveResult = analytics.performAnalytics(data, NeuroSync::Analytics::AnalyticsType::PRESCRIPTIVE);
    std::cout << "Prescriptive analytics completed with confidence: " << prescriptiveResult.confidence << std::endl;
    std::cout << "Processing time: " << prescriptiveResult.processingTime << " ms" << std::endl;
    
    std::cout << "\n--- Performing Diagnostic Analytics ---" << std::endl;
    auto diagnosticResult = analytics.performAnalytics(data, NeuroSync::Analytics::AnalyticsType::DIAGNOSTIC);
    std::cout << "Diagnostic analytics completed with confidence: " << diagnosticResult.confidence << std::endl;
    std::cout << "Processing time: " << diagnosticResult.processingTime << " ms" << std::endl;
    
    std::cout << "\n--- Performing Cognitive Analytics ---" << std::endl;
    auto cognitiveResult = analytics.performAnalytics(data, NeuroSync::Analytics::AnalyticsType::COGNITIVE);
    std::cout << "Cognitive analytics completed with confidence: " << cognitiveResult.confidence << std::endl;
    std::cout << "Processing time: " << cognitiveResult.processingTime << " ms" << std::endl;
    
    std::cout << "\n--- Performing Real-time Analytics ---" << std::endl;
    auto realtimeResult = analytics.performAnalytics(data, NeuroSync::Analytics::AnalyticsType::REALTIME);
    std::cout << "Real-time analytics completed with confidence: " << realtimeResult.confidence << std::endl;
    std::cout << "Processing time: " << realtimeResult.processingTime << " ms" << std::endl;
    
    // Візуалізація даних
    // Visualize data
    // Визуализация данных
    std::cout << "\n--- Visualizing Data ---" << std::endl;
    if (analytics.visualizeData(data, "analytics_visualization.txt")) {
        std::cout << "Data visualization saved to analytics_visualization.txt" << std::endl;
    } else {
        std::cerr << "Failed to visualize data" << std::endl;
    }
    
    // Експорт результатів
    // Export results
    // Экспорт результатов
    std::cout << "\n--- Exporting Results ---" << std::endl;
    if (analytics.exportResults(predictiveResult, "predictive_results.txt")) {
        std::cout << "Predictive results exported to predictive_results.txt" << std::endl;
    } else {
        std::cerr << "Failed to export predictive results" << std::endl;
    }
    
    // Отримання статистики
    // Get statistics
    // Получение статистики
    std::cout << "\n--- Analytics Statistics ---" << std::endl;
    auto stats = analytics.getStatistics();
    std::cout << "Total Analyses Performed: " << stats.totalAnalysesPerformed << std::endl;
    std::cout << "Total Data Points Processed: " << stats.totalDataPointsProcessed << std::endl;
    std::cout << "Average Processing Time: " << stats.averageProcessingTime << " ms" << std::endl;
    std::cout << "Total Anomalies Detected: " << stats.totalAnomaliesDetected << std::endl;
    std::cout << "Total Insights Generated: " << stats.totalInsightsGenerated << std::endl;
    
    std::cout << "\nAdvanced Analytics Example completed successfully!" << std::endl;
    
    return 0;
}