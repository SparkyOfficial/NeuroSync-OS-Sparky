#ifndef ADVANCED_ANALYTICS_H
#define ADVANCED_ANALYTICS_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "../neuron/NeuronManager.h"
#include "../network_neural/NeuralNetwork.h"

// AdvancedAnalytics.h
// Модуль розширеної аналітики даних для NeuroSync OS Sparky
// Advanced data analytics module for NeuroSync OS Sparky
// Модуль расширенной аналитики данных для NeuroSync OS Sparky

namespace NeuroSync {
namespace Analytics {

    // Тип аналітики
    // Analytics type
    // Тип аналитики
    enum class AnalyticsType {
        PREDICTIVE,     // Прогнозна аналітика / Predictive analytics / Прогнозная аналитика
        PRESCRIPTIVE,   // Прескриптивна аналітика / Prescriptive analytics / Прескриптивная аналитика
        DIAGNOSTIC,     // Діагностична аналітика / Diagnostic analytics / Диагностическая аналитика
        COGNITIVE,      // Когнітивна аналітика / Cognitive analytics / Когнитивная аналитика
        REALTIME        // Аналітика в реальному часі / Real-time analytics / Аналитика в реальном времени
    };

    // Структура даних для аналітики
    // Analytics data structure
    // Структура данных для аналитики
    struct AnalyticsData {
        std::map<std::string, std::vector<double>> metrics;  // Метрики / Metrics / Метрики
        std::string dataSource;                              // Джерело даних / Data source / Источник данных
        long long timestamp;                                // Часова мітка / Timestamp / Временная метка
        std::map<std::string, std::string> metadata;        // Метадані / Metadata / Метаданные
        
        AnalyticsData() : timestamp(0) {}
    };

    // Структура результатів аналітики
    // Analytics results structure
    // Структура результатов аналитики
    struct AnalyticsResult {
        std::map<std::string, double> predictions;          // Прогнози / Predictions / Прогнозы
        std::map<std::string, std::string> recommendations; // Рекомендації / Recommendations / Рекомендации
        std::vector<std::string> insights;                  // Інсайти / Insights / Инсайты
        double confidence;                                  // Рівень довіри / Confidence level / Уровень доверия
        long long processingTime;                          // Час обробки / Processing time / Время обработки
        bool success;                                       // Успішність / Success / Успех
        
        AnalyticsResult() : confidence(0.0), processingTime(0), success(true) {}
    };

    // Модуль розширеної аналітики
    // Advanced analytics module
    // Модуль расширенной аналитики
    class AdvancedAnalytics {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        AdvancedAnalytics();
        
        // Деструктор
        // Destructor
        // Деструктор
        ~AdvancedAnalytics();
        
        // Ініціалізація модуля
        // Initialize module
        // Инициализация модуля
        bool initialize();
        
        // Виконати аналітику
        // Perform analytics
        // Выполнить аналитику
        AnalyticsResult performAnalytics(const AnalyticsData& data, AnalyticsType type);
        
        // Прогнозувати
        // Predict
        // Прогнозировать
        std::map<std::string, double> predict(const std::vector<std::vector<double>>& inputData);
        
        // Рекомендувати
        // Recommend
        // Рекомендовать
        std::map<std::string, std::string> recommend(const std::map<std::string, double>& currentState);
        
        // Виявляти аномалії
        // Detect anomalies
        // Обнаруживать аномалии
        std::vector<std::string> detectAnomalies(const std::vector<std::vector<double>>& data);
        
        // Класифікувати дані
        // Classify data
        // Классифицировать данные
        std::map<std::string, std::string> classifyData(const std::vector<std::vector<double>>& data);
        
        // Кластеризувати дані
        // Cluster data
        // Кластеризовать данные
        std::map<std::string, std::vector<int>> clusterData(const std::vector<std::vector<double>>& data);
        
        // Аналізувати тенденції
        // Analyze trends
        // Анализировать тенденции
        std::vector<std::string> analyzeTrends(const std::map<std::string, std::vector<double>>& timeSeriesData);
        
        // Генерувати інсайти
        // Generate insights
        // Генерировать инсайты
        std::vector<std::string> generateInsights(const AnalyticsData& data);
        
        // Візуалізувати дані
        // Visualize data
        // Визуализировать данные
        bool visualizeData(const AnalyticsData& data, const std::string& outputPath);
        
        // Експортувати результати
        // Export results
        // Экспортировать результаты
        bool exportResults(const AnalyticsResult& result, const std::string& filePath);
        
        // Імпортувати дані
        // Import data
        // Импортировать данные
        bool importData(const std::string& filePath, AnalyticsData& data);
        
        // Отримати статистику
        // Get statistics
        // Получить статистику
        struct AnalyticsStatistics {
            size_t totalAnalysesPerformed;
            size_t totalDataPointsProcessed;
            double averageProcessingTime;
            size_t totalAnomaliesDetected;
            size_t totalInsightsGenerated;
            long long lastAnalysisTime;
        };
        
        AnalyticsStatistics getStatistics() const;
        
        // Отримати версію модуля
        // Get module version
        // Получить версию модуля
        std::string getVersion() const;
        
    private:
        std::unique_ptr<Network::NeuralNetwork> predictiveModel;  // Прогнозна модель / Predictive model / Прогнозная модель
        std::unique_ptr<Network::NeuralNetwork> classificationModel; // Модель класифікації / Classification model / Модель классификации
        std::unique_ptr<Network::NeuralNetwork> clusteringModel;     // Модель кластеризації / Clustering model / Модель кластеризации
        std::unique_ptr<NeuronManager> neuronManager;               // Менеджер нейронів / Neuron manager / Менеджер нейронов
        AnalyticsStatistics statistics;                             // Статистика / Statistics / Статистика
        bool isInitialized;                                        // Прапор ініціалізації / Initialization flag / Флаг инициализации
        std::string version;                                       // Версія модуля / Module version / Версия модуля
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void initializeModels();
        long long getCurrentTimeMillis() const;
        std::vector<double> normalizeData(const std::vector<double>& data);
        std::vector<double> denormalizeData(const std::vector<double>& data, const std::vector<double>& originalData);
        double calculateEuclideanDistance(const std::vector<double>& a, const std::vector<double>& b);
        std::vector<double> calculateCentroid(const std::vector<std::vector<double>>& cluster);
        std::map<std::string, double> calculateCorrelations(const std::map<std::string, std::vector<double>>& data);
        std::string generateReport(const AnalyticsResult& result);
    };

} // namespace Analytics
} // namespace NeuroSync

#endif // ADVANCED_ANALYTICS_H