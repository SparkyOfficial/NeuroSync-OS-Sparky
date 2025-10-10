#include "memory/MemoryCore.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace NeuroSync::Memory;

// Приклад класу для тестування управління пам'яттю
// Example class for testing memory management
// Приклад класу для тестування управління пам'яттю
class TestObject {
public:
    TestObject(int id, size_t size) : id(id), dataSize(size) {
        // Виділити пам'ять для даних
        // Allocate memory for data
        // Виділити пам'ять для даних
        data = new char[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<char>(id + i);
        }
    }
    
    ~TestObject() {
        // Звільнити пам'ять даних
        // Free data memory
        // Звільнити пам'ять даних
        delete[] data;
    }
    
    int getId() const { return id; }
    size_t getSize() const { return dataSize; }
    
private:
    int id;
    size_t dataSize;
    char* data;
};

// Функція для тестування пулу пам'яті
// Function to test memory pool
// Функція для тестування пулу пам'яті
void testMemoryPool(MemoryCore& memoryCore) {
    std::cout << "=== Тестування пулу пам'яті ===" << std::endl;
    
    // Отримати початкову статистику
    // Get initial statistics
    // Отримати початкову статистику
    size_t initialUsed = memoryCore.getUsedMemory();
    std::cout << "Початкова використана пам'ять: " << initialUsed << " байт" << std::endl;
    
    // Виділити кілька блоків пам'яті різного розміру
    // Allocate several memory blocks of different sizes
    // Виділити кілька блоків пам'яті різного розміру
    std::vector<void*> pointers;
    
    // Виділити малі блоки (до 256 байт)
    // Allocate small blocks (up to 256 bytes)
    // Виділити малі блоки (до 256 байт)
    for (int i = 0; i < 10; ++i) {
        void* ptr = memoryCore.allocate(100 + i * 10);
        if (ptr) {
            pointers.push_back(ptr);
            std::cout << "Виділено малий блок #" << i << " розміром " << (100 + i * 10) << " байт" << std::endl;
        }
    }
    
    // Виділити середні блоки (256 байт - 4KB)
    // Allocate medium blocks (256 bytes - 4KB)
    // Виділити середні блоки (256 байт - 4KB)
    for (int i = 0; i < 5; ++i) {
        void* ptr = memoryCore.allocate(512 + i * 512);
        if (ptr) {
            pointers.push_back(ptr);
            std::cout << "Виділено середній блок #" << i << " розміром " << (512 + i * 512) << " байт" << std::endl;
        }
    }
    
    // Виділити великі блоки (понад 4KB)
    // Allocate large blocks (over 4KB)
    // Виділити великі блоки (понад 4KB)
    for (int i = 0; i < 3; ++i) {
        void* ptr = memoryCore.allocate(8192 + i * 4096);
        if (ptr) {
            pointers.push_back(ptr);
            std::cout << "Виділено великий блок #" << i << " розміром " << (8192 + i * 4096) << " байт" << std::endl;
        }
    }
    
    // Отримати статистику після виділення
    // Get statistics after allocation
    // Отримати статистику після виділення
    size_t allocatedUsed = memoryCore.getUsedMemory();
    std::cout << "Використана пам'ять після виділення: " << allocatedUsed << " байт" << std::endl;
    std::cout << "Виділено додатково: " << (allocatedUsed - initialUsed) << " байт" << std::endl;
    
    // Звільнити всі блоки
    // Free all blocks
    // Звільнити всі блоки
    for (void* ptr : pointers) {
        memoryCore.deallocate(ptr);
    }
    
    // Отримати фінальну статистику
    // Get final statistics
    // Отримати фінальну статистику
    size_t finalUsed = memoryCore.getUsedMemory();
    std::cout << "Використана пам'ять після звільнення: " << finalUsed << " байт" << std::endl;
    std::cout << "Різниця після звільнення: " << (finalUsed - initialUsed) << " байт" << std::endl;
}

