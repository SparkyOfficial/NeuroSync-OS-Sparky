#include "Diagnostics.h"
#include <cstdio>

// Diagnostics.cpp
// Реалізація модуля діагностики для NeuroSync OS Sparky
// Implementation of diagnostics module for NeuroSync OS Sparky
// Реалізація модуля діагностики для NeuroSync OS Sparky

Diagnostics::Diagnostics() : tracingEnabled(false) {
    // TODO: Ініціалізація модуля діагностики
    // TODO: Initialize diagnostics module
    // TODO: Ініціалізувати модуль діагностики
}

Diagnostics::~Diagnostics() {
    // TODO: Очищення ресурсів модуля діагностики
    // TODO: Clean up diagnostics module resources
    // TODO: Очистити ресурси модуля діагностики
}

void Diagnostics::startTracing() {
    // TODO: Почати трасування активності нейронів
    // TODO: Start tracing neuron activity
    // TODO: Почати трасування активності нейронів
    tracingEnabled = true;
    printf("[DIAGNOSTICS] Tracing started\n");
    printf("[ДІАГНОСТИКА] Трасування розпочато\n");
    printf("[ДИАГНОСТИКА] Трассировка начата\n");
}

void Diagnostics::stopTracing() {
    // TODO: Зупинити трасування активності нейронів
    // TODO: Stop tracing neuron activity
    // TODO: Зупинити трасування активності нейронів
    tracingEnabled = false;
    printf("[DIAGNOSTICS] Tracing stopped\n");
    printf("[ДІАГНОСТИКА] Трасування зупинено\n");
    printf("[ДИАГНОСТИКА] Трассировка остановлена\n");
}

void Diagnostics::logEvent(int neuronId, const char* event) {
    // TODO: Записати подію в журнал діагностики
    // TODO: Log event to diagnostics journal
    // TODO: Записати подію в журнал діагностики
    if (tracingEnabled) {
        printf("[NEURON %d] %s\n", neuronId, event);
        printf("[НЕЙРОН %d] %s\n", neuronId, event);
        printf("[НЕЙРОН %d] %s\n", neuronId, event);
    }
}

void Diagnostics::getReport() {
    // TODO: Сформувати звіт про активність нейронів
    // TODO: Generate neuron activity report
    // TODO: Сформувати звіт про активність нейронів
    printf("[DIAGNOSTICS] Activity report\n");
    printf("[ДІАГНОСТИКА] Звіт про активність\n");
    printf("[ДИАГНОСТИКА] Отчет об активности\n");
}