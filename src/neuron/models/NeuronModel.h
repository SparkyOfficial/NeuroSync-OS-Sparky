#ifndef NEURON_MODEL_H
#define NEURON_MODEL_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <atomic>

// NeuronModel.h
// Модель нейрона для NeuroSync OS Sparky
// Neuron model for NeuroSync OS Sparky
// Модель нейрона для NeuroSync OS Sparky

namespace NeuroSync {
namespace Neuron {
namespace Models {

    // Тип нейрона
    // Neuron type
    // Тип нейрона
    enum class NeuronType {
        INPUT,      // Входной нейрон / Input neuron / Вхідний нейрон
        HIDDEN,     // Скрытый нейрон / Hidden neuron / Прихований нейрон
        OUTPUT,     // Выходной нейрон / Output neuron / Вихідний нейрон
        PROCESSING, // Обрабатывающий нейрон / Processing neuron / Обробний нейрон
        MEMORY      // Нейрон памяти / Memory neuron / Нейрон пам'яті
    };

    // Статус нейрона
    // Neuron status
    // Статус нейрона
    enum class NeuronStatus {
        CREATED,    // Создан / Created / Створений
        INITIALIZED,// Инициализирован / Initialized / Ініціалізований
        ACTIVE,     // Активен / Active / Активний
        INACTIVE,   // Неактивен / Inactive / Неактивний
        PROCESSING, // Обрабатывает / Processing / Обробляє
        SLEEPING,   // Спит / Sleeping / Спить
        TERMINATED  // Завершен / Terminated / Завершений
    };

    // Структура для представления состояния нейрона
    // Structure to represent neuron state
    // Структура для представлення стану нейрона
    struct NeuronState {
        double activationLevel;     // Уровень активации / Activation level / Рівень активації
        double threshold;           // Порог активации / Activation threshold / Поріг активації
        double learningRate;        // Скорость обучения / Learning rate / Швидкість навчання
        long long lastFiredTime;    // Время последнего срабатывания / Last fired time / Час останнього спрацювання
        int fireCount;              // Количество срабатываний / Fire count / Кількість спрацювань
        double energyLevel;         // Уровень энергии / Energy level / Рівень енергії
    };

    // Структура для представления входных данных нейрона
    // Structure to represent neuron input data
    // Структура для представлення вхідних даних нейрона
    struct NeuronInput {
        int sourceNeuronId;         // ID источника / Source ID / ID джерела
        double signalStrength;      // Сила сигнала / Signal strength / Сила сигналу
        long long timestamp;        // Временная метка / Timestamp / Тимчасова мітка
        std::vector<double> data;   // Данные сигнала / Signal data / Дані сигналу
    };

    // Структура для представления выходных данных нейрона
    // Structure to represent neuron output data
    // Структура для представлення вихідних даних нейрона
    struct NeuronOutput {
        int targetNeuronId;         // ID цели / Target ID / ID цілі
        double signalStrength;      // Сила сигнала / Signal strength / Сила сигналу
        long long timestamp;        // Временная метка / Timestamp / Тимчасова мітка
        std::vector<double> data;   // Данные сигнала / Signal data / Дані сигналу
    };

    // Модель нейрона
    // Neuron model
    // Модель нейрона
    class NeuronModel {
    public:
        NeuronModel(int id, NeuronType type, const std::string& name);
        ~NeuronModel();
        
        // Получение ID нейрона
        // Get neuron ID
        // Отримання ID нейрона
        int getId() const;
        
        // Получение типа нейрона
        // Get neuron type
        // Отримання типу нейрона
        NeuronType getType() const;
        
        // Получение имени нейрона
        // Get neuron name
        // Отримання імені нейрона
        const std::string& getName() const;
        
        // Получение статуса нейрона
        // Get neuron status
        // Отримання статусу нейрона
        NeuronStatus getStatus() const;
        
        // Установка статуса нейрона
        // Set neuron status
        // Встановлення статусу нейрона
        void setStatus(NeuronStatus status);
        
