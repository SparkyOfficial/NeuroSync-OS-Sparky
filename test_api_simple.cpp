#include "src/api/NeuroAPI.h"
#include <iostream>
#include <cstring>
#include <cstddef>

int main() {
    std::cout << "Testing Enhanced API..." << std::endl;
    
    try {
        // Initialize system
        neurosync_init();
        std::cout << "System initialized successfully" << std::endl;
        
        // Create advanced neurons
        int input_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_INPUT, "TestInput");
        int hidden_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_HIDDEN, "TestHidden");
        std::cout << "Created neurons: input=" << input_neuron << ", hidden=" << hidden_neuron << std::endl;
        
        // Create connection
        bool conn_result = neurosync_create_connection(input_neuron, hidden_neuron, 1);
        std::cout << "Connection creation result: " << (conn_result ? "success" : "failure") << std::endl;
        
        // Activate neurons
        bool activate_result = neurosync_activate_neuron(input_neuron);
        std::cout << "Neuron activation result: " << (activate_result ? "success" : "failure") << std::endl;
        
        // Send message
        const char* message = "Test message";
        bool send_result = neurosync_send_message_advanced(input_neuron, hidden_neuron,
                                                        message, strlen(message) + 1,
                                                        MESSAGE_PRIORITY_NORMAL, 1.0);
        std::cout << "Message sending result: " << (send_result ? "success" : "failure") << std::endl;
        
        // Get statistics
        int active_count = neurosync_get_active_neuron_count();
        int total_count = neurosync_get_total_neuron_count();
        std::cout << "Neuron counts - active: " << active_count << ", total: " << total_count << std::endl;
        
        // Get connection count
        size_t conn_count = neurosync_get_connection_count();
        std::cout << "Connection count: " << conn_count << std::endl;
        
        // Get message queue size
        size_t queue_size = neurosync_get_message_queue_size();
        std::cout << "Message queue size: " << queue_size << std::endl;
        
        // Get system statistics
        NeuroSyncSystemStatistics stats = neurosync_get_system_statistics();
        std::cout << "System statistics retrieved successfully" << std::endl;
        
        // Cleanup
        neurosync_delete_neuron(input_neuron);
        neurosync_delete_neuron(hidden_neuron);
        std::cout << "Neurons deleted successfully" << std::endl;
        
        std::cout << "Enhanced API test completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}