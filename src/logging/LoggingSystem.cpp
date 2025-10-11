#include "LoggingSystem.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace NeuroSync {
namespace Logging {

    // Глобальна система логування
    // Global logging system
    // Глобальная система логирования
    LoggingSystem gLogger;

    // ConsoleLogOutput implementation
    ConsoleLogOutput::ConsoleLogOutput() : initialized(false) {
        // Конструктор виводу логів у консоль
        // Console log output constructor
        // Конструктор вывода логов в консоль
    }

    ConsoleLogOutput::~ConsoleLogOutput() {
        // Деструктор виводу логів у консоль
        // Console log output destructor
        // Деструктор вывода логов в консоль
        if (initialized) {
            close();
        }
    }

    void ConsoleLogOutput::writeLog(const LogEntry& entry) {
        // Запис логу у консоль
        // Write log to console
        // Запись лога в консоль
        if (!initialized) {
            return;
        }
        
        std::string formattedMessage = "[" + entry.timestamp + "] [" + 
                                      entry.threadId + "] [" + 
                                      entry.module + "] [" + 
                                      gLogger.getLogLevelName(entry.level) + "] " + 
                                      entry.message;
        
        // Встановлюємо колір залежно від рівня логування
        // Set color based on log level
        // Устанавливаем цвет в зависимости от уровня логирования
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;
        
        // Зберігаємо поточні атрибути консолі
        // Save current console attributes
        // Сохраняем текущие атрибуты консоли
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
        
        // Встановлюємо колір
        // Set color
        // Устанавливаем цвет
        switch (entry.level) {
            case LogLevel::LOG_DEBUG:
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case LogLevel::LOG_INFO:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case LogLevel::LOG_WARNING:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case LogLevel::LOG_ERROR:
            case LogLevel::LOG_CRITICAL:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
        }
        
        std::cout << formattedMessage << std::endl;
        
        // Відновлюємо поточні атрибути консолі
        // Restore current console attributes
        // Восстанавливаем текущие атрибуты консоли
        SetConsoleTextAttribute(hConsole, saved_attributes);
#else
        // Unix/Linux термінали
        // Unix/Linux terminals
        // Unix/Linux терминалы
        switch (entry.level) {
            case LogLevel::LOG_DEBUG:
                std::cout << "\033[36m" << formattedMessage << "\033[0m" << std::endl; // Cyan
                break;
            case LogLevel::LOG_INFO:
                std::cout << "\033[32m" << formattedMessage << "\033[0m" << std::endl; // Green
                break;
            case LogLevel::LOG_WARNING:
                std::cout << "\033[33m" << formattedMessage << "\033[0m" << std::endl; // Yellow
                break;
            case LogLevel::LOG_ERROR:
            case LogLevel::LOG_CRITICAL:
                std::cout << "\033[31m" << formattedMessage << "\033[0m" << std::endl; // Red
                break;
        }
#endif
    }

    LogOutputType ConsoleLogOutput::getType() const {
        // Отримання типу виводу
        // Get output type
        // Получение типа вывода
        return LogOutputType::CONSOLE;
    }

    bool ConsoleLogOutput::initialize() {
        // Ініціалізація виводу логів у консоль
        // Initialize console log output
        // Инициализация вывода логов в консоль
        initialized = true;
        return true;
    }

    void ConsoleLogOutput::close() {
        // Закриття виводу логів у консоль
        // Close console log output
        // Закрытие вывода логов в консоль
        initialized = false;
    }

    // FileLogOutput implementation
    FileLogOutput::FileLogOutput(const std::string& filename) 
        : filename(filename), initialized(false) {
        // Конструктор виводу логів у файл
        // File log output constructor
        // Конструктор вывода логов в файл
    }

    FileLogOutput::~FileLogOutput() {
        // Деструктор виводу логів у файл
        // File log output destructor
        // Деструктор вывода логов в файл
        if (initialized) {
            close();
        }
    }

