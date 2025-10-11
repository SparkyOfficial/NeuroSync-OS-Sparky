#ifndef REAL_TIME_ANALYTICS_H
#define REAL_TIME_ANALYTICS_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <algorithm>
#include "../diagnostics/Profiler.h"
#include "../core/Scheduler.h"
#include "../memory/MemoryCore.h"
#include "../logging/LoggingSystem.h"

// RealTimeAnalytics.h
// Аналітика в реальному часі для NeuroSync OS Sparky
// Real-time analytics for NeuroSync OS Sparky
// Аналитика в реальном времени для NeuroSync OS Sparky

namespace NeuroSync {
namespace Analytics {

    // Типи аналітики
    // Analytics types
    // Типы аналитики
    enum class AnalyticsType {
        PERFORMANCE,        // Аналіз продуктивності / Performance analysis / Анализ производительности
        MEMORY,            // Аналіз пам'яті / Memory analysis / Анализ памяти
        NETWORK,           // Аналіз мережі / Network analysis / Анализ сети
        NEURON_ACTIVITY,   // Аналіз активності нейронів / Neuron activity analysis / Анализ активности нейронов
        SYSTEM_HEALTH      // Аналіз стану системи / System health analysis / Анализ состояния системы
    };

    // Рівні серйозності
    // Severity levels
    // Уровни серьезности
    enum class SeverityLevel {
        INFO,               // Інформація / Information / Информация
        WARNING,            // Попередження / Warning / Предупреждение
        ERROR,              // Помилка / Error / Ошибка
        CRITICAL            // Критично / Critical / Критично
    };

    // Конфігурація аналітики
    // Analytics configuration
    // Конфигурация аналитики
    struct AnalyticsConfig {
        int samplingInterval;                       // Інтервал вибірки (мс) / Sampling interval (ms) / Интервал выборки (мс)
        int alertThreshold;                        // Поріг сповіщень / Alert threshold / Порог уведомлений
        bool enableRealTimeProcessing;              // Увімкнути обробку в реальному часі / Enable real-time processing / Включить обработку в реальном времени
        int dataRetentionPeriod;                   // Період зберігання даних (секунди) / Data retention period (seconds) / Период хранения данных (секунды)
        int maxAlertsPerMinute;                    // Максимум сповіщень на хвилину / Max alerts per minute / Максимум уведомлений в минуту
        bool enableAnomalyDetection;                // Увімкнути виявлення аномалій / Enable anomaly detection / Включить обнаружение аномалий
        double anomalyThreshold;                    // Поріг аномалій / Anomaly threshold / Порог аномалий
        std::vector<AnalyticsType> enabledAnalytics; // Увімкнені типи аналітики / Enabled analytics types / Включенные типы аналитики
        
        AnalyticsConfig() 
            : samplingInterval(1000), alertThreshold(80), enableRealTimeProcessing(true),
              dataRetentionPeriod(3600), maxAlertsPerMinute(10), enableAnomalyDetection(true),
              anomalyThreshold(2.0) {}
    };

    // Дані аналітики
    // Analytics data
    // Данные аналитики
    struct AnalyticsData {
        AnalyticsType type;                         // Тип аналітики / Analytics type / Тип аналитики
        std::string metricName;                     // Назва метрики / Metric name / Название метрики
        double value;                               // Значення / Value / Значение
        long long timestamp;                        // Часова мітка / Timestamp / Временная метка
        std::map<std::string, std::string> metadata; // Метадані / Metadata / Метаданные
        
        AnalyticsData() : type(AnalyticsType::PERFORMANCE), value(0.0), timestamp(0) {}
    };

    // Сповіщення
    // Alert
    // Уведомление
    struct Alert {
        std::string alertId;                        // ID сповіщення / Alert ID / ID уведомления
        AnalyticsType type;                        // Тип аналітики / Analytics type / Тип аналитики
        SeverityLevel severity;                     // Рівень серйозності / Severity level / Уровень серьезности
        std::string message;                        // Повідомлення / Message / Сообщение
        std::string metricName;                     // Назва метрики / Metric name / Название метрики
        double currentValue;                        // Поточне значення / Current value / Текущее значение
        double threshold;                           // Поріг / Threshold / Порог
        long long timestamp;                        // Часова мітка / Timestamp / Временная метка
        bool acknowledged;                          // Підтверджено / Acknowledged / Подтверждено
        std::map<std::string, std::string> metadata; // Метадані / Metadata / Метаданные
        
        Alert() : type(AnalyticsType::PERFORMANCE), severity(SeverityLevel::INFO), 
                 currentValue(0.0), threshold(0.0), timestamp(0), acknowledged(false) {}
    };

    // Статистика аналітики
    // Analytics statistics
    // Статистика аналитики
    struct AnalyticsStats {
        size_t totalDataPoints;                     // Загальна кількість точок даних / Total data points / Общее количество точек данных
        size_t totalAlerts;                         // Загальна кількість сповіщень / Total alerts / Общее количество уведомлений
        size_t activeAlerts;                        // Активні сповіщення / Active alerts / Активные уведомления
        std::map<AnalyticsType, size_t> dataPointsByType; // Точки даних за типом / Data points by type / Точки данных по типам
        std::map<SeverityLevel, size_t> alertsBySeverity; // Сповіщення за серйозністю / Alerts by severity / Уведомления по серьезности
        double averageProcessingTime;               // Середній час обробки / Average processing time / Среднее время обработки
        long long lastProcessedTimestamp;          // Остання обробка / Last processed / Последняя обработка
        size_t anomaliesDetected;                   // Виявлено аномалій / Anomalies detected / Обнаружено аномалий
        
