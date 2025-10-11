# Logging System Module
# Модуль системи логування
# Модуль системы логирования

## Overview
## Огляд
## Обзор

The Logging System module provides a comprehensive logging framework for NeuroSync OS Sparky. It supports multiple output formats (console, file, network, custom) and different log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL). The system is thread-safe and designed for high-performance logging in a multi-threaded environment.

Модуль системи логування забезпечує комплексну систему логування для NeuroSync OS Sparky. Він підтримує кілька форматів виводу (консоль, файл, мережа, користувацький) та різні рівні логування (DEBUG, INFO, WARNING, ERROR, CRITICAL). Система є потокобезпечною та розроблена для високопродуктивного логування в багатопоточному середовищі.

Модуль системы логирования обеспечивает комплексную систему логирования для NeuroSync OS Sparky. Он поддерживает несколько форматов вывода (консоль, файл, сеть, пользовательский) и различные уровни логирования (DEBUG, INFO, WARNING, ERROR, CRITICAL). Система является потокобезопасной и разработана для высокопроизводительного логирования в многопоточной среде.

## Features
## Особливості
## Возможности

- **Multiple Log Levels**: Support for DEBUG, INFO, WARNING, ERROR, and CRITICAL levels
- **Multiple Output Formats**: Console, file, network, and custom output support
- **Thread Safety**: Fully thread-safe implementation with mutexes
- **Colorized Console Output**: Different colors for different log levels
- **Timestamp Support**: Precise timestamp with milliseconds
- **Module Identification**: Log messages can be tagged with module names
- **Thread Identification**: Each log entry includes thread ID
- **Flexible Configuration**: Runtime configuration of log levels and outputs

- **Кілька рівнів логування**: Підтримка рівнів DEBUG, INFO, WARNING, ERROR та CRITICAL
- **Кілька форматів виводу**: Підтримка виводу в консоль, файл, мережу та користувацький вивід
- **Потокобезпека**: Повністю потокобезпечна реалізація з використанням м'ютексів
- **Кольоровий консольний вивід**: Різні кольори для різних рівнів логування
- **Підтримка міток часу**: Точна мітка часу з мілісекундами
- **Ідентифікація модулів**: Повідомлення логу можуть бути позначені іменами модулів
- **Ідентифікація потоків**: Кожен запис логу включає ID потоку
- **Гнучка конфігурація**: Налаштування рівнів логування та виводів під час виконання

- **Несколько уровней логирования**: Поддержка уровней DEBUG, INFO, WARNING, ERROR и CRITICAL
- **Несколько форматов вывода**: Поддержка вывода в консоль, файл, сеть и пользовательский вывод
- **Потокобезопасность**: Полностью потокобезопасная реализация с использованием мьютексов
- **Цветной консольный вывод**: Разные цвета для разных уровней логирования
- **Поддержка меток времени**: Точная метка времени с миллисекундами
- **Идентификация модулей**: Сообщения лога могут быть помечены именами модулей
- **Идентификация потоков**: Каждая запись лога включает ID потока
- **Гибкая конфигурация**: Настройка уровней логирования и выводов во время выполнения

## API Reference
## Посилання на API
## Ссылка на API

### LogLevel Enum
### Перерахування LogLevel
### Перечисление LogLevel

| Value | Description | Опис | Описание |
|-------|-------------|------|----------|
| `DEBUG` | Debug level messages | Повідомлення рівня налагодження | Сообщения уровня отладки |
| `INFO` | Informational messages | Інформаційні повідомлення | Информационные сообщения |
| `WARNING` | Warning messages | Попереджувальні повідомлення | Предупреждающие сообщения |
| `ERROR` | Error messages | Повідомлення про помилки | Сообщения об ошибках |
| `CRITICAL` | Critical error messages | Критичні повідомлення про помилки | Критические сообщения об ошибках |

### LogOutputType Enum
### Перерахування LogOutputType
### Перечисление LogOutputType

| Value | Description | Опис | Описание |
|-------|-------------|------|----------|
| `CONSOLE` | Console output | Вивід у консоль | Вывод в консоль |
| `FILE` | File output | Вивід у файл | Вывод в файл |
| `NETWORK` | Network output | Мережевий вивід | Сетевой вывод |
| `CUSTOM` | Custom output | Користувацький вивід | Пользовательский вывод |

