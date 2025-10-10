#ifndef SCHEDULER_H
#define SCHEDULER_H

// Scheduler.h
// Планувальник задач для NeuroSync OS Sparky
// Task scheduler for NeuroSync OS Sparky
// Планувальник завдань для NeuroSync OS Sparky

// TODO: Реалізувати планировник задач який працює з нейронами
// TODO: Implement a task scheduler that works with neurons
// TODO: Реалізувати планувальник завдань, який працює з нейронами

class Scheduler {
public:
    Scheduler();
    ~Scheduler();
    
    // Запустити планувальник
    // Start the scheduler
    // Запустити планувальник
    void start();
    
    // Зупинити планувальник
    // Stop the scheduler
    // Зупинити планувальник
    void stop();
    
    // Додати задачу до планувальника
    // Add a task to the scheduler
    // Додати завдання до планувальника
    void addTask(void (*task)(), int priority);
    
private:
    bool running;
};

#endif // SCHEDULER_H