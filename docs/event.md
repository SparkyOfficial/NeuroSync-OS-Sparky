# Event System Module
# Модуль системи подій
# Модуль системы событий

## Overview
## Огляд
## Обзор

The Event System module provides a robust event-driven architecture for NeuroSync OS Sparky. It enables neurons and other components to communicate through events, allowing for loose coupling and flexible system design. The system supports multiple event types, priority-based processing, and thread-safe operations.

Модуль системи подій забезпечує надійну архітектуру, керовану подіями, для NeuroSync OS Sparky. Він дозволяє нейронам та іншим компонентам спілкуватися через події, забезпечуючи слабкий зв'язок та гнучке проектування системи. Система підтримує кілька типів подій, обробку на основі пріоритетів та потокобезпечні операції.

Модуль системы событий обеспечивает надежную архитектуру, управляемую событиями, для NeuroSync OS Sparky. Он позволяет нейронам и другим компонентам общаться через события, обеспечивая слабую связность и гибкое проектирование системы. Система поддерживает несколько типов событий, обработку на основе приоритетов и потокобезопасные операции.

## Features
## Особливості
## Возможности

- **Event Types**: Support for various event types including neuron activation, signal transmission, and custom events.
- **Thread Safety**: Fully thread-safe implementation with mutexes and atomic operations.
- **Priority Processing**: Events can be prioritized for processing order.
- **Subscription Model**: Neurons can subscribe to specific event types.
- **Asynchronous Publishing**: Support for both synchronous and asynchronous event publishing.
- **Statistics Tracking**: Comprehensive statistics on event processing.

- **Типи подій**: Підтримка різних типів подій, включаючи активацію нейронів, передачу сигналів та користувацькі події.
- **Потокобезпека**: Повністю потокобезпечна реалізація з використанням м'ютексів та атомарних операцій.
- **Обробка пріоритетів**: Події можуть мати пріоритет для порядку обробки.
- **Модель підписки**: Нейрони можуть підписуватися на конкретні типи подій.
- **Асинхронна публікація**: Підтримка як синхронної, так і асинхронної публікації подій.
- **Відстеження статистики**: Вичерпна статистика обробки подій.

- **Типы событий**: Поддержка различных типов событий, включая активацию нейронов, передачу сигналов и пользовательские события.
- **Потокобезопасность**: Полностью потокобезопасная реализация с использованием мьютексов и атомарных операций.
- **Обработка приоритетов**: События могут иметь приоритет для порядка обработки.
- **Модель подписки**: Нейроны могут подписываться на конкретные типы событий.
- **Асинхронная публикация**: Поддержка как синхронной, так и асинхронной публикации событий.
- **Отслеживание статистики**: Исчерпывающая статистика обработки событий.

## Event Types
## Типи подій
## Типы событий

1. `NEURON_ACTIVATION` - Neuron activation event
2. `NEURON_DEACTIVATION` - Neuron deactivation event
3. `SIGNAL_TRANSMISSION` - Signal transmission event
4. `CONNECTION_ESTABLISHED` - Connection established event
5. `CONNECTION_BROKEN` - Connection broken event
6. `LEARNING_EVENT` - Learning event
7. `SYSTEM_ERROR` - System error event
8. `CUSTOM_EVENT` - Custom event

1. `NEURON_ACTIVATION` - Подія активації нейрона
2. `NEURON_DEACTIVATION` - Подія деактивації нейрона
3. `SIGNAL_TRANSMISSION` - Подія передачі сигналу
4. `CONNECTION_ESTABLISHED` - Подія встановлення з'єднання
5. `CONNECTION_BROKEN` - Подія розриву з'єднання
6. `LEARNING_EVENT` - Подія навчання
7. `SYSTEM_ERROR` - Подія системної помилки
8. `CUSTOM_EVENT` - Користувацька подія

1. `NEURON_ACTIVATION` - Событие активации нейрона
2. `NEURON_DEACTIVATION` - Событие деактивации нейрона
3. `SIGNAL_TRANSMISSION` - Событие передачи сигнала
4. `CONNECTION_ESTABLISHED` - Событие установления соединения
5. `CONNECTION_BROKEN` - Событие разрыва соединения
6. `LEARNING_EVENT` - Событие обучения
7. `SYSTEM_ERROR` - Событие системной ошибки
8. `CUSTOM_EVENT` - Пользовательское событие

## API Reference
## Посилання на API
## Ссылка на API

### EventSystem Class
### Клас EventSystem
### Класс EventSystem

#### Constructor
#### Конструктор
#### Конструктор
```cpp
EventSystem();
```

#### Methods
#### Методи
#### Методы

