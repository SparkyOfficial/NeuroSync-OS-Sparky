#ifndef AUDIO_PROCESSING_H
#define AUDIO_PROCESSING_H

#include <vector>
#include <string>
#include <memory>
#include <map>

// AudioProcessing.h
// Модуль обробки аудіо для NeuroSync OS Sparky
// Audio processing module for NeuroSync OS Sparky
// Модуль обработки аудио для NeuroSync OS Sparky

namespace NeuroSync {
namespace Audio {

    // Формат аудіо
    // Audio format
    // Формат аудио
    enum class AudioFormat {
        PCM_16BIT,      // PCM 16-біт / PCM 16-bit / PCM 16-бит
        PCM_24BIT,      // PCM 24-біт / PCM 24-bit / PCM 24-бит
        PCM_32BIT,      // PCM 32-біт / PCM 32-bit / PCM 32-бит
        FLOAT_32BIT,    // 32-біт з плаваючою точкою / 32-bit floating point / 32-бит с плавающей точкой
        FLOAT_64BIT     // 64-біт з плаваючою точкою / 64-bit floating point / 64-бит с плавающей точкой
    };

    // Аудіо фрейм
    // Audio frame
    // Аудио фрейм
    struct AudioFrame {
        std::vector<double> samples;    // Семпли / Samples / Сэмплы
        int sampleRate;                // Частота дискретизації / Sample rate / Частота дискретизации
        int channels;                  // Кількість каналів / Number of channels / Количество каналов
        AudioFormat format;            // Формат аудіо / Audio format / Формат аудио
        
        AudioFrame() : sampleRate(44100), channels(2), format(AudioFormat::FLOAT_32BIT) {}
        AudioFrame(int rate, int ch, AudioFormat fmt) 
            : sampleRate(rate), channels(ch), format(fmt) {}
    };

    // Аудіо потік
    // Audio stream
    // Аудио поток
    struct AudioStream {
        std::vector<AudioFrame> frames;  // Фрейми / Frames / Фреймы
        double duration;                // Тривалість в секундах / Duration in seconds / Длительность в секундах
        
        AudioStream() : duration(0.0) {}
    };

    // Результат розпізнавання мови
    // Speech recognition result
    // Результат распознавания речи
    struct SpeechRecognitionResult {
        std::string text;               // Розпізнаний текст / Recognized text / Распознанный текст
        double confidence;             // Впевненість / Confidence / Уверенность
        double startTime;              // Час початку / Start time / Время начала
        double endTime;                // Час закінчення / End time / Время окончания
        std::map<std::string, double> wordConfidences; // Впевненість для кожного слова / Confidence for each word / Уверенность для каждого слова
        
        SpeechRecognitionResult() : confidence(0.0), startTime(0.0), endTime(0.0) {}
    };

    // Результат синтезу мови
    // Speech synthesis result
    // Результат синтеза речи
    struct SpeechSynthesisResult {
        AudioStream audio;              // Синтезоване аудіо / Synthesized audio / Синтезированное аудио
        double processingTime;         // Час обробки / Processing time / Время обработки
        
        SpeechSynthesisResult() : processingTime(0.0) {}
    };

    // Аудіо фільтр
    // Audio filter
    // Аудио фильтр
    struct AudioFilter {
        std::string type;               // Тип фільтра / Filter type / Тип фильтра
        double parameter1;             // Параметр 1 / Parameter 1 / Параметр 1
        double parameter2;             // Параметр 2 / Parameter 2 / Параметр 2
        double parameter3;             // Параметр 3 / Parameter 3 / Параметр 3
        
        AudioFilter() : type("none"), parameter1(0.0), parameter2(0.0), parameter3(0.0) {}
        AudioFilter(const std::string& t, double p1, double p2 = 0.0, double p3 = 0.0)
            : type(t), parameter1(p1), parameter2(p2), parameter3(p3) {}
    };

    // Конфігурація обробки аудіо
    // Audio processing configuration
    // Конфигурация обработки аудио
    struct AudioConfig {
        bool enableSpeechRecognition;   // Увімкнути розпізнавання мови / Enable speech recognition / Включить распознавание речи
        bool enableSpeechSynthesis;     // Увімкнути синтез мови / Enable speech synthesis / Включить синтез речи
        bool enableNoiseReduction;      // Увімкнути зниження шуму / Enable noise reduction / Включить снижение шума
        bool enableEchoCancellation;    // Увімкнути скасування відлуння / Enable echo cancellation / Включить подавление эха
        int sampleRate;                // Частота дискретизації / Sample rate / Частота дискретизации
        int channels;                  // Кількість каналів / Number of channels / Количество каналов
        AudioFormat format;            // Формат аудіо / Audio format / Формат аудио
        std::string language;          // Мова / Language / Язык
        std::string modelPath;        // Шлях до моделі / Model path / Путь к модели
        
