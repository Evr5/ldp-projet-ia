#include "tf_idf.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>


std::vector<std::string> readDocument(const std::string& filePath) {
    std::vector<std::string> table;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filePath << std::endl;
        return table;
    }

    std::locale loc;
    std::string word;
    while (file >> word) {
        // Convertit le mot en minuscules
        for (char& c : word) {
            c = std::tolower(c, loc);
        }
        // Enlève les signes de ponctuation
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) { return std::ispunct(c); }), word.end());
        table.push_back(word);
    }

    file.close();
    return table;
}

std::map<std::string, double> computeTF(const std::vector<std::string>& words) {
    std::map<std::string, double> tfMap;

    // Compte le nombre d'occurrences de chaque mot
    std::map<std::string, int> wordCount;
    for (const auto& word : words) {
        wordCount[word]++;
    }

    // Calcule la fréquence de chaque mot
    int totalWords = words.size();
    for (auto count : wordCount) {
        tfMap[count.first] = static_cast<double>(count.second) / totalWords;
    }

    return tfMap;
}

std::map<std::string, double> computeIDF(const std::vector<std::map<std::string, double>>& documentsTF, int totalDocuments) {
    std::map<std::string, double> idfMap;

    // Compter le nombre de documents contenant chaque mot
    std::map<std::string, int> docCount;
    for (auto document : documentsTF) {
        for (auto pair : document) {
            if (pair.second > 0) {
                docCount[pair.first]++;
            }
        }
    }

    // Calculer l'IDF pour chaque mot
    for (auto pair : docCount) {
        idfMap[pair.first] = std::log10(static_cast<double>(totalDocuments) / pair.second);
    }

    return idfMap;
}

std::map<std::string, double> calculateTFIDF(const std::map<std::string, double>& tf, const std::map<std::string, double>& idf) {
    std::map<std::string, double> tfidfScores;

    // Calculer le score TF-IDF pour chaque mot
    for (auto pair : tf) {
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
    // Affiche les scores TF-IDF pour chaque mot
    for (auto pair : tfidfScores) {
        std::cout << "Mot : " << pair.first << ", Score TF-IDF : " << pair.second << std::endl;
    }
}

int main(){
    std::vector<std::string> words = readDocument("medecine_1.txt");

    std::map<std::string, double> TF = computeTF(words);

    // Affichage des résultats
    std::cout << "Frequence des mots :\n";
    for (const auto& pair : TF) {
        std::cout << pair.first << " : " << pair.second << '\n';
    }

    return 0;
}