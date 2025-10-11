# Testing Framework
# Тестувальний фреймворк
# Тестовый фреймворк

## Overview
# Огляд
# Обзор

The Testing Framework is a comprehensive unit testing framework designed specifically for the NeuroSync OS Sparky microkernel. It provides support for various types of testing including unit tests, integration tests, system tests, performance tests, stress tests, and regression tests.

Тестувальний фреймворк - це комплексний фреймворк для модульного тестування, розроблений спеціально для мікроядра NeuroSync OS Sparky. Він забезпечує підтримку різних типів тестування, включаючи модульні тести, інтеграційні тести, системні тести, тести продуктивності, стрес-тести та регресійні тести.

Тестовый фреймворк - это комплексный фреймворк для модульного тестирования, разработанный специально для микроядра NeuroSync OS Sparky. Он обеспечивает поддержку различных типов тестирования, включая модульные тесты, интеграционные тесты, системные тесты, тесты производительности, стресс-тесты и регрессионные тесты.

## Features
# Особливості
# Особенности

- Multiple test types support (Unit, Integration, System, Performance, Stress, Regression)
- Поддержка нескольких типов тестов (Модульные, Интеграционные, Системные, Производительности, Стресс, Регрессионные)
- Підтримка кількох типів тестів (Модульні, Інтеграційні, Системні, Продуктивності, Стрес, Регресійні)

- Assertion macros for easy test writing
- Макроси тверджень для легкого написання тестів
- Макросы утверждений для легкого написания тестов

- Test suites for organizing tests
- Набори тестів для організації тестів
- Наборы тестов для организации тестов

- Configurable test execution (verbose output, color output, stop on failure)
- Налаштовуване виконання тестів (докладний вивід, кольоровий вивід, зупинка при помилці)
- Настраиваемое выполнение тестов (подробный вывод, цветной вывод, остановка при ошибке)

- Parallel test execution
- Паралельне виконання тестів
- Параллельное выполнение тестов

- Test result reporting in multiple formats (text, XML, JSON)
- Звіт про результати тестів у кількох форматах (текст, XML, JSON)
- Отчет о результатах тестов в нескольких форматах (текст, XML, JSON)

- Export/import test results
- Експорт/імпорт результатів тестів
- Экспорт/импорт результатов тестов

## Usage
# Використання
# Использование

### Basic Example
# Базовий приклад
# Базовый пример

```cpp
#include "TestingFramework.h"

using namespace NeuroSync;

// Initialize global testing framework
std::unique_ptr<TestingFramework> NeuroSync::gTestingFramework = std::make_unique<TestingFramework>();

// Sample test function
void testAddition() {
    ASSERT_EQUAL(4, 2 + 2);
    ASSERT_EQUAL(0, -1 + 1);
}

int main() {
    // Configure testing framework
    TestingConfig config;
    config.enableVerboseOutput = true;
    
    gTestingFramework->initialize(config);
    
    // Register test suite and test
    gTestingFramework->registerTestSuite("MathTests");
    gTestingFramework->registerTest("MathTests", "AdditionTest", TestType::UNIT, testAddition);
    
    // Run tests
    bool success = gTestingFramework->runAllTests();
    
    // Generate report
    std::string report = gTestingFramework->generateReport();
    std::cout << report << std::endl;
    
    return success ? 0 : 1;
}
```

## API Reference
# Посилання на API
# Ссылка на API

### TestingFramework Class
# Клас TestingFramework
# Класс TestingFramework

#### Constructor
# Конструктор
# Конструктор
```cpp
TestingFramework();
```

#### initialize
# ініціалізація
# инициализация
```cpp
bool initialize(const TestingConfig& config);
```
Initializes the testing framework with the provided configuration.
Ініціалізує тестувальний фреймворк із наданою конфігурацією.
Инициализирует тестовый фреймворк с предоставленной конфигурацией.

#### registerTest
# реєстрація тесту
# регистрация теста
```cpp
void registerTest(const std::string& suiteName, 
                  const std::string& testName,
                  TestType type,
                  std::function<void()> testFunction);
```
Registers a test function with the specified suite and name.
Реєструє тестову функцію з вказаним набором і ім'ям.
Регистрирует тестовую функцию с указанным набором и именем.

#### runAllTests
# запуск усіх тестів
# запуск всех тестов
```cpp
bool runAllTests();
```
Runs all registered tests and returns true if all tests pass.
Запускає всі зареєстровані тести та повертає true, якщо всі тести пройдено.
Запускает все зарегистрированные тесты и возвращает true, если все тесты пройдены.

#### generateReport
# генерація звіту
# генерация отчета
```cpp
std::string generateReport() const;
```
Generates a test report in the configured format.
Генерує звіт про тестування у налаштованому форматі.
Генерирует отчет о тестировании в настроенном формате.

## Assertion Macros
# Макроси тверджень
# Макросы утверждений

