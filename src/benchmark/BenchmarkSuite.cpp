/*
 * BenchmarkSuite.cpp
 * Реалізація набору тестів продуктивності для NeuroSync OS Sparky
 * Implementation of benchmark suite for NeuroSync OS Sparky
 * Реализация набора тестов производительности для NeuroSync OS Sparky
 */

#include "BenchmarkSuite.h"
#include <algorithm>
#include <fstream>
#include <thread>
#include <cmath>

namespace NeuroSync {

    // Глобальний набір тестів продуктивності
    // Global benchmark suite
    // Глобальный набор тестов производительности
    std::unique_ptr<BenchmarkSuite> gBenchmarkSuite = std::make_unique<BenchmarkSuite>();

    // Конструктор
    // Constructor
    // Конструктор
    BenchmarkSuite::BenchmarkSuite() {
        // Ініціалізація за замовчуванням
        // Default initialization
        // Инициализация по умолчанию
    }

    // Деструктор
    // Destructor
    // Деструктор
    BenchmarkSuite::~BenchmarkSuite() {
        // Очищення ресурсів
        // Resource cleanup
        // Очистка ресурсов
    }

    // Ініціалізація набору тестів продуктивності
    // Initialize benchmark suite
    // Инициализация набора тестов производительности
    bool BenchmarkSuite::initialize(const BenchmarkConfig& config) {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        this->config = config;
        return true;
    }

    // Реєстрація тесту продуктивності
    // Register performance test
    // Регистрация теста производительности
    void BenchmarkSuite::registerBenchmark(const std::string& testName,
                                         BenchmarkType type,
                                         std::function<void(size_t)> benchmarkFunction) {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        benchmarkRegistry[testName] = std::make_pair(type, benchmarkFunction);
        
        if (config.verboseOutput) {
            std::cout << "Registered benchmark: " << testName << std::endl;
        }
    }

    // Запуск усіх тестів продуктивності
    // Run all performance tests
    // Запуск всех тестов производительности
    std::vector<BenchmarkResult> BenchmarkSuite::runAllBenchmarks() {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        std::vector<BenchmarkResult> results;
        
        for (const auto& pair : benchmarkRegistry) {
            const std::string& testName = pair.first;
            BenchmarkResult result = runBenchmark(testName, config.defaultIterations);
            results.push_back(result);
        }
        
        benchmarkResults = results;
        return results;
    }

    // Запуск конкретного тесту продуктивності
    // Run specific performance test
    // Запуск конкретного теста производительности
    BenchmarkResult BenchmarkSuite::runBenchmark(const std::string& testName, 
                                               size_t iterations) {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        
        // Перевірка наявності тесту
        // Check if test exists
        // Проверка наличия теста
        auto it = benchmarkRegistry.find(testName);
        if (it == benchmarkRegistry.end()) {
            BenchmarkResult result(testName, BenchmarkType::CPU);
            result.additionalInfo = "Benchmark not found";
            return result;
        }
        
        // Визначення кількості ітерацій
        // Determine number of iterations
        // Определение количества итераций
        if (iterations == 0) {
            iterations = config.defaultIterations;
        }
        
        const auto& benchmarkFunction = it->second.second;
        BenchmarkType type = it->second.first;
        
        BenchmarkResult result(testName, type);
        result.iterations = iterations;
        
        // Розігрів (warmup)
        // Warmup
        // Разогрев
        if (config.enableWarmup && config.warmupIterations > 0) {
            if (config.verboseOutput) {
                std::cout << "Running warmup for " << testName << " (" << config.warmupIterations << " iterations)" << std::endl;
            }
            
            for (size_t i = 0; i < config.warmupIterations; ++i) {
                benchmarkFunction(1);
            }
        }
        
        // Запуск тесту
        // Run test
        // Запуск теста
        if (config.verboseOutput) {
            std::cout << "Running benchmark " << testName << " (" << iterations << " iterations)" << std::endl;
        }
        
        result.startTime = std::chrono::high_resolution_clock::now();
        benchmarkFunction(iterations);
        result.endTime = std::chrono::high_resolution_clock::now();
        
        // Обчислення результатів
        // Calculate results
        // Вычисление результатов
        result.duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
            result.endTime - result.startTime);
        
        result.averageTimePerIteration = static_cast<double>(result.duration.count()) / iterations;
        
        // Обчислення пропускної здатності
        // Calculate throughput
        // Вычисление пропускной способности
        double durationSeconds = static_cast<double>(result.duration.count()) / 1e9;
        if (durationSeconds > 0) {
            result.throughput = static_cast<double>(iterations) / durationSeconds;
        }
        
        if (config.verboseOutput) {
            std::cout << "Benchmark " << testName << " completed in " 
                      << result.duration.count() << " ns" << std::endl;
        }
        
