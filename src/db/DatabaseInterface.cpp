#include "DatabaseInterface.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <thread>
#include <sstream>
#include <iomanip>

// DatabaseInterface.cpp
// Реалізація модуля інтерфейсу бази даних для NeuroSync OS Sparky
// Implementation of database interface module for NeuroSync OS Sparky
// Реализация модуля интерфейса базы данных для NeuroSync OS Sparky
// Автор: Андрій Будильников

namespace NeuroSync {
namespace Database {

    // Конструктор
    // Constructor
    // Конструктор
    DatabaseInterface::DatabaseInterface() 
        : isInitialized(false), connected(false), version("1.0.0") {
        statistics.totalQueriesExecuted = 0;
        statistics.totalRecordsInserted = 0;
        statistics.totalRecordsUpdated = 0;
        statistics.totalRecordsDeleted = 0;
        statistics.totalConnections = 0;
        statistics.averageQueryTime = 0.0;
        statistics.lastQueryTime = 0;
    }

    // Деструктор
    // Destructor
    // Деструктор
    DatabaseInterface::~DatabaseInterface() {
        disconnect();
    }

    // Ініціалізація інтерфейсу
    // Initialize interface
    // Инициализация интерфейса
    bool DatabaseInterface::initialize() {
        if (isInitialized) {
            return true;
        }

        // Ініціалізація ресурсів бази даних
        // Initialize database resources
        // Инициализация ресурсов базы данных
        initializeDatabaseResources();

        isInitialized = true;
        std::cout << "[DATABASE] Database interface initialized successfully" << std::endl;
        return true;
    }

    // Підключення до бази даних
    // Connect to database
    // Подключение к базе данных
    bool DatabaseInterface::connect(const std::string& connectionString, DatabaseType type) {
        if (connected) {
            return true;
        }

        if (!isInitialized) {
            if (!initialize()) {
                std::cerr << "[DATABASE] Failed to initialize before connection" << std::endl;
                return false;
            }
        }

        // Створення моделі бази даних
        // Create database model
        // Создание модели базы данных
        currentDatabase = std::make_unique<DatabaseModel>(type, "NeuroSyncDB");

        // Симуляція процесу підключення
        // Simulate connection process
        // Симуляция процесса подключения
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        connected = true;
        statistics.totalConnections++;

        std::cout << "[DATABASE] Connected to database successfully" << std::endl;
        return true;
    }

    // Відключення від бази даних
    // Disconnect from database
    // Отключение от базы данных
    void DatabaseInterface::disconnect() {
        if (!connected) {
            return;
        }

        // Симуляція процесу відключення
        // Simulate disconnection process
        // Симуляция процесса отключения
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        currentDatabase.reset();
        connected = false;

        std::cout << "[DATABASE] Disconnected from database" << std::endl;
    }

    // Перевірка підключення
    // Check connection
    // Проверка подключения
    bool DatabaseInterface::isConnected() const {
        return connected;
    }

    // Створення колекції/таблиці
    // Create collection/table
    // Создание коллекции/таблицы
    bool DatabaseInterface::createCollection(const std::string& collectionName) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        if (!currentDatabase) {
            std::cerr << "[DATABASE] No database model initialized" << std::endl;
            return false;
        }

        // Додавання колекції до моделі
        // Add collection to model
        // Добавление коллекции к модели
        currentDatabase->collections.insert(collectionName);

        // Симуляція процесу створення
        // Simulate creation process
        // Симуляция процесса создания
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        std::cout << "[DATABASE] Collection '" << collectionName << "' created successfully" << std::endl;
        return true;
    }

    // Видалення колекції/таблиці
    // Drop collection/table
    // Удаление коллекции/таблицы
    bool DatabaseInterface::dropCollection(const std::string& collectionName) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        if (!currentDatabase) {
            std::cerr << "[DATABASE] No database model initialized" << std::endl;
            return false;
        }

        // Видалення колекції з моделі
        // Remove collection from model
        // Удаление коллекции из модели
        currentDatabase->collections.erase(collectionName);

        // Симуляція процесу видалення
        // Simulate drop process
        // Симуляция процесса удаления
        std::this_thread::sleep_for(std::chrono::milliseconds(15));