- `ASSERT_TRUE(condition)` - Asserts that the condition is true
- `ASSERT_TRUE(condition)` - Переконується, що умова істинна
- `ASSERT_TRUE(condition)` - Убеждается, что условие истинно

- `ASSERT_FALSE(condition)` - Asserts that the condition is false
- `ASSERT_FALSE(condition)` - Переконується, що умова хибна
- `ASSERT_FALSE(condition)` - Убеждается, что условие ложно

- `ASSERT_EQUAL(expected, actual)` - Asserts that expected equals actual
- `ASSERT_EQUAL(expected, actual)` - Переконується, що очікуване дорівнює фактичному
- `ASSERT_EQUAL(expected, actual)` - Убеждается, что ожидаемое равно фактическому

- `ASSERT_NOT_EQUAL(expected, actual)` - Asserts that expected does not equal actual
- `ASSERT_NOT_EQUAL(expected, actual)` - Переконується, що очікуване не дорівнює фактичному
- `ASSERT_NOT_EQUAL(expected, actual)` - Убеждается, что ожидаемое не равно фактическому

- `ASSERT_THROW(expression, exceptionType)` - Asserts that the expression throws the specified exception type
- `ASSERT_THROW(expression, exceptionType)` - Переконується, що вираз видає вказану тип винятку
- `ASSERT_THROW(expression, exceptionType)` - Убеждается, что выражение выдает указанный тип исключения

- `ASSERT_NO_THROW(expression)` - Asserts that the expression does not throw any exception
- `ASSERT_NO_THROW(expression)` - Переконується, що вираз не видає жодного винятку
- `ASSERT_NO_THROW(expression)` - Убеждается, что выражение не выдает никакого исключения

## Configuration
# Конфігурація
# Конфигурация

The TestingConfig structure allows you to configure various aspects of the testing framework:

Структура TestingConfig дозволяє налаштувати різні аспекти тестувального фреймворку:

Структура TestingConfig позволяет настроить различные аспекты тестового фреймворка:

```cpp
struct TestingConfig {
    bool enableVerboseOutput;     // Enable verbose output
                                  // Увімкнути докладний вивід
                                  // Включить подробный вывод
    
    bool enableColorOutput;       // Enable color output
                                  // Увімкнути кольоровий вивід
                                  // Включить цветной вывод
    
    bool stopOnFailure;           // Stop execution on first failure
                                  // Зупинити виконання при першій помилці
                                  // Остановить выполнение при первой ошибке
    
    bool runSkippedTests;         // Run skipped tests
                                  // Запустити пропущені тести
                                  // Запустить пропущенные тесты
    
    std::string outputFormat;     // Output format ("text", "xml", "json")
                                  // Формат виводу ("text", "xml", "json")
                                  // Формат вывода ("text", "xml", "json")
    
    std::string outputPath;       // Output path for test results
                                  // Шлях виводу для результатів тестів
                                  // Путь вывода для результатов тестов
    
    std::vector<std::string> includeSuites;  // Suites to include
                                             // Набори для включення
                                             // Наборы для включения
    
    std::vector<std::string> excludeSuites;  // Suites to exclude
                                             // Набори для виключення
                                             // Наборы для исключения
    
    uint32_t maxConcurrency;      // Maximum concurrency level
                                  // Максимальний рівень одночасності
                                  // Максимальный уровень параллелизма
};
```

## Test Types
# Типи тестів
# Типы тестов

The framework supports the following test types:

Фреймворк підтримує наступні типи тестів:

Фреймворк поддерживает следующие типы тестов:

- `UNIT` - Unit tests that test individual components
- `UNIT` - Модульні тести, які тестують окремі компоненти
- `UNIT` - Модульные тесты, которые тестируют отдельные компоненты

- `INTEGRATION` - Integration tests that test component interactions
- `INTEGRATION` - Інтеграційні тести, які тестують взаємодії компонентів
- `INTEGRATION` - Интеграционные тесты, которые тестируют взаимодействия компонентов

- `SYSTEM` - System tests that test the entire system
- `SYSTEM` - Системні тести, які тестують всю систему
- `SYSTEM` - Системные тесты, которые тестируют всю систему

- `PERFORMANCE` - Performance tests that measure execution speed
- `PERFORMANCE` - Тести продуктивності, які вимірюють швидкість виконання
- `PERFORMANCE` - Тесты производительности, которые измеряют скорость выполнения

- `STRESS` - Stress tests that test system under heavy load
- `STRESS` - Стрес-тести, які тестують систему під великим навантаженням
- `STRESS` - Стресс-тесты, которые тестируют систему под большой нагрузкой

- `REGRESSION` - Regression tests that ensure no new bugs are introduced
- `REGRESSION` - Регресійні тести, які забезпечують відсутність нових помилок
- `REGRESSION` - Регрессионные тесты, которые обеспечивают отсутствие новых ошибок