        return result;
    }

    // Отримання результатів тестів продуктивності
    // Get performance test results
    // Получение результатов тестов производительности
    std::vector<BenchmarkResult> BenchmarkSuite::getBenchmarkResults() const {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        return benchmarkResults;
    }

    // Очищення результатів тестів продуктивності
    // Clear performance test results
    // Очистка результатов тестов производительности
    void BenchmarkSuite::clearBenchmarkResults() {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        benchmarkResults.clear();
    }

    // Експорт результатів тестів продуктивності
    // Export performance test results
    // Экспорт результатов тестов производительности
    bool BenchmarkSuite::exportResults(const std::string& format, 
                                     const std::string& outputPath) {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        std::string data = serializeBenchmarkResults(benchmarkResults, format);
        
        std::ofstream file(outputPath);
        if (!file.is_open()) {
            return false;
        }
        
        file << data;
        file.close();
        return true;
    }

    // Генерація звіту про тестування продуктивності
    // Generate performance test report
    // Генерация отчета о тестировании производительности
    std::string BenchmarkSuite::generateReport() const {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        return generateTextReport(benchmarkResults);
    }

    // Отримання конфігурації тестування продуктивності
    // Get performance testing configuration
    // Получение конфигурации тестирования производительности
    BenchmarkConfig BenchmarkSuite::getConfiguration() const {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        return config;
    }

    // Встановлення конфігурації тестування продуктивності
    // Set performance testing configuration
    // Установка конфигурации тестирования производительности
    void BenchmarkSuite::setConfiguration(const BenchmarkConfig& config) {
        std::lock_guard<std::mutex> lock(benchmarkMutex);
        this->config = config;
    }

    // Серіалізація результатів тестів продуктивності
    // Serialize performance test results
    // Сериализация результатов тестов производительности
    std::string BenchmarkSuite::serializeBenchmarkResults(const std::vector<BenchmarkResult>& results, 
                                                        const std::string& format) {
        if (format == "json") {
            return generateJsonReport(results);
        } else if (format == "csv") {
            return generateCsvReport(results);
        } else {
            return generateTextReport(results);
        }
    }

    // Генерація текстового звіту
    // Generate text report
    // Генерация текстового отчета
    std::string BenchmarkSuite::generateTextReport(const std::vector<BenchmarkResult>& results) const {
        std::ostringstream oss;
        oss << "Performance Benchmark Report\n";
        oss << "============================\n\n";
        
        for (const auto& result : results) {
            oss << "Test: " << result.testName << "\n";
            oss << "Type: ";
            switch (result.testType) {
                case BenchmarkType::CPU: oss << "CPU"; break;
                case BenchmarkType::MEMORY: oss << "Memory"; break;
                case BenchmarkType::IO: oss << "I/O"; break;
                case BenchmarkType::NETWORK: oss << "Network"; break;
                case BenchmarkType::SYNAPSE: oss << "Synapse"; break;
                case BenchmarkType::NEURON: oss << "Neuron"; break;
            }
            oss << "\n";
            
            oss << "Duration: " << result.duration.count() << " ns\n";
            oss << "Iterations: " << result.iterations << "\n";
            oss << "Average time per iteration: " << std::fixed << std::setprecision(2) 
                << result.averageTimePerIteration << " ns\n";
            oss << "Throughput: " << std::fixed << std::setprecision(2) 
                << result.throughput << " operations/s\n";
            
            if (!result.additionalInfo.empty()) {
                oss << "Additional info: " << result.additionalInfo << "\n";
            }
            
            oss << "\n";
        }
        
        return oss.str();
    }

    // Генерація JSON звіту
    // Generate JSON report
    // Генерация JSON отчета
    std::string BenchmarkSuite::generateJsonReport(const std::vector<BenchmarkResult>& results) const {
        std::ostringstream oss;
        oss << "{\n";
        oss << "  \"benchmarkResults\": [\n";
        
        for (size_t i = 0; i < results.size(); ++i) {
            const auto& result = results[i];
            oss << "    {\n";
            oss << "      \"testName\": \"" << result.testName << "\",\n";
            oss << "      \"testType\": ";
            switch (result.testType) {
                case BenchmarkType::CPU: oss << "\"CPU\""; break;
                case BenchmarkType::MEMORY: oss << "\"Memory\""; break;
                case BenchmarkType::IO: oss << "\"IO\""; break;
                case BenchmarkType::NETWORK: oss << "\"Network\""; break;
                case BenchmarkType::SYNAPSE: oss << "\"Synapse\""; break;
                case BenchmarkType::NEURON: oss << "\"Neuron\""; break;
            }
            oss << ",\n";
            oss << "      \"durationNs\": " << result.duration.count() << ",\n";
            oss << "      \"iterations\": " << result.iterations << ",\n";
            oss << "      \"averageTimePerIterationNs\": " << std::fixed << std::setprecision(2) 
                << result.averageTimePerIteration << ",\n";
            oss << "      \"throughputOpsPerSec\": " << std::fixed << std::setprecision(2) 
                << result.throughput << "\n";
            oss << "    }";
            if (i < results.size() - 1) {
                oss << ",";
            }
            oss << "\n";
        }
        
        oss << "  ]\n";
        oss << "}\n";
        
        return oss.str();
    }

    // Генерація CSV звіту
    // Generate CSV report
    // Генерация CSV отчета
    std::string BenchmarkSuite::generateCsvReport(const std::vector<BenchmarkResult>& results) const {
        std::ostringstream oss;
        oss << "Test Name,Test Type,Duration (ns),Iterations,Average Time per Iteration (ns),Throughput (ops/s)\n";
        
        for (const auto& result : results) {
            oss << "\"" << result.testName << "\",";
            
            switch (result.testType) {
                case BenchmarkType::CPU: oss << "CPU"; break;
                case BenchmarkType::MEMORY: oss << "Memory"; break;
                case BenchmarkType::IO: oss << "IO"; break;
                case BenchmarkType::NETWORK: oss << "Network"; break;
                case BenchmarkType::SYNAPSE: oss << "Synapse"; break;
                case BenchmarkType::NEURON: oss << "Neuron"; break;
            }
            oss << ",";
            
            oss << result.duration.count() << ",";
            oss << result.iterations << ",";
            oss << std::fixed << std::setprecision(2) << result.averageTimePerIteration << ",";
            oss << std::fixed << std::setprecision(2) << result.throughput << "\n";
        }
        
        return oss.str();
    }

} // namespace NeuroSync