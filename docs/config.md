# Configuration Manager Module
# Модуль менеджера конфігурації
# Модуль менеджера конфигурации

## Overview
## Огляд
## Обзор

The Configuration Manager module provides a flexible and thread-safe configuration system for NeuroSync OS Sparky. It allows runtime configuration of system parameters through key-value pairs with support for multiple data types (string, integer, float, boolean). The module supports loading and saving configurations from/to files, making it easy to persist settings across system restarts.

Модуль менеджера конфігурації забезпечує гнучку та потокобезпечну систему конфігурації для NeuroSync OS Sparky. Він дозволяє налаштовувати параметри системи під час виконання через пари ключ-значення з підтримкою кількох типів даних (рядок, ціле число, число з плаваючою точкою, булеве значення). Модуль підтримує завантаження та збереження конфігурацій з/у файли, що полегшує збереження налаштувань між перезапусками системи.

Модуль менеджера конфигурации обеспечивает гибкую и потокобезопасную систему конфигурации для NeuroSync OS Sparky. Он позволяет настраивать параметры системы во время выполнения через пары ключ-значение с поддержкой нескольких типов данных (строка, целое число, число с плавающей точкой, булево значение). Модуль поддерживает загрузку и сохранение конфигураций из/в файлы, что облегчает сохранение настроек между перезапусками системы.

## Features
## Особливості
## Возможности

- **Multiple Data Types**: Support for string, integer, float, and boolean values
- **Thread Safety**: Fully thread-safe implementation with mutexes
- **File Persistence**: Load and save configurations to/from files
- **Default Values**: Built-in default configuration values
- **Key Management**: Add, retrieve, update, and remove configuration keys
- **Configuration Validation**: Type-safe configuration value handling

- **Кілька типів даних**: Підтримка значень рядка, цілого числа, числа з плаваючою точкою та булевих значень
- **Потокобезпека**: Повністю потокобезпечна реалізація з використанням м'ютексів
- **Збереження у файлі**: Завантаження та збереження конфігурацій з/у файли
- **Значення за замовчуванням**: Вбудовані значення конфігурації за замовчуванням
- **Управління ключами**: Додавання, отримання, оновлення та видалення ключів конфігурації
- **Валідація конфігурації**: Безпечна обробка значень конфігурації з урахуванням типів

- **Несколько типов данных**: Поддержка значений строки, целого числа, числа с плавающей точкой и булевых значений
- **Потокобезопасность**: Полностью потокобезопасная реализация с использованием мьютексов
- **Сохранение в файле**: Загрузка и сохранение конфигураций из/в файлы
- **Значения по умолчанию**: Встроенные значения конфигурации по умолчанию
- **Управление ключами**: Добавление, получение, обновление и удаление ключей конфигурации
- **Валидация конфигурации**: Безопасная обработка значений конфигурации с учетом типов

## API Reference
## Посилання на API
## Ссылка на API

### ConfigurationManager Class
### Клас ConfigurationManager
### Класс ConfigurationManager

#### Constructor
#### Конструктор
#### Конструктор
```cpp
ConfigurationManager();
```

#### Methods
#### Методи
#### Методы

| Method | Description | Опис | Описание |
|--------|-------------|------|----------|
| `bool initialize(const std::string& configFile = "")` | Initialize the configuration manager | Ініціалізувати менеджер конфігурації | Инициализировать менеджер конфигурации |
| `bool loadFromFile(const std::string& filename)` | Load configuration from file | Завантажити конфігурацію з файлу | Загрузить конфигурацию из файла |
| `bool saveToFile(const std::string& filename) const` | Save configuration to file | Зберегти конфігурацію у файл | Сохранить конфигурацию в файл |
| `void setConfigValue(const std::string& key, const ConfigValue& value)` | Set configuration value | Встановити значення конфігурації | Установить значение конфигурации |
| `ConfigValue getConfigValue(const std::string& key) const` | Get configuration value | Отримати значення конфігурації | Получить значение конфигурации |
| `std::string getString(const std::string& key, const std::string& defaultValue = "") const` | Get string value | Отримати строкове значення | Получить строковое значение |
| `int getInteger(const std::string& key, int defaultValue = 0) const` | Get integer value | Отримати ціле значення | Получить целое значение |
| `float getFloat(const std::string& key, float defaultValue = 0.0f) const` | Get float value | Отримати число з плаваючою точкою | Получить число с плавающей точкой |
| `bool getBoolean(const std::string& key, bool defaultValue = false) const` | Get boolean value | Отримати булеве значення | Получить булево значение |
| `bool hasKey(const std::string& key) const` | Check if key exists | Перевірити наявність ключа | Проверить наличие ключа |
| `void removeConfigValue(const std::string& key)` | Remove configuration value | Видалити значення конфігурації | Удалить значение конфигурации |
| `std::vector<std::string> getAllKeys() const` | Get all keys | Отримати всі ключі | Получить все ключи |
| `void clear()` | Clear all configuration values | Очистити всі значення конфігурації | Очистить все значения конфигурации |
| `size_t getConfigCount() const` | Get configuration count | Отримати кількість конфігурацій | Получить количество конфигураций |
| `void setDefaultConfiguration()` | Set default configuration | Встановити конфігурацію за замовчуванням | Установить конфигурацию по умолчанию |

