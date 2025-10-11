/*
 * analytics_example.cpp
 * Приклад використання аналітики в реальному часі
 * Example of using real-time analytics
 * Пример использования аналитики в реальном времени
 */

#include "../analytics/RealTimeAnalytics.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using namespace NeuroSync::Analytics;

// Реалізація спостерігача для відображення аналітики
// Observer implementation for displaying analytics
// Реализация наблюдателя для отображения аналитики
class AnalyticsObserverExample : public AnalyticsObserver {
public:
    void onAnalyticsData(const AnalyticsData& data) override {
        std::cout << "[ANALYTICS] Data received:" << std::endl;
        std::cout << "  Type: " << static_cast<int>(data.type) << std::endl;
        std::cout << "  Metric: " << data.metricName << std::endl;
        std::cout << "  Value: " << data.value << std::endl;
        std::cout << "  Timestamp: " << data.timestamp << std::endl;
        std::cout << std::endl;
    }
    
    void onAlert(const Alert& alert) override {
        std::cout << "[ALERT] " << alert.message << std::endl;
        std::cout << "  Severity: " << static_cast<int>(alert.severity) << std::endl;
        std::cout << "  Current Value: " << alert.currentValue << std::endl;
        std::cout << "  Threshold: " << alert.threshold << std::endl;
        std::cout << "  Alert ID: " << alert.alertId << std::endl;
        std::cout << std::endl;
    }
    
    void onAnalyticsStatsUpdated(const AnalyticsStats& stats) override {
        std::cout << "[STATS] Analytics statistics updated:" << std::endl;
        std::cout << "  Total Data Points: " << stats.totalDataPoints << std::endl;
        std::cout << "  Total Alerts: " << stats.totalAlerts << std::endl;
        std::cout << "  Active Alerts: " << stats.activeAlerts << std::endl;
        std::cout << "  Anomalies Detected: " << stats.anomaliesDetected << std::endl;
        std::cout << "  Average Processing Time: " << stats.averageProcessingTime << " ms" << std::endl;
        std::cout << std::endl;
    }
    
    void onAnomalyDetected(const AnalyticsData& data, double deviation) override {
        std::cout << "[ANOMALY] Anomaly detected:" << std::endl;
        std::cout << "  Metric: " << data.metricName << std::endl;
        std::cout << "  Value: " << data.value << std::endl;
        std::cout << "  Deviation: " << deviation << std::endl;
        std::cout << std::endl;
    }
};

