#include "NaturalLanguageProcessing.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>
#include <set>
#include <numeric>

// NaturalLanguageProcessing.cpp
// Реалізація модуля обробки природної мови для NeuroSync OS Sparky
// Implementation of natural language processing module for NeuroSync OS Sparky
// Реализация модуля обработки естественного языка для NeuroSync OS Sparky

namespace NeuroSync {
namespace NLP {

    // Стоп-слова для різних мов
    // Stop words for different languages
    // Стоп-слова для разных языков
    const std::set<std::string> ENGLISH_STOP_WORDS = {
        "the", "a", "an", "and", "or", "but", "in", "on", "at", "to", "for", "of", "with", "by",
        "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "do", "does", "did",
        "will", "would", "could", "should", "may", "might", "must", "can", "shall",
        "i", "you", "he", "she", "it", "we", "they", "me", "him", "her", "us", "them",
        "my", "your", "his", "her", "its", "our", "their", "mine", "yours", "hers", "ours", "theirs"
    };

    const std::set<std::string> UKRAINIAN_STOP_WORDS = {
        "і", "та", "але", "або", "в", "на", "за", "до", "з", "про", "для", "через", "під", "над",
        "є", "бути", "була", "було", "були", "є", "бути", "мати", "маю", "маєш", "має", "маємо", "маєте", "мають",
        "я", "ти", "він", "вона", "воно", "ми", "ви", "вони", "мене", "тебе", "його", "її", "нас", "вас", "їх",
        "мій", "твій", "його", "її", "наш", "ваш", "їхній"
    };

    const std::set<std::string> RUSSIAN_STOP_WORDS = {
        "и", "или", "но", "а", "в", "на", "за", "до", "с", "о", "для", "через", "под", "над",
        "есть", "быть", "был", "была", "было", "были", "есть", "быть", "иметь", "имею", "имеешь", "имеет", "имеем", "имеете", "имеют",
        "я", "ты", "он", "она", "оно", "мы", "вы", "они", "меня", "тебя", "его", "ее", "нас", "вас", "их",
        "мой", "твой", "его", "ее", "наш", "ваш", "их"
    };

    // Конструктор процесора
    // Processor constructor
    // Конструктор процессора
    NaturalLanguageProcessor::NaturalLanguageProcessor() {
        // Ініціалізація за замовчуванням
        // Default initialization
        // Инициализация по умолчанию
    }

    // Деструктор процесора
    // Processor destructor
    // Деструктор процессора
    NaturalLanguageProcessor::~NaturalLanguageProcessor() {
        // Очищення ресурсів
        // Resource cleanup
        // Очистка ресурсов
    }

    // Ініціалізація процесора
    // Initialize processor
    // Инициализация процессора
    bool NaturalLanguageProcessor::initialize(const NLPConfig& config) {
        configuration = config;
        
        // Ініціалізація словника для лематизації
        // Initialize dictionary for lemmatization
        // Инициализация словаря для лемматизации
        dictionary = {
            {"running", "run"}, {"ran", "run"}, {"runs", "run"},
            {"walking", "walk"}, {"walked", "walk"}, {"walks", "walk"},
            {"better", "good"}, {"best", "good"},
            {"worse", "bad"}, {"worst", "bad"}
        };
        
        // Ініціалізація правил стемінгу
        // Initialize stemming rules
        // Инициализация правил стемминга
        stemRules = {
            {"ing$", ""}, {"ed$", ""}, {"ly$", ""}, {"er$", ""}, {"est$", ""}
        };
        
        // Ініціалізація лексикону сентименту
        // Initialize sentiment lexicon
        // Инициализация лексикона сентимента
        sentimentLexicon = {
            {"good", Sentiment::POSITIVE}, {"great", Sentiment::POSITIVE}, {"excellent", Sentiment::VERY_POSITIVE},
            {"bad", Sentiment::NEGATIVE}, {"terrible", Sentiment::VERY_NEGATIVE}, {"awful", Sentiment::VERY_NEGATIVE},
            {"happy", Sentiment::POSITIVE}, {"sad", Sentiment::NEGATIVE}, {"angry", Sentiment::NEGATIVE},
            {"love", Sentiment::VERY_POSITIVE}, {"hate", Sentiment::VERY_NEGATIVE}
        };
        
        // Ініціалізація моделі перекладу
        // Initialize translation model
        // Инициализация модели перевода
        translationModel = {
            {"hello", "привіт"}, {"world", "світ"}, {"good", "добре"}, {"bad", "погано"},
            {"привет", "hello"}, {"мир", "world"}, {"хорошо", "good"}, {"плохо", "bad"}
        };
        
        // Ініціалізація профілів мов
        // Initialize language profiles
        // Инициализация профилей языков
        languageProfiles["en"] = {"the", "and", "of", "to", "a", "in", "is", "you", "that", "it"};
        languageProfiles["uk"] = {"і", "та", "в", "на", "з", "до", "як", "що", "це", "він"};
        languageProfiles["ru"] = {"и", "в", "не", "на", "я", "что", "быть", "с", "он", "этот"};
        
        return true;
    }

