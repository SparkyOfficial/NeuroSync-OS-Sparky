#ifndef COMPUTER_VISION_H
#define COMPUTER_VISION_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <chrono>
#include "../neuron/NeuronManager.h"
#include "../network_neural/NeuralNetwork.h"
#include "../event/EventSystem.h"

// ComputerVision.h
// Модуль комп'ютерного зору для NeuroSync OS Sparky
// Computer vision module for NeuroSync OS Sparky
// Модуль компьютерного зрения для NeuroSync OS Sparky

namespace NeuroSync {
namespace Vision {

    // Тип зображення
    // Image type
    // Тип изображения
    enum class ImageType {
        RGB,        // Кольорове зображення / Color image / Цветное изображение
        GRAYSCALE,  // Чорно-біле зображення / Grayscale image / Черно-белое изображение
        BINARY,     // Бінарне зображення / Binary image / Бинарное изображение
        DEPTH,      // Глибинне зображення / Depth image / Глубинное изображение
        THERMAL,    // Теплове зображення / Thermal image / Тепловое изображение
        INFRARED    // Інфрачервоне зображення / Infrared image / Инфракрасное изображение
    };

    // Структура зображення
    // Image structure
    // Структура изображения
    struct Image {
        std::vector<std::vector<std::vector<unsigned char>>> pixels; // Пікселі зображення / Image pixels / Пиксели изображения
        int width;                                                  // Ширина / Width / Ширина
        int height;                                                 // Висота / Height / Высота
        int channels;                                               // Кількість каналів / Number of channels / Количество каналов
        ImageType type;                                             // Тип зображення / Image type / Тип изображения
        long long timestamp;                                       // Часова мітка / Timestamp / Временная метка
        
        Image() : width(0), height(0), channels(0), type(ImageType::RGB), timestamp(0) {}
        Image(int w, int h, int c, ImageType t) : width(w), height(h), channels(c), type(t), timestamp(0) {
            pixels.resize(h, std::vector<std::vector<unsigned char>>(w, std::vector<unsigned char>(c, 0)));
        }
    };

    // Структура виявленого об'єкта
    // Detected object structure
    // Структура обнаруженного объекта
    struct DetectedObject {
        std::string className;              // Назва класу / Class name / Название класса
        double confidence;                  // Впевненість / Confidence / Уверенность
        int x, y, width, height;            // Позиція та розмір / Position and size / Позиция и размер
        std::map<std::string, double> features; // Ознаки об'єкта / Object features / Признаки объекта
        long long timestamp;               // Часова мітка / Timestamp / Временная метка
        
        DetectedObject() : confidence(0.0), x(0), y(0), width(0), height(0), timestamp(0) {}
    };

    // Структура відеопотоку
    // Video stream structure
    // Структура видеопотока
    struct VideoStream {
        std::string streamId;               // ID потоку / Stream ID / ID потока
        int frameWidth;                     // Ширина кадру / Frame width / Ширина кадра
        int frameHeight;                    // Висота кадру / Frame height / Высота кадра
        int frameRate;                      // Частота кадрів / Frame rate / Частота кадров
        std::string source;                 // Джерело / Source / Источник
        bool isActive;                     // Чи активний / Is active / Активен ли
        long long lastFrameTime;           // Час останнього кадру / Last frame time / Время последнего кадра
        
        VideoStream() : frameWidth(0), frameHeight(0), frameRate(0), isActive(false), lastFrameTime(0) {}
    };

    // Модуль комп'ютерного зору
    // Computer vision module
    // Модуль компьютерного зрения
    class ComputerVision {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        ComputerVision();
        
        // Деструктор
        // Destructor
        // Деструктор
        ~ComputerVision();
        
        // Ініціалізація модуля
        // Initialize module
        // Инициализация модуля
        bool initialize();
        
        // Завантажити зображення
        // Load image
        // Загрузить изображение
        bool loadImage(const std::string& filePath, Image& image);
        
        // Зберегти зображення
        // Save image
        // Сохранить изображение
        bool saveImage(const Image& image, const std::string& filePath);
        
        // Захопити кадр з відеопотоку
        // Capture frame from video stream
        // Захватить кадр из видеопотока
        bool captureFrame(const std::string& streamId, Image& frame);
        
        // Додати відеопотік
        // Add video stream
        // Добавить видеопоток
        bool addVideoStream(const std::string& streamId, const std::string& source, int width, int height, int frameRate);
        
        // Видалити відеопотік
        // Remove video stream
        // Удалить видеопоток
        bool removeVideoStream(const std::string& streamId);
        
