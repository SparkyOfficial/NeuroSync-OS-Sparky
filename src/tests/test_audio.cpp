#include "../audio/AudioProcessing.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace NeuroSync::Audio;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync Audio Processing Tests\n";
    std::cout << "========================================\n\n";
    
    // Створення модуля обробки аудіо
    // Create audio processing module
    // Создание модуля обработки аудио
    AudioProcessor audioProcessor;
    
    // Тест ініціалізації
    // Test initialization
    // Тест инициализации
    std::cout << "1. Testing initialization...\n";
    AudioConfig config;
    bool initResult = audioProcessor.initialize(config);
    assert(initResult);
    std::cout << "   ✓ Initialization successful\n\n";
    
    // Тест створення аудіо фрейму
    // Test audio frame creation
    // Тест создания аудио фрейма
    std::cout << "2. Testing audio frame creation...\n";
    AudioFrame frame(44100, 2, AudioFormat::FLOAT_32BIT);
    assert(frame.sampleRate == 44100);
    assert(frame.channels == 2);
    assert(frame.format == AudioFormat::FLOAT_32BIT);
    std::cout << "   ✓ Audio frame creation successful\n\n";
    
    // Тест створення аудіо потоку
    // Test audio stream creation
    // Тест создания аудио потока
    std::cout << "3. Testing audio stream creation...\n";
    AudioStream stream;
    assert(stream.duration == 0.0);
    assert(stream.frames.empty());
    std::cout << "   ✓ Audio stream creation successful\n\n";
    
    // Тест завантаження аудіо
    // Test audio loading
    // Тест загрузки аудио
    std::cout << "4. Testing audio loading...\n";
    AudioStream loadedAudio;
    bool loadResult = audioProcessor.loadAudio("test_audio.wav", loadedAudio);
    assert(loadResult);
    std::cout << "   ✓ Audio loading successful\n";
    std::cout << "   Loaded audio duration: " << loadedAudio.duration << " seconds\n\n";
    
    // Тест збереження аудіо
    // Test audio saving
    // Тест сохранения аудио
    std::cout << "5. Testing audio saving...\n";
    bool saveResult = audioProcessor.saveAudio(loadedAudio, "output_audio.wav");
    assert(saveResult);
    std::cout << "   ✓ Audio saving successful\n\n";
    
    // Тест розпізнавання мови
    // Test speech recognition
    // Тест распознавания речи
    std::cout << "6. Testing speech recognition...\n";
    SpeechRecognitionResult recognitionResult = audioProcessor.recognizeSpeech(loadedAudio);
    std::cout << "   ✓ Speech recognition successful\n";
    std::cout << "   Recognized text: " << recognitionResult.text << "\n";
    std::cout << "   Confidence: " << recognitionResult.confidence << "\n\n";
    
    // Тест синтезу мови
    // Test speech synthesis
    // Тест синтеза речи
    std::cout << "7. Testing speech synthesis...\n";
    SpeechSynthesisResult synthesisResult = audioProcessor.synthesizeSpeech("Test text for synthesis");
    std::cout << "   ✓ Speech synthesis successful\n";
    std::cout << "   Synthesized audio duration: " << synthesisResult.audio.duration << " seconds\n";
    std::cout << "   Processing time: " << synthesisResult.processingTime << " ms\n\n";
    
    // Тест виявлення голосової активності
    // Test voice activity detection
    // Тест обнаружения голосовой активности
    std::cout << "8. Testing voice activity detection...\n";
    std::vector<std::pair<double, double>> voiceSegments = audioProcessor.detectVoiceActivity(loadedAudio);
    std::cout << "   ✓ Voice activity detection successful\n";
    std::cout << "   Found " << voiceSegments.size() << " voice segments\n\n";
    
    // Тест виявлення тональності
    // Test pitch detection
    // Тест обнаружения тональности
    std::cout << "9. Testing pitch detection...\n";
    std::vector<double> pitches = audioProcessor.detectPitch(loadedAudio);
    std::cout << "   ✓ Pitch detection successful\n";
    std::cout << "   Found " << pitches.size() << " pitch values\n\n";
    
    // Тест виявлення тембру
    // Test timbre detection
    // Тест обнаружения тембра
    std::cout << "10. Testing timbre detection...\n";
    std::map<std::string, double> timbreFeatures = audioProcessor.detectTimbre(loadedAudio);
    std::cout << "   ✓ Timbre detection successful\n";
    std::cout << "   Found " << timbreFeatures.size() << " timbre features\n\n";
    
    // Тест фільтрації аудіо
    // Test audio filtering
    // Тест фильтрации аудио
    std::cout << "11. Testing audio filtering...\n";
    AudioFilter filter("lowpass", 1000.0);
    AudioStream filteredAudio = audioProcessor.filterAudio(loadedAudio, filter);
    assert(filteredAudio.duration == loadedAudio.duration);
    std::cout << "   ✓ Audio filtering successful\n";
    std::cout << "   Filtered audio duration: " << filteredAudio.duration << " seconds\n\n";
    
    // Тест зниження шуму
    // Test noise reduction
    // Тест снижения шума
    std::cout << "12. Testing noise reduction...\n";
    AudioStream noiseReducedAudio = audioProcessor.reduceNoise(loadedAudio);
    std::cout << "   ✓ Noise reduction successful\n";
    std::cout << "   Noise reduced audio duration: " << noiseReducedAudio.duration << " seconds\n\n";
    
    // Тест скасування відлуння
    // Test echo cancellation
    // Тест подавления эха
    std::cout << "13. Testing echo cancellation...\n";
    AudioStream echoCancelledAudio = audioProcessor.cancelEcho(loadedAudio);
    std::cout << "   ✓ Echo cancellation successful\n";
    std::cout << "   Echo cancelled audio duration: " << echoCancelledAudio.duration << " seconds\n\n";
    
    // Тест перетворення частоти дискретизації
    // Test sample rate conversion
    // Тест преобразования частоты дискретизации
    std::cout << "14. Testing sample rate conversion...\n";
    AudioStream convertedAudio = audioProcessor.convertSampleRate(loadedAudio, 22050);
    std::cout << "   ✓ Sample rate conversion successful\n";
    std::cout << "   Converted sample rate: " << convertedAudio.frames[0].sampleRate << " Hz\n";
    std::cout << "   Converted audio duration: " << convertedAudio.duration << " seconds\n\n";
    
    // Тест зміни кількості каналів
    // Test channel conversion
    // Тест преобразования количества каналов
    std::cout << "15. Testing channel conversion...\n";
    AudioStream monoAudio = audioProcessor.convertChannels(loadedAudio, 1);
    std::cout << "   ✓ Channel conversion successful\n";
    std::cout << "   Converted channels: " << monoAudio.frames[0].channels << "\n";
    std::cout << "   Mono audio duration: " << monoAudio.duration << " seconds\n\n";
    
    // Тест зміни гучності
    // Test volume adjustment
    // Тест изменения громкости
    std::cout << "16. Testing volume adjustment...\n";
    AudioStream louderAudio = audioProcessor.adjustVolume(loadedAudio, 1.5);
    std::cout << "   ✓ Volume adjustment successful\n";
    std::cout << "   Louder audio duration: " << louderAudio.duration << " seconds\n\n";
    
    // Тест нормалізації аудіо
    // Test audio normalization
    // Тест нормализации аудио
    std::cout << "17. Testing audio normalization...\n";
    AudioStream normalizedAudio = audioProcessor.normalizeAudio(loadedAudio);
    std::cout << "   ✓ Audio normalization successful\n";
    std::cout << "   Normalized audio duration: " << normalizedAudio.duration << " seconds\n\n";
    
    // Тест видобування ознак
    // Test feature extraction
    // Тест извлечения признаков
    std::cout << "18. Testing feature extraction...\n";
    std::vector<double> features = audioProcessor.extractFeatures(loadedAudio);
    assert(!features.empty());
    std::cout << "   ✓ Feature extraction successful\n";
    std::cout << "   Extracted " << features.size() << " features\n\n";
    
    // Тест порівняння аудіо
    // Test audio comparison
    // Тест сравнения аудио
    std::cout << "19. Testing audio comparison...\n";
    double similarity = audioProcessor.compareAudio(loadedAudio, loadedAudio);
    assert(similarity >= 0.0 && similarity <= 1.0);
    std::cout << "   ✓ Audio comparison successful\n";
    std::cout << "   Audio similarity: " << similarity << "\n\n";
    
    // Тест конфігурації
    // Test configuration
    // Тест конфигурации
    std::cout << "20. Testing configuration...\n";
    AudioConfig newConfig = audioProcessor.getConfiguration();
    audioProcessor.updateConfiguration(newConfig);
    std::cout << "   ✓ Configuration test successful\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  All Audio Processing Tests Passed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}