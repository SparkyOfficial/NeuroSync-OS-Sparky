#include "../threadpool/ThreadPool.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

// Приклад використання пулу потоків
// Thread pool usage example
// Пример использования пула потоков

// Функція для обчислення факторіала
// Factorial calculation function
// Функция для вычисления факториала
unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Функція для обчислення чисел Фібоначчі
// Fibonacci numbers calculation function
// Функция для вычисления чисел Фибоначчи
unsigned long long fibonacci(int n) {
    if (n <= 1) return n;
    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Функція для обчислення простих чисел
// Prime numbers calculation function
// Функция для вычисления простых чисел
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cout << "=== ThreadPool Example ===" << std::endl;
    
    // Створення пулу потоків з 4 потоками
    // Creating thread pool with 4 threads
    // Создание пула потоков с 4 потоками
    NeuroSync::ThreadPool pool(4);
    
    std::cout << "Created thread pool with " << pool.getThreadCount() << " threads" << std::endl;
    
    // Вектор для зберігання результатів
    // Vector to store results
    // Вектор для хранения результатов
    std::vector<std::future<unsigned long long>> factorialResults;
    std::vector<std::future<unsigned long long>> fibonacciResults;
    std::vector<std::future<bool>> primeResults;
    
    // Додавання завдань для обчислення факторіалів
    // Adding tasks for factorial calculations
    // Добавление задач для вычисления факториалов
    std::cout << "\nEnqueuing factorial tasks..." << std::endl;
    for (int i = 10; i <= 15; ++i) {
        auto future = pool.enqueue(factorial, i);
        factorialResults.push_back(std::move(future));
    }
    
    // Додавання завдань для обчислення чисел Фібоначчі
    // Adding tasks for Fibonacci calculations
    // Добавление задач для вычисления чисел Фибоначчи
    std::cout << "Enqueuing Fibonacci tasks..." << std::endl;
    for (int i = 30; i <= 35; ++i) {
        auto future = pool.enqueue(fibonacci, i);
        fibonacciResults.push_back(std::move(future));
    }
    
    // Додавання завдань для перевірки простих чисел
    // Adding tasks for prime checking
    // Добавление задач для проверки простых чисел
    std::cout << "Enqueuing prime checking tasks..." << std::endl;
    for (int i = 999990; i <= 999999; ++i) {
        auto future = pool.enqueue(isPrime, i);
        primeResults.push_back(std::move(future));
    }
    
    std::cout << "Total tasks in queue: " << pool.getQueueSize() << std::endl;
    
    // Очікування результатів обчислень факторіалів
    // Waiting for factorial calculation results
    // Ожидание результатов вычисления факториалов
    std::cout << "\nFactorial Results:" << std::endl;
    for (size_t i = 0; i < factorialResults.size(); ++i) {
        int n = 10 + static_cast<int>(i);
        unsigned long long result = factorialResults[i].get();
        std::cout << "factorial(" << n << ") = " << result << std::endl;
    }
    
    // Очікування результатів обчислень чисел Фібоначчі
    // Waiting for Fibonacci calculation results
    // Ожидание результатов вычисления чисел Фибоначчи
    std::cout << "\nFibonacci Results:" << std::endl;
    for (size_t i = 0; i < fibonacciResults.size(); ++i) {
        int n = 30 + static_cast<int>(i);
        unsigned long long result = fibonacciResults[i].get();
        std::cout << "fibonacci(" << n << ") = " << result << std::endl;
    }
    
    // Очікування результатів перевірки простих чисел
    // Waiting for prime checking results
    // Ожидание результатов проверки простых чисел
    std::cout << "\nPrime Checking Results:" << std::endl;
    for (size_t i = 0; i < primeResults.size(); ++i) {
        int n = 999990 + static_cast<int>(i);
        bool result = primeResults[i].get();
        std::cout << n << " is " << (result ? "prime" : "not prime") << std::endl;
    }
    
    // Демонстрація перезапуску пулу потоків
    // Demonstrating thread pool restart
    // Демонстрация перезапуска пула потоков
    std::cout << "\nRestarting thread pool..." << std::endl;
    pool.restart();
    std::cout << "Thread pool restarted with " << pool.getThreadCount() << " threads" << std::endl;
    
    // Додавання ще одного завдання після перезапуску
    // Adding another task after restart
    // Добавление еще одной задачи после перезапуска
    auto future = pool.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 42;
    });
    
    std::cout << "Result from task after restart: " << future.get() << std::endl;
    
    std::cout << "\nThreadPool example completed!" << std::endl;
    
    return 0;
}