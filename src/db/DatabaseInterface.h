#ifndef DATABASE_INTERFACE_H
#define DATABASE_INTERFACE_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <set>
#include <functional>
#include "../neuron/NeuronManager.h"
#include "../network_neural/NeuralNetwork.h"

// DatabaseInterface.h
// Модуль інтерфейсу бази даних для NeuroSync OS Sparky
// Database interface module for NeuroSync OS Sparky
// Модуль интерфейса базы данных для NeuroSync OS Sparky

namespace NeuroSync {
namespace Database {

    // Типи баз даних
    // Database types
    // Типы баз данных
    enum class DatabaseType {
        RELATIONAL,     // Реляційна база даних / Relational database / Реляционная база данных
        NOSQL,          // NoSQL база даних / NoSQL database / NoSQL база данных
        GRAPH,          // Графова база даних / Graph database / Графовая база данных
        DOCUMENT,       // Документна база даних / Document database / Документная база данных
        KEY_VALUE,      // База даних ключ-значення / Key-value database / База данных ключ-значение
        COLUMN_FAMILY,  // База даних сімейства стовпців / Column-family database / База данных семейства колонок
        TIME_SERIES,    // База даних часових рядів / Time series database / База данных временных рядов
        VECTOR          // Векторна база даних / Vector database / Векторная база данных
    };

    // Структура запису бази даних
    // Database record structure
    // Структура записи базы данных
    struct DatabaseRecord {
        std::map<std::string, std::string> fields;  // Поля запису / Record fields / Поля записи
        std::string id;                             // Унікальний ідентифікатор / Unique identifier / Уникальный идентификатор
        long long timestamp;                       // Часова мітка / Timestamp / Временная метка
        std::string collection;                     // Колекція/таблиця / Collection/table / Коллекция/таблица
        
        DatabaseRecord() : timestamp(0) {}
        
        DatabaseRecord(const std::string& recordId, const std::string& coll = "")
            : id(recordId), collection(coll), timestamp(0) {}
    };

    // Структура запиту до бази даних
    // Database query structure
    // Структура запроса к базе данных
    struct DatabaseQuery {
        std::string collection;                     // Колекція/таблиця / Collection/table / Коллекция/таблица
        std::map<std::string, std::string> filters; // Фільтри / Filters / Фильтры
        std::vector<std::string> fields;            // Поля для вибірки / Fields to select / Поля для выборки
        std::string sortField;                      // Поле для сортування / Field to sort by / Поле для сортировки
        int sortOrder;                              // Порядок сортування (1 - зростання, -1 - спадання) / Sort order (1 - ascending, -1 - descending) / Порядок сортировки (1 - возрастание, -1 - убывание)
        int limit;                                  // Ліміт результатів / Limit results / Лимит результатов
        int offset;                                 // Зсув результатів / Offset results / Сдвиг результатов
        
        DatabaseQuery() : sortOrder(1), limit(-1), offset(0) {}
        
        DatabaseQuery(const std::string& coll)
            : collection(coll), sortOrder(1), limit(-1), offset(0) {}
    };

    // Структура результату запиту
    // Query result structure
    // Структура результата запроса
    struct QueryResult {
        std::vector<DatabaseRecord> records;        // Записи результату / Result records / Записи результата
        size_t totalCount;                          // Загальна кількість записів / Total record count / Общее количество записей
        double executionTime;                       // Час виконання запиту / Query execution time / Время выполнения запроса
        bool success;                               // Успішність виконання / Execution success / Успешность выполнения
        std::string errorMessage;                   // Повідомлення про помилку / Error message / Сообщение об ошибке
        
        QueryResult() : totalCount(0), executionTime(0.0), success(true) {}
    };

    // Структура моделі бази даних
    // Database model structure
    // Структура модели базы данных
    struct DatabaseModel {
        DatabaseType type;                          // Тип бази даних / Database type / Тип базы данных
        std::string name;                           // Ім'я бази даних / Database name / Имя базы данных
        std::map<std::string, std::string> connectionParams; // Параметри підключення / Connection parameters / Параметры подключения
        std::unique_ptr<Network::NeuralNetwork> neuralNetwork; // Нейронна мережа для інтелектуальних запитів / Neural network for intelligent queries / Нейронная сеть для интеллектуальных запросов
        std::set<std::string> collections;          // Колекції/таблиці / Collections/tables / Коллекции/таблицы
        size_t recordCount;                        // Кількість записів / Record count / Количество записей
        
        DatabaseModel(DatabaseType t, const std::string& n)
            : type(t), name(n), recordCount(0) {}
    };

    // Модуль інтерфейсу бази даних
    // Database interface module
    // Модуль интерфейса базы данных
    class DatabaseInterface {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        DatabaseInterface();
        
        // Деструктор
        // Destructor
        // Деструктор
        ~DatabaseInterface();
        
        // Ініціалізація інтерфейсу
        // Initialize interface
        // Инициализация интерфейса
        bool initialize();
        