        // Получение состояния нейрона
        // Get neuron state
        // Отримання стану нейрона
        const NeuronState& getState() const;
        
        // Обновление состояния нейрона
        // Update neuron state
        // Оновлення стану нейрона
        void updateState(const NeuronState& state);
        
        // Добавление входного сигнала
        // Add input signal
        // Додавання вхідного сигналу
        void addInput(const NeuronInput& input);
        
        // Получение всех входных сигналов
        // Get all input signals
        // Отримання всіх вхідних сигналів
        const std::vector<NeuronInput>& getInputs() const;
        
        // Очистка входных сигналов
        // Clear input signals
        // Очищення вхідних сигналів
        void clearInputs();
        
        // Добавление выходного сигнала
        // Add output signal
        // Додавання вихідного сигналу
        void addOutput(const NeuronOutput& output);
        
        // Получение всех выходных сигналов
        // Get all output signals
        // Отримання всіх вихідних сигналів
        const std::vector<NeuronOutput>& getOutputs() const;
        
        // Очистка выходных сигналов
        // Clear output signals
        // Очищення вихідних сигналів
        void clearOutputs();
        
        // Добавление связи с другим нейроном
        // Add connection to another neuron
        // Додавання зв'язку з іншим нейроном
        void addConnection(int neuronId, double weight);
        
        // Удаление связи с другим нейроном
        // Remove connection to another neuron
        // Видалення зв'язку з іншим нейроном
        void removeConnection(int neuronId);
        
        // Получение всех связей
        // Get all connections
        // Отримання всіх зв'язків
        const std::map<int, double>& getConnections() const;
        
        // Обновление веса связи
        // Update connection weight
        // Оновлення ваги зв'язку
        void updateConnectionWeight(int neuronId, double weight);
        
        // Получение времени создания
        // Get creation time
        // Отримання часу створення
        long long getCreationTime() const;
        
        // Получение времени последнего обновления
        // Get last update time
        // Отримання часу останнього оновлення
        long long getLastUpdateTime() const;
        
        // Установка времени последнего обновления
        // Set last update time
        // Встановлення часу останнього оновлення
        void setLastUpdateTime(long long time);
        
        // Активация нейрона
        // Activate neuron
        // Активація нейрона
        bool activate();
        
        // Деактивация нейрона
        // Deactivate neuron
        // Деактивація нейрона
        void deactivate();
        
        // Проверка, должен ли нейрон сработать
        // Check if neuron should fire
        // Перевірка, чи повинен нейрон спрацювати
        bool shouldFire() const;
        
        // Получение выходного сигнала при срабатывании
        // Get output signal when firing
        // Отримання вихідного сигналу при спрацюванні
        NeuronOutput getFiringOutput() const;
        
    private:
        int id;                             // Уникальный идентификатор нейрона / Unique neuron identifier / Унікальний ідентифікатор нейрона
        NeuronType type;                    // Тип нейрона / Neuron type / Тип нейрона
        std::string name;                   // Имя нейрона / Neuron name / Ім'я нейрона
        std::atomic<NeuronStatus> status;   // Статус нейрона / Neuron status / Статус нейрона
        NeuronState state;                  // Состояние нейрона / Neuron state / Стан нейрона
        std::vector<NeuronInput> inputs;    // Входные сигналы / Input signals / Вхідні сигнали
        std::vector<NeuronOutput> outputs;  // Выходные сигналы / Output signals / Вихідні сигнали
        std::map<int, double> connections;  // Связи с другими нейронами / Connections to other neurons / Зв'язки з іншими нейронами
        long long creationTime;             // Время создания / Creation time / Час створення
        std::atomic<long long> lastUpdateTime; // Время последнего обновления / Last update time / Час останнього оновлення
        
        // Внутренние методы
        // Internal methods
        // Внутрішні методи
        double calculateActivation();
        void processInputs();
        NeuronOutput generateOutput();
        long long getCurrentTimeMillis() const;
    };

} // namespace Models
} // namespace Neuron
} // namespace NeuroSync

#endif // NEURON_MODEL_H