    void FileLogOutput::writeLog(const LogEntry& entry) {
        // Запис логу у файл
        // Write log to file
        // Запись лога в файл
        if (!initialized || !fileStream.is_open()) {
            return;
        }
        
        std::string formattedMessage = "[" + entry.timestamp + "] [" + 
                                      entry.threadId + "] [" + 
                                      entry.module + "] [" + 
                                      gLogger.getLogLevelName(entry.level) + "] " + 
                                      entry.message + "\n";
        
        fileStream << formattedMessage;
        fileStream.flush();
    }

    LogOutputType FileLogOutput::getType() const {
        // Отримання типу виводу
        // Get output type
        // Получение типа вывода
        return LogOutputType::FILE;
    }

    bool FileLogOutput::initialize() {
        // Ініціалізація виводу логів у файл
        // Initialize file log output
        // Инициализация вывода логов в файл
        if (filename.empty()) {
            return false;
        }
        
        fileStream.open(filename, std::ios::app);
        if (!fileStream.is_open()) {
            return false;
        }
        
        initialized = true;
        return true;
    }

    void FileLogOutput::close() {
        // Закриття виводу логів у файл
        // Close file log output
        // Закрытие вывода логов в файл
        if (fileStream.is_open()) {
            fileStream.close();
        }
        initialized = false;
    }

    void FileLogOutput::setFilename(const std::string& filename) {
        // Встановлення імені файлу
        // Set filename
        // Установка имени файла
        this->filename = filename;
    }

    std::string FileLogOutput::getFilename() const {
        // Отримання імені файлу
        // Get filename
        // Получение имени файла
        return filename;
    }

    // LoggingSystem implementation
    LoggingSystem::LoggingSystem() : currentLevel(LogLevel::LOG_INFO) {
        // Конструктор системи логування
        // Logging system constructor
        // Конструктор системы логирования
    }

    LoggingSystem::~LoggingSystem() {
        // Деструктор системи логування
        // Logging system destructor
        // Деструктор системы логирования
        closeAllOutputs();
    }

    bool LoggingSystem::initialize() {
        // Ініціалізація системи логування
        // Initialize logging system
        // Инициализация системы логирования
        std::lock_guard<std::mutex> lock(logMutex);
        
        // Додаємо консольний вивід за замовчуванням
        // Add console output by default
        // Добавляем консольный вывод по умолчанию
        auto consoleOutput = std::make_shared<ConsoleLogOutput>();
        if (consoleOutput->initialize()) {
            outputs.push_back(consoleOutput);
        }
        
        return true;
    }

    void LoggingSystem::setLogLevel(LogLevel level) {
        // Встановлення рівня логування
        // Set logging level
        // Установка уровня логирования
        std::lock_guard<std::mutex> lock(logMutex);
        currentLevel = level;
    }

    LogLevel LoggingSystem::getLogLevel() const {
        // Отримання рівня логування
        // Get logging level
        // Получение уровня логирования
        std::lock_guard<std::mutex> lock(logMutex);
        return currentLevel;
    }

    bool LoggingSystem::addLogOutput(std::shared_ptr<LogOutput> output) {
        // Додавання виводу логів
        // Add log output
        // Добавление вывода логов
        if (!output) {
            return false;
        }
        
        std::lock_guard<std::mutex> lock(logMutex);
        
        // Перевіряємо чи вивід такого типу вже існує
        // Check if output of this type already exists
        // Проверяем существует ли вывод такого типа уже
        for (const auto& existingOutput : outputs) {
            if (existingOutput->getType() == output->getType()) {
                return false; // Вивід такого типу вже існує / Output of this type already exists / Вывод такого типа уже существует
            }
        }
        
        if (output->initialize()) {
            outputs.push_back(output);
            return true;
        }
        
        return false;
    }

    bool LoggingSystem::removeLogOutput(LogOutputType type) {
        // Видалення виводу логів
        // Remove log output
        // Удаление вывода логов
        std::lock_guard<std::mutex> lock(logMutex);
        
        auto it = std::find_if(outputs.begin(), outputs.end(),
            [type](const std::shared_ptr<LogOutput>& output) {
                return output->getType() == type;
            });
            
        if (it != outputs.end()) {
            (*it)->close();
            outputs.erase(it);
            return true;
        }
        
        return false;
    }

