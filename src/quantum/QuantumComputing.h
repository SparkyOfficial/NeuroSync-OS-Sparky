#ifndef QUANTUM_COMPUTING_H
#define QUANTUM_COMPUTING_H

#include <vector>
#include <complex>
#include <memory>
#include <string>
#include <map>
#include <random>

// QuantumComputing.h
// Модуль квантових обчислень для NeuroSync OS Sparky
// Quantum computing module for NeuroSync OS Sparky
// Модуль квантовых вычислений для NeuroSync OS Sparky

namespace NeuroSync {
namespace Quantum {

    // Типи квантових вентилів
    // Types of quantum gates
    // Типы квантовых вентилей
    enum class QuantumGateType {
        PAULI_X,        // Паулі X (NOT) / Pauli X (NOT) / Паули X (NOT)
        PAULI_Y,        // Паулі Y / Pauli Y / Паули Y
        PAULI_Z,        // Паулі Z / Pauli Z / Паули Z
        HADAMARD,       // Вентиль Адамара / Hadamard gate / Вентиль Адамара
        CNOT,           // Контрольований NOT / Controlled NOT / Контролируемый NOT
        TOFFOLI,        // Вентиль Тоффолі / Toffoli gate / Вентиль Тоффоли
        PHASE,          // Фазовий вентиль / Phase gate / Фазовый вентиль
        ROTATION_X,     // Обертання навколо осі X / Rotation around X axis / Вращение вокруг оси X
        ROTATION_Y,     // Обертання навколо осі Y / Rotation around Y axis / Вращение вокруг оси Y
        ROTATION_Z      // Обертання навколо осі Z / Rotation around Z axis / Вращение вокруг оси Z
    };

    // Квантовий біт (кубіт)
    // Quantum bit (qubit)
    // Квантовый бит (кубит)
    class Qubit {
    public:
        Qubit();
        Qubit(double alpha, double beta);
        ~Qubit() = default;
        
        // Отримати амплітуди
        // Get amplitudes
        // Получить амплитуды
        std::complex<double> getAlpha() const { return alpha; }
        std::complex<double> getBeta() const { return beta; }
        
        // Встановити амплітуди
        // Set amplitudes
        // Установить амплитуды
        void setAmplitudes(double alphaReal, double alphaImag, double betaReal, double betaImag);
        
        // Нормалізувати кубіт
        // Normalize qubit
        // Нормализовать кубит
        void normalize();
        
        // Виміряти кубіт
        // Measure qubit
        // Измерить кубит
        int measure();
        
        // Отримати ймовірність стану |0>
        // Get probability of state |0>
        // Получить вероятность состояния |0>
        double getProbabilityZero() const;
        
        // Отримати ймовірність стану |1>
        // Get probability of state |1>
        // Получить вероятность состояния |1>
        double getProbabilityOne() const;
        
    private:
        std::complex<double> alpha;  // Амплітуда стану |0> / Amplitude of state |0> / Амплитуда состояния |0>
        std::complex<double> beta;   // Амплітуда стану |1> / Amplitude of state |1> / Амплитуда состояния |1>
        mutable std::mt19937 rng;    // Генератор випадкових чисел / Random number generator / Генератор случайных чисел
    };

    // Квантовий вентиль
    // Quantum gate
    // Квантовый вентиль
    class QuantumGate {
    public:
        QuantumGate(QuantumGateType type, const std::vector<int>& qubitIndices);
        QuantumGate(QuantumGateType type, int qubitIndex);
        QuantumGate(QuantumGateType type, int controlIndex, int targetIndex);
        ~QuantumGate() = default;
        
        // Отримати тип вентиля
        // Get gate type
        // Получить тип вентиля
        QuantumGateType getType() const { return gateType; }
        
        // Отримати індекси кубітів
        // Get qubit indices
        // Получить индексы кубитов
        const std::vector<int>& getQubitIndices() const { return qubitIndices; }
        
        // Встановити параметри вентиля
        // Set gate parameters
        // Установить параметры вентиля
        void setParameters(double param1, double param2 = 0.0);
        
        // Отримати матричне представлення вентиля
        // Get matrix representation of gate
        // Получить матричное представление вентиля
        std::vector<std::vector<std::complex<double>>> getMatrix() const;
        
    private:
        QuantumGateType gateType;           // Тип вентиля / Gate type / Тип вентиля
        std::vector<int> qubitIndices;      // Індекси кубітів / Qubit indices / Индексы кубитов
        double parameter1;                  // Перший параметр / First parameter / Первый параметр
        double parameter2;                  // Другий параметр / Second parameter / Второй параметр
        
        // Створити матрицю Паулі X
        // Create Pauli X matrix
        // Создать матрицу Паули X
        std::vector<std::vector<std::complex<double>>> createPauliX() const;
        
        // Створити матрицю Паулі Y
        // Create Pauli Y matrix
        // Создать матрицу Паули Y
        std::vector<std::vector<std::complex<double>>> createPauliY() const;
        