    // Токенізація тексту
    // Tokenize text
    // Токенизация текста
    std::vector<Token> NaturalLanguageProcessor::tokenize(const std::string& text) {
        std::vector<Token> tokens;
        
        // Попередня обробка тексту
        // Preprocess text
        // Предварительная обработка текста
        std::string processedText = preprocessText(text);
        
        // Розбиття на речення
        // Split into sentences
        // Разбиение на предложения
        std::vector<std::string> sentences = splitSentences(processedText);
        
        int position = 0;
        for (const auto& sentence : sentences) {
            // Розбиття на слова
            // Split into words
            // Разбиение на слова
            std::vector<std::string> words = splitWords(sentence);
            
            for (const auto& word : words) {
                if (!word.empty()) {
                    // Визначення частини мови
                    // Determine part of speech
                    // Определение части речи
                    PartOfSpeech pos = getPartOfSpeech(word);
                    
                    // Створення токена
                    // Create token
                    // Создание токена
                    Token token(word, pos, position++);
                    tokens.push_back(token);
                }
            }
        }
        
        return tokens;
    }

    // Лематизація тексту
    // Lemmatize text
    // Лемматизация текста
    std::string NaturalLanguageProcessor::lemmatize(const std::string& word) {
        if (!configuration.enableLemmatization) {
            return word;
        }
        
        // Перевірка в словнику
        // Check in dictionary
        // Проверка в словаре
        auto it = dictionary.find(word);
        if (it != dictionary.end()) {
            return it->second;
        }
        
        // Якщо не знайдено, повертаємо оригінальне слово
        // If not found, return original word
        // Если не найдено, возвращаем оригинальное слово
        return word;
    }

    // Стемінг тексту
    // Stem text
    // Стемминг текста
    std::string NaturalLanguageProcessor::stem(const std::string& word) {
        if (!configuration.enableStemming) {
            return word;
        }
        
        std::string stemmed = word;
        
        // Застосування правил стемінгу
        // Apply stemming rules
        // Применение правил стемминга
        for (const auto& rule : stemRules) {
            // Проста реалізація заміни закінчень
            // Simple implementation of ending replacement
            // Простая реализация замены окончаний
            if (stemmed.length() > rule.first.length()) {
                std::string ending = rule.first.substr(0, rule.first.length() - 1); // Видаляємо $
                if (stemmed.substr(stemmed.length() - ending.length()) == ending) {
                    stemmed = stemmed.substr(0, stemmed.length() - ending.length()) + rule.second;
                    break;
                }
            }
        }
        
        return stemmed;
    }

    // Визначення частин мови
    // Part of speech tagging
    // Определение частей речи
    std::vector<Token> NaturalLanguageProcessor::posTag(const std::vector<Token>& tokens) {
        if (!configuration.enablePOS) {
            return tokens;
        }
        
        std::vector<Token> taggedTokens = tokens;
        
        // Проста реалізація тегування частин мови
        // Simple implementation of part of speech tagging
        // Простая реализация тегирования частей речи
        for (auto& token : taggedTokens) {
            token.pos = getPartOfSpeech(token.text);
        }
        
        return taggedTokens;
    }

