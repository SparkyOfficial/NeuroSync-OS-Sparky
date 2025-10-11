# Plugin System Module
# Модуль системи плагінів
# Модуль системы плагинов

## Overview
## Огляд
## Обзор

The Plugin System module provides a flexible and extensible plugin architecture for NeuroSync OS Sparky. It allows dynamic loading and unloading of modules at runtime, enabling users to extend the functionality of the system without modifying the core codebase. The system supports both Windows DLLs and Unix shared libraries, making it cross-platform compatible.

Модуль системи плагінів забезпечує гнучку та розширювану архітектуру плагінів для NeuroSync OS Sparky. Він дозволяє динамічно завантажувати та вивантажувати модулі під час виконання, дозволяючи користувачам розширювати функціональність системи без зміни базового коду. Система підтримує як Windows DLL, так і Unix shared libraries, роблячи її кросплатформенною.

Модуль системы плагинов обеспечивает гибкую и расширяемую архитектуру плагинов для NeuroSync OS Sparky. Он позволяет динамически загружать и выгружать модули во время выполнения, позволяя пользователям расширять функциональность системы без изменения базового кода. Система поддерживает как Windows DLL, так и Unix shared libraries, делая ее кроссплатформенной.

## Features
## Особливості
## Возможности

- **Dynamic Loading**: Load and unload plugins at runtime
- **Cross-Platform**: Support for both Windows DLLs and Unix shared libraries
- **Thread Safety**: Fully thread-safe implementation with mutexes
- **Plugin Interface**: Standard interface for all plugins
- **Plugin Management**: Load single plugins or all plugins from a directory
- **Plugin Information**: Retrieve detailed information about loaded plugins
- **Error Handling**: Comprehensive error handling and reporting

- **Динамічне завантаження**: Завантаження та вивантаження плагінів під час виконання
- **Кросплатформенність**: Підтримка Windows DLL та Unix shared libraries
- **Потокобезпека**: Повністю потокобезпечна реалізація з використанням м'ютексів
- **Інтерфейс плагінів**: Стандартний інтерфейс для всіх плагінів
- **Управління плагінами**: Завантаження окремих плагінів або всіх плагінів з директорії
- **Інформація про плагіни**: Отримання детальної інформації про завантажені плагіни
- **Обробка помилок**: Вичерпна обробка помилок та звітність

- **Динамическая загрузка**: Загрузка и выгрузка плагинов во время выполнения
- **Кроссплатформенность**: Поддержка Windows DLL и Unix shared libraries
- **Потокобезопасность**: Полностью потокобезопасная реализация с использованием мьютексов
- **Интерфейс плагинов**: Стандартный интерфейс для всех плагинов
- **Управление плагинами**: Загрузка отдельных плагинов или всех плагинов из директории
- **Информация о плагинах**: Получение детальной информации о загруженных плагинах
- **Обработка ошибок**: Исчерпывающая обработка ошибок и отчетность

## API Reference
## Посилання на API
## Ссылка на API

### PluginInterface Class
### Клас PluginInterface
### Класс PluginInterface

The base interface that all plugins must implement.

Базовий інтерфейс, який повинні реалізовувати всі плагіни.

Базовый интерфейс, который должны реализовывать все плагины.

#### Methods
#### Методи
#### Методы

| Method | Description | Опис | Описание |
|--------|-------------|------|----------|
| `virtual bool initialize() = 0` | Initialize the plugin | Ініціалізувати плагін | Инициализировать плагин |
| `virtual void deinitialize() = 0` | Deinitialize the plugin | Деініціалізувати плагін | Деинициализировать плагин |
| `virtual std::string getName() const = 0` | Get plugin name | Отримати ім'я плагіна | Получить имя плагина |
| `virtual std::string getVersion() const = 0` | Get plugin version | Отримати версію плагіна | Получить версию плагина |
| `virtual std::string getDescription() const = 0` | Get plugin description | Отримати опис плагіна | Получить описание плагина |

### PluginSystem Class
### Клас PluginSystem
### Класс PluginSystem

#### Constructor
#### Конструктор
#### Конструктор
```cpp
PluginSystem();
```

#### Methods
#### Методи
#### Методы

