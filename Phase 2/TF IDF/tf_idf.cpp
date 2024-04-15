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

int main(){
    return 0;
}