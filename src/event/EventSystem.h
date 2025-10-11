#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <vector>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include <mutex>
#include <atomic>
#include <thread>
#include <queue>
#include <condition_variable>
#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"

// EventSystem.h
// Система подій для NeuroSync OS Sparky
// Event system for NeuroSync OS Sparky
// Система событий для NeuroSync OS Sparky

namespace NeuroSync {
namespace Event {

    // Тип події
    // Event type
    // Тип события
    enum class EventType {
        NEURON_ACTIVATION,      // Активація нейрона / Neuron activation / Активация нейрона
        NEURON_DEACTIVATION,    // Деактивація нейрона / Neuron deactivation / Деактивация нейрона
        SIGNAL_TRANSMISSION,    // Передача сигналу / Signal transmission / Передача сигнала
        CONNECTION_ESTABLISHED, // Встановлення зв'язку / Connection established / Установление связи
        CONNECTION_BROKEN,      // Розрив зв'язку / Connection broken / Разрыв связи
        LEARNING_EVENT,         // Подія навчання / Learning event / Событие обучения
        SYSTEM_ERROR,           // Системна помилка / System error / Системная ошибка
        CUSTOM_EVENT            // Користувацька подія / Custom event / Пользовательское событие
    };

    // Структура події
    // Event structure
    // Структура события
    struct Event {
        int eventId;                    // Унікальний ID події / Unique event ID / Уникальный ID события
        EventType type;                 // Тип події / Event type / Тип события
        int sourceId;                   // ID джерела / Source ID / ID источника
        int targetId;                   // ID цілі / Target ID / ID цели
        long long timestamp;            // Часова мітка / Timestamp / Временная метка
        std::string data;               // Дані події / Event data / Данные события
        int priority;                   // Пріоритет події / Event priority / Приоритет события
        bool processed;                 // Прапор обробки / Processing flag / Флаг обработки
        
        Event(int id, EventType t, int src, int tgt, const std::string& d = "", int prio = 0)
            : eventId(id), type(t), sourceId(src), targetId(tgt), 
              timestamp(0), data(d), priority(prio), processed(false) {}
    };

    // Обробник подій
    // Event handler
    // Обработчик событий
    using EventHandler = std::function<void(const Event&)>;

    // Система подій
    // Event system
    // Система событий
    class EventSystem {
    public:
        EventSystem();
        ~EventSystem();
        
        // Ініціалізація системи подій
        // Initialize event system
        // Инициализация системы событий
        bool initialize();
        
        // Запустити систему подій
        // Start event system
        // Запустить систему событий
        void start();
        
        // Зупинити систему подій
        // Stop event system
        // Остановить систему событий
        void stop();
        
        // Зареєструвати обробник подій
        // Register event handler
        // Зарегистрировать обработчик событий
        bool registerHandler(EventType type, const EventHandler& handler);
        
        // Видалити обробник подій
        // Remove event handler
        // Удалить обработчик событий
        bool removeHandler(EventType type, const EventHandler& handler);
        
        // Опублікувати подію
        // Publish event
        // Опубликовать событие
        bool publishEvent(const Event& event);
        
        // Опублікувати подію асинхронно
        // Publish event asynchronously
        // Опубликовать событие асинхронно
        bool publishEventAsync(const Event& event);
        
        // Підписатися на події
        // Subscribe to events
        // Подписаться на события
        bool subscribe(int neuronId, EventType type);
        
        // Відписатися від подій
        // Unsubscribe from events
        // Отписаться от событий
        bool unsubscribe(int neuronId, EventType type);
        
        // Отримати кількість очікуючих подій
        // Get pending event count
        // Получить количество ожидающих событий
        size_t getPendingEventCount() const;
        
        // Отримати кількість оброблених подій
        // Get processed event count
        // Получить количество обработанных событий
        size_t getProcessedEventCount() const;
        
        // Очистити чергу подій
        // Clear event queue
        // Очистить очередь событий
        void clearEventQueue();
        
        // Встановити максимальний розмір черги
        // Set maximum queue size
        // Установить максимальный размер очереди
        void setMaxQueueSize(size_t maxSize);
        
        // Отримати максимальний розмір черги
        // Get maximum queue size
        // Получить максимальный размер очереди
        size_t getMaxQueueSize() const;
        
        // Отримати статистику системи подій
        // Get event system statistics
        // Получить статистику системы событий
        struct EventStatistics {
            size_t totalEventsPublished;
            size_t totalEventsProcessed;
            size_t totalEventsDropped;
            size_t activeSubscriptions;
            size_t registeredHandlers;
            long long lastProcessingTime;
        };
        
        EventStatistics getStatistics() const;
        
    private:
        // Черга подій
        // Event queue
        // Очередь событий
        std::queue<Event> eventQueue;
        
        // Мьютекс для синхронізації черги
        // Mutex for queue synchronization
        // Мьютекс для синхронизации очереди
        mutable std::mutex queueMutex;
        
        // Умовна змінна для очікування подій
        // Condition variable for waiting events
        // Условная переменная для ожидания событий
        std::condition_variable eventCondition;
        
        // Обробники подій за типом
        // Event handlers by type
        // Обработчики событий по типу
        std::map<EventType, std::vector<EventHandler>> handlers;
        
        // Мьютекс для синхронізації обробників
        // Mutex for handler synchronization
        // Мьютекс для синхронизации обработчиков
        mutable std::mutex handlersMutex;
        
        // Підписки нейронів на події
        // Neuron subscriptions to events
        // Подписки нейронов на события
        std::map<int, std::vector<EventType>> subscriptions;
        
        // Мьютекс для синхронізації підписок
        // Mutex for subscription synchronization
        // Мьютекс для синхронизации подписок
        mutable std::mutex subscriptionsMutex;
        
        // Потік обробки подій
        // Event processing thread
        // Поток обработки событий
        std::thread processingThread;
        
        // Прапор запуску системи
        // System running flag
        // Флаг запуска системы
        std::atomic<bool> running;
        
        // Статистика
        // Statistics
        // Статистика
        mutable std::mutex statisticsMutex;
        EventStatistics statistics;
        
        // Максимальний розмір черги
        // Maximum queue size
        // Максимальный размер очереди
        size_t maxQueueSize;
        
        // Лічильник ID подій
        // Event ID counter
        // Счетчик ID событий
        std::atomic<int> eventIdCounter;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void processEvents();
        long long getCurrentTimeMillis() const;
        void updateStatistics(const Event& event, bool processed);
        bool isSubscribed(int neuronId, EventType type) const;
    };

} // namespace Event
} // namespace NeuroSync

#endif // EVENT_SYSTEM_H