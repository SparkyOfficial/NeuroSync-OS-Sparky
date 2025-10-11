/*
 * DocumentationGenerator.cpp
 * Реалізація генератора документації для NeuroSync OS Sparky
 * Implementation of documentation generator for NeuroSync OS Sparky
 * Реализация генератора документации для NeuroSync OS Sparky
 */

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "DocumentationGenerator.h"
#include <experimental/filesystem>
#include <fstream>
#include <algorithm>
#include <cctype>

namespace NeuroSync {

    namespace fs = std::experimental::filesystem;

    // Глобальний генератор документації
    // Global documentation generator
    // Глобальный генератор документации
    std::unique_ptr<DocumentationGenerator> gDocGenerator = std::make_unique<DocumentationGenerator>();

    // Конструктор
    // Constructor
    // Конструктор
    DocumentationGenerator::DocumentationGenerator() {
        // Ініціалізація за замовчуванням
        // Default initialization
        // Инициализация по умолчанию
    }

    // Деструктор
    // Destructor
    // Деструктор
    DocumentationGenerator::~DocumentationGenerator() {
        // Очищення ресурсів
        // Resource cleanup
        // Очистка ресурсов
    }

    // Ініціалізація генератора документації
    // Initialize documentation generator
    // Инициализация генератора документации
    bool DocumentationGenerator::initialize(const DocumentationConfig& config) {
        std::lock_guard<std::mutex> lock(docGenMutex);
        this->config = config;
        return true;
    }

    // Аналіз джерельних файлів
    // Analyze source files
    // Анализ исходных файлов
    bool DocumentationGenerator::analyzeSourceFiles() {
        std::lock_guard<std::mutex> lock(docGenMutex);
        
        if (config.sourceDirectory.empty()) {
            std::cerr << "Source directory is not set\n";
            return false;
        }
        
        try {
            // Отримання списку файлів
            // Get list of files
            // Получение списка файлов
            std::vector<std::string> files = getFilesInDirectory(config.sourceDirectory);
            
            // Аналіз кожного файлу
            // Analyze each file
            // Анализ каждого файла
            for (const auto& file : files) {
                if (!parseSourceFile(file)) {
                    std::cerr << "Failed to parse file: " << file << std::endl;
                }
            }
            
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error analyzing source files: " << e.what() << std::endl;
            return false;
        }
    }

    // Генерація документації
    // Generate documentation
    // Генерация документации
    bool DocumentationGenerator::generateDocumentation() {
        std::lock_guard<std::mutex> lock(docGenMutex);
        
        if (classes.empty() && functions.empty() && variables.empty()) {
            std::cerr << "No elements to document. Run analyzeSourceFiles() first.\n";
            return false;
        }
        
        try {
            // Створення каталогу виводу
            // Create output directory
            // Создание каталога вывода
            fs::create_directories(config.outputDirectory);
            
            // Генерація документації в залежності від формату
            // Generate documentation based on format
            // Генерация документации в зависимости от формата
            std::string documentation;
            if (config.outputFormat == "md") {
                documentation = generateMarkdownDocumentation();
            } else if (config.outputFormat == "xml") {
                documentation = generateXmlDocumentation();
            } else {
                documentation = generateHtmlDocumentation();
            }
            
            // Збереження головної сторінки документації
            // Save main documentation page
            // Сохранение главной страницы документации
            std::string outputPath = config.outputDirectory + "/index." + 
                (config.outputFormat == "md" ? "md" : 
                 config.outputFormat == "xml" ? "xml" : "html");
            
            std::ofstream file(outputPath);
            if (!file.is_open()) {
                std::cerr << "Failed to create output file: " << outputPath << std::endl;
                return false;
            }
            
            file << documentation;
            file.close();
            
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error generating documentation: " << e.what() << std::endl;
            return false;
        }
    }

    // Експорт документації
    // Export documentation
    // Экспорт документации
    bool DocumentationGenerator::exportDocumentation(const std::string& format, 
                                                   const std::string& outputPath) {
        // Note: We don't lock the mutex here because generateDocumentation will lock it
        // This avoids a deadlock situation
        
        DocumentationConfig originalConfig = config;
        config.outputFormat = format;
        std::string originalOutputDir = config.outputDirectory;
        
        // Extract directory path from file path
        fs::path outputPathObj(outputPath);
        config.outputDirectory = outputPathObj.parent_path().string();
        
        bool result = generateDocumentation();
        
        // Відновлення оригінальної конфігурації
        // Restore original configuration
        // Восстановление оригинальной конфигурации
        config = originalConfig;
        
        return result;
    }

