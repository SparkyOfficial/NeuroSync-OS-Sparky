/*
 * comprehensive_example.cpp
 * Комплексний приклад використання NeuroSync OS Sparky
 * Comprehensive example of using NeuroSync OS Sparky
 * Комплексный пример использования NeuroSync OS Sparky
 */

#include "../neuron/NeuronManager.h"
#include "../synapse/SynapseBus.h"
#include "../memory/MemoryCore.h"
#include "../core/Scheduler.h"
#include "../api/NeuroAPI.h"
#include "../diagnostics/Diagnostics.h"
#include "../testing/TestingFramework.h"
#include "../benchmark/BenchmarkSuite.h"
#include "../config/ConfigurationManager.h"
#include "../logging/LoggingSystem.h"
#include "../event/EventSystem.h"
#include "../network/NetworkCommunication.h"
#include "../security/SecurityModule.h"
#include "../threadpool/ThreadPool.h"
#include "../filesystem/FileSystem.h"
#include "../network_neural/NeuralNetwork.h"
#include "../visualization/VisualizationModule.h"
#include "../plugin/PluginSystem.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace NeuroSync;

// Initialize global components
std::unique_ptr<NeuronManager> gNeuronManager = std::make_unique<NeuronManager>();
std::unique_ptr<SynapseBus> gSynapseBus = std::make_unique<SynapseBus>();
std::unique_ptr<MemoryCore> gMemoryCore = std::make_unique<MemoryCore>();
std::unique_ptr<Scheduler> gScheduler = std::make_unique<Scheduler>();
std::unique_ptr<NeuroAPI> gNeuroAPI = std::make_unique<NeuroAPI>();
std::unique_ptr<Diagnostics> gDiagnostics = std::make_unique<Diagnostics>();
std::unique_ptr<TestingFramework> gTestingFramework = std::make_unique<TestingFramework>();
std::unique_ptr<BenchmarkSuite> gBenchmarkSuite = std::make_unique<BenchmarkSuite>();
std::unique_ptr<ConfigurationManager> gConfigManager = std::make_unique<ConfigurationManager>();
std::unique_ptr<LoggingSystem> gLoggingSystem = std::make_unique<LoggingSystem>();
std::unique_ptr<EventSystem> gEventSystem = std::make_unique<EventSystem>();
std::unique_ptr<NetworkCommunication> gNetworkComm = std::make_unique<NetworkCommunication>();
std::unique_ptr<SecurityModule> gSecurityModule = std::make_unique<SecurityModule>();
std::unique_ptr<ThreadPool> gThreadPool = std::make_unique<ThreadPool>();
std::unique_ptr<FileSystem> gFileSystem = std::make_unique<FileSystem>();
std::unique_ptr<NeuralNetwork> gNeuralNetwork = std::make_unique<NeuralNetwork>();
std::unique_ptr<VisualizationModule> gVisualization = std::make_unique<VisualizationModule>();
std::unique_ptr<PluginSystem> gPluginSystem = std::make_unique<PluginSystem>();

// Sample neuron processing function
void processNeuronData(NeuronID neuronId) {
    // Simulate neuron processing
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    // Send signal through synapse bus
    gSynapseBus->sendMessage(neuronId, "processed_data", "Neuron " + std::to_string(neuronId) + " processed");
}

// Sample benchmark function
void benchmarkNeuronCreation(size_t iterations) {
    for (size_t i = 0; i < iterations; ++i) {
        NeuronID neuronId = gNeuronManager->createNeuron(NeuronType::PROCESSING);
        gNeuronManager->destroyNeuron(neuronId);
    }
}

// Sample test function
void testNeuronCreation() {
    NeuronID neuronId = gNeuronManager->createNeuron(NeuronType::INPUT);
    ASSERT_TRUE(neuronId != INVALID_NEURON_ID);
    ASSERT_TRUE(gNeuronManager->getNeuronType(neuronId) == NeuronType::INPUT);
    gNeuronManager->destroyNeuron(neuronId);
}

