/*
 * ai_assistant_example.cpp
 * Приклад штучного інтелекту-асистента
 * AI Assistant example
 * Пример ИИ-ассистента
 */

#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"
#include "../network_neural/NeuralNetwork.h"
#include "../memory/MemoryCore.h"
#include "../event/EventSystem.h"
#include "../logging/LoggingSystem.h"
#include "../config/ConfigurationManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

using namespace NeuroSync;

// Global components
std::unique_ptr<NeuronManager> gNeuronManager = std::make_unique<NeuronManager>();
std::unique_ptr<SynapseBus> gSynapseBus = std::make_unique<SynapseBus>();
std::unique_ptr<NeuralNetwork> gNeuralNetwork = std::make_unique<NeuralNetwork>();
std::unique_ptr<MemoryCore> gMemoryCore = std::make_unique<MemoryCore>();
std::unique_ptr<EventSystem> gEventSystem = std::make_unique<EventSystem>();
std::unique_ptr<LoggingSystem> gLoggingSystem = std::make_unique<LoggingSystem>();
std::unique_ptr<ConfigurationManager> gConfigManager = std::make_unique<ConfigurationManager>();

// AI Assistant class
class AIAssistant {
private:
    NeuronID inputNeuron;
    NeuronID processingNeuron;
    NeuronID outputNeuron;
    NeuronID memoryNeuron;
    std::map<std::string, std::string> knowledgeBase;
    
public:
    AIAssistant() {
        // Initialize components
        gNeuronManager->initialize();
        gSynapseBus->initialize();
        gNeuralNetwork->initialize();
        gMemoryCore->initialize();
        gEventSystem->initialize();
        gLoggingSystem->initialize();
        
        // Set up logging
        gLoggingSystem->setLogLevel(LogLevel::INFO);
        gLoggingSystem->addOutput(std::make_shared<ConsoleOutput>());
        
        // Create neurons
        inputNeuron = gNeuronManager->createNeuron(NeuronType::INPUT);
        processingNeuron = gNeuronManager->createNeuron(NeuronType::PROCESSING);
        outputNeuron = gNeuronManager->createNeuron(NeuronType::OUTPUT);
        memoryNeuron = gNeuronManager->createNeuron(NeuronType::MEMORY);
        
        // Connect neurons
        gSynapseBus->connectNeurons(inputNeuron, processingNeuron, 1.0f);
        gSynapseBus->connectNeurons(processingNeuron, outputNeuron, 1.0f);
        gSynapseBus->connectNeurons(processingNeuron, memoryNeuron, 0.8f);
        gSynapseBus->connectNeurons(memoryNeuron, processingNeuron, 0.7f);
        
        // Initialize knowledge base
        initializeKnowledgeBase();
        
        // Log initialization
        gLoggingSystem->log(LogLevel::INFO, "AI Assistant initialized");
    }
    
    ~AIAssistant() {
        // Clean up neurons
        gNeuronManager->destroyNeuron(inputNeuron);
        gNeuronManager->destroyNeuron(processingNeuron);
        gNeuronManager->destroyNeuron(outputNeuron);
        gNeuronManager->destroyNeuron(memoryNeuron);
        
        gLoggingSystem->log(LogLevel::INFO, "AI Assistant shut down");
    }
    
    void initializeKnowledgeBase() {
        knowledgeBase["hello"] = "Hello! How can I help you today?";
        knowledgeBase["hi"] = "Hi there! What can I do for you?";
        knowledgeBase["how are you"] = "I'm doing well, thank you for asking!";
        knowledgeBase["what is your name"] = "I'm NeuroSync AI Assistant, nice to meet you!";
        knowledgeBase["bye"] = "Goodbye! Have a great day!";
        knowledgeBase["goodbye"] = "See you later! Take care!";
        knowledgeBase["thank you"] = "You're welcome! I'm happy to help.";
        knowledgeBase["thanks"] = "No problem! I'm here to assist you.";
    }
    
    std::string processInput(const std::string& input) {
        gLoggingSystem->log(LogLevel::INFO, "Processing input: " + input);
        
        // Convert input to lowercase for matching
        std::string lowerInput = input;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        
        // Check knowledge base
        auto it = knowledgeBase.find(lowerInput);
        if (it != knowledgeBase.end()) {
            gLoggingSystem->log(LogLevel::INFO, "Found response in knowledge base");
            return it->second;
        }
        
        // Use neural network for more complex processing
        std::string response = processWithNeuralNetwork(input);
        
        // Store in memory for future reference
        storeInMemory(input, response);
        
        return response;
    }
    
    std::string processWithNeuralNetwork(const std::string& input) {
        gLoggingSystem->log(LogLevel::INFO, "Processing with neural network");
        
        // Simulate neural network processing
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        // Simple pattern matching for demonstration
        if (input.find("weather") != std::string::npos) {
            return "I'm sorry, I don't have access to weather information right now.";
        } else if (input.find("time") != std::string::npos) {
            return "I don't have access to real-time information, but I'm always here to help!";
        } else if (input.find("help") != std::string::npos) {
            return "I can answer simple questions and have a conversation with you. Try asking me about myself!";
        } else if (input.find("?") != std::string::npos) {
            return "That's an interesting question. I'm still learning and improving every day.";
        } else {
            return "I understand you're saying: \"" + input + "\". How can I assist you further?";
        }
    }
    
    void storeInMemory(const std::string& input, const std::string& response) {
        gLoggingSystem->log(LogLevel::INFO, "Storing conversation in memory");
        
        // Simulate memory storage
        std::string memoryKey = "conversation_" + std::to_string(std::hash<std::string>{}(input));
        // In a real implementation, this would store in the memory core
    }
    
    void learnFromInteraction(const std::string& input, const std::string& feedback) {
        gLoggingSystem->log(LogLevel::INFO, "Learning from interaction");
        
        // Add to knowledge base
        knowledgeBase[input] = feedback;
        
        // In a real implementation, this would train the neural network
    }
};

// Simple console interface
class ConsoleInterface {
private:
    AIAssistant assistant;
    
public:
    void run() {
        std::cout << "========================================\n";
        std::cout << "  NeuroSync AI Assistant\n";
        std::cout << "  Type 'quit' to exit\n";
        std::cout << "========================================\n\n";
        
        std::string input;
        while (true) {
            std::cout << "You: ";
            std::getline(std::cin, input);
            
            if (input == "quit" || input == "exit" || input == "bye") {
                std::cout << "AI: Goodbye! Have a great day!\n";
                break;
            }
            
            if (input.empty()) {
                continue;
            }
            
            std::string response = assistant.processInput(input);
            std::cout << "AI: " << response << "\n\n";
        }
    }
};

int main() {
    try {
        std::cout << "Starting NeuroSync AI Assistant...\n\n";
        
        ConsoleInterface interface;
        interface.run();
        
        std::cout << "\nThank you for using NeuroSync AI Assistant!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}