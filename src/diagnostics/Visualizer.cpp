#include "Visualizer.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

namespace NeuroSync {
namespace Diagnostics {

    // Конструктор візуалізатора
    // Visualizer constructor
    // Конструктор візуалізатора
    Visualizer::Visualizer() {}

    // Деструктор візуалізатора
    // Visualizer destructor
    // Деструктор візуалізатора
    Visualizer::~Visualizer() {}

    // Додати запис про активність нейрона
    // Add neuron activity record
    // Додати запис про активність нейрона
    void Visualizer::addNeuronActivity(int neuronId, const std::string& activityType, 
                                      double intensity, const std::vector<int>& connections) {
        std::lock_guard<std::mutex> lock(visualizerMutex);
        
        NeuronActivity activity(neuronId, activityType, intensity);
        activity.connectedNeurons = connections;
        
        neuronActivities[neuronId].push_back(activity);
    }

    // Генерувати текстовий звіт
    // Generate text report
    // Генерувати текстовий звіт
    std::string Visualizer::generateTextReport() const {
        std::lock_guard<std::mutex> lock(visualizerMutex);
        
        std::ostringstream report;
        report << "=== NeuroSync OS Sparky Activity Report ===\n";
        report << "Generated at: " << formatTimestamp(std::chrono::high_resolution_clock::now()) << "\n\n";
        
        // Загальна статистика
        // Overall statistics
        // Загальна статистика
        size_t totalActivities = 0;
        for (const auto& pair : neuronActivities) {
            totalActivities += pair.second.size();
        }
        report << "Total neuron activities recorded: " << totalActivities << "\n";
        report << "Total unique neurons: " << neuronActivities.size() << "\n\n";
        
        // Активність по нейронах
        // Activity by neurons
        // Активність по нейронах
        report << "Neuron Activity Details:\n";
        report << "------------------------\n";
        
        for (const auto& pair : neuronActivities) {
            int neuronId = pair.first;
            const auto& activities = pair.second;
            
            report << "Neuron #" << neuronId << ":\n";
            report << "  Total activities: " << activities.size() << "\n";
            
            // Типи активності
            // Activity types
            // Типи активності
            std::unordered_map<std::string, int> activityCounts;
            for (const auto& activity : activities) {
                activityCounts[activity.activityType]++;
            }
            
            report << "  Activity types:\n";
            for (const auto& countPair : activityCounts) {
                report << "    " << countPair.first << ": " << countPair.second << "\n";
            }
            report << "\n";
        }
        
        return report.str();
    }

    // Генерувати HTML звіт
    // Generate HTML report
    // Генерувати HTML звіт
    std::string Visualizer::generateHTMLReport() const {
        std::lock_guard<std::mutex> lock(visualizerMutex);
        
        std::ostringstream html;
        html << "<!DOCTYPE html>\n";
        html << "<html>\n";
        html << "<head>\n";
        html << "<title>NeuroSync OS Sparky Activity Report</title>\n";
        html << "<style>\n";
        html << "body { font-family: Arial, sans-serif; margin: 20px; }\n";
        html << "h1, h2 { color: #333; }\n";
        html << ".neuron-card { border: 1px solid #ddd; margin: 10px 0; padding: 15px; border-radius: 5px; }\n";
        html << ".activity-type { background-color: #f0f0f0; padding: 5px; margin: 2px 0; border-radius: 3px; }\n";
        html << "</style>\n";
        html << "</head>\n";
        html << "<body>\n";
        html << "<h1>NeuroSync OS Sparky Activity Report</h1>\n";
        html << "<p>Generated at: " << formatTimestamp(std::chrono::high_resolution_clock::now()) << "</p>\n";
        
        // Загальна статистика
        // Overall statistics
        // Загальна статистика
        size_t totalActivities = 0;
        for (const auto& pair : neuronActivities) {
            totalActivities += pair.second.size();
        }
        html << "<h2>Overall Statistics</h2>\n";
        html << "<p>Total neuron activities recorded: " << totalActivities << "</p>\n";
        html << "<p>Total unique neurons: " << neuronActivities.size() << "</p>\n";
        
        // Активність по нейронах
        // Activity by neurons
        // Активність по нейронах
        html << "<h2>Neuron Activity Details</h2>\n";
        
        for (const auto& pair : neuronActivities) {
            int neuronId = pair.first;
            const auto& activities = pair.second;
            
            html << "<div class=\"neuron-card\">\n";
            html << "<h3>Neuron #" << neuronId << "</h3>\n";
            html << "<p>Total activities: " << activities.size() << "</p>\n";
            
            // Типи активності
            // Activity types
            // Типи активності
            std::unordered_map<std::string, int> activityCounts;
            for (const auto& activity : activities) {
                activityCounts[activity.activityType]++;
            }
            
            html << "<h4>Activity Types:</h4>\n";
            for (const auto& countPair : activityCounts) {
                html << "<div class=\"activity-type\">" << countPair.first << ": " << countPair.second << "</div>\n";
            }
            html << "</div>\n";
        }
        
        html << "</body>\n";
        html << "</html>\n";
        
        return html.str();
    }