## Configuration File Format
## Формат файлу конфігурації
## Формат файла конфигурации

The configuration file format is simple key-value pairs with support for comments:

Формат файлу конфігурації - це прості пари ключ-значення з підтримкою коментарів:

Формат файла конфигурации - это простые пары ключ-значение с поддержкой комментариев:

```
# This is a comment
; This is also a comment

system.name = NeuroSync OS Sparky
system.version = 1.0.0
system.debug = true
system.log_level = 2
scheduler.max_threads = 8
scheduler.quantum_ms = 10
memory.pool_size = 1048576
```

## Usage Example
## Приклад використання
## Пример использования

```cpp
#include "config/ConfigurationManager.h"

using namespace NeuroSync::Config;

int main() {
    // Create configuration manager
    ConfigurationManager configManager;
    
    // Initialize with default configuration
    configManager.initialize();
    
    // Get configuration values
    std::string systemName = configManager.getString("system.name");
    bool debugMode = configManager.getBoolean("system.debug");
    int maxThreads = configManager.getInteger("scheduler.max_threads");
    
    // Set new configuration values
    configManager.setConfigValue("custom.setting", ConfigValue("custom_value"));
    configManager.setConfigValue("custom.number", ConfigValue(42));
    
    // Save configuration to file
    configManager.saveToFile("config.txt");
    
    // Load configuration from file
    ConfigurationManager loadedConfig;
    loadedConfig.loadFromFile("config.txt");
    
    return 0;
}
```

## Integration
## Інтеграція
## Интеграция

The Configuration Manager integrates with other NeuroSync OS Sparky modules:

Менеджер конфігурації інтегрується з іншими модулями NeuroSync OS Sparky:

Менеджер конфигурации интегрируется с другими модулями NeuroSync OS Sparky:

1. **Core**: Configures scheduler parameters
2. **NeuronManager**: Configures neuron limits and behavior
3. **SynapseBus**: Configures connection limits and priorities
4. **MemoryCore**: Configures memory pool sizes
5. **EventSystem**: Configures event queue sizes
6. **Diagnostics**: Configures logging levels and output formats

1. **Core**: Налаштовує параметри планувальника
2. **NeuronManager**: Налаштовує обмеження нейронів та поведінку
3. **SynapseBus**: Налаштовує обмеження з'єднань та пріоритети
4. **MemoryCore**: Налаштовує розміри пулу пам'яті
5. **EventSystem**: Налаштовує розміри черги подій
6. **Diagnostics**: Налаштовує рівні ведення журналів та формати виводу

1. **Core**: Настраивает параметры планировщика
2. **NeuronManager**: Настраивает ограничения нейронов и поведение
3. **SynapseBus**: Настраивает ограничения соединений и приоритеты
4. **MemoryCore**: Настраивает размеры пула памяти
5. **EventSystem**: Настраивает размеры очереди событий
6. **Diagnostics**: Настраивает уровни ведения журналов и форматы вывода

## Performance Considerations
## Міркування щодо продуктивності
## Соображения производительности

- Configuration values are stored in a hash map for O(1) average lookup time
- Thread safety is implemented with mutexes, which may introduce slight overhead in high-concurrency scenarios
- File I/O operations are performed synchronously and may block during load/save operations
- Memory usage is minimal, with configuration values stored as simple structures

- Значення конфігурації зберігаються в хеш-карті для середнього часу пошуку O(1)
- Потокобезпека реалізована за допомогою м'ютексів, що може призвести до невеликих накладних витрат у сценаріях з високою паралелізацією
- Операції вводу-виводу файлів виконуються синхронно і можуть блокуватися під час операцій завантаження/збереження
- Використання пам'яті мінімальне, значення конфігурації зберігаються як прості структури

- Значения конфигурации хранятся в хеш-карте для среднего времени поиска O(1)
- Потокобезопасность реализована с помощью мьютексов, что может привести к небольшим накладным расходам в сценариях с высокой параллелизацией
- Операции ввода-вывода файлов выполняются синхронно и могут блокироваться во время операций загрузки/сохранения
- Использование памяти минимальное, значения конфигурации хранятся как простые структуры