    // Аналіз сентименту
    // Sentiment analysis
    // Анализ сентимента
    SentimentResult NaturalLanguageProcessor::analyzeSentiment(const std::string& text) {
        SentimentResult result;
        
        if (!configuration.enableSentiment) {
            result.sentiment = Sentiment::NEUTRAL;
            result.confidence = 0.5;
            return result;
        }
        
        // Токенізація тексту
        // Tokenize text
        // Токенизация текста
        std::vector<Token> tokens = tokenize(text);
        
        double positiveScore = 0.0;
        double negativeScore = 0.0;
        int wordCount = 0;
        
        // Аналіз кожного токена
        // Analyze each token
        // Анализ каждого токена
        for (const auto& token : tokens) {
            auto it = sentimentLexicon.find(token.text);
            if (it != sentimentLexicon.end()) {
                wordCount++;
                switch (it->second) {
                    case Sentiment::VERY_POSITIVE:
                        positiveScore += 2.0;
                        break;
                    case Sentiment::POSITIVE:
                        positiveScore += 1.0;
                        break;
                    case Sentiment::VERY_NEGATIVE:
                        negativeScore += 2.0;
                        break;
                    case Sentiment::NEGATIVE:
                        negativeScore += 1.0;
                        break;
                    default:
                        break;
                }
            }
        }
        
        // Обчислення загального сентименту
        // Calculate overall sentiment
        // Вычисление общего сентимента
        double totalScore = positiveScore - negativeScore;
        double maxScore = wordCount * 2.0;
        
        if (maxScore > 0) {
            double normalizedScore = totalScore / maxScore;
            result.confidence = std::abs(normalizedScore);
            
            if (normalizedScore > 0.3) {
                result.sentiment = Sentiment::POSITIVE;
            } else if (normalizedScore > 0.1) {
                result.sentiment = Sentiment::NEUTRAL;
            } else if (normalizedScore > -0.1) {
                result.sentiment = Sentiment::NEUTRAL;
            } else if (normalizedScore > -0.3) {
                result.sentiment = Sentiment::NEGATIVE;
            } else {
                result.sentiment = Sentiment::VERY_NEGATIVE;
            }
        } else {
            result.sentiment = Sentiment::NEUTRAL;
            result.confidence = 0.0;
        }
        
        return result;
    }

    // Виділення іменованих сутностей
    // Named entity recognition
    // Выделение именованных сущностей
    NERResult NaturalLanguageProcessor::recognizeEntities(const std::string& text) {
        NERResult result;
        
        if (!configuration.enableNER) {
            return result;
        }
        
        // Проста реалізація виділення іменованих сутностей
        // Simple implementation of named entity recognition
        // Простая реализация выделения именованных сущностей
        std::vector<std::string> words = splitWords(preprocessText(text));
        
        for (size_t i = 0; i < words.size(); ++i) {
            const std::string& word = words[i];
            
            // Виділення імен
            // Extract names
            // Выделение имен
            if (!word.empty() && std::isupper(word[0])) {
                // Проста перевірка - якщо слово починається з великої літери, вважаємо його ім'ям
                // Simple check - if word starts with capital letter, consider it a name
                // Простая проверка - если слово начинается с заглавной буквы, считаем его именем
                NamedEntity entity(word, "PERSON", static_cast<int>(i), static_cast<int>(i + word.length()), 0.7);
                result.entities.push_back(entity);
            }
        }
        
        result.confidence = 0.7;
        return result;
    }

