#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstddef>
#include <vector>
#include <mutex>

namespace NeuroSync {
namespace Memory {

    // Структура для представлення блоку пам'яті в пулі
    // Structure to represent a memory block in the pool
    // Структура для представлення блоку пам'яті в пулі
    struct MemoryBlock {
        void* address;           // Адреса блоку пам'яті
        size_t size;             // Розмір блоку
        bool isFree;             // Прапор вільного блоку
        MemoryBlock* next;       // Наступний блок у списку
        MemoryBlock* prev;       // Попередній блок у списку
        
        MemoryBlock(void* addr, size_t sz) 
            : address(addr), size(sz), isFree(true), next(nullptr), prev(nullptr) {}
    };

    // Пул пам'яті для ефективного управління пам'яттю
    // Memory pool for efficient memory management
    // Пул пам'яті для ефективного управління пам'яттю
    class MemoryPool {
    public:
        MemoryPool(size_t poolSize);
        ~MemoryPool();
        
        // Виділити блок пам'яті з пулу
        // Allocate a block of memory from the pool
        // Виділити блок пам'яті з пулу
        void* allocate(size_t size);
        
        // Звільнити блок пам'яті в пул
        // Deallocate a block of memory to the pool
        // Звільнити блок пам'яті в пул
        void deallocate(void* ptr);
        
        // Отримати статистику пулу
        // Get pool statistics
        // Отримати статистику пулу
        size_t getTotalSize() const { return totalSize; }
        size_t getUsedSize() const { return usedSize; }
        size_t getFreeSize() const { return totalSize - usedSize; }
        size_t getBlockCount() const { return blockCount; }
        
        // Перевірити, чи належить вказівник цьому пулу
        // Check if pointer belongs to this pool
        // Перевірити, чи належить вказівник цьому пулу
        bool contains(void* ptr) const;
        
    private:
        char* poolMemory;           // Базова пам'ять пулу
        size_t totalSize;           // Загальний розмір пулу
        size_t usedSize;            // Використаний розмір
        size_t blockCount;          // Кількість блоків
        MemoryBlock* freeBlocks;    // Список вільних блоків
        MemoryBlock* usedBlocks;    // Список використаних блоків
        mutable std::mutex poolMutex; // М'ютекс для потокобезпеки
        
        // Ініціалізувати пул пам'яті
        // Initialize memory pool
        // Ініціалізувати пул пам'яті
        void initializePool();
        
        // Знайти вільний блок потрібного розміру
        // Find a free block of required size
        // Знайти вільний блок потрібного розміру
        MemoryBlock* findFreeBlock(size_t size);
        
        // Розділити блок на два менші блоки
        // Split a block into two smaller blocks
        // Розділити блок на два менші блоки
        void splitBlock(MemoryBlock* block, size_t size);
        
        // Об'єднати суміжні вільні блоки
        // Merge adjacent free blocks
        // Об'єднати суміжні вільні блоки
        void mergeFreeBlocks();
    };

} // namespace Memory
} // namespace NeuroSync

#endif // MEMORY_POOL_H