    // Отримання конфігурації
    // Get configuration
    // Получение конфигурации
    DocumentationConfig DocumentationGenerator::getConfiguration() const {
        std::lock_guard<std::mutex> lock(docGenMutex);
        return config;
    }

    // Встановлення конфігурації
    // Set configuration
    // Установка конфигурации
    void DocumentationGenerator::setConfiguration(const DocumentationConfig& config) {
        std::lock_guard<std::mutex> lock(docGenMutex);
        this->config = config;
    }

    // Отримання інформації про класи
    // Get class information
    // Получение информации о классах
    std::vector<ClassInfo> DocumentationGenerator::getClasses() const {
        std::lock_guard<std::mutex> lock(docGenMutex);
        return classes;
    }

    // Отримання інформації про функції
    // Get function information
    // Получение информации о функциях
    std::vector<FunctionInfo> DocumentationGenerator::getFunctions() const {
        std::lock_guard<std::mutex> lock(docGenMutex);
        return functions;
    }

    // Отримання інформації про змінні
    // Get variable information
    // Получение информации о переменных
    std::vector<VariableInfo> DocumentationGenerator::getVariables() const {
        std::lock_guard<std::mutex> lock(docGenMutex);
        return variables;
    }

    // Аналіз джерельного файлу
    // Parse source file
    // Анализ исходного файла
    bool DocumentationGenerator::parseSourceFile(const std::string& filePath) {
        // Перевірка розширення файлу
        // Check file extension
        // Проверка расширения файла
        std::string extension = fs::path(filePath).extension().string();
        if (std::find(config.fileExtensions.begin(), config.fileExtensions.end(), extension) == 
            config.fileExtensions.end()) {
            return true; // Не обробляти цей файл
            // Don't process this file
            // Не обрабатывать этот файл
        }
        
        std::ifstream file(filePath);
        if (!file.is_open()) {
            return false;
        }
        
        std::string line;
        std::string currentClass;
        
        // Якщо це заголовний файл, аналізуємо його
        // If this is a header file, parse it
        // Если это заголовочный файл, анализируем его
        if (extension == ".h" || extension == ".hpp") {
            return parseHeaderFile(filePath);
        }
        
        // Для файлів реалізації просто зберігаємо інформацію про наявність файлу
        // For implementation files, just store information about the file's existence
        // Для файлов реализации просто сохраняем информацию о наличии файла
        while (std::getline(file, line)) {
            // Тут можна додати аналіз реалізаційних файлів
            // Here we could add analysis of implementation files
            // Здесь можно добавить анализ файлов реализации
        }
        
        return true;
    }

