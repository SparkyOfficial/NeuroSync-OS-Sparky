#include "../audio/AudioProcessing.h"
#include <iostream>
#include <string>

using namespace NeuroSync::Audio;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync Audio Processing Example\n";
    std::cout << "========================================\n\n";
    
    // Створення модуля обробки аудіо
    // Create audio processing module
    // Создание модуля обработки аудио
    AudioProcessor audioProcessor;
    
    // Ініціалізація модуля
    // Initialize module
    // Инициализация модуля
    AudioConfig config;
    config.enableSpeechRecognition = true;
    config.enableSpeechSynthesis = true;
    config.enableNoiseReduction = true;
    config.enableEchoCancellation = true;
    config.sampleRate = 44100;
    config.channels = 2;
    config.format = AudioFormat::FLOAT_32BIT;
    config.language = "en-US";
    config.modelPath = "./models/audio_model.bin";
    
    if (!audioProcessor.initialize(config)) {
        std::cerr << "Failed to initialize audio processor" << std::endl;
        return 1;
    }
    
    std::cout << "Audio processor initialized successfully\n\n";
    
    // Завантаження аудіо
    // Load audio
    // Загрузка аудио
    std::cout << "1. Loading audio...\n";
    AudioStream audioStream;
    if (!audioProcessor.loadAudio("sample_audio.wav", audioStream)) {
        std::cerr << "Failed to load audio" << std::endl;
        return 1;
    }
    std::cout << "   ✓ Audio loaded successfully (" << audioStream.duration << " seconds)\n\n";
    
    // Розпізнавання мови
    // Speech recognition
    // Распознавание речи
    std::cout << "2. Recognizing speech...\n";
    SpeechRecognitionResult recognitionResult = audioProcessor.recognizeSpeech(audioStream);
    std::cout << "   ✓ Speech recognition completed\n";
    std::cout << "   Recognized text: " << recognitionResult.text << "\n";
    std::cout << "   Confidence: " << recognitionResult.confidence << "\n";
    std::cout << "   Time range: " << recognitionResult.startTime << " - " << recognitionResult.endTime << " seconds\n";
    std::cout << "   Word confidences:\n";
    for (const auto& pair : recognitionResult.wordConfidences) {
        std::cout << "   - " << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "\n";
    
    // Синтез мови
    // Speech synthesis
    // Синтез речи
    std::cout << "3. Synthesizing speech...\n";
    SpeechSynthesisResult synthesisResult = audioProcessor.synthesizeSpeech("Hello, this is a test of speech synthesis.");
    std::cout << "   ✓ Speech synthesis completed\n";
    std::cout << "   Synthesized audio duration: " << synthesisResult.audio.duration << " seconds\n";
    std::cout << "   Processing time: " << synthesisResult.processingTime << " ms\n\n";
    
    // Виявлення голосової активності
    // Voice activity detection
    // Обнаружение голосовой активности
    std::cout << "4. Detecting voice activity...\n";
    std::vector<std::pair<double, double>> voiceSegments = audioProcessor.detectVoiceActivity(audioStream);
    std::cout << "   ✓ Voice activity detection completed\n";
    std::cout << "   Found " << voiceSegments.size() << " voice segments\n";
    for (const auto& segment : voiceSegments) {
        std::cout << "   - " << segment.first << " - " << segment.second << " seconds\n";
    }
    std::cout << "\n";
    
    // Виявлення тональності
    // Pitch detection
    // Обнаружение тональности
    std::cout << "5. Detecting pitch...\n";
    std::vector<double> pitches = audioProcessor.detectPitch(audioStream);
    std::cout << "   ✓ Pitch detection completed\n";
    std::cout << "   Found " << pitches.size() << " pitch values\n";
    for (size_t i = 0; i < std::min(size_t(5), pitches.size()); ++i) {
        std::cout << "   - Pitch " << i << ": " << pitches[i] << " Hz\n";
    }
    if (pitches.size() > 5) {
        std::cout << "   ... and " << (pitches.size() - 5) << " more values\n";
    }
    std::cout << "\n";
    
    // Виявлення тембру
    // Timbre detection
    // Обнаружение тембра
    std::cout << "6. Detecting timbre...\n";
    std::map<std::string, double> timbreFeatures = audioProcessor.detectTimbre(audioStream);
    std::cout << "   ✓ Timbre detection completed\n";
    std::cout << "   Timbre features:\n";
    for (const auto& pair : timbreFeatures) {
        std::cout << "   - " << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "\n";
    
    // Фільтрація аудіо
    // Audio filtering
    // Фильтрация аудио
    std::cout << "7. Filtering audio...\n";
    AudioFilter lowPassFilter("lowpass", 1000.0); // ФНЧ з частотою зрізу 1000 Гц / Low-pass filter with 1000 Hz cutoff / ФНЧ с частотой среза 1000 Гц
    AudioStream filteredAudio = audioProcessor.filterAudio(audioStream, lowPassFilter);
    std::cout << "   ✓ Audio filtering completed\n";
    std::cout << "   Filtered audio duration: " << filteredAudio.duration << " seconds\n\n";
    
    // Зниження шуму
    // Noise reduction
    // Снижение шума
    std::cout << "8. Reducing noise...\n";
    AudioStream noiseReducedAudio = audioProcessor.reduceNoise(audioStream);
    std::cout << "   ✓ Noise reduction completed\n";
    std::cout << "   Noise reduced audio duration: " << noiseReducedAudio.duration << " seconds\n\n";
    
    // Скасування відлуння
    // Echo cancellation
    // Подавление эха
    std::cout << "9. Cancelling echo...\n";
    AudioStream echoCancelledAudio = audioProcessor.cancelEcho(audioStream);
    std::cout << "   ✓ Echo cancellation completed\n";
    std::cout << "   Echo cancelled audio duration: " << echoCancelledAudio.duration << " seconds\n\n";
    
    // Перетворення частоти дискретизації
    // Sample rate conversion
    // Преобразование частоты дискретизации
    std::cout << "10. Converting sample rate...\n";
    AudioStream convertedAudio = audioProcessor.convertSampleRate(audioStream, 22050);
    std::cout << "   ✓ Sample rate conversion completed\n";
    std::cout << "   Original sample rate: " << audioStream.frames[0].sampleRate << " Hz\n";
    std::cout << "   Converted sample rate: " << convertedAudio.frames[0].sampleRate << " Hz\n";
    std::cout << "   Converted audio duration: " << convertedAudio.duration << " seconds\n\n";
    
    // Зміна кількості каналів
    // Channel conversion
    // Преобразование количества каналов
    std::cout << "11. Converting channels...\n";
    AudioStream monoAudio = audioProcessor.convertChannels(audioStream, 1);
    std::cout << "   ✓ Channel conversion completed\n";
    std::cout << "   Original channels: " << audioStream.frames[0].channels << "\n";
    std::cout << "   Converted channels: " << monoAudio.frames[0].channels << "\n";
    std::cout << "   Mono audio duration: " << monoAudio.duration << " seconds\n\n";
    
    // Зміна гучності
    // Volume adjustment
    // Изменение громкости
    std::cout << "12. Adjusting volume...\n";
    AudioStream louderAudio = audioProcessor.adjustVolume(audioStream, 1.5); // Збільшення гучності на 50% / Increase volume by 50% / Увеличение громкости на 50%
    std::cout << "   ✓ Volume adjustment completed\n";
    std::cout << "   Louder audio duration: " << louderAudio.duration << " seconds\n\n";
    
    // Нормалізація аудіо
    // Audio normalization
    // Нормализация аудио
    std::cout << "13. Normalizing audio...\n";
    AudioStream normalizedAudio = audioProcessor.normalizeAudio(audioStream);
    std::cout << "   ✓ Audio normalization completed\n";
    std::cout << "   Normalized audio duration: " << normalizedAudio.duration << " seconds\n\n";
    
    // Видобування ознак
    // Feature extraction
    // Извлечение признаков
    std::cout << "14. Extracting features...\n";
    std::vector<double> features = audioProcessor.extractFeatures(audioStream);
    std::cout << "   ✓ Feature extraction completed\n";
    std::cout << "   Extracted " << features.size() << " features\n\n";
    
    // Порівняння аудіо
    // Audio comparison
    // Сравнение аудио
    std::cout << "15. Comparing audio...\n";
    double similarity = audioProcessor.compareAudio(audioStream, audioStream);
    std::cout << "   ✓ Audio comparison completed\n";
    std::cout << "   Audio similarity: " << similarity << "\n\n";
    
    // Збереження аудіо
    // Save audio
    // Сохранение аудио
    std::cout << "16. Saving audio...\n";
    if (!audioProcessor.saveAudio(audioStream, "output_audio.wav")) {
        std::cerr << "Failed to save audio" << std::endl;
        return 1;
    }
    std::cout << "   ✓ Audio saved successfully\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  Audio Processing Example Completed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}