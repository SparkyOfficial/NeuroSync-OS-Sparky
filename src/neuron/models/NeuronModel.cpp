#include "NeuronModel.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <chrono>

// NeuronModel.cpp
// Реалізація моделі нейрона для NeuroSync OS Sparky
// Implementation of neuron model for NeuroSync OS Sparky
// Реалізація моделі нейрона для NeuroSync OS Sparky

namespace NeuroSync {
namespace Neuron {
namespace Models {

    // Конструктор моделі нейрона
    // Neuron model constructor
    // Конструктор моделі нейрона
    NeuronModel::NeuronModel(int id, NeuronType type, const std::string& name)
        : id(id), type(type), name(name), status(NeuronStatus::CREATED),
          creationTime(getCurrentTimeMillis()), lastUpdateTime(creationTime) {
        // Ініціалізація стану
        // Initialize state
        // Ініціалізувати стан
        state.activationLevel = 0.0;
        state.threshold = 0.5;
        state.learningRate = 0.1;
        state.lastFiredTime = 0;
        state.fireCount = 0;
        state.energyLevel = 1.0;
        
        // Резервування векторів для ефективності
        // Reserve vectors for efficiency
        // Резервування векторів для ефективності
        inputs.reserve(10);
        outputs.reserve(10);
    }

    // Деструктор моделі нейрона
    // Neuron model destructor
    // Деструктор моделі нейрона
    NeuronModel::~NeuronModel() {}

    // Получение ID нейрона
    // Get neuron ID
    // Отримання ID нейрона
    int NeuronModel::getId() const {
        return id;
    }

    // Получение типа нейрона
    // Get neuron type
    // Отримання типу нейрона
    NeuronType NeuronModel::getType() const {
        return type;
    }

    // Получение имени нейрона
    // Get neuron name
    // Отримання імені нейрона
    const std::string& NeuronModel::getName() const {
        return name;
    }

    // Получение статуса нейрона
    // Get neuron status
    // Отримання статусу нейрона
    NeuronStatus NeuronModel::getStatus() const {
        return status.load();
    }

