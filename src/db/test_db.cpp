#include "DatabaseInterface.h"
#include <iostream>

using namespace NeuroSync::Database;

int main() {
    std::cout << "Testing Database Interface Module" << std::endl;
    
    // Create database interface
    DatabaseInterface dbInterface;
    
    // Initialize
    if (dbInterface.initialize()) {
        std::cout << "Database interface initialized successfully" << std::endl;
    } else {
        std::cerr << "Failed to initialize database interface" << std::endl;
        return 1;
    }
    
    // Connect to database
    if (dbInterface.connect("test_connection")) {
        std::cout << "Connected to database successfully" << std::endl;
    } else {
        std::cerr << "Failed to connect to database" << std::endl;
        return 1;
    }
    
    // Create a collection
    if (dbInterface.createCollection("test_collection")) {
        std::cout << "Collection created successfully" << std::endl;
    } else {
        std::cerr << "Failed to create collection" << std::endl;
        return 1;
    }
    
    // Insert a record
    DatabaseRecord record;
    record.id = "test_record_1";
    record.collection = "test_collection";
    record.fields["name"] = "Test Record";
    record.fields["value"] = "123.45";
    
    if (dbInterface.insertRecord(record)) {
        std::cout << "Record inserted successfully" << std::endl;
    } else {
        std::cerr << "Failed to insert record" << std::endl;
        return 1;
    }
    
    // Select records
    DatabaseQuery query;
    query.collection = "test_collection";
    
    QueryResult result = dbInterface.selectRecords(query);
    if (result.success) {
        std::cout << "Selected " << result.records.size() << " records" << std::endl;
        for (const auto& record : result.records) {
            std::cout << "Record ID: " << record.id << std::endl;
            for (const auto& field : record.fields) {
                std::cout << "  " << field.first << ": " << field.second << std::endl;
            }
        }
    } else {
        std::cerr << "Failed to select records: " << result.errorMessage << std::endl;
        return 1;
    }
    
    // Get statistics
    auto stats = dbInterface.getStatistics();
    std::cout << "Total queries executed: " << stats.totalQueriesExecuted << std::endl;
    std::cout << "Total records inserted: " << stats.totalRecordsInserted << std::endl;
    
    // Disconnect
    dbInterface.disconnect();
    std::cout << "Disconnected from database" << std::endl;
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}