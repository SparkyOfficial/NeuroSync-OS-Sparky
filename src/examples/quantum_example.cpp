#include "../quantum/QuantumComputing.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace NeuroSync::Quantum;

// Приклад використання квантових обчислень
// Example of using quantum computing
// Пример использования квантовых вычислений

int main() {
    try {
        std::cout << "========================================\n";
        std::cout << "  Quantum Computing Example\n";
        std::cout << "  NeuroSync OS Sparky\n";
        std::cout << "========================================\n\n";
        
        // Створення квантового комп'ютера
        // Create quantum computer
        // Создание квантового компьютера
        std::cout << "Creating quantum computer...\n";
        QuantumComputer quantumComputer;
        
        // Ініціалізація квантового комп'ютера з 3 кубітами
        // Initialize quantum computer with 3 qubits
        // Инициализация квантового компьютера с 3 кубитами
        if (!quantumComputer.initialize(3)) {
            std::cerr << "Failed to initialize quantum computer\n";
            return 1;
        }
        
        std::cout << "Quantum computer initialized with 3 qubits\n\n";
        
        // Створення квантового регістру
        // Create quantum register
        // Создание квантового регистра
        std::cout << "Creating quantum register...\n";
        if (!quantumComputer.createRegister(3)) {
            std::cerr << "Failed to create quantum register\n";
            return 1;
        }
        
        std::cout << "Quantum register created successfully\n\n";
        
        // Демонстрація роботи з кубітами
        // Demonstrate qubit operations
        // Демонстрация работы с кубитами
        std::cout << "Demonstrating qubit operations...\n";
        
        // Створення кубіта
        // Create qubit
        // Создание кубита
        Qubit qubit;
        std::cout << "Created qubit in state |0>\n";
        std::cout << "Probability of |0>: " << qubit.getProbabilityZero() << "\n";
        std::cout << "Probability of |1>: " << qubit.getProbabilityOne() << "\n\n";
        
        // Встановлення суперпозиції
        // Set superposition
        // Установка суперпозиции
        double sqrt2 = std::sqrt(2.0);
        qubit.setAmplitudes(1.0/sqrt2, 0.0, 1.0/sqrt2, 0.0);
        std::cout << "Set qubit in superposition state\n";
        std::cout << "Probability of |0>: " << qubit.getProbabilityZero() << "\n";
        std::cout << "Probability of |1>: " << qubit.getProbabilityOne() << "\n\n";
        
        // Вимірювання кубіта
        // Measure qubit
        // Измерение кубита
        int measurement = qubit.measure();
        std::cout << "Measured qubit: " << measurement << "\n";
        std::cout << "After measurement:\n";
        std::cout << "Probability of |0>: " << qubit.getProbabilityZero() << "\n";
        std::cout << "Probability of |1>: " << qubit.getProbabilityOne() << "\n\n";
        
        // Демонстрація квантових вентилів
        // Demonstrate quantum gates
        // Демонстрация квантовых вентилей
        std::cout << "Demonstrating quantum gates...\n";
        
        // Створення вентиля Адамара
        // Create Hadamard gate
        // Создание вентиля Адамара
        QuantumGate hadamard(QuantumGateType::HADAMARD, 0);
        std::cout << "Created Hadamard gate for qubit 0\n";
        
        // Створення вентиля Паулі X
        // Create Pauli X gate
        // Создание вентиля Паули X
        QuantumGate pauliX(QuantumGateType::PAULI_X, 1);
        std::cout << "Created Pauli X gate for qubit 1\n";
        
        // Створення вентиля CNOT
        // Create CNOT gate
        // Создание вентиля CNOT
        QuantumGate cnot(QuantumGateType::CNOT, 0, 1);
        std::cout << "Created CNOT gate with control qubit 0 and target qubit 1\n\n";
        
        // Застосування вентилів до квантового комп'ютера
        // Apply gates to quantum computer
        // Применение вентилей к квантовому компьютеру
        std::cout << "Applying quantum gates...\n";
        quantumComputer.applyGate(hadamard);
        quantumComputer.applyGate(pauliX);
        quantumComputer.applyGate(cnot);
        std::cout << "Quantum gates applied successfully\n\n";
        
        // Демонстрація квантових алгоритмів
        // Demonstrate quantum algorithms
        // Демонстрация квантовых алгоритмов
        std::cout << "Demonstrating quantum algorithms...\n";
        
        // Алгоритм Дойча-Йожи
        // Deutsch-Jozsa algorithm
        // Алгоритм Дойча-Йожи
        std::cout << "Running Deutsch-Jozsa algorithm...\n";
        DeutschJozsaAlgorithm deutschJozsa;
        if (deutschJozsa.initialize(3)) {
            std::cout << "Deutsch-Jozsa algorithm initialized\n";
            
            // Встановлення оракульної функції
            // Set oracle function
            // Установка оракульной функции
            deutschJozsa.setFunction([](int x) -> int {
                // Приклад констанної функції
                // Example of constant function
                // Пример постоянной функции
                return 0;
            });
            
            if (deutschJozsa.execute()) {
                std::cout << "Deutsch-Jozsa algorithm executed successfully\n";
                auto results = deutschJozsa.getResults();
                std::cout << "Results: ";
                for (int result : results) {
                    std::cout << result << " ";
                }
                std::cout << "\n\n";
            } else {
                std::cout << "Failed to execute Deutsch-Jozsa algorithm\n\n";
            }
        } else {
            std::cout << "Failed to initialize Deutsch-Jozsa algorithm\n\n";
        }
        
        // Алгоритм Гровера
        // Grover's algorithm
        // Алгоритм Гровера
        std::cout << "Running Grover's algorithm...\n";
        GroverAlgorithm grover;
        if (grover.initialize(3)) {
            std::cout << "Grover's algorithm initialized\n";
            
            // Встановлення цільового стану
            // Set target state
            // Установка целевого состояния
            grover.setTargetState(5);
            
            if (grover.execute()) {
                std::cout << "Grover's algorithm executed successfully\n";
                auto results = grover.getResults();
                std::cout << "Results: ";
                for (int result : results) {
                    std::cout << result << " ";
                }
                std::cout << "\n\n";
            } else {
                std::cout << "Failed to execute Grover's algorithm\n\n";
            }
        } else {
            std::cout << "Failed to initialize Grover's algorithm\n\n";
        }
        
        // Вимірювання всіх кубітів
        // Measure all qubits
        // Измерение всех кубитов
        std::cout << "Measuring all qubits...\n";
        auto measurements = quantumComputer.measureAll();
        std::cout << "Measurements: ";
        for (int measurement : measurements) {
            std::cout << measurement << " ";
        }
        std::cout << "\n\n";
        
        // Отримання статистики
        // Get statistics
        // Получение статистики
        std::cout << "Getting quantum computer statistics...\n";
        auto stats = quantumComputer.getStatistics();
        std::cout << "Quantum Computer Statistics:\n";
        std::cout << "  Total Qubits: " << stats.totalQubits << "\n";
        std::cout << "  Total Gates: " << stats.totalGates << "\n";
        std::cout << "  Total Measurements: " << stats.totalMeasurements << "\n";
        std::cout << "  Execution Time: " << stats.executionTime << " ms\n";
        std::cout << "  Gate Usage:\n";
        for (const auto& pair : stats.gateUsage) {
            std::cout << "    " << pair.first << ": " << pair.second << "\n";
        }
        std::cout << "\n";
        
        std::cout << "Quantum Computing Example completed!\n";
        std::cout << "========================================\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}