    // Визначення мови
    // Language detection
    // Определение языка
    LanguageProfile NaturalLanguageProcessor::detectLanguage(const std::string& text) {
        LanguageProfile profile;
        
        // Проста реалізація визначення мови
        // Simple implementation of language detection
        // Простая реализация определения языка
        std::vector<std::string> words = splitWords(preprocessText(text));
        
        std::map<std::string, int> languageScores;
        
        // Підрахунок відповідності для кожної мови
        // Count matches for each language
        // Подсчет соответствий для каждого языка
        for (const auto& langPair : languageProfiles) {
            const std::string& language = langPair.first;
            const std::vector<std::string>& commonWords = langPair.second;
            
            int score = 0;
            for (const auto& word : words) {
                for (const auto& commonWord : commonWords) {
                    if (word == commonWord) {
                        score++;
                        break;
                    }
                }
            }
            
            languageScores[language] = score;
        }
        
        // Визначення мови з найвищим балом
        // Determine language with highest score
        // Определение языка с наивысшим баллом
        std::string detectedLanguage = configuration.defaultLanguage;
        int maxScore = 0;
        
        for (const auto& scorePair : languageScores) {
            if (scorePair.second > maxScore) {
                maxScore = scorePair.second;
                detectedLanguage = scorePair.first;
            }
        }
        
        profile.language = detectedLanguage;
        profile.confidence = maxScore > 0 ? static_cast<double>(maxScore) / words.size() : 0.0;
        
        return profile;
    }

    // Переклад тексту
    // Translate text
    // Перевод текста
    std::string NaturalLanguageProcessor::translate(const std::string& text, const std::string& targetLanguage) {
        // Проста реалізація перекладу
        // Simple implementation of translation
        // Простая реализация перевода
        std::vector<std::string> words = splitWords(preprocessText(text));
        std::string translatedText;
        
        for (const auto& word : words) {
            auto it = translationModel.find(word);
            if (it != translationModel.end()) {
                translatedText += it->second + " ";
            } else {
                // Якщо переклад не знайдено, залишаємо оригінальне слово
                // If translation not found, keep original word
                // Если перевод не найден, оставляем оригинальное слово
                translatedText += word + " ";
            }
        }
        
        // Видалення зайвого пробілу в кінці
        // Remove extra space at the end
        // Удаление лишнего пробела в конце
        if (!translatedText.empty()) {
            translatedText.pop_back();
        }
        
        return translatedText;
    }

    // Виділення ключових слів
    // Extract keywords
    // Выделение ключевых слов
    std::vector<std::string> NaturalLanguageProcessor::extractKeywords(const std::string& text) {
        std::vector<std::string> keywords;
        
        // Токенізація тексту
        // Tokenize text
        // Токенизация текста
        std::vector<Token> tokens = tokenize(text);
        
        // Фільтрація стоп-слів та невеликих слів
        // Filter stop words and small words
        // Фильтрация стоп-слов и маленьких слов
        for (const auto& token : tokens) {
            if (token.text.length() > 3 && !isStopWord(token.text)) {
                // Перевірка, чи слово вже додано
                // Check if word is already added
                // Проверка, добавлено ли слово уже
                if (std::find(keywords.begin(), keywords.end(), token.text) == keywords.end()) {
                    keywords.push_back(token.text);
                }
            }
        }
        
        return keywords;
    }

    // Підсумовування тексту
    // Summarize text
    // Резюмирование текста
    std::string NaturalLanguageProcessor::summarize(const std::string& text, size_t sentenceCount) {
        // Розбиття на речення
        // Split into sentences
        // Разбиение на предложения
        std::vector<std::string> sentences = splitSentences(text);
        
        if (sentences.size() <= sentenceCount) {
            return text;
        }
        
        // Ранжування речень
        // Rank sentences
        // Ранжирование предложений
        std::vector<std::pair<std::string, double>> rankedSentences = rankSentences(sentences);
        
        // Сортування за рейтингом
        // Sort by rank
        // Сортировка по рейтингу
        std::sort(rankedSentences.begin(), rankedSentences.end(),
                  [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
                      return a.second > b.second;
                  });
        
        // Вибір найвищих речень
        // Select top sentences
        // Выбор наивысших предложений
        std::string summary;
        for (size_t i = 0; i < std::min(sentenceCount, rankedSentences.size()); ++i) {
            summary += rankedSentences[i].first + " ";
        }
        
        return summary;
    }

