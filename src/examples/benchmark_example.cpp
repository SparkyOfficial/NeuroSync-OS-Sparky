/*
 * benchmark_example.cpp
 * Приклад використання набору тестів продуктивності
 * Example of using the benchmark suite
 * Пример использования набора тестов производительности
 */

#include "../benchmark/BenchmarkSuite.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstring>

using namespace NeuroSync;

// Sample functions to benchmark
void benchmarkVectorAllocation(size_t iterations) {
    for (size_t i = 0; i < iterations; ++i) {
        std::vector<int> vec(1000);
        for (size_t j = 0; j < vec.size(); ++j) {
            vec[j] = static_cast<int>(j);
        }
    }
}

void benchmarkStringConcatenation(size_t iterations) {
    for (size_t i = 0; i < iterations; ++i) {
        std::string str;
        for (int j = 0; j < 100; ++j) {
            str += "test";
        }
    }
}

void benchmarkMathOperations(size_t iterations) {
    volatile double result = 0.0;
    for (size_t i = 0; i < iterations; ++i) {
        for (int j = 0; j < 1000; ++j) {
            result += std::sqrt(static_cast<double>(j));
            result += std::sin(static_cast<double>(j));
            result += std::cos(static_cast<double>(j));
        }
    }
}

void benchmarkMemoryCopy(size_t iterations) {
    const size_t dataSize = 1024 * 1024; // 1MB
    std::vector<char> source(dataSize, 'A');
    std::vector<char> destination(dataSize);
    
    for (size_t i = 0; i < iterations; ++i) {
        std::memcpy(destination.data(), source.data(), dataSize);
    }
}

int main() {
    std::cout << "Benchmark Suite Example\n";
    std::cout << "======================\n\n";
    
    // Configure benchmark suite
    BenchmarkConfig config;
    config.defaultIterations = 1000;
    config.enableWarmup = true;
    config.warmupIterations = 100;
    config.verboseOutput = true;
    config.outputFormat = "text";
    
    if (!gBenchmarkSuite->initialize(config)) {
        std::cerr << "Failed to initialize benchmark suite\n";
        return 1;
    }
    
    // Register benchmarks
    gBenchmarkSuite->registerBenchmark("VectorAllocation", BenchmarkType::MEMORY, benchmarkVectorAllocation);
    gBenchmarkSuite->registerBenchmark("StringConcatenation", BenchmarkType::CPU, benchmarkStringConcatenation);
    gBenchmarkSuite->registerBenchmark("MathOperations", BenchmarkType::CPU, benchmarkMathOperations);
    gBenchmarkSuite->registerBenchmark("MemoryCopy", BenchmarkType::MEMORY, benchmarkMemoryCopy);
    
    // Run all benchmarks
    std::cout << "Running all benchmarks...\n";
    std::vector<BenchmarkResult> results = gBenchmarkSuite->runAllBenchmarks();
    
    // Generate and display report
    std::string report = gBenchmarkSuite->generateReport();
    std::cout << "\nBenchmark Report:\n";
    std::cout << report << std::endl;
    
    // Export results
    gBenchmarkSuite->exportResults("json", "./benchmark_results.json");
    gBenchmarkSuite->exportResults("csv", "./benchmark_results.csv");
    
    std::cout << "\nBenchmark results exported to ./benchmark_results.json and ./benchmark_results.csv\n";
    
    return 0;
}