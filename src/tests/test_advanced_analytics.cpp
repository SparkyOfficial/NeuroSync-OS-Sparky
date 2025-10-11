#include "../advanced_analytics/AdvancedAnalytics.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include <random>

// Тести для модуля розширеної аналітики
// Tests for the advanced analytics module
// Тесты для модуля расширенной аналитики

void testAdvancedAnalyticsInitialization() {
    std::cout << "Testing AdvancedAnalytics initialization..." << std::endl;
    
    NeuroSync::Analytics::AdvancedAnalytics analytics;
    
    // Перевірка, що модуль успішно ініціалізується
    // Check that the module initializes successfully
    // Проверка, что модуль успешно инициализируется
    assert(analytics.initialize());
    
    std::cout << "AdvancedAnalytics initialization test passed!" << std::endl;
}

void testPredictiveAnalytics() {
    std::cout << "Testing Predictive Analytics..." << std::endl;
    
    NeuroSync::Analytics::AdvancedAnalytics analytics;
    analytics.initialize();
    
    // Створення тестових даних
    // Create test data
    // Создание тестовых данных
    NeuroSync::Analytics::AnalyticsData data;
    data.dataSource = "Test Data";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);
    
    // Додавання тестових метрик
    // Add test metrics
    // Добавление тестовых метрик
    for (int i = 0; i < 3; ++i) {
        std::vector<double> values;
        for (int j = 0; j < 5; ++j) {
            values.push_back(dis(gen));
        }
        data.metrics["test_metric_" + std::to_string(i)] = values;
    }
    
    // Виконання прогнозної аналітики
    // Perform predictive analytics
    // Выполнение прогнозной аналитики
    auto result = analytics.performAnalytics(data, NeuroSync::Analytics::AnalyticsType::PREDICTIVE);
    
    // Перевірка результатів
    // Check results
    // Проверка результатов
    assert(result.success);
    assert(result.confidence > 0.0);
    assert(result.processingTime >= 0);
    
    std::cout << "Predictive Analytics test passed!" << std::endl;
}

void testAnomalyDetection() {
    std::cout << "Testing Anomaly Detection..." << std::endl;
    
    NeuroSync::Analytics::AdvancedAnalytics analytics;
    analytics.initialize();
    
    // Створення тестових даних з аномаліями
    // Create test data with anomalies
    // Создание тестовых данных с аномалиями
    std::vector<std::vector<double>> testData = {
        {1.0, 2.0, 3.0, 4.0, 5.0},           // Нормальні дані / Normal data / Нормальные данные
        {10.0, 20.0, 30.0, 40.0, 500.0}      // Дані з аномалією / Data with anomaly / Данные с аномалией
    };
    
    // Виконання виявлення аномалій
    // Perform anomaly detection
    // Выполнение обнаружения аномалий
    auto anomalies = analytics.detectAnomalies(testData);
    
    // Перевірка, що аномалії виявлено
    // Check that anomalies are detected
    // Проверка, что аномалии обнаружены
    assert(!anomalies.empty());
    
    std::cout << "Anomaly Detection test passed!" << std::endl;
}

void testDataVisualization() {
    std::cout << "Testing Data Visualization..." << std::endl;
    
    NeuroSync::Analytics::AdvancedAnalytics analytics;
    analytics.initialize();
    
    // Створення тестових даних
    // Create test data
    // Создание тестовых данных
    NeuroSync::Analytics::AnalyticsData data;
    data.dataSource = "Visualization Test Data";
    
    std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
    data.metrics["test_values"] = values;
    
    // Виконання візуалізації
    // Perform visualization
    // Выполнение визуализации
    bool success = analytics.visualizeData(data, "test_visualization.txt");
    
    // Перевірка успішності візуалізації
    // Check visualization success
    // Проверка успешности визуализации
    assert(success);
    
    std::cout << "Data Visualization test passed!" << std::endl;
}

void testResultsExport() {
    std::cout << "Testing Results Export..." << std::endl;
    
    NeuroSync::Analytics::AdvancedAnalytics analytics;
    analytics.initialize();
    
    // Створення тестових результатів
    // Create test results
    // Создание тестовых результатов
    NeuroSync::Analytics::AnalyticsResult result;
    result.success = true;
    result.confidence = 0.95;
    result.processingTime = 100;
    result.predictions["test_prediction"] = 0.75;
    result.recommendations["test_recommendation"] = "Increase parameter";
    result.insights.push_back("Test insight");
    
    // Експорт результатів
    // Export results
    // Экспорт результатов
    bool success = analytics.exportResults(result, "test_results.txt");
    
    // Перевірка успішності експорту
    // Check export success
    // Проверка успешности экспорта
    assert(success);
    
    std::cout << "Results Export test passed!" << std::endl;
}

void testStatistics() {
    std::cout << "Testing Statistics..." << std::endl;
    
    NeuroSync::Analytics::AdvancedAnalytics analytics;
    analytics.initialize();
    
    // Отримання початкової статистики
    // Get initial statistics
    // Получение начальной статистики
    auto initialStats = analytics.getStatistics();
    
    // Створення тестових даних
    // Create test data
    // Создание тестовых данных
    NeuroSync::Analytics::AnalyticsData data;
    data.dataSource = "Statistics Test Data";
    
    std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
    data.metrics["test_values"] = values;
    
    // Виконання аналітики
    // Perform analytics
    // Выполнение аналитики
    analytics.performAnalytics(data, NeuroSync::Analytics::AnalyticsType::PREDICTIVE);
    
    // Отримання оновленої статистики
    // Get updated statistics
    // Получение обновленной статистики
    auto updatedStats = analytics.getStatistics();
    
    // Перевірка, що статистика оновлена
    // Check that statistics are updated
    // Проверка, что статистика обновлена
    assert(updatedStats.totalAnalysesPerformed > initialStats.totalAnalysesPerformed);
    assert(updatedStats.totalDataPointsProcessed > initialStats.totalDataPointsProcessed);
    
    std::cout << "Statistics test passed!" << std::endl;
}

int main() {
    std::cout << "=== Advanced Analytics Tests ===" << std::endl;
    
    try {
        testAdvancedAnalyticsInitialization();
        testPredictiveAnalytics();
        testAnomalyDetection();
        testDataVisualization();
        testResultsExport();
        testStatistics();
        
        std::cout << "\nAll Advanced Analytics tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}