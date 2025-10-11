#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"
#include <iostream>

int main() {
    std::cout << "Starting minimal test..." << std::endl;
    
    // Create neuron manager
    NeuronManager neuronManager;
    neuronManager.initialize();
    
    // Create synapse bus
    SynapseBus synapseBus;
    synapseBus.initialize();
    
    // Create neurons
    int neuron1 = neuronManager.createNeuron(nullptr);
    int neuron2 = neuronManager.createNeuron(nullptr);
    
    std::cout << "Created neurons: " << neuron1 << ", " << neuron2 << std::endl;
    
    // Create connection
    bool connected = synapseBus.createConnection(neuron1, neuron2, 1.0f);
    std::cout << "Connection created: " << (connected ? "success" : "failed") << std::endl;
    
    // Test activation
    bool activated = neuronManager.activateNeuron(neuron1);
    std::cout << "Neuron activation: " << (activated ? "success" : "failed") << std::endl;
    
    std::cout << "Minimal test completed successfully!" << std::endl;
    
    return 0;
}