        // Створити матрицю Паулі Z
        // Create Pauli Z matrix
        // Создать матрицу Паули Z
        std::vector<std::vector<std::complex<double>>> createPauliZ() const;
        
        // Створити матрицю Адамара
        // Create Hadamard matrix
        // Создать матрицу Адамара
        std::vector<std::vector<std::complex<double>>> createHadamard() const;
        
        // Створити матрицю CNOT
        // Create CNOT matrix
        // Создать матрицу CNOT
        std::vector<std::vector<std::complex<double>>> createCNOT() const;
        
        // Створити матрицю Тоффолі
        // Create Toffoli matrix
        // Создать матрицу Тоффоли
        std::vector<std::vector<std::complex<double>>> createToffoli() const;
        
        // Створити фазову матрицю
        // Create phase matrix
        // Создать фазовую матрицу
        std::vector<std::vector<std::complex<double>>> createPhase() const;
        
        // Створити матрицю обертання навколо осі X
        // Create rotation matrix around X axis
        // Создать матрицу вращения вокруг оси X
        std::vector<std::vector<std::complex<double>>> createRotationX() const;
        
        // Створити матрицю обертання навколо осі Y
        // Create rotation matrix around Y axis
        // Создать матрицу вращения вокруг оси Y
        std::vector<std::vector<std::complex<double>>> createRotationY() const;
        
        // Створити матрицю обертання навколо осі Z
        // Create rotation matrix around Z axis
        // Создать матрицу вращения вокруг оси Z
        std::vector<std::vector<std::complex<double>>> createRotationZ() const;
    };

    // Квантовий регістр
    // Quantum register
    // Квантовый регистр
    class QuantumRegister {
    public:
        QuantumRegister(int numQubits);
        ~QuantumRegister() = default;
        
        // Отримати кількість кубітів
        // Get number of qubits
        // Получить количество кубитов
        int getNumQubits() const { return static_cast<int>(qubits.size()); }
        
        // Отримати кубіт за індексом
        // Get qubit by index
        // Получить кубит по индексу
        Qubit& getQubit(int index);
        const Qubit& getQubit(int index) const;
        
        // Встановити стан кубіта
        // Set qubit state
        // Установить состояние кубита
        void setQubitState(int index, double alphaReal, double alphaImag, double betaReal, double betaImag);
        
        // Ініціалізувати всі кубіти в стані |0>
        // Initialize all qubits in state |0>
        // Инициализировать все кубиты в состоянии |0>
        void initializeZero();
        
        // Ініціалізувати всі кубіти в стані |1>
        // Initialize all qubits in state |1>
        // Инициализировать все кубиты в состоянии |1>
        void initializeOne();
        
        // Ініціалізувати всі кубіти в суперпозиції
        // Initialize all qubits in superposition
        // Инициализировать все кубиты в суперпозиции
        void initializeSuperposition();
        
        // Застосувати вентиль до регістру
        // Apply gate to register
        // Применить вентиль к регистру
        void applyGate(const QuantumGate& gate);
        
        // Виміряти всі кубіти
        // Measure all qubits
        // Измерить все кубиты
        std::vector<int> measureAll();
        
        // Виміряти конкретний кубіт
        // Measure specific qubit
        // Измерить конкретный кубит
        int measureQubit(int index);
        
        // Отримати стан регістру як вектор амплітуд
        // Get register state as amplitude vector
        // Получить состояние регистра как вектор амплитуд
        std::vector<std::complex<double>> getStateVector() const;
        
        // Встановити стан регістру з вектора амплітуд
        // Set register state from amplitude vector
        // Установить состояние регистра из вектора амплитуд
        void setStateVector(const std::vector<std::complex<double>>& state);
        
    private:
        std::vector<Qubit> qubits;  // Кубіти / Qubits / Кубиты
        
        // Застосувати одно-кубітний вентиль
        // Apply single-qubit gate
        // Применить одно-кубитный вентиль
        void applySingleQubitGate(const QuantumGate& gate);
        
        // Застосувати дво-кубітний вентиль
        // Apply two-qubit gate
        // Применить двух-кубитный вентиль
        void applyTwoQubitGate(const QuantumGate& gate);
        
        // Застосувати три-кубітний вентиль
        // Apply three-qubit gate
        // Применить трех-кубитный вентиль
        void applyThreeQubitGate(const QuantumGate& gate);
        
        // Нормалізувати стан регістру
        // Normalize register state
        // Нормализовать состояние регистра
        void normalize();
    };

    // Квантовий алгоритм
    // Quantum algorithm
    // Квантовый алгоритм
    class QuantumAlgorithm {
    public:
        QuantumAlgorithm(const std::string& name);
        virtual ~QuantumAlgorithm() = default;
        
        // Ініціалізація алгоритму
        // Initialize algorithm
        // Инициализация алгоритма
        virtual bool initialize(int numQubits) = 0;
        
        // Виконати алгоритм
        // Execute algorithm
        // Выполнить алгоритм
        virtual bool execute() = 0;
        
