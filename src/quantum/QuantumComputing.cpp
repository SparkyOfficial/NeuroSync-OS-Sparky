#include "QuantumComputing.h"
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <cassert>

// QuantumComputing.cpp
// Реалізація модуля квантових обчислень для NeuroSync OS Sparky
// Implementation of quantum computing module for NeuroSync OS Sparky
// Реализация модуля квантовых вычислений для NeuroSync OS Sparky

namespace NeuroSync {
namespace Quantum {

    // Конструктор кубіта
    // Qubit constructor
    // Конструктор кубита
    Qubit::Qubit() : alpha(1.0, 0.0), beta(0.0, 0.0), rng(std::random_device{}()) {}

    // Конструктор кубіта з амплітудами
    // Qubit constructor with amplitudes
    // Конструктор кубита с амплитудами
    Qubit::Qubit(double alphaReal, double alphaImag, double betaReal, double betaImag) 
        : alpha(alphaReal, alphaImag), beta(betaReal, betaImag), rng(std::random_device{}()) {
        normalize();
    }

    // Встановити амплітуди
    // Set amplitudes
    // Установить амплитуды
    void Qubit::setAmplitudes(double alphaReal, double alphaImag, double betaReal, double betaImag) {
        alpha = std::complex<double>(alphaReal, alphaImag);
        beta = std::complex<double>(betaReal, betaImag);
        normalize();
    }

    // Нормалізувати кубіт
    // Normalize qubit
    // Нормализовать кубит
    void Qubit::normalize() {
        double norm = std::abs(alpha) * std::abs(alpha) + std::abs(beta) * std::abs(beta);
        if (norm > 0) {
            double sqrtNorm = std::sqrt(norm);
            alpha /= sqrtNorm;
            beta /= sqrtNorm;
        }
    }

    // Виміряти кубіт
    // Measure qubit
    // Измерить кубит
    int Qubit::measure() {
        double probZero = getProbabilityZero();
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        double randomValue = dis(rng);
        
        if (randomValue < probZero) {
            alpha = std::complex<double>(1.0, 0.0);
            beta = std::complex<double>(0.0, 0.0);
            return 0;
        } else {
            alpha = std::complex<double>(0.0, 0.0);
            beta = std::complex<double>(1.0, 0.0);
            return 1;
        }
    }

    // Отримати ймовірність стану |0>
    // Get probability of state |0>
    // Получить вероятность состояния |0>
    double Qubit::getProbabilityZero() const {
        return std::abs(alpha) * std::abs(alpha);
    }

    // Отримати ймовірність стану |1>
    // Get probability of state |1>
    // Получить вероятность состояния |1>
    double Qubit::getProbabilityOne() const {
        return std::abs(beta) * std::abs(beta);
    }

    // Конструктор квантового вентиля
    // Quantum gate constructor
    // Конструктор квантового вентиля
    QuantumGate::QuantumGate(QuantumGateType type, const std::vector<int>& qubitIndices)
        : gateType(type), qubitIndices(qubitIndices), parameter1(0.0), parameter2(0.0) {}

    // Конструктор квантового вентиля з одним кубітом
    // Quantum gate constructor with single qubit
    // Конструктор квантового вентиля с одним кубитом
    QuantumGate::QuantumGate(QuantumGateType type, int qubitIndex)
        : gateType(type), qubitIndices({qubitIndex}), parameter1(0.0), parameter2(0.0) {}

    // Конструктор квантового вентиля з контрольним та цільовим кубітами
    // Quantum gate constructor with control and target qubits
    // Конструктор квантового вентиля с контрольным и целевым кубитами
    QuantumGate::QuantumGate(QuantumGateType type, int controlIndex, int targetIndex)
        : gateType(type), qubitIndices({controlIndex, targetIndex}), parameter1(0.0), parameter2(0.0) {}

    // Встановити параметри вентиля
    // Set gate parameters
    // Установить параметры вентиля
    void QuantumGate::setParameters(double param1, double param2) {
        parameter1 = param1;
        parameter2 = param2;
    }

