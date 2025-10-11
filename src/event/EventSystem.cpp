#include "EventSystem.h"
#include <chrono>
#include <algorithm>
#include <iostream>

namespace NeuroSync {
namespace Event {

    EventSystem::EventSystem()
        : running(false), maxQueueSize(1000), eventIdCounter(0) {
        statistics.totalEventsPublished = 0;
        statistics.totalEventsProcessed = 0;
        statistics.totalEventsDropped = 0;
        statistics.activeSubscriptions = 0;
        statistics.registeredHandlers = 0;
        statistics.lastProcessingTime = 0;
    }

    EventSystem::~EventSystem() {
        stop();
    }

    bool EventSystem::initialize() {
        // Initialization logic if needed
        return true;
    }

    void EventSystem::start() {
        if (running.exchange(true)) {
            return; // Already running
        }
        
        processingThread = std::thread(&EventSystem::processEvents, this);
        asyncProcessingThread = std::thread(&EventSystem::processAsyncEvents, this);
    }

    void EventSystem::stop() {
        if (!running.exchange(false)) {
            return; // Already stopped
        }
        
        // Wake up the processing threads
        eventCondition.notify_all();
        asyncEventCondition.notify_all();
        
        if (processingThread.joinable()) {
            processingThread.join();
        }
        
        if (asyncProcessingThread.joinable()) {
            asyncProcessingThread.join();
        }
    }

    bool EventSystem::registerHandler(EventType type, const EventHandler& handler) {
        if (!handler) {
            return false;
        }
        
        std::lock_guard<std::mutex> lock(handlersMutex);
        handlers[type].push_back(handler);
        statistics.registeredHandlers = handlers.size();
        return true;
    }

    bool EventSystem::removeHandler(EventType type, const EventHandler& handler) {
        std::lock_guard<std::mutex> lock(handlersMutex);
        
        auto it = handlers.find(type);
        if (it == handlers.end()) {
            return false;
        }
        
        auto& handlerList = it->second;
        auto handlerIt = std::find_if(handlerList.begin(), handlerList.end(),
            [&handler](const EventHandler& h) {
                return h.target_type() == handler.target_type();
            });
            
        if (handlerIt != handlerList.end()) {
            handlerList.erase(handlerIt);
            if (handlerList.empty()) {
                handlers.erase(it);
            }
            statistics.registeredHandlers = handlers.size();
            return true;
        }
        
        return false;
    }

    bool EventSystem::publishEvent(const Event& event) {
        // Set timestamp if not already set
        Event eventCopy = event;
        if (eventCopy.timestamp == 0) {
            eventCopy.timestamp = getCurrentTimeMillis();
        }
        
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (eventQueue.size() >= maxQueueSize) {
                // Queue is full, drop the event
                std::lock_guard<std::mutex> statLock(statisticsMutex);
                statistics.totalEventsDropped++;
                return false;
            }
            eventQueue.push(eventCopy);
            statistics.totalEventsPublished++;
        }
        
        // Notify the processing thread
        eventCondition.notify_one();
        return true;
    }

    bool EventSystem::publishEventAsync(const Event& event) {
        // Реалізація асинхронної публікації події з використанням окремої черги
        // Implementation of asynchronous event publishing using a separate queue
        // Реализация асинхронной публикации события с использованием отдельной очереди
        
        // Використання окремої асинхронної черги для кращої продуктивності
        // Using a separate async queue for better performance
        // Использование отдельной асинхронной очереди для лучшей производительности
        // і щоб уникнути блокування головного потоку обробки подій
        // and to avoid blocking the main event processing thread
        // и чтобы избежать блокировки основного потока обработки событий
        
        // 1. Додавання події до окремої асинхронної черги
        // 1. Adding the event to a separate async queue
        // 1. Добавление события в отдельную асинхронную очередь
        {
            std::lock_guard<std::mutex> lock(asyncQueueMutex);
            if (asyncEventQueue.size() >= maxQueueSize) {
                // Черга заповнена, викидаємо подію
                // Queue is full, drop the event
                // Очередь заполнена, выбрасываем событие
                std::lock_guard<std::mutex> statLock(statisticsMutex);
                statistics.totalEventsDropped++;
                return false;
            }
            asyncEventQueue.push(event);
            statistics.totalEventsPublished++;
        }
        
        // 2. Сповіщення окремого асинхронного потоку обробки
        // 2. Notifying a separate async processing thread
        // 2. Оповещение отдельного асинхронного потока обработки
        asyncEventCondition.notify_one();
        
        // 3. Повернення негайно без очікування обробки
        // 3. Returning immediately without waiting for processing
        // 3. Возвращение немедленно без ожидания обработки
        return true;
    }

    // TODO: Implement proper broadcast mechanism
    // TODO: This is the same as publishEvent
    // In a real implementation, this would broadcast an event to all subscribed neurons
    // and handlers. This would involve:
    // 1. Creating an event with the provided event type and data
    // 2. Broadcasting the event to all subscribed neurons
    // 3. Calling all registered handlers for the event type
    // 4. Handling any errors or exceptions that occur during broadcasting
    void EventSystem::broadcastEvent(const std::string& eventType, const std::string& eventData) {
        // Create an event with the provided event type and data
        // Note: In a real implementation, we would convert the string eventType to EventType enum
        // For now, we'll use a default event type
        Event event(eventIdCounter++, EventType::CUSTOM_EVENT, -1, -1, eventData, 0);
        event.timestamp = getCurrentTimeMillis();
        
        // Broadcast the event to all subscribed neurons and handlers
        publishEvent(event);
    }

