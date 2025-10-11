# Documentation Generator
# Генератор документації
# Генератор документации

## Overview
# Огляд
# Обзор

The Documentation Generator is a comprehensive tool designed specifically for the NeuroSync OS Sparky microkernel. It provides automated generation of API documentation, user guides, technical documentation, and tutorials from source code comments and structure.

Генератор документації - це комплексний інструмент, розроблений спеціально для мікроядра NeuroSync OS Sparky. Він забезпечує автоматичне створення API документації, посібників користувача, технічної документації та навчальних матеріалів з коментарів до вихідного коду та його структури.

Генератор документации - это комплексный инструмент, разработанный специально для микроядра NeuroSync OS Sparky. Он обеспечивает автоматическую генерацию API документации, руководств пользователя, технической документации и учебных материалов из комментариев исходного кода и его структуры.

## Features
# Особливості
# Особенности

- Multiple documentation types support (API, User Guide, Technical, Tutorial)
- Підтримка кількох типів документації (API, Посібник користувача, Технічна, Навчальна)
- Поддержка нескольких типов документации (API, Руководство пользователя, Техническая, Учебная)

- Configurable documentation generation (source directory, output directory, format)
- Налаштовуване створення документації (каталог джерел, каталог виводу, формат)
- Настраиваемая генерация документации (каталог исходников, каталог вывода, формат)

- Multiple output formats (HTML, Markdown, XML)
- Кілька форматів виводу (HTML, Markdown, XML)
- Несколько форматов вывода (HTML, Markdown, XML)

- Export/import documentation
- Експорт/імпорт документації
- Экспорт/импорт документации

- Source code analysis for classes, functions, and variables
- Аналіз вихідного коду для класів, функцій та змінних
- Анализ исходного кода для классов, функций и переменных

## Usage
# Використання
# Использование

### Basic Example
# Базовий приклад
# Базовый пример

```cpp
#include "DocumentationGenerator.h"

using namespace NeuroSync;

// Initialize global documentation generator
std::unique_ptr<DocumentationGenerator> NeuroSync::gDocGenerator = std::make_unique<DocumentationGenerator>();

int main() {
    // Configure documentation generator
    DocumentationConfig config;
    config.sourceDirectory = "./src";
    config.outputDirectory = "./docs/generated";
    config.outputFormat = "html";
    config.projectName = "NeuroSync OS Sparky";
    config.projectVersion = "1.0.0";
    
    gDocGenerator->initialize(config);
    
    // Analyze source files
    gDocGenerator->analyzeSourceFiles();
    
    // Generate documentation
    gDocGenerator->generateDocumentation();
    
    // Export documentation in different formats
    gDocGenerator->exportDocumentation("md", "./docs/generated/documentation.md");
    gDocGenerator->exportDocumentation("xml", "./docs/generated/documentation.xml");
    
    return 0;
}
```

## API Reference
# Посилання на API
# Ссылка на API

### DocumentationGenerator Class
# Клас DocumentationGenerator
# Класс DocumentationGenerator

#### Constructor
# Конструктор
# Конструктор
```cpp
DocumentationGenerator();
```

#### initialize
# ініціалізація
# инициализация
```cpp
bool initialize(const DocumentationConfig& config);
```
Initializes the documentation generator with the provided configuration.
Ініціалізує генератор документації із наданою конфігурацією.
Инициализирует генератор документации с предоставленной конфигурацией.

#### analyzeSourceFiles
# аналіз джерельних файлів
# анализ исходных файлов
```cpp
bool analyzeSourceFiles();
```
Analyzes source files in the configured source directory.
Аналізує вихідні файли в налаштованому каталозі джерел.
Анализирует исходные файлы в настроенном каталоге исходников.

#### generateDocumentation
# генерація документації
# генерация документации
```cpp
bool generateDocumentation();
```
Generates documentation in the configured format.
Генерує документацію в налаштованому форматі.
Генерирует документацию в настроенном формате.

#### exportDocumentation
# експорт документації
# экспорт документации
```cpp
bool exportDocumentation(const std::string& format, const std::string& outputPath);
```
Exports documentation in the specified format to the given output path.
Експортує документацію в зазначеному форматі до заданого шляху виводу.
Экспортирует документацию в указанном формате по заданному пути вывода.

#### generateHtmlDocumentation
# генерація HTML документації
# генерация HTML документации
```cpp
std::string generateHtmlDocumentation() const;
```
Generates HTML documentation.
Генерує HTML документацію.
Генерирует HTML документацию.

#### generateMarkdownDocumentation
# генерація Markdown документації
# генерация Markdown документации
```cpp
std::string generateMarkdownDocumentation() const;
```
Generates Markdown documentation.
Генерує Markdown документацію.
Генерирует Markdown документацию.

#### generateXmlDocumentation
# генерація XML документації
# генерация XML документации
```cpp
std::string generateXmlDocumentation() const;
```
Generates XML documentation.
Генерує XML документацію.
Генерирует XML документацию.

## Configuration
# Конфігурація
# Конфигурация

The DocumentationConfig structure allows you to configure various aspects of the documentation generator:

Структура DocumentationConfig дозволяє налаштувати різні аспекти генератора документації:

Структура DocumentationConfig позволяет настроить различные аспекты генератора документации:

```cpp
struct DocumentationConfig {
    std::string sourceDirectory;       // Source directory
                                       // Каталог джерел
                                       // Каталог исходников
    
    std::string outputDirectory;       // Output directory
                                       // Каталог виводу
                                       // Каталог вывода
    
    std::vector<std::string> fileExtensions; // File extensions to process
                                            // Розширення файлів для обробки
                                            // Расширения файлов для обработки
    
    bool includePrivate;               // Include private members
                                       // Включати приватні члени
                                       // Включать приватные члены
    
    bool includeInternal;              // Include internal elements
                                       // Включати внутрішні елементи
                                       // Включать внутренние элементы
    
    std::string outputFormat;          // Output format ("html", "md", "xml")
                                       // Формат виводу ("html", "md", "xml")
                                       // Формат вывода ("html", "md", "xml")
    
    std::string projectName;           // Project name
                                       // Назва проекту
                                       // Название проекта
    
    std::string projectVersion;        // Project version
                                       // Версія проекту
                                       // Версия проекта
};
```

## Documentation Types
# Типи документації
# Типы документации

The framework supports the following documentation types:

Фреймворк підтримує наступні типи документації:

Фреймворк поддерживает следующие типы документации:

- `API` - API documentation
- `API` - API документація
- `API` - API документация

- `USER_GUIDE` - User guide
- `USER_GUIDE` - Посібник користувача
- `USER_GUIDE` - Руководство пользователя

- `TECHNICAL` - Technical documentation
- `TECHNICAL` - Технічна документація
- `TECHNICAL` - Техническая документация

- `TUTORIAL` - Tutorial
- `TUTORIAL` - Посібник з навчання
- `TUTORIAL` - Учебное пособие

## Supported Output Formats
# Підтримувані формати виводу
# Поддерживаемые форматы вывода

The Documentation Generator supports the following output formats:

Генератор документації підтримує наступні формати виводу:

Генератор документации поддерживает следующие форматы вывода:

- `HTML` - HyperText Markup Language
- `HTML` - Мова гіпертекстової розмітки
- `HTML` - Язык гипертекстовой разметки

- `Markdown` - Markdown format
- `Markdown` - Формат Markdown
- `Markdown` - Формат Markdown

- `XML` - eXtensible Markup Language
- `XML` - Розширювана мова розмітки
- `XML` - Расширяемый язык разметки