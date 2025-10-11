# Benchmark Suite
# Набір тестів продуктивності
# Набор тестов производительности

## Overview
# Огляд
# Обзор

The Benchmark Suite is a comprehensive performance testing framework designed specifically for the NeuroSync OS Sparky microkernel. It provides tools to measure and analyze the performance of various system components including CPU operations, memory allocation, I/O operations, network communication, synapse processing, and neuron processing.

Набір тестів продуктивності - це комплексний фреймворк для тестування продуктивності, розроблений спеціально для мікроядра NeuroSync OS Sparky. Він надає інструменти для вимірювання та аналізу продуктивності різних компонентів системи, включаючи операції ЦП, виділення пам'яті, операції вводу-виводу, мережеву комунікацію, обробку синапсів та обробку нейронів.

Набор тестов производительности - это комплексный фреймворк для тестирования производительности, разработанный специально для микроядра NeuroSync OS Sparky. Он предоставляет инструменты для измерения и анализа производительности различных компонентов системы, включая операции ЦП, выделение памяти, операции ввода-вывода, сетевую коммуникацию, обработку синапсов и обработку нейронов.

## Features
# Особливості
# Особенности

- Multiple benchmark types support (CPU, Memory, I/O, Network, Synapse, Neuron)
- Підтримка кількох типів тестів продуктивності (ЦП, Пам'ять, Ввод-вивід, Мережа, Синапси, Нейрони)
- Поддержка нескольких типов тестов производительности (ЦП, Память, Ввод-вывод, Сеть, Синапсы, Нейроны)

- Configurable benchmark execution (iterations, warmup, verbose output)
- Налаштовуване виконання тестів (ітерації, розігрів, докладний вивід)
- Настраиваемое выполнение тестов (итерации, разогрев, подробный вывод)

- Warmup phase for more accurate measurements
- Фаза розігріву для більш точних вимірювань
- Фаза разогрева для более точных измерений

- Multiple output formats (text, JSON, CSV)
- Кілька форматів виводу (текст, JSON, CSV)
- Несколько форматов вывода (текст, JSON, CSV)

- Export/import benchmark results
- Експорт/імпорт результатів тестів
- Экспорт/импорт результатов тестов

## Usage
# Використання
# Использование

### Basic Example
# Базовий приклад
# Базовый пример

```cpp
#include "BenchmarkSuite.h"

using namespace NeuroSync;

// Initialize global benchmark suite
std::unique_ptr<BenchmarkSuite> NeuroSync::gBenchmarkSuite = std::make_unique<BenchmarkSuite>();

// Sample benchmark function
void benchmarkVectorAllocation(size_t iterations) {
    for (size_t i = 0; i < iterations; ++i) {
        std::vector<int> vec(1000);
        for (size_t j = 0; j < vec.size(); ++j) {
            vec[j] = static_cast<int>(j);
        }
    }
}

int main() {
    // Configure benchmark suite
    BenchmarkConfig config;
    config.defaultIterations = 1000;
    config.enableWarmup = true;
    
    gBenchmarkSuite->initialize(config);
    
    // Register benchmark
    gBenchmarkSuite->registerBenchmark("VectorAllocation", BenchmarkType::MEMORY, benchmarkVectorAllocation);
    
    // Run benchmark
    BenchmarkResult result = gBenchmarkSuite->runBenchmark("VectorAllocation", 1000);
    
    // Generate report
    std::string report = gBenchmarkSuite->generateReport();
    std::cout << report << std::endl;
    
    return 0;
}
```

## API Reference
# Посилання на API
# Ссылка на API

### BenchmarkSuite Class
# Клас BenchmarkSuite
# Класс BenchmarkSuite

#### Constructor
# Конструктор
# Конструктор
```cpp
BenchmarkSuite();
```

#### initialize
# ініціалізація
# инициализация
```cpp
bool initialize(const BenchmarkConfig& config);
```
Initializes the benchmark suite with the provided configuration.
Ініціалізує набір тестів продуктивності із наданою конфігурацією.
Инициализирует набор тестов производительности с предоставленной конфигурацией.

#### registerBenchmark
# реєстрація тесту продуктивності
# регистрация теста производительности
```cpp
void registerBenchmark(const std::string& testName,
                       BenchmarkType type,
                       std::function<void(size_t)> benchmarkFunction);
```
Registers a benchmark function with the specified name and type.
Реєструє функцію тесту продуктивності з вказаним ім'ям і типом.
Регистрирует функцию теста производительности с указанным именем и типом.

#### runBenchmark
# запуск тесту продуктивності
# запуск теста производительности
```cpp
BenchmarkResult runBenchmark(const std::string& testName, 
                             size_t iterations = 0);
```
Runs a specific benchmark and returns the result.
Запускає конкретний тест продуктивності та повертає результат.
Запускает конкретный тест производительности и возвращает результат.

#### runAllBenchmarks
# запуск усіх тестів продуктивності
# запуск всех тестов производительности
```cpp
std::vector<BenchmarkResult> runAllBenchmarks();
```
Runs all registered benchmarks and returns their results.
Запускає всі зареєстровані тести продуктивності та повертає їхні результати.
Запускает все зарегистрированные тесты производительности и возвращает их результаты.

#### generateReport
# генерація звіту
# генерация отчета
```cpp
std::string generateReport() const;
```
Generates a benchmark report in the configured format.
Генерує звіт про тести продуктивності у налаштованому форматі.
Генерирует отчет о тестах производительности в настроенном формате.

## Benchmark Types
# Типи тестів продуктивності
# Типы тестов производительности

The framework supports the following benchmark types:

Фреймворк підтримує наступні типи тестів продуктивності:

Фреймворк поддерживает следующие типы тестов производительности:

- `CPU` - CPU intensive operations
- `CPU` - Операції, що інтенсивно використовують ЦП
- `CPU` - Операции, интенсивно использующие ЦП

- `MEMORY` - Memory allocation and manipulation
- `MEMORY` - Виділення та маніпуляції пам'яттю
- `MEMORY` - Выделение и манипуляции памятью

- `IO` - Input/Output operations
- `IO` - Операції вводу-виводу
- `IO` - Операции ввода-вывода

- `NETWORK` - Network communication
- `NETWORK` - Мережева комунікація
- `NETWORK` - Сетевая коммуникация

- `SYNAPSE` - Synapse processing
- `SYNAPSE` - Обробка синапсів
- `SYNAPSE` - Обработка синапсов

- `NEURON` - Neuron processing
- `NEURON` - Обробка нейронів
- `NEURON` - Обработка нейронов

## Configuration
# Конфігурація
# Конфигурация

The BenchmarkConfig structure allows you to configure various aspects of the benchmark suite:

Структура BenchmarkConfig дозволяє налаштувати різні аспекти набору тестів продуктивності:

Структура BenchmarkConfig позволяет настроить различные аспекты набора тестов производительности:

```cpp
struct BenchmarkConfig {
    size_t defaultIterations;      // Default number of iterations
                                   // Кількість ітерацій за замовчуванням
                                   // Количество итераций по умолчанию
    
    bool enableWarmup;             // Enable warmup phase
                                   // Увімкнути фазу розігріву
                                   // Включить фазу разогрева
    
    size_t warmupIterations;       // Number of warmup iterations
                                   // Кількість ітерацій розігріву
                                   // Количество итераций разогрева
    
    bool verboseOutput;            // Enable verbose output
                                   // Увімкнути докладний вивід
                                   // Включить подробный вывод
    
    std::string outputFormat;      // Output format ("text", "json", "csv")
                                   // Формат виводу ("text", "json", "csv")
                                   // Формат вывода ("text", "json", "csv")
    
    std::string outputPath;        // Output path for benchmark results
                                   // Шлях виводу для результатів тестів
                                   // Путь вывода для результатов тестов
};
```

## Benchmark Result Structure
# Структура результату тесту продуктивності
# Структура результата теста производительности

The BenchmarkResult structure contains detailed information about a benchmark execution:

Структура BenchmarkResult містить детальну інформацію про виконання тесту продуктивності:

Структура BenchmarkResult содержит подробную информацию о выполнении теста производительности:

```cpp
struct BenchmarkResult {
    std::string testName;                    // Name of the benchmark
                                             // Назва тесту
                                             // Название теста
    
    BenchmarkType testType;                  // Type of the benchmark
                                             // Тип тесту
                                             // Тип теста
    
    std::chrono::high_resolution_clock::time_point startTime;  // Start time
                                                               // Час початку
                                                               // Время начала
    
    std::chrono::high_resolution_clock::time_point endTime;    // End time
                                                               // Час закінчення
                                                               // Время окончания
    
    std::chrono::nanoseconds duration;       // Total duration
                                             // Загальна тривалість
                                             // Общая продолжительность
    
    size_t iterations;                       // Number of iterations
                                             // Кількість ітерацій
                                             // Количество итераций
    
    double averageTimePerIteration;          // Average time per iteration (ns)
                                             // Середній час на ітерацію (нс)
                                             // Среднее время на итерацию (нс)
    
    size_t dataSize;                         // Size of data processed (bytes)
                                             // Розмір оброблених даних (байти)
                                             // Размер обработанных данных (байты)
    
    double throughput;                       // Throughput (operations/s or MB/s)
                                             // Пропускна здатність (операцій/с або МБ/с)
                                             // Пропускная способность (операций/с или МБ/с)
    
    std::string additionalInfo;              // Additional information
                                             // Додаткова інформація
                                             // Дополнительная информация
};
```