#include "NeuronModel.h"
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iostream>

// NeuronModel.cpp
// Реализация модели нейрона для NeuroSync OS Sparky
// Implementation of neuron model for NeuroSync OS Sparky
// Реалізація моделі нейрона для NeuroSync OS Sparky

namespace NeuroSync {
namespace Neuron {
namespace Models {

    NeuronModel::NeuronModel(int id, NeuronType type, const std::string& name)
        : id(id), type(type), name(name), status(NeuronStatus::CREATED),
          creationTime(getCurrentTimeMillis()), lastUpdateTime(creationTime) {
        // Конструктор модели нейрона
        // Constructor of neuron model
        // Конструктор моделі нейрона
        
        // Инициализация состояния нейрона
        // Initialize neuron state
        // Ініціалізація стану нейрона
        state.activationLevel = 0.0;
        state.threshold = 0.5;
        state.learningRate = 0.1;
        state.lastFiredTime = 0;
        state.fireCount = 0;
        state.energyLevel = 1.0;
    }

    NeuronModel::~NeuronModel() {
        // Деструктор модели нейрона
        // Destructor of neuron model
        // Деструктор моделі нейрона
    }

    int NeuronModel::getId() const {
        // Получение ID нейрона
        // Get neuron ID
        // Отримання ID нейрона
        
        return id;
    }

    NeuronType NeuronModel::getType() const {
        // Получение типа нейрона
        // Get neuron type
        // Отримання типу нейрона
        
        return type;
    }

    const std::string& NeuronModel::getName() const {
        // Получение имени нейрона
        // Get neuron name
        // Отримання імені нейрона
        
        return name;
    }

    NeuronStatus NeuronModel::getStatus() const {
        // Получение статуса нейрона
        // Get neuron status
        // Отримання статусу нейрона
        
        return status.load();
    }

