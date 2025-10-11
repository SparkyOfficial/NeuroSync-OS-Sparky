#ifndef COMPUTER_VISION_H
#define COMPUTER_VISION_H

#include <vector>
#include <string>
#include <memory>
#include <map>

// ComputerVision.h
// Модуль комп'ютерного зору для NeuroSync OS Sparky
// Computer vision module for NeuroSync OS Sparky
// Модуль компьютерного зрения для NeuroSync OS Sparky

namespace NeuroSync {
namespace CV {

    // Тип зображення
    // Image type
    // Тип изображения
    enum class ImageType {
        GRAYSCALE,      // Відтінки сірого / Grayscale / Оттенки серого
        RGB,            // Кольорове RGB / Color RGB / Цветное RGB
        RGBA,           // Кольорове RGBA / Color RGBA / Цветное RGBA
        BINARY,         // Бінарне / Binary / Бинарное
        HSV             // HSV / HSV / HSV
    };

    // Структура пікселя
    // Pixel structure
    // Структура пикселя
    struct Pixel {
        union {
            struct {
                unsigned char r, g, b, a;  // Для кольорових зображень / For color images / Для цветных изображений
            };
            unsigned char gray;            // Для відтінків сірого / For grayscale / Для оттенков серого
            unsigned char value;           // Для бінарних зображень / For binary images / Для бинарных изображений
        };
        
        Pixel() : r(0), g(0), b(0), a(255) {}
        Pixel(unsigned char gray) : gray(gray) {}
        Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) 
            : r(r), g(g), b(b), a(a) {}
    };

    // Структура зображення
    // Image structure
    // Структура изображения
    struct Image {
        int width;                      // Ширина / Width / Ширина
        int height;                     // Висота / Height / Высота
        ImageType type;                // Тип зображення / Image type / Тип изображения
        std::vector<Pixel> pixels;      // Пікселі / Pixels / Пиксели
        
        Image() : width(0), height(0), type(ImageType::RGB) {}
        Image(int w, int h, ImageType t = ImageType::RGB) 
            : width(w), height(h), type(t), pixels(w * h) {}
    };

    // Прямокутник
    // Rectangle
    // Прямоугольник
    struct Rectangle {
        int x, y;           // Координати верхнього лівого кута / Top-left corner coordinates / Координаты верхнего левого угла
        int width, height;  // Ширина та висота / Width and height / Ширина и высота
        
        Rectangle() : x(0), y(0), width(0), height(0) {}
        Rectangle(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
    };

    // Точка
    // Point
    // Точка
    struct Point {
        int x, y;  // Координати / Coordinates / Координаты
        
        Point() : x(0), y(0) {}
        Point(int x, int y) : x(x), y(y) {}
    };

    // Об'єкт
    // Object
    // Объект
    struct Object {
        std::string label;          // Мітка / Label / Метка
        Rectangle boundingBox;       // Обмежувальна рамка / Bounding box / Ограничительная рамка
        double confidence;         // Впевненість / Confidence / Уверенность
        std::vector<Point> contour; // Контур / Contour / Контур
        
        Object() : confidence(0.0) {}
        Object(const std::string& l, const Rectangle& box, double conf) 
            : label(l), boundingBox(box), confidence(conf) {}
    };

    // Результат виявлення об'єктів
    // Object detection result
    // Результат обнаружения объектов
    struct DetectionResult {
        std::vector<Object> objects;  // Виявлені об'єкти / Detected objects / Обнаруженные объекты
        double processingTime;       // Час обробки / Processing time / Время обработки
        
        DetectionResult() : processingTime(0.0) {}
    };

    // Результат сегментації
    // Segmentation result
    // Результат сегментации
    struct SegmentationResult {
        Image segmented;              // Сегментоване зображення / Segmented image / Сегментированное изображение
        std::vector<Object> segments; // Сегменти / Segments / Сегменты
        double processingTime;       // Час обробки / Processing time / Время обработки
        
        SegmentationResult() : processingTime(0.0) {}
    };

