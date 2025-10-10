#include "NeuronManager.h"

// NeuronManager.cpp
// Реалізація менеджера нейронів для NeuroSync OS Sparky
// Implementation of neuron manager for NeuroSync OS Sparky
// Реалізація менеджера нейронів для NeuroSync OS Sparky

NeuronManager::NeuronManager() : neuronCount(0) {
    // TODO: Ініціалізація менеджера нейронів
    // TODO: Initialize neuron manager
    // TODO: Ініціалізувати менеджер нейронів
}

NeuronManager::~NeuronManager() {
    // TODO: Очищення ресурсів менеджера нейронів
    // TODO: Clean up neuron manager resources
    // TODO: Очистити ресурси менеджера нейронів
}

int NeuronManager::createNeuron(void (*processFunction)()) {
    // TODO: Створити новий нейрон з вказаною функцією обробки
    // TODO: Create a new neuron with the specified processing function
    // TODO: Створити новий нейрон з вказаною функцією обробки
    neuronCount++;
    return neuronCount; // Повертаємо ID нейрона / Return neuron ID / Повертаємо ID нейрона
}

void NeuronManager::deleteNeuron(int neuronId) {
    // TODO: Видалити нейрон з вказаним ID
    // TODO: Delete neuron with specified ID
    // TODO: Видалити нейрон з вказаним ID
    if (neuronCount > 0) {
        neuronCount--;
    }
}

int NeuronManager::getActiveNeuronCount() {
    // TODO: Повернути кількість активних нейронів
    // TODO: Return the number of active neurons
    // TODO: Повернути кількість активних нейронів
    return neuronCount;
}