#include "../NeuroSync.h"
#include <iostream>
#include <cassert>
#include <cstring>

void test_neuron_process() {
    // Empty function for testing
}

int main() {
    // Initialize system
    neurosync_init();
    
    // Test neuron creation
    int neuronId = neurosync_create_neuron(test_neuron_process);
    assert(neuronId > 0);
    
    // Test neuron deletion
    neurosync_delete_neuron(neuronId);
    
    // Test connection creation
    int neuron1 = neurosync_create_neuron(test_neuron_process);
    int neuron2 = neurosync_create_neuron(test_neuron_process);
    bool connectionResult = neurosync_create_connection(neuron1, neuron2, 50);
    assert(connectionResult == true);
    
    // Test message sending
    const char* testMessage = "Test message";
    bool messageResult = neurosync_send_message(neuron1, neuron2, (void*)testMessage, strlen(testMessage) + 1, 1, 50);
    assert(messageResult == true);
    
    // Cleanup
    neurosync_delete_neuron(neuron1);
    neurosync_delete_neuron(neuron2);
    
    // Stop the system to terminate message processing thread
    neurosync_stop();
    
    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}