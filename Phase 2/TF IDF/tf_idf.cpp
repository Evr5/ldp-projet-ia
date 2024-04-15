#include "tf_idf.hpp"
#include <fstream>
#include <iostream>
#include <cmath>


std::vector<std::string> readDocument(const std::string& filePath) {
    std::vector<std::string> words;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filePath << std::endl;
        return words;
    }

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    file.close();
    return words;
}

std::map<std::string, double> computeTF(const std::vector<std::string>& words) {
    std::map<std::string, double> tfMap;

    // Compter le nombre d'occurrences de chaque mot
    std::map<std::string, int> wordCount;
    for (const auto& word : words) {
        wordCount[word]++;
    }

    // Calculer la fréquence de chaque mot
    int totalWords = words.size();
    for (const auto& pair : wordCount) {
        tfMap[pair.first] = static_cast<double>(pair.second) / totalWords;
    }

    return tfMap;
}

std::map<std::string, double> computeIDF(const std::vector<std::map<std::string, double>>& documentsTF, int totalDocuments) {
    std::map<std::string, double> idfMap;

    // Compter le nombre de documents contenant chaque mot
    std::map<std::string, int> docCount;
    for (const auto& document : documentsTF) {
        for (const auto& pair : document) {
            if (pair.second > 0) {
                docCount[pair.first]++;
            }
        }
    }

    // Calculer l'IDF pour chaque mot
    for (const auto& pair : docCount) {
        idfMap[pair.first] = std::log10(static_cast<double>(totalDocuments) / pair.second);
    }

    return idfMap;
}

std::map<std::string, double> calculateTFIDF(const std::map<std::string, double>& tf, const std::map<std::string, double>& idf) {
    std::map<std::string, double> tfidfScores;

    // Calculer le score TF-IDF pour chaque mot
    for (const auto& pair : tf) {
        auto it = idf.find(pair.first);
        if (it != idf.end()) {
            tfidfScores[pair.first] = pair.second * it->second;
        } else {
            std::cerr << "Erreur: IDF non trouvé pour le mot " << pair.first << std::endl;
        }
    }

    return tfidfScores;
}

void displayTFIDFScores(const std::map<std::string, double>& tfidfScores) {
    // Afficher les scores TF-IDF pour chaque mot
    for (const auto& pair : tfidfScores) {
        std::cout << "Mot : " << pair.first << ", Score TF-IDF : " << pair.second << std::endl;
    }
}

struct SentimentDictionary {
    std::vector<std::string> positiveWords;
    std::vector<std::string> negativeWords;
};

void loadSentimentDictionary(SentimentDictionary& dictionary, const std::string& positivePath, const std::string& negativePath) {
    // Charger les mots-clés associés aux sentiments positifs
    std::ifstream positiveFile(positivePath);
    if (positiveFile.is_open()) {
        std::string word;
        while (std::getline(positiveFile, word)) {
            dictionary.positiveWords.push_back(word);
        }
        positiveFile.close();
    } else {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << positivePath << " pour les mots-clés positifs." << std::endl;
    }

    // Charger les mots-clés associés aux sentiments négatifs
    std::ifstream negativeFile(negativePath);
    if (negativeFile.is_open()) {
        std::string word;
        while (std::getline(negativeFile, word)) {
            dictionary.negativeWords.push_back(word);
        }
        negativeFile.close();
    } else {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << negativePath << " pour les mots-clés négatifs." << std::endl;
    }
}

struct AnalysisResult {
    int positiveCount;
    int negativeCount;
    std::string overallSentiment;
};

AnalysisResult analyzeSentiment(const SentimentDictionary& dictionary, const std::string& filePath) {
    AnalysisResult result;
    result.positiveCount = 0;
    result.negativeCount = 0;

    // Ouvrir le fichier texte
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filePath << std::endl;
        result.overallSentiment = "Neutre"; // Retourner neutre en cas d'erreur
        return result;
    }

    // Lire chaque mot du fichier et vérifier s'il est présent dans les listes de mots-clés positifs et négatifs
    std::string word;
    while (file >> word) {
        for (const auto& positiveWord : dictionary.positiveWords) {
            if (word == positiveWord) {
                result.positiveCount++;
                break;
            }
        }
        for (const auto& negativeWord : dictionary.negativeWords) {
            if (word == negativeWord) {
                result.negativeCount++;
                break;
            }
        }
    }

    file.close();

    // Déterminer le sentiment global en fonction des nombres de mots positifs et négatifs
    if (result.positiveCount > result.negativeCount) {
        result.overallSentiment = "Positif";
    } else if (result.negativeCount > result.positiveCount) {
        result.overallSentiment = "Négatif";
    } else {
        result.overallSentiment = "Neutre";
    }

    return result;
}

int main(){
    return 0;
}