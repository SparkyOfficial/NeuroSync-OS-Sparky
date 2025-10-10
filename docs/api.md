# API Documentation for NeuroSync OS Sparky

## Overview

The NeuroSync OS Sparky API provides a comprehensive C interface for creating, managing, and interacting with neuron-based processes. The API is designed to be simple yet powerful, allowing developers to build complex neural networks and distributed systems.

## Basic API Functions

### System Initialization

```c
void neurosync_init();
```

Initializes the NeuroSync OS Sparky system, setting up all necessary components including the neuron manager, synapse bus, scheduler, and diagnostics.

### Neuron Management

```c
int neurosync_create_neuron(void (*process_function)());
```

Creates a new neuron with an optional processing function.

```c
void neurosync_delete_neuron(int neuron_id);
```

Deletes a neuron by its ID.

### Connection Management

```c
bool neurosync_create_connection(int neuron_a, int neuron_b, int weight);
```

Creates a connection between two neurons with a specified weight.

### Message Passing

```c
bool neurosync_send_message(int sender_id, int receiver_id, void* data, size_t data_size, int priority, int weight);
```

Sends a message from one neuron to another with specified priority and weight.

### System Control

```c
void neurosync_start();
void neurosync_stop();
```

Starts and stops the NeuroSync system.

## Advanced API Functions

### Enhanced Neuron Creation

```c
int neurosync_create_neuron_advanced(NeuroSyncNeuronType type, const char* name);
```

Creates a neuron with a specific type and name. Available neuron types:
- `NEURON_TYPE_INPUT` - Input neuron
- `NEURON_TYPE_HIDDEN` - Hidden neuron
- `NEURON_TYPE_OUTPUT` - Output neuron
- `NEURON_TYPE_PROCESSING` - Processing neuron
- `NEURON_TYPE_MEMORY` - Memory neuron

### Neuron Activation Control

```c
bool neurosync_activate_neuron(int neuron_id);
bool neurosync_deactivate_neuron(int neuron_id);
```

Activates or deactivates a neuron.

### Neuron Statistics

```c
int neurosync_get_active_neuron_count();
int neurosync_get_total_neuron_count();
```

Retrieves statistics about neuron counts.

### Advanced Message Passing

```c
bool neurosync_send_message_advanced(int sender_id, int receiver_id, 
                                   const void* data, size_t data_size,
                                   NeuroSyncMessagePriority priority, double weight);
```

Sends a message with more detailed priority control:
- `MESSAGE_PRIORITY_LOW` - Low priority
- `MESSAGE_PRIORITY_NORMAL` - Normal priority
- `MESSAGE_PRIORITY_HIGH` - High priority
- `MESSAGE_PRIORITY_CRITICAL` - Critical priority

### Message Reception

```c
bool neurosync_receive_message(int* sender_id, int* receiver_id, 
                              void** data, size_t* data_size,
                              NeuroSyncMessagePriority* priority, double* weight);
```

Receives a message from the synapse bus.

### Connection Management

```c
bool neurosync_update_connection_weight(int neuron_a, int neuron_b, double weight);
double neurosync_get_connection_weight(int neuron_a, int neuron_b);
bool neurosync_activate_connection(int neuron_a, int neuron_b);
bool neurosync_deactivate_connection(int neuron_a, int neuron_b);
```

Advanced connection management functions for updating weights and activating/deactivating connections.

### System Statistics

```c
size_t neurosync_get_connection_count();
size_t neurosync_get_message_queue_size();
NeuroSyncSystemStatistics neurosync_get_system_statistics();
```

Retrieves various system statistics including connection counts, message queue sizes, and detailed system metrics.

### Neuron Configuration

```c
bool neurosync_set_neuron_threshold(int neuron_id, double threshold);
double neurosync_get_neuron_threshold(int neuron_id);
bool neurosync_set_neuron_callback(int neuron_id, void (*callback_function)());
int neurosync_get_neuron_id_by_name(const char* name);
```

Functions for configuring neuron behavior and retrieving neuron information by name.

## Integration Examples

### Simple Neuron Network

```c
#include "api/NeuroAPI.h"

void process_function() {
    // Neuron processing logic
}

int main() {
    // Initialize system
    neurosync_init();
    
    // Create neurons
    int input_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_INPUT, "Input");
    int hidden_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_HIDDEN, "Hidden");
    int output_neuron = neurosync_create_neuron_advanced(NEURON_TYPE_OUTPUT, "Output");
    
    // Create connections
    neurosync_create_connection(input_neuron, hidden_neuron, 1);
    neurosync_create_connection(hidden_neuron, output_neuron, 1);
    
    // Activate neurons
    neurosync_activate_neuron(input_neuron);
    neurosync_activate_neuron(hidden_neuron);
    
    // Send message
    const char* message = "Hello Neural Network!";
    neurosync_send_message_advanced(input_neuron, hidden_neuron, 
                                  message, strlen(message) + 1,
                                  MESSAGE_PRIORITY_NORMAL, 1.0);
    
    // Cleanup
    neurosync_delete_neuron(input_neuron);
    neurosync_delete_neuron(hidden_neuron);
    neurosync_delete_neuron(output_neuron);
    
    return 0;
}
```

### Complex Neural Network with Statistics

```c
#include "api/NeuroAPI.h"
#include <stdio.h>

int main() {
    // Initialize system
    neurosync_init();
    
    // Create a network of neurons
    int neurons[10];
    for (int i = 0; i < 10; i++) {
        char name[32];
        sprintf(name, "Neuron_%d", i);
        neurons[i] = neurosync_create_neuron_advanced(NEURON_TYPE_HIDDEN, name);
    }
    
    // Connect neurons in a mesh pattern
    for (int i = 0; i < 9; i++) {
        neurosync_create_connection(neurons[i], neurons[i+1], 0.5);
    }
    
    // Activate all neurons
    for (int i = 0; i < 10; i++) {
        neurosync_activate_neuron(neurons[i]);
    }
    
    // Send messages between neurons
    for (int i = 0; i < 9; i++) {
        char message[64];
        sprintf(message, "Message from neuron %d", i);
        neurosync_send_message_advanced(neurons[i], neurons[i+1],
                                      message, strlen(message) + 1,
                                      MESSAGE_PRIORITY_HIGH, 0.8);
    }
    
    // Get system statistics
    NeuroSyncSystemStatistics stats = neurosync_get_system_statistics();
    printf("Total messages sent: %zu\n", stats.totalMessagesSent);
    printf("Total connections: %zu\n", stats.totalConnections);
    
    // Cleanup
    for (int i = 0; i < 10; i++) {
        neurosync_delete_neuron(neurons[i]);
    }
    
    return 0;
}
```

## Best Practices

1. **Always Initialize**: Call `neurosync_init()` before using any other API functions
2. **Resource Management**: Always delete neurons when they're no longer needed
3. **Error Checking**: Check return values of functions that return boolean values
4. **Naming Convention**: Use descriptive names for neurons to aid in debugging
5. **Connection Management**: Regularly update connection weights based on network performance
6. **Statistics Monitoring**: Use system statistics to monitor and optimize network performance

## Thread Safety

The NeuroSync API is designed to be thread-safe:
- All API functions can be called from multiple threads
- Internal synchronization protects shared resources
- No additional synchronization is needed when using the API from multiple threads

## Performance Considerations

1. **Batch Operations**: When creating many neurons or connections, consider batching operations
2. **Message Prioritization**: Use appropriate message priorities to ensure critical communications
3. **Connection Weights**: Regularly update connection weights to optimize network performance
4. **Resource Cleanup**: Always clean up resources to prevent memory leaks