#include "Diagnostics.h"
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace NeuroSync {
namespace Diagnostics {

    // Конструктор модуля діагностики
    // Diagnostics module constructor
    // Конструктор модуля діагностики
    Diagnostics::Diagnostics() : tracingEnabled(false) {
        profiler = std::make_unique<Profiler>();
        visualizer = std::make_unique<Visualizer>();
        performanceMonitor = std::make_unique<PerformanceMonitor>();
    }

    // Деструктор модуля діагностики
    // Diagnostics module destructor
    // Деструктор модуля діагностики
    Diagnostics::~Diagnostics() {}

    // Почати трасування
    // Start tracing
    // Почати трасування
    void Diagnostics::startTracing() {
        tracingEnabled = true;
        printf("[DIAGNOSTICS] Tracing started\n");
        printf("[ДІАГНОСТИКА] Трасування розпочато\n");
        printf("[ДИАГНОСТИКА] Трассировка начата\n");
    }

    // Зупинити трасування
    // Stop tracing
    // Зупинити трасування
    void Diagnostics::stopTracing() {
        tracingEnabled = false;
        printf("[DIAGNOSTICS] Tracing stopped\n");
        printf("[ДІАГНОСТИКА] Трасування зупинено\n");
        printf("[ДИАГНОСТИКА] Трассировка остановлена\n");
    }

    // Записати подію
    // Log an event
    // Записати подію
    void Diagnostics::logEvent(int neuronId, const std::string& eventType, const std::string& message) {
        std::lock_guard<std::mutex> lock(diagnosticsMutex);
        
        if (tracingEnabled) {
            DiagnosticEvent event(neuronId, eventType, message);
            events.push_back(event);
            
            // Також додати до візуалізатора
            // Also add to visualizer
            // Також додати до візуалізатора
            visualizer->addNeuronActivity(neuronId, eventType);
            
            printf("[NEURON %d] %s: %s\n", neuronId, eventType.c_str(), message.c_str());
            printf("[НЕЙРОН %d] %s: %s\n", neuronId, eventType.c_str(), message.c_str());
            printf("[НЕЙРОН %d] %s: %s\n", neuronId, eventType.c_str(), message.c_str());
        }
    }

    // Отримати звіт про активність
    // Get activity report
    // Отримати звіт про активність
    std::string Diagnostics::getReport() const {
        return getTextReport();
    }

    // Отримати текстовий звіт
    // Get text report
    // Отримати текстовий звіт
    std::string Diagnostics::getTextReport() const {
        std::lock_guard<std::mutex> lock(diagnosticsMutex);
        
        std::ostringstream report;
        report << "=== NeuroSync OS Sparky Diagnostics Report ===\n";
        report << "Generated at: " << formatTimestamp(std::chrono::high_resolution_clock::now()) << "\n\n";
        
        // Загальна статистика
        // Overall statistics
        // Загальна статистика
        report << "Total diagnostic events: " << events.size() << "\n\n";
        
        // Події діагностики
        // Diagnostic events
        // Події діагностики
        report << "Diagnostic Events:\n";
        report << "------------------\n";
        
        for (const auto& event : events) {
            report << "[" << formatTimestamp(event.timestamp) << "] ";
            report << "Neuron #" << event.neuronId << " - ";
            report << event.eventType << ": " << event.message << "\n";
        }
        
        // Додати звіт візуалізатора
        // Add visualizer report
        // Додати звіт візуалізатора
        report << "\n" << visualizer->generateTextReport();
        
        // Додати інформацію про продуктивність
        // Add performance information
        // Додати інформацію про продуктивність
        auto latestMetrics = performanceMonitor->getLatestMetrics();
        report << "\nLatest Performance Metrics:\n";
        report << "---------------------------\n";
        report << "CPU Usage: " << latestMetrics.cpuUsage << "%\n";
        report << "Memory Usage: " << latestMetrics.memoryUsage << " bytes\n";
        report << "Active Neurons: " << latestMetrics.activeNeurons << "\n";
        report << "Active Synapses: " << latestMetrics.activeSynapses << "\n";
        report << "Messages per Second: " << latestMetrics.messagesPerSecond << "\n";
        
        return report.str();
    }

    // Отримати HTML звіт
    // Get HTML report
    // Отримати HTML звіт
    std::string Diagnostics::getHTMLReport() const {
        std::lock_guard<std::mutex> lock(diagnosticsMutex);
        
        std::ostringstream html;
        html << "<!DOCTYPE html>\n";
        html << "<html>\n";
        html << "<head>\n";
        html << "<title>NeuroSync OS Sparky Diagnostics Report</title>\n";
        html << "<style>\n";
        html << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
        html << "h1, h2 { color: #333; }\n";
        html << ".event { border: 1px solid #ddd; margin: 5px 0; padding: 10px; border-radius: 3px; }\n";
        html << ".metrics { background-color: #f9f9f9; padding: 15px; border-radius: 5px; }\n";
        html << "</style>\n";
        html << "</head>\n";
        html << "<body>\n";
        html << "<h1>NeuroSync OS Sparky Diagnostics Report</h1>\n";
        html << "<p>Generated at: " << formatTimestamp(std::chrono::high_resolution_clock::now()) << "</p>\n";
        
        // Загальна статистика
        // Overall statistics
        // Загальна статистика
        html << "<h2>Diagnostic Summary</h2>\n";
        html << "<p>Total diagnostic events: " << events.size() << "</p>\n";
        
        // Події діагностики
        // Diagnostic events
        // Події діагностики
        html << "<h2>Diagnostic Events</h2>\n";
        
        for (const auto& event : events) {
            html << "<div class=\"event\">\n";
            html << "<strong>[" << formatTimestamp(event.timestamp) << "]</strong> ";
            html << "Neuron #" << event.neuronId << " - ";
            html << "<em>" << event.eventType << "</em>: " << event.message << "\n";
            html << "</div>\n";
        }
        
        // Додати звіт візуалізатора
        // Add visualizer report
        // Додати звіт візуалізатора
        html << "<h2>Neuron Activity Visualization</h2>\n";
        // Тут ми б вставили візуалізацію, але для простоти використаємо текстовий звіт
        // Here we would insert visualization, but for simplicity we'll use text report
        html << "<pre>" << visualizer->generateTextReport() << "</pre>\n";
        
        // Додати інформацію про продуктивність
        // Add performance information
        // Додати інформацію про продуктивність
        auto latestMetrics = performanceMonitor->getLatestMetrics();
        html << "<h2>Performance Metrics</h2>\n";
        html << "<div class=\"metrics\">\n";
        html << "<p><strong>CPU Usage:</strong> " << latestMetrics.cpuUsage << "%</p>\n";
        html << "<p><strong>Memory Usage:</strong> " << latestMetrics.memoryUsage << " bytes</p>\n";
        html << "<p><strong>Active Neurons:</strong> " << latestMetrics.activeNeurons << "</p>\n";
        html << "<p><strong>Active Synapses:</strong> " << latestMetrics.activeSynapses << "</p>\n";
        html << "<p><strong>Messages per Second:</strong> " << latestMetrics.messagesPerSecond << "</p>\n";
        html << "</div>\n";
        
        html << "</body>\n";
        html << "</html>\n";
        
        return html.str();
    }

    // Експортувати у форматі CSV
    // Export in CSV format
    // Експортувати у форматі CSV
    std::string Diagnostics::exportToCSV() const {
        std::lock_guard<std::mutex> lock(diagnosticsMutex);
        
        std::ostringstream csv;
        csv << "Timestamp,NeuronId,EventType,Message\n";
        
        for (const auto& event : events) {
            csv << "\"" << formatTimestamp(event.timestamp) << "\",";
            csv << event.neuronId << ",";
            csv << "\"" << event.eventType << "\",";
            csv << "\"" << event.message << "\"\n";
        }
        
        return csv.str();
    }

    // Експортувати у форматі JSON
    // Export in JSON format
    // Експортувати у форматі JSON
    std::string Diagnostics::exportToJSON() const {
        std::lock_guard<std::mutex> lock(diagnosticsMutex);
        
        std::ostringstream json;
        json << "{\n";
        json << "  \"diagnosticsReport\": {\n";
        json << "    \"generatedAt\": \"" << formatTimestamp(std::chrono::high_resolution_clock::now()) << "\",\n";
        json << "    \"totalEvents\": " << events.size() << ",\n";
        json << "    \"events\": [\n";
        
        for (size_t i = 0; i < events.size(); ++i) {
            const auto& event = events[i];
            json << "      {\n";
            json << "        \"timestamp\": \"" << formatTimestamp(event.timestamp) << "\",\n";
            json << "        \"neuronId\": " << event.neuronId << ",\n";
            json << "        \"eventType\": \"" << event.eventType << "\",\n";
            json << "        \"message\": \"" << event.message << "\"\n";
            json << "      }";
            if (i < events.size() - 1) {
                json << ",";
            }
            json << "\n";
        }
        
        json << "    ]\n";
        json << "  }\n";
        json << "}\n";
        
        return json.str();
    }

    // Почати профілювання
    // Start profiling
    // Почати профілювання
    void Diagnostics::beginProfile(const std::string& eventName, int threadId) {
        profiler->begin(eventName, threadId);
    }

    // Завершити профілювання
    // End profiling
    // Завершити профілювання
    void Diagnostics::endProfile(const std::string& eventName) {
        profiler->end(eventName);
    }

    // Оновити метрики продуктивності
    // Update performance metrics
    // Оновити метрики продуктивності
    void Diagnostics::updatePerformanceMetrics(double cpu, size_t memory, size_t neurons, 
                                              size_t synapses, size_t messages) {
        performanceMonitor->updateMetrics(cpu, memory, neurons, synapses, messages);
    }

    // Почати моніторинг продуктивності
    // Start performance monitoring
    // Почати моніторинг продуктивності
    void Diagnostics::startPerformanceMonitoring() {
        performanceMonitor->startMonitoring();
    }

    // Зупинити моніторинг продуктивності
    // Stop performance monitoring
    // Зупинити моніторинг продуктивності
    void Diagnostics::stopPerformanceMonitoring() {
        performanceMonitor->stopMonitoring();
    }

    // Отримати останні метрики
    // Get latest metrics
    // Отримати останні метрики
    PerformanceMetrics Diagnostics::getLatestMetrics() const {
        return performanceMonitor->getLatestMetrics();
    }

    // Перевірити порогові значення
    // Check threshold values
    // Перевірити порогові значення
    bool Diagnostics::checkThresholds() const {
        return performanceMonitor->checkThresholds();
    }

    // Форматувати часову мітку
    // Format timestamp
    // Форматувати часову мітку
    std::string Diagnostics::formatTimestamp(const std::chrono::high_resolution_clock::time_point& tp) const {
        auto duration = tp.time_since_epoch();
        auto secs = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        std::time_t time = static_cast<std::time_t>(secs);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

} // namespace Diagnostics
} // namespace NeuroSync