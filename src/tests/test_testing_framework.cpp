/*
 * test_testing_framework.cpp
 * Тести для тестувального фреймворку
 * Tests for the testing framework
 * Тесты для тестового фреймворка
 */

#include "../testing/TestingFramework.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace NeuroSync;

// Sample functions to test
void sampleTestFunction1() {
    ASSERT_TRUE(true);
}

void sampleTestFunction2() {
    ASSERT_EQUAL(5, 5);
}

int main() {
    std::cout << "Testing Framework Tests\n";
    std::cout << "======================\n\n";
    
    // Initialize the global testing framework
    TestingConfig config;
    config.enableVerboseOutput = true;
    config.enableColorOutput = true;
    config.stopOnFailure = false;
    
    if (!gTestingFramework->initialize(config)) {
        std::cerr << "Failed to initialize testing framework\n";
        return 1;
    }
    
    // Register test suites
    gTestingFramework->registerTestSuite("BasicTests");
    gTestingFramework->registerTestSuite("AdvancedTests");
    
    // Register tests
    gTestingFramework->registerTest("BasicTests", "SampleTest1", TestType::UNIT, sampleTestFunction1);
    gTestingFramework->registerTest("BasicTests", "SampleTest2", TestType::UNIT, sampleTestFunction2);
    
    // Run all tests
    std::cout << "Running tests...\n";
    bool success = gTestingFramework->runAllTests();
    
    // Generate and display report
    std::string report = gTestingFramework->generateReport();
    std::cout << "\nTest Report:\n";
    std::cout << report << std::endl;
    
    if (success) {
        std::cout << "\nAll tests passed!\n";
    } else {
        std::cout << "\nSome tests failed.\n";
    }
    
    return success ? 0 : 1;
}