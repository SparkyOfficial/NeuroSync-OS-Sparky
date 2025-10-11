#ifndef ADVANCED_NLP_H
#define ADVANCED_NLP_H

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <chrono>
#include <set>
#include "../neuron/NeuronManager.h"
#include "../network_neural/NeuralNetwork.h"
#include "../event/EventSystem.h"

// AdvancedNLP.h
// Модуль розширеного оброблення природної мови для NeuroSync OS Sparky
// Advanced natural language processing module for NeuroSync OS Sparky
// Модуль расширенной обработки естественного языка для NeuroSync OS Sparky

namespace NeuroSync {
namespace NLP {

    // Тип мови
    // Language type
    // Тип языка
    enum class Language {
        ENGLISH,    // Англійська / English / Английский
        UKRAINIAN,  // Українська / Ukrainian / Украинский
        RUSSIAN,    // Російська / Russian / Русский
        GERMAN,     // Німецька / German / Немецкий
        FRENCH,     // Французька / French / Французский
        SPANISH,    // Іспанська / Spanish / Испанский
        CHINESE,    // Китайська / Chinese / Китайский
        JAPANESE    // Японська / Japanese / Японский
    };

    // Структура токена
    // Token structure
    // Структура токена
    struct Token {
        std::string text;           // Текст токена / Token text / Текст токена
        std::string lemma;          // Лема / Lemma / Лемма
        std::string pos;            // Частина мови / Part of speech / Часть речи
        std::string nerTag;         // Тег іменованої сутності / Named entity tag / Тег именованной сущности
        int tokenId;                // ID токена / Token ID / ID токена
        int sentenceId;             // ID речення / Sentence ID / ID предложения
        std::map<std::string, double> embeddings; // Векторні представлення / Vector representations / Векторные представления
        
        Token() : tokenId(0), sentenceId(0) {}
        Token(const std::string& t, int id, int sentId) : text(t), tokenId(id), sentenceId(sentId) {}
    };

    // Структура речення
    // Sentence structure
    // Структура предложения
    struct Sentence {
        std::vector<Token> tokens;      // Токени / Tokens / Токены
        std::string text;               // Текст речення / Sentence text / Текст предложения
        int sentenceId;                 // ID речення / Sentence ID / ID предложения
        double sentimentScore;          // Оцінка настрою / Sentiment score / Оценка настроения
        std::string sentimentLabel;      // Мітка настрою / Sentiment label / Метка настроения
        std::map<std::string, double> topics; // Теми / Topics / Темы
        
        Sentence() : sentenceId(0), sentimentScore(0.0) {}
    };

    // Структура документа
    // Document structure
    // Структура документа
    struct Document {
        std::vector<Sentence> sentences;    // Речення / Sentences / Предложения
        std::string text;                   // Текст документа / Document text / Текст документа
        std::string docId;                  // ID документа / Document ID / ID документа
        Language language;                  // Мова / Language / Язык
        long long timestamp;               // Часова мітка / Timestamp / Временная метка
        std::map<std::string, double> topics; // Теми документа / Document topics / Темы документа
        double readabilityScore;            // Оцінка читабельності / Readability score / Оценка читаемости
        
        Document() : sentenceId(0), language(Language::ENGLISH), timestamp(0), readabilityScore(0.0) {}
    };

    // Структура запиту
    // Query structure
    // Структура запроса
    struct Query {
        std::string text;               // Текст запиту / Query text / Текст запроса
        Language language;              // Мова запиту / Query language / Язык запроса
        std::vector<std::string> keywords; // Ключові слова / Keywords / Ключевые слова
        std::map<std::string, double> intent; // Наміри / Intent / Намерения
        long long timestamp;           // Часова мітка / Timestamp / Временная метка
        
        Query() : language(Language::ENGLISH), timestamp(0) {}
    };

    // Структура результату
    // Result structure
    // Структура результата
    struct Result {
        std::string text;               // Текст результату / Result text / Текст результата
        double relevanceScore;          // Оцінка релевантності / Relevance score / Оценка релевантности
        std::string docId;              // ID документа / Document ID / ID документа
        int sentenceId;                 // ID речення / Sentence ID / ID предложения
        std::map<std::string, double> entities; // Виявлені сутності / Detected entities / Обнаруженные сущности
        
        Result() : relevanceScore(0.0), sentenceId(0) {}
    };

    // Модуль розширеного оброблення природної мови
    // Advanced natural language processing module
    // Модуль расширенной обработки естественного языка
    class AdvancedNLP {
    public:
        // Конструктор
        // Constructor
        // Конструктор
        AdvancedNLP();
        
        // Деструктор
        // Destructor
        // Деструктор
        ~AdvancedNLP();
        
        // Ініціалізація модуля
        // Initialize module
        // Инициализация модуля
        bool initialize();
        
        // Токенізація тексту
        // Tokenize text
        // Токенизация текста
        std::vector<Token> tokenize(const std::string& text, Language language = Language::ENGLISH);
        
        // Лематизація токенів
        // Lemmatize tokens
        // Лемматизация токенов
        std::vector<Token> lemmatize(const std::vector<Token>& tokens);
        
        // Визначення частин мови
        // Part-of-speech tagging
        // Определение частей речи
        std::vector<Token> posTag(const std::vector<Token>& tokens);
        
