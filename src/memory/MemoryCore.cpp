#include "MemoryCore.h"
#include <cstdlib>
#include <iostream>

namespace NeuroSync {
namespace Memory {

    // Конструктор ядра управління пам'яттю
    // Memory management core constructor
    // Конструктор ядра управління пам'яттю
    MemoryCore::MemoryCore() {
        initializePools();
        garbageCollector = std::make_unique<GarbageCollector>();
    }

    // Деструктор ядра управління пам'яттю
    // Memory management core destructor
    // Деструктор ядра управління пам'яттю
    MemoryCore::~MemoryCore() {
        // Все автоматично звільниться завдяки unique_ptr
        // Everything will be automatically freed thanks to unique_ptr
    }

    // Ініціалізувати пули пам'яті
    // Initialize memory pools
    // Ініціалізувати пули пам'яті
    void MemoryCore::initializePools() {
        // Ініціалізація пулу для малих об'єктів (16 MB)
        // Initialize pool for small objects (16 MB)
        // Ініціалізація пулу для малих об'єктів (16 MB)
        smallPool = std::make_unique<MemoryPool>(16 * 1024 * 1024);
        
        // Ініціалізація пулу для середніх об'єктів (64 MB)
        // Initialize pool for medium objects (64 MB)
        // Ініціалізація пулу для середніх об'єктів (64 MB)
        mediumPool = std::make_unique<MemoryPool>(64 * 1024 * 1024);
        
        // Ініціалізація пулу для великих об'єктів (256 MB)
        // Initialize pool for large objects (256 MB)
        // Ініціалізація пулу для великих об'єктів (256 MB)
        largePool = std::make_unique<MemoryPool>(256 * 1024 * 1024);
    }

    // Визначити тип пулу за розміром
    // Determine pool type by size
    // Визначити тип пулу за розміром
    MemoryCore::PoolType MemoryCore::getPoolType(size_t size) {
        if (size <= 256) {
            return PoolType::SMALL;
        } else if (size <= 4 * 1024) {
            return PoolType::MEDIUM;
        } else {
            return PoolType::LARGE;
        }
    }

    // Виділити блок пам'яті
    // Allocate a block of memory
    // Виділити блок пам'яті
    void* MemoryCore::allocate(size_t size) {
        if (size == 0) {
            return nullptr;
        }
        
        std::lock_guard<std::mutex> lock(coreMutex);
        
        // Визначити тип пулу за розміром
        // Determine pool type by size
        // Визначити тип пулу за розміром
        PoolType type = getPoolType(size);
        
        // Виділити пам'ять з відповідного пулу
        // Allocate memory from the appropriate pool
        // Виділити пам'ять з відповідного пулу
        void* ptr = nullptr;
        switch (type) {
            case PoolType::SMALL:
                ptr = smallPool->allocate(size);
                break;
            case PoolType::MEDIUM:
                ptr = mediumPool->allocate(size);
                break;
            case PoolType::LARGE:
                ptr = largePool->allocate(size);
                break;
        }
        
        // Якщо не вдалося виділити з пулу, використати стандартний аллокатор
        // If allocation from pool failed, use standard allocator
        // Якщо не вдалося виділити з пулу, використати стандартний аллокатор
        if (!ptr) {
            ptr = malloc(size);
        }
        
        return ptr;
    }

    // Звільнити блок пам'яті
    // Free a block of memory
    // Звільнити блок пам'яті
    void MemoryCore::deallocate(void* ptr) {
        if (!ptr) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(coreMutex);
        
        // Визначити, до якого пулу належить вказівник
        // Determine which pool the pointer belongs to
        // Визначити, до якого пулу належить вказівник
        if (smallPool->contains(ptr)) {
            smallPool->deallocate(ptr);
        } else if (mediumPool->contains(ptr)) {
            mediumPool->deallocate(ptr);
        } else if (largePool->contains(ptr)) {
            largePool->deallocate(ptr);
        } else {
            // Вказівник не належить жодному пулу, використати стандартний деаллокатор
            // Pointer doesn't belong to any pool, use standard deallocator
            // Вказівник не належить жодному пулу, використати стандартний деаллокатор
            free(ptr);
        }
    }

