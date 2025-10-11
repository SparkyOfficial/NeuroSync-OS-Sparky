#include "RealTimeAnalytics.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <numeric>
#include <cmath>

// RealTimeAnalytics.cpp
// Реалізація аналітика в реальному часі для NeuroSync OS Sparky
// Implementation of real-time analytics for NeuroSync OS Sparky
// Реализация аналитика в реальном времени для NeuroSync OS Sparky

namespace NeuroSync {
namespace Analytics {

    // Конструктор аналітика в реальному часі
    // Real-time analytics constructor
    // Конструктор аналитика в реальном времени
    RealTimeAnalytics::RealTimeAnalytics() 
        : isRunning(false) {
        // Ініціалізація компонентів
        // Initialize components
        // Инициализация компонентов
    }

    // Деструктор аналітика в реальному часі
    // Real-time analytics destructor
    // Деструктор аналитика в реальном времени
    RealTimeAnalytics::~RealTimeAnalytics() {
        stopAnalytics();
        
        if (analyticsThread.joinable()) {
            analyticsThread.join();
        }
    }

    // Ініціалізація аналітика
    // Initialize analytics
    // Инициализация аналитика
    bool RealTimeAnalytics::initialize(const AnalyticsConfig& config) {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        configuration = config;
        
        // Ініціалізація компонентів
        // Initialize components
        // Инициализация компонентов
        profiler = std::make_unique<Diagnostics::Profiler>();
        scheduler = std::make_unique<Core::Scheduler>();
        memoryCore = std::make_unique<Memory::MemoryCore>();
        logger = std::make_unique<Logging::LoggingSystem>();
        
        // Ініціалізація компонентів
        // Initialize components
        // Инициализация компонентов
        if (profiler) {
            profiler->begin("RealTimeAnalyticsInitialization");
        }
        
        if (scheduler) {
            scheduler->initialize();
        }
        
        if (memoryCore) {
            memoryCore->initialize();
        }
        
        if (logger) {
            logger->initialize();
            logger->setLogLevel(Logging::LogLevel::LOG_INFO);
        }
        
        // Ініціалізація історичних даних для кожного типу аналітики
        // Initialize historical data for each analytics type
        // Инициализация исторических данных для каждого типа аналитики
        for (const auto& type : configuration.enabledAnalytics) {
            historicalData[type] = std::vector<double>();
            historicalData[type].reserve(1000); // Резервування місця / Reserve space / Резервирование места
        }
        
        if (logger) {
            logger->info("Analytics", "RealTimeAnalytics initialized successfully");
        }
        
        return true;
    }

    // Додати спостерігача
    // Add observer
    // Добавить наблюдателя
    void RealTimeAnalytics::addObserver(std::shared_ptr<AnalyticsObserver> observer) {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        if (observer) {
            observers.push_back(observer);
            if (logger) {
                logger->info("Analytics", "Observer added to RealTimeAnalytics");
            }
        }
    }

    // Видалити спостерігача
    // Remove observer
    // Удалить наблюдателя
    void RealTimeAnalytics::removeObserver(std::shared_ptr<AnalyticsObserver> observer) {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        if (observer) {
            observers.erase(
                std::remove(observers.begin(), observers.end(), observer), 
                observers.end()
            );
            if (logger) {
                logger->info("Analytics", "Observer removed from RealTimeAnalytics");
            }
        }
    }

    // Запустити аналітик
    // Start analytics
    // Запустить аналитик
    bool RealTimeAnalytics::startAnalytics() {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        if (isRunning) {
            if (logger) {
                logger->warning("Analytics", "Analytics is already running");
            }
            return false;
        }
        
        isRunning = true;
        
        // Запуск потоку аналітики
        // Start analytics thread
        // Запуск потока аналитики
        analyticsThread = std::thread(&RealTimeAnalytics::analyticsLoop, this);
        
        if (logger) {
            logger->info("Analytics", "RealTimeAnalytics started successfully");
        }
        
        return true;
    }

    // Зупинити аналітик
    // Stop analytics
    // Остановить аналитик
    void RealTimeAnalytics::stopAnalytics() {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        isRunning = false;
        
        if (logger) {
            logger->info("Analytics", "RealTimeAnalytics stopped");
        }
    }