    // Експортувати дані у форматі CSV
    // Export data in CSV format
    // Експортувати дані у форматі CSV
    std::string Visualizer::exportToCSV() const {
        std::lock_guard<std::mutex> lock(visualizerMutex);
        
        std::ostringstream csv;
        csv << "NeuronId,ActivityType,Intensity,Timestamp,Connections\n";
        
        for (const auto& pair : neuronActivities) {
            int neuronId = pair.first;
            const auto& activities = pair.second;
            
            for (const auto& activity : activities) {
                csv << neuronId << ",";
                csv << "\"" << activity.activityType << "\",";
                csv << activity.intensity << ",";
                csv << formatTimestamp(activity.timestamp) << ",";
                
                // Форматувати з'єднання
                // Format connections
                // Форматувати з'єднання
                csv << "\"";
                for (size_t i = 0; i < activity.connectedNeurons.size(); ++i) {
                    csv << activity.connectedNeurons[i];
                    if (i < activity.connectedNeurons.size() - 1) {
                        csv << ";";
                    }
                }
                csv << "\"\n";
            }
        }
        
        return csv.str();
    }

    // Отримати активність конкретного нейрона
    // Get activity of specific neuron
    // Отримати активність конкретного нейрона
    std::vector<NeuronActivity> Visualizer::getNeuronActivity(int neuronId) const {
        std::lock_guard<std::mutex> lock(visualizerMutex);
        
        auto it = neuronActivities.find(neuronId);
        if (it != neuronActivities.end()) {
            return it->second;
        }
        return {};
    }

    // Отримати загальну активність
    // Get overall activity
    // Отримати загальну активність
    std::vector<NeuronActivity> Visualizer::getAllActivity() const {
        std::lock_guard<std::mutex> lock(visualizerMutex);
        
        std::vector<NeuronActivity> allActivities;
        for (const auto& pair : neuronActivities) {
            const auto& activities = pair.second;
            allActivities.insert(allActivities.end(), activities.begin(), activities.end());
        }
        
        return allActivities;
    }

    // Очистити дані
    // Clear data
    // Очистити дані
    void Visualizer::clear() {
        std::lock_guard<std::mutex> lock(visualizerMutex);
        neuronActivities.clear();
    }

    // Форматувати часову мітку
    // Format timestamp
    // Форматувати часову мітку
    std::string Visualizer::formatTimestamp(const std::chrono::high_resolution_clock::time_point& tp) const {
        // Convert to system_clock time_point
        auto system_tp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            tp - std::chrono::high_resolution_clock::now() + std::chrono::system_clock::now());
        auto time = std::chrono::system_clock::to_time_t(system_tp);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

} // namespace Diagnostics
} // namespace NeuroSync