| Method | Description | Опис | Описание |
|--------|-------------|------|----------|
| `bool initialize()` | Initialize the plugin system | Ініціалізувати систему плагінів | Инициализировать систему плагинов |
| `bool loadPlugin(const std::string& pluginPath)` | Load a plugin from file | Завантажити плагін з файлу | Загрузить плагин из файла |
| `bool unloadPlugin(const std::string& pluginName)` | Unload a plugin | Вивантажити плагін | Выгрузить плагин |
| `std::vector<std::string> getLoadedPlugins() const` | Get list of loaded plugins | Отримати список завантажених плагінів | Получить список загруженных плагинов |
| `PluginInfo getPluginInfo(const std::string& pluginName) const` | Get plugin information | Отримати інформацію про плагін | Получить информацию о плагине |
| `bool isPluginLoaded(const std::string& pluginName) const` | Check if plugin is loaded | Перевірити чи завантажений плагін | Проверить загружен ли плагин |
| `PluginInterface* getPluginInstance(const std::string& pluginName) const` | Get plugin instance | Отримати екземпляр плагіна | Получить экземпляр плагина |
| `bool loadPluginsFromDirectory(const std::string& directoryPath)` | Load all plugins from directory | Завантажити всі плагіни з директорії | Загрузить все плагины из директории |
| `void unloadAllPlugins()` | Unload all plugins | Вивантажити всі плагіни | Выгрузить все плагины |
| `size_t getPluginCount() const` | Get loaded plugin count | Отримати кількість завантажених плагінів | Получить количество загруженных плагинов |

### PluginInfo Struct
### Структура PluginInfo
### Структура PluginInfo

Information about a loaded plugin.

Інформація про завантажений плагін.

Информация о загруженном плагине.

#### Fields
#### Поля
#### Поля

| Field | Description | Опис | Описание |
|-------|-------------|------|----------|
| `std::string name` | Plugin name | Ім'я плагіна | Имя плагина |
| `std::string version` | Plugin version | Версія плагіна | Версия плагина |
| `std::string description` | Plugin description | Опис плагіна | Описание плагина |
| `std::string filePath` | Plugin file path | Шлях до файлу плагіна | Путь к файлу плагина |
| `PLUGIN_HANDLE handle` | Plugin library handle | Дескриптор бібліотеки плагіна | Дескриптор библиотеки плагина |
| `PluginInterface* instance` | Plugin instance | Екземпляр плагіна | Экземпляр плагина |
| `CreatePluginFunc createFunc` | Plugin creation function | Функція створення плагіна | Функция создания плагина |
| `DestroyPluginFunc destroyFunc` | Plugin destruction function | Функція знищення плагіна | Функция уничтожения плагина |
| `bool loaded` | Plugin loaded flag | Прапор завантаження плагіна | Флаг загрузки плагина |

## Creating Plugins
## Створення плагінів
## Создание плагинов

To create a plugin for NeuroSync OS Sparky, you need to:

1. Inherit from the `PluginInterface` class
2. Implement all required methods
3. Export `createPlugin` and `destroyPlugin` functions
4. Compile as a shared library (DLL on Windows, .so on Unix)

Щоб створити плагін для NeuroSync OS Sparky, потрібно:

1. Успадкувати від класу `PluginInterface`
2. Реалізувати всі необхідні методи
3. Експортувати функції `createPlugin` та `destroyPlugin`
4. Скомпілювати як shared library (DLL на Windows, .so на Unix)

Чтобы создать плагин для NeuroSync OS Sparky, нужно:

1. Унаследоваться от класса `PluginInterface`
2. Реализовать все необходимые методы
3. Экспортировать функции `createPlugin` и `destroyPlugin`
4. Скомпилировать как shared library (DLL на Windows, .so на Unix)

### Example Plugin
### Приклад плагіна
### Пример плагина