    // Додати дані для аналізу
    // Add data for analysis
    // Добавить данные для анализа
    void RealTimeAnalytics::addData(const AnalyticsData& data) {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        // Додавання даних до відповідної черги
        // Add data to appropriate queue
        // Добавление данных в соответствующую очередь
        dataQueues[data.type].push(data);
        
        // Додавання значення до історичних даних
        // Add value to historical data
        // Добавление значения в исторические данные
        if (historicalData.find(data.type) != historicalData.end()) {
            historicalData[data.type].push_back(data.value);
            
            // Обмеження розміру історичних даних
            // Limit historical data size
            // Ограничение размера исторических данных
            if (historicalData[data.type].size() > 10000) {
                historicalData[data.type].erase(historicalData[data.type].begin());
            }
        }
        
        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        statistics.totalDataPoints++;
        statistics.dataPointsByType[data.type]++;
        
        if (logger && statistics.totalDataPoints % 1000 == 0) {
            logger->info("Analytics", "Added data point. Total: " + std::to_string(statistics.totalDataPoints));
        }
    }

    // Отримати останні дані
    // Get recent data
    // Получить последние данные
    std::vector<AnalyticsData> RealTimeAnalytics::getRecentData(AnalyticsType type, int count) const {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        std::vector<AnalyticsData> recentData;
        
        // Для демонстрації повертаємо останні дані з черги
        // For demonstration, return recent data from queue
        // Для демонстрации возвращаем последние данные из очереди
        auto it = dataQueues.find(type);
        if (it != dataQueues.end()) {
            std::queue<AnalyticsData> tempQueue = it->second;
            int itemsToCopy = std::min(count, static_cast<int>(tempQueue.size()));
            
            // Копіювання останніх елементів
            // Copy last items
            // Копирование последних элементов
            std::vector<AnalyticsData> tempVector;
            while (!tempQueue.empty()) {
                tempVector.push_back(tempQueue.front());
                tempQueue.pop();
            }
            
            // Вибір останніх 'count' елементів
            // Select last 'count' items
            // Выбор последних 'count' элементов
            int startIdx = std::max(0, static_cast<int>(tempVector.size()) - count);
            for (int i = startIdx; i < static_cast<int>(tempVector.size()); ++i) {
                recentData.push_back(tempVector[i]);
            }
        }
        
        return recentData;
    }

    // Отримати активні сповіщення
    // Get active alerts
    // Получить активные уведомления
    std::vector<Alert> RealTimeAnalytics::getActiveAlerts() const {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        std::vector<Alert> activeAlerts;
        
        // Фільтрація непідтверджених сповіщень
        // Filter unacknowledged alerts
        // Фильтрация неподтвержденных уведомлений
        for (const auto& pair : alerts) {
            if (!pair.second.acknowledged) {
                activeAlerts.push_back(pair.second);
            }
        }
        
        // Сортування за часовою міткою (найновіші першими)
        // Sort by timestamp (newest first)
        // Сортировка по временной метке (новейшие первыми)
        std::sort(activeAlerts.begin(), activeAlerts.end(), 
                 [](const Alert& a, const Alert& b) {
                     return a.timestamp > b.timestamp;
                 });
        
        return activeAlerts;
    }

    // Підтвердити сповіщення
    // Acknowledge alert
    // Подтвердить уведомление
    bool RealTimeAnalytics::acknowledgeAlert(const std::string& alertId) {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        auto it = alerts.find(alertId);
        if (it != alerts.end()) {
            it->second.acknowledged = true;
            statistics.activeAlerts = std::max(0LL, static_cast<long long>(statistics.activeAlerts) - 1);
            
            if (logger) {
                logger->info("Analytics", "Alert acknowledged: " + alertId);
            }
            
            return true;
        }
        
        if (logger) {
            logger->warning("Analytics", "Alert not found for acknowledgment: " + alertId);
        }
        
        return false;
    }

    // Отримати статистику
    // Get statistics
    // Получить статистику
    AnalyticsStats RealTimeAnalytics::getStatistics() const {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        return statistics;
    }

    // Отримати конфігурацію
    // Get configuration
    // Получить конфигурацию
    AnalyticsConfig RealTimeAnalytics::getConfiguration() const {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        return configuration;
    }

    // Встановити поріг сповіщень
    // Set alert threshold
    // Установить порог уведомлений
    void RealTimeAnalytics::setAlertThreshold(int threshold) {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        configuration.alertThreshold = threshold;
        
        if (logger) {
            logger->info("Analytics", "Alert threshold set to: " + std::to_string(threshold));
        }
    }

