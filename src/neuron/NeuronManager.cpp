#include "NeuronManager.h"
#include <string>

// NeuronManager.cpp
// Реалізація менеджера нейронів для NeuroSync OS Sparky
// Implementation of neuron manager for NeuroSync OS Sparky
// Реалізація менеджера нейронів для NeuroSync OS Sparky

NeuronManager::NeuronManager() {
    // Ініціалізація менеджера нейронів
    // Initialize neuron manager
    // Ініціалізація менеджера нейронів
    lifecycleManager.initialize();
}

NeuronManager::~NeuronManager() {
    // Очищення ресурсів менеджера нейронів
    // Clean up neuron manager resources
    // Очистити ресурси менеджера нейронів
}

bool NeuronManager::initialize() {
    // Ініціалізація менеджера нейронів
    // Initialize neuron manager
    // Ініціалізація менеджера нейронів
    return lifecycleManager.initialize();
}

int NeuronManager::createNeuron(void (*processFunction)()) {
    // Створити новий нейрон з вказаною функцією обробки
    // Create a new neuron with the specified processing function
    // Створити новий нейрон з вказаною функцією обробки
    static int neuronCounter = 0;
    std::string name = "Neuron_" + std::to_string(++neuronCounter);
    return lifecycleManager.createNeuron(NeuroSync::Neuron::Models::NeuronType::PROCESSING, name);
}

int NeuronManager::createNeuron(NeuroSync::Neuron::Models::NeuronType type, const std::string& name) {
    // Створити новий нейрон з параметрами
    // Create a new neuron with parameters
    // Створити новий нейрон з параметрами
    return lifecycleManager.createNeuron(type, name);
}

bool NeuronManager::deleteNeuron(int neuronId) {
    // Видалити нейрон з вказаним ID
    // Delete neuron with specified ID
    // Видалити нейрон з вказаним ID
    return lifecycleManager.deleteNeuron(neuronId);
}

bool NeuronManager::activateNeuron(int neuronId) {
    // Активувати нейрон
    // Activate a neuron
    // Активувати нейрон
    return lifecycleManager.activateNeuron(neuronId);
}

bool NeuronManager::deactivateNeuron(int neuronId) {
    // Деактивувати нейрон
    // Deactivate a neuron
    // Деактивувати нейрон
    return lifecycleManager.deactivateNeuron(neuronId);
}

int NeuronManager::getActiveNeuronCount() {
    // Повернути кількість активних нейронів
    // Return the number of active neurons
    // Повернути кількість активних нейронів
    return static_cast<int>(lifecycleManager.getActiveNeuronCount());
}

int NeuronManager::getTotalNeuronCount() {
    // Повернути загальну кількість нейронів
    // Return the total number of neurons
    // Повернути загальну кількість нейронів
    return static_cast<int>(lifecycleManager.getNeuronCount());
}

bool NeuronManager::addConnection(int sourceNeuronId, int targetNeuronId, double weight) {
    // Додати зв'язок між нейронами
    // Add connection between neurons
    // Додати зв'язок між нейронами
    return lifecycleManager.addConnection(sourceNeuronId, targetNeuronId, weight);
}

bool NeuronManager::removeConnection(int sourceNeuronId, int targetNeuronId) {
    // Видалити зв'язок між нейронами
    // Remove connection between neurons
    // Видалити зв'язок між нейронами
    return lifecycleManager.removeConnection(sourceNeuronId, targetNeuronId);
}

bool NeuronManager::updateConnectionWeight(int sourceNeuronId, int targetNeuronId, double weight) {
    // Оновити вагу зв'язку
    // Update connection weight
    // Оновити вагу зв'язку
    return lifecycleManager.updateConnectionWeight(sourceNeuronId, targetNeuronId, weight);
}