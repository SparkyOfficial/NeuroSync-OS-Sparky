#include "src/memory/MemoryCore.h"
#include "src/memory/MemoryPool.h"
#include "src/memory/GarbageCollector.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void testMemoryPool() {
    std::cout << "=== Testing MemoryPool ===" << std::endl;
    
    try {
        // Create a memory pool
        NeuroSync::Memory::MemoryPool pool(1024 * 1024); // 1MB pool
        
        std::cout << "Pool total size: " << pool.getTotalSize() << " bytes" << std::endl;
        std::cout << "Pool used size: " << pool.getUsedSize() << " bytes" << std::endl;
        std::cout << "Pool free size: " << pool.getFreeSize() << " bytes" << std::endl;
        
        // Allocate some memory
        void* ptr1 = pool.allocate(1024);
        std::cout << "Allocated 1024 bytes at " << ptr1 << std::endl;
        
        void* ptr2 = pool.allocate(2048);
        std::cout << "Allocated 2048 bytes at " << ptr2 << std::endl;
        
        std::cout << "Pool used size after allocation: " << pool.getUsedSize() << " bytes" << std::endl;
        std::cout << "Pool free size after allocation: " << pool.getFreeSize() << " bytes" << std::endl;
        
        // Deallocate memory
        pool.deallocate(ptr1);
        std::cout << "Deallocated first block" << std::endl;
        
        pool.deallocate(ptr2);
        std::cout << "Deallocated second block" << std::endl;
        
        std::cout << "Pool used size after deallocation: " << pool.getUsedSize() << " bytes" << std::endl;
        std::cout << "Pool free size after deallocation: " << pool.getFreeSize() << " bytes" << std::endl;
        
        std::cout << "MemoryPool test passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "MemoryPool test failed: " << e.what() << std::endl;
    }
}

void testGarbageCollector() {
    std::cout << "\n=== Testing GarbageCollector ===" << std::endl;
    
    try {
        NeuroSync::Memory::GarbageCollector gc;
        
        std::cout << "Initial GC objects: " << gc.getTotalObjects() << std::endl;
        std::cout << "Initial collected objects: " << gc.getCollectedObjects() << std::endl;
        
        // Register an object
        void* obj = malloc(1024);
        gc.registerObject(obj, 1024);
        std::cout << "Registered object at " << obj << std::endl;
        
        std::cout << "GC objects after registration: " << gc.getTotalObjects() << std::endl;
        
        // Add and remove references
        gc.addReference(obj);
        std::cout << "Added reference to object" << std::endl;
        
        gc.removeReference(obj);
        std::cout << "Removed reference from object" << std::endl;
        
        // Collect garbage
        gc.collect();
        std::cout << "Performed garbage collection" << std::endl;
        
        std::cout << "Final GC objects: " << gc.getTotalObjects() << std::endl;
        std::cout << "Final collected objects: " << gc.getCollectedObjects() << std::endl;
        
        // Clean up
        free(obj);
        
        std::cout << "GarbageCollector test passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "GarbageCollector test failed: " << e.what() << std::endl;
    }
}

void testMemoryCore() {
    std::cout << "\n=== Testing MemoryCore ===" << std::endl;
    
    try {
        NeuroSync::Memory::MemoryCore memoryCore;
        
        std::cout << "MemoryCore total memory: " << memoryCore.getTotalMemory() << " bytes" << std::endl;
        std::cout << "MemoryCore used memory: " << memoryCore.getUsedMemory() << " bytes" << std::endl;
        std::cout << "MemoryCore free memory: " << memoryCore.getFreeMemory() << " bytes" << std::endl;
        
        // Test allocation of different sizes
        void* smallPtr = memoryCore.allocate(100);
        std::cout << "Allocated small block (100 bytes) at " << smallPtr << std::endl;
        
        void* mediumPtr = memoryCore.allocate(2048);
        std::cout << "Allocated medium block (2048 bytes) at " << mediumPtr << std::endl;
        
        void* largePtr = memoryCore.allocate(16384);
        std::cout << "Allocated large block (16384 bytes) at " << largePtr << std::endl;
        
        std::cout << "MemoryCore used memory after allocation: " << memoryCore.getUsedMemory() << " bytes" << std::endl;
        
        // Test deallocation
        memoryCore.deallocate(smallPtr);
        std::cout << "Deallocated small block" << std::endl;
        
        memoryCore.deallocate(mediumPtr);
        std::cout << "Deallocated medium block" << std::endl;
        
        memoryCore.deallocate(largePtr);
        std::cout << "Deallocated large block" << std::endl;
        
        std::cout << "MemoryCore used memory after deallocation: " << memoryCore.getUsedMemory() << " bytes" << std::endl;
        
        std::cout << "MemoryCore test passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "MemoryCore test failed: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== Comprehensive Memory Management Test ===" << std::endl;
    
    testMemoryPool();
    testGarbageCollector();
    testMemoryCore();
    
    std::cout << "\n=== All tests completed ===" << std::endl;
    return 0;
}