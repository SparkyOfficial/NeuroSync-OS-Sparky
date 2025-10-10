#ifndef PROFILER_H
#define PROFILER_H

#include <chrono>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>

namespace NeuroSync {
namespace Diagnostics {

    // Структура для зберігання інформації про подію профілювання
    // Structure to store profiling event information
    // Структура для зберігання інформації про подію профілювання
    struct ProfileEvent {
        std::string name;
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;
        std::chrono::microseconds duration;
        int threadId;
        
        // Конструктор за замовчуванням
        // Default constructor
        // Конструктор за замовчуванням
        ProfileEvent() : startTime(std::chrono::high_resolution_clock::now()), 
                        endTime(startTime), duration(0), threadId(0) {}
        
        // Конструктор з параметрами
        // Constructor with parameters
        // Конструктор з параметрами
        ProfileEvent(const std::string& eventName, int tid = 0) 
            : name(eventName), startTime(std::chrono::high_resolution_clock::now()), 
              endTime(startTime), duration(0), threadId(tid) {}
    };

    // Профайлер для вимірювання продуктивності
    // Profiler for performance measurement
    // Профайлер для вимірювання продуктивності
    class Profiler {
    public:
        Profiler();
        ~Profiler();
        
        // Почати вимірювання
        // Start measurement
        // Почати вимірювання
        void begin(const std::string& eventName, int threadId = 0);
        
        // Завершити вимірювання
        // End measurement
        // Завершити вимірювання
        void end(const std::string& eventName);
        
        // Отримати статистику профілювання
        // Get profiling statistics
        // Отримати статистику профілювання
        std::vector<ProfileEvent> getEvents() const;
        
        // Очистити дані профілювання
        // Clear profiling data
        // Очистити дані профілювання
        void clear();
        
        // Експортувати дані у форматі JSON
        // Export data in JSON format
        // Експортувати дані у форматі JSON
        std::string exportToJSON() const;
        
    private:
        std::unordered_map<std::string, ProfileEvent> activeEvents;
        std::vector<ProfileEvent> completedEvents;
        mutable std::mutex profilerMutex;
    };

} // namespace Diagnostics
} // namespace NeuroSync

#endif // PROFILER_H