    // Установка статуса нейрона
    // Set neuron status
    // Встановлення статусу нейрона
    void NeuronModel::setStatus(NeuronStatus status) {
        this->status.store(status);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Получение состояния нейрона
    // Get neuron state
    // Отримання стану нейрона
    const NeuronState& NeuronModel::getState() const {
        return state;
    }

    // Обновление состояния нейрона
    // Update neuron state
    // Оновлення стану нейрона
    void NeuronModel::updateState(const NeuronState& newState) {
        state = newState;
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Добавление входного сигнала
    // Add input signal
    // Додавання вхідного сигналу
    void NeuronModel::addInput(const NeuronInput& input) {
        inputs.push_back(input);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Получение всех входных сигналов
    // Get all input signals
    // Отримання всіх вхідних сигналів
    const std::vector<NeuronInput>& NeuronModel::getInputs() const {
        return inputs;
    }

    // Очистка входных сигналов
    // Clear input signals
    // Очищення вхідних сигналів
    void NeuronModel::clearInputs() {
        inputs.clear();
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Добавление выходного сигнала
    // Add output signal
    // Додавання вихідного сигналу
    void NeuronModel::addOutput(const NeuronOutput& output) {
        outputs.push_back(output);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Получение всех выходных сигналов
    // Get all output signals
    // Отримання всіх вихідних сигналів
    const std::vector<NeuronOutput>& NeuronModel::getOutputs() const {
        return outputs;
    }

    // Очистка выходных сигналов
    // Clear output signals
    // Очищення вихідних сигналів
    void NeuronModel::clearOutputs() {
        outputs.clear();
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Добавление связи с другим нейроном
    // Add connection to another neuron
    // Додавання зв'язку з іншим нейроном
    void NeuronModel::addConnection(int neuronId, double weight) {
        connections[neuronId] = weight;
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Удаление связи с другим нейроном
    // Remove connection to another neuron
    // Видалення зв'язку з іншим нейроном
    void NeuronModel::removeConnection(int neuronId) {
        connections.erase(neuronId);
        setLastUpdateTime(getCurrentTimeMillis());
    }

    // Получение всех связей
    // Get all connections
    // Отримання всіх зв'язків
    const std::map<int, double>& NeuronModel::getConnections() const {
        return connections;
    }

    // Обновление веса связи
    // Update connection weight
    // Оновлення ваги зв'язку
    void NeuronModel::updateConnectionWeight(int neuronId, double weight) {
        auto it = connections.find(neuronId);
        if (it != connections.end()) {
            it->second = weight;
            setLastUpdateTime(getCurrentTimeMillis());
        }
    }

    // Получение времени создания
    // Get creation time
    // Отримання часу створення
    long long NeuronModel::getCreationTime() const {
        return creationTime;
    }

    // Получение времени последнего обновления
    // Get last update time
    // Отримання часу останнього оновлення
    long long NeuronModel::getLastUpdateTime() const {
        return lastUpdateTime.load();
    }

    // Установка времени последнего обновления
    // Set last update time
    // Встановлення часу останнього оновлення
    void NeuronModel::setLastUpdateTime(long long time) {
        lastUpdateTime.store(time);
    }

    // Активация нейрона
    // Activate neuron
    // Активація нейрона
    bool NeuronModel::activate() {
        setStatus(NeuronStatus::ACTIVE);
        state.activationLevel = calculateActivation();
        return true;
    }

    // Деактивация нейрона
    // Deactivate neuron
    // Деактивація нейрона
    void NeuronModel::deactivate() {
        setStatus(NeuronStatus::INACTIVE);
        state.activationLevel = 0.0;
    }

    // Проверка, должен ли нейрон сработать
    // Check if neuron should fire
    // Перевірка, чи повинен нейрон спрацювати
    bool NeuronModel::shouldFire() const {
        return state.activationLevel >= state.threshold;
    }

    // Получение выходного сигнала при срабатывании
    // Get output signal when firing
    // Отримання вихідного сигналу при спрацюванні
    NeuronOutput NeuronModel::getFiringOutput() const {
        NeuronOutput output;
        output.timestamp = getCurrentTimeMillis();
        output.signalStrength = state.activationLevel;
        // В реальной реализации здесь будет логика генерации выходных данных
        // In real implementation, there will be logic for generating output data
        // В реальній реалізації тут буде логіка генерації вихідних даних
        return output;
    }

    // Обчислити активацію нейрона
    // Calculate neuron activation
    // Обчислити активацію нейрона
    double NeuronModel::calculateActivation() {
        // Обчислити зважену суму вхідних сигналів
        // Calculate weighted sum of input signals
        // Обчислити зважену суму вхідних сигналів
        double weightedSum = 0.0;
        for (const auto& input : inputs) {
            // Тут ми припускаємо, що у нас є доступ до значень вхідних нейронів
            // Here we assume we have access to input neuron values
            // Тут мы предполагаем, що у нас є доступ до значень вхідних нейронів
            weightedSum += input.signalStrength; // Спрощена модель / Simplified model / Упрощенная модель
        }
        
        // Застосувати сигмоїдну функцію активації
        // Apply sigmoid activation function
        // Применить сигмоидную функцию активации
        double activation = 1.0 / (1.0 + std::exp(-weightedSum));
        
        return activation;
    }

    // Обробити вхідні сигнали
    // Process input signals
    // Обработать входные сигналы
    void NeuronModel::processInputs() {
        // Обчислити новий рівень активації
        // Calculate new activation level
        // Вычислить новый уровень активации
        double newActivation = calculateActivation();
        state.activationLevel = newActivation;
        
        // Перевірити, чи перевищено поріг активації
        // Check if activation threshold is exceeded
        // Проверить, превышен ли порог активации
        if (newActivation >= state.threshold) {
            activate();
        } else {
            deactivate();
        }
    }

    // Згенерувати вихідний сигнал
    // Generate output signal
    // Сгенерировать выходной сигнал
    NeuronOutput NeuronModel::generateOutput() {
        NeuronOutput output;
        output.timestamp = getCurrentTimeMillis();
        output.signalStrength = state.activationLevel;
        // В реальной реализации здесь будет логика генерации выходных данных
        // In real implementation, there will be logic for generating output data
        // В реальній реалізації тут буде логіка генерації вихідних даних
        return output;
    }

    // Отримати поточний час у мілісекундах
    // Get current time in milliseconds
    // Получить текущее время в миллисекундах
    long long NeuronModel::getCurrentTimeMillis() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

} // namespace Models
} // namespace Neuron
} // namespace NeuroSync