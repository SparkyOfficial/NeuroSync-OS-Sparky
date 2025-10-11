// test_event_system.cpp
// Тестування системи подій / Event system testing / Тестирование системы событий
// NeuroSync OS Sparky

#include "../event/EventSystem.h"
#include <iostream>
#include <thread>
#include <cassert>
#include <atomic>

using namespace NeuroSync::Event;

// Атомічний лічильник для тестування
// Atomic counter for testing
// Атомарный счетчик для тестирования
std::atomic<int> activationCount(0);
std::atomic<int> transmissionCount(0);

// Тестовий обробник подій активації
// Test neuron activation event handler
// Тестовый обработчик события активации
void testActivationHandler(const Event& event) {
    if (event.type == EventType::NEURON_ACTIVATION) {
        activationCount++;
    }
}

// Тестовий обробник подій передачі
// Test signal transmission event handler
// Тестовый обработчик события передачи
void testTransmissionHandler(const Event& event) {
    if (event.type == EventType::SIGNAL_TRANSMISSION) {
        transmissionCount++;
    }
}

int main() {
    std::cout << "NeuroSync OS Sparky - Event System Tests" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // Тест 1: Створення та ініціалізація
    // Test 1: Creation and initialization
    // Тест 1: Создание и инициализация
    std::cout << "Test 1: Creating and initializing EventSystem..." << std::endl;
    EventSystem eventSystem;
    assert(eventSystem.initialize());
    std::cout << "PASS: EventSystem created and initialized successfully" << std::endl;
    
    // Тест 2: Реєстрація обробників
    // Test 2: Handler registration
    // Тест 2: Регистрация обработчиков
    std::cout << "Test 2: Registering event handlers..." << std::endl;
    bool handlerRegistered = eventSystem.registerHandler(EventType::NEURON_ACTIVATION, testActivationHandler);
    assert(handlerRegistered);
    
    handlerRegistered = eventSystem.registerHandler(EventType::SIGNAL_TRANSMISSION, testTransmissionHandler);
    assert(handlerRegistered);
    std::cout << "PASS: Event handlers registered successfully" << std::endl;
    
    // Тест 3: Підписка на події
    // Test 3: Event subscription
    // Тест 3: Подписка на события
    std::cout << "Test 3: Subscribing to events..." << std::endl;
    bool subscribed = eventSystem.subscribe(1, EventType::NEURON_ACTIVATION);
    assert(subscribed);
    
    subscribed = eventSystem.subscribe(2, EventType::SIGNAL_TRANSMISSION);
    assert(subscribed);
    std::cout << "PASS: Subscribed to events successfully" << std::endl;
    
    // Тест 4: Запуск системи подій
    // Test 4: Starting event system
    // Тест 4: Запуск системы событий
    std::cout << "Test 4: Starting event system..." << std::endl;
    eventSystem.start();
    std::cout << "PASS: Event system started successfully" << std::endl;
    
    // Тест 5: Публікація подій
    // Test 5: Publishing events
    // Тест 5: Публикация событий
    std::cout << "Test 5: Publishing events..." << std::endl;
    Event activationEvent(1, EventType::NEURON_ACTIVATION, 1, 0, "", 1);
    Event transmissionEvent(2, EventType::SIGNAL_TRANSMISSION, 1, 2, "test_data", 2);
    
    bool published = eventSystem.publishEvent(activationEvent);
    assert(published);
    
    published = eventSystem.publishEvent(transmissionEvent);
    assert(published);
    std::cout << "PASS: Events published successfully" << std::endl;
    
    // Зачекати, щоб обробники встигли виконатися
    // Wait for handlers to execute
    // Подождать, чтобы обработчики успели выполниться
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Тест 6: Перевірка обробки подій
    // Test 6: Checking event processing
    // Тест 6: Проверка обработки событий
    std::cout << "Test 6: Checking event processing..." << std::endl;
    assert(activationCount.load() == 1);
    assert(transmissionCount.load() == 1);
    std::cout << "PASS: Events processed correctly" << std::endl;
    
    // Тест 7: Статистика
    // Test 7: Statistics
    // Тест 7: Статистика
    std::cout << "Test 7: Checking statistics..." << std::endl;
    auto stats = eventSystem.getStatistics();
    assert(stats.totalEventsPublished == 2);
    assert(stats.totalEventsProcessed == 2);
    assert(stats.totalEventsDropped == 0);
    assert(stats.registeredHandlers == 2);
    assert(stats.activeSubscriptions == 2);
    std::cout << "PASS: Statistics are correct" << std::endl;
    
    // Тест 8: Зупинка системи подій
    // Test 8: Stopping event system
    // Тест 8: Остановка системы событий
    std::cout << "Test 8: Stopping event system..." << std::endl;
    eventSystem.stop();
    std::cout << "PASS: Event system stopped successfully" << std::endl;
    
    // Тест 9: Видалення обробників
    // Test 9: Removing handlers
    // Тест 9: Удаление обработчиков
    std::cout << "Test 9: Removing event handlers..." << std::endl;
    bool handlerRemoved = eventSystem.removeHandler(EventType::NEURON_ACTIVATION, testActivationHandler);
    assert(handlerRemoved);
    std::cout << "PASS: Event handlers removed successfully" << std::endl;
    
    // Тест 10: Відписка від подій
    // Test 10: Unsubscribing from events
    // Тест 10: Отписка от событий
    std::cout << "Test 10: Unsubscribing from events..." << std::endl;
    bool unsubscribed = eventSystem.unsubscribe(1, EventType::NEURON_ACTIVATION);
    assert(unsubscribed);
    std::cout << "PASS: Unsubscribed from events successfully" << std::endl;
    
    std::cout << "\nAll Event System tests passed!" << std::endl;
    return 0;
}