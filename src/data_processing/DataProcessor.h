#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <vector>
#include <string>
#include <memory>
#include <map>

// DataProcessor.h
// Процесор даних для NeuroSync OS Sparky
// Data processor for NeuroSync OS Sparky
// Процессор данных для NeuroSync OS Sparky

namespace NeuroSync {
namespace DataProcessing {

    // Типи попередньої обробки
    // Preprocessing types
    // Типы предварительной обработки
    enum class PreprocessingType {
        NORMALIZATION,      // Нормалізація / Normalization / Нормализация
        STANDARDIZATION,    // Стандартизація / Standardization / Стандартизация
        SCALING,            // Масштабування / Scaling / Масштабирование
        ENCODING,           // Кодування / Encoding / Кодирование
        FILTERING           // Фільтрація / Filtering / Фильтрация
    };

    // Конфігурація процесора даних
    // Data processor configuration
    // Конфигурация процессора данных
    struct DataProcessorConfig {
        bool shuffleData;               // Перемішувати дані / Shuffle data / Перемешивать данные
        double trainValidationSplit;    // Розділення навчання/валідації / Train/validation split / Разделение обучения/валидации
        bool removeDuplicates;          // Видаляти дублікати / Remove duplicates / Удалять дубликаты
        std::map<PreprocessingType, bool> preprocessingSteps; // Кроки попередньої обробки / Preprocessing steps / Шаги предварительной обработки
        
        DataProcessorConfig() 
            : shuffleData(true), trainValidationSplit(0.8), removeDuplicates(true) {}
    };

    // Результати обробки даних
    // Data processing results
    // Результаты обработки данных
    struct ProcessingResults {
        size_t originalDataSize;        // Початковий розмір даних / Original data size / Исходный размер данных
        size_t processedDataSize;       // Розмір оброблених даних / Processed data size / Размер обработанных данных
        size_t removedDuplicates;       // Видалено дублікатів / Removed duplicates / Удалено дубликатов
        std::map<std::string, double> statistics; // Статистика / Statistics / Статистика
        std::string processingTime;     // Час обробки / Processing time / Время обработки
    };

    // Процесор даних
    // Data processor
    // Процессор данных
    class DataProcessor {
    public:
        DataProcessor();
        ~DataProcessor();
        
        // Ініціалізація процесора даних
        // Initialize data processor
        // Инициализация процессора данных
        bool initialize(const DataProcessorConfig& config = DataProcessorConfig());
        
        // Завантажити дані з файлу
        // Load data from file
        // Загрузить данные из файла
        bool loadDataFromFile(const std::string& filename);
        
        // Зберегти дані у файл
        // Save data to file
        // Сохранить данные в файл
        bool saveDataToFile(const std::string& filename) const;
        
        // Попередня обробка даних
        // Preprocess data
        // Предварительная обработка данных
        std::vector<std::vector<double>> preprocessData(const std::vector<std::vector<double>>& data);
        
        // Нормалізація даних
        // Normalize data
        // Нормализация данных
        std::vector<std::vector<double>> normalizeData(const std::vector<std::vector<double>>& data);
        
        // Стандартизація даних
        // Standardize data
        // Стандартизация данных
        std::vector<std::vector<double>> standardizeData(const std::vector<std::vector<double>>& data);
        
        // Масштабування даних
        // Scale data
        // Масштабирование данных
        std::vector<std::vector<double>> scaleData(const std::vector<std::vector<double>>& data, 
                                                  double minRange = 0.0, double maxRange = 1.0);
        
        // Кодування категоріальних даних
        // Encode categorical data
        // Кодирование категориальных данных
        std::vector<std::vector<double>> encodeCategoricalData(const std::vector<std::vector<std::string>>& data);
        
        // Фільтрація даних
        // Filter data
        // Фильтрация данных
        std::vector<std::vector<double>> filterData(const std::vector<std::vector<double>>& data,
                                                   const std::vector<bool>& mask);
        
        // Видалення дублікатів
        // Remove duplicates
        // Удаление дубликатов
        std::vector<std::vector<double>> removeDuplicates(const std::vector<std::vector<double>>& data);
        
        // Перемішування даних
        // Shuffle data
        // Перемешивание данных
        std::vector<std::vector<double>> shuffleData(const std::vector<std::vector<double>>& data);
        
        // Розділення даних на навчальні та тестові
        // Split data into training and testing
        // Разделение данных на обучающие и тестовые
        std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> 
            splitData(const std::vector<std::vector<double>>& data, double splitRatio = 0.8);
        
        // Отримати статистику даних
        // Get data statistics
        // Получить статистику данных
        std::map<std::string, double> getDataStatistics(const std::vector<std::vector<double>>& data) const;
        
        // Отримати конфігурацію
        // Get configuration
        // Получить конфигурацию
        DataProcessorConfig getConfiguration() const;
        
        // Отримати результати
        // Get results
        // Получить результаты
        ProcessingResults getResults() const;
        
    private:
        DataProcessorConfig configuration;  // Конфігурація / Configuration / Конфигурация
        ProcessingResults results;          // Результати / Results / Результаты
        std::vector<std::vector<double>> currentData; // Поточні дані / Current data / Текущие данные
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void updateResults(const ProcessingResults& newResults);
        std::vector<double> calculateColumnStats(const std::vector<std::vector<double>>& data, 
                                                size_t columnIndex) const;
    };

} // namespace DataProcessing
} // namespace NeuroSync

#endif // DATA_PROCESSOR_H