        // Виявлення об'єктів
        // Object detection
        // Обнаружение объектов
        std::vector<DetectedObject> detectObjects(const Image& image);
        
        // Класифікація зображень
        // Image classification
        // Классификация изображений
        std::map<std::string, double> classifyImage(const Image& image);
        
        // Сегментація зображень
        // Image segmentation
        // Сегментация изображений
        Image segmentImage(const Image& image);
        
        // Відстеження об'єктів
        // Object tracking
        // Отслеживание объектов
        std::vector<DetectedObject> trackObjects(const std::vector<Image>& frames);
        
        // Розпізнавання облич
        // Face recognition
        // Распознавание лиц
        std::map<std::string, double> recognizeFaces(const Image& image);
        
        // Виявлення руху
        // Motion detection
        // Обнаружение движения
        std::vector<std::pair<int, int>> detectMotion(const Image& frame1, const Image& frame2);
        
        // Оптичне розпізнавання символів
        // Optical character recognition
        // Оптическое распознавание символов
        std::string recognizeText(const Image& image);
        
        // Покращення зображення
        // Image enhancement
        // Улучшение изображения
        Image enhanceImage(const Image& image);
        
        // Стерео зіставлення
        // Stereo matching
        // Стерео сопоставление
        Image stereoMatching(const Image& leftImage, const Image& rightImage);
        
        // Генерація 3D хмари точок
        // Generate 3D point cloud
        // Генерация 3D облака точек
        std::vector<std::vector<double>> generatePointCloud(const Image& depthImage);
        
        // Аналіз сцени
        // Scene analysis
        // Анализ сцены
        std::map<std::string, std::string> analyzeScene(const Image& image);
        
        // Виявлення аномалій
        // Anomaly detection
        // Обнаружение аномалий
        std::vector<DetectedObject> detectAnomalies(const std::vector<Image>& images);
        
        // Навчання моделі
        // Train model
        // Обучение модели
        bool trainModel(const std::vector<Image>& trainingImages, 
                       const std::vector<std::vector<DetectedObject>>& trainingLabels,
                       int epochs, double learningRate);
        
        // Експорт моделі
        // Export model
        // Экспорт модели
        bool exportModel(const std::string& filePath);
        
        // Імпорт моделі
        // Import model
        // Импорт модели
        bool importModel(const std::string& filePath);
        
        // Отримати статистику
        // Get statistics
        // Получить статистику
        struct VisionStatistics {
            size_t totalImagesProcessed;
            size_t totalObjectsDetected;
            double averageProcessingTime;
            size_t totalVideoStreams;
            long long lastProcessingTime;
            double detectionAccuracy;
        };
        
        VisionStatistics getStatistics() const;
        
        // Отримати версію модуля
        // Get module version
        // Получить версию модуля
        std::string getVersion() const;
        
    private:
        std::unique_ptr<Network::NeuralNetwork> detectionModel;     // Модель виявлення / Detection model / Модель обнаружения
        std::unique_ptr<Network::NeuralNetwork> classificationModel; // Модель класифікації / Classification model / Модель классификации
        std::unique_ptr<Network::NeuralNetwork> segmentationModel;   // Модель сегментації / Segmentation model / Модель сегментации
        std::unique_ptr<NeuronManager> neuronManager;              // Менеджер нейронів / Neuron manager / Менеджер нейронов
        std::unique_ptr<Event::EventSystem> eventSystem;           // Система подій / Event system / Система событий
        VisionStatistics statistics;                                // Статистика / Statistics / Статистика
        bool isInitialized;                                       // Прапор ініціалізації / Initialization flag / Флаг инициализации
        std::string version;                                      // Версія модуля / Module version / Версия модуля
        std::map<std::string, VideoStream> videoStreams;          // Відеопотоки / Video streams / Видеопотоки
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void initializeModels();
        long long getCurrentTimeMillis() const;
        std::vector<unsigned char> convertToGrayscale(const std::vector<std::vector<std::vector<unsigned char>>>& pixels);
        std::vector<std::vector<std::vector<unsigned char>>> applyFilter(const std::vector<std::vector<std::vector<unsigned char>>>& pixels, 
                                                                        const std::vector<std::vector<double>>& kernel);
        double calculateSimilarity(const Image& img1, const Image& img2);
        std::vector<double> extractFeatures(const Image& image);
        std::string generateReport(const VisionStatistics& stats);
    };

} // namespace Vision
} // namespace NeuroSync

#endif // COMPUTER_VISION_H