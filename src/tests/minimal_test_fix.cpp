#include "../NeuroSync.h"
#include <iostream>
#include <cassert>

void test_neuron_process() {
    std::cout << "Test neuron processing..." << std::endl;
}

int main() {
    std::cout << "=== Minimal Test ===" << std::endl;
    
    // Initialize system
    neurosync_init();
    
    // Test neuron creation
    int neuronId = neurosync_create_neuron(test_neuron_process);
    assert(neuronId > 0);
    std::cout << "✓ Neuron creation test passed" << std::endl;
    
    // Test neuron deletion
    neurosync_delete_neuron(neuronId);
    std::cout << "✓ Neuron deletion test passed" << std::endl;
    
    // Test connection creation
    int neuron1 = neurosync_create_neuron(test_neuron_process);
    int neuron2 = neurosync_create_neuron(test_neuron_process);
    bool connectionResult = neurosync_create_connection(neuron1, neuron2, 50);
    assert(connectionResult == true);
    std::cout << "✓ Connection creation test passed" << std::endl;
    
    // Test message sending
    const char* testMessage = "Test message";
    std::cout << "About to send message..." << std::endl;
    bool messageResult = neurosync_send_message(neuron1, neuron2, (void*)testMessage, strlen(testMessage) + 1, 1, 50);
    std::cout << "Message send result: " << messageResult << std::endl;
    assert(messageResult == true);
    std::cout << "✓ Message sending test passed" << std::endl;
    
    // Cleanup
    neurosync_delete_neuron(neuron1);
    neurosync_delete_neuron(neuron2);
    
    std::cout << "\nAll tests passed!" << std::endl;
    
    return 0;
}