        // Підключення до бази даних
        // Connect to database
        // Подключение к базе данных
        bool connect(const std::string& connectionString, DatabaseType type = DatabaseType::RELATIONAL);
        
        // Відключення від бази даних
        // Disconnect from database
        // Отключение от базы данных
        void disconnect();
        
        // Перевірка підключення
        // Check connection
        // Проверка подключения
        bool isConnected() const;
        
        // Створення колекції/таблиці
        // Create collection/table
        // Создание коллекции/таблицы
        bool createCollection(const std::string& collectionName);
        
        // Видалення колекції/таблиці
        // Drop collection/table
        // Удаление коллекции/таблицы
        bool dropCollection(const std::string& collectionName);
        
        // Вставка запису
        // Insert record
        // Вставка записи
        bool insertRecord(const DatabaseRecord& record);
        
        // Оновлення запису
        // Update record
        // Обновление записи
        bool updateRecord(const DatabaseRecord& record);
        
        // Видалення запису
        // Delete record
        // Удаление записи
        bool deleteRecord(const std::string& collection, const std::string& id);
        
        // Вибірка записів
        // Select records
        // Выборка записей
        QueryResult selectRecords(const DatabaseQuery& query);
        
        // Виконання власного запиту
        // Execute custom query
        // Выполнение пользовательского запроса
        QueryResult executeQuery(const std::string& query);
        
        // Транзакція
        // Transaction
        // Транзакция
        bool beginTransaction();
        bool commitTransaction();
        bool rollbackTransaction();
        
        // Індексація
        // Indexing
        // Индексация
        bool createIndex(const std::string& collection, const std::string& field);
        bool dropIndex(const std::string& collection, const std::string& field);
        
        // Резервне копіювання
        // Backup
        // Резервное копирование
        bool backup(const std::string& backupPath);
        bool restore(const std::string& backupPath);
        
        // Оптимізація
        // Optimization
        // Оптимизация
        bool optimize();
        
        // Аналіз даних
        // Data analysis
        // Анализ данных
        std::map<std::string, double> analyzeData(const std::string& collection);
        
        // Інтелектуальний запит
        // Intelligent query
        // Интеллектуальный запрос
        QueryResult intelligentQuery(const std::string& naturalLanguageQuery);
        
        // Генерація звіту
        // Report generation
        // Генерация отчета
        std::string generateReport(const std::string& collection, const std::string& reportType);
        
        // Валідація даних
        // Data validation
        // Валидация данных
        bool validateData(const DatabaseRecord& record);
        
        // Статистика інтерфейсу
        // Interface statistics
        // Статистика интерфейса
        struct DatabaseStatistics {
            size_t totalQueriesExecuted;
            size_t totalRecordsInserted;
            size_t totalRecordsUpdated;
            size_t totalRecordsDeleted;
            size_t totalConnections;
            double averageQueryTime;
            long long lastQueryTime;
            
            DatabaseStatistics() : totalQueriesExecuted(0), totalRecordsInserted(0), 
                                  totalRecordsUpdated(0), totalRecordsDeleted(0), 
                                  totalConnections(0), averageQueryTime(0.0), 
                                  lastQueryTime(0) {}
        };
        
        DatabaseStatistics getStatistics() const;
        
        // Отримати версію модуля
        // Get module version
        // Получить версию модуля
        std::string getVersion() const;
        
    private:
        std::unique_ptr<DatabaseModel> currentDatabase; // Поточна база даних / Current database / Текущая база данных
        std::unique_ptr<NeuronManager> neuronManager;    // Менеджер нейронів / Neuron manager / Менеджер нейронов
        DatabaseStatistics statistics;                  // Статистика / Statistics / Статистика
        bool isInitialized;                            // Прапор ініціалізації / Initialization flag / Флаг инициализации
        bool connected;                                // Прапор підключення / Connection flag / Флаг подключения
        std::string version;                           // Версія модуля / Module version / Версия модуля
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void initializeDatabaseResources();
        long long getCurrentTimeMillis() const;
        std::string generateRecordId();
        std::string serializeRecord(const DatabaseRecord& record);
        DatabaseRecord deserializeRecord(const std::string& serializedRecord);
        std::vector<DatabaseRecord> filterRecords(const std::vector<DatabaseRecord>& records, 
                                                 const std::map<std::string, std::string>& filters);
        std::vector<DatabaseRecord> sortRecords(const std::vector<DatabaseRecord>& records, 
                                               const std::string& sortField, int sortOrder);
        std::vector<DatabaseRecord> limitRecords(const std::vector<DatabaseRecord>& records, 
                                                int limit, int offset);
        double calculateSimilarity(const std::string& query1, const std::string& query2);
        std::vector<double> textToVector(const std::string& text);
        std::string vectorToText(const std::vector<double>& vector);
    };

} // namespace Database
} // namespace NeuroSync

#endif // DATABASE_INTERFACE_H