        // Отримати результати
        // Get results
        // Получить результаты
        virtual std::vector<int> getResults() const = 0;
        
        // Отримати ім'я алгоритму
        // Get algorithm name
        // Получить имя алгоритма
        const std::string& getName() const { return algorithmName; }
        
        // Встановити квантовий регістр
        // Set quantum register
        // Установить квантовый регистр
        void setQuantumRegister(std::unique_ptr<QuantumRegister> reg);
        
        // Отримати квантовий регістр
        // Get quantum register
        // Получить квантовый регистр
        QuantumRegister* getQuantumRegister() const;
        
    protected:
        std::string algorithmName;                      // Ім'я алгоритму / Algorithm name / Имя алгоритма
        std::unique_ptr<QuantumRegister> quantumRegister; // Квантовий регістр / Quantum register / Квантовый регистр
    };

    // Алгоритм Дойча-Йожи
    // Deutsch-Jozsa algorithm
    // Алгоритм Дойча-Йожи
    class DeutschJozsaAlgorithm : public QuantumAlgorithm {
    public:
        DeutschJozsaAlgorithm();
        ~DeutschJozsaAlgorithm() override = default;
        
        // Ініціалізація алгоритму
        // Initialize algorithm
        // Инициализация алгоритма
        bool initialize(int numQubits) override;
        
        // Виконати алгоритм
        // Execute algorithm
        // Выполнить алгоритм
        bool execute() override;
        
        // Отримати результати
        // Get results
        // Получить результаты
        std::vector<int> getResults() const override;
        
        // Встановити функцію
        // Set function
        // Установить функцию
        void setFunction(const std::function<int(int)>& func);
        
    private:
        std::function<int(int)> oracleFunction;  // Оракульна функція / Oracle function / Оракульная функция
    };

    // Алгоритм Гровера
    // Grover's algorithm
    // Алгоритм Гровера
    class GroverAlgorithm : public QuantumAlgorithm {
    public:
        GroverAlgorithm();
        ~GroverAlgorithm() override = default;
        
        // Ініціалізація алгоритму
        // Initialize algorithm
        // Инициализация алгоритма
        bool initialize(int numQubits) override;
        
        // Виконати алгоритм
        // Execute algorithm
        // Выполнить алгоритм
        bool execute() override;
        
        // Отримати результати
        // Get results
        // Получить результаты
        std::vector<int> getResults() const override;
        
        // Встановити цільовий стан
        // Set target state
        // Установить целевое состояние
        void setTargetState(int target);
        
    private:
        int targetState;  // Цільовий стан / Target state / Целевое состояние
        
        // Створити оракульний вентиль
        // Create oracle gate
        // Создать оракульный вентиль
        QuantumGate createOracleGate();
        
        // Створити вентиль дифузії
        // Create diffusion gate
        // Создать вентиль диффузии
        QuantumGate createDiffusionGate();
    };

    // Квантовий комп'ютер
    // Quantum computer
    // Квантовый компьютер
    class QuantumComputer {
    public:
        QuantumComputer();
        ~QuantumComputer() = default;
        
        // Ініціалізація квантового комп'ютера
        // Initialize quantum computer
        // Инициализация квантового компьютера
        bool initialize(int numQubits);
        
        // Створити квантовий регістр
        // Create quantum register
        // Создать квантовый регистр
        bool createRegister(int numQubits);
        
        // Застосувати вентиль
        // Apply gate
        // Применить вентиль
        bool applyGate(const QuantumGate& gate);
        
        // Виконати квантовий алгоритм
        // Execute quantum algorithm
        // Выполнить квантовый алгоритм
        bool executeAlgorithm(QuantumAlgorithm& algorithm);
        
        // Виміряти всі кубіти
        // Measure all qubits
        // Измерить все кубиты
        std::vector<int> measureAll();
        
        // Виміряти конкретний кубіт
        // Measure specific qubit
        // Измерить конкретный кубит
        int measureQubit(int index);
        
        // Отримати статистику
        // Get statistics
        // Получить статистику
        struct QuantumStatistics {
            int totalQubits;
            int totalGates;
            int totalMeasurements;
            double executionTime;
            std::map<std::string, int> gateUsage;
        };
        
        QuantumStatistics getStatistics() const;
        
        // Скинути статистику
        // Reset statistics
        // Сбросить статистику
        void resetStatistics();
        
    private:
        std::unique_ptr<QuantumRegister> quantumRegister;  // Квантовий регістр / Quantum register / Квантовый регистр
        QuantumStatistics statistics;                      // Статистика / Statistics / Статистика
        bool isInitialized;                                // Прапор ініціалізації / Initialization flag / Флаг инициализации
        
        // Оновити статистику
        // Update statistics
        // Обновить статистику
        void updateStatistics(const QuantumGate& gate);
    };

} // namespace Quantum
} // namespace NeuroSync

#endif // QUANTUM_COMPUTING_H