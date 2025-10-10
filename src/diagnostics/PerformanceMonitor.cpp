#include "PerformanceMonitor.h"
#include <sstream>
#include <numeric>
#include <algorithm>

namespace NeuroSync {
namespace Diagnostics {

    // Конструктор монітора продуктивності
    // Performance monitor constructor
    // Конструктор монітора продуктивності
    PerformanceMonitor::PerformanceMonitor() 
        : monitoringActive(false), cpuThreshold(80.0), memoryThreshold(1024 * 1024 * 1024), // 1GB
          neuronThreshold(10000) {}

    // Деструктор монітора продуктивності
    // Performance monitor destructor
    // Деструктор монітора продуктивності
    PerformanceMonitor::~PerformanceMonitor() {}

    // Почати моніторинг
    // Start monitoring
    // Почати моніторинг
    void PerformanceMonitor::startMonitoring() {
        monitoringActive = true;
    }

    // Зупинити моніторинг
    // Stop monitoring
    // Зупинити моніторинг
    void PerformanceMonitor::stopMonitoring() {
        monitoringActive = false;
    }

    // Оновити метрики
    // Update metrics
    // Оновити метрики
    void PerformanceMonitor::updateMetrics(double cpu, size_t memory, size_t neurons, 
                                          size_t synapses, size_t messages) {
        if (!monitoringActive) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(monitorMutex);
        
        PerformanceMetrics metrics;
        metrics.cpuUsage = cpu;
        metrics.memoryUsage = memory;
        metrics.activeNeurons = neurons;
        metrics.activeSynapses = synapses;
        metrics.messagesPerSecond = messages;
        metrics.timestamp = std::chrono::steady_clock::now();
        
        updateHistory(metrics);
    }

    // Отримати останні метрики
    // Get latest metrics
    // Отримати останні метрики
    PerformanceMetrics PerformanceMonitor::getLatestMetrics() const {
        std::lock_guard<std::mutex> lock(monitorMutex);
        
        if (metricsHistory.empty()) {
            return PerformanceMetrics();
        }
        
        return metricsHistory.back();
    }

    // Отримати історію метрик
    // Get metrics history
    // Отримати історію метрик
    std::vector<PerformanceMetrics> PerformanceMonitor::getMetricsHistory() const {
        std::lock_guard<std::mutex> lock(monitorMutex);
        return metricsHistory;
    }

    // Отримати середні метрики
    // Get average metrics
    // Отримати середні метрики
    PerformanceMetrics PerformanceMonitor::getAverageMetrics() const {
        std::lock_guard<std::mutex> lock(monitorMutex);
        
        if (metricsHistory.empty()) {
            return PerformanceMetrics();
        }
        
        PerformanceMetrics avgMetrics;
        
        // Обчислити середні значення
        // Calculate average values
        // Обчислити середні значення
        double cpuSum = 0.0;
        size_t memorySum = 0;
        size_t neuronSum = 0;
        size_t synapseSum = 0;
        size_t messageSum = 0;
        
        for (const auto& metrics : metricsHistory) {
            cpuSum += metrics.cpuUsage;
            memorySum += metrics.memoryUsage;
            neuronSum += metrics.activeNeurons;
            synapseSum += metrics.activeSynapses;
            messageSum += metrics.messagesPerSecond;
        }
        
        size_t count = metricsHistory.size();
        avgMetrics.cpuUsage = cpuSum / count;
        avgMetrics.memoryUsage = memorySum / count;
        avgMetrics.activeNeurons = neuronSum / count;
        avgMetrics.activeSynapses = synapseSum / count;
        avgMetrics.messagesPerSecond = messageSum / count;
        
        return avgMetrics;
    }

    // Експортувати метрики у форматі JSON
    // Export metrics in JSON format
    // Експортувати метрики у форматі JSON
    std::string PerformanceMonitor::exportToJSON() const {
        std::lock_guard<std::mutex> lock(monitorMutex);
        
        std::ostringstream json;
        json << "{\n";
        json << "  \"performanceMetrics\": [\n";
        
        for (size_t i = 0; i < metricsHistory.size(); ++i) {
            const auto& metrics = metricsHistory[i];
            json << "    {\n";
            json << "      \"cpuUsage\": " << metrics.cpuUsage << ",\n";
            json << "      \"memoryUsage\": " << metrics.memoryUsage << ",\n";
            json << "      \"activeNeurons\": " << metrics.activeNeurons << ",\n";
            json << "      \"activeSynapses\": " << metrics.activeSynapses << ",\n";
            json << "      \"messagesPerSecond\": " << metrics.messagesPerSecond << "\n";
            json << "    }";
            if (i < metricsHistory.size() - 1) {
                json << ",";
            }
            json << "\n";
        }
        
        json << "  ]\n";
        json << "}\n";
        
        return json.str();
    }

    // Перевірити порогові значення
    // Check threshold values
    // Перевірити порогові значення
    bool PerformanceMonitor::checkThresholds() const {
        std::lock_guard<std::mutex> lock(monitorMutex);
        
        if (metricsHistory.empty()) {
            return true;
        }
        
        const auto& latest = metricsHistory.back();
        return (latest.cpuUsage <= cpuThreshold) && 
               (latest.memoryUsage <= memoryThreshold) && 
               (latest.activeNeurons <= neuronThreshold);
    }

    // Оновити історію метрик
    // Update metrics history
    // Оновити історію метрик
    void PerformanceMonitor::updateHistory(const PerformanceMetrics& metrics) {
        // Обмежити розмір історії до 1000 записів
        // Limit history size to 1000 records
        // Обмежити розмір історії до 1000 записів
        if (metricsHistory.size() >= 1000) {
            metricsHistory.erase(metricsHistory.begin());
        }
        
        metricsHistory.push_back(metrics);
    }

} // namespace Diagnostics
} // namespace NeuroSync