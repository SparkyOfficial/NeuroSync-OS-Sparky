#include "../visualization/VisualizationModule.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

// Приклад використання модуля візуалізації
// Visualization module usage example
// Пример использования модуля визуализации

int main() {
    std::cout << "=== Visualization Module Example ===" << std::endl;
    
    // Ініціалізація модуля візуалізації
    // Initializing visualization module
    // Инициализация модуля визуализации
    NeuroSync::gVisualizationModule = std::make_unique<NeuroSync::VisualizationModule>();
    
    NeuroSync::VisualizationConfig config;
    config.width = 1024;
    config.height = 768;
    config.backgroundColor = "#F0F0F0";
    config.textColor = "#333333";
    config.enableAnimation = true;
    config.refreshRate = 500; // 500 мілісекунд
    // 500 milliseconds
    // 500 миллисекунд
    config.enableExport = true;
    config.exportFormat = "png";
    config.exportPath = "./visualizations";
    
    if (!NeuroSync::gVisualizationModule->initialize(config)) {
        std::cerr << "Failed to initialize visualization module" << std::endl;
        return 1;
    }
    
    std::cout << "Visualization module initialized" << std::endl;
    
    // Запуск модуля візуалізації
    // Starting visualization module
    // Запуск модуля визуализации
    if (!NeuroSync::gVisualizationModule->start()) {
        std::cerr << "Failed to start visualization module" << std::endl;
        return 1;
    }
    
    std::cout << "Visualization module started" << std::endl;
    
    // Створення графіків
    // Creating charts
    // Создание графиков
    std::cout << "\nCreating charts..." << std::endl;
    std::string neuronActivityChart = NeuroSync::gVisualizationModule->createChart(
        "Neuron Activity", 
        NeuroSync::ChartType::LINE, 
        NeuroSync::DataType::NEURON_ACTIVITY
    );
    
    std::string synapseWeightChart = NeuroSync::gVisualizationModule->createChart(
        "Synapse Weights", 
        NeuroSync::ChartType::BAR, 
        NeuroSync::DataType::SYNAPSE_WEIGHT
    );
    
    std::string signalStrengthChart = NeuroSync::gVisualizationModule->createChart(
        "Signal Strength", 
        NeuroSync::ChartType::SCATTER, 
        NeuroSync::DataType::SIGNAL_STRENGTH
    );
    
    std::string memoryUsageChart = NeuroSync::gVisualizationModule->createChart(
        "Memory Usage", 
        NeuroSync::ChartType::PIE, 
        NeuroSync::DataType::MEMORY_USAGE
    );
    
    std::cout << "Created charts:" << std::endl;
    std::cout << "  Neuron Activity Chart: " << neuronActivityChart << std::endl;
    std::cout << "  Synapse Weight Chart: " << synapseWeightChart << std::endl;
    std::cout << "  Signal Strength Chart: " << signalStrengthChart << std::endl;
    std::cout << "  Memory Usage Chart: " << memoryUsageChart << std::endl;
    
    // Отримання списку графіків
    // Getting list of charts
    // Получение списка графиков
    std::cout << "\nChart list:" << std::endl;
    auto chartList = NeuroSync::gVisualizationModule->getChartList();
    for (const auto& chartId : chartList) {
        std::cout << "  " << chartId << std::endl;
    }
    
    // Генерація тестових даних
    // Generating test data
    // Генерация тестовых данных
    std::cout << "\nGenerating test data..." << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);
    
    auto now = std::chrono::system_clock::now();
    
    // Додавання точок даних для активності нейронів
    // Adding data points for neuron activity
    // Добавление точек данных для активности нейронов
    for (int i = 0; i < 50; ++i) {
        NeuroSync::DataPoint point(
            now + std::chrono::seconds(i),
            dis(gen),
            "Neuron_" + std::to_string(i % 10)
        );
        NeuroSync::gVisualizationModule->addDataPoint(neuronActivityChart, point);
    }
    
    // Додавання точок даних для ваг синапсів
    // Adding data points for synapse weights
    // Добавление точек данных для весов синапсов
    for (int i = 0; i < 10; ++i) {
        NeuroSync::DataPoint point(
            now + std::chrono::seconds(i),
            dis(gen),
            "Synapse_" + std::to_string(i)
        );
        NeuroSync::gVisualizationModule->addDataPoint(synapseWeightChart, point);
    }
    
    // Додавання точок даних для сили сигналів
    // Adding data points for signal strength
    // Добавление точек данных для силы сигналов
    for (int i = 0; i < 30; ++i) {
        NeuroSync::DataPoint point(
            now + std::chrono::seconds(i),
            dis(gen),
            "Signal_" + std::to_string(i % 5)
        );
        NeuroSync::gVisualizationModule->addDataPoint(signalStrengthChart, point);
    }
    
    // Додавання точок даних для використання пам'яті
    // Adding data points for memory usage
    // Добавление точек данных для использования памяти
    std::vector<std::string> memoryLabels = {"Core", "Neuron", "Synapse", "Memory", "Diagnostics"};
    for (int i = 0; i < 5; ++i) {
        NeuroSync::DataPoint point(
            now,
            dis(gen),
            memoryLabels[i]
        );
        NeuroSync::gVisualizationModule->addDataPoint(memoryUsageChart, point);
    }
    
    // Отримання графіків
    // Getting charts
    // Получение графиков
    std::cout << "\nChart information:" << std::endl;
    auto neuronChart = NeuroSync::gVisualizationModule->getChart(neuronActivityChart);
    std::cout << "  Neuron Activity Chart:" << std::endl;
    std::cout << "    Title: " << neuronChart.title << std::endl;
    std::cout << "    Data Points: " << neuronChart.dataPoints.size() << std::endl;
    
    auto synapseChart = NeuroSync::gVisualizationModule->getChart(synapseWeightChart);
    std::cout << "  Synapse Weight Chart:" << std::endl;
    std::cout << "    Title: " << synapseChart.title << std::endl;
    std::cout << "    Data Points: " << synapseChart.dataPoints.size() << std::endl;
    
    // Отримання останніх даних
    // Getting latest data
    // Получение последних данных
    std::cout << "\nLatest data (last 5 points):" << std::endl;
    auto latestData = NeuroSync::gVisualizationModule->getLatestData(neuronActivityChart, 5);
    std::cout << "  Neuron Activity Chart:" << std::endl;
    for (const auto& point : latestData) {
        auto duration = point.timestamp.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        std::cout << "    " << millis << ": " << point.value << " (" << point.label << ")" << std::endl;
    }
    
    // Встановлення властивостей графіка
    // Setting chart properties
    // Установка свойств графика
    std::map<std::string, std::string> properties;
    properties["color"] = "#FF0000";
    properties["lineWidth"] = "2";
    properties["showLegend"] = "true";
    
    NeuroSync::gVisualizationModule->setChartProperties(neuronActivityChart, properties);
    
    // Отримання властивостей графіка
    // Getting chart properties
    // Получение свойств графика
    auto chartProperties = NeuroSync::gVisualizationModule->getChartProperties(neuronActivityChart);
    std::cout << "\nChart properties:" << std::endl;
    for (const auto& pair : chartProperties) {
        std::cout << "  " << pair.first << ": " << pair.second << std::endl;
    }
    
    // Візуалізація графіків
    // Rendering charts
    // Визуализация графиков
    std::cout << "\nRendering charts..." << std::endl;
    
    // Створення директорії для візуалізацій
    // Creating directory for visualizations
    // Создание директории для визуализаций
    system("mkdir visualizations 2>/dev/null || mkdir visualizations 2>nul");
    
    if (NeuroSync::gVisualizationModule->renderChart(neuronActivityChart, "./visualizations/neuron_activity.png")) {
        std::cout << "  Rendered neuron activity chart" << std::endl;
    }
    
    if (NeuroSync::gVisualizationModule->renderChart(synapseWeightChart, "./visualizations/synapse_weights.png")) {
        std::cout << "  Rendered synapse weight chart" << std::endl;
    }
    
    if (NeuroSync::gVisualizationModule->renderChart(signalStrengthChart, "./visualizations/signal_strength.png")) {
        std::cout << "  Rendered signal strength chart" << std::endl;
    }
    
    if (NeuroSync::gVisualizationModule->renderChart(memoryUsageChart, "./visualizations/memory_usage.png")) {
        std::cout << "  Rendered memory usage chart" << std::endl;
    }
    
    // Візуалізація всіх графіків
    // Rendering all charts
    // Визуализация всех графиков
    std::cout << "\nRendering all charts..." << std::endl;
    if (NeuroSync::gVisualizationModule->renderAllCharts("./visualizations")) {
        std::cout << "  Rendered all charts" << std::endl;
    }
    
    // Експорт даних графіка
    // Exporting chart data
    // Экспорт данных графика
    std::cout << "\nExporting chart data..." << std::endl;
    if (NeuroSync::gVisualizationModule->exportChartData(neuronActivityChart, "csv", "./visualizations/neuron_activity.csv")) {
        std::cout << "  Exported neuron activity data" << std::endl;
    }
    
    // Отримання статистики
    // Getting statistics
    // Получение статистики
    std::cout << "\nVisualization statistics:" << std::endl;
    std::cout << "  Chart count: " << NeuroSync::gVisualizationModule->getChartCount() << std::endl;
    std::cout << "  Visualization status: " << static_cast<int>(NeuroSync::gVisualizationModule->getStatus()) << std::endl;
    
    // Очищення графіків
    // Clearing charts
    // Очистка графиков
    std::cout << "\nClearing charts..." << std::endl;
    NeuroSync::gVisualizationModule->clearAllCharts();
    std::cout << "  Chart count after clearing: " << NeuroSync::gVisualizationModule->getChartCount() << std::endl;
    
    // Зупинка модуля візуалізації
    // Stopping visualization module
    // Остановка модуля визуализации
    std::cout << "\nStopping visualization module..." << std::endl;
    NeuroSync::gVisualizationModule->stop();
    
    std::cout << "\nVisualization module example completed!" << std::endl;
    
    return 0;
}