```cpp
#include "PluginSystem.h"
#include <string>

class MyPlugin : public NeuroSync::Plugin::PluginInterface {
public:
    MyPlugin() : initialized(false) {}
    virtual ~MyPlugin() {
        if (initialized) {
            deinitialize();
        }
    }
    
    virtual bool initialize() override {
        if (initialized) return true;
        // Initialization code here
        initialized = true;
        return true;
    }
    
    virtual void deinitialize() override {
        if (!initialized) return;
        // Deinitialization code here
        initialized = false;
    }
    
    virtual std::string getName() const override {
        return "MyPlugin";
    }
    
    virtual std::string getVersion() const override {
        return "1.0.0";
    }
    
    virtual std::string getDescription() const override {
        return "An example plugin";
    }
    
    // Custom plugin functionality
    void doSomething() {
        // Plugin functionality here
    }

private:
    bool initialized;
};

// Export functions
extern "C" {
    NeuroSync::Plugin::PluginInterface* createPlugin() {
        return new MyPlugin();
    }
    
    void destroyPlugin(NeuroSync::Plugin::PluginInterface* plugin) {
        delete plugin;
    }
}
```

## Usage Example
## Приклад використання
## Пример использования

```cpp
#include "plugin/PluginSystem.h"

using namespace NeuroSync::Plugin;

int main() {
    // Create plugin system
    PluginSystem pluginSystem;
    
    // Initialize plugin system
    pluginSystem.initialize();
    
    // Load a plugin
    pluginSystem.loadPlugin("my_plugin.dll");
    
    // Get plugin instance
    PluginInterface* plugin = pluginSystem.getPluginInstance("MyPlugin");
    
    // Use plugin (assuming it has custom functionality)
    // MyPlugin* myPlugin = dynamic_cast<MyPlugin*>(plugin);
    // if (myPlugin) {
    //     myPlugin->doSomething();
    // }
    
    // Unload plugin
    pluginSystem.unloadPlugin("MyPlugin");
    
    return 0;
}
```

## Integration
## Інтеграція
## Интеграция

The Plugin System integrates with other NeuroSync OS Sparky modules:

Система плагінів інтегрується з іншими модулями NeuroSync OS Sparky:

Система плагинов интегрируется с другими модулями NeuroSync OS Sparky:

1. **Core**: Can load core extension plugins
2. **NeuronManager**: Can load neuron behavior plugins
3. **SynapseBus**: Can load synapse processing plugins
4. **MemoryCore**: Can load memory management plugins
5. **Diagnostics**: Can load diagnostic plugins
6. **API**: Can load API extension plugins

1. **Core**: Може завантажувати плагіни розширення ядра
2. **NeuronManager**: Може завантажувати плагіни поведінки нейронів
3. **SynapseBus**: Може завантажувати плагіни обробки синапсів
4. **MemoryCore**: Може завантажувати плагіни управління пам'яттю
5. **Diagnostics**: Може завантажувати плагіни діагностики
6. **API**: Може завантажувати плагіни розширення API

1. **Core**: Может загружать плагины расширения ядра
2. **NeuronManager**: Может загружать плагины поведения нейронов
3. **SynapseBus**: Может загружать плагины обработки синапсов
4. **MemoryCore**: Может загружать плагины управления памятью
5. **Diagnostics**: Может загружать плагины диагностики
6. **API**: Может загружать плагины расширения API

## Performance Considerations
## Міркування щодо продуктивності
## Соображения производительности

- Plugin loading and unloading operations are thread-safe but may block briefly
- Plugin functions should be lightweight to avoid blocking the main application thread
- The plugin system uses minimal memory overhead for tracking loaded plugins
- Dynamic loading adds slight overhead during plugin initialization

- Операції завантаження та вивантаження плагінів є потокобезпечними, але можуть короткочасно блокуватися
- Функції плагінів мають бути легкими, щоб уникнути блокування головного потоку програми
- Система плагінів використовує мінімальні накладні витрати пам'яті для відстеження завантажених плагінів
- Динамічне завантаження додає невеликі накладні витрати під час ініціалізації плагіна

- Операции загрузки и выгрузки плагинов являются потокобезопасными, но могут кратковременно блокироваться
- Функции плагинов должны быть легкими, чтобы избежать блокировки главного потока приложения
- Система плагинов использует минимальные накладные расходы памяти для отслеживания загруженных плагинов
- Динамическая загрузка добавляет небольшие накладные расходы во время инициализации плагина