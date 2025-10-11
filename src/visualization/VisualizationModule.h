#ifndef VISUALIZATION_MODULE_H
#define VISUALIZATION_MODULE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <chrono>
#include <atomic>
#include <mutex>

// VisualizationModule.h
// Модуль візуалізації для NeuroSync OS Sparky
// Visualization module for NeuroSync OS Sparky
// Модуль визуализации для NeuroSync OS Sparky

namespace NeuroSync {

    // Типи графіків
    // Chart types
    // Типы графиков
    enum class ChartType {
        LINE,           // Лінійний графік
        // Line chart
        // Линейный график
        
        BAR,            // Стовпчикова діаграма
        // Bar chart
        // Столбчатая диаграмма
        
        PIE,            // Кругова діаграма
        // Pie chart
        // Круговая диаграмма
        
        SCATTER,        // Точкова діаграма
        // Scatter plot
        // Точечная диаграмма
        
        HEATMAP,        // Теплова карта
        // Heatmap
        // Тепловая карта
        
        NETWORK,        // Мережева діаграма
        // Network diagram
        // Сетевая диаграмма
        
        HISTOGRAM       // Гістограма
        // Histogram
        // Гистограмма
    };

    // Типи даних для візуалізації
    // Data types for visualization
    // Типы данных для визуализации
    enum class DataType {
        NEURON_ACTIVITY,    // Активність нейронів
        // Neuron activity
        // Активность нейронов
        
        SYNAPSE_WEIGHT,     // Вага синапсів
        // Synapse weight
        // Вес синапсов
        
        SIGNAL_STRENGTH,    // Сила сигналів
        // Signal strength
        // Сила сигналов
        
        PROCESSING_TIME,    // Час обробки
        // Processing time
        // Время обработки
        
        MEMORY_USAGE,       // Використання пам'яті
        // Memory usage
        // Использование памяти
        
        NETWORK_TRAFFIC,    // Мережевий трафік
        // Network traffic
        // Сетевой трафик
        
        CUSTOM              // Користувацькі дані
        // Custom data
        // Пользовательские данные
    };

    // Структура точки даних
    // Data point structure
    // Структура точки данных
    struct DataPoint {
        std::chrono::system_clock::time_point timestamp;
        double value;
        std::string label;
        
        DataPoint() : value(0.0) {}
        
        DataPoint(const std::chrono::system_clock::time_point& ts, double val, const std::string& lbl = "")
            : timestamp(ts), value(val), label(lbl) {}
    };

    // Структура графіка
    // Chart structure
    // Структура графика
    struct Chart {
        std::string id;
        std::string title;
        ChartType type;
        DataType dataType;
        std::vector<DataPoint> dataPoints;
        std::map<std::string, std::string> properties;
        
        Chart() : type(ChartType::LINE), dataType(DataType::CUSTOM) {}
        
        Chart(const std::string& chartId, const std::string& chartTitle, 
              ChartType chartType, DataType dataType)
            : id(chartId), title(chartTitle), type(chartType), dataType(dataType) {}
    };

    // Конфігурація візуалізації
    // Visualization configuration
    // Конфигурация визуализации
    struct VisualizationConfig {
        uint32_t width;
        uint32_t height;
        std::string backgroundColor;
        std::string textColor;
        bool enableAnimation;
        uint32_t refreshRate;  // В мілісекундах
        // In milliseconds
        // В миллисекундах
        bool enableExport;
        std::string exportFormat;  // "png", "svg", "pdf"
        std::string exportPath;
        
        VisualizationConfig() : width(800), height(600), 
                               backgroundColor("#FFFFFF"),
                               textColor("#000000"),
                               enableAnimation(true),
                               refreshRate(1000),
                               enableExport(false),
                               exportFormat("png"),
                               exportPath("./visualizations") {}
    };

    // Статус візуалізації
    // Visualization status
    // Статус визуализации
    enum class VisualizationStatus {
        DISABLED,       // Візуалізація вимкнена
        // Visualization disabled
        // Визуализация отключена
        
        INITIALIZING,   // Ініціалізація
        // Initializing
        // Инициализация
        
        ACTIVE,         // Активна
        // Active
        // Активна
        
        RENDERING,      // Візуалізація
        // Rendering
        // Визуализация
        
        ERROR           // Помилка
        // Error
        // Ошибка
    };

    // Інтерфейс модуля візуалізації
    // Visualization module interface
    // Интерфейс модуля визуализации
    class VisualizationModule {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        VisualizationModule();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~VisualizationModule();
        
        // Ініціалізація модуля візуалізації
        // Initialize visualization module
        // Инициализация модуля визуализации
        virtual bool initialize(const VisualizationConfig& config);
        
