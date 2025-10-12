#include "src/audio/AudioProcessing.h"
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::cout << "Testing Audio Processing Implementation..." << std::endl;
    
    // Create a simple test WAV file
    std::ofstream testFile("test.wav", std::ios::binary);
    if (testFile.is_open()) {
        // Write a simple WAV header and some dummy data
        std::vector<char> dummyData(1024, 0);
        testFile.write(dummyData.data(), dummyData.size());
        testFile.close();
        std::cout << "Created test.wav file" << std::endl;
    } else {
        std::cerr << "Failed to create test.wav file" << std::endl;
        return 1;
    }
    
    // Test audio processing
    NeuroSync::Audio::AudioProcessor processor;
    
    NeuroSync::Audio::AudioStream audioStream;
    if (processor.loadAudio("test.wav", audioStream)) {
        std::cout << "Successfully loaded audio file" << std::endl;
        
        if (processor.saveAudio(audioStream, "output.wav")) {
            std::cout << "Successfully saved audio file" << std::endl;
        } else {
            std::cerr << "Failed to save audio file" << std::endl;
        }
    } else {
        std::cerr << "Failed to load audio file" << std::endl;
    }
    
    // Clean up test files
    std::remove("test.wav");
    std::remove("output.wav");
    
    std::cout << "Audio processing test completed!" << std::endl;
    return 0;
}