    // Аналіз читабельності
    // Readability analysis
    // Анализ читаемости
    double NaturalLanguageProcessor::analyzeReadability(const std::string& text) {
        // Проста реалізація аналізу читабельності
        // Simple implementation of readability analysis
        // Простая реализация анализа читаемости
        std::vector<std::string> sentences = splitSentences(text);
        std::vector<std::string> words = splitWords(preprocessText(text));
        
        if (sentences.empty() || words.empty()) {
            return 0.0;
        }
        
        // Обчислення середньої довжини речення
        // Calculate average sentence length
        // Вычисление средней длины предложения
        double avgSentenceLength = static_cast<double>(words.size()) / sentences.size();
        
        // Обчислення середньої довжини слова
        // Calculate average word length
        // Вычисление средней длины слова
        double totalWordLength = 0.0;
        for (const auto& word : words) {
            totalWordLength += word.length();
        }
        double avgWordLength = totalWordLength / words.size();
        
        // Проста формула читабельності
        // Simple readability formula
        // Простая формула читаемости
        double readability = 100.0 - (avgSentenceLength * 0.5) - (avgWordLength * 5.0);
        
        return std::max(0.0, std::min(100.0, readability));
    }

    // Отримання конфігурації
    // Get configuration
    // Получение конфигурации
    NLPConfig NaturalLanguageProcessor::getConfiguration() const {
        return configuration;
    }

    // Оновлення конфігурації
    // Update configuration
    // Обновление конфигурации
    void NaturalLanguageProcessor::updateConfiguration(const NLPConfig& config) {
        configuration = config;
    }

    // Розбиття на речення
    // Split into sentences
    // Разбиение на предложения
    std::vector<std::string> NaturalLanguageProcessor::splitSentences(const std::string& text) {
        std::vector<std::string> sentences;
        std::string sentence;
        
        for (char c : text) {
            sentence += c;
            if (c == '.' || c == '!' || c == '?') {
                if (!sentence.empty()) {
                    sentences.push_back(sentence);
                    sentence.clear();
                }
            }
        }
        
        if (!sentence.empty()) {
            sentences.push_back(sentence);
        }
        
        return sentences;
    }

    // Розбиття на слова
    // Split into words
    // Разбиение на слова
    std::vector<std::string> NaturalLanguageProcessor::splitWords(const std::string& sentence) {
        std::vector<std::string> words;
        std::string word;
        
        for (char c : sentence) {
            if (std::isspace(c) || c == ',' || c == ';' || c == ':' || c == '.' || c == '!' || c == '?') {
                if (!word.empty()) {
                    // Перетворення в нижній регістр
                    // Convert to lowercase
                    // Преобразование в нижний регистр
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    words.push_back(word);
                    word.clear();
                }
            } else if (std::isalnum(c)) {
                word += c;
            }
        }
        
        if (!word.empty()) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            words.push_back(word);
        }
        
        return words;
    }

    // Перевірка стоп-слова
    // Check stop word
    // Проверка стоп-слова
    bool NaturalLanguageProcessor::isStopWord(const std::string& word) {
        // Проста реалізація перевірки стоп-слів
        // Simple implementation of stop word checking
        // Простая реализация проверки стоп-слов
        return ENGLISH_STOP_WORDS.find(word) != ENGLISH_STOP_WORDS.end() ||
               UKRAINIAN_STOP_WORDS.find(word) != UKRAINIAN_STOP_WORDS.end() ||
               RUSSIAN_STOP_WORDS.find(word) != RUSSIAN_STOP_WORDS.end();
    }

