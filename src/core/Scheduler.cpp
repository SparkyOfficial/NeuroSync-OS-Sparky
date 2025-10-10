#include "Scheduler.h"

// Scheduler.cpp
// Реалізація планувальника задач для NeuroSync OS Sparky
// Implementation of the task scheduler for NeuroSync OS Sparky
// Реалізація планувальника завдань для NeuroSync OS Sparky

Scheduler::Scheduler() : running(false) {
    // TODO: Ініціалізація планувальника
    // TODO: Initialize the scheduler
    // TODO: Ініціалізувати планувальник
}

Scheduler::~Scheduler() {
    // TODO: Очищення ресурсів планувальника
    // TODO: Clean up scheduler resources
    // TODO: Очистити ресурси планувальника
}

void Scheduler::start() {
    // TODO: Запустити цикл планувальника
    // TODO: Start the scheduler loop
    // TODO: Запустити цикл планувальника
    running = true;
}

void Scheduler::stop() {
    // TODO: Зупинити цикл планувальника
    // TODO: Stop the scheduler loop
    // TODO: Зупинити цикл планувальника
    running = false;
}

void Scheduler::addTask(void (*task)(), int priority) {
    // TODO: Додати задачу до черги задач з відповідним пріоритетом
    // TODO: Add a task to the task queue with appropriate priority
    // TODO: Додати завдання до черги завдань з відповідним пріоритетом
}