    void LoggingSystem::log(LogLevel level, const std::string& module, const std::string& message) {
        // Запис логу
        // Write log
        // Запись лога
        if (!shouldLog(level)) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(logMutex);
        
        LogEntry entry(level, message, module, getCurrentTimestamp(), getThreadId());
        
        // Записуємо лог у всі виводи
        // Write log to all outputs
        // Записываем лог во все выводы
        for (const auto& output : outputs) {
            output->writeLog(entry);
        }
    }

    void LoggingSystem::debug(const std::string& module, const std::string& message) {
        // Запис логу рівня DEBUG
        // Write DEBUG level log
        // Запись лога уровня DEBUG
        log(LogLevel::LOG_DEBUG, module, message);
    }

    void LoggingSystem::info(const std::string& module, const std::string& message) {
        // Запис логу рівня INFO
        // Write INFO level log
        // Запись лога уровня INFO
        log(LogLevel::LOG_INFO, module, message);
    }

    void LoggingSystem::warning(const std::string& module, const std::string& message) {
        // Запис логу рівня WARNING
        // Write WARNING level log
        // Запись лога уровня WARNING
        log(LogLevel::LOG_WARNING, module, message);
    }

    void LoggingSystem::error(const std::string& module, const std::string& message) {
        // Запис логу рівня ERROR
        // Write ERROR level log
        // Запись лога уровня ERROR
        log(LogLevel::LOG_ERROR, module, message);
    }

    void LoggingSystem::critical(const std::string& module, const std::string& message) {
        // Запис логу рівня CRITICAL
        // Write CRITICAL level log
        // Запись лога уровня CRITICAL
        log(LogLevel::LOG_CRITICAL, module, message);
    }

    size_t LoggingSystem::getOutputCount() const {
        // Отримання кількості виводів
        // Get output count
        // Получение количества выводов
        std::lock_guard<std::mutex> lock(logMutex);
        return outputs.size();
    }

    void LoggingSystem::closeAllOutputs() {
        // Закриття всіх виводів
        // Close all outputs
        // Закрытие всех выводов
        std::lock_guard<std::mutex> lock(logMutex);
        
        for (const auto& output : outputs) {
            output->close();
        }
        
        outputs.clear();
    }

    std::string LoggingSystem::formatLogMessage(const LogEntry& entry) const {
        // Форматування повідомлення логу
        // Format log message
        // Форматирование сообщения лога
        std::ostringstream oss;
        oss << "[" << entry.timestamp << "] "
            << "[" << entry.threadId << "] "
            << "[" << entry.module << "] "
            << "[" << getLogLevelName(entry.level) << "] "
            << entry.message;
        return oss.str();
    }

    std::string LoggingSystem::getCurrentTimestamp() const {
        // Отримання поточного часу
        // Get current time
        // Получение текущего времени
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }

    std::string LoggingSystem::getThreadId() const {
        // Отримання ідентифікатора потоку
        // Get thread ID
        // Получение идентификатора потока
#ifdef _WIN32
        return std::to_string(GetCurrentThreadId());
#else
        return std::to_string(pthread_self());
#endif
    }

    std::string LoggingSystem::getLogLevelName(LogLevel level) const {
        // Отримання назви рівня логування
        // Get log level name
        // Получение названия уровня логирования
        switch (level) {
            case LogLevel::LOG_DEBUG:
                return "DEBUG";
            case LogLevel::LOG_INFO:
                return "INFO";
            case LogLevel::LOG_WARNING:
                return "WARNING";
            case LogLevel::LOG_ERROR:
                return "ERROR";
            case LogLevel::LOG_CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }

    bool LoggingSystem::shouldLog(LogLevel level) const {
        // Перевірка чи потрібно логувати повідомлення цього рівня
        // Check if message of this level should be logged
        // Проверка нужно ли логировать сообщение этого уровня
        std::lock_guard<std::mutex> lock(logMutex);
        return static_cast<int>(level) >= static_cast<int>(currentLevel);
    }

} // namespace Logging
} // namespace NeuroSync