#ifndef PERFORMANCE_OPTIMIZER_H
#define PERFORMANCE_OPTIMIZER_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include "../core/Scheduler.h"
#include "../threadpool/ThreadPool.h"
#include "../memory/MemoryCore.h"
#include "../diagnostics/Profiler.h"

// PerformanceOptimizer.h
// Оптімізатор продуктивності для NeuroSync OS Sparky
// Performance optimizer for NeuroSync OS Sparky
// Оптимизатор производительности для NeuroSync OS Sparky

namespace NeuroSync {
namespace Performance {

    // Типи оптимізації
    // Optimization types
    // Типы оптимизации
    enum class OptimizationType {
        CPU,            // Оптимізація ЦП / CPU optimization / Оптимизация ЦП
        MEMORY,         // Оптимізація пам'яті / Memory optimization / Оптимизация памяти
        THREADING,      // Оптимізація потоків / Threading optimization / Оптимизация потоков
        IO,             // Оптимізація вводу-виводу / I/O optimization / Оптимизация ввода-вывода
        NETWORK,        // Оптимізація мережі / Network optimization / Оптимизация сети
        CACHE           // Оптимізація кешу / Cache optimization / Оптимизация кэша
    };

    // Стратегії оптимізації
    // Optimization strategies
    // Стратегии оптимизации
    enum class OptimizationStrategy {
        AGGRESSIVE,     // Агресивна / Aggressive / Агрессивная
        BALANCED,       // Збалансована / Balanced / Сбалансированная
        CONSERVATIVE    // Консервативна / Conservative / Консервативная
    };

    // Конфігурація оптимізатора
    // Optimizer configuration
    // Конфигурация оптимизатора
    struct OptimizerConfig {
        OptimizationStrategy strategy;           // Стратегія оптимізації / Optimization strategy / Стратегия оптимизации
        bool autoOptimization;                  // Автоматична оптимізація / Auto optimization / Автоматическая оптимизация
        int optimizationInterval;               // Інтервал оптимізації (мс) / Optimization interval (ms) / Интервал оптимизации (мс)
        double cpuThreshold;                    // Поріг завантаження ЦП / CPU load threshold / Порог загрузки ЦП
        size_t memoryThreshold;                 // Поріг використання пам'яті / Memory usage threshold / Порог использования памяти
        int threadCount;                        // Кількість потоків / Thread count / Количество потоков
        bool enableProfiling;                   // Увімкнути профілювання / Enable profiling / Включить профилирование
        
        OptimizerConfig() 
            : strategy(OptimizationStrategy::BALANCED), autoOptimization(true), 
              optimizationInterval(5000), cpuThreshold(0.8), memoryThreshold(1024 * 1024 * 100), // 100 MB
              threadCount(4), enableProfiling(true) {}
    };

    // Результати оптимізації
    // Optimization results
    // Результаты оптимизации
    struct OptimizationResults {
        std::map<OptimizationType, double> improvements;  // Покращення для кожного типу / Improvements for each type / Улучшения для каждого типа
        double overallPerformanceGain;                    // Загальний приріст продуктивності / Overall performance gain / Общий прирост производительности
        long long optimizationTime;                       // Час оптимізації / Optimization time / Время оптимизации
        std::string recommendations;                      // Рекомендації / Recommendations / Рекомендации
        std::map<std::string, std::string> metrics;       // Метрики / Metrics / Метрики
    };

    // Статистика продуктивності
    // Performance statistics
    // Статистика производительности
    struct PerformanceStats {
        double cpuUsage;                        // Використання ЦП / CPU usage / Использование ЦП
        size_t memoryUsage;                     // Використання пам'яті / Memory usage / Использование памяти
        size_t memoryAvailable;                 // Доступна пам'ять / Available memory / Доступная память
        int activeThreads;                      // Активні потоки / Active threads / Активные потоки
        int threadPoolSize;                     // Розмір пулу потоків / Thread pool size / Размер пула потоков
        size_t ioOperations;                    // Операції вводу-виводу / I/O operations / Операции ввода-вывода
        double networkLatency;                  // Затримка мережі / Network latency / Задержка сети
        size_t cacheHits;                       // Попадання в кеш / Cache hits / Попадания в кэш
        size_t cacheMisses;                     // Промахи кешу / Cache misses / Промахи кэша
        long long timestamp;                    // Часова мітка / Timestamp / Временная метка
        
        PerformanceStats() 
            : cpuUsage(0.0), memoryUsage(0), memoryAvailable(0), activeThreads(0),
              threadPoolSize(0), ioOperations(0), networkLatency(0.0), 
              cacheHits(0), cacheMisses(0), timestamp(0) {}
    };

    // Інтерфейс спостерігача за продуктивністю
    // Performance observer interface
    // Интерфейс наблюдателя за производительностью
    class PerformanceObserver {
    public:
        virtual ~PerformanceObserver() = default;
        
