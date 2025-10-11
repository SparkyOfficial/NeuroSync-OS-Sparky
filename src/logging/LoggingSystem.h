#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>
#include <map>

// LoggingSystem.h
// Система логування для NeuroSync OS Sparky
// Logging system for NeuroSync OS Sparky
// Система логирования для NeuroSync OS Sparky

namespace NeuroSync {
namespace Logging {

    // Рівні логування
    // Logging levels
    // Уровни логирования
    enum class LogLevel {
        LOG_DEBUG = 0,
        LOG_INFO = 1,
        LOG_WARNING = 2,
        LOG_ERROR = 3,
        LOG_CRITICAL = 4
    };

    // Типи виводу логів
    // Log output types
    // Типы вывода логов
    enum class LogOutputType {
        CONSOLE,
        FILE,
        NETWORK,
        CUSTOM
    };

    // Структура запису логу
    // Log entry structure
    // Структура записи лога
    struct LogEntry {
        LogLevel level;
        std::string message;
        std::string module;
        std::string timestamp;
        std::string threadId;
        
        LogEntry(LogLevel lvl, const std::string& msg, const std::string& mod, 
                const std::string& ts, const std::string& tid)
            : level(lvl), message(msg), module(mod), timestamp(ts), threadId(tid) {}
    };

    // Базовий інтерфейс для виводу логів
    // Base interface for log output
    // Базовый интерфейс для вывода логов
    class LogOutput {
    public:
        virtual ~LogOutput() = default;
        
        // Запис логу
        // Write log
        // Запись лога
        virtual void writeLog(const LogEntry& entry) = 0;
        
        // Отримання типу виводу
        // Get output type
        // Получение типа вывода
        virtual LogOutputType getType() const = 0;
        
        // Ініціалізація виводу
        // Initialize output
        // Инициализация вывода
        virtual bool initialize() = 0;
        
        // Закриття виводу
        // Close output
        // Закрытие вывода
        virtual void close() = 0;
    };

    // Вивід логів у консоль
    // Console log output
    // Вывод логов в консоль
    class ConsoleLogOutput : public LogOutput {
    public:
        ConsoleLogOutput();
        virtual ~ConsoleLogOutput();
        
        virtual void writeLog(const LogEntry& entry) override;
        virtual LogOutputType getType() const override;
        virtual bool initialize() override;
        virtual void close() override;
        
    private:
        bool initialized;
    };

    // Вивід логів у файл
    // File log output
    // Вывод логов в файл
    class FileLogOutput : public LogOutput {
    public:
        FileLogOutput(const std::string& filename);
        virtual ~FileLogOutput();
        
        virtual void writeLog(const LogEntry& entry) override;
        virtual LogOutputType getType() const override;
        virtual bool initialize() override;
        virtual void close() override;
        
        // Встановлення імені файлу
        // Set filename
        // Установка имени файла
        void setFilename(const std::string& filename);
        
        // Отримання імені файлу
        // Get filename
        // Получение имени файла
        std::string getFilename() const;
        
    private:
        std::string filename;
        std::ofstream fileStream;
        bool initialized;
    };

    // Система логування
    // Logging system
    // Система логирования
    class LoggingSystem {
    public:
        LoggingSystem();
        ~LoggingSystem();
        
        // Ініціалізація системи логування
        // Initialize logging system
        // Инициализация системы логирования
        bool initialize();
        
        // Встановлення рівня логування
        // Set logging level
        // Установка уровня логирования
        void setLogLevel(LogLevel level);
        
        // Отримання рівня логування
        // Get logging level
        // Получение уровня логирования
        LogLevel getLogLevel() const;
        
        // Додавання виводу логів
        // Add log output
        // Добавление вывода логов
        bool addLogOutput(std::shared_ptr<LogOutput> output);
        
        // Видалення виводу логів
        // Remove log output
        // Удаление вывода логов
        bool removeLogOutput(LogOutputType type);
        
        // Запис логу
        // Write log
        // Запись лога
        void log(LogLevel level, const std::string& module, const std::string& message);
        
        // Запис логу різних рівнів
        // Write logs of different levels
        // Запись логов разных уровней
        void debug(const std::string& module, const std::string& message);
        void info(const std::string& module, const std::string& message);
        void warning(const std::string& module, const std::string& message);
        void error(const std::string& module, const std::string& message);
        void critical(const std::string& module, const std::string& message);
        
        // Отримання кількості виводів
        // Get output count
        // Получение количества выводов
        size_t getOutputCount() const;
        
        // Закриття всіх виводів
        // Close all outputs
        // Закрытие всех выводов
        void closeAllOutputs();
        
        // Форматування повідомлення логу
        // Format log message
        // Форматирование сообщения лога
        std::string formatLogMessage(const LogEntry& entry) const;
        
        // Отримання поточного часу
        // Get current time
        // Получение текущего времени
        std::string getCurrentTimestamp() const;
        
        // Отримання ідентифікатора потоку
        // Get thread ID
        // Получение идентификатора потока
        std::string getThreadId() const;
        
        // Отримання назви рівня логування
        // Get log level name
        // Получение названия уровня логирования
        std::string getLogLevelName(LogLevel level) const;
        
    private:
        LogLevel currentLevel;
        std::vector<std::shared_ptr<LogOutput>> outputs;
        mutable std::mutex logMutex;
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        bool shouldLog(LogLevel level) const;
    };

    // Глобальна система логування
    // Global logging system
    // Глобальная система логирования
    extern LoggingSystem gLogger;

} // namespace Logging
} // namespace NeuroSync

#endif // LOGGING_SYSTEM_H