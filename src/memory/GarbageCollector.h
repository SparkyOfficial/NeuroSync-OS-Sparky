#ifndef GARBAGE_COLLECTOR_H
#define GARBAGE_COLLECTOR_H

#include <cstddef>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>

namespace NeuroSync {
namespace Memory {

    // Структура для представлення об'єкта в системі збору сміття
    // Structure to represent an object in the garbage collection system
    // Структура для представлення об'єкта в системі збору сміття
    struct GCObject {
        void* address;              // Адреса об'єкта
        size_t size;                // Розмір об'єкта
        std::atomic<int> refCount;  // Лічильник посилань
        std::chrono::steady_clock::time_point lastAccess; // Час останнього доступу
        bool marked;                // Прапор позначення для збору сміття
        
        GCObject(void* addr, size_t sz) 
            : address(addr), size(sz), refCount(1), marked(false) {
            lastAccess = std::chrono::steady_clock::now();
        }
    };

    // Система збору сміття для автоматичного управління пам'яттю
    // Garbage collection system for automatic memory management
    // Система збору сміття для автоматичного управління пам'яттю
    class GarbageCollector {
    public:
        GarbageCollector();
        ~GarbageCollector();
        
        // Зареєструвати об'єкт для збору сміття
        // Register an object for garbage collection
        // Зареєструвати об'єкт для збору сміття
        void registerObject(void* address, size_t size);
        
        // Додати посилання на об'єкт
        // Add a reference to an object
        // Додати посилання на об'єкт
        void addReference(void* address);
        
        // Видалити посилання на об'єкт
        // Remove a reference to an object
        // Видалити посилання на об'єкт
        void removeReference(void* address);
        
        // Позначити об'єкт як доступний (для збору сміття)
        // Mark an object as reachable (for garbage collection)
        // Позначити об'єкт як доступний (для збору сміття)
        void markObject(void* address);
        
        // Виконати збір сміття
        // Perform garbage collection
        // Виконати збір сміття
        void collect();
        
        // Запустити автоматичний збір сміття у фоновому потоці
        // Start automatic garbage collection in a background thread
        // Запустити автоматичний збір сміття у фоновому потоці
        void startAutoCollection(std::chrono::milliseconds interval);
        
        // Зупинити автоматичний збір сміття
        // Stop automatic garbage collection
        // Зупинити автоматичний збір сміття
        void stopAutoCollection();
        
        // Отримати статистику збору сміття
        // Get garbage collection statistics
        // Отримати статистику збору сміття
        size_t getTotalObjects() const { return objects.size(); }
        size_t getCollectedObjects() const { return collectedObjects; }
        size_t getTotalMemoryFreed() const { return totalMemoryFreed; }
        
    private:
        std::unordered_map<void*, GCObject*> objects;  // Зареєстровані об'єкти
        std::unordered_set<GCObject*> roots;           // Кореневі об'єкти
        mutable std::mutex gcMutex;                    // М'ютекс для потокобезпеки
        std::atomic<size_t> collectedObjects;          // Кількість зібраних об'єктів
        std::atomic<size_t> totalMemoryFreed;          // Загальна звільнена пам'ять
        std::atomic<bool> autoCollectionRunning;       // Прапор автоматичного збору
        std::thread autoCollectionThread;              // Потік автоматичного збору
        
        // Виконати алгоритм позначення-збору
        // Perform mark-and-sweep algorithm
        // Виконати алгоритм позначення-збору
        void markAndSweep();
        
        // Позначити доступні об'єкти
        // Mark reachable objects
        // Позначити доступні об'єкти
        void mark();
        
        // Зібрати недоступні об'єкти
        // Sweep unreachable objects
        // Зібрати недоступні об'єкти
        void sweep();
        
        // Фонова функція автоматичного збору сміття
        // Background function for automatic garbage collection
        // Фонова функція автоматичного збору сміття
        void autoCollectionLoop(std::chrono::milliseconds interval);
    };

} // namespace Memory
} // namespace NeuroSync

#endif // GARBAGE_COLLECTOR_H