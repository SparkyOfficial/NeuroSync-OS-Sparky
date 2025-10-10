#include "src/memory/MemoryCore.h"
#include <iostream>

int main() {
    std::cout << "Testing MemoryCore..." << std::endl;
    
    try {
        NeuroSync::Memory::MemoryCore memoryCore;
        
        // Test basic allocation
        void* ptr = memoryCore.allocate(1024);
        if (ptr) {
            std::cout << "Successfully allocated 1024 bytes" << std::endl;
            memoryCore.deallocate(ptr);
            std::cout << "Successfully deallocated memory" << std::endl;
        } else {
            std::cout << "Failed to allocate memory" << std::endl;
            return 1;
        }
        
        // Test statistics
        std::cout << "Total memory: " << memoryCore.getTotalMemory() << " bytes" << std::endl;
        std::cout << "Used memory: " << memoryCore.getUsedMemory() << " bytes" << std::endl;
        std::cout << "Free memory: " << memoryCore.getFreeMemory() << " bytes" << std::endl;
        
        std::cout << "MemoryCore test completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}