    bool EventSystem::subscribe(int neuronId, EventType type) {
        std::lock_guard<std::mutex> lock(subscriptionsMutex);
        
        auto& subscriptionsList = subscriptions[neuronId];
        if (std::find(subscriptionsList.begin(), subscriptionsList.end(), type) == subscriptionsList.end()) {
            subscriptionsList.push_back(type);
            statistics.activeSubscriptions = subscriptions.size();
            return true;
        }
        
        return false; // Already subscribed
    }

    bool EventSystem::unsubscribe(int neuronId, EventType type) {
        std::lock_guard<std::mutex> lock(subscriptionsMutex);
        
        auto it = subscriptions.find(neuronId);
        if (it == subscriptions.end()) {
            return false;
        }
        
        auto& subscriptionsList = it->second;
        auto typeIt = std::find(subscriptionsList.begin(), subscriptionsList.end(), type);
        if (typeIt != subscriptionsList.end()) {
            subscriptionsList.erase(typeIt);
            if (subscriptionsList.empty()) {
                subscriptions.erase(it);
            }
            statistics.activeSubscriptions = subscriptions.size();
            return true;
        }
        
        return false;
    }

    size_t EventSystem::getPendingEventCount() const {
        std::lock_guard<std::mutex> lock(queueMutex);
        return eventQueue.size();
    }

    size_t EventSystem::getProcessedEventCount() const {
        std::lock_guard<std::mutex> lock(statisticsMutex);
        return statistics.totalEventsProcessed;
    }

    void EventSystem::clearEventQueue() {
        std::lock_guard<std::mutex> lock(queueMutex);
        while (!eventQueue.empty()) {
            eventQueue.pop();
        }
    }

    void EventSystem::setMaxQueueSize(size_t maxSize) {
        std::lock_guard<std::mutex> lock(queueMutex);
        maxQueueSize = maxSize;
    }

    size_t EventSystem::getMaxQueueSize() const {
        std::lock_guard<std::mutex> lock(queueMutex);
        return maxQueueSize;
    }

    EventSystem::EventStatistics EventSystem::getStatistics() const {
        std::lock_guard<std::mutex> lock(statisticsMutex);
        return statistics;
    }

    void EventSystem::processEvents() {
        while (running) {
            std::unique_lock<std::mutex> lock(queueMutex);
            
            // Wait for events or stop signal
            eventCondition.wait(lock, [this] { return !eventQueue.empty() || !running; });
            
            if (!running && eventQueue.empty()) {
                break;
            }
            
            // Process all available events
            while (!eventQueue.empty()) {
                Event event = eventQueue.front();
                eventQueue.pop();
                
                lock.unlock(); // Unlock while processing to avoid deadlocks
                
                // Process the event
                long long startTime = getCurrentTimeMillis();
                
                // Check if there are handlers for this event type
                {
                    std::lock_guard<std::mutex> handlersLock(handlersMutex);
                    auto it = handlers.find(event.type);
                    if (it != handlers.end()) {
                        // Call all handlers for this event type
                        for (const auto& handler : it->second) {
                            try {
                                handler(event);
                            } catch (...) {
                                // Handle exceptions in handlers gracefully
                                std::cerr << "Exception in event handler for event type: " 
                                          << static_cast<int>(event.type) << std::endl;
                            }
                        }
                    }
                }
                
                // Update statistics
                long long processingTime = getCurrentTimeMillis() - startTime;
                updateStatistics(event, true);
                
                lock.lock(); // Lock again for the next iteration
            }
        }
    }

    void EventSystem::processAsyncEvents() {
        while (running) {
            std::unique_lock<std::mutex> lock(asyncQueueMutex);
            
            // Wait for async events or stop signal
            asyncEventCondition.wait(lock, [this] { return !asyncEventQueue.empty() || !running; });
            
            if (!running && asyncEventQueue.empty()) {
                break;
            }
            
            // Process all available async events
            while (!asyncEventQueue.empty()) {
                Event event = asyncEventQueue.front();
                asyncEventQueue.pop();
                
                lock.unlock(); // Unlock while processing to avoid deadlocks
                
                // Process the async event
                long long startTime = getCurrentTimeMillis();
                
                // Check if there are handlers for this event type
                {
                    std::lock_guard<std::mutex> handlersLock(handlersMutex);
                    auto it = handlers.find(event.type);
                    if (it != handlers.end()) {
                        // Call all handlers for this event type
                        for (const auto& handler : it->second) {
                            try {
                                handler(event);
                            } catch (...) {
                                // Handle exceptions in handlers gracefully
                                std::cerr << "Exception in async event handler for event type: " 
                                          << static_cast<int>(event.type) << std::endl;
                            }
                        }
                    }
                }
                
                // Update statistics
                long long processingTime = getCurrentTimeMillis() - startTime;
                updateStatistics(event, true);
                
                lock.lock(); // Lock again for the next iteration
            }
        }
    }

    long long EventSystem::getCurrentTimeMillis() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    void EventSystem::updateStatistics(const Event& event, bool processed) {
        std::lock_guard<std::mutex> lock(statisticsMutex);
        if (processed) {
            statistics.totalEventsProcessed++;
        }
        statistics.lastProcessingTime = getCurrentTimeMillis();
    }

    bool EventSystem::isSubscribed(int neuronId, EventType type) const {
        std::lock_guard<std::mutex> lock(subscriptionsMutex);
        
        auto it = subscriptions.find(neuronId);
        if (it == subscriptions.end()) {
            return false;
        }
        
        const auto& subscriptionsList = it->second;
        return std::find(subscriptionsList.begin(), subscriptionsList.end(), type) != subscriptionsList.end();
    }

} // namespace Event
} // namespace NeuroSync