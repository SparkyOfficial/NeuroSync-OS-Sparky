#include "src/database/DatabaseInterface.h"
#include <iostream>
#include <any>

int main() {
    std::cout << "Testing DatabaseInterface compilation..." << std::endl;
    
    NeuroSync::Database::DatabaseInterface db;
    
    NeuroSync::Database::DatabaseConfig config;
    config.type = NeuroSync::Database::DatabaseType::SQLITE;
    config.host = "localhost";
    config.port = 5432;
    config.databaseName = "test_db";
    
    bool initialized = db.initialize(config);
    std::cout << "Database initialized: " << (initialized ? "true" : "false") << std::endl;
    
    bool connected = db.connect();
    std::cout << "Database connected: " << (connected ? "true" : "false") << std::endl;
    
    // Test std::any usage
    std::map<std::string, std::any> testData;
    testData["id"] = 123;
    testData["name"] = std::string("test");
    testData["value"] = 45.67;
    
    auto result = db.insert("test_table", testData);
    std::cout << "Insert result - success: " << (result.success ? "true" : "false") 
              << ", rows: " << result.rowCount << std::endl;
    
    db.disconnect();
    std::cout << "Database disconnected" << std::endl;
    
    return 0;
}