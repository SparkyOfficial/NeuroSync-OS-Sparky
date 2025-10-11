# Visualization Module Documentation

## Overview

The Visualization Module provides comprehensive data visualization capabilities for the NeuroSync OS Sparky, enabling the creation of various charts and graphs to monitor neuron activity, synapse weights, and system performance.

## Огляд модуля візуалізації

Модуль візуалізації забезпечує комплексні можливості візуалізації даних для NeuroSync OS Sparky, дозволяючи створювати різні діаграми та графіки для моніторингу активності нейронів, ваг синапсів і продуктивності системи.

## Обзор модуля визуализации

Модуль визуализации обеспечивает комплексные возможности визуализации данных для NeuroSync OS Sparky, позволяя создавать различные диаграммы и графики для мониторинга активности нейронов, весов синапсов и производительности системы.

## Key Features

1. **Multiple Chart Types**: Line, bar, pie, scatter, heatmap, network, and histogram charts
2. **Real-time Data Visualization**: Live updating of charts with new data points
3. **Data Export/Import**: Support for exporting and importing chart data in various formats
4. **Chart Customization**: Configurable chart properties and styling
5. **Performance Monitoring**: Visualization of system performance metrics
6. **Neuron Activity Tracking**: Monitoring of neuron activation patterns
7. **Synapse Weight Analysis**: Visualization of synapse weight changes
8. **Thread Safety**: Designed for concurrent access with thread safety

## Основні можливості

1. **Різні типи діаграм**: Лінійні, стовпчикові, кругові, точкові, теплові карти, мережеві діаграми та гістограми
2. **Візуалізація даних у реальному часі**: Постійне оновлення діаграм новими точками даних
3. **Експорт/імпорт даних**: Підтримка експорту та імпорту даних діаграм у різних форматах
4. **Налаштування діаграм**: Налаштовувані властивості та стилізація діаграм
5. **Моніторинг продуктивності**: Візуалізація метрик продуктивності системи
6. **Відстеження активності нейронів**: Моніторинг шаблонів активації нейронів
7. **Аналіз ваг синапсів**: Візуалізація змін ваг синапсів
8. **Потокобезпека**: Розроблений для одночасного доступу з потокобезпекою

## Основные возможности

1. **Разные типы диаграмм**: Линейные, столбчатые, круговые, точечные, тепловые карты, сетевые диаграммы и гистограммы
2. **Визуализация данных в реальном времени**: Постоянное обновление диаграмм новыми точками данных
3. **Экспорт/импорт данных**: Поддержка экспорта и импорта данных диаграмм в разных форматах
4. **Настройка диаграмм**: Настраиваемые свойства и стилизация диаграмм
5. **Мониторинг производительности**: Визуализация метрик производительности системы
6. **Отслеживание активности нейронов**: Мониторинг шаблонов активации нейронов
7. **Анализ весов синапсов**: Визуализация изменений весов синапсов
8. **Потокобезопасность**: Разработан для одновременного доступа с потокобезопасностью

## API Reference

### VisualizationModule Class

#### Constructor
```cpp
VisualizationModule();
```
Creates a new VisualizationModule instance.

Створює новий екземпляр VisualizationModule.

Создаёт новый экземпляр VisualizationModule.

#### Destructor
```cpp
virtual ~VisualizationModule();
```
Destroys the VisualizationModule instance and cleans up resources.

Знищує екземпляр VisualizationModule та звільняє ресурси.

Уничтожает экземпляр VisualizationModule и освобождает ресурсы.

#### initialize
```cpp
virtual bool initialize(const VisualizationConfig& config);
```
Initializes the visualization module with the specified configuration.

Ініціалізує модуль візуалізації з вказаною конфігурацією.

Инициализирует модуль визуализации с указанной конфигурацией.

#### start
```cpp
virtual bool start();
```
Starts the visualization module.

Запускає модуль візуалізації.

Запускает модуль визуализации.

#### stop
```cpp
virtual void stop();
```
Stops the visualization module.

Зупиняє модуль візуалізації.

Останавливает модуль визуализации.