        // Запуск модуля візуалізації
        // Start visualization module
        // Запуск модуля визуализации
        virtual bool start();
        
        // Зупинка модуля візуалізації
        // Stop visualization module
        // Остановка модуля визуализации
        virtual void stop();
        
        // Створення графіка
        // Create chart
        // Создание графика
        virtual std::string createChart(const std::string& title, 
                                       ChartType type, 
                                       DataType dataType);
        
        // Додавання точки даних
        // Add data point
        // Добавление точки данных
        virtual bool addDataPoint(const std::string& chartId, 
                                 const DataPoint& dataPoint);
        
        // Оновлення графіка
        // Update chart
        // Обновление графика
        virtual bool updateChart(const std::string& chartId, 
                                const std::vector<DataPoint>& dataPoints);
        
        // Видалення графіка
        // Remove chart
        // Удаление графика
        virtual bool removeChart(const std::string& chartId);
        
        // Отримання графіка
        // Get chart
        // Получение графика
        virtual Chart getChart(const std::string& chartId) const;
        
        // Отримання списку графіків
        // Get list of charts
        // Получение списка графиков
        virtual std::vector<std::string> getChartList() const;
        
        // Візуалізація графіка
        // Render chart
        // Визуализация графика
        virtual bool renderChart(const std::string& chartId, 
                                const std::string& outputPath = "");
        
        // Візуалізація всіх графіків
        // Render all charts
        // Визуализация всех графиков
        virtual bool renderAllCharts(const std::string& outputDir = "");
        
        // Отримання статусу візуалізації
        // Get visualization status
        // Получение статуса визуализации
        VisualizationStatus getStatus() const;
        
        // Отримання конфігурації візуалізації
        // Get visualization configuration
        // Получение конфигурации визуализации
        VisualizationConfig getConfiguration() const;
        
        // Встановлення конфігурації візуалізації
        // Set visualization configuration
        // Установка конфигурации визуализации
        void setConfiguration(const VisualizationConfig& config);
        
        // Отримання кількості графіків
        // Get chart count
        // Получение количества графиков
        size_t getChartCount() const;
        
        // Очищення всіх графіків
        // Clear all charts
        // Очистка всех графиков
        void clearAllCharts();
        
        // Експорт даних графіка
        // Export chart data
        // Экспорт данных графика
        virtual bool exportChartData(const std::string& chartId, 
                                    const std::string& format,
                                    const std::string& outputPath);
        
        // Імпорт даних графіка
        // Import chart data
        // Импорт данных графика
        virtual bool importChartData(const std::string& chartId, 
                                    const std::string& format,
                                    const std::string& inputPath);
        
        // Отримання останніх даних графіка
        // Get latest chart data
        // Получение последних данных графика
        virtual std::vector<DataPoint> getLatestData(const std::string& chartId, 
                                                     size_t count = 100) const;
        
        // Встановлення властивостей графіка
        // Set chart properties
        // Установка свойств графика
        virtual bool setChartProperties(const std::string& chartId, 
                                       const std::map<std::string, std::string>& properties);
        
        // Отримання властивостей графіка
        // Get chart properties
        // Получение свойств графика
        virtual std::map<std::string, std::string> getChartProperties(const std::string& chartId) const;
        
    protected:
        VisualizationConfig config;
        VisualizationStatus status;
        std::map<std::string, Chart> charts;
        mutable std::mutex visualizationMutex;
        std::atomic<uint64_t> renderCount;
        std::chrono::system_clock::time_point lastRender;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        virtual std::string generateChartId();
        virtual bool renderLineChart(const Chart& chart, const std::string& outputPath);
        virtual bool renderBarChart(const Chart& chart, const std::string& outputPath);
        virtual bool renderPieChart(const Chart& chart, const std::string& outputPath);
        virtual bool renderScatterPlot(const Chart& chart, const std::string& outputPath);
        virtual bool renderHeatmap(const Chart& chart, const std::string& outputPath);
        virtual bool renderNetworkDiagram(const Chart& chart, const std::string& outputPath);
        virtual bool renderHistogram(const Chart& chart, const std::string& outputPath);
        virtual std::string serializeChartData(const Chart& chart, const std::string& format);
        virtual bool deserializeChartData(Chart& chart, const std::string& format, const std::string& data);
        virtual std::vector<DataPoint> filterDataPoints(const std::vector<DataPoint>& dataPoints, 
                                                       size_t maxPoints);
    };

    // Глобальний модуль візуалізації
    // Global visualization module
    // Глобальный модуль визуализации
    extern std::unique_ptr<VisualizationModule> gVisualizationModule;

} // namespace NeuroSync

#endif // VISUALIZATION_MODULE_H