        std::cout << "[DATABASE] Collection '" << collectionName << "' dropped successfully" << std::endl;
        return true;
    }

    // Вставка запису
    // Insert record
    // Вставка записи
    bool DatabaseInterface::insertRecord(const DatabaseRecord& record) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        auto startTime = getCurrentTimeMillis();

        // Симуляція процесу вставки
        // Simulate insertion process
        // Симуляция процесса вставки
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        // Генерація ID, якщо не встановлено
        // Generate ID if not set
        // Генерация ID, если не установлен
        DatabaseRecord newRecord = record;
        if (newRecord.id.empty()) {
            newRecord.id = generateRecordId();
        }

        // Встановлення часової мітки
        // Set timestamp
        // Установка временной метки
        newRecord.timestamp = getCurrentTimeMillis();

        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        statistics.totalRecordsInserted++;
        statistics.lastQueryTime = getCurrentTimeMillis() - startTime;

        std::cout << "[DATABASE] Record inserted successfully with ID: " << newRecord.id << std::endl;
        return true;
    }

    // Оновлення запису
    // Update record
    // Обновление записи
    bool DatabaseInterface::updateRecord(const DatabaseRecord& record) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        auto startTime = getCurrentTimeMillis();

        // Симуляція процесу оновлення
        // Simulate update process
        // Симуляция процесса обновления
        std::this_thread::sleep_for(std::chrono::milliseconds(7));

        // Оновлення часової мітки
        // Update timestamp
        // Обновление временной метки
        DatabaseRecord updatedRecord = record;
        updatedRecord.timestamp = getCurrentTimeMillis();

        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        statistics.totalRecordsUpdated++;
        statistics.lastQueryTime = getCurrentTimeMillis() - startTime;

        std::cout << "[DATABASE] Record updated successfully with ID: " << record.id << std::endl;
        return true;
    }

    // Видалення запису
    // Delete record
    // Удаление записи
    bool DatabaseInterface::deleteRecord(const std::string& collection, const std::string& id) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        auto startTime = getCurrentTimeMillis();

        // Симуляція процесу видалення
        // Simulate deletion process
        // Симуляция процесса удаления
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        statistics.totalRecordsDeleted++;
        statistics.lastQueryTime = getCurrentTimeMillis() - startTime;

        std::cout << "[DATABASE] Record deleted successfully from collection '" << collection 
                  << "' with ID: " << id << std::endl;
        return true;
    }

    // Вибірка записів
    // Select records
    // Выборка записей
    QueryResult DatabaseInterface::selectRecords(const DatabaseQuery& query) {
        QueryResult result;

        if (!connected) {
            result.success = false;
            result.errorMessage = "Not connected to database";
            std::cerr << "[DATABASE] " << result.errorMessage << std::endl;
            return result;
        }

        auto startTime = getCurrentTimeMillis();

        // Симуляція процесу вибірки
        // Simulate selection process
        // Симуляция процесса выборки
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(10, 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));

        // Генерація результатів
        // Generate results
        // Генерация результатов
        int recordCount = query.limit > 0 ? std::min(query.limit, 20) : 5;
        result.totalCount = recordCount;

        for (int i = 0; i < recordCount; ++i) {
            DatabaseRecord record;
            record.id = generateRecordId();
            record.collection = query.collection;
            record.timestamp = getCurrentTimeMillis() - (i * 1000);

            // Додавання полів
            // Add fields
            // Добавление полей
            record.fields["name"] = "Record " + std::to_string(i + 1);
            record.fields["value"] = std::to_string((i + 1) * 10.5);
            record.fields["category"] = "Category " + std::to_string((i % 3) + 1);

            result.records.push_back(record);
        }

        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        statistics.totalQueriesExecuted++;
        auto endTime = getCurrentTimeMillis();
        result.executionTime = (endTime - startTime) / 1000.0; // В секундах / In seconds / В секундах
        statistics.lastQueryTime = endTime - startTime;

        result.success = true;
        std::cout << "[DATABASE] Selected " << result.records.size() << " records from collection '" 
                  << query.collection << "' in " << result.executionTime << " seconds" << std::endl;

        return result;
    }

    // Виконання власного запиту
    // Execute custom query
    // Выполнение пользовательского запроса
    QueryResult DatabaseInterface::executeQuery(const std::string& query) {
        QueryResult result;

        if (!connected) {
            result.success = false;
            result.errorMessage = "Not connected to database";
            std::cerr << "[DATABASE] " << result.errorMessage << std::endl;
            return result;
        }

        auto startTime = getCurrentTimeMillis();

        // Симуляція процесу виконання запиту
        // Simulate query execution process
        // Симуляция процесса выполнения запроса
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(20, 150);
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));

        // Аналіз типу запиту
        // Analyze query type
        // Анализ типа запроса
        std::string upperQuery = query;
        std::transform(upperQuery.begin(), upperQuery.end(), upperQuery.begin(), ::toupper);

        if (upperQuery.find("SELECT") != std::string::npos) {
            // Генерація результатів SELECT запиту
            // Generate SELECT query results
            // Генерация результатов SELECT запроса
            int recordCount = 5;
            result.totalCount = recordCount;

            for (int i = 0; i < recordCount; ++i) {
                DatabaseRecord record;
                record.id = generateRecordId();
                record.timestamp = getCurrentTimeMillis() - (i * 1000);

                // Додавання полів
                // Add fields
                // Добавление полей
                record.fields["id"] = record.id;
                record.fields["name"] = "Result " + std::to_string(i + 1);
                record.fields["score"] = std::to_string((i + 1) * 15.7);

                result.records.push_back(record);
            }
        } else if (upperQuery.find("INSERT") != std::string::npos) {
            // Симуляція INSERT запиту
            // Simulate INSERT query
            // Симуляция INSERT запроса
            result.totalCount = 1;
            statistics.totalRecordsInserted++;
        } else if (upperQuery.find("UPDATE") != std::string::npos) {
            // Симуляція UPDATE запиту
            // Simulate UPDATE query
            // Симуляция UPDATE запроса
            result.totalCount = 0;
            statistics.totalRecordsUpdated += 3;
        } else if (upperQuery.find("DELETE") != std::string::npos) {
            // Симуляція DELETE запиту
            // Simulate DELETE query
            // Симуляция DELETE запроса
            result.totalCount = 0;
            statistics.totalRecordsDeleted += 2;
        }

        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        statistics.totalQueriesExecuted++;
        auto endTime = getCurrentTimeMillis();
        result.executionTime = (endTime - startTime) / 1000.0; // В секундах / In seconds / В секундах
        statistics.lastQueryTime = endTime - startTime;

        result.success = true;
        std::cout << "[DATABASE] Executed query in " << result.executionTime << " seconds" << std::endl;

        return result;
    }

    // Транзакція
    // Transaction
    // Транзакция
    bool DatabaseInterface::beginTransaction() {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція початку транзакції
        // Simulate beginning of transaction
        // Симуляция начала транзакции
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        std::cout << "[DATABASE] Transaction started" << std::endl;
        return true;
    }

    bool DatabaseInterface::commitTransaction() {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція фіксації транзакції
        // Simulate committing transaction
        // Симуляция фиксации транзакции
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        std::cout << "[DATABASE] Transaction committed" << std::endl;
        return true;
    }

    bool DatabaseInterface::rollbackTransaction() {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція відкочення транзакції
        // Simulate rolling back transaction
        // Симуляция отката транзакции
        std::this_thread::sleep_for(std::chrono::milliseconds(8));

        std::cout << "[DATABASE] Transaction rolled back" << std::endl;
        return true;
    }

    // Індексація
    // Indexing
    // Индексация
    bool DatabaseInterface::createIndex(const std::string& collection, const std::string& field) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція створення індексу
        // Simulate index creation
        // Симуляция создания индекса
        std::this_thread::sleep_for(std::chrono::milliseconds(25));

        std::cout << "[DATABASE] Index created on field '" << field << "' in collection '" 
                  << collection << "'" << std::endl;
        return true;
    }

    bool DatabaseInterface::dropIndex(const std::string& collection, const std::string& field) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція видалення індексу
        // Simulate index deletion
        // Симуляция удаления индекса
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        std::cout << "[DATABASE] Index dropped on field '" << field << "' in collection '" 
                  << collection << "'" << std::endl;
        return true;
    }

    // Резервне копіювання
    // Backup
    // Резервное копирование
    bool DatabaseInterface::backup(const std::string& backupPath) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція процесу резервного копіювання
        // Simulate backup process
        // Симуляция процесса резервного копирования
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        std::cout << "[DATABASE] Database backup created at: " << backupPath << std::endl;
        return true;
    }

    bool DatabaseInterface::restore(const std::string& backupPath) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція процесу відновлення
        // Simulate restore process
        // Симуляция процесса восстановления
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        std::cout << "[DATABASE] Database restored from: " << backupPath << std::endl;
        return true;
    }

    // Оптимізація
    // Optimization
    // Оптимизация
    bool DatabaseInterface::optimize() {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return false;
        }

        // Симуляція процесу оптимізації
        // Simulate optimization process
        // Симуляция процесса оптимизации
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        std::cout << "[DATABASE] Database optimized successfully" << std::endl;
        return true;
    }

    // Аналіз даних
    // Data analysis
    // Анализ данных
    std::map<std::string, double> DatabaseInterface::analyzeData(const std::string& collection) {
        std::map<std::string, double> analysisResults;

        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return analysisResults;
        }

        // Симуляція процесу аналізу даних
        // Simulate data analysis process
        // Симуляция процесса анализа данных
        std::this_thread::sleep_for(std::chrono::milliseconds(75));

        // Генерація результатів аналізу
        // Generate analysis results
        // Генерация результатов анализа
        analysisResults["record_count"] = 1250.0;
        analysisResults["average_size"] = 1024.5;
        analysisResults["fragmentation"] = 0.15;
        analysisResults["compression_ratio"] = 0.75;
        analysisResults["index_efficiency"] = 0.88;

        std::cout << "[DATABASE] Data analysis completed for collection: " << collection << std::endl;
        return analysisResults;
    }

    // Інтелектуальний запит
    // Intelligent query
    // Интеллектуальный запрос
    QueryResult DatabaseInterface::intelligentQuery(const std::string& naturalLanguageQuery) {
        QueryResult result;

        if (!connected) {
            result.success = false;
            result.errorMessage = "Not connected to database";
            std::cerr << "[DATABASE] " << result.errorMessage << std::endl;
            return result;
        }

        auto startTime = getCurrentTimeMillis();

        // Симуляція процесу інтелектуального запиту
        // Simulate intelligent query process
        // Симуляция процесса интеллектуального запроса
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Генерація результатів
        // Generate results
        // Генерация результатов
        int recordCount = 3;
        result.totalCount = recordCount;

        for (int i = 0; i < recordCount; ++i) {
            DatabaseRecord record;
            record.id = generateRecordId();
            record.timestamp = getCurrentTimeMillis() - (i * 1000);

            // Додавання полів
            // Add fields
            // Добавление полей
            record.fields["result"] = "Intelligent result " + std::to_string(i + 1);
            record.fields["confidence"] = std::to_string(0.85 + (i * 0.05));

            result.records.push_back(record);
        }

        // Оновлення статистики
        // Update statistics
        // Обновление статистики
        statistics.totalQueriesExecuted++;
        auto endTime = getCurrentTimeMillis();
        result.executionTime = (endTime - startTime) / 1000.0; // В секундах / In seconds / В секундах
        statistics.lastQueryTime = endTime - startTime;

        result.success = true;
        std::cout << "[DATABASE] Intelligent query processed in " << result.executionTime << " seconds" << std::endl;

        return result;
    }

    // Генерація звіту
    // Report generation
    // Генерация отчета
    std::string DatabaseInterface::generateReport(const std::string& collection, const std::string& reportType) {
        if (!connected) {
            std::cerr << "[DATABASE] Not connected to database" << std::endl;
            return "";
        }

        // Симуляція процесу генерації звіту
        // Simulate report generation process
        // Симуляция процесса генерации отчета
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // Генерація тексту звіту
        // Generate report text
        // Генерация текста отчета
        std::ostringstream report;
        report << "=== Database Report ===\n";
        report << "Collection: " << collection << "\n";
        report << "Report Type: " << reportType << "\n";
        report << "Generated: " << getCurrentTimeMillis() << "\n";
        report << "Records Analyzed: 1250\n";
        report << "Average Record Size: 1024.5 bytes\n";
        report << "Fragmentation: 15%\n";
        report << "========================\n";

        std::string reportText = report.str();
        std::cout << "[DATABASE] Report generated for collection: " << collection << std::endl;

        return reportText;
    }

    // Валідація даних
    // Data validation
    // Валидация данных
    bool DatabaseInterface::validateData(const DatabaseRecord& record) {
        // Симуляція процесу валідації даних
        // Simulate data validation process
        // Симуляция процесса валидации данных
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        // Проста валідація - перевірка наявності ID
        // Simple validation - check for ID presence
        // Простая валидация - проверка наличия ID
        bool isValid = !record.id.empty();

        std::cout << "[DATABASE] Data validation " << (isValid ? "passed" : "failed") 
                  << " for record ID: " << record.id << std::endl;

        return isValid;
    }

    // Статистика інтерфейсу
    // Interface statistics
    // Статистика интерфейса
    DatabaseInterface::DatabaseStatistics DatabaseInterface::getStatistics() const {
        return statistics;
    }

    // Отримати версію модуля
    // Get module version
    // Получить версию модуля
    std::string DatabaseInterface::getVersion() const {
        return version;
    }

    // Внутрішні методи
    // Internal methods
    // Внутренние методы
    void DatabaseInterface::initializeDatabaseResources() {
        // Ініціалізація ресурсів бази даних
        // Initialize database resources
        // Инициализация ресурсов базы данных
        std::cout << "[DATABASE] Initializing database resources" << std::endl;
    }

    long long DatabaseInterface::getCurrentTimeMillis() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    std::string DatabaseInterface::generateRecordId() {
        // Генерація унікального ID для запису
        // Generate unique ID for record
        // Генерация уникального ID для записи
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(100000, 999999);

        std::ostringstream id;
        id << "rec_" << dis(gen) << "_" << getCurrentTimeMillis() % 1000000;
        return id.str();
    }

    std::string DatabaseInterface::serializeRecord(const DatabaseRecord& record) {
        // Спрощена серіалізація запису
        // Simplified record serialization
        // Упрощенная сериализация записи
        std::ostringstream serialized;
        serialized << record.id << "|" << record.collection << "|" << record.timestamp << "|";
        
        for (const auto& field : record.fields) {
            serialized << field.first << "=" << field.second << ";";
        }
        
        return serialized.str();
    }

    DatabaseRecord DatabaseInterface::deserializeRecord(const std::string& serializedRecord) {
        // Реалізація десеріалізації запису
        // Implementation of record deserialization
        // Реализация десериализации записи
        DatabaseRecord record;
        
        // Розділення серіалізованого рядка
        // Split serialized string
        // Разделение сериализованной строки
        std::istringstream iss(serializedRecord);
        std::string segment;
        std::vector<std::string> segments;
        
        while (std::getline(iss, segment, '|')) {
            segments.push_back(segment);
        }
        
        // Перевірка мінімальної кількості сегментів
        // Check minimum number of segments
        // Проверка минимального количества сегментов
        if (segments.size() >= 3) {
            record.id = segments[0];
            record.collection = segments[1];
            record.timestamp = std::stoll(segments[2]);
            
            // Обробка полів
            // Process fields
            // Обработка полей
            if (segments.size() > 3) {
                std::istringstream fieldsStream(segments[3]);
                std::string fieldPair;
                
                while (std::getline(fieldsStream, fieldPair, ';')) {
                    size_t eqPos = fieldPair.find('=');
                    if (eqPos != std::string::npos) {
                        std::string key = fieldPair.substr(0, eqPos);
                        std::string value = fieldPair.substr(eqPos + 1);
                        record.fields[key] = value;
                    }
                }
            }
        }
        
        return record;
    }

    std::vector<DatabaseRecord> DatabaseInterface::filterRecords(const std::vector<DatabaseRecord>& records, 
                                                               const std::map<std::string, std::string>& filters) {
        // Реалізація фільтрації записів
        // Implementation of record filtering
        // Реализация фильтрации записей
        std::vector<DatabaseRecord> filteredRecords;
        
        // Якщо немає фільтрів, повертаємо всі записи
        // If no filters, return all records
        // Если нет фильтров, возвращаем все записи
        if (filters.empty()) {
            return records;
        }
        
        // Фільтрація записів
        // Filter records
        // Фильтрация записей
        for (const auto& record : records) {
            bool matches = true;
            
            // Перевірка всіх фільтрів
            // Check all filters
            // Проверка всех фильтров
            for (const auto& filter : filters) {
                auto it = record.fields.find(filter.first);
                if (it == record.fields.end() || it->second != filter.second) {
                    matches = false;
                    break;
                }
            }
            
            if (matches) {
                filteredRecords.push_back(record);
            }
        }
        
        return filteredRecords;
    }

    std::vector<DatabaseRecord> DatabaseInterface::sortRecords(const std::vector<DatabaseRecord>& records, 
                                                             const std::string& sortField, int sortOrder) {
        // Реалізація сортування записів
        // Implementation of record sorting
        // Реализация сортировки записей
        std::vector<DatabaseRecord> sortedRecords = records;
        
        // Сортування записів
        // Sort records
        // Сортировка записей
        std::sort(sortedRecords.begin(), sortedRecords.end(), 
                  [&sortField, &sortOrder](const DatabaseRecord& a, const DatabaseRecord& b) {
                      auto itA = a.fields.find(sortField);
                      auto itB = b.fields.find(sortField);
                      
                      // Якщо поле не знайдено в одному з записів, вважаємо його меншим
                      // If field not found in one of the records, consider it smaller
                      // Если поле не найдено в одной из записей, считаем его меньшим
                      if (itA == a.fields.end() && itB == b.fields.end()) return false;
                      if (itA == a.fields.end()) return true;
                      if (itB == b.fields.end()) return false;
                      
                      // Сортування залежно від порядку
                      // Sort depending on order
                      // Сортировка в зависимости от порядка
                      if (sortOrder > 0) {
                          return itA->second < itB->second;
                      } else {
                          return itA->second > itB->second;
                      }
                  });
        
        return sortedRecords;
    }

    std::vector<DatabaseRecord> DatabaseInterface::limitRecords(const std::vector<DatabaseRecord>& records, 
                                                              int limit, int offset) {
        // Реалізація обмеження записів
        // Implementation of record limiting
        // Реализация ограничения записей
        std::vector<DatabaseRecord> limitedRecords;
        
        // Перевірка коректності параметрів
        // Check parameter validity
        // Проверка корректности параметров
        if (offset < 0 || offset >= static_cast<int>(records.size())) {
            return limitedRecords;
        }
        
        // Визначення кінцевої позиції
        // Determine end position
        // Определение конечной позиции
        int endPos = records.size();
        if (limit > 0) {
            endPos = std::min(offset + limit, static_cast<int>(records.size()));
        }
        
        // Копіювання записів у межах обмеження
        // Copy records within limit
        // Копирование записей в пределах ограничения
        for (int i = offset; i < endPos; ++i) {
            limitedRecords.push_back(records[i]);
        }
        
        return limitedRecords;
    }

    double DatabaseInterface::calculateSimilarity(const std::string& query1, const std::string& query2) {
        // Реалізація обчислення схожості
        // Implementation of similarity calculation
        // Реализация вычисления схожести
        
        // Просте обчислення схожості на основі довжини рядків
        // Simple similarity calculation based on string lengths
        // Простое вычисление схожести на основе длины строк
        if (query1.empty() && query2.empty()) {
            return 1.0;
        }
        
        if (query1.empty() || query2.empty()) {
            return 0.0;
        }
        
        // Обчислення схожості на основі спільних символів
        // Calculate similarity based on common characters
        // Вычисление схожести на основе общих символов
        std::set<char> chars1(query1.begin(), query1.end());
        std::set<char> chars2(query2.begin(), query2.end());
        
        std::set<char> intersection;
        std::set_intersection(chars1.begin(), chars1.end(),
                              chars2.begin(), chars2.end(),
                              std::inserter(intersection, intersection.begin()));
        
        std::set<char> Union;
        std::set_union(chars1.begin(), chars1.end(),
                       chars2.begin(), chars2.end(),
                       std::inserter(Union, Union.begin()));
        
        if (Union.empty()) {
            return 1.0;
        }
        
        return static_cast<double>(intersection.size()) / Union.size();
    }

    std::vector<double> DatabaseInterface::textToVector(const std::string& text) {
        // Реалізація перетворення тексту в вектор
        // Implementation of text to vector conversion
        // Реализация преобразования текста в вектор
        std::vector<double> vector;
        
        // Просте перетворення: ASCII-значення символів
        // Simple conversion: ASCII values of characters
        // Простое преобразование: ASCII-значения символов
        for (char c : text) {
            vector.push_back(static_cast<double>(static_cast<unsigned char>(c)));
        }
        
        // Нормалізація значень
        // Normalize values
        // Нормализация значений
        for (double& value : vector) {
            value /= 255.0; // Нормалізація до діапазону [0, 1] / Normalize to range [0, 1] / Нормализация к диапазону [0, 1]
        }
        
        return vector;
    }

    std::string DatabaseInterface::vectorToText(const std::vector<double>& vector) {
        // Реалізація перетворення вектору в текст
        // Implementation of vector to text conversion
        // Реализация преобразования вектора в текст
        std::string text;
        
        // Перетворення значень вектору в символи
        // Convert vector values to characters
        // Преобразование значений вектора в символы
        for (double value : vector) {
            // Денормалізація значення
            // Denormalize value
            // Денормализация значения
            int charValue = static_cast<int>(value * 255.0);
            
            // Перевірка меж
            // Check bounds
            // Проверка границ
            charValue = std::max(0, std::min(255, charValue));
            
            // Додавання символу
            // Add character
            // Добавление символа
            text += static_cast<char>(charValue);
        }
        
        return text;
    }

} // namespace Database
} // namespace NeuroSync