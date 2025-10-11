#include "../cv/ComputerVision.h"
#include <iostream>
#include <string>

using namespace NeuroSync::CV;

int main() {
    std::cout << "========================================\n";
    std::cout << "  NeuroSync Computer Vision Example\n";
    std::cout << "========================================\n\n";
    
    // Створення модуля комп'ютерного зору
    // Create computer vision module
    // Создание модуля компьютерного зрения
    ComputerVision cvModule;
    
    // Ініціалізація модуля
    // Initialize module
    // Инициализация модуля
    CVConfig config;
    config.enableObjectDetection = true;
    config.enableFaceDetection = true;
    config.enableSegmentation = true;
    config.enableOCR = true;
    config.detectionThreshold = 0.5;
    config.maxObjects = 100;
    config.modelPath = "./models/cv_model.bin";
    
    if (!cvModule.initialize(config)) {
        std::cerr << "Failed to initialize computer vision module" << std::endl;
        return 1;
    }
    
    std::cout << "Computer vision module initialized successfully\n\n";
    
    // Завантаження зображення
    // Load image
    // Загрузка изображения
    std::cout << "1. Loading image...\n";
    Image image;
    if (!cvModule.loadImage("sample_image.jpg", image)) {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }
    std::cout << "   ✓ Image loaded successfully (" << image.width << "x" << image.height << ")\n\n";
    
    // Виявлення об'єктів
    // Object detection
    // Обнаружение объектов
    std::cout << "2. Detecting objects...\n";
    DetectionResult detectionResult = cvModule.detectObjects(image);
    std::cout << "   ✓ Object detection completed\n";
    std::cout << "   Found " << detectionResult.objects.size() << " objects\n";
    std::cout << "   Processing time: " << detectionResult.processingTime << " ms\n";
    for (const auto& obj : detectionResult.objects) {
        std::cout << "   - " << obj.label << " (confidence: " << obj.confidence << ")\n";
    }
    std::cout << "\n";
    
    // Виявлення облич
    // Face detection
    // Обнаружение лиц
    std::cout << "3. Detecting faces...\n";
    DetectionResult faceResult = cvModule.detectFaces(image);
    std::cout << "   ✓ Face detection completed\n";
    std::cout << "   Found " << faceResult.objects.size() << " faces\n";
    std::cout << "   Processing time: " << faceResult.processingTime << " ms\n";
    for (const auto& face : faceResult.objects) {
        std::cout << "   - " << face.label << " (confidence: " << face.confidence << ")\n";
    }
    std::cout << "\n";
    
    // Сегментація зображення
    // Image segmentation
    // Сегментация изображения
    std::cout << "4. Segmenting image...\n";
    SegmentationResult segmentationResult = cvModule.segmentImage(image);
    std::cout << "   ✓ Image segmentation completed\n";
    std::cout << "   Found " << segmentationResult.segments.size() << " segments\n";
    std::cout << "   Processing time: " << segmentationResult.processingTime << " ms\n";
    std::cout << "   Segmented image size: " << segmentationResult.segmented.width << "x" << segmentationResult.segmented.height << "\n";
    for (const auto& segment : segmentationResult.segments) {
        std::cout << "   - " << segment.label << " (confidence: " << segment.confidence << ")\n";
    }
    std::cout << "\n";
    
    // Оптичне розпізнавання символів
    // Optical character recognition
    // Оптическое распознавание символов
    std::cout << "5. Recognizing text...\n";
    std::string recognizedText = cvModule.recognizeText(image);
    std::cout << "   ✓ Text recognition completed\n";
    std::cout << "   Recognized text: " << recognizedText << "\n\n";
    
    // Класифікація зображення
    // Image classification
    // Классификация изображения
    std::cout << "6. Classifying image...\n";
    std::map<std::string, double> classifications = cvModule.classifyImage(image);
    std::cout << "   ✓ Image classification completed\n";
    std::cout << "   Classifications:\n";
    for (const auto& pair : classifications) {
        std::cout << "   - " << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "\n";
    
    // Виявлення країв
    // Edge detection
    // Обнаружение краев
    std::cout << "7. Detecting edges...\n";
    Image edgeImage = cvModule.detectEdges(image);
    std::cout << "   ✓ Edge detection completed\n";
    std::cout << "   Edge image size: " << edgeImage.width << "x" << edgeImage.height << "\n\n";
    
    // Виявлення кутів
    // Corner detection
    // Обнаружение углов
    std::cout << "8. Detecting corners...\n";
    std::vector<Point> corners = cvModule.detectCorners(image);
    std::cout << "   ✓ Corner detection completed\n";
    std::cout << "   Found " << corners.size() << " corners\n\n";
    
    // Виявлення ліній
    // Line detection
    // Обнаружение линий
    std::cout << "9. Detecting lines...\n";
    std::vector<std::pair<Point, Point>> lines = cvModule.detectLines(image);
    std::cout << "   ✓ Line detection completed\n";
    std::cout << "   Found " << lines.size() << " lines\n\n";
    
    // Фільтрація зображення
    // Image filtering
    // Фильтрация изображения
    std::cout << "10. Filtering image...\n";
    Image filteredImage = cvModule.filterImage(image, "blur");
    std::cout << "   ✓ Image filtering completed\n";
    std::cout << "   Filtered image size: " << filteredImage.width << "x" << filteredImage.height << "\n\n";
    
    // Морфологічні операції
    // Morphological operations
    // Морфологические операции
    std::cout << "11. Performing morphological operations...\n";
    Image morphedImage = cvModule.morphologicalOperation(image, "erode");
    std::cout << "   ✓ Morphological operations completed\n";
    std::cout << "   Morphed image size: " << morphedImage.width << "x" << morphedImage.height << "\n\n";
    
    // Геометричні перетворення
    // Geometric transformations
    // Геометрические преобразования
    std::cout << "12. Transforming image...\n";
    Image transformedImage = cvModule.transformImage(image, "resize");
    std::cout << "   ✓ Image transformation completed\n";
    std::cout << "   Transformed image size: " << transformedImage.width << "x" << transformedImage.height << "\n\n";
    
    // Видобування ознак
    // Feature extraction
    // Извлечение признаков
    std::cout << "13. Extracting features...\n";
    std::vector<double> features = cvModule.extractFeatures(image);
    std::cout << "   ✓ Feature extraction completed\n";
    std::cout << "   Extracted " << features.size() << " features\n\n";
    
    // Порівняння зображень
    // Image comparison
    // Сравнение изображений
    std::cout << "14. Comparing images...\n";
    double similarity = cvModule.compareImages(image, image);
    std::cout << "   ✓ Image comparison completed\n";
    std::cout << "   Image similarity: " << similarity << "\n\n";
    
    // Збереження зображення
    // Save image
    // Сохранение изображения
    std::cout << "15. Saving image...\n";
    if (!cvModule.saveImage(image, "output_image.jpg")) {
        std::cerr << "Failed to save image" << std::endl;
        return 1;
    }
    std::cout << "   ✓ Image saved successfully\n\n";
    
    std::cout << "========================================\n";
    std::cout << "  Computer Vision Example Completed Successfully!\n";
    std::cout << "========================================\n";
    
    return 0;
}