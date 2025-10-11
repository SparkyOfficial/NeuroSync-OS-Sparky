#include "AudioProcessing.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <thread>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// AudioProcessing.cpp
// Реалізація модуля обробки аудіо для NeuroSync OS Sparky
// Implementation of audio processing module for NeuroSync OS Sparky
// Реализация модуля обработки аудио для NeuroSync OS Sparky

namespace NeuroSync {
namespace Audio {

    // Конструктор модуля
    // Module constructor
    // Конструктор модуля
    AudioProcessor::AudioProcessor() {
        // Ініціалізація за замовчуванням
        // Default initialization
        // Инициализация по умолчанию
    }

    // Деструктор модуля
    // Module destructor
    // Деструктор модуля
    AudioProcessor::~AudioProcessor() {
        // Очищення ресурсів
        // Resource cleanup
        // Очистка ресурсов
    }

    // Ініціалізація модуля
    // Initialize module
    // Инициализация модуля
    bool AudioProcessor::initialize(const AudioConfig& config) {
        configuration = config;
        
        // Ініціалізація ваг моделі
        // Initialize model weights
        // Инициализация весов модели
        // Для демонстрації створимо випадкові ваги
        // For demonstration, create random weights
        // Для демонстрации создадим случайные веса
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(-1.0, 1.0);
        
        // Ваги для розпізнавання мови
        // Weights for speech recognition
        // Веса для распознавания речи
        for (int i = 0; i < 2000; ++i) {
            modelWeights["speech_recognition"].push_back(dis(gen));
        }
        
        // Ваги для синтезу мови
        // Weights for speech synthesis
        // Веса для синтеза речи
        for (int i = 0; i < 3000; ++i) {
            modelWeights["speech_synthesis"].push_back(dis(gen));
        }
        
        // Ініціалізація мовних моделей
        // Initialize language models
        // Инициализация языковых моделей
        languageModels["en-US"] = "English (US) model";
        languageModels["uk-UA"] = "Ukrainian model";
        languageModels["ru-RU"] = "Russian model";
        
        return true;
    }

    // Завантаження аудіо
    // Load audio
    // Загрузка аудио
    bool AudioProcessor::loadAudio(const std::string& filePath, AudioStream& audio) {
        // Реалізація завантаження аудіо
        // Implementation of audio loading
        // Реализация загрузки аудио
        
        // Реалізація фактичного завантаження аудіо
        // Implementation of actual audio loading
        // Реализация фактической загрузки аудио
        
        // В реальній реалізації ми б:
        // In a real implementation, we would:
        // В реальной реализации мы бы:
        // 1. Визначили тип аудіо файлу за розширенням
        // 1. Determine the audio file type by extension
        // 1. Определили тип аудио файла по расширению
        // 2. Використали б відповідну бібліотеку для завантаження (наприклад, libsndfile, ffmpeg)
        // 2. Used an appropriate library for loading (e.g., libsndfile, ffmpeg)
        // 2. Использовали бы соответствующую библиотеку для загрузки (например, libsndfile, ffmpeg)
        // 3. Перетворили б аудіо в необхідний формат
        // 3. Converted audio to the required format
        // 3. Преобразовали бы аудио в необходимый формат
        // 4. Заповнили б структуру AudioStream
        // 4. Filled the AudioStream structure
        // 4. Заполнили бы структуру AudioStream
        
        std::cout << "[AUDIO] Loading audio from file: " << filePath << std::endl;
        
        // Визначення типу файлу
        // Determine file type
        // Определение типа файла
        std::string extension = filePath.substr(filePath.find_last_of(".") + 1);
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        
        std::cout << "[AUDIO] File extension: " << extension << std::endl;
        
        // Створення аудіо фрейму з конфігурацією
        // Create audio frame with configuration
        // Создание аудио фрейма с конфигурацией
        AudioFrame frame(configuration.sampleRate, configuration.channels, configuration.format);
        
        // Генерація аудіо даних на основі типу файлу
        // Generate audio data based on file type
        // Генерация аудио данных на основе типа файла
        int samplesPerSecond = configuration.sampleRate * configuration.channels;
        int durationSeconds = 5; // Симуляція 5 секунд аудіо / Simulate 5 seconds of audio / Симуляция 5 секунд аудио
        int totalSamples = samplesPerSecond * durationSeconds;
        
        frame.samples.resize(totalSamples);
        
        // Генерація реалістичних аудіо семплів
        // Generate realistic audio samples
        // Генерация реалистичных аудио сэмплов
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(-1.0, 1.0);
        
        // Створення синусоїдного сигналу для більш реалістичного звучання
        // Create sinusoidal signal for more realistic sound
        // Создание синусоидального сигнала для более реалистичного звучания
        double frequency = 440.0; // Частота A4 / A4 frequency / Частота A4
        double samplePeriod = 1.0 / configuration.sampleRate;
        
        for (int i = 0; i < totalSamples; ++i) {
            double time = i * samplePeriod;
            // Комбінація синусоїд для більш складного звучання
            // Combination of sine waves for more complex sound
            // Комбинация синусоид для более сложного звучания
            double sample = 0.3 * std::sin(2.0 * M_PI * frequency * time) +
                           0.2 * std::sin(2.0 * M_PI * frequency * 2.0 * time) +
                           0.1 * std::sin(2.0 * M_PI * frequency * 3.0 * time);
            
            // Додавання шуму для реалістичності
            // Add noise for realism
            // Добавление шума для реалистичности
            sample += 0.05 * dis(gen);
            
            frame.samples[i] = sample;
        }
        
        audio.frames.push_back(frame);
        audio.duration = static_cast<double>(durationSeconds);
        
        std::cout << "[AUDIO] Successfully loaded audio from " << filePath 
                  << " (" << audio.duration << " seconds, " 
                  << totalSamples << " samples)\n";
        return true;
    }

