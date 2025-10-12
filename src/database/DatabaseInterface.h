#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <any>

// DatabaseInterface.h
// Інтерфейс бази даних для NeuroSync OS Sparky
// Database interface for NeuroSync OS Sparky
// Интерфейс базы данных для NeuroSync OS Sparky

namespace NeuroSync {
namespace Database {

    // Тип бази даних
    // Database type
    // Тип базы данных
    enum class DatabaseType {
        SQLITE,         // SQLite / SQLite / SQLite
        POSTGRESQL,     // PostgreSQL / PostgreSQL / PostgreSQL
        MYSQL,          // MySQL / MySQL / MySQL
        MONGODB,        // MongoDB / MongoDB / MongoDB
        REDIS           // Redis / Redis / Redis
    };

    // Результат запиту
    // Query result
    // Результат запроса
    struct QueryResult {
        std::vector<std::map<std::string, std::any>> rows;  // Рядки результату / Result rows / Строки результата
        size_t rowCount;                                   // Кількість рядків / Row count / Количество строк
        size_t affectedRows;                              // Кількість змінених рядків / Affected rows / Количество измененных строк
        std::vector<std::string> columnNames;              // Назви стовпців / Column names / Названия столбцов
        bool success;                                     // Успіх операції / Operation success / Успех операции
        std::string errorMessage;                         // Повідомлення про помилку / Error message / Сообщение об ошибке
        
        QueryResult() : rowCount(0), affectedRows(0), success(true) {}
    };

    // Конфігурація бази даних
    // Database configuration
    // Конфигурация базы данных
    struct DatabaseConfig {
        DatabaseType type;              // Тип бази даних / Database type / Тип базы данных
        std::string host;              // Хост / Host / Хост
        int port;                      // Порт / Port / Порт
        std::string databaseName;      // Назва бази даних / Database name / Название базы данных
        std::string username;          // Ім'я користувача / Username / Имя пользователя
        std::string password;          // Пароль / Password / Пароль
        int maxConnections;            // Максимальна кількість з'єднань / Maximum connections / Максимальное количество соединений
        int connectionTimeout;         // Таймаут з'єднання (мс) / Connection timeout (ms) / Таймаут соединения (мс)
        bool enableConnectionPooling;  // Увімкнути пул з'єднань / Enable connection pooling / Включить пул соединений
        
        DatabaseConfig() 
            : type(DatabaseType::SQLITE), host("localhost"), port(5432), 
              maxConnections(10), connectionTimeout(30000), enableConnectionPooling(true) {}
    };

    // Транзакція
    // Transaction
    // Транзакция
    struct Transaction {
        std::string transactionId;      // ID транзакції / Transaction ID / ID транзакции
        long long startTime;           // Час початку / Start time / Время начала
        std::vector<std::string> queries; // Запити в транзакції / Queries in transaction / Запросы в транзакции
        bool committed;               // Чи зафіксовано / Committed / Зафиксировано
        bool rolledBack;              // Чи скасовано / Rolled back / Отменено
        
        Transaction() : startTime(0), committed(false), rolledBack(false) {}
    };

    // Інтерфейс бази даних
    // Database interface
    // Интерфейс базы данных
    class DatabaseInterface {
    public:
        DatabaseInterface();
        virtual ~DatabaseInterface();
        
        // Ініціалізація бази даних
        // Initialize database
        // Инициализация базы данных
        virtual bool initialize(const DatabaseConfig& config);
        
        // Підключення до бази даних
        // Connect to database
        // Подключение к базе данных
        virtual bool connect();
        
        // Відключення від бази даних
        // Disconnect from database
        // Отключение от базы данных
        virtual void disconnect();
        
        // Перевірка з'єднання
        // Check connection
        // Проверка соединения
        virtual bool isConnected() const;
        
        // Виконання запиту
        // Execute query
        // Выполнение запроса
        virtual QueryResult executeQuery(const std::string& query);
        
