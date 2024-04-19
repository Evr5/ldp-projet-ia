#include "tf_idf.hpp"
#include <fstream>
#include <cmath>


std::vector<std::string> readDocument(const std::string& filePath) {
    std::vector<std::string> table;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << filePath << std::endl;
    } else {
        std::string word;
        while (file >> word) {
            // Convertit le mot en minuscules
            for (char& c : word) {
                c = std::tolower(c);
            }
            // Enlève les signes de ponctuation
            std::string clean_word;
            for (char c : word) {
                if (std::isalnum(c)) { // Vérifie si le caractère est une lettre ou un chiffre
                    clean_word += c;
                } else if (std::ispunct(c)) { // Vérifie si le caractère est un signe de ponctuation
                    // Si le signe de ponctuation est suivie d'une lettre, ajoute le mot précédent et commence un nouveau mot
                    if (!clean_word.empty() && std::isalpha(clean_word.back())) {
                        table.push_back(clean_word);
                        clean_word.clear();
                    }
                }
            }
            // Ajoute le mot final s'il n'est pas vide
            if (!clean_word.empty()) {
                table.push_back(clean_word);
            }
        }
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
    for (auto doc : docCount) {
        idfMap[doc.first] = std::log10(static_cast<double>(totalDocuments) / doc.second);
    }
    return idfMap;
}

std::map<std::string, double> calculateTFIDF(const std::map<std::string, double>& tf, const std::map<std::string, double>& idf) {
    std::map<std::string, double> tfidfScores;

    // Calculer le score TF-IDF pour chaque mot
    for (auto t : tf) {
        auto it = idf.find(t.first);
        if (it != idf.end()) {
            tfidfScores[t.first] = t.second * it->second;
        }
    }
    return tfidfScores;
}

void displayTFIDFScores(const std::map<std::string, double>& tfidfScores) {
    // Affiche les scores TF-IDF pour chaque mot
    for (auto tfidf : tfidfScores) {
        std::cout << tfidf.first << " : " << tfidf.second << std::endl;
    }
}

int main() {
    std::string filePath = "ethan.txt";
    std::vector<std::string> mots = readDocument(filePath);
    
    // Affichage du contenu du vecteur
    std::cout << "Contenu du vecteur :" << std::endl;
    for (const std::string& mot : mots) {
        std::cout << mot << std::endl;
    }
    return 0;
}