        AnalyticsStats() 
            : totalDataPoints(0), totalAlerts(0), activeAlerts(0), 
              averageProcessingTime(0.0), lastProcessedTimestamp(0), anomaliesDetected(0) {}
    };

    // Інтерфейс спостерігача за аналітикою
    // Analytics observer interface
    // Интерфейс наблюдателя за аналитикой
    class AnalyticsObserver {
    public:
        virtual ~AnalyticsObserver() = default;
        
        // Сповіщення про нові дані аналітики
        // New analytics data notification
        // Уведомление о новых данных аналитики
        virtual void onAnalyticsData(const AnalyticsData& data) = 0;
        
        // Сповіщення про нове сповіщення
        // New alert notification
        // Уведомление о новом уведомлении
        virtual void onAlert(const Alert& alert) = 0;
        
        // Сповіщення про статистику аналітики
        // Analytics statistics notification
        // Уведомление о статистике аналитики
        virtual void onAnalyticsStatsUpdated(const AnalyticsStats& stats) = 0;
        
        // Сповіщення про виявлення аномалії
        // Anomaly detection notification
        // Уведомление об обнаружении аномалии
        virtual void onAnomalyDetected(const AnalyticsData& data, double deviation) = 0;
    };

    // Аналітик в реальному часі
    // Real-time analytics
    // Аналитик в реальном времени
    class RealTimeAnalytics {
    public:
        RealTimeAnalytics();
        ~RealTimeAnalytics();
        
        // Ініціалізація аналітика
        // Initialize analytics
        // Инициализация аналитика
        bool initialize(const AnalyticsConfig& config = AnalyticsConfig());
        
        // Додати спостерігача
        // Add observer
        // Добавить наблюдателя
        void addObserver(std::shared_ptr<AnalyticsObserver> observer);
        
        // Видалити спостерігача
        // Remove observer
        // Удалить наблюдателя
        void removeObserver(std::shared_ptr<AnalyticsObserver> observer);
        
        // Запустити аналітик
        // Start analytics
        // Запустить аналитик
        bool startAnalytics();
        
        // Зупинити аналітик
        // Stop analytics
        // Остановить аналитик
        void stopAnalytics();
        
        // Додати дані для аналізу
        // Add data for analysis
        // Добавить данные для анализа
        void addData(const AnalyticsData& data);
        
        // Отримати останні дані
        // Get recent data
        // Получить последние данные
        std::vector<AnalyticsData> getRecentData(AnalyticsType type, int count = 100) const;
        
        // Отримати активні сповіщення
        // Get active alerts
        // Получить активные уведомления
        std::vector<Alert> getActiveAlerts() const;
        
        // Підтвердити сповіщення
        // Acknowledge alert
        // Подтвердить уведомление
        bool acknowledgeAlert(const std::string& alertId);
        
        // Отримати статистику
        // Get statistics
        // Получить статистику
        AnalyticsStats getStatistics() const;
        
        // Отримати конфігурацію
        // Get configuration
        // Получить конфигурацию
        AnalyticsConfig getConfiguration() const;
        
        // Встановити поріг сповіщень
        // Set alert threshold
        // Установить порог уведомлений
        void setAlertThreshold(int threshold);
        
        // Встановити інтервал вибірки
        // Set sampling interval
        // Установить интервал выборки
        void setSamplingInterval(int interval);
        
        // Перевірити з'єднання
        // Check connection
        // Проверить соединение
        bool isConnected() const;
        
    private:
        AnalyticsConfig configuration;                          // Конфігурація / Configuration / Конфигурация
        mutable std::mutex analyticsMutex;                     // М'ютекс для потокобезпеки / Mutex for thread safety / Мьютекс для потокобезопасности
        std::unique_ptr<Diagnostics::Profiler> profiler;       // Профілювальник / Profiler / Профилировщик
        std::unique_ptr<Core::Scheduler> scheduler;            // Планувальник / Scheduler / Планировщик
        std::unique_ptr<Memory::MemoryCore> memoryCore;        // Ядро пам'яті / Memory core / Ядро памяти
        std::unique_ptr<Logging::LoggingSystem> logger;        // Система логування / Logging system / Система логирования
        std::vector<std::shared_ptr<AnalyticsObserver>> observers; // Спостерігачі / Observers / Наблюдатели
        std::atomic<bool> isRunning;                           // Прапор роботи / Running flag / Флаг работы
        std::thread analyticsThread;                           // Потік аналітики / Analytics thread / Поток аналитики
        std::map<AnalyticsType, std::queue<AnalyticsData>> dataQueues; // Черги даних / Data queues / Очереди данных
        std::map<std::string, Alert> alerts;                   // Сповіщення / Alerts / Уведомления
        AnalyticsStats statistics;                             // Статистика / Statistics / Статистика
        std::map<AnalyticsType, std::vector<double>> historicalData; // Історичні дані / Historical data / Исторические данные
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void analyticsLoop();
        void collectAnalyticsData();
        void processAnalyticsData();
        void detectAnomalies();
        void generateAlerts();
        void updateStatistics();
        void cleanupOldData();
        void notifyAnalyticsData(const AnalyticsData& data);
        void notifyAlert(const Alert& alert);
        void notifyAnalyticsStatsUpdated(const AnalyticsStats& stats);
        void notifyAnomalyDetected(const AnalyticsData& data, double deviation);
        std::string generateAlertId();
        double calculateMovingAverage(const std::vector<double>& data, size_t windowSize);
        double calculateStandardDeviation(const std::vector<double>& data);
        bool isAnomaly(double value, const std::vector<double>& historicalData);
        Alert createAlert(AnalyticsType type, SeverityLevel severity, const std::string& message,
                         const std::string& metricName, double currentValue, double threshold);
    };

} // namespace Analytics
} // namespace NeuroSync

#endif // REAL_TIME_ANALYTICS_H