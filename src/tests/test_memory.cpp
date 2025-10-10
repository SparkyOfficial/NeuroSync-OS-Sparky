#include "memory/MemoryCore.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace NeuroSync::Memory;

void testMemoryPoolAllocation() {
    std::cout << "Тестування виділення пам'яті з пулу..." << std::endl;
    
    MemoryCore memoryCore;
    
    // Тестування виділення малого блоку
    // Testing small block allocation
    // Тестування виділення малого блоку
    void* ptr1 = memoryCore.allocate(100);
    assert(ptr1 != nullptr);
    
    // Тестування виділення середнього блоку
    // Testing medium block allocation
    // Тестування виділення середнього блоку
    void* ptr2 = memoryCore.allocate(1024);
    assert(ptr2 != nullptr);
    
    // Тестування виділення великого блоку
    // Testing large block allocation
    // Тестування виділення великого блоку
    void* ptr3 = memoryCore.allocate(8192);
    assert(ptr3 != nullptr);
    
    // Звільнення блоків
    // Freeing blocks
    // Звільнення блоків
    memoryCore.deallocate(ptr1);
    memoryCore.deallocate(ptr2);
    memoryCore.deallocate(ptr3);
    
    std::cout << "Тестування виділення пам'яті з пулу пройдено успішно!" << std::endl;
}

void testGarbageCollection() {
    std::cout << "Тестування збору сміття..." << std::endl;
    
    MemoryCore memoryCore;
    
    // Створення об'єкта для збору сміття
    // Creating an object for garbage collection
    // Створення об'єкта для збору сміття
    void* obj = memoryCore.allocate(1024);
    assert(obj != nullptr);
    
    // Реєстрація об'єкта для збору сміття
    // Registering object for garbage collection
    // Реєстрація об'єкта для збору сміття
    memoryCore.registerForGC(obj, 1024);
    
    // Перевірка кількості об'єктів
    // Checking object count
    // Перевірка кількості об'єктів
    assert(memoryCore.getGCTotalObjects() == 1);
    
    // Додавання посилання
    // Adding reference
    // Додавання посилання
    memoryCore.addReference(obj);
    
    // Видалення посилання
    // Removing reference
    // Видалення посилання
    memoryCore.removeReference(obj);
    
    // Виконання збору сміття
    // Performing garbage collection
    // Виконання збору сміття
    memoryCore.collectGarbage();
    
    std::cout << "Тестування збору сміття пройдено успішно!" << std::endl;
}

void testMemoryStatistics() {
    std::cout << "Тестування статистики пам'яті..." << std::endl;
    
    MemoryCore memoryCore;
    
    // Отримання початкової статистики
    // Getting initial statistics
    // Отримання початкової статистики
    size_t initialTotal = memoryCore.getTotalMemory();
    size_t initialUsed = memoryCore.getUsedMemory();
    size_t initialFree = memoryCore.getFreeMemory();
    
    // Виділення пам'яті
    // Allocating memory
    // Виділення пам'яті
    void* ptr = memoryCore.allocate(512);
    assert(ptr != nullptr);
    
    // Перевірка статистики після виділення
    // Checking statistics after allocation
    // Перевірка статистики після виділення
    size_t allocatedUsed = memoryCore.getUsedMemory();
    assert(allocatedUsed >= initialUsed + 512);
    
    // Звільнення пам'яті
    // Freeing memory
    // Звільнення пам'яті
    memoryCore.deallocate(ptr);
    
    std::cout << "Тестування статистики пам'яті пройдено успішно!" << std::endl;
}

void testPoolTypes() {
    std::cout << "Тестування типів пулу..." << std::endl;
    
    MemoryCore memoryCore;
    
    // Тестування пулу для малих об'єктів
    // Testing small object pool
    // Тестування пулу для малих об'єктів
    void* smallPtr = memoryCore.allocate(100);
    assert(smallPtr != nullptr);
    memoryCore.deallocate(smallPtr);
    
    // Тестування пулу для середніх об'єктів
    // Testing medium object pool
    // Тестування пулу для середніх об'єктів
    void* mediumPtr = memoryCore.allocate(2048);
    assert(mediumPtr != nullptr);
    memoryCore.deallocate(mediumPtr);
    
    // Тестування пулу для великих об'єктів
    // Testing large object pool
    // Тестування пулу для великих об'єктів
    void* largePtr = memoryCore.allocate(16384);
    assert(largePtr != nullptr);
    memoryCore.deallocate(largePtr);
    
    std::cout << "Тестування типів пулу пройдено успішно!" << std::endl;
}

int main() {
    std::cout << "=== Запуск тестів управління пам'яттю ===" << std::endl;
    
    try {
        testMemoryPoolAllocation();
        testGarbageCollection();
        testMemoryStatistics();
        testPoolTypes();
        
        std::cout << "\n=== Усі тести управління пам'яттю пройдено успішно! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Помилка під час тестування: " << e.what() << std::endl;
        return 1;
    }
}