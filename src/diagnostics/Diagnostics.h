#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "Profiler.h"
#include "Visualizer.h"
#include "PerformanceMonitor.h"
#include <string>
#include <vector>
#include <memory>
#include <mutex>

// Diagnostics.h
// Модуль діагностики для NeuroSync OS Sparky
// Diagnostics module for NeuroSync OS Sparky
// Модуль діагностики для NeuroSync OS Sparky

namespace NeuroSync {
namespace Diagnostics {

    // Подія діагностики
    // Diagnostic event
    // Подія діагностики
    struct DiagnosticEvent {
        int neuronId;
        std::string eventType;
        std::string message;
        std::chrono::high_resolution_clock::time_point timestamp;
        
        DiagnosticEvent(int id, const std::string& type, const std::string& msg)
            : neuronId(id), eventType(type), message(msg), 
              timestamp(std::chrono::high_resolution_clock::now()) {}
    };

    class Diagnostics {
    public:
        Diagnostics();
        ~Diagnostics();
        
        // Почати трасування
        // Start tracing
        // Почати трасування
        void startTracing();
        
        // Зупинити трасування
        // Stop tracing
        // Зупинити трасування
        void stopTracing();
        
        // Записати подію
        // Log an event
        // Записати подію
        void logEvent(int neuronId, const std::string& eventType, const std::string& message);
        
        // Отримати звіт про активність
        // Get activity report
        // Отримати звіт про активність
        std::string getReport() const;
        
        // Отримати текстовий звіт
        // Get text report
        // Отримати текстовий звіт
        std::string getTextReport() const;
        
        // Отримати HTML звіт
        // Get HTML report
        // Отримати HTML звіт
        std::string getHTMLReport() const;
        
        // Експортувати у форматі CSV
        // Export in CSV format
        // Експортувати у форматі CSV
        std::string exportToCSV() const;
        
        // Експортувати у форматі JSON
        // Export in JSON format
        // Експортувати у форматі JSON
        std::string exportToJSON() const;
        
        // Почати профілювання
        // Start profiling
        // Почати профілювання
        void beginProfile(const std::string& eventName, int threadId = 0);
        
        // Завершити профілювання
        // End profiling
        // Завершити профілювання
        void endProfile(const std::string& eventName);
        
        // Оновити метрики продуктивності
        // Update performance metrics
        // Оновити метрики продуктивності
        void updatePerformanceMetrics(double cpu, size_t memory, size_t neurons, 
                                    size_t synapses, size_t messages);
        
        // Почати моніторинг продуктивності
        // Start performance monitoring
        // Почати моніторинг продуктивності
        void startPerformanceMonitoring();
        
        // Зупинити моніторинг продуктивності
        // Stop performance monitoring
        // Зупинити моніторинг продуктивності
        void stopPerformanceMonitoring();
        
        // Отримати останні метрики
        // Get latest metrics
        // Отримати останні метрики
        PerformanceMetrics getLatestMetrics() const;
        
        // Перевірити порогові значення
        // Check threshold values
        // Перевірити порогові значення
        bool checkThresholds() const;
        
    private:
        bool tracingEnabled;
        std::vector<DiagnosticEvent> events;
        mutable std::mutex diagnosticsMutex;
        
        // Компоненти діагностики
        // Diagnostic components
        // Компоненти діагностики
        std::unique_ptr<Profiler> profiler;
        std::unique_ptr<Visualizer> visualizer;
        std::unique_ptr<PerformanceMonitor> performanceMonitor;
        
        // Форматувати часову мітку
        // Format timestamp
        // Форматувати часову мітку
        std::string formatTimestamp(const std::chrono::high_resolution_clock::time_point& tp) const;
    };

} // namespace Diagnostics
} // namespace NeuroSync

#endif // DIAGNOSTICS_H