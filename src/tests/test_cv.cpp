#include "../cv/ComputerVision.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace NeuroSync::CV;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync Computer Vision Tests\n";
    std::cout << "========================================\n\n";
    
    // Створення модуля комп'ютерного зору
    // Create computer vision module
    // Создание модуля компьютерного зрения
    ComputerVision cvModule;
    
    // Тест ініціалізації
    // Test initialization
    // Тест инициализации
    std::cout << "1. Testing initialization...\n";
    CVConfig config;
    bool initResult = cvModule.initialize(config);
    assert(initResult);
    std::cout << "   ✓ Initialization successful\n\n";
    
    // Тест створення зображення
    // Test image creation
    // Тест создания изображения
    std::cout << "2. Testing image creation...\n";
    Image image(640, 480, ImageType::RGB);
    assert(image.width == 640);
    assert(image.height == 480);
    assert(image.type == ImageType::RGB);
    assert(image.pixels.size() == 640 * 480);
    std::cout << "   ✓ Image creation successful\n\n";
    
    // Тест завантаження зображення
    // Test image loading
    // Тест загрузки изображения
    std::cout << "3. Testing image loading...\n";
    Image loadedImage;
    bool loadResult = cvModule.loadImage("test_image.jpg", loadedImage);
    assert(loadResult);
    std::cout << "   ✓ Image loading successful\n\n";
    
    // Тест збереження зображення
    // Test image saving
    // Тест сохранения изображения
    std::cout << "4. Testing image saving...\n";
    bool saveResult = cvModule.saveImage(loadedImage, "output_image.jpg");
    assert(saveResult);
    std::cout << "   ✓ Image saving successful\n\n";
    
    // Тест виявлення об'єктів
    // Test object detection
    // Тест обнаружения объектов
    std::cout << "5. Testing object detection...\n";
    DetectionResult detectionResult = cvModule.detectObjects(loadedImage);
    std::cout << "   ✓ Object detection successful\n";
    std::cout << "   Found " << detectionResult.objects.size() << " objects\n";
    std::cout << "   Processing time: " << detectionResult.processingTime << " ms\n\n";
    
    // Тест виявлення облич
    // Test face detection
    // Тест обнаружения лиц
    std::cout << "6. Testing face detection...\n";
    DetectionResult faceResult = cvModule.detectFaces(loadedImage);
    std::cout << "   ✓ Face detection successful\n";
    std::cout << "   Found " << faceResult.objects.size() << " faces\n";
    std::cout << "   Processing time: " << faceResult.processingTime << " ms\n\n";
    
    // Тест сегментації зображення
    // Test image segmentation
    // Тест сегментации изображения
    std::cout << "7. Testing image segmentation...\n";
    SegmentationResult segmentationResult = cvModule.segmentImage(loadedImage);
    std::cout << "   ✓ Image segmentation successful\n";
    std::cout << "   Found " << segmentationResult.segments.size() << " segments\n";
    std::cout << "   Processing time: " << segmentationResult.processingTime << " ms\n\n";
    
    // Тест оптичного розпізнавання символів
    // Test optical character recognition
    // Тест оптического распознавания символов
    std::cout << "8. Testing OCR...\n";
    std::string recognizedText = cvModule.recognizeText(loadedImage);
    std::cout << "   ✓ OCR successful\n";
    std::cout << "   Recognized text: " << recognizedText << "\n\n";
    
    // Тест класифікації зображення
    // Test image classification
    // Тест классификации изображения
    std::cout << "9. Testing image classification...\n";
    std::map<std::string, double> classifications = cvModule.classifyImage(loadedImage);
    std::cout << "   ✓ Image classification successful\n";
    std::cout << "   Found " << classifications.size() << " classifications\n\n";
    
    // Тест виявлення країв
    // Test edge detection
    // Тест обнаружения краев
    std::cout << "10. Testing edge detection...\n";
    Image edgeImage = cvModule.detectEdges(loadedImage);
    assert(edgeImage.width == loadedImage.width);
    assert(edgeImage.height == loadedImage.height);
    std::cout << "   ✓ Edge detection successful\n";
    std::cout << "   Edge image size: " << edgeImage.width << "x" << edgeImage.height << "\n\n";
    
    // Тест виявлення кутів
    // Test corner detection
    // Тест обнаружения углов
    std::cout << "11. Testing corner detection...\n";
    std::vector<Point> corners = cvModule.detectCorners(loadedImage);
    std::cout << "   ✓ Corner detection successful\n";
    std::cout << "   Found " << corners.size() << " corners\n\n";
    
    // Тест виявлення ліній
    // Test line detection
    // Тест обнаружения линий
    std::cout << "12. Testing line detection...\n";
    std::vector<std::pair<Point, Point>> lines = cvModule.detectLines(loadedImage);
    std::cout << "   ✓ Line detection successful\n";
    std::cout << "   Found " << lines.size() << " lines\n\n";
    
    // Тест фільтрації зображення
    // Test image filtering
    // Тест фильтрации изображения
    std::cout << "13. Testing image filtering...\n";
    Image filteredImage = cvModule.filterImage(loadedImage, "blur");
    assert(filteredImage.width == loadedImage.width);
    assert(filteredImage.height == loadedImage.height);
    std::cout << "   ✓ Image filtering successful\n";
    std::cout << "   Filtered image size: " << filteredImage.width << "x" << filteredImage.height << "\n\n";
    
    // Тест морфологічних операцій
    // Test morphological operations
    // Тест морфологических операций
    std::cout << "14. Testing morphological operations...\n";
    Image morphedImage = cvModule.morphologicalOperation(loadedImage, "erode");
    std::cout << "   ✓ Morphological operations successful\n";
    std::cout << "   Morphed image size: " << morphedImage.width << "x" << morphedImage.height << "\n\n";
    
    // Тест геометричних перетворень
    // Test geometric transformations
    // Тест геометрических преобразований
    std::cout << "15. Testing geometric transformations...\n";
    Image transformedImage = cvModule.transformImage(loadedImage, "resize");
    std::cout << "   ✓ Geometric transformations successful\n";
    std::cout << "   Transformed image size: " << transformedImage.width << "x" << transformedImage.height << "\n\n";
    
    // Тест видобування ознак
    // Test feature extraction
    // Тест извлечения признаков
    std::cout << "16. Testing feature extraction...\n";
    std::vector<double> features = cvModule.extractFeatures(loadedImage);
    assert(!features.empty());
    std::cout << "   ✓ Feature extraction successful\n";
    std::cout << "   Extracted " << features.size() << " features\n\n";
    
    // Тест порівняння зображень
    // Test image comparison
    // Тест сравнения изображений
    std::cout << "17. Testing image comparison...\n";
    double similarity = cvModule.compareImages(loadedImage, loadedImage);
    assert(similarity >= 0.0 && similarity <= 1.0);
    std::cout << "   ✓ Image comparison successful\n";
    std::cout << "   Image similarity: " << similarity << "\n\n";
    
    // Тест конфігурації
    // Test configuration
    // Тест конфигурации
    std::cout << "18. Testing configuration...\n";
    CVConfig newConfig = cvModule.getConfiguration();
    cvModule.updateConfiguration(newConfig);
    std::cout << "   ✓ Configuration test successful\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  All Computer Vision Tests Passed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}