    // Аналіз заголовного файлу
    // Parse header file
    // Анализ заголовочного файла
    bool DocumentationGenerator::parseHeaderFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            return false;
        }
        
        std::string line;
        std::string currentClass;
        
        while (std::getline(file, line)) {
            // Видалення пробілів на початку та в кінці
            // Remove leading and trailing whitespace
            // Удаление пробелов в начале и в конце
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);
            
            // Пропуск порожніх рядків та коментарів
            // Skip empty lines and comments
            // Пропуск пустых строк и комментариев
            if (line.empty() || line[0] == '/' || line[0] == '*') {
                continue;
            }
            
            // Пошук оголошення класу
            // Search for class declaration
            // Поиск объявления класса
            if (line.find("class ") != std::string::npos && 
                line.find(";") == std::string::npos) {
                if (parseClassDeclaration(line, filePath)) {
                    // Витягування назви класу
                    // Extract class name
                    // Извлечение имени класса
                    size_t classPos = line.find("class ");
                    size_t nameStart = classPos + 6;
                    size_t nameEnd = line.find_first_of(" {:;", nameStart);
                    if (nameEnd != std::string::npos) {
                        currentClass = line.substr(nameStart, nameEnd - nameStart);
                        // Видалення пробілів
                        // Remove whitespace
                        // Удаление пробелов
                        currentClass.erase(0, currentClass.find_first_not_of(" \t"));
                        currentClass.erase(currentClass.find_last_not_of(" \t") + 1);
                    }
                }
            }
            // Пошук оголошення функції
            // Search for function declaration
            // Поиск объявления функции
            else if (line.find("(") != std::string::npos && 
                     line.find(")") != std::string::npos &&
                     line.find(";") != std::string::npos) {
                parseFunctionDeclaration(line, filePath, currentClass);
            }
            // Пошук оголошення змінної
            // Search for variable declaration
            // Поиск объявления переменной
            else if (line.find(";") != std::string::npos && 
                     line.find("(") == std::string::npos &&
                     line.find("class ") == std::string::npos &&
                     line.find("struct ") == std::string::npos &&
                     line.find("enum ") == std::string::npos) {
                parseVariableDeclaration(line, filePath, currentClass);
            }
        }
        
        return true;
    }

    // Аналіз оголошення класу
    // Parse class declaration
    // Анализ объявления класса
    bool DocumentationGenerator::parseClassDeclaration(const std::string& line, 
                                                     const std::string& filePath) {
        ClassInfo classInfo;
        classInfo.filePath = filePath;
        
        // Витягування назви класу
        // Extract class name
        // Извлечение имени класса
        size_t classPos = line.find("class ");
        size_t nameStart = classPos + 6;
        size_t nameEnd = line.find_first_of(" {:;", nameStart);
        if (nameEnd != std::string::npos) {
            classInfo.name = line.substr(nameStart, nameEnd - nameStart);
            // Видалення пробілів
            // Remove whitespace
            // Удаление пробелов
            classInfo.name.erase(0, classInfo.name.find_first_not_of(" \t"));
            classInfo.name.erase(classInfo.name.find_last_not_of(" \t") + 1);
            
            classes.push_back(classInfo);
            return true;
        }
        
        return false;
    }

    // Аналіз оголошення функції
    // Parse function declaration
    // Анализ объявления функции
    bool DocumentationGenerator::parseFunctionDeclaration(const std::string& line, 
                                                        const std::string& filePath,
                                                        const std::string& className) {
        FunctionInfo functionInfo;
        functionInfo.filePath = filePath;
        functionInfo.className = className;
        
        // Витягування назви функції
        // Extract function name
        // Извлечение имени функции
        size_t nameEnd = line.find("(");
        if (nameEnd != std::string::npos) {
            // Пошук початку назви функції
            // Find the beginning of the function name
            // Поиск начала имени функции
            size_t nameStart = line.find_last_of(" \t", nameEnd);
            if (nameStart != std::string::npos) {
                functionInfo.name = line.substr(nameStart + 1, nameEnd - nameStart - 1);
                // Видалення пробілів
                // Remove whitespace
                // Удаление пробелов
                functionInfo.name.erase(0, functionInfo.name.find_first_not_of(" \t"));
                functionInfo.name.erase(functionInfo.name.find_last_not_of(" \t") + 1);
                
                functions.push_back(functionInfo);
                return true;
            }
        }
        
        return false;
    }

    // Аналіз оголошення змінної
    // Parse variable declaration
    // Анализ объявления переменной
    bool DocumentationGenerator::parseVariableDeclaration(const std::string& line, 
                                                        const std::string& filePath,
                                                        const std::string& className) {
        VariableInfo variableInfo;
        variableInfo.filePath = filePath;
        variableInfo.className = className;
        
        // Витягування назви змінної
        // Extract variable name
        // Извлечение имени переменной
        size_t nameEnd = line.find(";");
        if (nameEnd != std::string::npos) {
            // Пошук початку назви змінної
            // Find the beginning of the variable name
            // Поиск начала имени переменной
            size_t nameStart = line.find_last_of(" \t", nameEnd);
            if (nameStart != std::string::npos) {
                variableInfo.name = line.substr(nameStart + 1, nameEnd - nameStart - 1);
                // Видалення пробілів
                // Remove whitespace
                // Удаление пробелов
                variableInfo.name.erase(0, variableInfo.name.find_first_not_of(" \t"));
                variableInfo.name.erase(variableInfo.name.find_last_not_of(" \t") + 1);
                
                variables.push_back(variableInfo);
                return true;
            }
        }
        
        return false;
    }

    // Витягування коментаря
    // Extract comment
    // Извлечение комментария
    std::string DocumentationGenerator::extractComment(const std::string& codeLine) {
        // Пошук коментаря у форматі // або /* */
        // Search for comment in // or /* */ format
        // Поиск комментария в формате // или /* */
        size_t commentPos = codeLine.find("//");
        if (commentPos != std::string::npos) {
            return codeLine.substr(commentPos + 2);
        }
        
        // Пошук багаторядкового коментаря
        // Search for multi-line comment
        // Поиск многострочного комментария
        commentPos = codeLine.find("/*");
        if (commentPos != std::string::npos) {
            size_t endPos = codeLine.find("*/", commentPos + 2);
            if (endPos != std::string::npos) {
                return codeLine.substr(commentPos + 2, endPos - commentPos - 2);
            }
        }
        
        return "";
    }

    // Отримання файлів у каталозі
    // Get files in directory
    // Получение файлов в каталоге
    std::vector<std::string> DocumentationGenerator::getFilesInDirectory(const std::string& directory) {
        std::vector<std::string> files;
        
        try {
            for (const auto& entry : fs::recursive_directory_iterator(directory)) {
                if (fs::is_regular_file(entry.status())) {
                    files.push_back(entry.path().string());
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error reading directory: " << e.what() << std::endl;
        }
        
        return files;
    }

    // Генерація HTML документації
    // Generate HTML documentation
    // Генерация HTML документации
    std::string DocumentationGenerator::generateHtmlDocumentation() const {
        std::ostringstream oss;
        
        oss << "<!DOCTYPE html>\n";
        oss << "<html lang=\"en\">\n";
        oss << "<head>\n";
        oss << "    <meta charset=\"UTF-8\">\n";
        oss << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
        oss << "    <title>" << config.projectName << " API Documentation</title>\n";
        oss << "    <style>\n";
        oss << "        body { font-family: Arial, sans-serif; margin: 20px; }\n";
        oss << "        h1, h2, h3 { color: #333; }\n";
        oss << "        .class, .function, .variable { margin-bottom: 20px; padding: 10px; border: 1px solid #ddd; }\n";
        oss << "        .class-name { font-size: 1.5em; font-weight: bold; color: #007acc; }\n";
        oss << "        .function-name { font-size: 1.2em; font-weight: bold; color: #007acc; }\n";
        oss << "        .variable-name { font-size: 1.1em; font-weight: bold; color: #007acc; }\n";
        oss << "        .description { margin: 5px 0; }\n";
        oss << "        .file-path { color: #666; font-size: 0.9em; }\n";
        oss << "    </style>\n";
        oss << "</head>\n";
        oss << "<body>\n";
        oss << "    <h1>" << config.projectName << " API Documentation</h1>\n";
        oss << "    <p>Version: " << config.projectVersion << "</p>\n";
        oss << "    \n";
        oss << "    <h2>Classes</h2>\n";
        
        for (const auto& classInfo : classes) {
            oss << "    <div class=\"class\">\n";
            oss << "        <div class=\"class-name\">" << sanitizeHtml(classInfo.name) << "</div>\n";
            oss << "        <div class=\"file-path\">File: " << sanitizeHtml(classInfo.filePath) << "</div>\n";
            oss << "        <div class=\"description\">" << sanitizeHtml(classInfo.description) << "</div>\n";
            oss << "    </div>\n";
        }
        
        oss << "    \n";
        oss << "    <h2>Functions</h2>\n";
        
        for (const auto& functionInfo : functions) {
            oss << "    <div class=\"function\">\n";
            oss << "        <div class=\"function-name\">" << sanitizeHtml(functionInfo.name) << "</div>\n";
            if (!functionInfo.className.empty()) {
                oss << "        <div>Class: " << sanitizeHtml(functionInfo.className) << "</div>\n";
            }
            oss << "        <div class=\"file-path\">File: " << sanitizeHtml(functionInfo.filePath) << "</div>\n";
            oss << "        <div class=\"description\">" << sanitizeHtml(functionInfo.description) << "</div>\n";
            oss << "    </div>\n";
        }
        
        oss << "    \n";
        oss << "    <h2>Variables</h2>\n";
        
        for (const auto& variableInfo : variables) {
            oss << "    <div class=\"variable\">\n";
            oss << "        <div class=\"variable-name\">" << sanitizeHtml(variableInfo.name) << "</div>\n";
            if (!variableInfo.className.empty()) {
                oss << "        <div>Class: " << sanitizeHtml(variableInfo.className) << "</div>\n";
            }
            oss << "        <div class=\"file-path\">File: " << sanitizeHtml(variableInfo.filePath) << "</div>\n";
            oss << "        <div class=\"description\">" << sanitizeHtml(variableInfo.description) << "</div>\n";
            oss << "    </div>\n";
        }
        
        oss << "</body>\n";
        oss << "</html>\n";
        
        return oss.str();
    }

    // Генерація Markdown документації
    // Generate Markdown documentation
    // Генерация Markdown документации
    std::string DocumentationGenerator::generateMarkdownDocumentation() const {
        std::ostringstream oss;
        
        oss << "# " << config.projectName << " API Documentation\n\n";
        oss << "**Version:** " << config.projectVersion << "\n\n";
        
        oss << "## Classes\n\n";
        
        for (const auto& classInfo : classes) {
            oss << "### " << classInfo.name << "\n\n";
            oss << "**File:** " << classInfo.filePath << "\n\n";
            oss << "**Description:** " << classInfo.description << "\n\n";
        }
        
        oss << "## Functions\n\n";
        
        for (const auto& functionInfo : functions) {
            oss << "### " << functionInfo.name << "\n\n";
            if (!functionInfo.className.empty()) {
                oss << "**Class:** " << functionInfo.className << "\n\n";
            }
            oss << "**File:** " << functionInfo.filePath << "\n\n";
            oss << "**Description:** " << functionInfo.description << "\n\n";
        }
        
        oss << "## Variables\n\n";
        
        for (const auto& variableInfo : variables) {
            oss << "### " << variableInfo.name << "\n\n";
            if (!variableInfo.className.empty()) {
                oss << "**Class:** " << variableInfo.className << "\n\n";
            }
            oss << "**File:** " << variableInfo.filePath << "\n\n";
            oss << "**Description:** " << variableInfo.description << "\n\n";
        }
        
        return oss.str();
    }

    // Генерація XML документації
    // Generate XML documentation
    // Генерация XML документации
    std::string DocumentationGenerator::generateXmlDocumentation() const {
        std::ostringstream oss;
        
        oss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        oss << "<documentation project=\"" << config.projectName << "\" version=\"" << config.projectVersion << "\">\n";
        
        oss << "    <classes>\n";
        for (const auto& classInfo : classes) {
            oss << "        <class>\n";
            oss << "            <name>" << classInfo.name << "</name>\n";
            oss << "            <file>" << classInfo.filePath << "</file>\n";
            oss << "            <description>" << classInfo.description << "</description>\n";
            oss << "        </class>\n";
        }
        oss << "    </classes>\n";
        
        oss << "    <functions>\n";
        for (const auto& functionInfo : functions) {
            oss << "        <function>\n";
            oss << "            <name>" << functionInfo.name << "</name>\n";
            if (!functionInfo.className.empty()) {
                oss << "            <class>" << functionInfo.className << "</class>\n";
            }
            oss << "            <file>" << functionInfo.filePath << "</file>\n";
            oss << "            <description>" << functionInfo.description << "</description>\n";
            oss << "        </function>\n";
        }
        oss << "    </functions>\n";
        
        oss << "    <variables>\n";
        for (const auto& variableInfo : variables) {
            oss << "        <variable>\n";
            oss << "            <name>" << variableInfo.name << "</name>\n";
            if (!variableInfo.className.empty()) {
                oss << "            <class>" << variableInfo.className << "</class>\n";
            }
            oss << "            <file>" << variableInfo.filePath << "</file>\n";
            oss << "            <description>" << variableInfo.description << "</description>\n";
            oss << "        </variable>\n";
        }
        oss << "    </variables>\n";
        
        oss << "</documentation>\n";
        
        return oss.str();
    }

    // Генерація HTML індексу
    // Generate HTML index
    // Генерация HTML индекса
    std::string DocumentationGenerator::generateHtmlIndex() const {
        return "<html><head><title>Documentation Index</title></head><body><h1>Documentation Index</h1></body></html>";
    }

    // Генерація HTML сторінки класу
    // Generate HTML class page
    // Генерация HTML страницы класса
    std::string DocumentationGenerator::generateHtmlClassPage(const ClassInfo& classInfo) const {
        return "<html><head><title>Class: " + classInfo.name + "</title></head><body><h1>Class: " + classInfo.name + "</h1></body></html>";
    }

    // Генерація HTML сторінки функції
    // Generate HTML function page
    // Генерация HTML страницы функции
    std::string DocumentationGenerator::generateHtmlFunctionPage(const FunctionInfo& functionInfo) const {
        return "<html><head><title>Function: " + functionInfo.name + "</title></head><body><h1>Function: " + functionInfo.name + "</h1></body></html>";
    }

    // Санітизація HTML
    // Sanitize HTML
    // Санитизация HTML
    std::string DocumentationGenerator::sanitizeHtml(const std::string& text) const {
        std::string result = text;
        // Simple HTML escaping
        size_t pos = 0;
        while ((pos = result.find("&", pos)) != std::string::npos) {
            result.replace(pos, 1, "&amp;");
            pos += 5;
        }
        pos = 0;
        while ((pos = result.find("<", pos)) != std::string::npos) {
            result.replace(pos, 1, "&lt;");
            pos += 4;
        }
        pos = 0;
        while ((pos = result.find(">", pos)) != std::string::npos) {
            result.replace(pos, 1, "&gt;");
            pos += 4;
        }
        pos = 0;
        while ((pos = result.find("\"", pos)) != std::string::npos) {
            result.replace(pos, 1, "&quot;");
            pos += 6;
        }
        return result;
    }

} // namespace NeuroSync
