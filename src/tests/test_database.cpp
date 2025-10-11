#include "../database/DatabaseInterface.h"
#include <iostream>
#include <cassert>
#include <string>
#include <map>
#include <any>

using namespace NeuroSync::Database;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync Database Interface Tests\n";
    std::cout << "========================================\n\n";
    
    // Створення інтерфейсу бази даних
    // Create database interface
    // Создание интерфейса базы данных
    DatabaseInterface dbInterface;
    
    // Тест ініціалізації
    // Test initialization
    // Тест инициализации
    std::cout << "1. Testing initialization...\n";
    DatabaseConfig config;
    config.type = DatabaseType::SQLITE;
    config.host = "localhost";
    config.port = 5432;
    config.databaseName = "test_db";
    config.username = "test_user";
    config.password = "test_password";
    config.maxConnections = 5;
    config.connectionTimeout = 15000;
    config.enableConnectionPooling = false;
    
    bool initResult = dbInterface.initialize(config);
    assert(initResult);
    std::cout << "   ✓ Initialization successful\n\n";
    
    // Тест підключення
    // Test connection
    // Тест подключения
    std::cout << "2. Testing connection...\n";
    bool connectResult = dbInterface.connect();
    assert(connectResult);
    std::cout << "   ✓ Connection successful\n\n";
    
    // Тест перевірки з'єднання
    // Test connection check
    // Тест проверки соединения
    std::cout << "3. Testing connection check...\n";
    bool isConnected = dbInterface.isConnected();
    assert(isConnected);
    std::cout << "   ✓ Connection check successful\n\n";
    
    // Тест виконання запиту
    // Test query execution
    // Тест выполнения запроса
    std::cout << "4. Testing query execution...\n";
    QueryResult result = dbInterface.executeQuery("SELECT * FROM test_table LIMIT 1");
    assert(result.success);
    std::cout << "   ✓ Query execution successful\n";
    std::cout << "   Rows returned: " << result.rowCount << "\n\n";
    
    // Тест виконання запиту з параметрами
    // Test query execution with parameters
    // Тест выполнения запроса с параметрами
    std::cout << "5. Testing query execution with parameters...\n";
    std::map<std::string, std::any> params;
    params["id"] = 1;
    params["name"] = std::string("test");
    
    QueryResult paramResult = dbInterface.executeQuery("SELECT * FROM test_table WHERE id = ? AND name = ?", params);
    assert(paramResult.success);
    std::cout << "   ✓ Query execution with parameters successful\n\n";
    
    // Тест вставки даних
    // Test data insertion
    // Тест вставки данных
    std::cout << "6. Testing data insertion...\n";
    std::map<std::string, std::any> insertData;
    insertData["name"] = std::string("TestNeuron");
    insertData["type"] = std::string("TEST");
    insertData["value"] = 123.45;
    
    QueryResult insertResult = dbInterface.insert("test_table", insertData);
    assert(insertResult.success);
    std::cout << "   ✓ Data insertion successful\n\n";
    
    // Тест оновлення даних
    // Test data update
    // Тест обновления данных
    std::cout << "7. Testing data update...\n";
    std::map<std::string, std::any> updateData;
    updateData["value"] = 543.21;
    
    QueryResult updateResult = dbInterface.update("test_table", updateData, "name = 'TestNeuron'");
    assert(updateResult.success);
    std::cout << "   ✓ Data update successful\n\n";
    
    // Тест видалення даних
    // Test data deletion
    // Тест удаления данных
    std::cout << "8. Testing data deletion...\n";
    QueryResult deleteResult = dbInterface.deleteRecord("test_table", "name = 'TestNeuron'");
    assert(deleteResult.success);
    std::cout << "   ✓ Data deletion successful\n\n";
    
    // Тест вибірки даних
    // Test data selection
    // Тест выборки данных
    std::cout << "9. Testing data selection...\n";
    std::vector<std::string> columns = {"id", "name"};
    QueryResult selectResult = dbInterface.select("test_table", columns, "id > 0", "id ASC", 5, 0);
    assert(selectResult.success);
    std::cout << "   ✓ Data selection successful\n";
    std::cout << "   Rows returned: " << selectResult.rowCount << "\n\n";
    
    // Тест транзакцій
    // Test transactions
    // Тест транзакций
    std::cout << "10. Testing transactions...\n";
    std::string transactionId = dbInterface.beginTransaction();
    assert(!transactionId.empty());
    std::cout << "   ✓ Transaction started: " << transactionId << "\n";
    
    // Виконання операцій в транзакції
    // Execute operations in transaction
    // Выполнение операций в транзакции
    std::map<std::string, std::any> transData1;
    transData1["name"] = std::string("TransTest1");
    transData1["type"] = std::string("TRANS");
    dbInterface.insert("test_table", transData1);
    
    std::map<std::string, std::any> transData2;
    transData2["name"] = std::string("TransTest2");
    transData2["type"] = std::string("TRANS");
    dbInterface.insert("test_table", transData2);
    
    // Фіксація транзакції
    // Commit transaction
    // Фиксация транзакции
    bool commitResult = dbInterface.commitTransaction(transactionId);
    assert(commitResult);
    std::cout << "   ✓ Transaction committed successfully\n\n";
    
    // Тест підготовлених запитів
    // Test prepared statements
    // Тест подготовленных запросов
    std::cout << "11. Testing prepared statements...\n";
    bool prepareResult = dbInterface.prepareStatement("SELECT * FROM test_table WHERE type = ?", "test_select");
    assert(prepareResult);
    std::cout << "   ✓ Statement prepared successfully\n";
    
    // Виконання підготовленого запиту
    // Execute prepared statement
    // Выполнение подготовленного запроса
    std::map<std::string, std::any> prepParams;
    prepParams["type"] = std::string("TRANS");
    
    QueryResult prepResult = dbInterface.executePreparedStatement("test_select", prepParams);
    assert(prepResult.success);
    std::cout << "   ✓ Prepared statement executed successfully\n";
    std::cout << "   Rows returned: " << prepResult.rowCount << "\n";
    
    // Закриття підготовленого запиту
    // Close prepared statement
    // Закрытие подготовленного запроса
    dbInterface.closePreparedStatement("test_select");
    std::cout << "   ✓ Prepared statement closed successfully\n\n";
    
    // Тест отримання статистики
    // Test getting statistics
    // Тест получения статистики
    std::cout << "12. Testing statistics retrieval...\n";
    DatabaseInterface::DatabaseStatistics stats = dbInterface.getStatistics();
    std::cout << "   ✓ Statistics retrieved successfully\n";
    std::cout << "   Total queries: " << stats.totalQueries << "\n";
    std::cout << "   Successful queries: " << stats.successfulQueries << "\n";
    std::cout << "   Failed queries: " << stats.failedQueries << "\n";
    std::cout << "   Active connections: " << stats.activeConnections << "\n";
    std::cout << "   Total transactions: " << stats.totalTransactions << "\n\n";
    
    // Тест отримання конфігурації
    // Test getting configuration
    // Тест получения конфигурации
    std::cout << "13. Testing configuration retrieval...\n";
    DatabaseConfig dbConfig = dbInterface.getConfiguration();
    assert(dbConfig.type == DatabaseType::SQLITE);
    assert(dbConfig.host == "localhost");
    assert(dbConfig.port == 5432);
    assert(dbConfig.databaseName == "test_db");
    assert(dbConfig.username == "test_user");
    assert(dbConfig.password == "test_password");
    assert(dbConfig.maxConnections == 5);
    assert(dbConfig.connectionTimeout == 15000);
    assert(dbConfig.enableConnectionPooling == false);
    std::cout << "   ✓ Configuration retrieved successfully\n\n";
    
    // Тест експорту даних
    // Test data export
    // Тест экспорта данных
    std::cout << "14. Testing data export...\n";
    bool exportResult = dbInterface.exportData("test_table", "test_backup.sql");
    assert(exportResult);
    std::cout << "   ✓ Data export successful\n\n";
    
    // Тест імпорту даних
    // Test data import
    // Тест импорта данных
    std::cout << "15. Testing data import...\n";
    bool importResult = dbInterface.importData("test_table", "test_backup.sql");
    assert(importResult);
    std::cout << "   ✓ Data import successful\n\n";
    
    // Тест створення резервної копії
    // Test backup creation
    // Тест создания резервной копии
    std::cout << "16. Testing backup creation...\n";
    bool backupResult = dbInterface.createBackup("test_backup.db");
    assert(backupResult);
    std::cout << "   ✓ Backup creation successful\n\n";
    
    // Тест відновлення з резервної копії
    // Test restore from backup
    // Тест восстановления из резервной копии
    std::cout << "17. Testing restore from backup...\n";
    bool restoreResult = dbInterface.restoreFromBackup("test_backup.db");
    assert(restoreResult);
    std::cout << "   ✓ Restore from backup successful\n\n";
    
    // Тест відключення
    // Test disconnection
    // Тест отключения
    std::cout << "18. Testing disconnection...\n";
    dbInterface.disconnect();
    bool isDisconnected = !dbInterface.isConnected();
    assert(isDisconnected);
    std::cout << "   ✓ Disconnection successful\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  All Database Interface Tests Passed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}