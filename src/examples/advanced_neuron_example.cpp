#include "../NeuroSync.h"
#include "../neuron/NeuronManager.h"
#include "../neuron/utils/NeuronUtils.h"
#include "../neuron/lifecycle/NeuronLifecycleManager.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// advanced_neuron_example.cpp
// Пример использования расширенного менеджера нейронов NeuroSync OS Sparky
// Example of using advanced neuron manager in NeuroSync OS Sparky
// Приклад використання розширеного менеджера нейронів NeuroSync OS Sparky

using namespace NeuroSync::Neuron;
using namespace NeuroSync::Neuron::Models;
using namespace NeuroSync::Neuron::Lifecycle;
using namespace NeuroSync::Neuron::Utils;

// Функции обработки для нейронов
// Processing functions for neurons
// Функції обробки для нейронів

void inputNeuronProcess() {
    std::cout << "[INPUT NEURON] Processing input data..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "[INPUT NEURON] Input processing complete." << std::endl;
}

void hiddenNeuronProcess() {
    std::cout << "[HIDDEN NEURON] Processing hidden data..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "[HIDDEN NEURON] Hidden processing complete." << std::endl;
}

void outputNeuronProcess() {
    std::cout << "[OUTPUT NEURON] Generating output..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    std::cout << "[OUTPUT NEURON] Output generation complete." << std::endl;
}

void processingNeuronProcess() {
    std::cout << "[PROCESSING NEURON] Performing complex processing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(125));
    std::cout << "[PROCESSING NEURON] Complex processing complete." << std::endl;
}

