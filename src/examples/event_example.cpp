// event_example.cpp
// Приклад використання системи подій / Event system usage example / Пример использования системы событий
// NeuroSync OS Sparky

#include "../event/EventSystem.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace NeuroSync::Event;

// Обробник подій активації нейрона
// Neuron activation event handler
// Обработчик события активации нейрона
void onNeuronActivation(const Event& event) {
    std::cout << "Neuron " << event.sourceId << " activated at " << event.timestamp << std::endl;
}

// Обробник подій передачі сигналу
// Signal transmission event handler
// Обработчик события передачи сигнала
void onSignalTransmission(const Event& event) {
    std::cout << "Signal transmitted from neuron " << event.sourceId 
              << " to neuron " << event.targetId << " with data: " << event.data << std::endl;
}

// Обробник подій навчання
// Learning event handler
// Обработчик события обучения
void onLearningEvent(const Event& event) {
    std::cout << "Learning event occurred in neuron " << event.sourceId 
              << " with data: " << event.data << std::endl;
}

int main() {
    std::cout << "NeuroSync OS Sparky - Event System Example" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    // Створення системи подій
    // Create event system
    // Создание системы событий
    EventSystem eventSystem;
    
    // Ініціалізація системи подій
    // Initialize event system
    // Инициализация системы событий
    if (!eventSystem.initialize()) {
        std::cerr << "Failed to initialize event system" << std::endl;
        return 1;
    }
    
    // Реєстрація обробників подій
    // Register event handlers
    // Регистрация обработчиков событий
    eventSystem.registerHandler(EventType::NEURON_ACTIVATION, onNeuronActivation);
    eventSystem.registerHandler(EventType::SIGNAL_TRANSMISSION, onSignalTransmission);
    eventSystem.registerHandler(EventType::LEARNING_EVENT, onLearningEvent);
    
    // Підписка на події
    // Subscribe to events
    // Подписка на события
    eventSystem.subscribe(1, EventType::NEURON_ACTIVATION);
    eventSystem.subscribe(2, EventType::SIGNAL_TRANSMISSION);
    eventSystem.subscribe(3, EventType::LEARNING_EVENT);
    
    // Запуск системи подій
    // Start event system
    // Запуск системы событий
    eventSystem.start();
    
    // Публікація подій
    // Publish events
    // Публикация событий
    Event activationEvent(1, EventType::NEURON_ACTIVATION, 1, 0, "", 1);
    Event transmissionEvent(2, EventType::SIGNAL_TRANSMISSION, 1, 2, "signal_data", 2);
    Event learningEvent(3, EventType::LEARNING_EVENT, 3, 0, "learning_data", 3);
    
    eventSystem.publishEvent(activationEvent);
    eventSystem.publishEvent(transmissionEvent);
    eventSystem.publishEvent(learningEvent);
    
    // Зачекати трохи, щоб обробники встигли виконатися
    // Wait a bit for handlers to execute
    // Подождать немного, чтобы обработчики успели выполниться
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Отримання статистики
    // Get statistics
    // Получение статистики
    auto stats = eventSystem.getStatistics();
    std::cout << "\nEvent System Statistics:" << std::endl;
    std::cout << "Total Events Published: " << stats.totalEventsPublished << std::endl;
    std::cout << "Total Events Processed: " << stats.totalEventsProcessed << std::endl;
    std::cout << "Total Events Dropped: " << stats.totalEventsDropped << std::endl;
    std::cout << "Active Subscriptions: " << stats.activeSubscriptions << std::endl;
    std::cout << "Registered Handlers: " << stats.registeredHandlers << std::endl;
    
    // Зупинка системи подій
    // Stop event system
    // Остановка системы событий
    eventSystem.stop();
    
    std::cout << "\nEvent system example completed successfully!" << std::endl;
    
    return 0;
}