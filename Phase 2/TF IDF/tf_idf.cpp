#include "tf_idf.hpp"
#include <fstream>
#include <cmath>


std::vector<std::string> readDocument(const std::string& filePath) {
    std::vector<std::string> list;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << filePath << std::endl;
    } else {
        std::string word;
        while (file >> word) {
            // Met le mot en minuscule
            for (char& c : word) {
                c = std::tolower(c);
            }
            // Enlève les signes de ponctuation
            std::string clean_word;
            for (char c : word) {
                if (std::ispunct(c)) { // On vérifie si le caractère est un signe de ponctuation
                    // S'il est suivie d'une lettre, on ajoute le mot précédent en enlevant le signe et on commence le nouveau mot
                    if (!clean_word.empty() && std::isalpha(clean_word.back())) {
                        list.push_back(clean_word);
                        clean_word.clear();
                    }
                } else {
                    clean_word += c;
                }
            }
            // Ajoute le mot final s'il n'est pas vide
            if (!clean_word.empty()) {
                list.push_back(clean_word);
            }
        }
    }
    file.close();
    return list;
}

std::map<std::string, double> computeTF(const std::vector<std::string>& words) {
    std::map<std::string, double> TFMap;

    // Compte le nombre de fois que les mots sont présent
    std::map<std::string, int> wordCount;
    for (const auto& word : words) {
        wordCount[word]++;
    }

    // Calcule le TF
    int totalWords = words.size();
    for (auto word : wordCount) {
        TFMap[word.first] = static_cast<double>(word.second) / totalWords;
    }
    return TFMap;
}

std::map<std::string, double> computeIDF(const std::vector<std::map<std::string, double>>& documentsTF, int totalDocuments) {
    std::map<std::string, double> IDFMap;

    // Compte le nombre de documents contenant chaque mot
    std::map<std::string, int> docCount;
    for (const auto document : documentsTF) {
        for (const auto word : document) {
            if (word.second > 0) {
                docCount[word.first]++;
            }
        }
    }

    // Calcule l'IDF
    for (auto doc : docCount) {
        IDFMap[doc.first] = std::log10(static_cast<double>(totalDocuments) / doc.second);
    }
    return IDFMap;
}

std::map<std::string, double> calculateTFIDF(const std::map<std::string, double>& tf, const std::map<std::string, double>& idf) {
    std::map<std::string, double> scores;

    // Calcule le score TF-IDF
    for (auto wordTF : tf) {
        auto wordIDF = idf.find(wordTF.first);
        if (wordIDF != idf.end()) {
            scores[wordTF.first] = wordTF.second * wordIDF->second;
        }
    }
    return scores;
}

void displayTFIDFScores(const std::map<std::string, double>& tfidfScores) {
    // Affiche les scores TF-IDF
    for (const auto TFIDF : tfidfScores) {
        std::cout << TFIDF.first << " : " << TFIDF.second << std::endl;
    }
}

int main() {
   return 0;
}