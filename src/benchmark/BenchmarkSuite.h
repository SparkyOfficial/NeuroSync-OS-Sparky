#ifndef BENCHMARK_SUITE_H
#define BENCHMARK_SUITE_H

/*
 * BenchmarkSuite.h
 * Набір тестів продуктивності для NeuroSync OS Sparky
 * Benchmark suite for NeuroSync OS Sparky
 * Набор тестов производительности для NeuroSync OS Sparky
 */

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <functional>
#include <memory>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <mutex>

namespace NeuroSync {

    // Типи тестів продуктивності
    // Performance test types
    // Типы тестов производительности
    enum class BenchmarkType {
        CPU,            // Тестування ЦП
        // CPU testing
        // Тестирование ЦП
        
        MEMORY,         // Тестування пам'яті
        // Memory testing
        // Тестирование памяти
        
        IO,             // Тестування вводу-виводу
        // I/O testing
        // Тестирование ввода-вывода
        
        NETWORK,        // Тестування мережі
        // Network testing
        // Тестирование сети
        
        SYNAPSE,        // Тестування синапсів
        // Synapse testing
        // Тестирование синапсов
        
        NEURON          // Тестування нейронів
        // Neuron testing
        // Тестирование нейронов
    };

    // Структура результату тесту продуктивності
    // Performance test result structure
    // Структура результата теста производительности
    struct BenchmarkResult {
        std::string testName;
        BenchmarkType testType;
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;
        std::chrono::nanoseconds duration;
        size_t iterations;
        double averageTimePerIteration;
        size_t dataSize;  // Size of data processed in bytes
        double throughput; // Throughput in MB/s or operations/s
        std::string additionalInfo;
        
        BenchmarkResult() : testType(BenchmarkType::CPU), 
                           duration(0), iterations(0), 
                           averageTimePerIteration(0.0),
                           dataSize(0), throughput(0.0) {}
        
        BenchmarkResult(const std::string& name, BenchmarkType type)
            : testName(name), testType(type), 
              duration(0), iterations(0), 
              averageTimePerIteration(0.0),
              dataSize(0), throughput(0.0) {}
    };

    // Конфігурація тестування продуктивності
    // Performance testing configuration
    // Конфигурация тестирования производительности
    struct BenchmarkConfig {
        size_t defaultIterations;      // Кількість ітерацій за замовчуванням
        // Default number of iterations
        // Количество итераций по умолчанию
        
        bool enableWarmup;             // Увімкнути розігрів
        // Enable warmup
        // Включить разогрев
        
        size_t warmupIterations;       // Кількість ітерацій розігріву
        // Number of warmup iterations
        // Количество итераций разогрева
        
        bool verboseOutput;            // Докладний вивід
        // Verbose output
        // Подробный вывод
        
        std::string outputFormat;      // Формат виводу ("text", "json", "csv")
        // Output format ("text", "json", "csv")
        // Формат вывода ("text", "json", "csv")
        
        std::string outputPath;        // Шлях виводу
        // Output path
        // Путь вывода
        
        BenchmarkConfig() : defaultIterations(1000),
                           enableWarmup(true),
                           warmupIterations(100),
                           verboseOutput(false),
                           outputFormat("text"),
                           outputPath("./benchmark_results") {}
    };

    // Інтерфейс набору тестів продуктивності
    // Performance benchmark suite interface
    // Интерфейс набора тестов производительности
    class BenchmarkSuite {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        BenchmarkSuite();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~BenchmarkSuite();
        
        // Ініціалізація набору тестів продуктивності
        // Initialize benchmark suite
        // Инициализация набора тестов производительности
        virtual bool initialize(const BenchmarkConfig& config);
        
        // Реєстрація тесту продуктивності
        // Register performance test
        // Регистрация теста производительности
        virtual void registerBenchmark(const std::string& testName,
                                     BenchmarkType type,
                                     std::function<void(size_t)> benchmarkFunction);
        
        // Запуск усіх тестів продуктивності
        // Run all performance tests
        // Запуск всех тестов производительности
        virtual std::vector<BenchmarkResult> runAllBenchmarks();
        
        // Запуск конкретного тесту продуктивності
        // Run specific performance test
        // Запуск конкретного теста производительности
        virtual BenchmarkResult runBenchmark(const std::string& testName, 
                                           size_t iterations = 0);
        
        // Отримання результатів тестів продуктивності
        // Get performance test results
        // Получение результатов тестов производительности
        virtual std::vector<BenchmarkResult> getBenchmarkResults() const;
        
        // Очищення результатів тестів продуктивності
        // Clear performance test results
        // Очистка результатов тестов производительности
        virtual void clearBenchmarkResults();
        
        // Експорт результатів тестів продуктивності
        // Export performance test results
        // Экспорт результатов тестов производительности
        virtual bool exportResults(const std::string& format, 
                                 const std::string& outputPath);
        
        // Генерація звіту про тестування продуктивності
        // Generate performance test report
        // Генерация отчета о тестировании производительности
        virtual std::string generateReport() const;
        
        // Отримання конфігурації тестування продуктивності
        // Get performance testing configuration
        // Получение конфигурации тестирования производительности
        BenchmarkConfig getConfiguration() const;
        
        // Встановлення конфігурації тестування продуктивності
        // Set performance testing configuration
        // Установка конфигурации тестирования производительности
        void setConfiguration(const BenchmarkConfig& config);
        
    protected:
        BenchmarkConfig config;
        std::map<std::string, std::pair<BenchmarkType, std::function<void(size_t)>>> benchmarkRegistry;
        std::vector<BenchmarkResult> benchmarkResults;
        mutable std::mutex benchmarkMutex;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        virtual std::string serializeBenchmarkResults(const std::vector<BenchmarkResult>& results, 
                                                    const std::string& format);
        virtual std::string generateTextReport(const std::vector<BenchmarkResult>& results) const;
        virtual std::string generateJsonReport(const std::vector<BenchmarkResult>& results) const;
        virtual std::string generateCsvReport(const std::vector<BenchmarkResult>& results) const;
    };

    // Глобальний набір тестів продуктивності
    // Global benchmark suite
    // Глобальный набор тестов производительности
    extern std::unique_ptr<BenchmarkSuite> gBenchmarkSuite;

} // namespace NeuroSync

#endif // BENCHMARK_SUITE_H