#ifndef SYNAPSE_BUS_H
#define SYNAPSE_BUS_H

// SynapseBus.h
// Шина синапсів для NeuroSync OS Sparky
// Synapse bus for NeuroSync OS Sparky
// Шина синапсів для NeuroSync OS Sparky

// TODO: Реалізувати механізм зв'язку між нейронами
// TODO: Implement communication mechanism between neurons
// TODO: Реалізувати механізм зв'язку між нейронами

struct Message {
    int senderId;      // ID відправника / Sender ID / ID відправника
    int receiverId;    // ID отримувача / Receiver ID / ID отримувача
    int priority;      // Пріоритет повідомлення / Message priority / Пріоритет повідомлення
    int weight;        // Вага зв'язку / Connection weight / Вага зв'язку
    void* data;        // Дані повідомлення / Message data / Дані повідомлення
    size_t dataSize;   // Розмір даних / Data size / Розмір даних
};

class SynapseBus {
public:
    SynapseBus();
    ~SynapseBus();
    
    // Надіслати повідомлення
    // Send a message
    // Надіслати повідомлення
    bool sendMessage(const Message& message);
    
    // Отримати повідомлення
    // Receive a message
    // Отримати повідомлення
    bool receiveMessage(Message& message);
    
    // Створити зв'язок між нейронами
    // Create connection between neurons
    // Створити зв'язок між нейронами
    bool createConnection(int neuronA, int neuronB, int weight);
    
private:
    // TODO: Реалізувати чергу повідомлень з пріоритетами
    // TODO: Implement priority message queue
    // TODO: Реалізувати чергу повідомлень з пріоритетами
};

#endif // SYNAPSE_BUS_H