/*
 * test_analytics.cpp
 * Тест для аналітики в реальному часі
 * Test for real-time analytics
 * Тест для аналитики в реальном времени
 */

#include "../analytics/RealTimeAnalytics.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <thread>
#include <chrono>

using namespace NeuroSync::Analytics;

// Тестова реалізація спостерігача
// Test observer implementation
// Тестовая реализация наблюдателя
class TestObserver : public AnalyticsObserver {
public:
    int analyticsDataCount = 0;
    int alertCount = 0;
    int statsUpdates = 0;
    int anomalyCount = 0;
    
    void onAnalyticsData(const AnalyticsData& data) override {
        analyticsDataCount++;
        std::cout << "[TEST] Analytics data received: " << data.metricName << std::endl;
    }
    
    void onAlert(const Alert& alert) override {
        alertCount++;
        std::cout << "[TEST] Alert received: " << alert.message << std::endl;
    }
    
    void onAnalyticsStatsUpdated(const AnalyticsStats& stats) override {
        statsUpdates++;
        std::cout << "[TEST] Stats updated. Data points: " << stats.totalDataPoints << std::endl;
    }
    
    void onAnomalyDetected(const AnalyticsData& data, double deviation) override {
        anomalyCount++;
        std::cout << "[TEST] Anomaly detected: " << data.metricName << std::endl;
    }
};