        // Виконання запиту з параметрами
        // Execute query with parameters
        // Выполнение запроса с параметрами
        virtual QueryResult executeQuery(const std::string& query, const std::map<std::string, std::any>& parameters);
        
        // Вставка даних
        // Insert data
        // Вставка данных
        virtual QueryResult insert(const std::string& table, const std::map<std::string, std::any>& data);
        
        // Оновлення даних
        // Update data
        // Обновление данных
        virtual QueryResult update(const std::string& table, const std::map<std::string, std::any>& data, 
                                  const std::string& whereClause = "");
        
        // Видалення даних
        // Delete data
        // Удаление данных
        virtual QueryResult deleteRecord(const std::string& table, const std::string& whereClause = "");
        
        // Вибірка даних
        // Select data
        // Выборка данных
        virtual QueryResult select(const std::string& table, const std::vector<std::string>& columns = {},
                                  const std::string& whereClause = "", const std::string& orderBy = "",
                                  int limit = -1, int offset = 0);
        
        // Створення транзакції
        // Begin transaction
        // Начало транзакции
        virtual std::string beginTransaction();
        
        // Фіксація транзакції
        // Commit transaction
        // Фиксация транзакции
        virtual bool commitTransaction(const std::string& transactionId);
        
        // Скасування транзакції
        // Rollback transaction
        // Отмена транзакции
        virtual bool rollbackTransaction(const std::string& transactionId);
        
        // Підготовка запиту
        // Prepare statement
        // Подготовка запроса
        virtual bool prepareStatement(const std::string& query, const std::string& statementId);
        
        // Виконання підготовленого запиту
        // Execute prepared statement
        // Выполнение подготовленного запроса
        virtual QueryResult executePreparedStatement(const std::string& statementId, 
                                                    const std::map<std::string, std::any>& parameters = {});
        
        // Закриття підготовленого запиту
        // Close prepared statement
        // Закрытие подготовленного запроса
        virtual void closePreparedStatement(const std::string& statementId);
        
        // Отримання статистики
        // Get statistics
        // Получение статистики
        struct DatabaseStatistics {
            size_t totalQueries;
            size_t successfulQueries;
            size_t failedQueries;
            size_t activeConnections;
            size_t totalTransactions;
            long long averageQueryTime;
            long long maxQueryTime;
        };
        
        virtual DatabaseStatistics getStatistics() const;
        
        // Отримання конфігурації
        // Get configuration
        // Получение конфигурации
        virtual DatabaseConfig getConfiguration() const;
        
        // Експорт даних
        // Export data
        // Экспорт данных
        virtual bool exportData(const std::string& tableName, const std::string& filePath);
        
        // Імпорт даних
        // Import data
        // Импорт данных
        virtual bool importData(const std::string& tableName, const std::string& filePath);
        
        // Створення резервної копії
        // Create backup
        // Создание резервной копии
        virtual bool createBackup(const std::string& backupPath);
        
        // Відновлення з резервної копії
        // Restore from backup
        // Восстановление из резервной копии
        virtual bool restoreFromBackup(const std::string& backupPath);
        
    protected:
        DatabaseConfig configuration;                    // Конфігурація / Configuration / Конфигурация
        mutable std::map<std::string, Transaction> transactions; // Транзакції / Transactions / Транзакции
        mutable std::map<std::string, std::string> preparedStatements; // Підготовлені запити / Prepared statements / Подготовленные запросы
        mutable DatabaseStatistics statistics;          // Статистика / Statistics / Статистика
        bool connected;                                // Стан з'єднання / Connection state / Состояние соединения
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        virtual long long getCurrentTimeMillis() const;
        virtual std::string generateTransactionId();
        virtual void updateStatistics(bool success, long long queryTime);
        virtual std::any convertToDatabaseType(const std::any& value);
        virtual std::string anyToString(const std::any& value);
    };

} // namespace Database
} // namespace NeuroSync

#endif // DATABASE_INTERFACE_H