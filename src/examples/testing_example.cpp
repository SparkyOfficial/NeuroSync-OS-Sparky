/*
 * testing_example.cpp
 * Приклад використання тестувального фреймворку
 * Example of using the testing framework
 * Пример использования тестового фреймворка
 */

#include "../testing/TestingFramework.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace NeuroSync;

// Sample functions to test
int add(int a, int b) {
    return a + b;
}

bool isEven(int num) {
    return num % 2 == 0;
}

void throwException() {
    throw std::runtime_error("Test exception");
}

// Test functions
void testAddition() {
    ASSERT_EQUAL(4, add(2, 2));
    ASSERT_EQUAL(0, add(-1, 1));
    ASSERT_EQUAL(100, add(50, 50));
}

void testEvenNumbers() {
    ASSERT_TRUE(isEven(2));
    ASSERT_TRUE(isEven(4));
    ASSERT_FALSE(isEven(3));
    ASSERT_FALSE(isEven(7));
}

void testExceptions() {
    ASSERT_THROW(throwException(), std::runtime_error);
    ASSERT_NO_THROW([]() { return 42; }());
}

void testPerformance() {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Simulate some work
    for (int i = 0; i < 1000; ++i) {
        add(i, i + 1);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // This is just a demo - in real performance tests, you would compare against thresholds
    ASSERT_TRUE(duration.count() >= 0); // Always true, just to have an assertion
}

void testStress() {
    // Stress test with many assertions
    for (int i = 0; i < 100; ++i) {
        ASSERT_TRUE(i >= 0);
        ASSERT_TRUE(i < 100);
        ASSERT_EQUAL(i, i);
    }
}

int main() {
    std::cout << "Testing Framework Example\n";
    std::cout << "========================\n\n";
    
    // Configure testing framework
    TestingConfig config;
    config.enableVerboseOutput = true;
    config.enableColorOutput = true;
    config.stopOnFailure = false;
    config.outputFormat = "text";
    config.maxConcurrency = 2;
    
    if (!gTestingFramework->initialize(config)) {
        std::cerr << "Failed to initialize testing framework\n";
        return 1;
    }
    
    // Register test suites
    gTestingFramework->registerTestSuite("MathTests");
    gTestingFramework->registerTestSuite("LogicTests");
    gTestingFramework->registerTestSuite("ExceptionTests");
    gTestingFramework->registerTestSuite("PerformanceTests");
    gTestingFramework->registerTestSuite("StressTests");
    
    // Register tests
    gTestingFramework->registerTest("MathTests", "AdditionTest", TestType::UNIT, testAddition);
    gTestingFramework->registerTest("LogicTests", "EvenNumbersTest", TestType::UNIT, testEvenNumbers);
    gTestingFramework->registerTest("ExceptionTests", "ExceptionHandlingTest", TestType::UNIT, testExceptions);
    gTestingFramework->registerTest("PerformanceTests", "BasicPerformanceTest", TestType::PERFORMANCE, testPerformance);
    gTestingFramework->registerTest("StressTests", "StressTest", TestType::STRESS, testStress);
    
    // Run all tests
    std::cout << "Running all tests...\n";
    bool success = gTestingFramework->runAllTests();
    
    // Generate and display report
    std::string report = gTestingFramework->generateReport();
    std::cout << "\nTest Report:\n";
    std::cout << report << std::endl;
    
    // Export results
    gTestingFramework->exportResults("text", "./test_results.txt");
    
    std::cout << "\nTest results exported to ./test_results.txt\n";
    
    return success ? 0 : 1;
}