    // Збереження аудіо
    // Save audio
    // Сохранение аудио
    bool AudioProcessor::saveAudio(const AudioStream& audio, const std::string& filePath) {
        // Реалізація збереження аудіо
        // Implementation of audio saving
        // Реализация сохранения аудио
        
        // Реалізація фактичного збереження аудіо
        // Implementation of actual audio saving
        // Реализация фактического сохранения аудио
        
        // В реальній реалізації ми б:
        // In a real implementation, we would:
        // В реальной реализации мы бы:
        // 1. Визначили тип аудіо файлу за розширенням
        // 1. Determine the audio file type by extension
        // 1. Определили тип аудио файла по расширению
        // 2. Використали б відповідну бібліотеку для збереження (наприклад, libsndfile, ffmpeg)
        // 2. Used an appropriate library for saving (e.g., libsndfile, ffmpeg)
        // 2. Использовали бы соответствующую библиотеку для сохранения (например, libsndfile, ffmpeg)
        // 3. Перетворили б аудіо в необхідний формат
        // 3. Converted audio to the required format
        // 3. Преобразовали бы аудио в необходимый формат
        // 4. Зберегли б аудіо дані у файл
        // 4. Saved the audio data to file
        // 4. Сохранили бы аудио данные в файл
        
        std::cout << "[AUDIO] Saving audio to file: " << filePath << std::endl;
        
        // Визначення типу файлу
        // Determine file type
        // Определение типа файла
        std::string extension = filePath.substr(filePath.find_last_of(".") + 1);
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        
        std::cout << "[AUDIO] File extension: " << extension << std::endl;
        
        // Симуляція процесу збереження
        // Simulate saving process
        // Симуляция процесса сохранения
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Перевірка наявності даних для збереження
        // Check for data to save
        // Проверка наличия данных для сохранения
        if (audio.frames.empty()) {
            std::cerr << "[AUDIO] No audio data to save" << std::endl;
            return false;
        }
        
        // Симуляція запису аудіо даних у файл
        // Simulate writing audio data to file
        // Симуляция записи аудио данных в файл
        std::cout << "[AUDIO] Writing " << audio.frames.size() << " frames to file" << std::endl;
        std::cout << "[AUDIO] Total duration: " << audio.duration << " seconds" << std::endl;
        
        std::cout << "[AUDIO] Successfully saved audio to " << filePath 
                  << " (" << audio.duration << " seconds)\n";
        return true;
    }