### LoggingSystem Class
### Клас LoggingSystem
### Класс LoggingSystem

#### Constructor
#### Конструктор
#### Конструктор
```cpp
LoggingSystem();
```

#### Methods
#### Методи
#### Методы

| Method | Description | Опис | Описание |
|--------|-------------|------|----------|
| `bool initialize()` | Initialize the logging system | Ініціалізувати систему логування | Инициализировать систему логирования |
| `void setLogLevel(LogLevel level)` | Set the logging level | Встановити рівень логування | Установить уровень логирования |
| `LogLevel getLogLevel() const` | Get the current logging level | Отримати поточний рівень логування | Получить текущий уровень логирования |
| `bool addLogOutput(std::shared_ptr<LogOutput> output)` | Add a log output | Додати вивід логу | Добавить вывод лога |
| `bool removeLogOutput(LogOutputType type)` | Remove a log output | Видалити вивід логу | Удалить вывод лога |
| `void log(LogLevel level, const std::string& module, const std::string& message)` | Write a log message | Записати повідомлення логу | Записать сообщение лога |
| `void debug(const std::string& module, const std::string& message)` | Write a DEBUG level log message | Записати повідомлення логу рівня DEBUG | Записать сообщение лога уровня DEBUG |
| `void info(const std::string& module, const std::string& message)` | Write an INFO level log message | Записати повідомлення логу рівня INFO | Записать сообщение лога уровня INFO |
| `void warning(const std::string& module, const std::string& message)` | Write a WARNING level log message | Записати повідомлення логу рівня WARNING | Записать сообщение лога уровня WARNING |
| `void error(const std::string& module, const std::string& message)` | Write an ERROR level log message | Записати повідомлення логу рівня ERROR | Записать сообщение лога уровня ERROR |
| `void critical(const std::string& module, const std::string& message)` | Write a CRITICAL level log message | Записати повідомлення логу рівня CRITICAL | Записать сообщение лога уровня CRITICAL |
| `size_t getOutputCount() const` | Get the number of log outputs | Отримати кількість виводів логу | Получить количество выводов лога |
| `void closeAllOutputs()` | Close all log outputs | Закрити всі виводи логу | Закрыть все выводы лога |
| `std::string formatLogMessage(const LogEntry& entry) const` | Format a log message | Форматувати повідомлення логу | Форматировать сообщение лога |
| `std::string getCurrentTimestamp() const` | Get current timestamp | Отримати поточну мітку часу | Получить текущую метку времени |
| `std::string getThreadId() const` | Get current thread ID | Отримати ID поточного потоку | Получить ID текущего потока |
| `std::string getLogLevelName(LogLevel level) const` | Get log level name | Отримати назву рівня логування | Получить название уровня логирования |

### LogOutput Class
### Клас LogOutput
### Класс LogOutput

Base interface for all log outputs.

Базовий інтерфейс для всіх виводів логу.

Базовый интерфейс для всех выводов лога.

#### Methods
#### Методи
#### Методы

| Method | Description | Опис | Описание |
|--------|-------------|------|----------|
| `virtual void writeLog(const LogEntry& entry) = 0` | Write a log entry | Записати запис логу | Записать запись лога |
| `virtual LogOutputType getType() const = 0` | Get output type | Отримати тип виводу | Получить тип вывода |
| `virtual bool initialize() = 0` | Initialize output | Ініціалізувати вивід | Инициализировать вывод |
| `virtual void close() = 0` | Close output | Закрити вивід | Закрыть вывод |

### ConsoleLogOutput Class
### Клас ConsoleLogOutput
### Класс ConsoleLogOutput

Console log output implementation.

Реалізація виводу логу в консоль.

Реализация вывода лога в консоль.

#### Constructor
#### Конструктор
#### Конструктор
```cpp
ConsoleLogOutput();
```

### FileLogOutput Class
### Клас FileLogOutput
### Класс FileLogOutput

File log output implementation.

Реалізація виводу логу у файл.

Реализация вывода лога в файл.

#### Constructor
#### Конструктор
#### Конструктор
```cpp
FileLogOutput(const std::string& filename);
```

#### Methods
#### Методи
#### Методы

