#include "DataProcessor.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <set>
#include <cmath>

// DataProcessor.cpp
// Реалізація процесора даних для NeuroSync OS Sparky
// Implementation of data processor for NeuroSync OS Sparky
// Реализация процессора данных для NeuroSync OS Sparky

namespace NeuroSync {
namespace DataProcessing {

    // Конструктор процесора даних
    // Data processor constructor
    // Конструктор процессора данных
    DataProcessor::DataProcessor() {
        // Ініціалізація за замовчуванням
        // Default initialization
        // Инициализация по умолчанию
    }

    // Деструктор процесора даних
    // Data processor destructor
    // Деструктор процессора данных
    DataProcessor::~DataProcessor() {
        // Очищення ресурсів
        // Resource cleanup
        // Очистка ресурсов
    }

    // Ініціалізація процесора даних
    // Initialize data processor
    // Инициализация процессора данных
    bool DataProcessor::initialize(const DataProcessorConfig& config) {
        configuration = config;
        return true;
    }

    // Завантажити дані з файлу
    // Load data from file
    // Загрузить данные из файла
    bool DataProcessor::loadDataFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        currentData.clear();
        std::string line;
        
        // Зчитування даних з файлу
        // Reading data from file
        // Чтение данных из файла
        while (std::getline(file, line)) {
            std::vector<double> row;
            std::stringstream ss(line);
            std::string value;
            
            // Розділення рядка на значення
            // Splitting line into values
            // Разделение строки на значения
            while (std::getline(ss, value, ',')) {
                try {
                    row.push_back(std::stod(value));
                } catch (const std::exception&) {
                    // Ігнорувати некоректні значення
                    // Ignore invalid values
                    // Игнорировать некорректные значения
                }
            }
            
            if (!row.empty()) {
                currentData.push_back(row);
            }
        }
        
        file.close();
        return !currentData.empty();
    }

