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
#include <memory>
#include <algorithm>
#include <cctype>

using namespace NeuroSync;

// Conversation data structure for storage in memory core
struct ConversationData {
    std::string input;
    std::string response;
    long long timestamp;
    
    ConversationData(const std::string& in, const std::string& resp) 
        : input(in), response(resp), timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count()) {}
};

// Training data structure for neural network
struct TrainingData {
    std::vector<double> input;
    std::vector<double> target;
    
    TrainingData(const std::vector<double>& in, const std::vector<double>& tgt)
        : input(in), target(tgt) {}
};

// Serialize conversation data to string
std::string serializeConversationData(const ConversationData& data) {
    // Simple serialization format: input|response|timestamp
    std::ostringstream oss;
    oss << data.input << "|" << data.response << "|" << data.timestamp;
    return oss.str();
}

// Deserialize conversation data from string
std::unique_ptr<ConversationData> deserializeConversationData(const std::string& serializedData) {
    std::istringstream iss(serializedData);
    std::string token;
    std::vector<std::string> tokens;
    
    // Split by |
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    // Check if we have all required fields
    if (tokens.size() != 3) {
        return nullptr;
    }
    
    // Parse timestamp
    long long timestamp = std::stoll(tokens[2]);
    
    // Create and return conversation data
    auto data = std::make_unique<ConversationData>(tokens[0], tokens[1]);
    data->timestamp = timestamp;
    return data;
};

// Global components
std::unique_ptr<NeuronManager> gNeuronManager = std::make_unique<NeuronManager>();
std::unique_ptr<SynapseBus> gSynapseBus = std::make_unique<SynapseBus>();
std::unique_ptr<Network::NeuralNetwork> gNeuralNetwork = std::make_unique<Network::NeuralNetwork>(
    Network::NetworkType::FEEDFORWARD, "AIAssistantNetwork");
std::unique_ptr<Memory::MemoryCore> gMemoryCore = std::make_unique<Memory::MemoryCore>();
std::unique_ptr<Event::EventSystem> gEventSystem = std::make_unique<Event::EventSystem>();
std::unique_ptr<Logging::LoggingSystem> gLoggingSystem = std::make_unique<Logging::LoggingSystem>();
std::unique_ptr<Config::ConfigurationManager> gConfigManager = std::make_unique<Config::ConfigurationManager>();

// AI Assistant class
class AIAssistant {
private:
    int inputNeuron;
    int processingNeuron;
    int outputNeuron;
    int memoryNeuron;
    std::map<std::string, std::string> knowledgeBase;
    std::vector<std::unique_ptr<ConversationData>> conversationHistory;
    std::vector<TrainingData> trainingData;
    
public:
    AIAssistant() {
        // Initialize components
        gNeuronManager->initialize();
        gSynapseBus->initialize();
        gNeuralNetwork->initialize();
        // MemoryCore is initialized in constructor
        gEventSystem->initialize();
        gLoggingSystem->initialize();
        gConfigManager->initialize();
        
        // Set up logging
        gLoggingSystem->setLogLevel(Logging::LogLevel::LOG_INFO);
        gLoggingSystem->addLogOutput(std::make_shared<Logging::ConsoleLogOutput>());
        
        // Create neurons
        inputNeuron = gNeuronManager->createNeuron(NeuroSync::Neuron::Models::NeuronType::INPUT, "InputNeuron");
        processingNeuron = gNeuronManager->createNeuron(NeuroSync::Neuron::Models::NeuronType::PROCESSING, "ProcessingNeuron");
        outputNeuron = gNeuronManager->createNeuron(NeuroSync::Neuron::Models::NeuronType::OUTPUT, "OutputNeuron");
        memoryNeuron = gNeuronManager->createNeuron(NeuroSync::Neuron::Models::NeuronType::MEMORY, "MemoryNeuron");
        
        // Connect neurons
        gSynapseBus->createConnection(inputNeuron, processingNeuron, 1.0f);
        gSynapseBus->createConnection(processingNeuron, outputNeuron, 1.0f);
        gSynapseBus->createConnection(processingNeuron, memoryNeuron, 0.8f);
        gSynapseBus->createConnection(memoryNeuron, processingNeuron, 0.7f);
        
        // Initialize neural network architecture
        initializeNeuralNetwork();
        
        // Initialize knowledge base
        initializeKnowledgeBase();
        
        // Log initialization
        gLoggingSystem->info("AIAssistant", "AI Assistant initialized");
    }
    