        // Сповіщення про зміну статистики
        // Statistics change notification
        // Уведомление об изменении статистики
        virtual void onPerformanceStatsUpdated(const PerformanceStats& stats) = 0;
        
        // Сповіщення про результати оптимізації
        // Optimization results notification
        // Уведомление о результатах оптимизации
        virtual void onOptimizationCompleted(const OptimizationResults& results) = 0;
        
        // Сповіщення про проблеми з продуктивністю
        // Performance issues notification
        // Уведомление о проблемах с производительностью
        virtual void onPerformanceIssueDetected(const std::string& issue, double severity) = 0;
    };

    // Оптимізатор продуктивності
    // Performance optimizer
    // Оптимизатор производительности
    class PerformanceOptimizer {
    public:
        PerformanceOptimizer();
        ~PerformanceOptimizer();
        
        // Ініціалізація оптимізатора
        // Initialize optimizer
        // Инициализация оптимизатора
        bool initialize(const OptimizerConfig& config = OptimizerConfig());
        
        // Додати спостерігача
        // Add observer
        // Добавить наблюдателя
        void addObserver(std::shared_ptr<PerformanceObserver> observer);
        
        // Видалити спостерігача
        // Remove observer
        // Удалить наблюдателя
        void removeObserver(std::shared_ptr<PerformanceObserver> observer);
        
        // Запустити автоматичну оптимізацію
        // Start automatic optimization
        // Запустить автоматическую оптимизацию
        bool startAutoOptimization();
        
        // Зупинити автоматичну оптимізацію
        // Stop automatic optimization
        // Остановить автоматическую оптимизацию
        void stopAutoOptimization();
        
        // Виконати оптимізацію
        // Perform optimization
        // Выполнить оптимизацию
        OptimizationResults optimize();
        
        // Оптимізувати ЦП
        // Optimize CPU
        // Оптимизировать ЦП
        double optimizeCPU();
        
        // Оптимізувати пам'ять
        // Optimize memory
        // Оптимизировать память
        double optimizeMemory();
        
        // Оптимізувати потоки
        // Optimize threads
        // Оптимизировать потоки
        double optimizeThreading();
        
        // Отримати статистику продуктивності
        // Get performance statistics
        // Получить статистику производительности
        PerformanceStats getPerformanceStats() const;
        
        // Отримати конфігурацію
        // Get configuration
        // Получить конфигурацию
        OptimizerConfig getConfiguration() const;
        
        // Встановити поріг ЦП
        // Set CPU threshold
        // Установить порог ЦП
        void setCpuThreshold(double threshold);
        
        // Встановити поріг пам'яті
        // Set memory threshold
        // Установить порог памяти
        void setMemoryThreshold(size_t threshold);
        
        // Отримати рекомендації
        // Get recommendations
        // Получить рекомендации
        std::string getRecommendations() const;
        
    private:
        OptimizerConfig configuration;                          // Конфігурація / Configuration / Конфигурация
        mutable std::mutex optimizerMutex;                     // М'ютекс для потокобезпеки / Mutex for thread safety / Мьютекс для потокобезопасности
        std::unique_ptr<Core::Scheduler> scheduler;            // Планувальник / Scheduler / Планировщик
        std::unique_ptr<NeuroSync::ThreadPool> threadPool;    // Пул потоків / Thread pool / Пул потоков
        std::unique_ptr<Memory::MemoryCore> memoryCore;        // Ядро пам'яті / Memory core / Ядро памяти
        std::unique_ptr<Diagnostics::Profiler> profiler;       // Профілювальник / Profiler / Профилировщик
        std::vector<std::shared_ptr<PerformanceObserver>> observers; // Спостерігачі / Observers / Наблюдатели
        std::atomic<bool> autoOptimizationRunning;            // Прапор автоматичної оптимізації / Auto optimization flag / Флаг автоматической оптимизации
        std::thread autoOptimizationThread;                    // Потік автоматичної оптимізації / Auto optimization thread / Поток автоматической оптимизации
        PerformanceStats currentStats;                         // Поточна статистика / Current statistics / Текущая статистика
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void autoOptimizationLoop();
        void collectPerformanceStats();
        void notifyStatsUpdated(const PerformanceStats& stats);
        void notifyOptimizationCompleted(const OptimizationResults& results);
        void notifyPerformanceIssue(const std::string& issue, double severity);
        double calculateCPULoad() const;
        size_t calculateMemoryUsage() const;
        int calculateActiveThreads() const;
        void applyOptimizationStrategy();
        std::string generateRecommendations() const;
        void updateThreadPoolSize(int newSize);
        void triggerGarbageCollection();
        void optimizeCache();
    };

} // namespace Performance
} // namespace NeuroSync

#endif // PERFORMANCE_OPTIMIZER_H