    // Зберегти дані у файл
    // Save data to file
    // Сохранить данные в файл
    bool DataProcessor::saveDataToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        // Запис даних у файл
        // Writing data to file
        // Запись данных в файл
        for (const auto& row : currentData) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        
        file.close();
        return true;
    }

    // Попередня обробка даних
    // Preprocess data
    // Предварительная обработка данных
    std::vector<std::vector<double>> DataProcessor::preprocessData(const std::vector<std::vector<double>>& data) {
        auto processedData = data;
        
        // Видалення дублікатів
        // Remove duplicates
        // Удаление дубликатов
        if (configuration.removeDuplicates) {
            processedData = removeDuplicates(processedData);
        }
        
        // Перемішування даних
        // Shuffle data
        // Перемешивание данных
        if (configuration.shuffleData) {
            processedData = shuffleData(processedData);
        }
        
        // Застосування кроків попередньої обробки
        // Apply preprocessing steps
        // Применение шагов предварительной обработки
        for (const auto& step : configuration.preprocessingSteps) {
            if (step.second) { // Якщо крок увімкнений / If step is enabled / Если шаг включен
                switch (step.first) {
                    case PreprocessingType::NORMALIZATION:
                        processedData = normalizeData(processedData);
                        break;
                    case PreprocessingType::STANDARDIZATION:
                        processedData = standardizeData(processedData);
                        break;
                    case PreprocessingType::SCALING:
                        processedData = scaleData(processedData);
                        break;
                    case PreprocessingType::ENCODING:
                        // Кодування застосовується до категоріальних даних
                        // Encoding is applied to categorical data
                        // Кодирование применяется к категориальным данным
                        break;
                    case PreprocessingType::FILTERING:
                        // Фільтрація вимагає маски
                        // Filtering requires a mask
                        // Фильтрация требует маски
                        break;
                }
            }
        }
        
        return processedData;
    }

    // Нормалізація даних
    // Normalize data
    // Нормализация данных
    std::vector<std::vector<double>> DataProcessor::normalizeData(const std::vector<std::vector<double>>& data) {
        if (data.empty()) {
            return data;
        }
        
        size_t numColumns = data[0].size();
        auto normalizedData = data;
        
        // Нормалізація для кожного стовпця
        // Normalization for each column
        // Нормализация для каждого столбца
        for (size_t col = 0; col < numColumns; ++col) {
            // Обчислення мінімуму та максимуму для стовпця
            // Calculate min and max for column
            // Вычисление минимума и максимума для столбца
            double minVal = data[0][col];
            double maxVal = data[0][col];
            
            for (const auto& row : data) {
                if (row.size() > col) {
                    minVal = std::min(minVal, row[col]);
                    maxVal = std::max(maxVal, row[col]);
                }
            }
            
            double range = maxVal - minVal;
            if (range > 0) {
                // Нормалізація значень у діапазоні [0, 1]
                // Normalize values in range [0, 1]
                // Нормализация значений в диапазоне [0, 1]
                for (auto& row : normalizedData) {
                    if (row.size() > col) {
                        row[col] = (row[col] - minVal) / range;
                    }
                }
            }
        }
        
        return normalizedData;
    }

    // Стандартизація даних
    // Standardize data
    // Стандартизация данных
    std::vector<std::vector<double>> DataProcessor::standardizeData(const std::vector<std::vector<double>>& data) {
        if (data.empty()) {
            return data;
        }
        
        size_t numColumns = data[0].size();
        auto standardizedData = data;
        
        // Стандартизація для кожного стовпця
        // Standardization for each column
        // Стандартизация для каждого столбца
        for (size_t col = 0; col < numColumns; ++col) {
            // Обчислення середнього та стандартного відхилення
            // Calculate mean and standard deviation
            // Вычисление среднего и стандартного отклонения
            double sum = 0.0;
            for (const auto& row : data) {
                if (row.size() > col) {
                    sum += row[col];
                }
            }
            
            double mean = sum / data.size();
            
            double sumSquaredDiff = 0.0;
            for (const auto& row : data) {
                if (row.size() > col) {
                    double diff = row[col] - mean;
                    sumSquaredDiff += diff * diff;
                }
            }
            
            double stdDev = std::sqrt(sumSquaredDiff / data.size());
            
            if (stdDev > 0) {
                // Стандартизація значень (z-оцінка)
                // Standardize values (z-score)
                // Стандартизация значений (z-оценка)
                for (auto& row : standardizedData) {
                    if (row.size() > col) {
                        row[col] = (row[col] - mean) / stdDev;
                    }
                }
            }
        }
        
        return standardizedData;
    }

    // Масштабування даних
    // Scale data
    // Масштабирование данных
    std::vector<std::vector<double>> DataProcessor::scaleData(const std::vector<std::vector<double>>& data, 
                                                             double minRange, double maxRange) {
        if (data.empty()) {
            return data;
        }
        
        size_t numColumns = data[0].size();
        auto scaledData = data;
        
        // Масштабування для кожного стовпця
        // Scaling for each column
        // Масштабирование для каждого столбца
        for (size_t col = 0; col < numColumns; ++col) {
            // Обчислення мінімуму та максимуму для стовпця
            // Calculate min and max for column
            // Вычисление минимума и максимума для столбца
            double minVal = data[0][col];
            double maxVal = data[0][col];
            
            for (const auto& row : data) {
                if (row.size() > col) {
                    minVal = std::min(minVal, row[col]);
                    maxVal = std::max(maxVal, row[col]);
                }
            }
            
            double originalRange = maxVal - minVal;
            double targetRange = maxRange - minRange;
            
            if (originalRange > 0) {
                // Масштабування значень у вказаний діапазон
                // Scale values to specified range
                // Масштабирование значений в указанный диапазон
                for (auto& row : scaledData) {
                    if (row.size() > col) {
                        row[col] = minRange + (row[col] - minVal) * targetRange / originalRange;
                    }
                }
            }
        }
        
        return scaledData;
    }

    // Кодування категоріальних даних
    // Encode categorical data
    // Кодирование категориальных данных
    std::vector<std::vector<double>> DataProcessor::encodeCategoricalData(const std::vector<std::vector<std::string>>& data) {
        std::vector<std::vector<double>> encodedData;
        
        if (data.empty()) {
            return encodedData;
        }
        
        size_t numColumns = data[0].size();
        
        // Для кожного стовпця створюємо словник унікальних значень
        // For each column, create a dictionary of unique values
        // Для каждого столбца создаем словарь уникальных значений
        std::vector<std::map<std::string, double>> encoders(numColumns);
        
        // Заповнення кодувальників
        // Filling encoders
        // Заполнение кодировщиков
        for (const auto& row : data) {
            for (size_t col = 0; col < std::min(row.size(), numColumns); ++col) {
                const std::string& value = row[col];
                if (encoders[col].find(value) == encoders[col].end()) {
                    encoders[col][value] = static_cast<double>(encoders[col].size());
                }
            }
        }
        
        // Кодування даних
        // Encoding data
        // Кодирование данных
        encodedData.reserve(data.size());
        for (const auto& row : data) {
            std::vector<double> encodedRow;
            encodedRow.reserve(std::min(row.size(), numColumns));
            
            for (size_t col = 0; col < std::min(row.size(), numColumns); ++col) {
                const std::string& value = row[col];
                auto it = encoders[col].find(value);
                if (it != encoders[col].end()) {
                    encodedRow.push_back(it->second);
                } else {
                    encodedRow.push_back(0.0); // За замовчуванням / Default / По умолчанию
                }
            }
            
            encodedData.push_back(encodedRow);
        }
        
        return encodedData;
    }

    // Фільтрація даних
    // Filter data
    // Фильтрация данных
    std::vector<std::vector<double>> DataProcessor::filterData(const std::vector<std::vector<double>>& data,
                                                              const std::vector<bool>& mask) {
        std::vector<std::vector<double>> filteredData;
        
        if (data.empty() || mask.empty()) {
            return filteredData;
        }
        
        size_t maskSize = std::min(data.size(), mask.size());
        filteredData.reserve(maskSize);
        
        // Фільтрація даних за маскою
        // Filtering data by mask
        // Фильтрация данных по маске
        for (size_t i = 0; i < maskSize; ++i) {
            if (mask[i] && i < data.size()) {
                filteredData.push_back(data[i]);
            }
        }
        
        return filteredData;
    }

    // Видалення дублікатів
    // Remove duplicates
    // Удаление дубликатов
    std::vector<std::vector<double>> DataProcessor::removeDuplicates(const std::vector<std::vector<double>>& data) {
        std::vector<std::vector<double>> uniqueData;
        
        if (data.empty()) {
            return uniqueData;
        }
        
        // Використання множини для відстеження унікальних рядків
        // Using a set to track unique rows
        // Использование множества для отслеживания уникальных строк
        std::set<std::vector<double>> uniqueRows;
        uniqueData.reserve(data.size());
        
        // Додавання унікальних рядків
        // Adding unique rows
        // Добавление уникальных строк
        for (const auto& row : data) {
            if (uniqueRows.find(row) == uniqueRows.end()) {
                uniqueRows.insert(row);
                uniqueData.push_back(row);
            }
        }
        
        return uniqueData;
    }

    // Перемішування даних
    // Shuffle data
    // Перемешивание данных
    std::vector<std::vector<double>> DataProcessor::shuffleData(const std::vector<std::vector<double>>& data) {
        auto shuffledData = data;
        
        if (shuffledData.empty()) {
            return shuffledData;
        }
        
        // Створення генератора випадкових чисел
        // Creating random number generator
        // Создание генератора случайных чисел
        std::random_device rd;
        std::mt19937 g(rd());
        
        // Перемішування даних
        // Shuffling data
        // Перемешивание данных
        std::shuffle(shuffledData.begin(), shuffledData.end(), g);
        
        return shuffledData;
    }

    // Розділення даних на навчальні та тестові
    // Split data into training and testing
    // Разделение данных на обучающие и тестовые
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> 
    DataProcessor::splitData(const std::vector<std::vector<double>>& data, double splitRatio) {
        if (data.empty() || splitRatio <= 0.0 || splitRatio >= 1.0) {
            return std::make_pair(data, std::vector<std::vector<double>>());
        }
        
        size_t splitIndex = static_cast<size_t>(data.size() * splitRatio);
        
        // Розділення даних
        // Splitting data
        // Разделение данных
        std::vector<std::vector<double>> trainingData(data.begin(), data.begin() + splitIndex);
        std::vector<std::vector<double>> testData(data.begin() + splitIndex, data.end());
        
        return std::make_pair(trainingData, testData);
    }

    // Отримати статистику даних
    // Get data statistics
    // Получить статистику данных
    std::map<std::string, double> DataProcessor::getDataStatistics(const std::vector<std::vector<double>>& data) const {
        std::map<std::string, double> stats;
        
        if (data.empty()) {
            return stats;
        }
        
        size_t numRows = data.size();
        size_t numCols = data[0].size();
        
        stats["row_count"] = static_cast<double>(numRows);
        stats["column_count"] = static_cast<double>(numCols);
        
        // Обчислення статистики для кожного стовпця
        // Calculate statistics for each column
        // Вычисление статистики для каждого столбца
        for (size_t col = 0; col < numCols; ++col) {
            auto columnStats = calculateColumnStats(data, col);
            
            std::string prefix = "column_" + std::to_string(col) + "_";
            stats[prefix + "mean"] = columnStats[0];
            stats[prefix + "std"] = columnStats[1];
            stats[prefix + "min"] = columnStats[2];
            stats[prefix + "max"] = columnStats[3];
        }
        
        return stats;
    }

    // Отримати конфігурацію
    // Get configuration
    // Получить конфигурацию
    DataProcessorConfig DataProcessor::getConfiguration() const {
        return configuration;
    }

    // Отримати результати
    // Get results
    // Получить результаты
    ProcessingResults DataProcessor::getResults() const {
        return results;
    }

    // Оновлення результатів
    // Update results
    // Обновление результатов
    void DataProcessor::updateResults(const ProcessingResults& newResults) {
        results = newResults;
    }

    // Обчислення статистики для стовпця
    // Calculate column statistics
    // Вычисление статистики для столбца
    std::vector<double> DataProcessor::calculateColumnStats(const std::vector<std::vector<double>>& data, 
                                                           size_t columnIndex) const {
        std::vector<double> stats(4, 0.0); // mean, std, min, max
        
        if (data.empty() || columnIndex >= data[0].size()) {
            return stats;
        }
        
        // Обчислення базових статистик
        // Calculate basic statistics
        // Вычисление базовых статистик
        double sum = 0.0;
        double minVal = data[0][columnIndex];
        double maxVal = data[0][columnIndex];
        
        for (const auto& row : data) {
            if (columnIndex < row.size()) {
                double value = row[columnIndex];
                sum += value;
                minVal = std::min(minVal, value);
                maxVal = std::max(maxVal, value);
            }
        }
        
        double mean = sum / data.size();
        
        double sumSquaredDiff = 0.0;
        for (const auto& row : data) {
            if (columnIndex < row.size()) {
                double diff = row[columnIndex] - mean;
                sumSquaredDiff += diff * diff;
            }
        }
        
        double stdDev = std::sqrt(sumSquaredDiff / data.size());
        
        stats[0] = mean;
        stats[1] = stdDev;
        stats[2] = minVal;
        stats[3] = maxVal;
        
        return stats;
    }

} // namespace DataProcessing
} // namespace NeuroSync