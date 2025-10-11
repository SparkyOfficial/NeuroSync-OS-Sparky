#include "../database/DatabaseInterface.h"
#include <iostream>
#include <string>
#include <map>
#include <any>

using namespace NeuroSync::Database;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync Database Interface Example\n";
    std::cout << "========================================\n\n";
    
    // Створення інтерфейсу бази даних
    // Create database interface
    // Создание интерфейса базы данных
    DatabaseInterface dbInterface;
    
    // Ініціалізація бази даних
    // Initialize database
    // Инициализация базы данных
    DatabaseConfig config;
    config.type = DatabaseType::SQLITE;
    config.host = "localhost";
    config.port = 5432;
    config.databaseName = "neurosync_db";
    config.username = "user";
    config.password = "password";
    config.maxConnections = 10;
    config.connectionTimeout = 30000;
    config.enableConnectionPooling = true;
    
    std::cout << "1. Initializing database...\n";
    if (!dbInterface.initialize(config)) {
        std::cerr << "Failed to initialize database" << std::endl;
        return 1;
    }
    std::cout << "   ✓ Database initialized successfully\n\n";
    
    // Підключення до бази даних
    // Connect to database
    // Подключение к базе данных
    std::cout << "2. Connecting to database...\n";
    if (!dbInterface.connect()) {
        std::cerr << "Failed to connect to database" << std::endl;
        return 1;
    }
    std::cout << "   ✓ Connected to database successfully\n\n";
    
    // Перевірка з'єднання
    // Check connection
    // Проверка соединения
    std::cout << "3. Checking connection...\n";
    if (dbInterface.isConnected()) {
        std::cout << "   ✓ Database is connected\n\n";
    } else {
        std::cout << "   ✗ Database is not connected\n\n";
    }
    
    // Виконання простого запиту
    // Execute simple query
    // Выполнение простого запроса
    std::cout << "4. Executing simple query...\n";
    QueryResult result = dbInterface.executeQuery("SELECT * FROM neurons LIMIT 5");
    if (result.success) {
        std::cout << "   ✓ Query executed successfully\n";
        std::cout << "   Rows returned: " << result.rowCount << "\n";
        std::cout << "   Columns: ";
        for (const auto& column : result.columnNames) {
            std::cout << column << " ";
        }
        std::cout << "\n";
        
        // Виведення даних
        // Print data
        // Вывод данных
        for (const auto& row : result.rows) {
            std::cout << "   Row: ";
            for (const auto& column : result.columnNames) {
                auto it = row.find(column);
                if (it != row.end()) {
                    // Просте перетворення для демонстрації
                    // Simple conversion for demonstration
                    // Простое преобразование для демонстрации
                    try {
                        if (it->second.type() == typeid(int)) {
                            std::cout << column << "=" << std::any_cast<int>(it->second) << " ";
                        } else if (it->second.type() == typeid(double)) {
                            std::cout << column << "=" << std::any_cast<double>(it->second) << " ";
                        } else if (it->second.type() == typeid(std::string)) {
                            std::cout << column << "=" << std::any_cast<std::string>(it->second) << " ";
                        }
                    } catch (const std::exception& e) {
                        std::cout << column << "=error ";
                    }
                }
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "   ✗ Query failed: " << result.errorMessage << "\n";
    }
    std::cout << "\n";
    
    // Вставка даних
    // Insert data
    // Вставка данных
    std::cout << "5. Inserting data...\n";
    std::map<std::string, std::any> insertData;
    insertData["name"] = std::string("Neuron1");
    insertData["type"] = std::string("PROCESSING");
    insertData["activation_threshold"] = 0.5;
    insertData["created_at"] = std::string("2025-01-01 12:00:00");
    
    QueryResult insertResult = dbInterface.insert("neurons", insertData);
    if (insertResult.success) {
        std::cout << "   ✓ Data inserted successfully\n";
    } else {
        std::cout << "   ✗ Data insertion failed: " << insertResult.errorMessage << "\n";
    }
    std::cout << "\n";
    
    // Оновлення даних
    // Update data
    // Обновление данных
    std::cout << "6. Updating data...\n";
    std::map<std::string, std::any> updateData;
    updateData["activation_threshold"] = 0.75;
    
    QueryResult updateResult = dbInterface.update("neurons", updateData, "name = 'Neuron1'");
    if (updateResult.success) {
        std::cout << "   ✓ Data updated successfully\n";
    } else {
        std::cout << "   ✗ Data update failed: " << updateResult.errorMessage << "\n";
    }
    std::cout << "\n";
    
    // Видалення даних
    // Delete data
    // Удаление данных
    std::cout << "7. Deleting data...\n";
    QueryResult deleteResult = dbInterface.deleteRecord("neurons", "name = 'Neuron1'");
    if (deleteResult.success) {
        std::cout << "   ✓ Data deleted successfully\n";
    } else {
        std::cout << "   ✗ Data deletion failed: " << deleteResult.errorMessage << "\n";
    }
    std::cout << "\n";
    
    // Вибірка даних
    // Select data
    // Выборка данных
    std::cout << "8. Selecting data...\n";
    std::vector<std::string> columns = {"id", "name", "type"};
    QueryResult selectResult = dbInterface.select("neurons", columns, "", "id ASC", 10, 0);
    if (selectResult.success) {
        std::cout << "   ✓ Data selected successfully\n";
        std::cout << "   Rows returned: " << selectResult.rowCount << "\n";
    } else {
        std::cout << "   ✗ Data selection failed: " << selectResult.errorMessage << "\n";
    }
    std::cout << "\n";
    
    // Створення транзакції
    // Begin transaction
    // Начало транзакции
    std::cout << "9. Beginning transaction...\n";
    std::string transactionId = dbInterface.beginTransaction();
    if (!transactionId.empty()) {
        std::cout << "   ✓ Transaction started: " << transactionId << "\n";
        
        // Виконання операцій в транзакції
        // Execute operations in transaction
        // Выполнение операций в транзакции
        std::map<std::string, std::any> transData1;
        transData1["name"] = std::string("TransNeuron1");
        transData1["type"] = std::string("INPUT");
        dbInterface.insert("neurons", transData1);
        
        std::map<std::string, std::any> transData2;
        transData2["name"] = std::string("TransNeuron2");
        transData2["type"] = std::string("OUTPUT");
        dbInterface.insert("neurons", transData2);
        
        // Фіксація транзакції
        // Commit transaction
        // Фиксация транзакции
        std::cout << "10. Committing transaction...\n";
        if (dbInterface.commitTransaction(transactionId)) {
            std::cout << "   ✓ Transaction committed successfully\n";
        } else {
            std::cout << "   ✗ Transaction commit failed\n";
        }
    } else {
        std::cout << "   ✗ Failed to start transaction\n";
    }
    std::cout << "\n";
    
    // Підготовка запиту
    // Prepare statement
    // Подготовка запроса
    std::cout << "11. Preparing statement...\n";
    if (dbInterface.prepareStatement("SELECT * FROM neurons WHERE type = ?", "select_by_type")) {
        std::cout << "   ✓ Statement prepared successfully\n";
        
        // Виконання підготовленого запиту
        // Execute prepared statement
        // Выполнение подготовленного запроса
        std::cout << "12. Executing prepared statement...\n";
        std::map<std::string, std::any> params;
        params["type"] = std::string("PROCESSING");
        
        QueryResult preparedResult = dbInterface.executePreparedStatement("select_by_type", params);
        if (preparedResult.success) {
            std::cout << "   ✓ Prepared statement executed successfully\n";
            std::cout << "   Rows returned: " << preparedResult.rowCount << "\n";
        } else {
            std::cout << "   ✗ Prepared statement execution failed: " << preparedResult.errorMessage << "\n";
        }
        
        // Закриття підготовленого запиту
        // Close prepared statement
        // Закрытие подготовленного запроса
        dbInterface.closePreparedStatement("select_by_type");
        std::cout << "   ✓ Prepared statement closed\n";
    } else {
        std::cout << "   ✗ Statement preparation failed\n";
    }
    std::cout << "\n";
    
    // Отримання статистики
    // Get statistics
    // Получение статистики
    std::cout << "13. Getting database statistics...\n";
    DatabaseInterface::DatabaseStatistics stats = dbInterface.getStatistics();
    std::cout << "   ✓ Statistics retrieved successfully\n";
    std::cout << "   Total queries: " << stats.totalQueries << "\n";
    std::cout << "   Successful queries: " << stats.successfulQueries << "\n";
    std::cout << "   Failed queries: " << stats.failedQueries << "\n";
    std::cout << "   Active connections: " << stats.activeConnections << "\n";
    std::cout << "   Total transactions: " << stats.totalTransactions << "\n";
    std::cout << "   Average query time: " << stats.averageQueryTime << " ms\n";
    std::cout << "   Max query time: " << stats.maxQueryTime << " ms\n\n";
    
    // Отримання конфігурації
    // Get configuration
    // Получение конфигурации
    std::cout << "14. Getting database configuration...\n";
    DatabaseConfig dbConfig = dbInterface.getConfiguration();
    std::cout << "   ✓ Configuration retrieved successfully\n";
    std::cout << "   Database type: " << static_cast<int>(dbConfig.type) << "\n";
    std::cout << "   Host: " << dbConfig.host << "\n";
    std::cout << "   Port: " << dbConfig.port << "\n";
    std::cout << "   Database name: " << dbConfig.databaseName << "\n";
    std::cout << "   Max connections: " << dbConfig.maxConnections << "\n";
    std::cout << "   Connection timeout: " << dbConfig.connectionTimeout << " ms\n";
    std::cout << "   Connection pooling: " << (dbConfig.enableConnectionPooling ? "enabled" : "disabled") << "\n\n";
    
    // Експорт даних
    // Export data
    // Экспорт данных
    std::cout << "15. Exporting data...\n";
    if (dbInterface.exportData("neurons", "neurons_backup.sql")) {
        std::cout << "   ✓ Data exported successfully to neurons_backup.sql\n";
    } else {
        std::cout << "   ✗ Data export failed\n";
    }
    std::cout << "\n";
    
    // Імпорт даних
    // Import data
    // Импорт данных
    std::cout << "16. Importing data...\n";
    if (dbInterface.importData("neurons", "neurons_backup.sql")) {
        std::cout << "   ✓ Data imported successfully from neurons_backup.sql\n";
    } else {
        std::cout << "   ✗ Data import failed\n";
    }
    std::cout << "\n";
    
    // Створення резервної копії
    // Create backup
    // Создание резервной копии
    std::cout << "17. Creating backup...\n";
    if (dbInterface.createBackup("database_backup.db")) {
        std::cout << "   ✓ Database backup created successfully\n";
    } else {
        std::cout << "   ✗ Database backup creation failed\n";
    }
    std::cout << "\n";
    
    // Відновлення з резервної копії
    // Restore from backup
    // Восстановление из резервной копии
    std::cout << "18. Restoring from backup...\n";
    if (dbInterface.restoreFromBackup("database_backup.db")) {
        std::cout << "   ✓ Database restored from backup successfully\n";
    } else {
        std::cout << "   ✗ Database restoration from backup failed\n";
    }
    std::cout << "\n";
    
    // Відключення від бази даних
    // Disconnect from database
    // Отключение от базы данных
    std::cout << "19. Disconnecting from database...\n";
    dbInterface.disconnect();
    std::cout << "   ✓ Disconnected from database successfully\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  Database Interface Example Completed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}