    void NeuronModel::setStatus(NeuronStatus status) {
        // Установка статуса нейрона
        // Set neuron status
        // Встановлення статусу нейрона
        
        this->status.store(status);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    const NeuronState& NeuronModel::getState() const {
        // Получение состояния нейрона
        // Get neuron state
        // Отримання стану нейрона
        
        return state;
    }

    void NeuronModel::updateState(const NeuronState& state) {
        // Обновление состояния нейрона
        // Update neuron state
        // Оновлення стану нейрона
        
        this->state = state;
        setLastUpdateTime(getCurrentTimeMillis());
    }

    void NeuronModel::addInput(const NeuronInput& input) {
        // Добавление входного сигнала
        // Add input signal
        // Додавання вхідного сигналу
        
        inputs.push_back(input);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    const std::vector<NeuronInput>& NeuronModel::getInputs() const {
        // Получение всех входных сигналов
        // Get all input signals
        // Отримання всіх вхідних сигналів
        
        return inputs;
    }

    void NeuronModel::clearInputs() {
        // Очистка входных сигналов
        // Clear input signals
        // Очищення вхідних сигналів
        
        inputs.clear();
        setLastUpdateTime(getCurrentTimeMillis());
    }

    void NeuronModel::addOutput(const NeuronOutput& output) {
        // Добавление выходного сигнала
        // Add output signal
        // Додавання вихідного сигналу
        
        outputs.push_back(output);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    const std::vector<NeuronOutput>& NeuronModel::getOutputs() const {
        // Получение всех выходных сигналов
        // Get all output signals
        // Отримання всіх вихідних сигналів
        
        return outputs;
    }

    void NeuronModel::clearOutputs() {
        // Очистка выходных сигналов
        // Clear output signals
        // Очищення вихідних сигналів
        
        outputs.clear();
        setLastUpdateTime(getCurrentTimeMillis());
    }

    void NeuronModel::addConnection(int neuronId, double weight) {
        // Добавление связи с другим нейроном
        // Add connection to another neuron
        // Додавання зв'язку з іншим нейроном
        
        connections[neuronId] = weight;
        setLastUpdateTime(getCurrentTimeMillis());
    }

    void NeuronModel::removeConnection(int neuronId) {
        // Удаление связи с другим нейроном
        // Remove connection to another neuron
        // Видалення зв'язку з іншим нейроном
        
        connections.erase(neuronId);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    const std::map<int, double>& NeuronModel::getConnections() const {
        // Получение всех связей
        // Get all connections
        // Отримання всіх зв'язків
        
        return connections;
    }

    void NeuronModel::updateConnectionWeight(int neuronId, double weight) {
        // Обновление веса связи
        // Update connection weight
        // Оновлення ваги зв'язку
        
        auto it = connections.find(neuronId);
        if (it != connections.end()) {
            it->second = weight;
            setLastUpdateTime(getCurrentTimeMillis());
        }
    }

    long long NeuronModel::getCreationTime() const {
        // Получение времени создания
        // Get creation time
        // Отримання часу створення
        
        return creationTime;
    }

    long long NeuronModel::getLastUpdateTime() const {
        // Получение времени последнего обновления
        // Get last update time
        // Отримання часу останнього оновлення
        
        return lastUpdateTime.load();
    }

    void NeuronModel::setLastUpdateTime(long long time) {
        // Установка времени последнего обновления
        // Set last update time
        // Встановлення часу останнього оновлення
        
        lastUpdateTime.store(time);
    }

    bool NeuronModel::activate() {
        // Активация нейрона
        // Activate neuron
        // Активація нейрона
        
        if (status.load() == NeuronStatus::ACTIVE) {
            return false; // Нейрон уже активен / Neuron is already active / Нейрон вже активний
        }
        
        setStatus(NeuronStatus::ACTIVE);
        return true;
    }

    void NeuronModel::deactivate() {
        // Деактивация нейрона
        // Deactivate neuron
        // Деактивація нейрона
        
        if (status.load() == NeuronStatus::ACTIVE) {
            setStatus(NeuronStatus::INACTIVE);
        }
    }

    bool NeuronModel::shouldFire() const {
        // Проверка, должен ли нейрон сработать
        // Check if neuron should fire
        // Перевірка, чи повинен нейрон спрацювати
        
        // Обработка входных сигналов
        // Process input signals
        // Обробка вхідних сигналів
        const_cast<NeuronModel*>(this)->processInputs();
        
        // Вычисление уровня активации
        // Calculate activation level
        // Обчислення рівня активації
        double activation = const_cast<NeuronModel*>(this)->calculateActivation();
        
        // Проверка, превышает ли активация порог
        // Check if activation exceeds threshold
        // Перевірка, чи перевищує активація поріг
        return activation >= state.threshold;
    }

    NeuronOutput NeuronModel::getFiringOutput() const {
        // Получение выходного сигнала при срабатывании
        // Get output signal when firing
        // Отримання вихідного сигналу при спрацюванні
        
        return const_cast<NeuronModel*>(this)->generateOutput();
    }

    double NeuronModel::calculateActivation() {
        // Вычисление уровня активации нейрона
        // Calculate neuron activation level
        // Обчислення рівня активації нейрона
        
        // Простая модель: сумма взвешенных входных сигналов
        // Simple model: sum of weighted input signals
        // Проста модель: сума зважених вхідних сигналів
        double weightedSum = 0.0;
        
        for (const auto& input : inputs) {
            weightedSum += input.signalStrength;
        }
        
        // Применение функции активации (сигмоид)
        // Apply activation function (sigmoid)
        // Застосування функції активації (сигмоид)
        double activation = 1.0 / (1.0 + exp(-weightedSum));
        
        // Обновление уровня активации в состоянии
        // Update activation level in state
        // Оновлення рівня активації в стані
        state.activationLevel = activation;
        
        return activation;
    }

    void NeuronModel::processInputs() {
        // Обработка входных сигналов
        // Process input signals
        // Обробка вхідних сигналів
        
        // В реальной реализации здесь может быть более сложная логика
        // In real implementation, there could be more complex logic here
        // В реальній реалізації тут може бути більш складна логіка
        
        // Пока просто оставляем как есть
        // For now, just leave as is
        // Поки просто залишаємо як є
    }

    NeuronOutput NeuronModel::generateOutput() {
        // Генерация выходного сигнала
        // Generate output signal
        // Генерація вихідного сигналу
        
        NeuronOutput output;
        output.timestamp = getCurrentTimeMillis();
        output.signalStrength = state.activationLevel;
        
        // В реальной реализации здесь будет более сложная логика
        // In real implementation, there will be more complex logic here
        // В реальній реалізації тут буде більш складна логіка
        
        // Для демонстрации просто отправляем сигнал всем связанным нейронам
        // For demonstration, just send signal to all connected neurons
        // Для демонстрації просто надсилаємо сигнал усім зв'язаним нейронам
        for (const auto& connection : connections) {
            output.targetNeuronId = connection.first;
            output.signalStrength = state.activationLevel * connection.second;
            outputs.push_back(output);
        }
        
        // Обновление статистики
        // Update statistics
        // Оновлення статистики
        state.lastFiredTime = output.timestamp;
        state.fireCount++;
        
        return output;
    }

    long long NeuronModel::getCurrentTimeMillis() const {
        // Получение текущего времени в миллисекундах
        // Get current time in milliseconds
        // Отримання поточного часу в мілісекундах
        
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        return millis;
    }

} // namespace Models
} // namespace Neuron
} // namespace NeuroSync