#### createChart
```cpp
virtual std::string createChart(const std::string& title, 
                               ChartType type, 
                               DataType dataType);
```
Creates a new chart with the specified title, type, and data type.

Створює нову діаграму з вказаною назвою, типом і типом даних.

Создаёт новую диаграмму с указанной назвой, типом и типом данных.

#### addDataPoint
```cpp
virtual bool addDataPoint(const std::string& chartId, 
                         const DataPoint& dataPoint);
```
Adds a data point to the specified chart.

Додає точку даних до вказаної діаграми.

Добавляет точку данных к указанной диаграмме.

#### updateChart
```cpp
virtual bool updateChart(const std::string& chartId, 
                        const std::vector<DataPoint>& dataPoints);
```
Updates the specified chart with new data points.

Оновлює вказану діаграму новими точками даних.

Обновляет указанную диаграмму новыми точками данных.

#### removeChart
```cpp
virtual bool removeChart(const std::string& chartId);
```
Removes the specified chart.

Видаляє вказану діаграму.

Удаляет указанную диаграмму.

#### getChart
```cpp
virtual Chart getChart(const std::string& chartId) const;
```
Gets the specified chart.

Отримує вказану діаграму.

Получает указанную диаграмму.

#### getChartList
```cpp
virtual std::vector<std::string> getChartList() const;
```
Gets a list of all chart IDs.

Отримує список усіх ідентифікаторів діаграм.

Получает список всех идентификаторов диаграмм.

#### renderChart
```cpp
virtual bool renderChart(const std::string& chartId, 
                        const std::string& outputPath = "");
```
Renders the specified chart to an output file.

Візуалізує вказану діаграму у вихідний файл.

Визуализирует указанную диаграмму в выходной файл.

#### renderAllCharts
```cpp
virtual bool renderAllCharts(const std::string& outputDir = "");
```
Renders all charts to output files.

Візуалізує всі діаграми у вихідні файли.

Визуализирует все диаграммы в выходные файлы.

#### getStatus
```cpp
VisualizationStatus getStatus() const;
```
Gets the current visualization status.

Отримує поточний статус візуалізації.

Получает текущий статус визуализации.

#### getConfiguration
```cpp
VisualizationConfig getConfiguration() const;
```
Gets the current visualization configuration.

Отримує поточну конфігурацію візуалізації.

Получает текущую конфигурацию визуализации.

#### setConfiguration
```cpp
void setConfiguration(const VisualizationConfig& config);
```
Sets the visualization configuration.

Встановлює конфігурацію візуалізації.

Устанавливает конфигурацию визуализации.

#### getChartCount
```cpp
size_t getChartCount() const;
```
Gets the count of charts.

Отримує кількість діаграм.

Получает количество диаграмм.

#### clearAllCharts
```cpp
void clearAllCharts();
```
Clears all charts.

Очищує всі діаграми.

Очищает все диаграммы.

#### exportChartData
```cpp
virtual bool exportChartData(const std::string& chartId, 
                            const std::string& format,
                            const std::string& outputPath);
```
Exports chart data to a file.

Експортує дані діаграми у файл.

Экспортирует данные диаграммы в файл.

#### importChartData
```cpp
virtual bool importChartData(const std::string& chartId, 
                            const std::string& format,
                            const std::string& inputPath);
```
Imports chart data from a file.

Імпортує дані діаграми з файлу.

Импортирует данные диаграммы из файла.

#### getLatestData
```cpp
virtual std::vector<DataPoint> getLatestData(const std::string& chartId, 
                                             size_t count = 100) const;
```
Gets the latest data points from the specified chart.

Отримує останні точки даних з вказаної діаграми.

Получает последние точки данных из указанной диаграммы.

#### setChartProperties
```cpp
virtual bool setChartProperties(const std::string& chartId, 
                               const std::map<std::string, std::string>& properties);
```
Sets properties for the specified chart.

Встановлює властивості для вказаної діаграми.

Устанавливает свойства для указанной диаграммы.

#### getChartProperties
```cpp
virtual std::map<std::string, std::string> getChartProperties(const std::string& chartId) const;
```
Gets properties for the specified chart.

