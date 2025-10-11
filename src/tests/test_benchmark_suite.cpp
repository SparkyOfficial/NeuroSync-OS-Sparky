/*
 * test_benchmark_suite.cpp
 * Тести для набору тестів продуктивності
 * Tests for the benchmark suite
 * Тесты для набора тестов производительности
 */

#include "../benchmark/BenchmarkSuite.h"
#include <iostream>
#include <cassert>

using namespace NeuroSync;

// Test functions for the benchmark suite itself
void testInitialization() {
    BenchmarkConfig config;
    config.defaultIterations = 500;
    config.enableWarmup = false;
    config.verboseOutput = true;
    
    assert(gBenchmarkSuite->initialize(config));
    
    BenchmarkConfig retrievedConfig = gBenchmarkSuite->getConfiguration();
    assert(retrievedConfig.defaultIterations == 500);
    assert(retrievedConfig.enableWarmup == false);
    assert(retrievedConfig.verboseOutput == true);
}

void testBenchmarkRegistration() {
    // Simple test function
    auto testFunction = [](size_t iterations) {
        for (size_t i = 0; i < iterations; ++i) {
            volatile int x = i * 2;
        }
    };
    
    gBenchmarkSuite->registerBenchmark("RegistrationTest", BenchmarkType::CPU, testFunction);
    
    // Try to run the registered benchmark
    BenchmarkResult result = gBenchmarkSuite->runBenchmark("RegistrationTest", 10);
    
    assert(result.testName == "RegistrationTest");
    assert(result.testType == BenchmarkType::CPU);
    assert(result.iterations == 10);
    assert(result.duration.count() >= 0);
}

void testBenchmarkExecution() {
    // Simple test function
    auto testFunction = [](size_t iterations) {
        volatile double sum = 0.0;
        for (size_t i = 0; i < iterations; ++i) {
            sum += i;
        }
    };
    
    gBenchmarkSuite->registerBenchmark("ExecutionTest", BenchmarkType::CPU, testFunction);
    
    // Run benchmark
    BenchmarkResult result = gBenchmarkSuite->runBenchmark("ExecutionTest", 100);
    
    assert(result.testName == "ExecutionTest");
    assert(result.iterations == 100);
    assert(result.duration.count() >= 0);
    assert(result.averageTimePerIteration >= 0);
}

void testMultipleBenchmarks() {
    // Test function 1
    auto testFunction1 = [](size_t iterations) {
        std::vector<int> vec(iterations);
        for (size_t i = 0; i < iterations; ++i) {
            vec[i] = static_cast<int>(i);
        }
    };
    
    // Test function 2
    auto testFunction2 = [](size_t iterations) {
        std::string str;
        for (size_t i = 0; i < iterations; ++i) {
            str += "a";
        }
    };
    
    gBenchmarkSuite->registerBenchmark("VectorTest", BenchmarkType::MEMORY, testFunction1);
    gBenchmarkSuite->registerBenchmark("StringTest", BenchmarkType::CPU, testFunction2);
    
    // Run all benchmarks
    std::vector<BenchmarkResult> results = gBenchmarkSuite->runAllBenchmarks();
    
    assert(results.size() >= 2);
    
    // Check that we have results for both benchmarks
    bool foundVectorTest = false;
    bool foundStringTest = false;
    
    for (const auto& result : results) {
        if (result.testName == "VectorTest") {
            foundVectorTest = true;
            assert(result.testType == BenchmarkType::MEMORY);
        } else if (result.testName == "StringTest") {
            foundStringTest = true;
            assert(result.testType == BenchmarkType::CPU);
        }
    }
    
    assert(foundVectorTest);
    assert(foundStringTest);
}

void testReportGeneration() {
    // Register and run a simple benchmark
    gBenchmarkSuite->registerBenchmark("TestBenchmark", BenchmarkType::CPU, 
        [](size_t iterations) {
            for (size_t i = 0; i < iterations; ++i) {
                // Simple operation
                volatile int x = i * 2;
            }
        });
    
    gBenchmarkSuite->runBenchmark("TestBenchmark", 100);
    
    // Test text report generation
    std::string textReport = gBenchmarkSuite->generateReport();
    assert(!textReport.empty());
    assert(textReport.find("TestBenchmark") != std::string::npos);
    
    // Test export functionality instead of direct serialization
    // Create temporary files for export
    bool jsonExportSuccess = gBenchmarkSuite->exportResults("json", "./temp_benchmark_results.json");
    assert(jsonExportSuccess);
    
    bool csvExportSuccess = gBenchmarkSuite->exportResults("csv", "./temp_benchmark_results.csv");
    assert(csvExportSuccess);
    
    // Clean up temporary files
    std::remove("./temp_benchmark_results.json");
    std::remove("./temp_benchmark_results.csv");
}

int main() {
    std::cout << "Benchmark Suite Self-Tests\n";
    std::cout << "=========================\n\n";
    
    // Configure benchmark suite
    BenchmarkConfig config;
    config.defaultIterations = 10;
    config.enableWarmup = false;
    config.verboseOutput = true;
    
    if (!gBenchmarkSuite->initialize(config)) {
        std::cerr << "Failed to initialize benchmark suite\n";
        return 1;
    }
    
    std::cout << "Running Benchmark Suite self-tests...\n";
    
    try {
        testInitialization();
        std::cout << "✓ Initialization test passed\n";
        
        testBenchmarkRegistration();
        std::cout << "✓ Benchmark registration test passed\n";
        
        testBenchmarkExecution();
        std::cout << "✓ Benchmark execution test passed\n";
        
        testMultipleBenchmarks();
        std::cout << "✓ Multiple benchmarks test passed\n";
        
        testReportGeneration();
        std::cout << "✓ Report generation test passed\n";
        
        std::cout << "\nAll self-tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception\n";
        return 1;
    }
}