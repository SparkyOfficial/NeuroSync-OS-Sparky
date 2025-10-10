#include "Profiler.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace NeuroSync {
namespace Diagnostics {

    // Конструктор профайлера
    // Profiler constructor
    // Конструктор профайлера
    Profiler::Profiler() {}

    // Деструктор профайлера
    // Profiler destructor
    // Деструктор профайлера
    Profiler::~Profiler() {}

    // Почати вимірювання
    // Start measurement
    // Почати вимірювання
    void Profiler::begin(const std::string& eventName, int threadId) {
        std::lock_guard<std::mutex> lock(profilerMutex);
        
        ProfileEvent event(eventName, threadId);
        activeEvents[eventName] = event;
    }

    // Завершити вимірювання
    // End measurement
    // Завершити вимірювання
    void Profiler::end(const std::string& eventName) {
        std::lock_guard<std::mutex> lock(profilerMutex);
        
        auto it = activeEvents.find(eventName);
        if (it != activeEvents.end()) {
            ProfileEvent completedEvent = it->second;
            completedEvent.endTime = std::chrono::high_resolution_clock::now();
            
            // Обчислити тривалість
            // Calculate duration
            // Обчислити тривалість
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                completedEvent.endTime - completedEvent.startTime);
            completedEvent.duration = duration;
            
            // Додати до завершених подій
            // Add to completed events
            // Додати до завершених подій
            completedEvents.push_back(completedEvent);
            
            // Видалити з активних подій
            // Remove from active events
            // Видалити з активних подій
            activeEvents.erase(it);
        }
    }

    // Отримати статистику профілювання
    // Get profiling statistics
    // Отримати статистику профілювання
    std::vector<ProfileEvent> Profiler::getEvents() const {
        std::lock_guard<std::mutex> lock(profilerMutex);
        return completedEvents;
    }

    // Очистити дані профілювання
    // Clear profiling data
    // Очистити дані профілювання
    void Profiler::clear() {
        std::lock_guard<std::mutex> lock(profilerMutex);
        activeEvents.clear();
        completedEvents.clear();
    }

    // Експортувати дані у форматі JSON
    // Export data in JSON format
    // Експортувати дані у форматі JSON
    std::string Profiler::exportToJSON() const {
        std::lock_guard<std::mutex> lock(profilerMutex);
        
        std::ostringstream json;
        json << "{\n";
        json << "  \"events\": [\n";
        
        for (size_t i = 0; i < completedEvents.size(); ++i) {
            const auto& event = completedEvents[i];
            json << "    {\n";
            json << "      \"name\": \"" << event.name << "\",\n";
            json << "      \"threadId\": " << event.threadId << ",\n";
            json << "      \"durationMicroseconds\": " << event.duration.count() << "\n";
            json << "    }";
            if (i < completedEvents.size() - 1) {
                json << ",";
            }
            json << "\n";
        }
        
        json << "  ]\n";
        json << "}\n";
        
        return json.str();
    }

} // namespace Diagnostics
} // namespace NeuroSync