int main() {
    std::cout << "=== Running Real-time Analytics Tests ===" << std::endl;
    
    try {
        // Тест 1: Створення та ініціалізація аналітика
        // Test 1: Creating and initializing analytics
        // Тест 1: Создание и инициализация аналитика
        std::cout << "\nTest 1: Creating and initializing analytics..." << std::endl;
        
        RealTimeAnalytics analytics;
        
        AnalyticsConfig config;
        config.samplingInterval = 100; // 100 мс для тесту / 100 ms for test / 100 мс для теста
        config.alertThreshold = 90;
        config.enableRealTimeProcessing = true;
        config.dataRetentionPeriod = 60; // 1 хвилина / 1 minute / 1 минута
        config.maxAlertsPerMinute = 3;
        config.enableAnomalyDetection = true;
        config.anomalyThreshold = 1.5;
        config.enabledAnalytics = {
            AnalyticsType::PERFORMANCE,
            AnalyticsType::MEMORY,
            AnalyticsType::NETWORK
        };
        
        bool initSuccess = analytics.initialize(config);
        assert(initSuccess);
        std::cout << "Analytics initialized successfully" << std::endl;
        
        // Тест 2: Додавання спостерігача
        // Test 2: Adding observer
        // Тест 2: Добавление наблюдателя
        std::cout << "\nTest 2: Adding observer..." << std::endl;
        
        auto observer = std::make_shared<TestObserver>();
        analytics.addObserver(observer);
        std::cout << "Observer added successfully" << std::endl;
        
        // Тест 3: Отримання конфігурації
        // Test 3: Getting configuration
        // Тест 3: Получение конфигурации
        std::cout << "\nTest 3: Getting configuration..." << std::endl;
        
        AnalyticsConfig retrievedConfig = analytics.getConfiguration();
        assert(retrievedConfig.samplingInterval == 100);
        assert(retrievedConfig.alertThreshold == 90);
        std::cout << "Configuration retrieved successfully" << std::endl;
        
        // Тест 4: Запуск аналітика
        // Test 4: Starting analytics
        // Тест 4: Запуск аналитика
        std::cout << "\nTest 4: Starting analytics..." << std::endl;
        
        bool analyticsStarted = analytics.startAnalytics();
        assert(analyticsStarted);
        std::cout << "Analytics started successfully" << std::endl;
        
        // Тест 5: Додавання даних для аналізу
        // Test 5: Adding data for analysis
        // Тест 5: Добавление данных для анализа
        std::cout << "\nTest 5: Adding analytics data..." << std::endl;
        
        AnalyticsData data;
        data.type = AnalyticsType::PERFORMANCE;
        data.metricName = "CPU_Usage";
        data.value = 75.5;
        data.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        
        analytics.addData(data);
        std::cout << "Analytics data added successfully" << std::endl;
        
        // Тест 6: Додавання даних високого рівня для генерації сповіщення
        // Test 6: Adding high-level data to generate alert
        // Тест 6: Добавление данных высокого уровня для генерации уведомления
        std::cout << "\nTest 6: Adding high-level data to generate alert..." << std::endl;
        
        AnalyticsData highData;
        highData.type = AnalyticsType::MEMORY;
        highData.metricName = "Memory_Usage";
        highData.value = 95.0; // Вище порогу / Above threshold / Выше порога
        highData.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        
        analytics.addData(highData);
        std::cout << "High-level data added successfully" << std::endl;
        
        // Тест 7: Очікування обробки даних
        // Test 7: Waiting for data processing
        // Тест 7: Ожидание обработки данных
        std::cout << "\nTest 7: Waiting for data processing..." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        // Тест 8: Отримання активних сповіщень
        // Test 8: Getting active alerts
        // Тест 8: Получение активных уведомлений
        std::cout << "\nTest 8: Getting active alerts..." << std::endl;
        
        auto activeAlerts = analytics.getActiveAlerts();
        std::cout << "Active alerts count: " << activeAlerts.size() << std::endl;
        
        // Тест 9: Підтвердження сповіщення
        // Test 9: Acknowledging alert
        // Тест 9: Подтверждение уведомления
        std::cout << "\nTest 9: Acknowledging alert..." << std::endl;
        
        if (!activeAlerts.empty()) {
            bool acknowledged = analytics.acknowledgeAlert(activeAlerts[0].alertId);
            assert(acknowledged);
            std::cout << "Alert acknowledged successfully" << std::endl;
        }
        
        // Тест 10: Отримання останніх даних
        // Test 10: Getting recent data
        // Тест 10: Получение последних данных
        std::cout << "\nTest 10: Getting recent data..." << std::endl;
        
        auto recentData = analytics.getRecentData(AnalyticsType::PERFORMANCE, 5);
        std::cout << "Recent data count: " << recentData.size() << std::endl;
        
        // Тест 11: Отримання статистики
        // Test 11: Getting statistics
        // Тест 11: Получение статистики
        std::cout << "\nTest 11: Getting statistics..." << std::endl;
        
        AnalyticsStats stats = analytics.getStatistics();
        std::cout << "Statistics:" << std::endl;
        std::cout << "  Total Data Points: " << stats.totalDataPoints << std::endl;
        std::cout << "  Total Alerts: " << stats.totalAlerts << std::endl;
        std::cout << "  Active Alerts: " << stats.activeAlerts << std::endl;
        std::cout << "  Anomalies Detected: " << stats.anomaliesDetected << std::endl;
        
        // Тест 12: Перевірка спостерігача
        // Test 12: Checking observer
        // Тест 12: Проверка наблюдателя
        std::cout << "\nTest 12: Checking observer statistics..." << std::endl;
        
        std::cout << "  Analytics Data Count: " << observer->analyticsDataCount << std::endl;
        std::cout << "  Alert Count: " << observer->alertCount << std::endl;
        std::cout << "  Stats Updates: " << observer->statsUpdates << std::endl;
        std::cout << "  Anomaly Count: " << observer->anomalyCount << std::endl;
        
        // Тест 13: Зупинка аналітика
        // Test 13: Stopping analytics
        // Тест 13: Остановка аналитика
        std::cout << "\nTest 13: Stopping analytics..." << std::endl;
        
        analytics.stopAnalytics();
        std::cout << "Analytics stopped successfully" << std::endl;
        
        // Тест 14: Видалення спостерігача
        // Test 14: Removing observer
        // Тест 14: Удаление наблюдателя
        std::cout << "\nTest 14: Removing observer..." << std::endl;
        
        analytics.removeObserver(observer);
        std::cout << "Observer removed successfully" << std::endl;
        
        std::cout << "\n=== All Real-time Analytics Tests Passed! ===" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}