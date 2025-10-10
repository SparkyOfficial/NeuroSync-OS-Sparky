#ifndef NEURON_MANAGER_H
#define NEURON_MANAGER_H

// NeuronManager.h
// Менеджер нейронів для NeuroSync OS Sparky
// Neuron manager for NeuroSync OS Sparky
// Менеджер нейронів для NeuroSync OS Sparky

// TODO: Реалізувати менеджер для створення/видалення нейронів
// TODO: Implement manager for creating/deleting neurons
// TODO: Реалізувати менеджер для створення/видалення нейронів

class NeuronManager {
public:
    NeuronManager();
    ~NeuronManager();
    
    // Створити новий нейрон
    // Create a new neuron
    // Створити новий нейрон
    int createNeuron(void (*processFunction)());
    
    // Видалити нейрон
    // Delete a neuron
    // Видалити нейрон
    void deleteNeuron(int neuronId);
    
    // Отримати кількість активних нейронів
    // Get the number of active neurons
    // Отримати кількість активних нейронів
    int getActiveNeuronCount();
    
private:
    int neuronCount;
};

#endif // NEURON_MANAGER_H