    // Отримати матричне представлення вентиля
    // Get matrix representation of gate
    // Получить матричное представление вентиля
    std::vector<std::vector<std::complex<double>>> QuantumGate::getMatrix() const {
        switch (gateType) {
            case QuantumGateType::PAULI_X:
                return createPauliX();
            case QuantumGateType::PAULI_Y:
                return createPauliY();
            case QuantumGateType::PAULI_Z:
                return createPauliZ();
            case QuantumGateType::HADAMARD:
                return createHadamard();
            case QuantumGateType::CNOT:
                return createCNOT();
            case QuantumGateType::TOFFOLI:
                return createToffoli();
            case QuantumGateType::PHASE:
                return createPhase();
            case QuantumGateType::ROTATION_X:
                return createRotationX();
            case QuantumGateType::ROTATION_Y:
                return createRotationY();
            case QuantumGateType::ROTATION_Z:
                return createRotationZ();
            default:
                // Тотожній вентиль за замовчуванням
                // Identity gate by default
                // Тождественный вентиль по умолчанию
                return {{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)},
                        {std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0)}};
        }
    }

    // Створити матрицю Паулі X
    // Create Pauli X matrix
    // Создать матрицу Паули X
    std::vector<std::vector<std::complex<double>>> QuantumGate::createPauliX() const {
        return {{std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0)},
                {std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)}};
    }

    // Створити матрицю Паулі Y
    // Create Pauli Y matrix
    // Создать матрицу Паули Y
    std::vector<std::vector<std::complex<double>>> QuantumGate::createPauliY() const {
        return {{std::complex<double>(0.0, 0.0), std::complex<double>(0.0, -1.0)},
                {std::complex<double>(0.0, 1.0), std::complex<double>(0.0, 0.0)}};
    }

    // Створити матрицю Паулі Z
    // Create Pauli Z matrix
    // Создать матрицу Паули Z
    std::vector<std::vector<std::complex<double>>> QuantumGate::createPauliZ() const {
        return {{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)},
                {std::complex<double>(0.0, 0.0), std::complex<double>(-1.0, 0.0)}};
    }

    // Створити матрицю Адамара
    // Create Hadamard matrix
    // Создать матрицу Адамара
    std::vector<std::vector<std::complex<double>>> QuantumGate::createHadamard() const {
        double sqrt2 = std::sqrt(2.0);
        return {{std::complex<double>(1.0/sqrt2, 0.0), std::complex<double>(1.0/sqrt2, 0.0)},
                {std::complex<double>(1.0/sqrt2, 0.0), std::complex<double>(-1.0/sqrt2, 0.0)}};
    }

    // Створити матрицю CNOT
    // Create CNOT matrix
    // Создать матрицу CNOT
    std::vector<std::vector<std::complex<double>>> QuantumGate::createCNOT() const {
        return {{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 0.0)},
                {std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 0.0)},
                {std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0)},
                {std::complex<double>(0.0, 0.0), std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)}};
    }

    // Створити матрицю Тоффолі
    // Create Toffoli matrix
    // Создать матрицу Тоффоли
    std::vector<std::vector<std::complex<double>>> QuantumGate::createToffoli() const {
        // Тро-кубітна матриця Тоффолі (8x8)
        // Three-qubit Toffoli matrix (8x8)
        // Трех-кубитная матрица Тоффоли (8x8)
        std::vector<std::vector<std::complex<double>>> matrix(8, std::vector<std::complex<double>>(8, std::complex<double>(0.0, 0.0)));
        
        // Заповнення одиничною матрицею
        // Fill with identity matrix
        // Заполнение единичной матрицей
        for (int i = 0; i < 8; ++i) {
            matrix[i][i] = std::complex<double>(1.0, 0.0);
        }
        
        // Зміна останніх двох рядків для реалізації Тоффолі
        // Change last two rows to implement Toffoli
        // Изменение последних двух строк для реализации Тоффоли
        matrix[6][6] = std::complex<double>(0.0, 0.0);
        matrix[6][7] = std::complex<double>(1.0, 0.0);
        matrix[7][6] = std::complex<double>(1.0, 0.0);
        matrix[7][7] = std::complex<double>(0.0, 0.0);
        
        return matrix;
    }

    // Створити фазову матрицю
    // Create phase matrix
    // Создать фазовую матрицу
    std::vector<std::vector<std::complex<double>>> QuantumGate::createPhase() const {
        double cosParam = std::cos(parameter1);
        double sinParam = std::sin(parameter1);
        return {{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)},
                {std::complex<double>(0.0, 0.0), std::complex<double>(cosParam, sinParam)}};
    }

    // Створити матрицю обертання навколо осі X
    // Create rotation matrix around X axis
    // Создать матрицу вращения вокруг оси X
    std::vector<std::vector<std::complex<double>>> QuantumGate::createRotationX() const {
        double cosHalf = std::cos(parameter1 / 2.0);
        double sinHalf = std::sin(parameter1 / 2.0);
        return {{std::complex<double>(cosHalf, 0.0), std::complex<double>(0.0, -sinHalf)},
                {std::complex<double>(0.0, -sinHalf), std::complex<double>(cosHalf, 0.0)}};
    }

    // Створити матрицю обертання навколо осі Y
    // Create rotation matrix around Y axis
    // Создать матрицу вращения вокруг оси Y
    std::vector<std::vector<std::complex<double>>> QuantumGate::createRotationY() const {
        double cosHalf = std::cos(parameter1 / 2.0);
        double sinHalf = std::sin(parameter1 / 2.0);
        return {{std::complex<double>(cosHalf, 0.0), std::complex<double>(-sinHalf, 0.0)},
                {std::complex<double>(sinHalf, 0.0), std::complex<double>(cosHalf, 0.0)}};
    }

    // Створити матрицю обертання навколо осі Z
    // Create rotation matrix around Z axis
    // Создать матрицу вращения вокруг оси Z
    std::vector<std::vector<std::complex<double>>> QuantumGate::createRotationZ() const {
        double cosHalf = std::cos(parameter1 / 2.0);
        double sinHalf = std::sin(parameter1 / 2.0);
        return {{std::complex<double>(cosHalf, -sinHalf), std::complex<double>(0.0, 0.0)},
                {std::complex<double>(0.0, 0.0), std::complex<double>(cosHalf, sinHalf)}};
    }

    // Конструктор квантового регістру
    // Quantum register constructor
    // Конструктор квантового регистра
    QuantumRegister::QuantumRegister(int numQubits) : qubits(numQubits) {}

    // Отримати кубіт за індексом
    // Get qubit by index
    // Получить кубит по индексу
    Qubit& QuantumRegister::getQubit(int index) {
        if (index < 0 || index >= static_cast<int>(qubits.size())) {
            throw std::out_of_range("Qubit index out of range");
        }
        return qubits[index];
    }

    // Отримати кубіт за індексом (const версія)
    // Get qubit by index (const version)
    // Получить кубит по индексу (const версия)
    const Qubit& QuantumRegister::getQubit(int index) const {
        if (index < 0 || index >= static_cast<int>(qubits.size())) {
            throw std::out_of_range("Qubit index out of range");
        }
        return qubits[index];
    }

    // Встановити стан кубіта
    // Set qubit state
    // Установить состояние кубита
    void QuantumRegister::setQubitState(int index, double alphaReal, double alphaImag, double betaReal, double betaImag) {
        if (index < 0 || index >= static_cast<int>(qubits.size())) {
            throw std::out_of_range("Qubit index out of range");
        }
        qubits[index].setAmplitudes(alphaReal, alphaImag, betaReal, betaImag);
    }

    // Ініціалізувати всі кубіти в стані |0>
    // Initialize all qubits in state |0>
    // Инициализировать все кубиты в состоянии |0>
    void QuantumRegister::initializeZero() {
        for (auto& qubit : qubits) {
            qubit.setAmplitudes(1.0, 0.0, 0.0, 0.0);
        }
    }

    // Ініціалізувати всі кубіти в стані |1>
    // Initialize all qubits in state |1>
    // Инициализировать все кубиты в состоянии |1>
    void QuantumRegister::initializeOne() {
        for (auto& qubit : qubits) {
            qubit.setAmplitudes(0.0, 0.0, 1.0, 0.0);
        }
    }

    // Ініціалізувати всі кубіти в суперпозиції
    // Initialize all qubits in superposition
    // Инициализировать все кубиты в суперпозиции
    void QuantumRegister::initializeSuperposition() {
        double sqrt2 = std::sqrt(2.0);
        for (auto& qubit : qubits) {
            qubit.setAmplitudes(1.0/sqrt2, 0.0, 1.0/sqrt2, 0.0);
        }
    }

    // Застосувати вентиль до регістру
    // Apply gate to register
    // Применить вентиль к регистру
    void QuantumRegister::applyGate(const QuantumGate& gate) {
        const auto& indices = gate.getQubitIndices();
        
        switch (indices.size()) {
            case 1:
                applySingleQubitGate(gate);
                break;
            case 2:
                applyTwoQubitGate(gate);
                break;
            case 3:
                applyThreeQubitGate(gate);
                break;
            default:
                throw std::invalid_argument("Unsupported number of qubits for gate");
        }
    }

    // Виміряти всі кубіти
    // Measure all qubits
    // Измерить все кубиты
    std::vector<int> QuantumRegister::measureAll() {
        std::vector<int> results;
        results.reserve(qubits.size());
        
        for (auto& qubit : qubits) {
            results.push_back(qubit.measure());
        }
        
        return results;
    }

    // Виміряти конкретний кубіт
    // Measure specific qubit
    // Измерить конкретный кубит
    int QuantumRegister::measureQubit(int index) {
        if (index < 0 || index >= static_cast<int>(qubits.size())) {
            throw std::out_of_range("Qubit index out of range");
        }
        return qubits[index].measure();
    }

    // Отримати стан регістру як вектор амплітуд
    // Get register state as amplitude vector
    // Получить состояние регистра как вектор амплитуд
    std::vector<std::complex<double>> QuantumRegister::getStateVector() const {
        // Для n кубітів вектор стану має 2^n елементів
        // For n qubits, state vector has 2^n elements
        // Для n кубитов вектор состояния имеет 2^n элементов
        int numStates = 1 << qubits.size();
        std::vector<std::complex<double>> stateVector(numStates);
        
        // Проста реалізація для одного кубіта
        // Simple implementation for one qubit
        // Простая реализация для одного кубита
        if (qubits.size() == 1) {
            stateVector[0] = qubits[0].getAlpha();
            stateVector[1] = qubits[0].getBeta();
        } else {
            // Для багатьох кубітів потрібна більш складна реалізація
            // For multiple qubits, more complex implementation is needed
            // Для многих кубитов нужна более сложная реализация
            // Це спрощена реалізація
            // This is a simplified implementation
            for (int i = 0; i < std::min(numStates, static_cast<int>(qubits.size())); ++i) {
                stateVector[i] = qubits[i].getAlpha();
            }
        }
        
        return stateVector;
    }

    // Встановити стан регістру з вектора амплітуд
    // Set register state from amplitude vector
    // Установить состояние регистра из вектора амплитуд
    void QuantumRegister::setStateVector(const std::vector<std::complex<double>>& state) {
        // Проста реалізація для одного кубіта
        // Simple implementation for one qubit
        // Простая реализация для одного кубита
        if (qubits.size() == 1 && state.size() >= 2) {
            qubits[0].setAmplitudes(state[0].real(), state[0].imag(), state[1].real(), state[1].imag());
        }
        // Для багатьох кубітів потрібна більш складна реалізація
        // For multiple qubits, more complex implementation is needed
        // Для многих кубитов нужна более сложная реализация
    }

    // Застосувати одно-кубітний вентиль
    // Apply single-qubit gate
    // Применить одно-кубитный вентиль
    void QuantumRegister::applySingleQubitGate(const QuantumGate& gate) {
        const auto& indices = gate.getQubitIndices();
        if (indices.empty()) {
            return;
        }
        
        int qubitIndex = indices[0];
        if (qubitIndex < 0 || qubitIndex >= static_cast<int>(qubits.size())) {
            throw std::out_of_range("Qubit index out of range");
        }
        
        // Отримати матрицю вентиля
        // Get gate matrix
        // Получить матрицу вентиля
        auto matrix = gate.getMatrix();
        if (matrix.size() != 2 || matrix[0].size() != 2) {
            throw std::invalid_argument("Invalid single-qubit gate matrix");
        }
        
        // Застосувати вентиль до кубіта
        // Apply gate to qubit
        // Применить вентиль к кубиту
        Qubit& qubit = qubits[qubitIndex];
        std::complex<double> oldAlpha = qubit.getAlpha();
        std::complex<double> oldBeta = qubit.getBeta();
        
        std::complex<double> newAlpha = matrix[0][0] * oldAlpha + matrix[0][1] * oldBeta;
        std::complex<double> newBeta = matrix[1][0] * oldAlpha + matrix[1][1] * oldBeta;
        
        qubit.setAmplitudes(newAlpha.real(), newAlpha.imag(), newBeta.real(), newBeta.imag());
    }

    // Застосувати дво-кубітний вентиль
    // Apply two-qubit gate
    // Применить двух-кубитный вентиль
    void QuantumRegister::applyTwoQubitGate(const QuantumGate& gate) {
        // У цій реалізації ми просто виводимо повідомлення
        // In this implementation we just print a message
        // В этой реализации мы просто выводим сообщение
        const auto& indices = gate.getQubitIndices();
        std::cout << "Applying two-qubit gate to qubits " << indices[0] << " and " << indices[1] << std::endl;
    }

    // Застосувати три-кубітний вентиль
    // Apply three-qubit gate
    // Применить трех-кубитный вентиль
    void QuantumRegister::applyThreeQubitGate(const QuantumGate& gate) {
        // У цій реалізації ми просто виводимо повідомлення
        // In this implementation we just print a message
        // В этой реализации мы просто выводим сообщение
        const auto& indices = gate.getQubitIndices();
        std::cout << "Applying three-qubit gate to qubits " << indices[0] << ", " << indices[1] << ", and " << indices[2] << std::endl;
    }

    // Нормалізувати стан регістру
    // Normalize register state
    // Нормализовать состояние регистра
    void QuantumRegister::normalize() {
        // У цій реалізації ми просто нормалізуємо кожен кубіт окремо
        // In this implementation we just normalize each qubit separately
        // В этой реализации мы просто нормализуем каждый кубит отдельно
        for (auto& qubit : qubits) {
            qubit.normalize();
        }
    }

    // Конструктор квантового алгоритму
    // Quantum algorithm constructor
    // Конструктор квантового алгоритма
    QuantumAlgorithm::QuantumAlgorithm(const std::string& name) : algorithmName(name) {}

    // Встановити квантовий регістр
    // Set quantum register
    // Установить квантовый регистр
    void QuantumAlgorithm::setQuantumRegister(std::unique_ptr<QuantumRegister> reg) {
        quantumRegister = std::move(reg);
    }

    // Отримати квантовий регістр
    // Get quantum register
    // Получить квантовый регистр
    QuantumRegister* QuantumAlgorithm::getQuantumRegister() const {
        return quantumRegister.get();
    }

    // Конструктор алгоритму Дойча-Йожи
    // Deutsch-Jozsa algorithm constructor
    // Конструктор алгоритма Дойча-Йожи
    DeutschJozsaAlgorithm::DeutschJozsaAlgorithm() : QuantumAlgorithm("Deutsch-Jozsa") {}

    // Ініціалізація алгоритму Дойча-Йожи
    // Initialize Deutsch-Jozsa algorithm
    // Инициализация алгоритма Дойча-Йожи
    bool DeutschJozsaAlgorithm::initialize(int numQubits) {
        if (numQubits < 2) {
            return false;
        }
        
        setQuantumRegister(std::make_unique<QuantumRegister>(numQubits));
        quantumRegister->initializeZero();
        return true;
    }

    // Виконати алгоритм Дойча-Йожи
    // Execute Deutsch-Jozsa algorithm
    // Выполнить алгоритм Дойча-Йожи
    bool DeutschJozsaAlgorithm::execute() {
        if (!quantumRegister) {
            return false;
        }
        
        int numQubits = quantumRegister->getNumQubits();
        if (numQubits < 2) {
            return false;
        }
        
        // Застосувати вентиль Адамара до всіх кубітів
        // Apply Hadamard gate to all qubits
        // Применить вентиль Адамара ко всем кубитам
        for (int i = 0; i < numQubits; ++i) {
            QuantumGate hadamard(QuantumGateType::HADAMARD, i);
            quantumRegister->applyGate(hadamard);
        }
        
        // Застосувати оракульну функцію
        // Apply oracle function
        // Применить оракульную функцию
        // У цій реалізації ми просто виводимо повідомлення
        // In this implementation we just print a message
        // В этой реализации мы просто выводим сообщение
        std::cout << "Applying oracle function in Deutsch-Jozsa algorithm" << std::endl;
        
        // Застосувати вентиль Адамара знову
        // Apply Hadamard gate again
        // Применить вентиль Адамара снова
        for (int i = 0; i < numQubits; ++i) {
            QuantumGate hadamard(QuantumGateType::HADAMARD, i);
            quantumRegister->applyGate(hadamard);
        }
        
        return true;
    }

    // Отримати результати алгоритму Дойча-Йожи
    // Get results of Deutsch-Jozsa algorithm
    // Получить результаты алгоритма Дойча-Йожи
    std::vector<int> DeutschJozsaAlgorithm::getResults() const {
        if (!quantumRegister) {
            return {};
        }
        
        return quantumRegister->measureAll();
    }

    // Встановити функцію
    // Set function
    // Установить функцию
    void DeutschJozsaAlgorithm::setFunction(const std::function<int(int)>& func) {
        oracleFunction = func;
    }

    // Конструктор алгоритму Гровера
    // Grover's algorithm constructor
    // Конструктор алгоритма Гровера
    GroverAlgorithm::GroverAlgorithm() : QuantumAlgorithm("Grover"), targetState(0) {}

    // Ініціалізація алгоритму Гровера
    // Initialize Grover's algorithm
    // Инициализация алгоритма Гровера
    bool GroverAlgorithm::initialize(int numQubits) {
        if (numQubits < 1) {
            return false;
        }
        
        setQuantumRegister(std::make_unique<QuantumRegister>(numQubits));
        quantumRegister->initializeSuperposition();
        return true;
    }

    // Виконати алгоритм Гровера
    // Execute Grover's algorithm
    // Выполнить алгоритм Гровера
    bool GroverAlgorithm::execute() {
        if (!quantumRegister) {
            return false;
        }
        
        int numQubits = quantumRegister->getNumQubits();
        if (numQubits < 1) {
            return false;
        }
        
        // Кількість ітерацій Гровера
        // Number of Grover iterations
        // Количество итераций Гровера
        int iterations = static_cast<int>(std::floor(std::pi / 4.0 * std::sqrt(1 << numQubits)));
        
        // Виконати ітерації
        // Execute iterations
        // Выполнить итерации
        for (int i = 0; i < iterations; ++i) {
            // Застосувати оракульний вентиль
            // Apply oracle gate
            // Применить оракульный вентиль
            QuantumGate oracle = createOracleGate();
            quantumRegister->applyGate(oracle);
            
            // Застосувати вентиль дифузії
            // Apply diffusion gate
            // Применить вентиль диффузии
            QuantumGate diffusion = createDiffusionGate();
            quantumRegister->applyGate(diffusion);
        }
        
        return true;
    }

    // Отримати результати алгоритму Гровера
    // Get results of Grover's algorithm
    // Получить результаты алгоритма Гровера
    std::vector<int> GroverAlgorithm::getResults() const {
        if (!quantumRegister) {
            return {};
        }
        
        return quantumRegister->measureAll();
    }

    // Встановити цільовий стан
    // Set target state
    // Установить целевое состояние
    void GroverAlgorithm::setTargetState(int target) {
        targetState = target;
    }

    // Створити оракульний вентиль
    // Create oracle gate
    // Создать оракульный вентиль
    QuantumGate GroverAlgorithm::createOracleGate() {
        // У цій реалізації ми створюємо простий оракульний вентиль
        // In this implementation we create a simple oracle gate
        // В этой реализации мы создаем простой оракульный вентиль
        QuantumGate oracle(QuantumGateType::PAULI_Z, 0);
        return oracle;
    }

    // Створити вентиль дифузії
    // Create diffusion gate
    // Создать вентиль диффузии
    QuantumGate GroverAlgorithm::createDiffusionGate() {
        // У цій реалізації ми створюємо простий вентиль дифузії
        // In this implementation we create a simple diffusion gate
        // В этой реализации мы создаем простой вентиль диффузии
        QuantumGate diffusion(QuantumGateType::HADAMARD, 0);
        return diffusion;
    }

    // Конструктор квантового комп'ютера
    // Quantum computer constructor
    // Конструктор квантового компьютера
    QuantumComputer::QuantumComputer() : isInitialized(false) {
        resetStatistics();
    }

    // Ініціалізація квантового комп'ютера
    // Initialize quantum computer
    // Инициализация квантового компьютера
    bool QuantumComputer::initialize(int numQubits) {
        if (numQubits <= 0) {
            return false;
        }
        
        quantumRegister = std::make_unique<QuantumRegister>(numQubits);
        quantumRegister->initializeZero();
        isInitialized = true;
        return true;
    }

    // Створити квантовий регістр
    // Create quantum register
    // Создать квантовый регистр
    bool QuantumComputer::createRegister(int numQubits) {
        if (numQubits <= 0) {
            return false;
        }
        
        quantumRegister = std::make_unique<QuantumRegister>(numQubits);
        quantumRegister->initializeZero();
        return true;
    }

    // Застосувати вентиль
    // Apply gate
    // Применить вентиль
    bool QuantumComputer::applyGate(const QuantumGate& gate) {
        if (!quantumRegister || !isInitialized) {
            return false;
        }
        
        auto startTime = std::chrono::high_resolution_clock::now();
        
        try {
            quantumRegister->applyGate(gate);
            updateStatistics(gate);
        } catch (const std::exception& e) {
            std::cerr << "Error applying gate: " << e.what() << std::endl;
            return false;
        }
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        statistics.executionTime += duration.count() / 1000.0; // Convert to milliseconds
        
        return true;
    }

    // Виконати квантовий алгоритм
    // Execute quantum algorithm
    // Выполнить квантовый алгоритм
    bool QuantumComputer::executeAlgorithm(QuantumAlgorithm& algorithm) {
        if (!isInitialized) {
            return false;
        }
        
        auto startTime = std::chrono::high_resolution_clock::now();
        
        bool success = algorithm.execute();
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        statistics.executionTime += duration.count() / 1000.0; // Convert to milliseconds
        
        return success;
    }

    // Виміряти всі кубіти
    // Measure all qubits
    // Измерить все кубиты
    std::vector<int> QuantumComputer::measureAll() {
        if (!quantumRegister || !isInitialized) {
            return {};
        }
        
        statistics.totalMeasurements++;
        return quantumRegister->measureAll();
    }

    // Виміряти конкретний кубіт
    // Measure specific qubit
    // Измерить конкретный кубит
    int QuantumComputer::measureQubit(int index) {
        if (!quantumRegister || !isInitialized) {
            return -1;
        }
        
        statistics.totalMeasurements++;
        return quantumRegister->measureQubit(index);
    }

    // Отримати статистику
    // Get statistics
    // Получить статистику
    QuantumComputer::QuantumStatistics QuantumComputer::getStatistics() const {
        return statistics;
    }

    // Скинути статистику
    // Reset statistics
    // Сбросить статистику
    void QuantumComputer::resetStatistics() {
        statistics.totalQubits = 0;
        statistics.totalGates = 0;
        statistics.totalMeasurements = 0;
        statistics.executionTime = 0.0;
        statistics.gateUsage.clear();
    }

    // Оновити статистику
    // Update statistics
    // Обновить статистику
    void QuantumComputer::updateStatistics(const QuantumGate& gate) {
        statistics.totalGates++;
        
        // Оновити використання вентилів
        // Update gate usage
        // Обновить использование вентилей
        std::string gateName;
        switch (gate.getType()) {
            case QuantumGateType::PAULI_X:
                gateName = "Pauli-X";
                break;
            case QuantumGateType::PAULI_Y:
                gateName = "Pauli-Y";
                break;
            case QuantumGateType::PAULI_Z:
                gateName = "Pauli-Z";
                break;
            case QuantumGateType::HADAMARD:
                gateName = "Hadamard";
                break;
            case QuantumGateType::CNOT:
                gateName = "CNOT";
                break;
            case QuantumGateType::TOFFOLI:
                gateName = "Toffoli";
                break;
            case QuantumGateType::PHASE:
                gateName = "Phase";
                break;
            case QuantumGateType::ROTATION_X:
                gateName = "Rotation-X";
                break;
            case QuantumGateType::ROTATION_Y:
                gateName = "Rotation-Y";
                break;
            case QuantumGateType::ROTATION_Z:
                gateName = "Rotation-Z";
                break;
            default:
                gateName = "Unknown";
                break;
        }
        
        statistics.gateUsage[gateName]++;
    }

} // namespace Quantum
} // namespace NeuroSync