        AudioConfig() 
            : enableSpeechRecognition(true), enableSpeechSynthesis(true), enableNoiseReduction(true), enableEchoCancellation(true),
              sampleRate(44100), channels(2), format(AudioFormat::FLOAT_32BIT),
              language("en-US"), modelPath("./models/audio_model.bin") {}
    };

    // Модуль обробки аудіо
    // Audio processing module
    // Модуль обработки аудио
    class AudioProcessor {
    public:
        AudioProcessor();
        ~AudioProcessor();
        
        // Ініціалізація модуля
        // Initialize module
        // Инициализация модуля
        bool initialize(const AudioConfig& config = AudioConfig());
        
        // Завантаження аудіо
        // Load audio
        // Загрузка аудио
        bool loadAudio(const std::string& filePath, AudioStream& audio);
        
        // Збереження аудіо
        // Save audio
        // Сохранение аудио
        bool saveAudio(const AudioStream& audio, const std::string& filePath);
        
        // Розпізнавання мови
        // Speech recognition
        // Распознавание речи
        SpeechRecognitionResult recognizeSpeech(const AudioStream& audio);
        
        // Синтез мови
        // Speech synthesis
        // Синтез речи
        SpeechSynthesisResult synthesizeSpeech(const std::string& text);
        
        // Виявлення голосової активності
        // Voice activity detection
        // Обнаружение голосовой активности
        std::vector<std::pair<double, double>> detectVoiceActivity(const AudioStream& audio);
        
        // Виявлення тональності
        // Pitch detection
        // Обнаружение тональности
        std::vector<double> detectPitch(const AudioStream& audio);
        
        // Виявлення тембру
        // Timbre detection
        // Обнаружение тембра
        std::map<std::string, double> detectTimbre(const AudioStream& audio);
        
        // Фільтрація аудіо
        // Audio filtering
        // Фильтрация аудио
        AudioStream filterAudio(const AudioStream& audio, const AudioFilter& filter);
        
        // Зниження шуму
        // Noise reduction
        // Снижение шума
        AudioStream reduceNoise(const AudioStream& audio);
        
        // Скасування відлуння
        // Echo cancellation
        // Подавление эха
        AudioStream cancelEcho(const AudioStream& audio);
        
        // Перетворення частоти дискретизації
        // Sample rate conversion
        // Преобразование частоты дискретизации
        AudioStream convertSampleRate(const AudioStream& audio, int newSampleRate);
        
        // Зміна кількості каналів
        // Channel conversion
        // Преобразование количества каналов
        AudioStream convertChannels(const AudioStream& audio, int newChannels);
        
        // Зміна гучності
        // Volume adjustment
        // Изменение громкости
        AudioStream adjustVolume(const AudioStream& audio, double gain);
        
        // Нормалізація аудіо
        // Audio normalization
        // Нормализация аудио
        AudioStream normalizeAudio(const AudioStream& audio);
        
        // Видобування ознак
        // Feature extraction
        // Извлечение признаков
        std::vector<double> extractFeatures(const AudioStream& audio);
        
        // Порівняння аудіо
        // Audio comparison
        // Сравнение аудио
        double compareAudio(const AudioStream& audio1, const AudioStream& audio2);
        
        // Отримання конфігурації
        // Get configuration
        // Получение конфигурации
        AudioConfig getConfiguration() const;
        
        // Оновлення конфігурації
        // Update configuration
        // Обновление конфигурации
        void updateConfiguration(const AudioConfig& config);
        
    private:
        AudioConfig configuration;                    // Конфігурація / Configuration / Конфигурация
        std::map<std::string, std::vector<double>> modelWeights; // Ваги моделі / Model weights / Веса модели
        std::map<std::string, std::string> languageModels; // Мовні моделі / Language models / Языковые модели
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        AudioStream applyLowPassFilter(const AudioStream& audio, double cutoffFrequency);
        AudioStream applyHighPassFilter(const AudioStream& audio, double cutoffFrequency);
        AudioStream applyBandPassFilter(const AudioStream& audio, double lowCutoff, double highCutoff);
        std::vector<double> calculateMFCC(const AudioStream& audio);
        std::vector<double> calculateSpectralFeatures(const AudioStream& audio);
        double calculateAudioEnergy(const AudioFrame& frame);
        std::vector<double> calculateZeroCrossingRate(const AudioStream& audio);
    };

} // namespace Audio
} // namespace NeuroSync

#endif // AUDIO_PROCESSING_H