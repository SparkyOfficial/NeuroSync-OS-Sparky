#ifndef NEURO_API_H
#define NEURO_API_H

// NeuroAPI.h
// C++ інтерфейс для NeuroSync OS Sparky
// C++ interface for NeuroSync OS Sparky
// C++ інтерфейс для NeuroSync OS Sparky

// TODO: Реалізувати C++ інтерфейс для створення та управління нейронами
// TODO: Implement C++ interface for creating and managing neurons
// TODO: Реалізувати C++ інтерфейс для створення та управління нейронами

// Функції API для роботи з нейронами
// API functions for working with neurons
// Функції API для роботи з нейронами

#ifdef __cplusplus
extern "C" {
#endif

// Ініціалізація системи
// System initialization
// Ініціалізація системи
void neurosync_init();

// Створення нейрона
// Create a neuron
// Створення нейрона
int neurosync_create_neuron(void (*process_function)());

// Видалення нейрона
// Delete a neuron
// Видалення нейрона
void neurosync_delete_neuron(int neuron_id);

// Створення зв'язку між нейронами
// Create connection between neurons
// Створення зв'язку між нейронами
bool neurosync_create_connection(int neuron_a, int neuron_b, int weight);

// Надсилання повідомлення нейрону
// Send message to neuron
// Надсилання повідомлення нейрону
bool neurosync_send_message(int sender_id, int receiver_id, void* data, size_t data_size, int priority, int weight);

// Запуск системи
// Start the system
// Запуск системи
void neurosync_start();

// Зупинка системи
// Stop the system
// Зупинка системи
void neurosync_stop();

#ifdef __cplusplus
}
#endif

#endif // NEURO_API_H