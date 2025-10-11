// test_logging_system.cpp
// Тестування системи логування / Logging system testing / Тестирование системы логирования
// NeuroSync OS Sparky

#include "../logging/LoggingSystem.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>

using namespace NeuroSync::Logging;

// Тестовий вивід логів
// Test log output
// Тестовый вывод логов
class TestLogOutput : public LogOutput {
public:
    TestLogOutput() : initialized(false), logCount(0) {}
    virtual ~TestLogOutput() {
        if (initialized) {
            close();
        }
    }
    
    virtual void writeLog(const LogEntry& entry) override {
        if (!initialized) {
            return;
        }
        lastEntry = entry;
        logCount++;
    }
    
    virtual LogOutputType getType() const override {
        return LogOutputType::CUSTOM;
    }
    
    virtual bool initialize() override {
        initialized = true;
        return true;
    }
    
    virtual void close() override {
        initialized = false;
    }
    
    LogEntry getLastEntry() const {
        return lastEntry;
    }
    
    size_t getLogCount() const {
        return logCount;
    }
    
private:
    bool initialized;
    LogEntry lastEntry{LogLevel::LOG_INFO, "", "", "", ""};
    size_t logCount;
};

int main() {
    std::cout << "NeuroSync OS Sparky - Logging System Tests" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    // Тест 1: Створення та ініціалізація
    // Test 1: Creation and initialization
    // Тест 1: Создание и инициализация
    std::cout << "Test 1: Creating and initializing LoggingSystem..." << std::endl;
    LoggingSystem logger;
    assert(logger.initialize());
    std::cout << "PASS: LoggingSystem created and initialized successfully" << std::endl;
    
    // Тест 2: Початковий рівень логування
    // Test 2: Initial logging level
    // Тест 2: Начальный уровень логирования
    std::cout << "Test 2: Checking initial logging level..." << std::endl;
    assert(logger.getLogLevel() == LogLevel::LOG_INFO);
    std::cout << "PASS: Initial logging level is INFO" << std::endl;
    
    // Тест 3: Встановлення рівня логування
    // Test 3: Setting logging level
    // Тест 3: Установка уровня логирования
    std::cout << "Test 3: Setting logging level..." << std::endl;
    logger.setLogLevel(LogLevel::LOG_DEBUG);
    assert(logger.getLogLevel() == LogLevel::LOG_DEBUG);
    std::cout << "PASS: Logging level set to DEBUG" << std::endl;
    
    // Тест 4: Кількість виводів
    // Test 4: Output count
    // Тест 4: Количество выводов
    std::cout << "Test 4: Checking output count..." << std::endl;
    assert(logger.getOutputCount() >= 1); // Має бути принаймні консольний вивід / Should be at least console output / Должен быть хотя бы консольный вывод
    std::cout << "PASS: Output count is correct" << std::endl;
    
    // Тест 5: Додавання тестового виводу
    // Test 5: Adding test output
    // Тест 5: Добавление тестового вывода
    std::cout << "Test 5: Adding test output..." << std::endl;
    auto testOutput = std::make_shared<TestLogOutput>();
    assert(logger.addLogOutput(testOutput));
    assert(logger.getOutputCount() >= 2);
    std::cout << "PASS: Test output added successfully" << std::endl;
    
    // Тест 6: Запис логів різних рівнів
    // Test 6: Writing logs of different levels
    // Тест 6: Запись логов разных уровней
    std::cout << "Test 6: Writing logs of different levels..." << std::endl;
    logger.debug("TestModule", "Debug message");
    logger.info("TestModule", "Info message");
    logger.warning("TestModule", "Warning message");
    logger.error("TestModule", "Error message");
    logger.critical("TestModule", "Critical message");
    
    // Перевіряємо, що логи були записані
    // Check that logs were written
    // Проверяем, что логи были записаны
    assert(testOutput->getLogCount() >= 5);
    std::cout << "PASS: Logs written successfully" << std::endl;
    
    // Тест 7: Отримання останнього запису логу
    // Test 7: Getting last log entry
    // Тест 7: Получение последней записи лога
    std::cout << "Test 7: Getting last log entry..." << std::endl;
    LogEntry lastEntry = testOutput->getLastEntry();
    assert(lastEntry.level == LogLevel::LOG_CRITICAL);
    assert(lastEntry.module == "TestModule");
    assert(lastEntry.message == "Critical message");
    std::cout << "PASS: Last log entry is correct" << std::endl;
    
    // Тест 8: Форматування повідомлення логу
    // Test 8: Formatting log message
    // Тест 8: Форматирование сообщения лога
    std::cout << "Test 8: Formatting log message..." << std::endl;
    std::string formattedMessage = logger.formatLogMessage(lastEntry);
    assert(!formattedMessage.empty());
    assert(formattedMessage.find("CRITICAL") != std::string::npos);
    assert(formattedMessage.find("TestModule") != std::string::npos);
    assert(formattedMessage.find("Critical message") != std::string::npos);
    std::cout << "PASS: Log message formatted correctly" << std::endl;
    
    // Тест 9: Отримання поточного часу
    // Test 9: Getting current time
    // Тест 9: Получение текущего времени
    std::cout << "Test 9: Getting current time..." << std::endl;
    std::string timestamp = logger.getCurrentTimestamp();
    assert(!timestamp.empty());
    assert(timestamp.length() >= 19); // Має бути принаймні YYYY-MM-DD HH:MM:SS / Should be at least YYYY-MM-DD HH:MM:SS / Должно быть хотя бы YYYY-MM-DD HH:MM:SS
    std::cout << "PASS: Current time obtained correctly" << std::endl;
    
    // Тест 10: Отримання ідентифікатора потоку
    // Test 10: Getting thread ID
    // Тест 10: Получение идентификатора потока
    std::cout << "Test 10: Getting thread ID..." << std::endl;
    std::string threadId = logger.getThreadId();
    assert(!threadId.empty());
    std::cout << "PASS: Thread ID obtained correctly" << std::endl;
    
    // Тест 11: Отримання назви рівня логування
    // Test 11: Getting log level name
    // Тест 11: Получение названия уровня логирования
    std::cout << "Test 11: Getting log level names..." << std::endl;
    assert(logger.getLogLevelName(LogLevel::LOG_DEBUG) == "DEBUG");
    assert(logger.getLogLevelName(LogLevel::LOG_INFO) == "INFO");
    assert(logger.getLogLevelName(LogLevel::LOG_WARNING) == "WARNING");
    assert(logger.getLogLevelName(LogLevel::LOG_ERROR) == "ERROR");
    assert(logger.getLogLevelName(LogLevel::LOG_CRITICAL) == "CRITICAL");
    std::cout << "PASS: Log level names are correct" << std::endl;
    
    // Тест 12: Видалення виводу
    // Test 12: Removing output
    // Тест 12: Удаление вывода
    std::cout << "Test 12: Removing test output..." << std::endl;
    assert(logger.removeLogOutput(LogOutputType::CUSTOM));
    assert(logger.getOutputCount() >= 1);
    std::cout << "PASS: Test output removed successfully" << std::endl;
    
    // Тест 13: Закриття всіх виводів
    // Test 13: Closing all outputs
    // Тест 13: Закрытие всех выводов
    std::cout << "Test 13: Closing all outputs..." << std::endl;
    logger.closeAllOutputs();
    assert(logger.getOutputCount() == 0);
    std::cout << "PASS: All outputs closed successfully" << std::endl;
    
    // Очищення тестового файлу
    // Clean up test file
    // Очистка тестового файла
    std::remove("example.log");
    
    std::cout << "\nAll Logging System tests passed!" << std::endl;
    return 0;
}