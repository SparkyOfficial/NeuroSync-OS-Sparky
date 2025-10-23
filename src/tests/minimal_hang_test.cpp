#include "../NeuroSync.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "Starting minimal hang test..." << std::endl;
    
    // Initialize the system
    neurosync_init();
    
    std::cout << "System initialized" << std::endl;
    
    // Create two neurons
    int neuron1 = neurosync_create_neuron(nullptr);
    int neuron2 = neurosync_create_neuron(nullptr);
    
    std::cout << "Created neurons: " << neuron1 << " and " << neuron2 << std::endl;
    
    // Create a connection
    bool connectionResult = neurosync_create_connection(neuron1, neuron2, 50);
    std::cout << "Connection result: " << (connectionResult ? "success" : "failure") << std::endl;
    
    // Send a message
    const char* testMessage = "Hello, Neuron!";
    std::cout << "Sending message..." << std::endl;
    bool messageResult = neurosync_send_message(neuron1, neuron2, (void*)testMessage, strlen(testMessage) + 1, 1, 50);
    std::cout << "Message send result: " << (messageResult ? "success" : "failure") << std::endl;
    
    // Wait a bit for processing
    std::cout << "Waiting for message processing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Done waiting." << std::endl;
    
    // Clean up
    std::cout << "Cleaning up..." << std::endl;
    neurosync_delete_neuron(neuron1);
    neurosync_delete_neuron(neuron2);
    std::cout << "Stopping system..." << std::endl;
    neurosync_stop();
    std::cout << "System stopped." << std::endl;
    
    std::cout << "Test completed successfully!" << std::endl;
    
    return 0;
}