    // Встановити інтервал вибірки
    // Set sampling interval
    // Установить интервал выборки
    void RealTimeAnalytics::setSamplingInterval(int interval) {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        configuration.samplingInterval = interval;
        
        if (logger) {
            logger->info("Analytics", "Sampling interval set to: " + std::to_string(interval) + " ms");
        }
    }

    // Перевірити з'єднання
    // Check connection
    // Проверить соединение
    bool RealTimeAnalytics::isConnected() const {
        std::lock_guard<std::mutex> lock(analyticsMutex);
        
        // У реальній реалізації тут би була перевірка з'єднання
        // In real implementation, there would be connection check
        // В реальной реализации здесь была бы проверка соединения
        
        // Для демонстрації повертаємо true, якщо компоненти ініціалізовані
        // For demonstration, return true if components are initialized
        // Для демонстрации возвращаем true, если компоненты инициализированы
        return profiler != nullptr && scheduler != nullptr && memoryCore != nullptr;
    }

    // Цикл аналітики
    // Analytics loop
    // Цикл аналитики
    void RealTimeAnalytics::analyticsLoop() {
        while (isRunning) {
            auto startTime = std::chrono::high_resolution_clock::now();
            
            // Збір даних аналітики
            // Collect analytics data
            // Сбор данных аналитики
            collectAnalyticsData();
            
            // Обробка даних аналітики
            // Process analytics data
            // Обработка данных аналитики
            processAnalyticsData();
            
            // Виявлення аномалій
            // Detect anomalies
            // Обнаружение аномалий
            detectAnomalies();
            
            // Генерація сповіщень
            // Generate alerts
            // Генерация уведомлений
            generateAlerts();
            
            // Оновлення статистики
            // Update statistics
            // Обновление статистики
            updateStatistics();
            
            // Очищення старих даних
            // Cleanup old data
            // Очистка старых данных
            cleanupOldData();
            
            auto endTime = std::chrono::high_resolution_clock::now();
            auto processingTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            
            // Оновлення середнього часу обробки
            // Update average processing time
            // Обновление среднего времени обработки
            statistics.averageProcessingTime = (statistics.averageProcessingTime * 0.9) + (processingTime * 0.1);
            
            // Очікування перед наступною ітерацією
            // Wait before next iteration
            // Ожидание перед следующей итерацией
            std::this_thread::sleep_for(std::chrono::milliseconds(configuration.samplingInterval));
        }
    }

    // Збір даних аналітики
    // Collect analytics data
    // Сбор данных аналитики
    void RealTimeAnalytics::collectAnalyticsData() {
        // У реальній реалізації тут би був збір справжніх даних
        // In real implementation, there would be collection of real data
        // В реальной реализации здесь был бы сбор настоящих данных
        
        // Для демонстрації генеруємо синтетичні дані
        // For demonstration, generate synthetic data
        // Для демонстрации генерируем синтетические данные
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dis(0.0, 100.0);
        
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        
        // Генерація даних для різних типів аналітики
        // Generate data for different analytics types
        // Генерация данных для разных типов аналитики
        for (const auto& type : configuration.enabledAnalytics) {
            AnalyticsData data;
            data.type = type;
            data.value = dis(gen);
            data.timestamp = timestamp;
            
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
            
            addData(data);
            notifyAnalyticsData(data);
        }
    }

    // Обробка даних аналітики
    // Process analytics data
    // Обработка данных аналитики
    void RealTimeAnalytics::processAnalyticsData() {
        // У реальній реалізації тут би була обробка даних
        // In real implementation, there would be data processing
        // В реальной реализации здесь была бы обработка данных
        
        // Для демонстрації просто логуємо обробку
        // For demonstration, just log processing
        // Для демонстрации просто логируем обработку
        if (logger && statistics.totalDataPoints % 5000 == 0) {
            logger->info("Analytics", "Processed analytics data. Total points: " + std::to_string(statistics.totalDataPoints));
        }
    }