| Method | Description | Опис | Описание |
|--------|-------------|------|----------|
| `bool initialize()` | Initialize the event system | Ініціалізувати систему подій | Инициализировать систему событий |
| `void start()` | Start the event processing thread | Запустити потік обробки подій | Запустить поток обработки событий |
| `void stop()` | Stop the event processing thread | Зупинити потік обробки подій | Остановить поток обработки событий |
| `bool registerHandler(EventType type, const EventHandler& handler)` | Register an event handler | Зареєструвати обробник подій | Зарегистрировать обработчик событий |
| `bool removeHandler(EventType type, const EventHandler& handler)` | Remove an event handler | Видалити обробник подій | Удалить обработчик событий |
| `bool publishEvent(const Event& event)` | Publish an event synchronously | Опублікувати подію синхронно | Опубликовать событие синхронно |
| `bool publishEventAsync(const Event& event)` | Publish an event asynchronously | Опублікувати подію асинхронно | Опубликовать событие асинхронно |
| `bool subscribe(int neuronId, EventType type)` | Subscribe to an event type | Підписатися на тип події | Подписаться на тип события |
| `bool unsubscribe(int neuronId, EventType type)` | Unsubscribe from an event type | Відписатися від типу події | Отписаться от типа события |
| `size_t getPendingEventCount() const` | Get the number of pending events | Отримати кількість очікуючих подій | Получить количество ожидающих событий |
| `size_t getProcessedEventCount() const` | Get the number of processed events | Отримати кількість оброблених подій | Получить количество обработанных событий |
| `void clearEventQueue()` | Clear the event queue | Очистити чергу подій | Очистить очередь событий |
| `void setMaxQueueSize(size_t maxSize)` | Set the maximum queue size | Встановити максимальний розмір черги | Установить максимальный размер очереди |
| `size_t getMaxQueueSize() const` | Get the maximum queue size | Отримати максимальний розмір черги | Получить максимальный размер очереди |
| `EventStatistics getStatistics() const` | Get event system statistics | Отримати статистику системи подій | Получить статистику системы событий |

## Usage Example
## Приклад використання
## Пример использования

```cpp
#include "event/EventSystem.h"

using namespace NeuroSync::Event;

// Event handler function
void onNeuronActivation(const Event& event) {
    std::cout << "Neuron " << event.sourceId << " activated" << std::endl;
}

int main() {
    // Create event system
    EventSystem eventSystem;
    
    // Initialize
    eventSystem.initialize();
    
    // Register handler
    eventSystem.registerHandler(EventType::NEURON_ACTIVATION, onNeuronActivation);
    
    // Subscribe to events
    eventSystem.subscribe(1, EventType::NEURON_ACTIVATION);
    
    // Start processing
    eventSystem.start();
    
    // Publish event
    Event event(1, EventType::NEURON_ACTIVATION, 1, 0);
    eventSystem.publishEvent(event);
    
    // Wait and stop
    std::this_thread::sleep_for(std::chrono::seconds(1));
    eventSystem.stop();
    
    return 0;
}
```

## Integration
## Інтеграція
## Интеграция

The Event System integrates with other NeuroSync OS Sparky modules:

Система подій інтегрується з іншими модулями NeuroSync OS Sparky:

Система событий интегрируется с другими модулями NeuroSync OS Sparky:

1. **NeuronManager**: Neurons can publish activation/deactivation events
2. **SynapseBus**: Synapses can publish signal transmission events
3. **Diagnostics**: Can monitor event processing statistics
4. **API**: Provides event-related functions for external control

1. **NeuronManager**: Нейрони можуть публікувати події активації/деактивації
2. **SynapseBus**: Синапси можуть публікувати події передачі сигналів
3. **Diagnostics**: Може відстежувати статистику обробки подій
4. **API**: Надає функції, пов'язані з подіями, для зовнішнього керування

1. **NeuronManager**: Нейроны могут публиковать события активации/деактивации
2. **SynapseBus**: Синапсы могут публиковать события передачи сигналов
3. **Diagnostics**: Может отслеживать статистику обработки событий
4. **API**: Предоставляет функции, связанные с событиями, для внешнего управления

## Performance Considerations
## Міркування щодо продуктивності
## Соображения производительности

- The event system uses a dedicated thread for processing events to avoid blocking the main application thread.
- Event handlers should be lightweight to prevent blocking the event processing thread.
- The system has a configurable maximum queue size to prevent memory exhaustion.
- Statistics are collected with minimal overhead using atomic operations where possible.

- Система подій використовує окремий потік для обробки подій, щоб уникнути блокування головного потоку програми.
- Обробники подій мають бути легкими, щоб запобігти блокуванню потоку обробки подій.
- Система має налаштовуваний максимальний розмір черги, щоб запобігти вичерпанню пам'яті.
- Статистика збирається з мінімальними накладними витратами за допомогою атомарних операцій, де це можливо.

- Система событий использует отдельный поток для обработки событий, чтобы избежать блокировки главного потока приложения.
- Обработчики событий должны быть легкими, чтобы предотвратить блокировку потока обработки событий.
- Система имеет настраиваемый максимальный размер очереди, чтобы предотвратить исчерпание памяти.
- Статистика собирается с минимальными накладными расходами с помощью атомарных операций, где это возможно.