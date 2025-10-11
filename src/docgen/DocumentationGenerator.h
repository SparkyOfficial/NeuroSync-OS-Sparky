#ifndef DOCUMENTATION_GENERATOR_H
#define DOCUMENTATION_GENERATOR_H

/*
 * DocumentationGenerator.h
 * Генератор документації для NeuroSync OS Sparky
 * Documentation generator for NeuroSync OS Sparky
 * Генератор документации для NeuroSync OS Sparky
 */

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <mutex>

namespace NeuroSync {

    // Типи документації
    // Documentation types
    // Типы документации
    enum class DocumentationType {
        API,            // API документація
        // API documentation
        // Документация API
        
        USER_GUIDE,     // Посібник користувача
        // User guide
        // Руководство пользователя
        
        TECHNICAL,      // Технічна документація
        // Technical documentation
        // Техническая документация
        
        TUTORIAL        // Посібник з навчання
        // Tutorial
        // Учебное пособие
    };

    // Структура інформації про клас
    // Class information structure
    // Структура информации о классе
    struct ClassInfo {
        std::string name;
        std::string description;
        std::string filePath;
        std::vector<std::string> methods;
        std::vector<std::string> properties;
        std::vector<std::string> inheritance;
        
        ClassInfo() = default;
        ClassInfo(const std::string& className) : name(className) {}
    };

    // Структура інформації про функцію
    // Function information structure
    // Структура информации о функции
    struct FunctionInfo {
        std::string name;
        std::string description;
        std::string returnType;
        std::vector<std::pair<std::string, std::string>> parameters; // type, name
        std::string filePath;
        std::string className; // empty if not a method
        
        FunctionInfo() = default;
        FunctionInfo(const std::string& funcName) : name(funcName) {}
    };

    // Структура інформації про змінну
    // Variable information structure
    // Структура информации о переменной
    struct VariableInfo {
        std::string name;
        std::string description;
        std::string type;
        std::string filePath;
        std::string className; // empty if not a member variable
        
        VariableInfo() = default;
        VariableInfo(const std::string& varName) : name(varName) {}
    };

    // Конфігурація генератора документації
    // Documentation generator configuration
    // Конфигурация генератора документации
    struct DocumentationConfig {
        std::string sourceDirectory;       // Каталог джерел
        // Source directory
        // Каталог исходников
        
        std::string outputDirectory;       // Каталог виводу
        // Output directory
        // Каталог вывода
        
        std::vector<std::string> fileExtensions; // Розширення файлів для обробки
        // File extensions to process
        // Расширения файлов для обработки
        
        bool includePrivate;               // Включати приватні члени
        // Include private members
        // Включать приватные члены
        
        bool includeInternal;              // Включати внутрішні елементи
        // Include internal elements
        // Включать внутренние элементы
        
        std::string outputFormat;          // Формат виводу ("html", "md", "xml")
        // Output format ("html", "md", "xml")
        // Формат вывода ("html", "md", "xml")
        
        std::string projectName;           // Назва проекту
        // Project name
        // Название проекта
        
        std::string projectVersion;        // Версія проекту
        // Project version
        // Версия проекта
        
        DocumentationConfig() : includePrivate(false),
                               includeInternal(false),
                               outputFormat("html"),
                               projectName("NeuroSync OS Sparky"),
                               projectVersion("1.0.0") {
            fileExtensions = {".h", ".hpp", ".cpp", ".cxx"};
        }
    };

    // Інтерфейс генератора документації
    // Documentation generator interface
    // Интерфейс генератора документации
    class DocumentationGenerator {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        DocumentationGenerator();
        
        // Деструктор
        // Destructor
        // Деструктор
        virtual ~DocumentationGenerator();
        
        // Ініціалізація генератора документації
        // Initialize documentation generator
        // Инициализация генератора документации
        virtual bool initialize(const DocumentationConfig& config);
        
        // Аналіз джерельних файлів
        // Analyze source files
        // Анализ исходных файлов
        virtual bool analyzeSourceFiles();
        
        // Генерація документації
        // Generate documentation
        // Генерация документации
        virtual bool generateDocumentation();
        
        // Експорт документації
        // Export documentation
        // Экспорт документации
        virtual bool exportDocumentation(const std::string& format, 
                                       const std::string& outputPath);
        
        // Отримання конфігурації
        // Get configuration
        // Получение конфигурации
        DocumentationConfig getConfiguration() const;
        
        // Встановлення конфігурації
        // Set configuration
        // Установка конфигурации
        void setConfiguration(const DocumentationConfig& config);
        
        // Отримання інформації про класи
        // Get class information
        // Получение информации о классах
        std::vector<ClassInfo> getClasses() const;
        
        // Отримання інформації про функції
        // Get function information
        // Получение информации о функциях
        std::vector<FunctionInfo> getFunctions() const;
        
        // Отримання інформації про змінні
        // Get variable information
        // Получение информации о переменных
        std::vector<VariableInfo> getVariables() const;
        
    protected:
        DocumentationConfig config;
        std::vector<ClassInfo> classes;
        std::vector<FunctionInfo> functions;
        std::vector<VariableInfo> variables;
        mutable std::mutex docGenMutex;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        virtual bool parseSourceFile(const std::string& filePath);
        virtual bool parseHeaderFile(const std::string& filePath);
        virtual bool parseClassDeclaration(const std::string& line, 
                                         const std::string& filePath);
        virtual bool parseFunctionDeclaration(const std::string& line, 
                                            const std::string& filePath,
                                            const std::string& className = "");
        virtual bool parseVariableDeclaration(const std::string& line, 
                                            const std::string& filePath,
                                            const std::string& className = "");
        virtual std::string extractComment(const std::string& codeLine);
        virtual std::vector<std::string> getFilesInDirectory(const std::string& directory);
        virtual std::string generateHtmlDocumentation() const;
        virtual std::string generateMarkdownDocumentation() const;
        virtual std::string generateXmlDocumentation() const;
        virtual std::string generateHtmlIndex() const;
        virtual std::string generateHtmlClassPage(const ClassInfo& classInfo) const;
        virtual std::string generateHtmlFunctionPage(const FunctionInfo& functionInfo) const;
        virtual std::string sanitizeHtml(const std::string& text) const;
    };

    // Глобальний генератор документації
    // Global documentation generator
    // Глобальный генератор документации
    extern std::unique_ptr<DocumentationGenerator> gDocGenerator;

} // namespace NeuroSync

#endif // DOCUMENTATION_GENERATOR_H