    // Конфігурація комп'ютерного зору
    // Computer vision configuration
    // Конфигурация компьютерного зрения
    struct CVConfig {
        bool enableObjectDetection;     // Увімкнути виявлення об'єктів / Enable object detection / Включить обнаружение объектов
        bool enableFaceDetection;       // Увімкнути виявлення облич / Enable face detection / Включить обнаружение лиц
        bool enableSegmentation;        // Увімкнути сегментацію / Enable segmentation / Включить сегментацию
        bool enableOCR;                // Увімкнути оптичне розпізнавання символів / Enable optical character recognition / Включить оптическое распознавание символов
        double detectionThreshold;     // Поріг виявлення / Detection threshold / Порог обнаружения
        int maxObjects;               // Максимальна кількість об'єктів / Maximum number of objects / Максимальное количество объектов
        std::string modelPath;        // Шлях до моделі / Model path / Путь к модели
        
        CVConfig() 
            : enableObjectDetection(true), enableFaceDetection(true), enableSegmentation(true), enableOCR(true),
              detectionThreshold(0.5), maxObjects(100), modelPath("./models/cv_model.bin") {}
    };

    // Модуль комп'ютерного зору
    // Computer vision module
    // Модуль компьютерного зрения
    class ComputerVision {
    public:
        ComputerVision();
        ~ComputerVision();
        
        // Ініціалізація модуля
        // Initialize module
        // Инициализация модуля
        bool initialize(const CVConfig& config = CVConfig());
        
        // Завантаження зображення
        // Load image
        // Загрузка изображения
        bool loadImage(const std::string& filePath, Image& image);
        
        // Збереження зображення
        // Save image
        // Сохранение изображения
        bool saveImage(const Image& image, const std::string& filePath);
        
        // Виявлення об'єктів
        // Object detection
        // Обнаружение объектов
        DetectionResult detectObjects(const Image& image);
        
        // Виявлення облич
        // Face detection
        // Обнаружение лиц
        DetectionResult detectFaces(const Image& image);
        
        // Сегментація зображення
        // Image segmentation
        // Сегментация изображения
        SegmentationResult segmentImage(const Image& image);
        
        // Оптичне розпізнавання символів
        // Optical character recognition
        // Оптическое распознавание символов
        std::string recognizeText(const Image& image);
        
        // Класифікація зображення
        // Image classification
        // Классификация изображения
        std::map<std::string, double> classifyImage(const Image& image);
        
        // Виявлення країв
        // Edge detection
        // Обнаружение краев
        Image detectEdges(const Image& image);
        
        // Виявлення кутів
        // Corner detection
        // Обнаружение углов
        std::vector<Point> detectCorners(const Image& image);
        
        // Виявлення ліній
        // Line detection
        // Обнаружение линий
        std::vector<std::pair<Point, Point>> detectLines(const Image& image);
        
        // Фільтрація зображення
        // Image filtering
        // Фильтрация изображения
        Image filterImage(const Image& image, const std::string& filterType);
        
        // Морфологічні операції
        // Morphological operations
        // Морфологические операции
        Image morphologicalOperation(const Image& image, const std::string& operation);
        
        // Геометричні перетворення
        // Geometric transformations
        // Геометрические преобразования
        Image transformImage(const Image& image, const std::string& transformation);
        
        // Видобування ознак
        // Feature extraction
        // Извлечение признаков
        std::vector<double> extractFeatures(const Image& image);
        
        // Порівняння зображень
        // Image comparison
        // Сравнение изображений
        double compareImages(const Image& image1, const Image& image2);
        
        // Отримання конфігурації
        // Get configuration
        // Получение конфигурации
        CVConfig getConfiguration() const;
        
        // Оновлення конфігурації
        // Update configuration
        // Обновление конфигурации
        void updateConfiguration(const CVConfig& config);
        
    private:
        CVConfig configuration;                    // Конфігурація / Configuration / Конфигурация
        std::map<std::string, std::vector<double>> modelWeights; // Ваги моделі / Model weights / Веса модели
        std::map<std::string, std::string> labels; // Мітки класів / Class labels / Метки классов
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        Image convertToGrayscale(const Image& image);
        Image applyGaussianBlur(const Image& image);
        Image applyCannyEdgeDetection(const Image& image);
        std::vector<Point> findContours(const Image& image);
        Rectangle findBoundingBox(const std::vector<Point>& points);
        double calculateHistogramSimilarity(const Image& image1, const Image& image2);
        std::vector<double> calculateHistogram(const Image& image);
        Image resizeImage(const Image& image, int newWidth, int newHeight);
        Image rotateImage(const Image& image, double angle);
        Image flipImage(const Image& image, bool horizontal, bool vertical);
    };

} // namespace CV
} // namespace NeuroSync

#endif // COMPUTER_VISION_H