    // Виявлення аномалій
    // Detect anomalies
    // Обнаружение аномалий
    void RealTimeAnalytics::detectAnomalies() {
        if (!configuration.enableAnomalyDetection) {
            return;
        }
        
        // У реальній реалізації тут би було виявлення аномалій
        // In real implementation, there would be anomaly detection
        // В реальной реализации здесь было бы обнаружение аномалий
        
        // Для демонстрації імітуємо виявлення аномалій
        // For demonstration, simulate anomaly detection
        // Для демонстрации имитируем обнаружение аномалий
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dis(0.0, 1.0);
        
        for (const auto& pair : dataQueues) {
            const auto& queue = pair.second;
            if (!queue.empty()) {
                const AnalyticsData& latestData = queue.back();
                
                // Імітація виявлення аномалій (1% ймовірність)
                // Simulate anomaly detection (1% probability)
                // Имитация обнаружения аномалий (1% вероятность)
                if (dis(gen) < 0.01) {
                    double deviation = dis(gen) * 5.0; // Випадкове відхилення / Random deviation / Случайное отклонение
                    notifyAnomalyDetected(latestData, deviation);
                    statistics.anomaliesDetected++;
                    
                    if (logger) {
                        logger->warning("Analytics", "Anomaly detected in " + latestData.metricName + 
                                       " with deviation: " + std::to_string(deviation));
                    }
                }
            }
        }
    }

    // Генерація сповіщень
    // Generate alerts
    // Генерация уведомлений
    void RealTimeAnalytics::generateAlerts() {
        // У реальній реалізації тут би була генерація справжніх сповіщень
        // In real implementation, there would be generation of real alerts
        // В реальной реализации здесь была бы генерация настоящих уведомлений
        
        // Для демонстрації імітуємо генерацію сповіщень
        // For demonstration, simulate alert generation
        // Для демонстрации имитируем генерацию уведомлений
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dis(0.0, 100.0);
        
        // Генерація сповіщень на основі поточних даних
        // Generate alerts based on current data
        // Генерация уведомлений на основе текущих данных
        for (const auto& pair : dataQueues) {
            const auto& queue = pair.second;
            if (!queue.empty()) {
                const AnalyticsData& latestData = queue.back();
                
                // Перевірка порогу для генерації сповіщення
                // Check threshold for alert generation
                // Проверка порога для генерации уведомления
                if (latestData.value > configuration.alertThreshold) {
                    // Обмеження кількості сповіщень на хвилину
                    // Limit alerts per minute
                    // Ограничение количества уведомлений в минуту
                    static auto lastAlertTime = std::chrono::steady_clock::now();
                    auto now = std::chrono::steady_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - lastAlertTime).count();
                    
                    if (elapsed >= 1 || statistics.totalAlerts < configuration.maxAlertsPerMinute) {
                        SeverityLevel severity = latestData.value > 90 ? SeverityLevel::CRITICAL : 
                                                latestData.value > 85 ? SeverityLevel::ERROR : 
                                                SeverityLevel::WARNING;
                        
                        Alert alert = createAlert(
                            latestData.type,
                            severity,
                            "High " + latestData.metricName + " detected: " + std::to_string(latestData.value) + "%",
                            latestData.metricName,
                            latestData.value,
                            configuration.alertThreshold
                        );
                        
                        alerts[alert.alertId] = alert;
                        statistics.totalAlerts++;
                        statistics.activeAlerts++;
                        statistics.alertsBySeverity[severity]++;
                        
                        notifyAlert(alert);
                        lastAlertTime = now;
                        
                        if (logger) {
                            logger->warning("Analytics", "Alert generated: " + alert.message);
                        }
                    }
                }
            }
        }
    }

    // Оновлення статистики
    // Update statistics
    // Обновление статистики
    void RealTimeAnalytics::updateStatistics() {
        statistics.lastProcessedTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        
        notifyAnalyticsStatsUpdated(statistics);
    }

    // Очищення старих даних
    // Cleanup old data
    // Очистка старых данных
    void RealTimeAnalytics::cleanupOldData() {
        auto now = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        
        // Видалення старих сповіщень
        // Remove old alerts
        // Удаление старых уведомлений
        auto it = alerts.begin();
        while (it != alerts.end()) {
            auto alertTime = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::milliseconds(it->second.timestamp)).count();
            
            if (now - alertTime > configuration.dataRetentionPeriod) {
                if (!it->second.acknowledged) {
                    statistics.activeAlerts = std::max(0LL, static_cast<long long>(statistics.activeAlerts) - 1);
                }
                it = alerts.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Сповіщення про нові дані аналітики
    // Notify about new analytics data
    // Уведомление о новых данных аналитики
    void RealTimeAnalytics::notifyAnalyticsData(const AnalyticsData& data) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        analyticsMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onAnalyticsData(data);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        analyticsMutex.lock();
    }

    // Сповіщення про нове сповіщення
    // Notify about new alert
    // Уведомление о новом уведомлении
    void RealTimeAnalytics::notifyAlert(const Alert& alert) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        analyticsMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onAlert(alert);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        analyticsMutex.lock();
    }

