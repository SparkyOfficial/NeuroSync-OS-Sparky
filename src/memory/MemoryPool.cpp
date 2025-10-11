#include "MemoryPool.h"
#include <stdexcept>
#include <algorithm>
#include <cstring>

namespace NeuroSync {
namespace Memory {

    // Конструктор пулу пам'яті
    // Memory pool constructor
    // Конструктор пулу пам'яті
    MemoryPool::MemoryPool(size_t poolSize) 
        : totalSize(poolSize), usedSize(0), blockCount(0), freeBlocks(nullptr), usedBlocks(nullptr) {
        // Виділити пам'ять для пулу
        // Allocate memory for the pool
        // Виділити пам'ять для пулу
        poolMemory = static_cast<char*>(malloc(poolSize));
        if (!poolMemory) {
            throw std::bad_alloc();
        }
        
        // Ініціалізувати пул
        // Initialize the pool
        // Ініціалізувати пул
        initializePool();
    }

    // Деструктор пулу пам'яті
    // Memory pool destructor
    // Деструктор пулу пам'яті
    MemoryPool::~MemoryPool() {
        // Звільнити всю пам'ять пулу
        // Free all pool memory
        // Звільнити всю пам'ять пулу
        if (poolMemory) {
            free(poolMemory);
        }
        
        // Звільнити всі блоки
        // Free all blocks
        // Звільнити всі блоки
        MemoryBlock* current = freeBlocks;
        while (current) {
            MemoryBlock* next = current->next;
            delete current;
            current = next;
        }
        
        current = usedBlocks;
        while (current) {
            MemoryBlock* next = current->next;
            delete current;
            current = next;
        }
    }

    // Ініціалізувати пул пам'яті
    // Initialize memory pool
    // Ініціалізувати пул пам'яті
    void MemoryPool::initializePool() {
        std::lock_guard<std::mutex> lock(poolMutex);
        
        // Створити один великий вільний блок
        // Create one large free block
        // Створити один великий вільний блок
        MemoryBlock* initialBlock = new MemoryBlock(poolMemory, totalSize);
        freeBlocks = initialBlock;
        blockCount = 1;
    }

    // Виділити блок пам'яті з пулу
    // Allocate a block of memory from the pool
    // Виділити блок пам'яті з пулу
    void* MemoryPool::allocate(size_t size) {
        if (size == 0) {
            return nullptr;
        }
        
        std::lock_guard<std::mutex> lock(poolMutex);
        
        // Знайти вільний блок потрібного розміру
        // Find a free block of required size
        // Знайти вільний блок потрібного розміру
        MemoryBlock* block = findFreeBlock(size);
        if (!block) {
            // Недостатньо пам'яті в пулі
            // Not enough memory in the pool
            // Недостатньо пам'яті в пулі
            return nullptr;
        }
        
        // Розділити блок, якщо він занадто великий
        // Split the block if it's too large
        // Розділити блок, якщо він занадто великий
        if (block->size > size + sizeof(MemoryBlock)) {
            splitBlock(block, size);
        }
        
        // Позначити блок як використаний
        // Mark the block as used
        // Позначити блок як використаний
        block->isFree = false;
        usedSize += block->size;
        
        // Перемістити блок зі списку вільних до списку використаних
        // Move the block from free list to used list
        // Перемістити блок зі списку вільних до списку використаних
        if (block->prev) {
            block->prev->next = block->next;
        } else {
            freeBlocks = block->next;
        }
        
        if (block->next) {
            block->next->prev = block->prev;
        }
        
        block->prev = nullptr;
        block->next = usedBlocks;
        if (usedBlocks) {
            usedBlocks->prev = block;
        }
        usedBlocks = block;
        
        return block->address;
    }

    // Звільнити блок пам'яті в пул
    // Deallocate a block of memory to the pool
    // Звільнити блок пам'яті в пул
    void MemoryPool::deallocate(void* ptr) {
        if (!ptr) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(poolMutex);
        
        // Знайти блок за адресою
        // Find the block by address
        // Знайти блок за адресою
        MemoryBlock* current = usedBlocks;
        while (current) {
            if (current->address == ptr) {
                break;
            }
            current = current->next;
        }
        
        if (!current) {
            // Адреса не належить цьому пулу
            // Address doesn't belong to this pool
            // Адреса не належить цьому пулу
            return;
        }
        
        // Позначити блок як вільний
        // Mark the block as free
        // Позначити блок як вільний
        current->isFree = true;
        usedSize -= current->size;
        
        // Перемістити блок зі списку використаних до списку вільних
        // Move the block from used list to free list
        // Перемістити блок зі списку використаних до списку вільних
        if (current->prev) {
            current->prev->next = current->next;
        } else {
            usedBlocks = current->next;
        }
        
        if (current->next) {
            current->next->prev = current->prev;
        }
        
        current->prev = nullptr;
        current->next = freeBlocks;
        if (freeBlocks) {
            freeBlocks->prev = current;
        }
        freeBlocks = current;
        
        // Об'єднати суміжні вільні блоки
        // Merge adjacent free blocks
        // Об'єднати суміжні вільні блоки
        mergeFreeBlocks();
    }

