#ifndef MEMORY_CORE_H
#define MEMORY_CORE_H

#include <cstddef>
#include <vector>
#include <memory>
#include <mutex>

// Підключення нових компонентів управління пам'яттю
// Include new memory management components
// Підключення нових компонентів управління пам'яттю
#include "MemoryPool.h"
#include "GarbageCollector.h"

// MemoryCore.h
// Ядро управління пам'яттю для NeuroSync OS Sparky
// Memory management core for NeuroSync OS Sparky
// Ядро управління пам'яттю для NeuroSync OS Sparky

namespace NeuroSync {
namespace Memory {

    class MemoryCore {
    public:
        // Типи пулы пам'яті для різних розмірів об'єктів
        // Memory pool types for different object sizes
        // Типи пулы пам'яті для різних розмірів об'єктів
        enum class PoolType {
            SMALL,    // Малі об'єкти (до 256 байт)
            MEDIUM,   // Середні об'єкти (256 байт - 4KB)
            LARGE     // Великі об'єкти (понад 4KB)
        };
        
        MemoryCore();
        ~MemoryCore();
        
        // Виділити блок пам'яті
        // Allocate a block of memory
        // Виділити блок пам'яті
        void* allocate(size_t size);
        
        // Звільнити блок пам'яті
        // Free a block of memory
        // Звільнити блок пам'яті
        void deallocate(void* ptr);
        
        // Зареєструвати об'єкт для збору сміття
        // Register an object for garbage collection
        // Зареєструвати об'єкт для збору сміття
        void registerForGC(void* address, size_t size);
        
        // Додати посилання на об'єкт
        // Add a reference to an object
        // Додати посилання на об'єкт
        void addReference(void* address);
        
        // Видалити посилання на об'єкт
        // Remove a reference to an object
        // Видалити посилання на об'єкт
        void removeReference(void* address);
        
        // Виконати збір сміття
        // Perform garbage collection
        // Виконати збір сміття
        void collectGarbage();
        
        // Отримати статистику використання пам'яті
        // Get memory usage statistics
        // Отримати статистику використання пам'яті
        size_t getUsedMemory();
        size_t getTotalMemory();
        size_t getFreeMemory();
        
        // Отримати статистику пулу пам'яті
        // Get memory pool statistics
        // Отримати статистику пулу пам'яті
        size_t getPoolUsedMemory(PoolType type);
        size_t getPoolTotalMemory(PoolType type);
        size_t getPoolFreeMemory(PoolType type);
        
        // Отримати статистику збору сміття
        // Get garbage collection statistics
        // Отримати статистику збору сміття
        size_t getGCTotalObjects();
        size_t getGCCollectedObjects();
        size_t getGCTotalMemoryFreed();
        
    private:
        // Пули пам'яті для різних розмірів об'єктів
        // Memory pools for different object sizes
        // Пули пам'яті для різних розмірів об'єктів
        std::unique_ptr<MemoryPool> smallPool;
        std::unique_ptr<MemoryPool> mediumPool;
        std::unique_ptr<MemoryPool> largePool;
        
        // Система збору сміття
        // Garbage collection system
        // Система збору сміття
        std::unique_ptr<GarbageCollector> garbageCollector;
        
        // М'ютекс для потокобезпеки
        // Mutex for thread safety
        // М'ютекс для потокобезпеки
        mutable std::mutex coreMutex;
        
        // Визначити тип пулу за розміром
        // Determine pool type by size
        // Визначити тип пулу за розміром
        PoolType getPoolType(size_t size);
        
        // Ініціалізувати пули пам'яті
        // Initialize memory pools
        // Ініціалізувати пули пам'яті
        void initializePools();
    };

} // namespace Memory
} // namespace NeuroSync

#endif // MEMORY_CORE_H