Отримує властивості для вказаної діаграми.

Получает свойства для указанной диаграммы.

### VisualizationConfig Structure

#### Members
- `uint32_t width` - Chart width
- `uint32_t height` - Chart height
- `std::string backgroundColor` - Background color
- `std::string textColor` - Text color
- `bool enableAnimation` - Enable animation
- `uint32_t refreshRate` - Refresh rate in milliseconds
- `bool enableExport` - Enable export
- `std::string exportFormat` - Export format ("png", "svg", "pdf")
- `std::string exportPath` - Export path

### Chart Structure

#### Members
- `std::string id` - Chart ID
- `std::string title` - Chart title
- `ChartType type` - Chart type
- `DataType dataType` - Data type
- `std::vector<DataPoint> dataPoints` - Data points
- `std::map<std::string, std::string> properties` - Chart properties

### DataPoint Structure

#### Members
- `std::chrono::system_clock::time_point timestamp` - Timestamp
- `double value` - Data value
- `std::string label` - Data label

### ChartType Enum

#### Values
- `LINE` - Line chart
- `BAR` - Bar chart
- `PIE` - Pie chart
- `SCATTER` - Scatter plot
- `HEATMAP` - Heatmap
- `NETWORK` - Network diagram
- `HISTOGRAM` - Histogram

### DataType Enum

#### Values
- `NEURON_ACTIVITY` - Neuron activity
- `SYNAPSE_WEIGHT` - Synapse weight
- `SIGNAL_STRENGTH` - Signal strength
- `PROCESSING_TIME` - Processing time
- `MEMORY_USAGE` - Memory usage
- `NETWORK_TRAFFIC` - Network traffic
- `CUSTOM` - Custom data

### VisualizationStatus Enum

#### Values
- `DISABLED` - Visualization disabled
- `INITIALIZING` - Initializing
- `ACTIVE` - Active
- `RENDERING` - Rendering
- `ERROR` - Error

## Usage Example

```cpp
#include "VisualizationModule.h"

int main() {
    // Create and initialize visualization module
    auto visualizationModule = std::make_unique<NeuroSync::VisualizationModule>();
    
    NeuroSync::VisualizationConfig config;
    config.width = 1024;
    config.height = 768;
    config.enableExport = true;
    config.exportPath = "./visualizations";
    
    visualizationModule->initialize(config);
    visualizationModule->start();
    
    // Create a neuron activity chart
    std::string chartId = visualizationModule->createChart(
        "Neuron Activity", 
        NeuroSync::ChartType::LINE, 
        NeuroSync::DataType::NEURON_ACTIVITY
    );
    
    // Add data points
    auto now = std::chrono::system_clock::now();
    for (int i = 0; i < 10; ++i) {
        NeuroSync::DataPoint point(
            now + std::chrono::seconds(i),
            i * 10.0,
            "Neuron_" + std::to_string(i)
        );
        visualizationModule->addDataPoint(chartId, point);
    }
    
    // Render the chart
    visualizationModule->renderChart(chartId, "./visualizations/neuron_activity.png");
    
    return 0;
}
```

## Приклад використання

```cpp
#include "VisualizationModule.h"

int main() {
    // Створення та ініціалізація модуля візуалізації
    auto visualizationModule = std::make_unique<NeuroSync::VisualizationModule>();
    
    NeuroSync::VisualizationConfig config;
    config.width = 1024;
    config.height = 768;
    config.enableExport = true;
    config.exportPath = "./visualizations";
    
    visualizationModule->initialize(config);
    visualizationModule->start();
    
    // Створення діаграми активності нейронів
    std::string chartId = visualizationModule->createChart(
        "Neuron Activity", 
        NeuroSync::ChartType::LINE, 
        NeuroSync::DataType::NEURON_ACTIVITY
    );
    
    // Додавання точок даних
    auto now = std::chrono::system_clock::now();
    for (int i = 0; i < 10; ++i) {
        NeuroSync::DataPoint point(
            now + std::chrono::seconds(i),
            i * 10.0,
            "Neuron_" + std::to_string(i)
        );
        visualizationModule->addDataPoint(chartId, point);
    }
    
    // Візуалізація діаграми
    visualizationModule->renderChart(chartId, "./visualizations/neuron_activity.png");
    
    return 0;
}
```