// Симуляція даних для аналізу
// Data simulation for analysis
// Симуляция данных для анализа
void simulateAnalyticsData(RealTimeAnalytics& analytics) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 100.0);
    
    // Симуляція даних протягом 30 секунд
    // Simulate data for 30 seconds
    // Симуляция данных в течение 30 секунд
    for (int i = 0; i < 30; ++i) {
        // Генерація даних для різних типів аналітики
        // Generate data for different analytics types
        // Генерация данных для разных типов аналитики
        std::vector<AnalyticsType> types = {
            AnalyticsType::PERFORMANCE,
            AnalyticsType::MEMORY,
            AnalyticsType::NETWORK,
            AnalyticsType::NEURON_ACTIVITY,
            AnalyticsType::SYSTEM_HEALTH
        };
        
        for (const auto& type : types) {
            AnalyticsData data;
            data.type = type;
            data.value = dis(gen);
            data.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            
            switch (type) {
                case AnalyticsType::PERFORMANCE:
                    data.metricName = "CPU_Usage";
                    break;
                case AnalyticsType::MEMORY:
                    data.metricName = "Memory_Usage";
                    break;
                case AnalyticsType::NETWORK:
                    data.metricName = "Network_Latency";
                    break;
                case AnalyticsType::NEURON_ACTIVITY:
                    data.metricName = "Neuron_Activity";
                    break;
                case AnalyticsType::SYSTEM_HEALTH:
                    data.metricName = "System_Health";
                    break;
            }
            
            // Додавання даних до аналітика
            // Adding data to analytics
            // Добавление данных в аналитик
            analytics.addData(data);
        }
        
        // Очікування 1 секунду перед наступною ітерацією
        // Wait 1 second before next iteration
        // Ожидание 1 секунду перед следующей итерацией
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  NeuroSync Real-time Analytics Example" << std::endl;
    std::cout << "========================================" << std::endl;
    
    try {
        // 1. Створення аналітика в реальному часі
        // 1. Creating real-time analytics
        // 1. Создание аналитика в реальном времени
        std::cout << "\n1. Creating Real-time Analytics..." << std::endl;
        
        RealTimeAnalytics analytics;
        
        // 2. Налаштування конфігурації
        // 2. Setting up configuration
        // 2. Настройка конфигурации
        std::cout << "\n2. Setting up configuration..." << std::endl;
        
        AnalyticsConfig config;
        config.samplingInterval = 500; // 500 мс / 500 ms / 500 мс
        config.alertThreshold = 80; // 80% поріг / 80% threshold / 80% порог
        config.enableRealTimeProcessing = true;
        config.dataRetentionPeriod = 1800; // 30 хвилин / 30 minutes / 30 минут
        config.maxAlertsPerMinute = 5;
        config.enableAnomalyDetection = true;
        config.anomalyThreshold = 2.0;
        config.enabledAnalytics = {
            AnalyticsType::PERFORMANCE,
            AnalyticsType::MEMORY,
            AnalyticsType::NETWORK,
            AnalyticsType::NEURON_ACTIVITY,
            AnalyticsType::SYSTEM_HEALTH
        };
        
        // 3. Ініціалізація аналітика
        // 3. Initializing analytics
        // 3. Инициализация аналитика
        std::cout << "\n3. Initializing analytics..." << std::endl;
        
        if (!analytics.initialize(config)) {
            std::cerr << "Failed to initialize Real-time Analytics" << std::endl;
            return 1;
        }
        
        std::cout << "Real-time Analytics initialized successfully!" << std::endl;
        
        // 4. Додавання спостерігача
        // 4. Adding observer
        // 4. Добавление наблюдателя
        std::cout << "\n4. Adding analytics observer..." << std::endl;
        
        auto observer = std::make_shared<AnalyticsObserverExample>();
        analytics.addObserver(observer);
        
        std::cout << "Analytics observer added!" << std::endl;
        
        // 5. Запуск аналітика
        // 5. Starting analytics
        // 5. Запуск аналитика
        std::cout << "\n5. Starting analytics..." << std::endl;
        
        if (!analytics.startAnalytics()) {
            std::cerr << "Failed to start analytics" << std::endl;
            return 1;
        }
        
        std::cout << "Analytics started successfully!" << std::endl;
        
        // 6. Симуляція даних для аналізу
        // 6. Simulating data for analysis
        // 6. Симуляция данных для анализа
        std::cout << "\n6. Simulating analytics data..." << std::endl;
        
        // Запуск потоку для симуляції даних
        // Starting thread for data simulation
        // Запуск потока для симуляции данных
        std::thread simulationThread(simulateAnalyticsData, std::ref(analytics));
        
        // 7. Очікування завершення симуляції
        // 7. Waiting for simulation completion
        // 7. Ожидание завершения симуляции
        std::cout << "\n7. Waiting for data simulation..." << std::endl;
        
        if (simulationThread.joinable()) {
            simulationThread.join();
        }
        
        std::cout << "Data simulation completed!" << std::endl;
        
        // 8. Очікування обробки даних аналітиком
        // 8. Waiting for analytics processing
        // 8. Ожидание обработки данных аналитиком
        std::cout << "\n8. Waiting for analytics processing..." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        // 9. Відображення статистики
        // 9. Displaying statistics
        // 9. Отображение статистики
        std::cout << "\n9. Displaying analytics statistics..." << std::endl;
        
        AnalyticsStats stats = analytics.getStatistics();
        std::cout << "Analytics Statistics:" << std::endl;
        std::cout << "  Total Data Points: " << stats.totalDataPoints << std::endl;
        std::cout << "  Total Alerts: " << stats.totalAlerts << std::endl;
        std::cout << "  Active Alerts: " << stats.activeAlerts << std::endl;
        std::cout << "  Anomalies Detected: " << stats.anomaliesDetected << std::endl;
        std::cout << "  Average Processing Time: " << stats.averageProcessingTime << " ms" << std::endl;
        std::cout << "  Last Processed Timestamp: " << stats.lastProcessedTimestamp << std::endl;
        
        // 10. Відображення активних сповіщень
        // 10. Displaying active alerts
        // 10. Отображение активных уведомлений
        std::cout << "\n10. Displaying active alerts..." << std::endl;
        
        auto activeAlerts = analytics.getActiveAlerts();
        std::cout << "Active Alerts (" << activeAlerts.size() << "):" << std::endl;
        for (const auto& alert : activeAlerts) {
            std::cout << "  Alert ID: " << alert.alertId << std::endl;
            std::cout << "  Message: " << alert.message << std::endl;
            std::cout << "  Severity: " << static_cast<int>(alert.severity) << std::endl;
            std::cout << "  Metric: " << alert.metricName << std::endl;
            std::cout << "  Value: " << alert.currentValue << std::endl;
            std::cout << std::endl;
        }
        
        // 11. Підтвердження сповіщень
        // 11. Acknowledging alerts
        // 11. Подтверждение уведомлений
        std::cout << "\n11. Acknowledging alerts..." << std::endl;
        
        for (const auto& alert : activeAlerts) {
            if (analytics.acknowledgeAlert(alert.alertId)) {
                std::cout << "Alert acknowledged: " << alert.alertId << std::endl;
            }
        }
        
        // 12. Отримання останніх даних
        // 12. Getting recent data
        // 12. Получение последних данных
        std::cout << "\n12. Getting recent analytics data..." << std::endl;
        
        auto recentData = analytics.getRecentData(AnalyticsType::PERFORMANCE, 5);
        std::cout << "Recent Performance Data (" << recentData.size() << " points):" << std::endl;
        for (const auto& data : recentData) {
            std::cout << "  Metric: " << data.metricName << std::endl;
            std::cout << "  Value: " << data.value << std::endl;
            std::cout << "  Timestamp: " << data.timestamp << std::endl;
            std::cout << std::endl;
        }
        
        // 13. Зупинка аналітика
        // 13. Stopping analytics
        // 13. Остановка аналитика
        std::cout << "\n13. Stopping analytics..." << std::endl;
        
        analytics.stopAnalytics();
        
        std::cout << "Analytics stopped successfully!" << std::endl;
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "  Real-time Analytics Example Completed!" << std::endl;
        std::cout << "========================================" << std::endl;
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}