| Method | Description | Опис | Описание |
|--------|-------------|------|----------|
| `void setFilename(const std::string& filename)` | Set the filename | Встановити ім'я файлу | Установить имя файла |
| `std::string getFilename() const` | Get the filename | Отримати ім'я файлу | Получить имя файла |

## Usage Example
## Приклад використання
## Пример использования

```cpp
#include "logging/LoggingSystem.h"

using namespace NeuroSync::Logging;

int main() {
    // Initialize the global logger
    gLogger.initialize();
    
    // Set log level to DEBUG
    gLogger.setLogLevel(LogLevel::DEBUG);
    
    // Write logs of different levels
    gLogger.debug("MyModule", "This is a debug message");
    gLogger.info("MyModule", "This is an info message");
    gLogger.warning("MyModule", "This is a warning message");
    gLogger.error("MyModule", "This is an error message");
    gLogger.critical("MyModule", "This is a critical message");
    
    // Add file output
    auto fileOutput = std::make_shared<FileLogOutput>("myapp.log");
    gLogger.addLogOutput(fileOutput);
    
    // Write a message that will go to both console and file
    gLogger.info("MyModule", "This message goes to console and file");
    
    // Remove file output
    gLogger.removeLogOutput(LogOutputType::FILE);
    
    // Close all outputs
    gLogger.closeAllOutputs();
    
    return 0;
}
```

## Integration
## Інтеграція
## Интеграция

The Logging System integrates with other NeuroSync OS Sparky modules:

Система логування інтегрується з іншими модулями NeuroSync OS Sparky:

Система логирования интегрируется с другими модулями NeuroSync OS Sparky:

1. **Core**: Logs scheduler operations and system events
2. **NeuronManager**: Logs neuron lifecycle events
3. **SynapseBus**: Logs signal transmission and connection events
4. **MemoryCore**: Logs memory allocation and deallocation
5. **Diagnostics**: Logs diagnostic information
6. **API**: Logs API calls and responses
7. **EventSystem**: Logs event processing
8. **ConfigurationManager**: Logs configuration changes

1. **Core**: Логує операції планувальника та системні події
2. **NeuronManager**: Логує події життєвого циклу нейронів
3. **SynapseBus**: Логує передачу сигналів та події з'єднання
4. **MemoryCore**: Логує виділення та звільнення пам'яті
5. **Diagnostics**: Логує діагностичну інформацію
6. **API**: Логує виклики API та відповіді
7. **EventSystem**: Логує обробку подій
8. **ConfigurationManager**: Логує зміни конфігурації

1. **Core**: Логирует операции планировщика и системные события
2. **NeuronManager**: Логирует события жизненного цикла нейронов
3. **SynapseBus**: Логирует передачу сигналов и события соединения
4. **MemoryCore**: Логирует выделение и освобождение памяти
5. **Diagnostics**: Логирует диагностическую информацию
6. **API**: Логирует вызовы API и ответы
7. **EventSystem**: Логирует обработку событий
8. **ConfigurationManager**: Логирует изменения конфигурации

## Performance Considerations
## Міркування щодо продуктивності
## Соображения производительности

- Log messages are formatted only when they need to be written
- Thread safety is implemented with mutexes, which may introduce slight overhead in high-concurrency scenarios
- Console output uses color codes for better readability without significant performance impact
- File output uses buffered writing for better performance
- The system supports runtime configuration of log levels to reduce logging overhead when detailed logging is not needed

- Повідомлення логу форматуються лише тоді, коли їх потрібно записати
- Потокобезпека реалізована за допомогою м'ютексів, що може призвести до невеликих накладних витрат у сценаріях з високою паралелізацією
- Консольний вивід використовує коди кольорів для кращої читабельності без значного впливу на продуктивність
- Файловий вивід використовує буферизований запис для кращої продуктивності
- Система підтримує налаштування рівнів логування під час виконання для зменшення накладних витрат на логування, коли детальне логування не потрібне

- Сообщения лога форматируются только когда их нужно записать
- Потокобезопасность реализована с помощью мьютексов, что может привести к небольшим накладным расходам в сценариях с высокой параллелизацией
- Консольный вывод использует коды цветов для лучшей читаемости без значительного влияния на производительность
- Файловый вывод использует буферизованную запись для лучшей производительности
- Система поддерживает настройку уровней логирования во время выполнения для уменьшения накладных расходов на логирование, когда детальное логирование не нужно