## Пример использования

```cpp
#include "VisualizationModule.h"

int main() {
    // Создание и инициализация модуля визуализации
    auto visualizationModule = std::make_unique<NeuroSync::VisualizationModule>();
    
    NeuroSync::VisualizationConfig config;
    config.width = 1024;
    config.height = 768;
    config.enableExport = true;
    config.exportPath = "./visualizations";
    
    visualizationModule->initialize(config);
    visualizationModule->start();
    
    // Создание диаграммы активности нейронов
    std::string chartId = visualizationModule->createChart(
        "Neuron Activity", 
        NeuroSync::ChartType::LINE, 
        NeuroSync::DataType::NEURON_ACTIVITY
    );
    
    // Добавление точек данных
    auto now = std::chrono::system_clock::now();
    for (int i = 0; i < 10; ++i) {
        NeuroSync::DataPoint point(
            now + std::chrono::seconds(i),
            i * 10.0,
            "Neuron_" + std::to_string(i)
        );
        visualizationModule->addDataPoint(chartId, point);
    }
    
    // Визуализация диаграммы
    visualizationModule->renderChart(chartId, "./visualizations/neuron_activity.png");
    
    return 0;
}
```

## Integration with NeuroSync OS Sparky

The VisualizationModule integrates with other NeuroSync modules:
- Used by the Diagnostics module for system performance visualization
- Utilized by the NeuronManager for neuron activity monitoring
- Employed by the SynapseBus for synapse weight analysis
- Leveraged by the MemoryCore for memory usage tracking

## Інтеграція з NeuroSync OS Sparky

Модуль візуалізації інтегрується з іншими модулями NeuroSync:
- Використовується модулем діагностики для візуалізації продуктивності системи
- Використовується NeuronManager для моніторингу активності нейронів
- Використовується SynapseBus для аналізу ваг синапсів
- Використовується MemoryCore для відстеження використання пам'яті

## Интеграция с NeuroSync OS Sparky

Модуль визуализации интегрируется с другими модулями NeuroSync:
- Используется модулем диагностики для визуализации производительности системы
- Используется NeuronManager для мониторинга активности нейронов
- Используется SynapseBus для анализа весов синапсов
- Используется MemoryCore для отслеживания использования памяти

## Performance Considerations

1. **Data Volume**: Large datasets may impact rendering performance; consider data filtering
2. **Refresh Rate**: Higher refresh rates provide smoother updates but consume more resources
3. **Chart Complexity**: Complex charts with many data points require more processing power
4. **Export Format**: Different export formats have varying performance characteristics
5. **Memory Usage**: Chart data is stored in memory; monitor memory consumption for large datasets

## Рекомендації щодо продуктивності

1. **Обсяг даних**: Великі набори даних можуть впливати на продуктивність візуалізації; розгляньте фільтрацію даних
2. **Частота оновлення**: Вищі частоти оновлення забезпечують плавніше оновлення, але споживають більше ресурсів
3. **Складність діаграм**: Складні діаграми з багатьма точками даних вимагають більше обчислювальної потужності
4. **Формат експорту**: Різні формати експорту мають різні характеристики продуктивності
5. **Використання пам'яті**: Дані діаграм зберігаються в пам'яті; відстежуйте споживання пам'яті для великих наборів даних

## Рекомендации по производительности

1. **Объем данных**: Большие наборы данных могут влиять на производительность визуализации; рассмотрите фильтрацию данных
2. **Частота обновления**: Высшие частоты обновления обеспечивают более плавное обновление, но потребляют больше ресурсов
3. **Сложность диаграмм**: Сложные диаграммы с множеством точек данных требуют больше вычислительной мощности
4. **Формат экспорта**: Разные форматы экспорта имеют различные характеристики производительности
5. **Использование памяти**: Данные диаграмм хранятся в памяти; отслеживайте потребление памяти для больших наборов данных