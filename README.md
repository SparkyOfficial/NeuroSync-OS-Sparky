# NeuroSync OS Sparky

## 🧠 Название проекта: NeuroSync OS Sparky
## (или — «Микроядро для синхронизации процессов и ИИ-модулей»)

## 💡 Идея / Idea / Ідея

Создать экспериментальное микроядро (мини-операционную систему), которое способно управлять потоками и задачами как "нейронами" — т.е. процессы не просто параллельные, а обмениваются сигналами, как в нервной системе.

Create an experimental microkernel (mini-operating system) that can manage threads and tasks as "neurons" - i.e., processes don't just run in parallel, but exchange signals like in a nervous system.

Створити експериментальне мікроядро (міні-операційну систему), яке здатне керувати потоками та завданнями як "нейронами" - тобто процеси не просто паралельні, а обмінюються сигналами, як у нервовій системі.

Такое ядро можно использовать как основу для:
- экспериментов с ИИ, моделированием мозга, системами событий;
- симуляций, где каждый процесс — "нейрон" (в том числе в играх, автоматизации, моделировании).

Such a kernel can be used as a basis for:
- AI experiments, brain modeling, event systems;
- simulations where each process is a "neuron" (including in games, automation, modeling).

Таке ядро можна використовувати як основу для:
- експериментів з ШІ, моделювання мозку, системами подій;
- симуляцій, де кожен процес - "нейрон" (зокрема в іграх, автоматизації, моделюванні).

## ⚙️ Суть проекта / Project essence / Суть проекту

Ты пишешь ядро, которое:
- работает на низком уровне C++ (без STL, почти bare-metal);
- имеет систему "нейронов-процессов" — каждый поток обрабатывает входящие сигналы (сообщения, события);
- поддерживает "синапсы" — каналы связи между потоками (очереди сообщений с приоритетами);
- планирует задачи через весовые связи (ближе к идее нейронных связей, чем обычному scheduler);
- может работать на CPU без ОС, как embedded-ядро, или как библиотека под Linux/Windows.

You're writing a kernel that:
- works at a low level of C++ (without STL, almost bare-metal);
- has a system of "neuron-processes" - each thread processes incoming signals (messages, events);
- supports "synapses" - communication channels between threads (priority message queues);
- schedules tasks through weighted connections (closer to the idea of neural connections than a regular scheduler);
- can run on a CPU without an OS, as an embedded kernel, or as a library under Linux/Windows.

Ви пишете ядро, яке:
- працює на низькому рівні C++ (без STL, майже bare-metal);
- має систему "нейронів-процесів" - кожен потік обробляє вхідні сигнали (повідомлення, події);
- підтримує "синапси" - канали зв'язку між потоками (черги повідомлень з пріоритетами);
- планує завдання через вагові зв'язки (ближче до ідеї нейронних зв'язків, ніж звичайний scheduler);
- може працювати на CPU без ОС, як embedded-ядро, або як бібліотека під Linux/Windows.

## 🔩 Модули проекта / Project modules / Модулі проекту

1. **Core** — планировщик (scheduler), обработка сигналов, система событий.
   - Scheduler - task scheduler, signal processing, event system.

2. **NeuronManager** — создание/удаление "нейронов" (потоков).
   - NeuronManager - creating/deleting "neurons" (threads).

3. **SynapseBus** — механизм связи: очередь сообщений с приоритетом и весом.
   - SynapseBus - communication mechanism: priority and weight message queue.

4. **MemoryCore** — собственный менеджер памяти (pool allocator).
   - MemoryCore - custom memory manager (pool allocator).

5. **Diagnostics** — трассировка активности нейронов (логика в духе "мозговой карты").
   - Diagnostics - neuron activity tracing (logic in the spirit of a "brain map").

6. **API** — C++ интерфейс для создания и управления нейронами, настройка их связей.
   - API - C++ interface for creating and managing neurons, setting up their connections.

## 📁 Структура проекта / Project structure / Структура проекту

```
NeuroSync-OS-Sparky/
├── src/
│   ├── core/          # Планировщик и основные компоненты
│   ├── neuron/        # Менеджер нейронов
│   ├── synapse/       # Шина синапсов
│   ├── memory/        # Менеджер памяти
│   ├── diagnostics/   # Модуль диагностики
│   ├── api/           # C++ интерфейс
│   ├── examples/      # Примеры использования
│   └── tests/         # Тесты
├── CMakeLists.txt     # Основной файл сборки
└── README.md          # Документация
```

## 🛠️ Сборка проекта / Building the project / Збірка проекту

```bash
# Запуск скрипта сборки
# Running the build script
# Запуск скрипта збірки
./build.bat

# Или сборка вручную
# Or manual build
# Або ручна збірка
mkdir _build
cd _build
cmake ..
cmake --build . --config Debug

# Запуск примера
# Running the example
# Запуск прикладу
./_build/bin/Debug/simple_example.exe
```

## 🧪 Пример использования / Usage example / Приклад використання

```cpp
#include "NeuroSync.h"

// Инициализация системы
neurosync_init();

// Создание нейронов
int neuron1 = neurosync_create_neuron(neuron1_process);
int neuron2 = neurosync_create_neuron(neuron2_process);

// Создание связи между нейронами
neurosync_create_connection(neuron1, neuron2, 50);

// Запуск системы
neurosync_start();

// Остановка системы
neurosync_stop();
```

## 📌 TODO

- Реализовать полноценный планировщик задач
- Реализовать систему очередей сообщений с приоритетами
- Реализовать пул аллокатор для эффективного управления памятью
- Добавить поддержку многопоточности
- Реализовать механизм весовых связей между нейронами
- Добавить поддержку встраиваемых скриптов для настройки нейронов