    // Обчислення TF-IDF
    // Calculate TF-IDF
    // Вычисление TF-IDF
    double NaturalLanguageProcessor::calculateTFIDF(const std::string& word, const std::vector<std::string>& documents) {
        if (documents.empty()) {
            return 0.0;
        }
        
        // Term Frequency (TF)
        double tf = 0.0;
        for (const auto& doc : documents) {
            std::vector<std::string> words = splitWords(preprocessText(doc));
            int wordCount = std::count(words.begin(), words.end(), word);
            if (wordCount > 0) {
                tf += static_cast<double>(wordCount) / words.size();
            }
        }
        tf /= documents.size();
        
        // Inverse Document Frequency (IDF)
        int docsWithWord = 0;
        for (const auto& doc : documents) {
            std::vector<std::string> words = splitWords(preprocessText(doc));
            if (std::find(words.begin(), words.end(), word) != words.end()) {
                docsWithWord++;
            }
        }
        
        double idf = docsWithWord > 0 ? std::log(static_cast<double>(documents.size()) / docsWithWord) : 0.0;
        
        return tf * idf;
    }

    // Попередня обробка тексту
    // Preprocess text
    // Предварительная обработка текста
    std::string NaturalLanguageProcessor::preprocessText(const std::string& text) {
        std::string processed = text;
        
        // Видалення зайвих пробілів
        // Remove extra spaces
        // Удаление лишних пробелов
        processed.erase(std::remove_if(processed.begin(), processed.end(), ::isspace), processed.end());
        
        return processed;
    }

    // Визначення частини мови
    // Determine part of speech
    // Определение части речи
    PartOfSpeech NaturalLanguageProcessor::getPartOfSpeech(const std::string& word) {
        // Проста реалізація визначення частини мови
        // Simple implementation of part of speech determination
        // Простая реализация определения части речи
        
        // Списки закінчень для різних частин мови
        // Lists of endings for different parts of speech
        // Списки окончаний для разных частей речи
        const std::vector<std::string> nounEndings = {"tion", "sion", "ness", "ment", "er", "or", "ist"};
        const std::vector<std::string> verbEndings = {"ing", "ed", "ate", "ify", "ize"};
        const std::vector<std::string> adjectiveEndings = {"ful", "less", "ous", "ive", "able", "ible"};
        const std::vector<std::string> adverbEndings = {"ly"};
        
        // Перевірка закінчень
        // Check endings
        // Проверка окончаний
        for (const auto& ending : nounEndings) {
            if (word.length() >= ending.length() && 
                word.substr(word.length() - ending.length()) == ending) {
                return PartOfSpeech::NOUN;
            }
        }
        
        for (const auto& ending : verbEndings) {
            if (word.length() >= ending.length() && 
                word.substr(word.length() - ending.length()) == ending) {
                return PartOfSpeech::VERB;
            }
        }
        
        for (const auto& ending : adjectiveEndings) {
            if (word.length() >= ending.length() && 
                word.substr(word.length() - ending.length()) == ending) {
                return PartOfSpeech::ADJECTIVE;
            }
        }
        
        for (const auto& ending : adverbEndings) {
            if (word.length() >= ending.length() && 
                word.substr(word.length() - ending.length()) == ending) {
                return PartOfSpeech::ADVERB;
            }
        }
        
        // За замовчуванням вважаємо іменником
        // By default, consider as noun
        // По умолчанию считаем существительным
        return PartOfSpeech::NOUN;
    }

    // Ранжування речень
    // Rank sentences
    // Ранжирование предложений
    std::vector<std::pair<std::string, double>> NaturalLanguageProcessor::rankSentences(const std::vector<std::string>& sentences) {
        std::vector<std::pair<std::string, double>> rankedSentences;
        
        // Проста реалізація ранжування речень
        // Simple implementation of sentence ranking
        // Простая реализация ранжирования предложений
        for (const auto& sentence : sentences) {
            std::vector<std::string> words = splitWords(preprocessText(sentence));
            double score = 0.0;
            
            // Оцінка на основі довжини та ключових слів
            // Score based on length and keywords
            // Оценка на основе длины и ключевых слов
            score += words.size() * 0.1; // Довжина речення / Sentence length
            
            // Перевірка наявності ключових слів
            // Check for keywords
            // Проверка наличия ключевых слов
            for (const auto& word : words) {
                if (!isStopWord(word)) {
                    score += 0.5; // Ключове слово / Keyword
                }
            }
            
            rankedSentences.push_back({sentence, score});
        }
        
        return rankedSentences;
    }

} // namespace NLP
} // namespace NeuroSync