int main() {
    std::cout << "NeuroSync OS Sparky Comprehensive Example\n";
    std::cout << "========================================\n\n";
    
    try {
        // Initialize core components
        gNeuronManager->initialize();
        gSynapseBus->initialize();
        gMemoryCore->initialize();
        gScheduler->initialize();
        gDiagnostics->initialize();
        gLoggingSystem->initialize();
        gEventSystem->initialize();
        gNetworkComm->initialize();
        gSecurityModule->initialize();
        gThreadPool->initialize();
        gFileSystem->initialize();
        gNeuralNetwork->initialize();
        gVisualization->initialize();
        gPluginSystem->initialize();
        
        // Configure testing framework
        TestingConfig testConfig;
        testConfig.enableVerboseOutput = true;
        gTestingFramework->initialize(testConfig);
        
        // Configure benchmark suite
        BenchmarkConfig benchConfig;
        benchConfig.defaultIterations = 1000;
        gBenchmarkSuite->initialize(benchConfig);
        
        // Configure logging
        gLoggingSystem->setLogLevel(LogLevel::INFO);
        gLoggingSystem->addOutput(std::make_shared<ConsoleOutput>());
        
        // Log startup
        gLoggingSystem->log(LogLevel::INFO, "NeuroSync OS Sparky starting up");
        
        // Create neurons
        std::cout << "Creating neurons...\n";
        NeuronID inputNeuron = gNeuronManager->createNeuron(NeuronType::INPUT);
        NeuronID hiddenNeuron1 = gNeuronManager->createNeuron(NeuronType::HIDDEN);
        NeuronID hiddenNeuron2 = gNeuronManager->createNeuron(NeuronType::HIDDEN);
        NeuronID outputNeuron = gNeuronManager->createNeuron(NeuronType::OUTPUT);
        
        std::cout << "Created neurons: " << inputNeuron << ", " << hiddenNeuron1 
                  << ", " << hiddenNeuron2 << ", " << outputNeuron << "\n";
        
        // Connect neurons through synapses
        std::cout << "Connecting neurons...\n";
        gSynapseBus->connectNeurons(inputNeuron, hiddenNeuron1, 1.0f);
        gSynapseBus->connectNeurons(hiddenNeuron1, hiddenNeuron2, 0.8f);
        gSynapseBus->connectNeurons(hiddenNeuron2, outputNeuron, 0.9f);
        
        // Process data through neurons
        std::cout << "Processing data...\n";
        processNeuronData(inputNeuron);
        
        // Run diagnostics
        std::cout << "Running diagnostics...\n";
        DiagnosticReport report = gDiagnostics->generateReport();
        std::cout << "System health: " << (report.systemHealth ? "GOOD" : "POOR") << "\n";
        
        // Run tests
        std::cout << "Running tests...\n";
        gTestingFramework->registerTest("NeuronTests", "NeuronCreationTest", TestType::UNIT, testNeuronCreation);
        gTestingFramework->runTest("NeuronTests", "NeuronCreationTest");
        
        // Run benchmarks
        std::cout << "Running benchmarks...\n";
        gBenchmarkSuite->registerBenchmark("PerformanceTests", "NeuronCreationBenchmark", 
                                         BenchmarkType::CPU, benchmarkNeuronCreation);
        gBenchmarkSuite->runBenchmark("NeuronCreationBenchmark", 100);
        
        // Visualize data
        std::cout << "Creating visualization...\n";
        gVisualization->addDataPoint("neuron_count", static_cast<double>(gNeuronManager->getNeuronCount()));
        gVisualization->addDataPoint("synapse_count", static_cast<double>(gSynapseBus->getSynapseCount()));
        gVisualization->generateChart("system_metrics", ChartType::BAR);
        
        // Clean up
        std::cout << "Cleaning up...\n";
        gNeuronManager->destroyNeuron(inputNeuron);
        gNeuronManager->destroyNeuron(hiddenNeuron1);
        gNeuronManager->destroyNeuron(hiddenNeuron2);
        gNeuronManager->destroyNeuron(outputNeuron);
        
        // Log shutdown
        gLoggingSystem->log(LogLevel::INFO, "NeuroSync OS Sparky shutting down");
        
        std::cout << "\nComprehensive example completed successfully!\n";
        std::cout << "Neurons created: " << gNeuronManager->getNeuronCount() << "\n";
        std::cout << "Synapses created: " << gSynapseBus->getSynapseCount() << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error in comprehensive example: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}