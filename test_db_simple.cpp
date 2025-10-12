#include "src/db/DatabaseInterface.h"
#include <iostream>
#include <cassert>

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
    
    // Test record serialization/deserialization
    DatabaseRecord originalRecord;
    originalRecord.id = "test_record_1";
    originalRecord.collection = "test_collection";
    originalRecord.fields["name"] = "Test Record";
    originalRecord.fields["value"] = "123.45";
    originalRecord.timestamp = 1234567890;
    
    // Serialize record
    std::string serialized = dbInterface.serializeRecord(originalRecord);
    std::cout << "Serialized record: " << serialized << std::endl;
    
    // Deserialize record
    DatabaseRecord deserializedRecord = dbInterface.deserializeRecord(serialized);
    
    // Verify deserialization
    assert(deserializedRecord.id == originalRecord.id);
    assert(deserializedRecord.collection == originalRecord.collection);
    assert(deserializedRecord.fields["name"] == originalRecord.fields["name"]);
    assert(deserializedRecord.fields["value"] == originalRecord.fields["value"]);
    assert(deserializedRecord.timestamp == originalRecord.timestamp);
    std::cout << "Serialization/Deserialization test passed" << std::endl;
    
    // Test text to vector conversion
    std::string testText = "Hello World";
    std::vector<double> vector = dbInterface.textToVector(testText);
    std::string restoredText = dbInterface.vectorToText(vector);
    
    std::cout << "Original text: " << testText << std::endl;
    std::cout << "Restored text: " << restoredText << std::endl;
    std::cout << "Text conversion test completed" << std::endl;
    
    // Test similarity calculation
    double similarity = dbInterface.calculateSimilarity("hello", "hello");
    std::cout << "Similarity of 'hello' and 'hello': " << similarity << std::endl;
    
    similarity = dbInterface.calculateSimilarity("hello", "world");
    std::cout << "Similarity of 'hello' and 'world': " << similarity << std::endl;
    
    // Test record filtering
    std::vector<DatabaseRecord> testRecords;
    for (int i = 0; i < 5; ++i) {
        DatabaseRecord record;
        record.id = "record_" + std::to_string(i);
        record.collection = "test_collection";
        record.fields["name"] = "Record " + std::to_string(i);
        record.fields["category"] = (i % 2 == 0) ? "even" : "odd";
        record.timestamp = 1234567890 + i;
        testRecords.push_back(record);
    }
    
    std::map<std::string, std::string> filters;
    filters["category"] = "even";
    std::vector<DatabaseRecord> filteredRecords = dbInterface.filterRecords(testRecords, filters);
    std::cout << "Filtered records count: " << filteredRecords.size() << std::endl;
    
    // Test record sorting
    std::vector<DatabaseRecord> sortedRecords = dbInterface.sortRecords(testRecords, "name", 1);
    std::cout << "Sorted records count: " << sortedRecords.size() << std::endl;
    
    // Test record limiting
    std::vector<DatabaseRecord> limitedRecords = dbInterface.limitRecords(testRecords, 3, 1);
    std::cout << "Limited records count: " << limitedRecords.size() << std::endl;
    
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