    // Знайти вільний блок потрібного розміру
    // Find a free block of required size
    // Знайти вільний блок потрібного розміру
    MemoryBlock* MemoryPool::findFreeBlock(size_t size) {
        MemoryBlock* current = freeBlocks;
        while (current) {
            if (current->size >= size) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Розділити блок на два менші блоки
    // Split a block into two smaller blocks
    // Розділити блок на два менші блоки
    void MemoryPool::splitBlock(MemoryBlock* block, size_t size) {
        // Обчислити розмір нового блоку
        // Calculate the size of the new block
        // Обчислити розмір нового блоку
        size_t remainingSize = block->size - size;
        
        // Створити новий блок для решти пам'яті
        // Create a new block for the remaining memory
        // Створити новий блок для решти пам'яті
        void* newAddress = static_cast<char*>(block->address) + size;
        MemoryBlock* newBlock = new MemoryBlock(newAddress, remainingSize);
        
        // Оновити розмір оригінального блоку
        // Update the size of the original block
        // Оновити розмір оригінального блоку
        block->size = size;
        
        // Додати новий блок до списку вільних блоків
        // Add the new block to the free blocks list
        // Додати новий блок до списку вільних блоків
        newBlock->next = freeBlocks;
        if (freeBlocks) {
            freeBlocks->prev = newBlock;
        }
        freeBlocks = newBlock;
        blockCount++;
    }

    // Об'єднати суміжні вільні блоки
    // Merge adjacent free blocks
    // Об'єднати суміжні вільні блоки
    void MemoryPool::mergeFreeBlocks() {
        // Сортуємо вільні блоки за адресою для полегшення об'єднання
        // Sort free blocks by address to facilitate merging
        // Сортируем свободные блоки по адресу для облегчения объединения
        
        // Створюємо вектор вільних блоків
        // Create a vector of free blocks
        // Создаем вектор свободных блоков
        std::vector<MemoryBlock*> freeBlocksVector;
        MemoryBlock* current = freeBlocks;
        
        while (current) {
            freeBlocksVector.push_back(current);
            current = current->next;
        }
        
        // Сортуємо блоки за адресою
        // Sort blocks by address
        // Сортируем блоки по адресу
        std::sort(freeBlocksVector.begin(), freeBlocksVector.end(), 
                 [](MemoryBlock* a, MemoryBlock* b) {
                     return a->address < b->address;
                 });
        
        // Об'єднуємо суміжні блоки
        // Merge adjacent blocks
        // Объединяем смежные блоки
        for (size_t i = 0; i < freeBlocksVector.size(); ) {
            MemoryBlock* currentBlock = freeBlocksVector[i];
            size_t mergedCount = 1;
            
            // Перевіряємо наступні блоки на суміжність
            // Check next blocks for adjacency
            // Проверяем следующие блоки на смежность
            for (size_t j = i + 1; j < freeBlocksVector.size(); ++j) {
                MemoryBlock* nextBlock = freeBlocksVector[j];
                
                // Перевіряємо, чи блоки суміжні
                // Check if blocks are adjacent
                // Проверяем, являются ли блоки смежными
                char* currentEnd = static_cast<char*>(currentBlock->address) + currentBlock->size;
                char* nextStart = static_cast<char*>(nextBlock->address);
                
                if (currentEnd == nextStart) {
                    // Блоки суміжні, об'єднуємо їх
                    // Blocks are adjacent, merge them
                    // Блоки смежные, объединяем их
                    currentBlock->size += nextBlock->size;
                    mergedCount++;
                    
                    // Видаляємо об'єднаний блок зі списку
                    // Remove merged block from list
                    // Удаляем объединенный блок из списка
                    if (nextBlock->prev) {
                        nextBlock->prev->next = nextBlock->next;
                    } else {
                        freeBlocks = nextBlock->next;
                    }
                    
                    if (nextBlock->next) {
                        nextBlock->next->prev = nextBlock->prev;
                    }
                    
                    // Видаляємо блок
                    // Delete block
                    // Удаляем блок
                    delete nextBlock;
                    blockCount--;
                } else {
                    // Блоки не суміжні, зупиняємося
                    // Blocks are not adjacent, stop
                    // Блоки не смежные, останавливаемся
                    break;
                }
            }
            
            i += mergedCount;
        }
        
        // Перебудовуємо список вільних блоків
        // Rebuild the free blocks list
        // Перестраиваем список свободных блоков
        freeBlocks = nullptr;
        MemoryBlock* prevBlock = nullptr;
        
        for (MemoryBlock* block : freeBlocksVector) {
            block->prev = prevBlock;
            block->next = nullptr;
            
            if (prevBlock) {
                prevBlock->next = block;
            } else {
                freeBlocks = block;
            }
            
            prevBlock = block;
        }
    }

    // Перевірити, чи належить вказівник цьому пулу
    // Check if pointer belongs to this pool
    // Перевірити, чи належить вказівник цьому пулу
    bool MemoryPool::contains(void* ptr) const {
        if (!ptr) {
            return false;
        }
        
        // Перевірити, чи адреса знаходиться в межах пулу
        // Check if the address is within the pool bounds
        // Перевірити, чи адреса знаходиться в межах пулу
        char* charPtr = static_cast<char*>(ptr);
        return (charPtr >= poolMemory) && (charPtr < (poolMemory + totalSize));
    }

} // namespace Memory
} // namespace NeuroSync