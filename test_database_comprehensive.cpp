#include "src/database/DatabaseInterface.h"
#include <iostream>
#include <any>
#include <cassert>

int main() {
    std::cout << "Testing comprehensive DatabaseInterface functionality..." << std::endl;
    
    NeuroSync::Database::DatabaseInterface db;
    
    // Test initialization
    NeuroSync::Database::DatabaseConfig config;
    config.type = NeuroSync::Database::DatabaseType::SQLITE;
    config.host = "localhost";
    config.port = 5432;
    config.databaseName = "test_db";
    
    bool initialized = db.initialize(config);
    std::cout << "Database initialized: " << (initialized ? "true" : "false") << std::endl;
    assert(initialized);
    
    // Test connection
    bool connected = db.connect();
    std::cout << "Database connected: " << (connected ? "true" : "false") << std::endl;
    assert(connected);
    
    // Test simple query execution
    auto queryResult = db.executeQuery("SELECT * FROM users");
    std::cout << "Simple query executed - success: " << (queryResult.success ? "true" : "false") 
              << ", rows: " << queryResult.rowCount << std::endl;
    assert(queryResult.success);
    
    // Test parameterized query execution
    std::map<std::string, std::any> params;
    params["id"] = 123;
    params["name"] = std::string("John Doe");
    
    auto paramQueryResult = db.executeQuery("SELECT * FROM users WHERE id = ? AND name = ?", params);
    std::cout << "Parameterized query executed - success: " << (paramQueryResult.success ? "true" : "false") 
              << ", rows: " << paramQueryResult.rowCount << std::endl;
    assert(paramQueryResult.success);
    
    // Test insert operation
    std::map<std::string, std::any> testData;
    testData["id"] = 456;
    testData["name"] = std::string("Jane Smith");
    testData["email"] = std::string("jane@example.com");
    testData["age"] = 30;
    
    auto insertResult = db.insert("users", testData);
    std::cout << "Insert operation - success: " << (insertResult.success ? "true" : "false") 
              << ", affected rows: " << insertResult.affectedRows << std::endl;
    assert(insertResult.success);
    
    // Test update operation
    std::map<std::string, std::any> updateData;
    updateData["age"] = 31;
    updateData["email"] = std::string("jane.smith@example.com");
    
    auto updateResult = db.update("users", updateData, "id = 456");
    std::cout << "Update operation - success: " << (updateResult.success ? "true" : "false") 
              << ", affected rows: " << updateResult.affectedRows << std::endl;
    assert(updateResult.success);
    
    // Test select operation
    std::vector<std::string> columns = {"id", "name", "email"};
    auto selectResult = db.select("users", columns, "age > 25", "name ASC", 10, 0);
    std::cout << "Select operation - success: " << (selectResult.success ? "true" : "false") 
              << ", rows: " << selectResult.rowCount << std::endl;
    assert(selectResult.success);
    
    // Test transaction functionality
    std::string transactionId = db.beginTransaction();
    std::cout << "Transaction started with ID: " << transactionId << std::endl;
    assert(!transactionId.empty());
    
    // Perform some operations within the transaction
    std::map<std::string, std::any> transactionData;
    transactionData["id"] = 789;
    transactionData["name"] = std::string("Bob Johnson");
    transactionData["email"] = std::string("bob@example.com");
    
    auto transactionInsertResult = db.insert("users", transactionData);
    std::cout << "Transaction insert - success: " << (transactionInsertResult.success ? "true" : "false") << std::endl;
    assert(transactionInsertResult.success);
    
    // Commit the transaction
    bool committed = db.commitTransaction(transactionId);
    std::cout << "Transaction committed: " << (committed ? "true" : "false") << std::endl;
    assert(committed);
    
    // Test prepared statements
    bool prepared = db.prepareStatement("SELECT * FROM users WHERE id = ?", "select_user");
    std::cout << "Statement prepared: " << (prepared ? "true" : "false") << std::endl;
    assert(prepared);
    
    std::map<std::string, std::any> preparedParams;
    preparedParams["id"] = 456;
    
    auto preparedResult = db.executePreparedStatement("select_user", preparedParams);
    std::cout << "Prepared statement executed - success: " << (preparedResult.success ? "true" : "false") 
              << ", rows: " << preparedResult.rowCount << std::endl;
    assert(preparedResult.success);
    
    // Close the prepared statement
    db.closePreparedStatement("select_user");
    std::cout << "Prepared statement closed" << std::endl;
    
    // Test statistics
    auto stats = db.getStatistics();
    std::cout << "Database statistics:" << std::endl;
    std::cout << "  Total queries: " << stats.totalQueries << std::endl;
    std::cout << "  Successful queries: " << stats.successfulQueries << std::endl;
    std::cout << "  Failed queries: " << stats.failedQueries << std::endl;
    std::cout << "  Active connections: " << stats.activeConnections << std::endl;
    std::cout << "  Total transactions: " << stats.totalTransactions << std::endl;
    
    // Test configuration
    auto dbConfig = db.getConfiguration();
    std::cout << "Database configuration:" << std::endl;
    std::cout << "  Type: " << static_cast<int>(dbConfig.type) << std::endl;
    std::cout << "  Host: " << dbConfig.host << std::endl;
    std::cout << "  Port: " << dbConfig.port << std::endl;
    std::cout << "  Database name: " << dbConfig.databaseName << std::endl;
    
    // Test export/import functionality
    bool exported = db.exportData("users", "users_backup.csv");
    std::cout << "Data exported: " << (exported ? "true" : "false") << std::endl;
    assert(exported);
    
    bool imported = db.importData("users", "users_backup.csv");
    std::cout << "Data imported: " << (imported ? "true" : "false") << std::endl;
    assert(imported);
    
    // Test backup/restore functionality
    bool backupCreated = db.createBackup("database_backup.db");
    std::cout << "Backup created: " << (backupCreated ? "true" : "false") << std::endl;
    assert(backupCreated);
    
    bool backupRestored = db.restoreFromBackup("database_backup.db");
    std::cout << "Backup restored: " << (backupRestored ? "true" : "false") << std::endl;
    assert(backupRestored);
    
    // Test disconnection
    db.disconnect();
    std::cout << "Database disconnected" << std::endl;
    
    std::cout << "All tests passed successfully!" << std::endl;
    
    return 0;
}