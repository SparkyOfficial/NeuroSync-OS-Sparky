#include "src/diagnostics/Diagnostics.h"
#include <iostream>

int main() {
    std::cout << "Testing Diagnostics system..." << std::endl;
    
    try {
        NeuroSync::Diagnostics::Diagnostics diagnostics;
        
        // Test basic functionality
        diagnostics.startTracing();
        diagnostics.logEvent(1, "TEST", "Diagnostics system test");
        diagnostics.stopTracing();
        
        // Test reports
        std::string report = diagnostics.getTextReport();
        if (!report.empty()) {
            std::cout << "Successfully generated text report" << std::endl;
        } else {
            std::cout << "Failed to generate text report" << std::endl;
            return 1;
        }
        
        // Test performance metrics
        diagnostics.startPerformanceMonitoring();
        diagnostics.updatePerformanceMetrics(45.5, 1024000, 500, 2000, 100);
        auto metrics = diagnostics.getLatestMetrics();
        
        std::cout << "CPU Usage: " << metrics.cpuUsage << "%" << std::endl;
        std::cout << "Memory Usage: " << metrics.memoryUsage << " bytes" << std::endl;
        
        diagnostics.stopPerformanceMonitoring();
        
        std::cout << "Diagnostics system test completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}