// Функція для тестування збору сміття
// Function to test garbage collection
// Функція для тестування збору сміття
void testGarbageCollection(MemoryCore& memoryCore) {
    std::cout << "\n=== Тестування збору сміття ===" << std::endl;
    
    // Отримати початкову статистику збору сміття
    // Get initial garbage collection statistics
    // Отримати початкову статистику збору сміття
    size_t initialObjects = memoryCore.getGCTotalObjects();
    size_t initialCollected = memoryCore.getGCCollectedObjects();
    std::cout << "Початкова кількість об'єктів: " << initialObjects << std::endl;
    std::cout << "Початкова кількість зібраних об'єктів: " << initialCollected << std::endl;
    
    // Створити кілька об'єктів і зареєструвати їх для збору сміття
    // Create several objects and register them for garbage collection
    // Створити кілька об'єктів і зареєструвати їх для збору сміття
    std::vector<void*> gcObjects;
    for (int i = 0; i < 5; ++i) {
        void* obj = memoryCore.allocate(1024);
        if (obj) {
            gcObjects.push_back(obj);
            memoryCore.registerForGC(obj, 1024);
            std::cout << "Створено об'єкт #" << i << " для збору сміття" << std::endl;
        }
    }
    
    // Додати посилання на деякі об'єкти
    // Add references to some objects
    // Додати посилання на деякі об'єкти
    for (size_t i = 0; i < gcObjects.size(); i += 2) {
        memoryCore.addReference(gcObjects[i]);
        std::cout << "Додано посилання на об'єкт #" << i << std::endl;
    }
    
    // Видалити посилання з деяких об'єктів
    // Remove references from some objects
    // Видалити посилання з деяких об'єктів
    for (size_t i = 0; i < gcObjects.size(); i += 2) {
        memoryCore.removeReference(gcObjects[i]);
        std::cout << "Видалено посилання з об'єкта #" << i << std::endl;
    }
    
    // Виконати збір сміття
    // Perform garbage collection
    // Виконати збір сміття
    std::cout << "Виконуємо збір сміття..." << std::endl;
    memoryCore.collectGarbage();
    
    // Отримати фінальну статистику збору сміття
    // Get final garbage collection statistics
    // Отримати фінальну статистику збору сміття
    size_t finalObjects = memoryCore.getGCTotalObjects();
    size_t finalCollected = memoryCore.getGCCollectedObjects();
    std::cout << "Фінальна кількість об'єктів: " << finalObjects << std::endl;
    std::cout << "Фінальна кількість зібраних об'єктів: " << finalCollected << std::endl;
    std::cout << "Зібрано об'єктів у цьому циклі: " << (finalCollected - initialCollected) << std::endl;
    
    // Звільнити об'єкти, які залишилися
    // Free remaining objects
    // Звільнити об'єкти, які залишилися
    for (void* obj : gcObjects) {
        memoryCore.deallocate(obj);
    }
}

// Функція для тестування багатопотокового доступу
// Function to test multithreaded access
// Функція для тестування багатопотокового доступу
void testMultithreadedAccess(MemoryCore& memoryCore) {
    std::cout << "\n=== Тестування багатопотокового доступу ===" << std::endl;
    
    // Створити кілька потоків, які одночасно працюють з пам'яттю
    // Create several threads that work with memory simultaneously
    // Створити кілька потоків, які одночасно працюють з пам'яттю
    std::vector<std::thread> threads;
    
    for (int t = 0; t < 4; ++t) {
        threads.emplace_back([&memoryCore, t]() {
            for (int i = 0; i < 10; ++i) {
                // Виділити пам'ять
                // Allocate memory
                // Виділити пам'ять
                void* ptr = memoryCore.allocate(100 + t * 50 + i * 10);
                if (ptr) {
                    // Заповнити пам'ять даними
                    // Fill memory with data
                    // Заповнити пам'ять даними
                    char* data = static_cast<char*>(ptr);
                    for (int j = 0; j < (100 + t * 50 + i * 10); ++j) {
                        data[j] = static_cast<char>((t + i + j) % 256);
                    }
                    
                    // Звільнити пам'ять
                    // Free memory
                    // Звільнити пам'ять
                    memoryCore.deallocate(ptr);
                }
            }
            std::cout << "Потік #" << t << " завершено" << std::endl;
        });
    }
    
    // Очікувати завершення всіх потоків
    // Wait for all threads to complete
    // Очікувати завершення всіх потоків
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << "Багатопотокове тестування завершено" << std::endl;
}

int main() {
    std::cout << "=== Приклад розширеного управління пам'яттю NeuroSync OS Sparky ===" << std::endl;
    
    try {
        // Створити ядро управління пам'яттю
        // Create memory management core
        // Створити ядро управління пам'яттю
        MemoryCore memoryCore;
        
        // Тестування пулу пам'яті
        // Memory pool testing
        // Тестування пулу пам'яті
        testMemoryPool(memoryCore);
        
        // Тестування збору сміття
        // Garbage collection testing
        // Тестування збору сміття
        testGarbageCollection(memoryCore);
        
        // Тестування багатопотокового доступу
        // Multithreaded access testing
        // Тестування багатопотокового доступу
        testMultithreadedAccess(memoryCore);
        
        // Вивести фінальну статистику
        // Print final statistics
        // Вивести фінальну статистику
        std::cout << "\n=== Фінальна статистика ===" << std::endl;
        std::cout << "Загальна пам'ять: " << memoryCore.getTotalMemory() << " байт" << std::endl;
        std::cout << "Використана пам'ять: " << memoryCore.getUsedMemory() << " байт" << std::endl;
        std::cout << "Вільна пам'ять: " << memoryCore.getFreeMemory() << " байт" << std::endl;
        std::cout << "Загальна кількість об'єктів GC: " << memoryCore.getGCTotalObjects() << std::endl;
        std::cout << "Зібрано об'єктів GC: " << memoryCore.getGCCollectedObjects() << std::endl;
        std::cout << "Звільнено пам'яті GC: " << memoryCore.getGCTotalMemoryFreed() << " байт" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nПриклад розширеного управління пам'яттю завершено успішно!" << std::endl;
    return 0;
}