    // Зареєструвати об'єкт для збору сміття
    // Register an object for garbage collection
    // Зареєструвати об'єкт для збору сміття
    void MemoryCore::registerForGC(void* address, size_t size) {
        if (!address || size == 0) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(coreMutex);
        garbageCollector->registerObject(address, size);
    }

    // Додати посилання на об'єкт
    // Add a reference to an object
    // Додати посилання на об'єкт
    void MemoryCore::addReference(void* address) {
        if (!address) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(coreMutex);
        garbageCollector->addReference(address);
    }

    // Видалити посилання на об'єкт
    // Remove a reference to an object
    // Видалити посилання на об'єкт
    void MemoryCore::removeReference(void* address) {
        if (!address) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(coreMutex);
        garbageCollector->removeReference(address);
    }

    // Виконати збір сміття
    // Perform garbage collection
    // Виконати збір сміття
    void MemoryCore::collectGarbage() {
        std::lock_guard<std::mutex> lock(coreMutex);
        garbageCollector->collect();
    }

    // Отримати статистику використання пам'яті
    // Get memory usage statistics
    // Отримати статистику використання пам'яті
    size_t MemoryCore::getUsedMemory() {
        std::lock_guard<std::mutex> lock(coreMutex);
        return smallPool->getUsedSize() + mediumPool->getUsedSize() + largePool->getUsedSize();
    }

    size_t MemoryCore::getTotalMemory() {
        std::lock_guard<std::mutex> lock(coreMutex);
        return smallPool->getTotalSize() + mediumPool->getTotalSize() + largePool->getTotalSize();
    }

    size_t MemoryCore::getFreeMemory() {
        std::lock_guard<std::mutex> lock(coreMutex);
        return smallPool->getFreeSize() + mediumPool->getFreeSize() + largePool->getFreeSize();
    }

    // Отримати статистику пулу пам'яті
    // Get memory pool statistics
    // Отримати статистику пулу пам'яті
    size_t MemoryCore::getPoolUsedMemory(PoolType type) {
        std::lock_guard<std::mutex> lock(coreMutex);
        switch (type) {
            case PoolType::SMALL:
                return smallPool->getUsedSize();
            case PoolType::MEDIUM:
                return mediumPool->getUsedSize();
            case PoolType::LARGE:
                return largePool->getUsedSize();
            default:
                return 0;
        }
    }

    size_t MemoryCore::getPoolTotalMemory(PoolType type) {
        std::lock_guard<std::mutex> lock(coreMutex);
        switch (type) {
            case PoolType::SMALL:
                return smallPool->getTotalSize();
            case PoolType::MEDIUM:
                return mediumPool->getTotalSize();
            case PoolType::LARGE:
                return largePool->getTotalSize();
            default:
                return 0;
        }
    }

    size_t MemoryCore::getPoolFreeMemory(PoolType type) {
        std::lock_guard<std::mutex> lock(coreMutex);
        switch (type) {
            case PoolType::SMALL:
                return smallPool->getFreeSize();
            case PoolType::MEDIUM:
                return mediumPool->getFreeSize();
            case PoolType::LARGE:
                return largePool->getFreeSize();
            default:
                return 0;
        }
    }

    // Отримати статистику збору сміття
    // Get garbage collection statistics
    // Отримати статистику збору сміття
    size_t MemoryCore::getGCTotalObjects() {
        std::lock_guard<std::mutex> lock(coreMutex);
        return garbageCollector->getTotalObjects();
    }

    size_t MemoryCore::getGCCollectedObjects() {
        std::lock_guard<std::mutex> lock(coreMutex);
        return garbageCollector->getCollectedObjects();
    }

    size_t MemoryCore::getGCTotalMemoryFreed() {
        std::lock_guard<std::mutex> lock(coreMutex);
        return garbageCollector->getTotalMemoryFreed();
    }

} // namespace Memory
} // namespace NeuroSync