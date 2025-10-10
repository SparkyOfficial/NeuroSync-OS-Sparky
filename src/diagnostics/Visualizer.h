#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <mutex>

namespace NeuroSync {
namespace Diagnostics {

    // Структура для представлення активності нейрона
    // Structure to represent neuron activity
    // Структура для представлення активності нейрона
    struct NeuronActivity {
        int neuronId;
        std::string activityType;
        std::chrono::high_resolution_clock::time_point timestamp;
        double intensity; // 0.0 to 1.0
        std::vector<int> connectedNeurons;
        
        // Конструктор за замовчуванням
        // Default constructor
        // Конструктор за замовчуванням
        NeuronActivity() : neuronId(0), timestamp(std::chrono::high_resolution_clock::now()), 
                          intensity(0.0) {}
        
        // Конструктор з параметрами
        // Constructor with parameters
        // Конструктор з параметрами
        NeuronActivity(int id, const std::string& type, double intensityLevel = 0.0)
            : neuronId(id), activityType(type), timestamp(std::chrono::high_resolution_clock::now()),
              intensity(intensityLevel) {}
    };

    // Візуалізатор активності нейронів
    // Neuron activity visualizer
    // Візуалізатор активності нейронів
    class Visualizer {
    public:
        Visualizer();
        ~Visualizer();
        
        // Додати запис про активність нейрона
        // Add neuron activity record
        // Додати запис про активність нейрона
        void addNeuronActivity(int neuronId, const std::string& activityType, 
                              double intensity = 0.0, const std::vector<int>& connections = {});
        
        // Генерувати текстовий звіт
        // Generate text report
        // Генерувати текстовий звіт
        std::string generateTextReport() const;
        
        // Генерувати HTML звіт
        // Generate HTML report
        // Генерувати HTML звіт
        std::string generateHTMLReport() const;
        
        // Експортувати дані у форматі CSV
        // Export data in CSV format
        // Експортувати дані у форматі CSV
        std::string exportToCSV() const;
        
        // Отримати активність конкретного нейрона
        // Get activity of specific neuron
        // Отримати активність конкретного нейрона
        std::vector<NeuronActivity> getNeuronActivity(int neuronId) const;
        
        // Отримати загальну активність
        // Get overall activity
        // Отримати загальну активність
        std::vector<NeuronActivity> getAllActivity() const;
        
        // Очистити дані
        // Clear data
        // Очистити дані
        void clear();
        
    private:
        std::unordered_map<int, std::vector<NeuronActivity>> neuronActivities;
        mutable std::mutex visualizerMutex;
        
        // Форматувати часову мітку
        // Format timestamp
        // Форматувати часову мітку
        std::string formatTimestamp(const std::chrono::high_resolution_clock::time_point& tp) const;
    };

} // namespace Diagnostics
} // namespace NeuroSync

#endif // VISUALIZER_H