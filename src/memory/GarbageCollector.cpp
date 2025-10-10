#include "GarbageCollector.h"
#include <iostream>
#include <algorithm>

namespace NeuroSync {
namespace Memory {

    // Конструктор системи збору сміття
    // Garbage collector constructor
    // Конструктор системи збору сміття
    GarbageCollector::GarbageCollector() 
        : collectedObjects(0), totalMemoryFreed(0), autoCollectionRunning(false) {}

    // Деструктор системи збору сміття
    // Garbage collector destructor
    // Деструктор системи збору сміття
    GarbageCollector::~GarbageCollector() {
        stopAutoCollection();
        
        // Звільнити всі об'єкти GC
        // Free all GC objects
        // Звільнити всі об'єкти GC
        for (auto& pair : objects) {
            delete pair.second;
        }
    }

    // Зареєструвати об'єкт для збору сміття
    // Register an object for garbage collection
    // Зареєструвати об'єкт для збору сміття
    void GarbageCollector::registerObject(void* address, size_t size) {
        if (!address) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(gcMutex);
        
        // Перевірити, чи об'єкт вже зареєстровано
        // Check if the object is already registered
        // Перевірити, чи об'єкт вже зареєстровано
        if (objects.find(address) != objects.end()) {
            return;
        }
        
        // Створити новий об'єкт GC
        // Create a new GC object
        // Створити новий об'єкт GC
        GCObject* obj = new GCObject(address, size);
        objects[address] = obj;
        roots.insert(obj); // Додати як кореневий об'єкт за замовчуванням
    }

    // Додати посилання на об'єкт
    // Add a reference to an object
    // Додати посилання на об'єкт
    void GarbageCollector::addReference(void* address) {
        if (!address) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(gcMutex);
        
        // Знайти об'єкт за адресою
        // Find the object by address
        // Знайти об'єкт за адресою
        auto it = objects.find(address);
        if (it != objects.end()) {
            it->second->refCount++;
            it->second->lastAccess = std::chrono::steady_clock::now();
        }
    }

    // Видалити посилання на об'єкт
    // Remove a reference to an object
    // Видалити посилання на об'єкт
    void GarbageCollector::removeReference(void* address) {
        if (!address) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(gcMutex);
        
        // Знайти об'єкт за адресою
        // Find the object by address
        // Знайти об'єкт за адресою
        auto it = objects.find(address);
        if (it != objects.end()) {
            it->second->refCount--;
            it->second->lastAccess = std::chrono::steady_clock::now();
            
            // Якщо лічильник посилань став нульовим, видалити з коренів
            // If the reference count becomes zero, remove from roots
            // Якщо лічильник посилань став нульовим, видалити з коренів
            if (it->second->refCount.load() <= 0) {
                roots.erase(it->second);
            }
        }
    }

    // Позначити об'єкт як доступний (для збору сміття)
    // Mark an object as reachable (for garbage collection)
    // Позначити об'єкт як доступний (для збору сміття)
    void GarbageCollector::markObject(void* address) {
        if (!address) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(gcMutex);
        
        // Знайти об'єкт за адресою
        // Find the object by address
        // Знайти об'єкт за адресою
        auto it = objects.find(address);
        if (it != objects.end()) {
            it->second->marked = true;
            it->second->lastAccess = std::chrono::steady_clock::now();
        }
    }

    // Виконати збір сміття
    // Perform garbage collection
    // Виконати збір сміття
    void GarbageCollector::collect() {
        std::lock_guard<std::mutex> lock(gcMutex);
        markAndSweep();
    }

    // Виконати алгоритм позначення-збору
    // Perform mark-and-sweep algorithm
    // Виконати алгоритм позначення-збору
    void GarbageCollector::markAndSweep() {
        mark();
        sweep();
    }

    // Позначити доступні об'єкти
    // Mark reachable objects
    // Позначити доступні об'єкти
    void GarbageCollector::mark() {
        // У цій спрощеній реалізації ми вважаємо всі кореневі об'єкти позначеними
        // In this simplified implementation, we consider all root objects as marked
        // У цій спрощеній реалізації ми вважаємо всі кореневі об'єкти позначеними
        for (GCObject* obj : roots) {
            obj->marked = true;
        }
    }

    // Зібрати недоступні об'єкти
    // Sweep unreachable objects
    // Зібрати недоступні об'єкти
    void GarbageCollector::sweep() {
        size_t collected = 0;
        size_t memoryFreed = 0;
        
        // Пройтися по всіх об'єктах
        // Iterate through all objects
        // Пройтися по всіх об'єктах
        auto it = objects.begin();
        while (it != objects.end()) {
            GCObject* obj = it->second;
            
            // Якщо об'єкт не позначений і має нульовий лічильник посилань
            // If the object is not marked and has zero reference count
            // Якщо об'єкт не позначений і має нульовий лічильник посилань
            if (!obj->marked && obj->refCount.load() <= 0) {
                // Звільнити пам'ять об'єкта
                // Free the object's memory
                // Звільнити пам'ять об'єкта
                free(obj->address);
                memoryFreed += obj->size;
                collected++;
                
                // Видалити об'єкт з колекцій
                // Remove the object from collections
                // Видалити об'єкт з колекцій
                roots.erase(obj);
                delete obj;
                it = objects.erase(it);
            } else {
                // Скинути прапор позначення для наступного циклу
                // Reset the marked flag for the next cycle
                // Скинути прапор позначення для наступного циклу
                obj->marked = false;
                ++it;
            }
        }
        
        // Оновити статистику
        // Update statistics
        // Оновити статистику
        collectedObjects += collected;
        totalMemoryFreed += memoryFreed;
    }

    // Запустити автоматичний збір сміття у фоновому потоці
    // Start automatic garbage collection in a background thread
    // Запустити автоматичний збір сміття у фоновому потоці
    void GarbageCollector::startAutoCollection(std::chrono::milliseconds interval) {
        if (autoCollectionRunning) {
            return;
        }
        
        autoCollectionRunning = true;
        autoCollectionThread = std::thread(&GarbageCollector::autoCollectionLoop, this, interval);
    }

    // Зупинити автоматичний збір сміття
    // Stop automatic garbage collection
    // Зупинити автоматичний збір сміття
    void GarbageCollector::stopAutoCollection() {
        if (autoCollectionRunning) {
            autoCollectionRunning = false;
            if (autoCollectionThread.joinable()) {
                autoCollectionThread.join();
            }
        }
    }

    // Фонова функція автоматичного збору сміття
    // Background function for automatic garbage collection
    // Фонова функція автоматичного збору сміття
    void GarbageCollector::autoCollectionLoop(std::chrono::milliseconds interval) {
        while (autoCollectionRunning) {
            std::this_thread::sleep_for(interval);
            if (autoCollectionRunning) {
                collect();
            }
        }
    }

} // namespace Memory
} // namespace NeuroSync