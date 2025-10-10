#include "src/api/NeuroAPI.h"
#include <iostream>
#include <cstring>
#include <cstddef>

int main() {
    std::cout << "Testing Basic API Functions..." << std::endl;
    
    // Initialize system
    neurosync_init();
    std::cout << "System initialized successfully" << std::endl;
    
    // Test basic neuron creation
    int neuron_id = neurosync_create_neuron(nullptr);
    std::cout << "Created basic neuron with ID: " << neuron_id << std::endl;
    
    // Test advanced neuron creation
    int advanced_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_HIDDEN, "TestNeuron");
    std::cout << "Created advanced neuron with ID: " << advanced_neuron << std::endl;
    
    // Test neuron activation
    bool activate_result = neurosync_activate_neuron(advanced_neuron);
    std::cout << "Neuron activation result: " << (activate_result ? "success" : "failure") << std::endl;
    
    // Test neuron deactivation
    bool deactivate_result = neurosync_deactivate_neuron(advanced_neuron);
    std::cout << "Neuron deactivation result: " << (deactivate_result ? "success" : "failure") << std::endl;
    
    // Test neuron statistics
    int active_count = neurosync_get_active_neuron_count();
    int total_count = neurosync_get_total_neuron_count();
    std::cout << "Neuron counts - active: " << active_count << ", total: " << total_count << std::endl;
    
    // Test connection creation
    bool conn_result = neurosync_create_connection(neuron_id, advanced_neuron, 1);
    std::cout << "Connection creation result: " << (conn_result ? "success" : "failure") << std::endl;
    
    // Test connection management
    bool update_result = neurosync_update_connection_weight(neuron_id, advanced_neuron, 0.8);
    std::cout << "Connection weight update result: " << (update_result ? "success" : "failure") << std::endl;
    
    double weight = neurosync_get_connection_weight(neuron_id, advanced_neuron);
    std::cout << "Connection weight: " << weight << std::endl;
    
    // Test connection activation/deactivation
    bool activate_conn = neurosync_activate_connection(neuron_id, advanced_neuron);
    std::cout << "Connection activation result: " << (activate_conn ? "success" : "failure") << std::endl;
    
    bool deactivate_conn = neurosync_deactivate_connection(neuron_id, advanced_neuron);
    std::cout << "Connection deactivation result: " << (deactivate_conn ? "success" : "failure") << std::endl;
    
    // Test connection statistics
    size_t conn_count = neurosync_get_connection_count();
    std::cout << "Connection count: " << conn_count << std::endl;
    
    // Test message sending
    const char* message = "Test message";
    bool send_result = neurosync_send_message(neuron_id, advanced_neuron,
                                           (void*)message, strlen(message) + 1,
                                           1, 1);
    std::cout << "Message sending result: " << (send_result ? "success" : "failure") << std::endl;
    
    // Test advanced message sending
    bool send_advanced_result = neurosync_send_message_advanced(neuron_id, advanced_neuron,
                                                             message, strlen(message) + 1,
                                                             MESSAGE_PRIORITY_NORMAL, 1.0);
    std::cout << "Advanced message sending result: " << (send_advanced_result ? "success" : "failure") << std::endl;
    
    // Test message queue statistics
    size_t queue_size = neurosync_get_message_queue_size();
    std::cout << "Message queue size: " << queue_size << std::endl;
    
    // Test system statistics
    NeuroSyncSystemStatistics stats = neurosync_get_system_statistics();
    std::cout << "System statistics retrieved successfully" << std::endl;
    std::cout << "  Total messages sent: " << stats.totalMessagesSent << std::endl;
    std::cout << "  Total connections: " << stats.totalConnections << std::endl;
    
    // Test neuron cleanup
    neurosync_delete_neuron(neuron_id);
    neurosync_delete_neuron(advanced_neuron);
    std::cout << "Neurons deleted successfully" << std::endl;
    
    std::cout << "Basic API test completed successfully!" << std::endl;
    return 0;
}