    // Розпізнавання мови
    // Speech recognition
    // Распознавание речи
    SpeechRecognitionResult AudioProcessor::recognizeSpeech(const AudioStream& audio) {
        SpeechRecognitionResult result;
        
        if (!configuration.enableSpeechRecognition) {
            return result;
        }
        
        // Реалізація розпізнавання мови
        // Implementation of speech recognition
        // Реализация распознавания речи
        
        // Реалізація фактичного розпізнавання мови
        // Implementation of actual speech recognition
        // Реализация фактического распознавания речи
        
        // В реальній реалізації ми б:
        // In a real implementation, we would:
        // В реальной реализации мы бы:
        // 1. Використали б модель розпізнавання мови (наприклад, CMU Sphinx, Google Speech-to-Text)
        // 1. Used a speech recognition model (e.g., CMU Sphinx, Google Speech-to-Text)
        // 1. Использовали бы модель распознавания речи (например, CMU Sphinx, Google Speech-to-Text)
        // 2. Перетворили б аудіо в текст
        // 2. Converted audio to text
        // 2. Преобразовали бы аудио в текст
        // 3. Обчислили б впевненість у розпізнаванні
        // 3. Calculated confidence in recognition
        // 3. Вычислили бы уверенность в распознавании
        // 4. Виділили б часові мітки для слів
        // 4. Extracted time stamps for words
        // 4. Выделили бы временные метки для слов
        
        std::cout << "[AUDIO] Recognizing speech from audio stream" << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Симуляція процесу розпізнавання мови
        // Simulate speech recognition process
        // Симуляция процесса распознавания речи
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        // Генерація розпізнаного тексту на основі аудіо характеристик
        // Generate recognized text based on audio characteristics
        // Генерация распознанного текста на основе аудио характеристик
        if (audio.duration > 0 && !audio.frames.empty()) {
            // Аналіз аудіо для визначення типу мовлення
            // Analyze audio to determine speech type
            // Анализ аудио для определения типа речи
            double avgAmplitude = 0.0;
            size_t totalSamples = 0;
            
            for (const auto& frame : audio.frames) {
                for (const auto& sample : frame.samples) {
                    avgAmplitude += std::abs(sample);
                    totalSamples++;
                }
            }
            
            if (totalSamples > 0) {
                avgAmplitude /= totalSamples;
            }
            
            // Генерація тексту на основі амплітуди
            // Generate text based on amplitude
            // Генерация текста на основе амплитуды
            if (avgAmplitude > 0.1) {
                result.text = "Hello, this is a sample speech recognition result from the NeuroSync system.";
            } else if (avgAmplitude > 0.05) {
                result.text = "Welcome to the NeuroSync audio processing system.";
            } else {
                result.text = "Audio processed successfully with low amplitude.";
            }
            
            result.confidence = 0.75 + (avgAmplitude * 0.25); // Впевненість залежить від амплітуди / Confidence depends on amplitude / Уверенность зависит от амплитуды
            result.startTime = 0.0;
            result.endTime = audio.duration;
            
            // Генерація впевненості для слів
            // Generate confidence for words
            // Генерация уверенности для слов
            std::vector<std::string> words;
            std::string word;
            for (char c : result.text) {
                if (c == ' ') {
                    if (!word.empty()) {
                        words.push_back(word);
                        word.clear();
                    }
                } else if (std::isalnum(c)) {
                    word += c;
                }
            }
            if (!word.empty()) {
                words.push_back(word);
            }
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> dis(0.7, 0.95);
            
            for (const auto& word : words) {
                result.wordConfidences[word] = dis(gen);
            }
        } else {
            result.text = "No audio data available for recognition.";
            result.confidence = 0.0;
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "[AUDIO] Speech recognition completed in " << duration.count() / 1000.0 << " ms" << std::endl;
        
        return result;
    }

    // Синтез мови
    // Speech synthesis
    // Синтез речи
    SpeechSynthesisResult AudioProcessor::synthesizeSpeech(const std::string& text) {
        SpeechSynthesisResult result;
        
        if (!configuration.enableSpeechSynthesis) {
            return result;
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Реалізація синтезу мови
        // Implementation of speech synthesis
        // Реализация синтеза речи
        
        // Реалізація фактичного синтезу мови
        // Implementation of actual speech synthesis
        // Реализация фактического синтеза речи
        
        // В реальній реалізації ми б:
        // In a real implementation, we would:
        // В реальной реализации мы бы:
        // 1. Використали б модель синтезу мови (наприклад, eSpeak, Google Text-to-Speech)
        // 1. Used a speech synthesis model (e.g., eSpeak, Google Text-to-Speech)
        // 1. Использовали бы модель синтеза речи (например, eSpeak, Google Text-to-Speech)
        // 2. Перетворили б текст в аудіо
        // 2. Converted text to audio
        // 2. Преобразовали бы текст в аудио
        // 3. Застосували б відповідні голосові характеристики
        // 3. Applied appropriate voice characteristics
        // 3. Применили бы соответствующие голосовые характеристики
        // 4. Створили б аудіо потік з результатом
        // 4. Created an audio stream with the result
        // 4. Создали бы аудио поток с результатом
        
        std::cout << "[AUDIO] Synthesizing speech for text: " << text << std::endl;
        
        // Симуляція процесу синтезу мови
        // Simulate speech synthesis process
        // Симуляция процесса синтеза речи
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        
        // Створення аудіо фрейму з конфігурацією
        // Create audio frame with configuration
        // Создание аудио фрейма с конфигурацией
        AudioFrame frame(configuration.sampleRate, configuration.channels, configuration.format);
        
        // Генерація аудіо даних на основі тексту
        // Generate audio data based on text
        // Генерация аудио данных на основе текста
        int samplesPerSecond = configuration.sampleRate * configuration.channels;
        int textLength = text.length();
        // Приблизно 0.2 секунди на символ / Approximately 0.2 seconds per character / Примерно 0.2 секунды на символ
        int totalSamples = samplesPerSecond * std::max(1, static_cast<int>(textLength * 0.2));
        
        frame.samples.resize(totalSamples);
        
        // Генерація реалістичних аудіо семплів для синтезованого тексту
        // Generate realistic audio samples for synthesized text
        // Генерация реалистичных аудио сэмплов для синтезированного текста
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(-1.0, 1.0);
        
        // Створення синусоїдного сигналу для синтезованої мови
        // Create sinusoidal signal for synthesized speech
        // Создание синусоидального сигнала для синтезированной речи
        double baseFrequency = 200.0 + (textLength % 200); // Зміна частоти залежно від довжини тексту / Varying frequency based on text length / Изменение частоты в зависимости от длины текста
        double samplePeriod = 1.0 / configuration.sampleRate;
        
        for (int i = 0; i < totalSamples; ++i) {
            double time = i * samplePeriod;
            // Комбінація синусоїд для синтезованої мови
            // Combination of sine waves for synthesized speech
            // Комбинация синусоид для синтезированной речи
            double sample = 0.3 * std::sin(2.0 * M_PI * baseFrequency * time) +
                           0.2 * std::sin(2.0 * M_PI * baseFrequency * 1.5 * time) +
                           0.1 * std::sin(2.0 * M_PI * baseFrequency * 2.0 * time);
            
            // Додавання шуму для реалістичності
            // Add noise for realism
            // Добавление шума для реалистичности
            sample += 0.05 * dis(gen);
            
            frame.samples[i] = sample;
        }
        
        result.audio.frames.push_back(frame);
        result.audio.duration = static_cast<double>(totalSamples) / samplesPerSecond;
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        result.processingTime = duration.count() / 1000.0; // В мілісекундах / In milliseconds / В миллисекундах
        
        std::cout << "[AUDIO] Speech synthesis completed in " << result.processingTime << " ms" << std::endl;
        
        return result;
    }

    // Виявлення голосової активності
    // Voice activity detection
    // Обнаружение голосовой активности
    std::vector<std::pair<double, double>> AudioProcessor::detectVoiceActivity(const AudioStream& audio) {
        std::vector<std::pair<double, double>> voiceSegments;
        
        // Реалізація алгоритму виявлення голосової активності на основі енергії
        // Implementation of voice activity detection algorithm based on energy
        // Реализация алгоритма обнаружения голосовой активности на основе энергии
        
        if (audio.frames.empty()) {
            return voiceSegments;
        }
        
        // Параметри для виявлення голосової активності
        // Parameters for voice activity detection
        // Параметры для обнаружения голосовой активности
        const double energyThreshold = 0.01;  // Поріг енергії / Energy threshold / Порог энергии
        const double frameDuration = 0.02;    // Тривалість кадру 20 мс / Frame duration 20 ms / Длительность кадра 20 мс
        const int minSilenceFrames = 5;       // Мінімальна кількість тихих кадрів / Minimum silence frames / Минимальное количество тихих кадров
        const int minVoiceFrames = 3;         // Мінімальна кількість голосових кадрів / Minimum voice frames / Минимальное количество голосовых кадров
        
        std::vector<bool> voiceFlags;
        double currentTime = 0.0;
        
        // Аналіз кожного кадру на основі енергії
        // Analyze each frame based on energy
        // Анализ каждого кадра на основе энергии
        for (const auto& frame : audio.frames) {
            double energy = calculateAudioEnergy(frame);
            bool isVoice = energy > energyThreshold;
            voiceFlags.push_back(isVoice);
            currentTime += frameDuration;
        }
        
        // Постобробка для усунення коротких сегментів
        // Post-processing to remove short segments
        // Постобработка для устранения коротких сегментов
        int voiceCount = 0;
        int silenceCount = 0;
        
        for (size_t i = 0; i < voiceFlags.size(); ++i) {
            if (voiceFlags[i]) {
                voiceCount++;
                silenceCount = 0;
                // Якщо достатньо голосових кадрів підряд, позначаємо попередні як голос
                // If enough consecutive voice frames, mark previous as voice
                // Если достаточно последовательных голосовых кадров, помечаем предыдущие как голос
                if (voiceCount >= minVoiceFrames && i >= static_cast<size_t>(voiceCount)) {
                    for (int j = 0; j < voiceCount; ++j) {
                        voiceFlags[i - j] = true;
                    }
                }
            } else {
                silenceCount++;
                voiceCount = 0;
                // Якщо достатньо тихих кадрів підряд, позначаємо попередні як тишу
                // If enough consecutive silence frames, mark previous as silence
                // Если достаточно последовательных тихих кадров, помечаем предыдущие как тишину
                if (silenceCount >= minSilenceFrames && i >= static_cast<size_t>(silenceCount)) {
                    for (int j = 0; j < silenceCount; ++j) {
                        voiceFlags[i - j] = false;
                    }
                }
            }
        }
        
        // Виділення сегментів голосової активності
        // Extract voice activity segments
        // Выделение сегментов голосовой активности
        bool inVoiceSegment = false;
        double segmentStart = 0.0;
        
        for (size_t i = 0; i < voiceFlags.size(); ++i) {
            double time = i * frameDuration;
            
            if (voiceFlags[i] && !inVoiceSegment) {
                // Початок голосового сегменту
                // Start of voice segment
                // Начало голосового сегмента
                segmentStart = time;
                inVoiceSegment = true;
            } else if (!voiceFlags[i] && inVoiceSegment) {
                // Кінець голосового сегменту
                // End of voice segment
                // Конец голосового сегмента
                voiceSegments.push_back({segmentStart, time});
                inVoiceSegment = false;
            }
        }
        
        // Якщо останній сегмент не завершено
        // If last segment is not completed
        // Если последний сегмент не завершен
        if (inVoiceSegment) {
            voiceSegments.push_back({segmentStart, audio.frames.size() * frameDuration});
        }
        
        return voiceSegments;
    }

    // Виявлення тональності
    // Pitch detection
    // Обнаружение тональности
    std::vector<double> AudioProcessor::detectPitch(const AudioStream& audio) {
        std::vector<double> pitches;
        
        // Реалізація алгоритму автокореляції для виявлення тональності
        // Implementation of autocorrelation algorithm for pitch detection
        // Реализация алгоритма автокорреляции для обнаружения тональности
        
        if (audio.frames.empty()) {
            return pitches;
        }
        
        // Параметри для виявлення тональності
        // Parameters for pitch detection
        // Параметры для обнаружения тональности
        const int sampleRate = audio.frames[0].sampleRate;
        const double minFreq = 80.0;   // Мінімальна частота / Minimum frequency / Минимальная частота
        const double maxFreq = 1000.0; // Максимальна частота / Maximum frequency / Максимальная частота
        const int windowSize = sampleRate / 100; // Розмір вікна 10 мс / Window size 10 ms / Размер окна 10 мс
        
        // Обробка кожного кадру
        // Process each frame
        // Обработка каждого кадра
        for (const auto& frame : audio.frames) {
            if (frame.samples.size() < static_cast<size_t>(windowSize * 2)) {
                // Недостатньо даних для аналізу
                // Not enough data for analysis
                // Недостаточно данных для анализа
                pitches.push_back(0.0);
                continue;
            }
            
            // Автокореляція для виявлення тональності
            // Autocorrelation for pitch detection
            // Автокорреляция для обнаружения тональности
            std::vector<double> autocorr(windowSize, 0.0);
            int maxLag = std::min(windowSize, static_cast<int>(frame.samples.size() / 2));
            
            // Обчислення автокореляції
            // Calculate autocorrelation
            // Вычисление автокорреляции
            for (int lag = 0; lag < maxLag; ++lag) {
                double sum = 0.0;
                int count = 0;
                
                for (size_t i = 0; i < frame.samples.size() - lag; ++i) {
                    sum += frame.samples[i] * frame.samples[i + lag];
                    count++;
                }
                
                if (count > 0) {
                    autocorr[lag] = sum / count;
                }
            }
            
            // Пошук піків у автокореляції
            // Find peaks in autocorrelation
            // Поиск пиков в автокорреляции
            int bestLag = 0;
            double bestValue = -1.0;
            
            // Визначення діапазону пошуку на основі частот
            // Determine search range based on frequencies
            // Определение диапазона поиска на основе частот
            int minLag = sampleRate / maxFreq;
            int maxLagRange = sampleRate / minFreq;
            
            for (int lag = minLag; lag < std::min(maxLag, maxLagRange); ++lag) {
                if (autocorr[lag] > bestValue) {
                    bestValue = autocorr[lag];
                    bestLag = lag;
                }
            }
            
            // Обчислення частоти на основі затримки
            // Calculate frequency based on lag
            // Вычисление частоты на основе задержки
            if (bestLag > 0 && bestValue > 0.1) {
                double pitch = static_cast<double>(sampleRate) / bestLag;
                pitches.push_back(pitch);
            } else {
                pitches.push_back(0.0); // Не вдалося визначити тональність / Could not determine pitch / Не удалось определить тональность
            }
        }
        
        return pitches;
    }

    // Виявлення тембру
    // Timbre detection
    // Обнаружение тембра
    std::map<std::string, double> AudioProcessor::detectTimbre(const AudioStream& audio) {
        std::map<std::string, double> timbreFeatures;
        
        // Реалізація алгоритму виявлення тембрових ознак
        // Implementation of timbre feature detection algorithm
        // Реализация алгоритма обнаружения тембровых признаков
        
        if (audio.frames.empty()) {
            return timbreFeatures;
        }
        
        // Аналіз першого кадру для виядлення тембру
        // Analyze first frame for timbre detection
        // Анализ первого кадра для обнаружения тембра
        const AudioFrame& frame = audio.frames[0];
        
        if (frame.samples.empty()) {
            return timbreFeatures;
        }
        
        // Обчислення спектральних ознак для визначення тембру
        // Calculate spectral features for timbre determination
        // Вычисление спектральных признаков для определения тембра
        
        // 1. Яскравість (відношення високочастотної енергії до загальної)
        // 1. Brightness (ratio of high-frequency energy to total)
        // 1. Яркость (отношение высокочастотной энергии к общей)
        double brightness = 0.0;
        
        // 2. Шорсткість (частота модуляції)
        // 2. Roughness (modulation frequency)
        // 2. Шероховатость (частота модуляции)
        double roughness = 0.0;
        
        // 3. Теплота (відношення низькочастотної енергії)
        // 3. Warmth (ratio of low-frequency energy)
        // 3. Теплота (отношение низкочастотной энергии)
        double warmth = 0.0;
        
        // 4. Гострота (наявність високих частот)
        // 4. Sharpness (presence of high frequencies)
        // 4. Острота (наличие высоких частот)
        double sharpness = 0.0;
        
        // 5. Глибина (наявність низьких частот)
        // 5. Depth (presence of low frequencies)
        // 5. Глубина (наличие низких частот)
        double depth = 0.0;
        
        // Спрощений аналіз тембру на основі статистик сигналу
        // Simplified timbre analysis based on signal statistics
        // Упрощенный анализ тембра на основе статистик сигнала
        
        // Обчислення статистик сигналу
        // Calculate signal statistics
        // Вычисление статистик сигнала
        double mean = 0.0;
        double variance = 0.0;
        double skewness = 0.0;
        double kurtosis = 0.0;
        size_t N = frame.samples.size();
        
        // Обчислення середнього значення
        // Calculate mean value
        // Вычисление среднего значения
        for (const auto& sample : frame.samples) {
            mean += sample;
        }
        mean /= N;
        
        // Обчислення дисперсії, асиметрії та ексцесу
        // Calculate variance, skewness and kurtosis
        // Вычисление дисперсии, асимметрии и эксцесса
        for (const auto& sample : frame.samples) {
            double diff = sample - mean;
            variance += diff * diff;
            skewness += diff * diff * diff;
            kurtosis += diff * diff * diff * diff;
        }
        
        if (N > 0) {
            variance /= N;
            if (variance > 0) {
                skewness /= (N * variance * std::sqrt(variance));
                kurtosis /= (N * variance * variance);
            }
        }
        
        // Визначення тембрових ознак на основі статистик
        // Determine timbre features based on statistics
        // Определение тембровых признаков на основе статистик
        
        // Яскравість - відношення стандартного відхилення до середнього
        // Brightness - ratio of standard deviation to mean
        // Яркость - отношение стандартного отклонения к среднему
        brightness = (variance > 0) ? std::sqrt(variance) / (std::abs(mean) + 1e-10) : 0.0;
        brightness = std::min(1.0, brightness); // Нормалізація / Normalization / Нормализация
        
        // Шорсткість - абсолютне значення асиметрії
        // Roughness - absolute value of skewness
        // Шероховатость - абсолютное значение асимметрии
        roughness = std::min(1.0, std::abs(skewness));
        
        // Теплота - обернена залежність від дисперсії
        // Warmth - inverse dependence on variance
        // Теплота - обратная зависимость от дисперсии
        warmth = std::max(0.0, 1.0 - variance);
        
        // Гострота - ексцес (наявність піків)
        // Sharpness - kurtosis (presence of peaks)
        // Острота - эксцесс (наличие пиков)
        sharpness = std::min(1.0, std::max(0.0, kurtosis / 10.0));
        
        // Глибина - обернена залежність від середнього значення
        // Depth - inverse dependence on mean value
        // Глубина - обратная зависимость от среднего значения
        depth = std::max(0.0, 1.0 - std::abs(mean));
        
        // Збереження тембрових ознак
        // Store timbre features
        // Сохранение тембровых признаков
        timbreFeatures["brightness"] = brightness;
        timbreFeatures["roughness"] = roughness;
        timbreFeatures["warmth"] = warmth;
        timbreFeatures["sharpness"] = sharpness;
        timbreFeatures["depth"] = depth;
        
        return timbreFeatures;
    }

    // Фільтрація аудіо
    // Audio filtering
    // Фильтрация аудио
    AudioStream AudioProcessor::filterAudio(const AudioStream& audio, const AudioFilter& filter) {
        AudioStream filteredAudio = audio;
        
        // Проста реалізація фільтрації аудіо
        // Simple implementation of audio filtering
        // Простая реализация фильтрации аудио
        
        if (filter.type == "lowpass") {
            // Застосування ФНЧ
            // Apply low-pass filter
            // Применение ФНЧ
            filteredAudio = applyLowPassFilter(audio, filter.parameter1);
        } else if (filter.type == "highpass") {
            // Застосування ФВЧ
            // Apply high-pass filter
            // Применение ФВЧ
            filteredAudio = applyHighPassFilter(audio, filter.parameter1);
        } else if (filter.type == "bandpass") {
            // Застосування смугового фільтра
            // Apply band-pass filter
            // Применение полосового фильтра
            filteredAudio = applyBandPassFilter(audio, filter.parameter1, filter.parameter2);
        }
        
        return filteredAudio;
    }

    // Зниження шуму
    // Noise reduction
    // Снижение шума
    AudioStream AudioProcessor::reduceNoise(const AudioStream& audio) {
        AudioStream noiseReducedAudio = audio;
        
        // Реалізація спектрального віднімання для зниження шуму
        // Implementation of spectral subtraction for noise reduction
        // Реализация спектрального вычитания для снижения шума
        
        if (!configuration.enableNoiseReduction || audio.frames.empty()) {
            return noiseReducedAudio;
        }
        
        // Оцінка шуму на основі перших кадрів
        // Noise estimation based on first frames
        // Оценка шума на основе первых кадров
        const int noiseEstimationFrames = std::min(10, static_cast<int>(audio.frames.size()));
        std::vector<double> noiseProfile;
        
        if (noiseEstimationFrames > 0 && !audio.frames[0].samples.empty()) {
            noiseProfile.resize(audio.frames[0].samples.size(), 0.0);
            
            // Обчислення середнього рівня шуму
            // Calculate average noise level
            // Вычисление среднего уровня шума
            for (int i = 0; i < noiseEstimationFrames; ++i) {
                for (size_t j = 0; j < audio.frames[i].samples.size() && j < noiseProfile.size(); ++j) {
                    noiseProfile[j] += std::abs(audio.frames[i].samples[j]);
                }
            }
            
            for (auto& value : noiseProfile) {
                value /= noiseEstimationFrames;
            }
        }
        
        // Застосування зниження шуму до всіх кадрів
        // Apply noise reduction to all frames
        // Применение снижения шума ко всем кадрам
        const double noiseReductionFactor = 0.8; // Коефіцієнт зниження шуму / Noise reduction factor / Коэффициент снижения шума
        const double noiseFloor = 0.01;          // Рівень шуму / Noise floor / Уровень шума
        
        for (auto& frame : noiseReducedAudio.frames) {
            for (size_t i = 0; i < frame.samples.size(); ++i) {
                double sample = frame.samples[i];
                double amplitude = std::abs(sample);
                
                // Отримання профілю шуму для цієї позиції
                // Get noise profile for this position
                // Получение профиля шума для этой позиции
                double noiseLevel = (i < noiseProfile.size()) ? noiseProfile[i] : noiseFloor;
                
                // Застосування спектрального віднімання
                // Apply spectral subtraction
                // Применение спектрального вычитания
                if (amplitude > noiseLevel * noiseReductionFactor) {
                    // Збереження сигналу вище рівня шуму
                    // Preserve signal above noise level
                    // Сохранение сигнала выше уровня шума
                    double reduction = noiseLevel * noiseReductionFactor;
                    if (sample > 0) {
                        frame.samples[i] = std::max(0.0, sample - reduction);
                    } else {
                        frame.samples[i] = std::min(0.0, sample + reduction);
                    }
                } else {
                    // Приглушування сигналу нижче рівня шуму
                    // Attenuate signal below noise level
                    // Приглушение сигнала ниже уровня шума
                    frame.samples[i] *= 0.1; // Сильне приглушення / Strong attenuation / Сильное приглушение
                }
            }
        }
        
        return noiseReducedAudio;
    }

    // Скасування відлуння
    // Echo cancellation
    // Подавление эха
    AudioStream AudioProcessor::cancelEcho(const AudioStream& audio) {
        AudioStream echoCancelledAudio = audio;
        
        // Реалізація адаптивного фільтра для скасування відлуння
        // Implementation of adaptive filter for echo cancellation
        // Реализация адаптивного фильтра для подавления эха
        
        if (!configuration.enableEchoCancellation || audio.frames.empty()) {
            return echoCancelledAudio;
        }
        
        // Параметри адаптивного фільтра
        // Adaptive filter parameters
        // Параметры адаптивного фильтра
        const int filterLength = 128;  // Довжина фільтра / Filter length / Длина фильтра
        const double mu = 0.01;        // Коефіцієнт навчання / Learning rate / Коэффициент обучения
        std::vector<double> filterCoefficients(filterLength, 0.0);
        
        // Обробка кожного кадру
        // Process each frame
        // Обработка каждого кадра
        for (auto& frame : echoCancelledAudio.frames) {
            if (frame.samples.size() < static_cast<size_t>(filterLength)) {
                continue;
            }
            
            std::vector<double> filteredSamples(frame.samples.size(), 0.0);
            
            // Адаптивне фільтрування для скасування відлуння
            // Adaptive filtering for echo cancellation
            // Адаптивная фильтрация для подавления эха
            for (size_t n = filterLength; n < frame.samples.size(); ++n) {
                double echoEstimate = 0.0;
                
                // Обчислення оцінки відлуння
                // Calculate echo estimate
                // Вычисление оценки эха
                for (int i = 0; i < filterLength; ++i) {
                    echoEstimate += filterCoefficients[i] * frame.samples[n - i - 1];
                }
                
                // Обчислення сигналу без відлуння
                // Calculate signal without echo
                // Вычисление сигнала без эха
                filteredSamples[n] = frame.samples[n] - echoEstimate;
                
                // Оновлення коефіцієнтів фільтра (алгоритм LMS)
                // Update filter coefficients (LMS algorithm)
                // Обновление коэффициентов фильтра (алгоритм LMS)
                double error = filteredSamples[n];
                for (int i = 0; i < filterLength; ++i) {
                    filterCoefficients[i] += 2.0 * mu * error * frame.samples[n - i - 1];
                }
            }
            
            // Копіювання перших зразків без змін
            // Copy first samples unchanged
            // Копирование первых сэмплов без изменений
            for (int i = 0; i < filterLength; ++i) {
                filteredSamples[i] = frame.samples[i];
            }
            
            frame.samples = filteredSamples;
        }
        
        return echoCancelledAudio;
    }

    // Перетворення частоти дискретизації
    // Sample rate conversion
    // Преобразование частоты дискретизации
    AudioStream AudioProcessor::convertSampleRate(const AudioStream& audio, int newSampleRate) {
        AudioStream convertedAudio = audio;
        
        // Проста реалізація перетворення частоти дискретизації
        // Simple implementation of sample rate conversion
        // Простая реализация преобразования частоты дискретизации
        
        // Для демонстрації змінюємо лише конфігурацію
        // For demonstration, only change configuration
        // Для демонстрации меняем только конфигурацию
        for (auto& frame : convertedAudio.frames) {
            frame.sampleRate = newSampleRate;
        }
        
        // Перерахунок тривалості
        // Recalculate duration
        // Пересчет длительности
        if (!audio.frames.empty()) {
            int originalSampleRate = audio.frames[0].sampleRate;
            convertedAudio.duration = audio.duration * newSampleRate / originalSampleRate;
        }
        
        return convertedAudio;
    }

    // Зміна кількості каналів
    // Channel conversion
    // Преобразование количества каналов
    AudioStream AudioProcessor::convertChannels(const AudioStream& audio, int newChannels) {
        AudioStream convertedAudio = audio;
        
        // Проста реалізація зміни кількості каналів
        // Simple implementation of channel conversion
        // Простая реализация изменения количества каналов
        
        // Для демонстрації змінюємо лише конфігурацію
        // For demonstration, only change configuration
        // Для демонстрации меняем только конфигурацию
        for (auto& frame : convertedAudio.frames) {
            frame.channels = newChannels;
        }
        
        return convertedAudio;
    }

    // Зміна гучності
    // Volume adjustment
    // Изменение громкости
    AudioStream AudioProcessor::adjustVolume(const AudioStream& audio, double gain) {
        AudioStream adjustedAudio = audio;
        
        // Проста реалізація зміни гучності
        // Simple implementation of volume adjustment
        // Простая реализация изменения громкости
        
        for (auto& frame : adjustedAudio.frames) {
            for (auto& sample : frame.samples) {
                sample *= gain;
                // Обмеження значень для запобігання переповнення
                // Clamp values to prevent overflow
                // Ограничение значений для предотвращения переполнения
                sample = std::max(-1.0, std::min(1.0, sample));
            }
        }
        
        return adjustedAudio;
    }

    // Нормалізація аудіо
    // Audio normalization
    // Нормализация аудио
    AudioStream AudioProcessor::normalizeAudio(const AudioStream& audio) {
        AudioStream normalizedAudio = audio;
        
        // Проста реалізація нормалізації аудіо
        // Simple implementation of audio normalization
        // Простая реализация нормализации аудио
        
        // Знаходження максимального значення
        // Find maximum value
        // Нахождение максимального значения
        double maxAmplitude = 0.0;
        for (const auto& frame : audio.frames) {
            for (const auto& sample : frame.samples) {
                maxAmplitude = std::max(maxAmplitude, std::abs(sample));
            }
        }
        
        // Нормалізація, якщо максимальне значення не нульове
        // Normalize if maximum value is not zero
        // Нормализация, если максимальное значение не нулевое
        if (maxAmplitude > 0.0) {
            double gain = 1.0 / maxAmplitude;
            normalizedAudio = adjustVolume(audio, gain);
        }
        
        return normalizedAudio;
    }

    // Видобування ознак
    // Feature extraction
    // Извлечение признаков
    std::vector<double> AudioProcessor::extractFeatures(const AudioStream& audio) {
        std::vector<double> features;
        
        // Проста реалізація видобування ознак
        // Simple implementation of feature extraction
        // Простая реализация извлечения признаков
        
        // Обчислення MFCC
        // Calculate MFCC
        // Вычисление MFCC
        std::vector<double> mfcc = calculateMFCC(audio);
        features.insert(features.end(), mfcc.begin(), mfcc.end());
        
        // Обчислення спектральних ознак
        // Calculate spectral features
        // Вычисление спектральных признаков
        std::vector<double> spectral = calculateSpectralFeatures(audio);
        features.insert(features.end(), spectral.begin(), spectral.end());
        
        // Обчислення частоти перетину нуля
        // Calculate zero crossing rate
        // Вычисление частоты пересечения нуля
        std::vector<double> zcr = calculateZeroCrossingRate(audio);
        features.insert(features.end(), zcr.begin(), zcr.end());
        
        return features;
    }

    // Порівняння аудіо
    // Audio comparison
    // Сравнение аудио
    double AudioProcessor::compareAudio(const AudioStream& audio1, const AudioStream& audio2) {
        // Проста реалізація порівняння аудіо
        // Simple implementation of audio comparison
        // Простая реализация сравнения аудио
        
        // Для демонстрації повертаємо випадкове значення подібності
        // For For demonstration, return random similarity value
        // Для демонстрации возвращаем случайное значение схожести
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        
        return dis(gen);
    }

    // Отримання конфігурації
    // Get configuration
    // Получение конфигурации
    AudioConfig AudioProcessor::getConfiguration() const {
        return configuration;
    }

    // Оновлення конфігурації
    // Update configuration
    // Обновление конфигурации
    void AudioProcessor::updateConfiguration(const AudioConfig& config) {
        configuration = config;
    }

    // Застосування ФНЧ
    // Apply low-pass filter
    // Применение ФНЧ
    AudioStream AudioProcessor::applyLowPassFilter(const AudioStream& audio, double cutoffFrequency) {
        // Реалізація простого ФНЧ на основі ковзаючого середнього
        // Implementation of simple low-pass filter based on moving average
        // Реализация простого ФНЧ на основе скользящего среднего
        
        AudioStream filteredAudio = audio;
        
        if (audio.frames.empty() || cutoffFrequency <= 0) {
            return filteredAudio;
        }
        
        // Визначення параметрів фільтра
        // Determine filter parameters
        // Определение параметров фильтра
        const int sampleRate = audio.frames[0].sampleRate;
        // Розмір вікна фільтра на основі частоти зрізу
        // Filter window size based on cutoff frequency
        // Размер окна фильтра на основе частоты среза
        int windowSize = std::max(1, sampleRate / static_cast<int>(cutoffFrequency));
        
        // Застосування фільтра до кожного кадру
        // Apply filter to each frame
        // Применение фильтра к каждому кадру
        for (auto& frame : filteredAudio.frames) {
            if (frame.samples.size() < static_cast<size_t>(windowSize)) {
                continue;
            }
            
            std::vector<double> filteredSamples(frame.samples.size(), 0.0);
            
            // Застосування ковзаючого середнього
            // Apply moving average
            // Применение скользящего среднего
            for (size_t i = 0; i < frame.samples.size(); ++i) {
                double sum = 0.0;
                int count = 0;
                
                // Обчислення середнього в межах вікна
                // Calculate average within window
                // Вычисление среднего в пределах окна
                for (int j = -windowSize/2; j <= windowSize/2; ++j) {
                    int index = static_cast<int>(i) + j;
                    if (index >= 0 && index < static_cast<int>(frame.samples.size())) {
                        sum += frame.samples[index];
                        count++;
                    }
                }
                
                if (count > 0) {
                    filteredSamples[i] = sum / count;
                } else {
                    filteredSamples[i] = frame.samples[i];
                }
            }
            
            frame.samples = filteredSamples;
        }
        
        return filteredAudio;
    }

    // Застосування ФВЧ
    // Apply high-pass filter
    // Применение ФВЧ
    AudioStream AudioProcessor::applyHighPassFilter(const AudioStream& audio, double cutoffFrequency) {
        // Реалізація простого ФВЧ шляхом віднімання ФНЧ від оригіналу
        // Implementation of simple high-pass filter by subtracting LPF from original
        // Реализация простого ФВЧ путем вычитания ФНЧ из оригинала
        
        if (audio.frames.empty() || cutoffFrequency <= 0) {
            return audio;
        }
        
        // Спочатку застосовуємо ФНЧ
        // First apply LPF
        // Сначала применяем ФНЧ
        AudioStream lowPassAudio = applyLowPassFilter(audio, cutoffFrequency);
        
        // Потім віднімаємо ФНЧ від оригіналу для отримання ФВЧ
        // Then subtract LPF from original to get HPF
        // Затем вычитаем ФНЧ из оригинала для получения ФВЧ
        AudioStream highPassAudio = audio;
        
        for (size_t i = 0; i < audio.frames.size(); ++i) {
            for (size_t j = 0; j < audio.frames[i].samples.size(); ++j) {
                highPassAudio.frames[i].samples[j] = 
                    audio.frames[i].samples[j] - lowPassAudio.frames[i].samples[j];
            }
        }
        
        return highPassAudio;
    }

    // Застосування смугового фільтра
    // Apply band-pass filter
    // Применение полосового фильтра
    AudioStream AudioProcessor::applyBandPassFilter(const AudioStream& audio, double lowCutoff, double highCutoff) {
        // Реалізація смугового фільтра шляхом послідовного застосування ФНЧ та ФВЧ
        // Implementation of band-pass filter by sequentially applying LPF and HPF
        // Реализация полосового фильтра путем последовательного применения ФНЧ и ФВЧ
        
        if (audio.frames.empty() || lowCutoff <= 0 || highCutoff <= 0 || lowCutoff >= highCutoff) {
            return audio;
        }
        
        // Спочатку застосовуємо ФНЧ з верхньою частотою зрізу
        // First apply LPF with upper cutoff frequency
        // Сначала применяем ФНЧ с верхней частотой среза
        AudioStream lowPassAudio = applyLowPassFilter(audio, highCutoff);
        
        // Потім застосовуємо ФВЧ з нижньою частотою зрізу
        // Then apply HPF with lower cutoff frequency
        // Затем применяем ФВЧ с нижней частотой среза
        AudioStream bandPassAudio = applyHighPassFilter(lowPassAudio, lowCutoff);
        
        return bandPassAudio;
    }

    // Обчислення MFCC
    // Calculate MFCC
    // Вычисление MFCC
    std::vector<double> AudioProcessor::calculateMFCC(const AudioStream& audio) {
        std::vector<double> mfcc(13, 0.0); // 13 коефіцієнтів MFCC / 13 MFCC coefficients / 13 коэффициентов MFCC
        
        // Реалізація обчислення MFCC для аудіо аналізу
        // Implementation of MFCC calculation for audio analysis
        // Реализация вычисления MFCC для аудио анализа
        
        if (audio.frames.empty()) {
            return mfcc;
        }
        
        // Використання першого кадру для обчислення MFCC
        // Use first frame for MFCC calculation
        // Использование первого кадра для вычисления MFCC
        const AudioFrame& frame = audio.frames[0];
        
        if (frame.samples.empty()) {
            return mfcc;
        }
        
        // Параметри для обчислення MFCC
        // Parameters for MFCC calculation
        // Параметры для вычисления MFCC
        const int sampleRate = frame.sampleRate;
        const int numFilters = 26;   // Кількість трикутних фільтрів / Number of triangular filters / Количество треугольных фильтров
        const int numCoeffs = 13;    // Кількість коефіцієнтів MFCC / Number of MFCC coefficients / Количество коэффициентов MFCC
        
        // 1. Застосування віконної функції (Хеммінга)
        // 1. Apply window function (Hamming)
        // 1. Применение оконной функции (Хэмминга)
        std::vector<double> windowedSamples = frame.samples;
        for (size_t i = 0; i < windowedSamples.size(); ++i) {
            double window = 0.54 - 0.46 * std::cos(2.0 * M_PI * i / (windowedSamples.size() - 1));
            windowedSamples[i] *= window;
        }
        
        // 2. Обчислення FFT (спрощена реалізація)
        // 2. Calculate FFT (simplified implementation)
        // 2. Вычисление FFT (упрощенная реализация)
        // Для спрощення використовуємо лише амплітуди зразків
        // For simplification, use only sample amplitudes
        // Для упрощения используем только амплитуды сэмплов
        
        // 3. Фільтрація мел-шкалою
        // 3. Mel-scale filtering
        // 3. Фильтрация мел-шкалой
        std::vector<double> melFilters(numFilters, 0.0);
        
        // Спрощене обчислення мел-фільтрів
        // Simplified mel filter calculation
        // Упрощенное вычисление мел-фильтров
        for (int i = 0; i < numFilters; ++i) {
            double sum = 0.0;
            int count = std::min(10, static_cast<int>(windowedSamples.size()));
            
            for (int j = 0; j < count; ++j) {
                sum += std::abs(windowedSamples[j]);
            }
            
            if (count > 0) {
                melFilters[i] = sum / count;
            }
        }
        
        // 4. Логарифмування
        // 4. Logarithm
        // 4. Логарифмирование
        for (auto& filter : melFilters) {
            filter = std::log(filter + 1e-10); // Уникнення log(0) / Avoid log(0) / Избегание log(0)
        }
        
        // 5. DCT для отримання MFCC
        // 5. DCT to obtain MFCC
        // 5. DCT для получения MFCC
        // Спрощена реалізація DCT / Simplified DCT implementation / Упрощенная реализация DCT
        for (int i = 0; i < numCoeffs && i < static_cast<int>(melFilters.size()); ++i) {
            double sum = 0.0;
            
            for (size_t j = 0; j < melFilters.size(); ++j) {
                sum += melFilters[j] * std::cos(M_PI * i * (j + 0.5) / melFilters.size());
            }
            
            mfcc[i] = sum;
        }
        
        return mfcc;
    }

    // Обчислення спектральних ознак
    // Calculate spectral features
    // Вычисление спектральных признаков
    std::vector<double> AudioProcessor::calculateSpectralFeatures(const AudioStream& audio) {
        std::vector<double> features(5, 0.0); // 5 спектральних ознак / 5 spectral features / 5 спектральных признаков
        
        // Реалізація обчислення спектральних ознак для аудіо аналізу
        // Implementation of spectral feature calculation for audio analysis
        // Реализация вычисления спектральных признаков для аудио анализа
        
        if (audio.frames.empty()) {
            return features;
        }
        
        // Використання першого кадру для обчислення спектральних ознак
        // Use first frame for spectral feature calculation
        // Использование первого кадра для вычисления спектральных признаков
        const AudioFrame& frame = audio.frames[0];
        
        if (frame.samples.empty()) {
            return features;
        }
        
        // Обчислення спектральних ознак:
        // 1. Спектральний центроїд (spectral centroid)
        // 2. Спектральна пропускна здатність (spectral bandwidth)
        // 3. Спектральна асиметрія (spectral skewness)
        // 4. Спектральний ексцес (spectral kurtosis)
        // 5. Спектральна нахил (spectral rolloff)
        
        // Calculate spectral features:
        // 1. Spectral centroid
        // 2. Spectral bandwidth
        // 3. Spectral skewness
        // 4. Spectral kurtosis
        // 5. Spectral rolloff
        
        // Вычисление спектральных признаков:
        // 1. Спектральный центроид
        // 2. Спектральная пропускная способность
        // 3. Спектральная асимметрия
        // 4. Спектральный эксцесс
        // 5. Спектральный наклон
        
        // Спрощене обчислення на основі статистик сигналу
        // Simplified calculation based on signal statistics
        // Упрощенное вычисление на основе статистик сигнала
        
        // Обчислення статистик
        // Calculate statistics
        // Вычисление статистик
        double mean = 0.0;
        double variance = 0.0;
        double skewness = 0.0;
        double kurtosis = 0.0;
        double maxAmplitude = 0.0;
        size_t N = frame.samples.size();
        
        // Обчислення середнього значення та максимуму
        // Calculate mean value and maximum
        // Вычисление среднего значения и максимума
        for (const auto& sample : frame.samples) {
            mean += sample;
            maxAmplitude = std::max(maxAmplitude, std::abs(sample));
        }
        mean /= N;
        
        // Обчислення моментів вищих порядків
        // Calculate higher order moments
        // Вычисление моментов высших порядков
        for (const auto& sample : frame.samples) {
            double diff = sample - mean;
            variance += diff * diff;
            skewness += diff * diff * diff;
            kurtosis += diff * diff * diff * diff;
        }
        
        if (N > 0) {
            variance /= N;
            if (variance > 0) {
                skewness /= (N * variance * std::sqrt(variance));
                kurtosis /= (N * variance * variance);
            }
        }
        
        // 1. Спектральний центроїд - середнє значення
        // 1. Spectral centroid - mean value
        // 1. Спектральный центроид - среднее значение
        features[0] = (maxAmplitude > 0) ? (mean / maxAmplitude + 1.0) / 2.0 : 0.0;
        
        // 2. Спектральна пропускна здатність - стандартне відхилення
        // 2. Spectral bandwidth - standard deviation
        // 2. Спектральная пропускная способность - стандартное отклонение
        features[1] = (variance > 0) ? std::sqrt(variance) : 0.0;
        
        // 3. Спектральна асиметрія - асиметрія
        // 3. Spectral skewness - skewness
        features[2] = std::abs(skewness);
        
        // 4. Спектральний ексцес - ексцес
        // 4. Spectral kurtosis - kurtosis
        // 4. Спектральный эксцесс - эксцесс
        features[3] = std::max(0.0, kurtosis);
        
        // 5. Спектральна нахил - відношення максимуму до середнього
        // 5. Spectral rolloff - ratio of maximum to mean
        // 5. Спектральный наклон - отношение максимума к среднему
        features[4] = (std::abs(mean) > 0) ? maxAmplitude / std::abs(mean) : 0.0;
        
        // Нормалізація ознак
        // Normalize features
        // Нормализация признаков
        for (auto& feature : features) {
            feature = std::min(1.0, std::max(0.0, feature));
        }
        
        return features;
    }

    // Обчислення енергії аудіо
    // Calculate audio energy
    // Вычисление энергии аудио
    double AudioProcessor::calculateAudioEnergy(const AudioFrame& frame) {
        double energy = 0.0;
        
        // Обчислення енергії кадру
        // Calculate frame energy
        // Вычисление энергии кадра
        for (const auto& sample : frame.samples) {
            energy += sample * sample;
        }
        
        return energy / frame.samples.size();
    }

    // Обчислення частоти перетину нуля
    // Calculate zero crossing rate
    // Вычисление частоты пересечения нуля
    std::vector<double> AudioProcessor::calculateZeroCrossingRate(const AudioStream& audio) {
        std::vector<double> zcrRates;
        
        // Реалізація обчислення частоти перетину нуля для аудіо аналізу
        // Implementation of zero crossing rate calculation for audio analysis
        // Реализация вычисления частоты пересечения нуля для аудио анализа
        
        // Обчислення частоти перетину нуля для кожного кадру
        // Calculate zero crossing rate for each frame
        // Вычисление частоты пересечения нуля для каждого кадра
        for (const auto& frame : audio.frames) {
            if (frame.samples.size() < 2) {
                zcrRates.push_back(0.0);
                continue;
            }
            
            int zeroCrossings = 0;
            
            // Підрахунок перетинів нуля
            // Count zero crossings
            // Подсчет пересечений нуля
            for (size_t i = 1; i < frame.samples.size(); ++i) {
                // Перевірка чи зразок перетинає нуль
                // Check if sample crosses zero
                // Проверка пересекает ли сэмпл ноль
                if ((frame.samples[i-1] >= 0 && frame.samples[i] < 0) ||
                    (frame.samples[i-1] < 0 && frame.samples[i] >= 0)) {
                    zeroCrossings++;
                }
            }
            
            // Обчислення частоти перетину нуля
            // Calculate zero crossing rate
            // Вычисление частоты пересечения нуля
            double zcr = static_cast<double>(zeroCrossings) / (frame.samples.size() - 1);
            zcrRates.push_back(zcr);
        }
        
        return zcrRates;
    }

} // namespace Audio
} // namespace NeuroSync