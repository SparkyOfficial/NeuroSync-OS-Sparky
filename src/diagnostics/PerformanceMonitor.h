#ifndef PERFORMANCE_MONITOR_H
#define PERFORMANCE_MONITOR_H

#include <chrono>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>

namespace NeuroSync {
namespace Diagnostics {

    // Структура для зберігання метрик продуктивності
    // Structure to store performance metrics
    // Структура для зберігання метрик продуктивності
    struct PerformanceMetrics {
        double cpuUsage;           // Використання CPU у відсотках
        size_t memoryUsage;        // Використання пам'яті в байтах
        size_t activeNeurons;      // Кількість активних нейронів
        size_t activeSynapses;     // Кількість активних синапсів
        size_t messagesPerSecond;  // Кількість повідомлень за секунду
        std::chrono::steady_clock::time_point timestamp;
        
        // Конструктор за замовчуванням
        // Default constructor
        // Конструктор за замовчуванням
        PerformanceMetrics() 
            : cpuUsage(0.0), memoryUsage(0), activeNeurons(0), activeSynapses(0), 
              messagesPerSecond(0), timestamp(std::chrono::steady_clock::now()) {}
    };

    // Монітор продуктивності системи
    // System performance monitor
    // Монітор продуктивності системи
    class PerformanceMonitor {
    public:
        PerformanceMonitor();
        ~PerformanceMonitor();
        
        // Почати моніторинг
        // Start monitoring
        // Почати моніторинг
        void startMonitoring();
        
        // Зупинити моніторинг
        // Stop monitoring
        // Зупинити моніторинг
        void stopMonitoring();
        
        // Оновити метрики
        // Update metrics
        // Оновити метрики
        void updateMetrics(double cpu, size_t memory, size_t neurons, size_t synapses, size_t messages);
        
        // Отримати останні метрики
        // Get latest metrics
        // Отримати останні метрики
        PerformanceMetrics getLatestMetrics() const;
        
        // Отримати історію метрик
        // Get metrics history
        // Отримати історію метрик
        std::vector<PerformanceMetrics> getMetricsHistory() const;
        
        // Отримати середні метрики
        // Get average metrics
        // Отримати середні метрики
        PerformanceMetrics getAverageMetrics() const;
        
        // Експортувати метрики у форматі JSON
        // Export metrics in JSON format
        // Експортувати метрики у форматі JSON
        std::string exportToJSON() const;
        
        // Перевірити порогові значення
        // Check threshold values
        // Перевірити порогові значення
        bool checkThresholds() const;
        
    private:
        std::vector<PerformanceMetrics> metricsHistory;
        std::atomic<bool> monitoringActive;
        mutable std::mutex monitorMutex;
        
        // Порогові значення
        // Threshold values
        // Порогові значення
        double cpuThreshold;
        size_t memoryThreshold;
        size_t neuronThreshold;
        
        // Оновити історію метрик
        // Update metrics history
        // Оновити історію метрик
        void updateHistory(const PerformanceMetrics& metrics);
    };

} // namespace Diagnostics
} // namespace NeuroSync

#endif // PERFORMANCE_MONITOR_H