int main() {
    std::cout << "=== NeuroSync OS Sparky Advanced Neuron Example ===" << std::endl;
    std::cout << "=== Приклад розширеного нейрона NeuroSync OS Sparky ===" << std::endl;
    std::cout << "=== Пример расширенного нейрона NeuroSync OS Sparky ===" << std::endl;
    
    // Создание менеджера нейронов
    // Creating neuron manager
    // Створення менеджера нейронів
    NeuronManager neuronManager;
    
    // Инициализация менеджера нейронов
    // Initialize neuron manager
    // Ініціалізація менеджера нейронів
    if (!neuronManager.initialize()) {
        std::cerr << "Failed to initialize neuron manager!" << std::endl;
        return 1;
    }
    
    std::cout << "Neuron manager initialized." << std::endl;
    std::cout << "Менеджер нейронів ініціалізовано." << std::endl;
    std::cout << "Менеджер нейронов инициализирован." << std::endl;
    
    // Создание различных типов нейронов
    // Creating different types of neurons
    // Створення різних типів нейронів
    std::cout << "\nCreating neurons..." << std::endl;
    std::cout << "Створення нейронів..." << std::endl;
    std::cout << "Создание нейронов..." << std::endl;
    
    int inputNeuron1 = neuronManager.createNeuron(NeuronType::INPUT, "Input_Neuron_1");
    int inputNeuron2 = neuronManager.createNeuron(NeuronType::INPUT, "Input_Neuron_2");
    int hiddenNeuron1 = neuronManager.createNeuron(NeuronType::HIDDEN, "Hidden_Neuron_1");
    int hiddenNeuron2 = neuronManager.createNeuron(NeuronType::HIDDEN, "Hidden_Neuron_2");
    int outputNeuron1 = neuronManager.createNeuron(NeuronType::OUTPUT, "Output_Neuron_1");
    int processingNeuron1 = neuronManager.createNeuron(NeuronType::PROCESSING, "Processing_Neuron_1");
    
    std::cout << "Created neurons with IDs: " << inputNeuron1 << ", " << inputNeuron2 << ", " 
              << hiddenNeuron1 << ", " << hiddenNeuron2 << ", " << outputNeuron1 << ", " << processingNeuron1 << std::endl;
    
    // Активация нейронов
    // Activating neurons
    // Активація нейронів
    std::cout << "\nActivating neurons..." << std::endl;
    std::cout << "Активація нейронів..." << std::endl;
    std::cout << "Активация нейронов..." << std::endl;
    
    neuronManager.activateNeuron(inputNeuron1);
    neuronManager.activateNeuron(inputNeuron2);
    neuronManager.activateNeuron(hiddenNeuron1);
    neuronManager.activateNeuron(hiddenNeuron2);
    neuronManager.activateNeuron(outputNeuron1);
    neuronManager.activateNeuron(processingNeuron1);
    
    std::cout << "Neurons activated." << std::endl;
    std::cout << "Нейрони активовано." << std::endl;
    std::cout << "Нейроны активированы." << std::endl;
    
    // Создание связей между нейронами
    // Creating connections between neurons
    // Створення зв'язків між нейронами
    std::cout << "\nCreating connections..." << std::endl;
    std::cout << "Створення зв'язків..." << std::endl;
    std::cout << "Создание связей..." << std::endl;
    
    neuronManager.addConnection(inputNeuron1, hiddenNeuron1, 0.8);
    neuronManager.addConnection(inputNeuron2, hiddenNeuron1, 0.6);
    neuronManager.addConnection(inputNeuron1, hiddenNeuron2, 0.7);
    neuronManager.addConnection(inputNeuron2, hiddenNeuron2, 0.9);
    neuronManager.addConnection(hiddenNeuron1, outputNeuron1, 0.85);
    neuronManager.addConnection(hiddenNeuron2, outputNeuron1, 0.75);
    neuronManager.addConnection(inputNeuron1, processingNeuron1, 0.5);
    neuronManager.addConnection(processingNeuron1, outputNeuron1, 0.65);
    
    std::cout << "Connections created." << std::endl;
    std::cout << "Зв'язки створено." << std::endl;
    std::cout << "Связи созданы." << std::endl;
    
    // Получение статистики
    // Get statistics
    // Отримання статистики
    std::cout << "\n=== Neuron Statistics ===" << std::endl;
    std::cout << "=== Статистика нейронів ===" << std::endl;
    std::cout << "=== Статистика нейронов ===" << std::endl;
    std::cout << "Total Neurons: " << neuronManager.getTotalNeuronCount() << std::endl;
    std::cout << "Загальна кількість нейронів: " << neuronManager.getTotalNeuronCount() << std::endl;
    std::cout << "Общее количество нейронов: " << neuronManager.getTotalNeuronCount() << std::endl;
    std::cout << "Active Neurons: " << neuronManager.getActiveNeuronCount() << std::endl;
    std::cout << "Активні нейрони: " << neuronManager.getActiveNeuronCount() << std::endl;
    std::cout << "Активные нейроны: " << neuronManager.getActiveNeuronCount() << std::endl;
    
    // Создание нейронной сети с заданной архитектурой
    // Creating neural network with specified architecture
    // Створення нейронної мережі з заданою архітектурою
    std::cout << "\n=== Creating Neural Network ===" << std::endl;
    std::cout << "=== Створення нейронної мережі ===" << std::endl;
    std::cout << "=== Создание нейронной сети ===" << std::endl;
    
    NeuronLifecycleManager networkManager;
    networkManager.initialize();
    
    // Создание нейронной сети 3-4-2 (3 входных, 4 скрытых, 2 выходных нейрона)
    // Creating neural network 3-4-2 (3 input, 4 hidden, 2 output neurons)
    // Створення нейронної мережі 3-4-2 (3 вхідних, 4 прихованих, 2 вихідних нейрона)
    std::vector<int> layerSizes = {3, 4, 2};
    if (NeuronUtils::createNeuralNetwork(networkManager, layerSizes)) {
        std::cout << "Neural network created successfully." << std::endl;
        std::cout << "Нейронна мережа створена успішно." << std::endl;
        std::cout << "Нейронная сеть создана успешно." << std::endl;
        
        NeuronUtils::printNetworkStatistics(networkManager);
    } else {
        std::cout << "Failed to create neural network." << std::endl;
        std::cout << "Не вдалося створити нейронну мережу." << std::endl;
        std::cout << "Не удалось создать нейронную сеть." << std::endl;
    }
    
    // Создание группы нейронов разных типов
    // Creating group of neurons of different types
    // Створення групи нейронів різних типів
    std::cout << "\n=== Creating Neuron Groups ===" << std::endl;
    std::cout << "=== Створення груп нейронів ===" << std::endl;
    std::cout << "=== Создание групп нейронов ===" << std::endl;
    
    std::vector<int> inputNeurons = NeuronUtils::createInputNeurons(networkManager, 3, "GroupInput");
    std::vector<int> hiddenNeurons = NeuronUtils::createHiddenNeurons(networkManager, 5, "GroupHidden");
    std::vector<int> outputNeurons = NeuronUtils::createOutputNeurons(networkManager, 2, "GroupOutput");
    
    std::cout << "Created " << inputNeurons.size() << " input neurons." << std::endl;
    std::cout << "Створено " << inputNeurons.size() << " вхідних нейронів." << std::endl;
    std::cout << "Создано " << inputNeurons.size() << " входных нейронов." << std::endl;
    
    std::cout << "Created " << hiddenNeurons.size() << " hidden neurons." << std::endl;
    std::cout << "Створено " << hiddenNeurons.size() << " прихованих нейронів." << std::endl;
    std::cout << "Создано " << hiddenNeurons.size() << " скрытых нейронов." << std::endl;
    
    std::cout << "Created " << outputNeurons.size() << " output neurons." << std::endl;
    std::cout << "Створено " << outputNeurons.size() << " вихідних нейронів." << std::endl;
    std::cout << "Создано " << outputNeurons.size() << " выходных нейронов." << std::endl;
    
    // Активация группы нейронов
    // Activating group of neurons
    // Активація групи нейронів
    std::vector<int> allNeurons;
    allNeurons.insert(allNeurons.end(), inputNeurons.begin(), inputNeurons.end());
    allNeurons.insert(allNeurons.end(), hiddenNeurons.begin(), hiddenNeurons.end());
    allNeurons.insert(allNeurons.end(), outputNeurons.begin(), outputNeurons.end());
    
    if (NeuronUtils::activateNeurons(networkManager, allNeurons)) {
        std::cout << "All neurons activated successfully." << std::endl;
        std::cout << "Усі нейрони активовано успішно." << std::endl;
        std::cout << "Все нейроны активированы успешно." << std::endl;
    } else {
        std::cout << "Failed to activate all neurons." << std::endl;
        std::cout << "Не вдалося активувати всі нейрони." << std::endl;
        std::cout << "Не удалось активировать все нейроны." << std::endl;
    }
    
    // Демонстрация работы нейронов
    // Demonstrating neuron operation
    // Демонстрація роботи нейронів
    std::cout << "\n=== Demonstrating Neuron Operation ===" << std::endl;
    std::cout << "=== Демонстрація роботи нейронів ===" << std::endl;
    std::cout << "=== Демонстрация работы нейронов ===" << std::endl;
    
    // Создание входных сигналов
    // Creating input signals
    // Створення вхідних сигналів
    NeuronInput input1;
    input1.sourceNeuronId = -1; // Внешний источник / External source / Зовнішнє джерело
    input1.signalStrength = 0.9;
    input1.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    input1.data = {1.0, 2.0, 3.0};
    
    NeuronInput input2;
    input2.sourceNeuronId = -1; // Внешний источник / External source / Зовнішнє джерело
    input2.signalStrength = 0.7;
    input2.timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    input2.data = {4.0, 5.0, 6.0};
    
    // Добавление входных сигналов нейронам
    // Adding input signals to neurons
    // Додавання вхідних сигналів нейронам
    std::vector<int> targetNeurons = {inputNeuron1, inputNeuron2};
    std::vector<NeuronInput> inputs = {input1, input2};
    
    if (NeuronUtils::addInputSignalsToNeurons(neuronManager, targetNeurons, inputs)) {
        std::cout << "Input signals added successfully." << std::endl;
        std::cout << "Вхідні сигнали додано успішно." << std::endl;
        std::cout << "Входные сигналы добавлены успешно." << std::endl;
    } else {
        std::cout << "Failed to add input signals." << std::endl;
        std::cout << "Не вдалося додати вхідні сигнали." << std::endl;
        std::cout << "Не удалось добавить входные сигналы." << std::endl;
    }
    
    // Проверка, должны ли нейроны сработать
    // Checking if neurons should fire
    // Перевірка, чи повинні нейрони спрацювати
    std::cout << "\nChecking neuron firing conditions..." << std::endl;
    std::cout << "Перевірка умов спрацювання нейронів..." << std::endl;
    std::cout << "Проверка условий срабатывания нейронов..." << std::endl;
    
    bool shouldInput1Fire = neuronManager.shouldNeuronFire(inputNeuron1);
    bool shouldInput2Fire = neuronManager.shouldNeuronFire(inputNeuron2);
    bool shouldHidden1Fire = neuronManager.shouldNeuronFire(hiddenNeuron1);
    
    std::cout << "Input Neuron 1 should fire: " << (shouldInput1Fire ? "Yes" : "No") << std::endl;
    std::cout << "Вхідний нейрон 1 повинен спрацювати: " << (shouldInput1Fire ? "Так" : "Ні") << std::endl;
    std::cout << "Входной нейрон 1 должен сработать: " << (shouldInput1Fire ? "Да" : "Нет") << std::endl;
    
    std::cout << "Input Neuron 2 should fire: " << (shouldInput2Fire ? "Yes" : "No") << std::endl;
    std::cout << "Вхідний нейрон 2 повинен спрацювати: " << (shouldInput2Fire ? "Так" : "Ні") << std::endl;
    std::cout << "Входной нейрон 2 должен сработать: " << (shouldInput2Fire ? "Да" : "Нет") << std::endl;
    
    std::cout << "Hidden Neuron 1 should fire: " << (shouldHidden1Fire ? "Yes" : "No") << std::endl;
    std::cout << "Прихований нейрон 1 повинен спрацювати: " << (shouldHidden1Fire ? "Так" : "Ні") << std::endl;
    std::cout << "Скрытый нейрон 1 должен сработать: " << (shouldHidden1Fire ? "Да" : "Нет") << std::endl;
    
    // Получение выходных сигналов
    // Getting output signals
    // Отримання вихідних сигналів
    if (shouldInput1Fire) {
        NeuronOutput output = neuronManager.getNeuronFiringOutput(inputNeuron1);
        std::cout << "Input Neuron 1 firing output - Target: " << output.targetNeuronId 
                  << ", Strength: " << output.signalStrength << std::endl;
    }
    
    // Очистка ресурсов
    // Cleaning up resources
    // Очищення ресурсів
    std::cout << "\nCleaning up resources..." << std::endl;
    std::cout << "Очищення ресурсів..." << std::endl;
    std::cout << "Очистка ресурсов..." << std::endl;
    
    // Деактивация нейронов
    // Deactivating neurons
    // Деактивація нейронів
    neuronManager.deactivateNeuron(inputNeuron1);
    neuronManager.deactivateNeuron(inputNeuron2);
    neuronManager.deactivateNeuron(hiddenNeuron1);
    neuronManager.deactivateNeuron(hiddenNeuron2);
    neuronManager.deactivateNeuron(outputNeuron1);
    neuronManager.deactivateNeuron(processingNeuron1);
    
    std::cout << "Neurons deactivated." << std::endl;
    std::cout << "Нейрони деактивовано." << std::endl;
    std::cout << "Нейроны деактивированы." << std::endl;
    
    std::cout << "\nAdvanced Neuron Example completed!" << std::endl;
    std::cout << "Приклад розширеного нейрона завершено!" << std::endl;
    std::cout << "Пример расширенного нейрона завершен!" << std::endl;
    
    return 0;
}