    ~AIAssistant() {
        // Store conversation history in memory core before shutdown
        storeConversationHistory();
        
        // Clean up neurons
        gNeuronManager->deleteNeuron(inputNeuron);
        gNeuronManager->deleteNeuron(processingNeuron);
        gNeuronManager->deleteNeuron(outputNeuron);
        gNeuronManager->deleteNeuron(memoryNeuron);
        
        gLoggingSystem->info("AIAssistant", "AI Assistant shut down");
    }
    
    void initializeNeuralNetwork() {
        // Create a simple feedforward neural network with:
        // - Input layer (10 neurons for text features)
        // - Hidden layer (20 neurons)
        // - Output layer (5 neurons for response categories)
        gNeuralNetwork->addLayer(10, "sigmoid");  // Input layer
        gNeuralNetwork->addLayer(20, "sigmoid");  // Hidden layer
        gNeuralNetwork->addLayer(5, "sigmoid");   // Output layer
        
        // Connect layers
        gNeuralNetwork->connectLayers(0, 1);  // Input to hidden
        gNeuralNetwork->connectLayers(1, 2);  // Hidden to output
        
        gLoggingSystem->info("AIAssistant", "Neural network initialized with 3 layers");
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
        gLoggingSystem->info("AIAssistant", "Processing input: " + input);
        
        // Convert input to lowercase for matching
        std::string lowerInput = input;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), 
                      [](unsigned char c){ return std::tolower(c); });
        
        // Check knowledge base
        auto it = knowledgeBase.find(lowerInput);
        if (it != knowledgeBase.end()) {
            gLoggingSystem->info("AIAssistant", "Found response in knowledge base");
            std::string response = it->second;
            
            // Store in conversation history
            conversationHistory.push_back(std::make_unique<ConversationData>(input, response));
            
            return response;
        }
        
        // Use neural network for more complex processing
        std::string response = processWithNeuralNetwork(input);
        
        // Store in memory for future reference
        storeInMemory(input, response);
        
        // Store in conversation history
        conversationHistory.push_back(std::make_unique<ConversationData>(input, response));
        
        return response;
    }
    
    std::string processWithNeuralNetwork(const std::string& input) {
        gLoggingSystem->info("AIAssistant", "Processing with neural network");
        
        // Convert text to feature vector (simplified)
        std::vector<double> features = textToFeatures(input);
        
        // Get prediction from neural network
        std::vector<double> prediction = gNeuralNetwork->predict(features);
        
        // Convert prediction to response
        std::string response = predictionToResponse(prediction);
        
        return response;
    }
    
    std::vector<double> textToFeatures(const std::string& text) {
        // Simple text to feature conversion (for demonstration)
        std::vector<double> features(10, 0.0);
        
        // Fill features based on text characteristics
        features[0] = static_cast<double>(text.length()) / 100.0;  // Normalized length
        features[1] = static_cast<double>(std::count(text.begin(), text.end(), ' ')) / 20.0;  // Word count
        features[2] = static_cast<double>(std::count_if(text.begin(), text.end(), ::isupper)) / text.length();  // Capital ratio
        features[3] = static_cast<double>(std::count(text.begin(), text.end(), '?')) / text.length();  // Question mark ratio
        features[4] = static_cast<double>(std::count(text.begin(), text.end(), '!')) / text.length();  // Exclamation mark ratio
        
        // Keyword presence features
        std::string lowerText = text;
        std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);
        features[5] = lowerText.find("weather") != std::string::npos ? 1.0 : 0.0;
        features[6] = lowerText.find("time") != std::string::npos ? 1.0 : 0.0;
        features[7] = lowerText.find("help") != std::string::npos ? 1.0 : 0.0;
        features[8] = lowerText.find("name") != std::string::npos ? 1.0 : 0.0;
        features[9] = lowerText.find("bye") != std::string::npos ? 1.0 : 0.0;
        
        return features;
    }
    
    std::string predictionToResponse(const std::vector<double>& prediction) {
        // Convert neural network prediction to response
        if (prediction.empty()) {
            return "I'm not sure how to respond to that.";
        }
        
        // Find the index of the highest prediction value
        int maxIndex = 0;
        for (size_t i = 1; i < prediction.size(); ++i) {
            if (prediction[i] > prediction[maxIndex]) {
                maxIndex = static_cast<int>(i);
            }
        }
        
        // Map prediction index to response category
        switch (maxIndex) {
            case 0:
                return "That's an interesting point. Can you tell me more?";
            case 1:
                return "I understand what you're saying. How can I help you with that?";
            case 2:
                return "Thanks for sharing that with me. Is there anything specific you'd like to know?";
            case 3:
                return "I see. What else would you like to discuss?";
            case 4:
                return "I appreciate your input. Let me know if there's anything I can assist you with.";
            default:
                return "I'm still learning. Could you rephrase that?";
        }
    }
    
    void storeInMemory(const std::string& input, const std::string& response) {
        gLoggingSystem->info("AIAssistant", "Storing conversation in memory");
        
        // Create conversation data
        std::unique_ptr<ConversationData> data = std::make_unique<ConversationData>(input, response);
        
        // Serialize the conversation data
        std::string serializedData = serializeConversationData(*data);
        
        // Allocate memory in the memory core
        size_t dataSize = serializedData.length();
        void* memoryAddress = gMemoryCore->allocate(dataSize);
        
        if (memoryAddress) {
            // Copy the serialized data to the allocated memory
            std::memcpy(memoryAddress, serializedData.c_str(), dataSize);
            
            // Register it with the garbage collector
            gMemoryCore->registerForGC(memoryAddress, dataSize);
            gLoggingSystem->info("AIAssistant", "Conversation stored in memory core at address: " + 
                               std::to_string(reinterpret_cast<uintptr_t>(memoryAddress)));
        } else {
            gLoggingSystem->warning("AIAssistant", "Failed to allocate memory for conversation data");
        }
    }
    
    void storeConversationHistory() {
        gLoggingSystem->info("AIAssistant", "Storing conversation history in memory core");
        
        // TODO: Implement a more sophisticated way to track conversation data
        // In a real implementation, we would have a more sophisticated way to track
        // conversation data, but for this example, we'll just store all conversations
        
        // Serialize and store the entire conversation history
        // to the memory core for persistence across sessions
        for (const auto& conversation : conversationHistory) {
            // Serialize the conversation data
            std::string serializedData = serializeConversationData(*conversation);
            
            // Allocate memory in the memory core
            size_t dataSize = serializedData.length();
            void* memoryAddress = gMemoryCore->allocate(dataSize);
            
            if (memoryAddress) {
                // Copy the serialized data to the allocated memory
                std::memcpy(memoryAddress, serializedData.c_str(), dataSize);
                
                // Register it with the garbage collector
                gMemoryCore->registerForGC(memoryAddress, dataSize);
                gLoggingSystem->info("AIAssistant", "Conversation stored in memory core at address: " + 
                                   std::to_string(reinterpret_cast<uintptr_t>(memoryAddress)));
            } else {
                gLoggingSystem->warning("AIAssistant", "Failed to allocate memory for conversation data");
            }
        }
        
        gLoggingSystem->info("AIAssistant", "Stored " + std::to_string(conversationHistory.size()) + 
                           " conversations in memory");
    }
    
    void loadConversationHistory() {
        gLoggingSystem->info("AIAssistant", "Loading conversation history from memory core");
        
        // Get all memory blocks from the memory core
        std::vector<std::pair<void*, size_t>> memoryBlocks = gMemoryCore->getAllMemoryBlocks();
        
        conversationHistory.clear();
        
        // Iterate through all memory blocks and try to deserialize conversation data
        for (const auto& block : memoryBlocks) {
            void* address = block.first;
            size_t size = block.second;
            
            // Convert memory block to string
            std::string data(static_cast<char*>(address), size);
            
            // Try to deserialize as conversation data
            std::unique_ptr<ConversationData> conversation = deserializeConversationData(data);
            if (conversation) {
                conversationHistory.push_back(std::move(conversation));
                gLoggingSystem->info("AIAssistant", "Loaded conversation from memory block");
            }
        }
        
        gLoggingSystem->info("AIAssistant", "Loaded " + std::to_string(conversationHistory.size()) + 
                           " conversations from memory core");
    }
    
    void learnFromInteraction(const std::string& input, const std::string& feedback) {
        gLoggingSystem->info("AIAssistant", "Learning from interaction");
        
        // Add to knowledge base
        knowledgeBase[input] = feedback;
        
        // Add to training data for neural network
        std::vector<double> features = textToFeatures(input);
        std::vector<double> target = responseToTarget(feedback);
        trainingData.emplace_back(features, target);
        
        // Train the neural network with the new data
        if (trainingData.size() >= 5) { // Train when we have enough data
            gLoggingSystem->info("AIAssistant", "Training neural network with new interaction");
            
            // Prepare training data in the format expected by the neural network
            std::vector<std::vector<double>> inputs;
            std::vector<std::vector<double>> targets;
            
            // Use last 5 interactions for training
            size_t startIndex = trainingData.size() > 5 ? trainingData.size() - 5 : 0;
            for (size_t i = startIndex; i < trainingData.size(); ++i) {
                inputs.push_back(trainingData[i].input);
                targets.push_back(trainingData[i].target);
            }
            
            // Train the neural network with a small number of epochs
            bool success = gNeuralNetwork->train(inputs, targets, 10, 0.01);
            
            if (success) {
                gLoggingSystem->info("AIAssistant", "Neural network training completed successfully");
            } else {
                gLoggingSystem->error("AIAssistant", "Neural network training failed");
            }
        } else {
            gLoggingSystem->info("AIAssistant", "Added interaction to training data (" + 
                               std::to_string(trainingData.size()) + " samples)");
        }
    }
    
    std::vector<double> responseToTarget(const std::string& response) {
        // Convert response to target vector for training
        std::vector<double> target(5, 0.0);
        
        std::string lowerResponse = response;
        std::transform(lowerResponse.begin(), lowerResponse.end(), lowerResponse.begin(), ::tolower);
        
        // Simple mapping based on response content
        if (lowerResponse.find("interesting") != std::string::npos || 
            lowerResponse.find("tell me more") != std::string::npos) {
            target[0] = 1.0;
        } else if (lowerResponse.find("understand") != std::string::npos || 
                  lowerResponse.find("help") != std::string::npos) {
            target[1] = 1.0;
        } else if (lowerResponse.find("thanks") != std::string::npos || 
                  lowerResponse.find("appreciate") != std::string::npos) {
            target[2] = 1.0;
        } else if (lowerResponse.find("see") != std::string::npos || 
                  lowerResponse.find("else") != std::string::npos) {
            target[3] = 1.0;
        } else {
            target[4] = 1.0; // Default category
        }
        
        return target;
    }
    
    void trainNeuralNetwork() {
        gLoggingSystem->info("AIAssistant", "Training neural network with " + 
                           std::to_string(trainingData.size()) + " samples");
        
        if (trainingData.empty()) {
            gLoggingSystem->warning("AIAssistant", "No training data available");
            return;
        }
        
        // Prepare training data in the format expected by the neural network
        std::vector<std::vector<double>> inputs;
        std::vector<std::vector<double>> targets;
        
        for (const auto& data : trainingData) {
            inputs.push_back(data.input);
            targets.push_back(data.target);
        }
        
        // Train the neural network
        bool success = gNeuralNetwork->train(inputs, targets, 100, 0.01);
        
        if (success) {
            gLoggingSystem->info("AIAssistant", "Neural network training completed successfully");
        } else {
            gLoggingSystem->error("AIAssistant", "Neural network training failed");
        }
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
        std::cout << "  Type 'train' to train the neural network\n";
        std::cout << "========================================\n\n";
        
        std::string input;
        while (true) {
            std::cout << "You: ";
            std::getline(std::cin, input);
            
            if (input == "quit" || input == "exit" || input == "bye") {
                std::cout << "AI: Goodbye! Have a great day!\n";
                break;
            }
            
            if (input == "train") {
                std::cout << "AI: Training neural network...\n";
                assistant.trainNeuralNetwork();
                std::cout << "AI: Training completed!\n\n";
                continue;
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