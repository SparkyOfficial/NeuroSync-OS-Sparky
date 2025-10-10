#ifndef NEURON_MANAGER_H
#define NEURON_MANAGER_H

#include "lifecycle/NeuronLifecycleManager.h"
#include "models/NeuronModel.h"

// NeuronManager.h
// Менеджер нейронів для NeuroSync OS Sparky
// Neuron manager for NeuroSync OS Sparky
// Менеджер нейронів для NeuroSync OS Sparky

class NeuronManager {
public:
    NeuronManager();
    ~NeuronManager();
    
    // Ініціалізація менеджера нейронів
    // Initialize neuron manager
    // Ініціалізація менеджера нейронів
    bool initialize();
    
    // Створити новий нейрон
    // Create a new neuron
    // Створити новий нейрон
    int createNeuron(void (*processFunction)());
    
    // Створити новий нейрон з параметрами
    // Create a new neuron with parameters
    // Створити новий нейрон з параметрами
    int createNeuron(NeuroSync::Neuron::Models::NeuronType type, const std::string& name);
    
    // Видалити нейрон
    // Delete a neuron
    // Видалити нейрон
    bool deleteNeuron(int neuronId);
    
    // Активувати нейрон
    // Activate a neuron
    // Активувати нейрон
    bool activateNeuron(int neuronId);
    
    // Деактивувати нейрон
    // Deactivate a neuron
    // Деактивувати нейрон
    bool deactivateNeuron(int neuronId);
    
    // Отримати кількість активних нейронів
    // Get the number of active neurons
    // Отримати кількість активних нейронів
    int getActiveNeuronCount();
    
    // Отримати загальну кількість нейронів
    // Get the total number of neurons
    // Отримати загальну кількість нейронів
    int getTotalNeuronCount();
    
    // Додати зв'язок між нейронами
    // Add connection between neurons
    // Додати зв'язок між нейронами
    bool addConnection(int sourceNeuronId, int targetNeuronId, double weight);
    
    // Видалити зв'язок між нейронами
    // Remove connection between neurons
    // Видалити зв'язок між нейронами
    bool removeConnection(int sourceNeuronId, int targetNeuronId);
    
    // Оновити вагу зв'язку
    // Update connection weight
    // Оновити вагу зв'язку
    bool updateConnectionWeight(int sourceNeuronId, int targetNeuronId, double weight);
    
private:
    // Розширений менеджер життєвого циклу нейронів
    // Advanced neuron lifecycle manager
    // Розширений менеджер життєвого циклу нейронів
    NeuroSync::Neuron::Lifecycle::NeuronLifecycleManager lifecycleManager;
};

#endif // NEURON_MANAGER_H