        // Визначення іменованих сутностей
        // Named entity recognition
        // Определение именованных сущностей
        std::vector<Token> nerTag(const std::vector<Token>& tokens);
        
        // Аналіз настрою
        // Sentiment analysis
        // Анализ настроения
        std::pair<std::string, double> analyzeSentiment(const std::string& text);
        
        // Витягування ключових слів
        // Keyword extraction
        // Извлечение ключевых слов
        std::vector<std::string> extractKeywords(const std::string& text);
        
        // Визначення тем
        // Topic modeling
        // Определение тем
        std::map<std::string, double> modelTopics(const std::string& text);
        
        // Переклад тексту
        // Translate text
        // Перевод текста
        std::string translate(const std::string& text, Language sourceLang, Language targetLang);
        
        // Генерація тексту
        // Text generation
        // Генерация текста
        std::string generateText(const std::string& prompt, int maxLength = 100);
        
        // Відповідь на запитання
        // Question answering
        // Ответ на вопрос
        std::string answerQuestion(const std::string& question, const std::string& context);
        
        // Резюмування тексту
        // Text summarization
        // Резюмирование текста
        std::string summarize(const std::string& text, double compressionRatio = 0.3);
        
        // Пошук інформації
        // Information retrieval
        // Поиск информации
        std::vector<Result> search(const Query& query, const std::vector<Document>& documents);
        
        // Кластеризація документів
        // Document clustering
        // Кластеризация документов
        std::map<std::string, std::vector<Document>> clusterDocuments(const std::vector<Document>& documents);
        
        // Виявлення плагіату
        // Plagiarism detection
        // Обнаружение плагиата
        std::vector<std::pair<Document, double>> detectPlagiarism(const Document& document, const std::vector<Document>& corpus);
        
        // Аналіз читабельності
        // Readability analysis
        // Анализ читаемости
        double analyzeReadability(const std::string& text);
        
        // Виявлення мови
        // Language detection
        // Обнаружение языка
        Language detectLanguage(const std::string& text);
        
        // Витягування відносин
        // Relation extraction
        // Извлечение отношений
        std::map<std::string, std::vector<std::pair<std::string, std::string>>> extractRelations(const std::vector<Token>& tokens);
        
        // Аналіз синтаксису
        // Syntactic analysis
        // Анализ синтаксиса
        std::vector<std::vector<int>> parseSyntax(const std::vector<Token>& tokens);
        
        // Навчання моделі
        // Train model
        // Обучение модели
        bool trainModel(const std::vector<std::string>& trainingData, 
                       const std::vector<std::vector<std::string>>& trainingLabels,
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
        struct NLPStatistics {
            size_t totalDocumentsProcessed;
            size_t totalTokensProcessed;
            size_t totalSentencesAnalyzed;
            double averageProcessingTime;
            size_t totalTranslationsPerformed;
            long long lastProcessingTime;
            double accuracy;
        };
        
        NLPStatistics getStatistics() const;
        
        // Отримати версію модуля
        // Get module version
        // Получить версию модуля
        std::string getVersion() const;
        
    private:
        std::unique_ptr<Network::NeuralNetwork> tokenizationModel;     // Модель токенізації / Tokenization model / Модель токенизации
        std::unique_ptr<Network::NeuralNetwork> posTaggingModel;       // Модель визначення частин мови / POS tagging model / Модель определения частей речи
        std::unique_ptr<Network::NeuralNetwork> nerModel;              // Модель визначення іменованих сутностей / NER model / Модель определения именованных сущностей
        std::unique_ptr<Network::NeuralNetwork> sentimentModel;        // Модель аналізу настрою / Sentiment analysis model / Модель анализа настроения
        std::unique_ptr<Network::NeuralNetwork> translationModel;      // Модель перекладу / Translation model / Модель перевода
        std::unique_ptr<NeuronManager> neuronManager;                 // Менеджер нейронів / Neuron manager / Менеджер нейронов
        std::unique_ptr<Event::EventSystem> eventSystem;              // Система подій / Event system / Система событий
        NLPStatistics statistics;                                      // Статистика / Statistics / Статистика
        bool isInitialized;                                          // Прапор ініціалізації / Initialization flag / Флаг инициализации
        std::string version;                                         // Версія модуля / Module version / Версия модуля
        std::map<Language, std::set<std::string>> stopWords;         // Стоп-слова / Stop words / Стоп-слова
        std::map<std::string, std::vector<double>> wordEmbeddings;   // Векторні представлення слів / Word embeddings / Векторные представления слов
        
        // Внутрішні методи
        // Internal methods
        // Внутренние методы
        void initializeModels();
        void initializeStopWords();
        void initializeWordEmbeddings();
        long long getCurrentTimeMillis() const;
        std::vector<std::string> splitIntoSentences(const std::string& text);
        std::vector<std::string> preprocessText(const std::string& text);
        double calculateSimilarity(const std::string& text1, const std::string& text2);
        std::vector<double> textToVector(const std::string& text);
        std::string vectorToText(const std::vector<double>& vector);
        std::string generateReport(const NLPStatistics& stats);
    };

} // namespace NLP
} // namespace NeuroSync

#endif // ADVANCED_NLP_H