    // Сповіщення про статистику аналітики
    // Notify about analytics statistics
    // Уведомление о статистике аналитики
    void RealTimeAnalytics::notifyAnalyticsStatsUpdated(const AnalyticsStats& stats) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        analyticsMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onAnalyticsStatsUpdated(stats);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        analyticsMutex.lock();
    }

    // Сповіщення про виявлення аномалії
    // Notify about anomaly detection
    // Уведомление об обнаружении аномалии
    void RealTimeAnalytics::notifyAnomalyDetected(const AnalyticsData& data, double deviation) {
        // Створення копії спостерігачів для безпечного ітерування
        // Create a copy of observers for safe iteration
        // Создание копии наблюдателей для безопасной итерации
        auto observersCopy = observers;
        
        // Розблокування м'ютекса перед викликом спостерігачів
        // Unlock mutex before calling observers
        // Разблокировка мьютекса перед вызовом наблюдателей
        analyticsMutex.unlock();
        
        for (const auto& observer : observersCopy) {
            if (observer) {
                observer->onAnomalyDetected(data, deviation);
            }
        }
        
        // Заблокування м'ютекса знову
        // Lock mutex again
        // Блокировка мьютекса снова
        analyticsMutex.lock();
    }

    // Генерація ID сповіщення
    // Generate alert ID
    // Генерация ID уведомления
    std::string RealTimeAnalytics::generateAlertId() {
        // Генерація випадкового ID
        // Generate random ID
        // Генерация случайного ID
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100000, 999999);
        
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        
        return "alert_" + std::to_string(dis(gen)) + "_" + std::to_string(timestamp % 1000000);
    }

    // Обчислення ковзного середнього
    // Calculate moving average
    // Вычисление скользящего среднего
    double RealTimeAnalytics::calculateMovingAverage(const std::vector<double>& data, size_t windowSize) {
        if (data.empty() || windowSize == 0) {
            return 0.0;
        }
        
        size_t actualWindowSize = std::min(windowSize, data.size());
        double sum = std::accumulate(data.end() - actualWindowSize, data.end(), 0.0);
        return sum / actualWindowSize;
    }

    // Обчислення стандартного відхилення
    // Calculate standard deviation
    // Вычисление стандартного отклонения
    double RealTimeAnalytics::calculateStandardDeviation(const std::vector<double>& data) {
        if (data.empty()) {
            return 0.0;
        }
        
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        double sqSum = std::accumulate(data.begin(), data.end(), 0.0,
                                      [mean](double sum, double value) {
                                          return sum + (value - mean) * (value - mean);
                                      });
        return std::sqrt(sqSum / data.size());
    }

    // Перевірка, чи є значення аномалією
    // Check if value is an anomaly
    // Проверка, является ли значение аномалией
    bool RealTimeAnalytics::isAnomaly(double value, const std::vector<double>& historicalData) {
        if (historicalData.empty()) {
            return false;
        }
        
        double mean = std::accumulate(historicalData.begin(), historicalData.end(), 0.0) / historicalData.size();
        double stdDev = calculateStandardDeviation(historicalData);
        
        // Виявлення аномалії на основі стандартного відхилення
        // Anomaly detection based on standard deviation
        // Обнаружение аномалии на основе стандартного отклонения
        double deviation = std::abs(value - mean);
        return deviation > (configuration.anomalyThreshold * stdDev);
    }

    // Створення сповіщення
    // Create alert
    // Создание уведомления
    Alert RealTimeAnalytics::createAlert(AnalyticsType type, SeverityLevel severity, const std::string& message,
                                       const std::string& metricName, double currentValue, double threshold) {
        Alert alert;
        alert.alertId = generateAlertId();
        alert.type = type;
        alert.severity = severity;
        alert.message = message;
        alert.metricName = metricName;
        alert.currentValue = currentValue;
        alert.threshold = threshold;
        alert.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        alert.acknowledged = false;
        
        return alert;
    }

} // namespace Analytics
} // namespace NeuroSync