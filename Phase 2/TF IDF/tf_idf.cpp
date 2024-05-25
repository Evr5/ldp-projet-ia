#include "tf_idf.hpp"
#include <fstream>
#include <cmath>


std::vector<std::string> readDocument(const std::string& filePath) {
    std::vector<std::string> list;
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        throw std::runtime_error( "Impossible d'ouvrir le fichier " + filePath);
    } else {
        std::string word;
        while (file >> word) {
            // Met le mot en minuscule
            for (char& c : word) {
                c = std::tolower(c);
            }
            // Nettoie le mot et ajoute les mots résultants à la liste
            std::vector<std::string> cleanedWords = cleanWord(word);
            list.insert(list.end(), cleanedWords.begin(), cleanedWords.end());
        }
    }
    file.close();
    return list;
}

std::vector<std::string> cleanWord(const std::string& word) {
    // Enlève les signes de ponctuation
    std::vector<std::string> cleanedWords;
    std::string clean_word;
    for (char c : word) {
        if (std::ispunct(c)) { // On vérifie si le caractère est un signe de ponctuation
            // S'il est suivi d'une lettre, on ajoute le mot précédent en enlevant le signe et on commence le nouveau mot
            if (!clean_word.empty() && std::isalpha(clean_word.back())) {
                cleanedWords.push_back(clean_word);
                clean_word.clear();
            }
        } else {
            clean_word += c;
        }
    }
    // Ajoute le mot final s'il n'est pas vide
    if (!clean_word.empty()) {
        cleanedWords.push_back(clean_word);
    }
    return cleanedWords;
}


std::map<std::string, double> computeTF(const std::vector<std::string>& words) {
    std::map<std::string, double> TF_map;

    // Compte le nombre de fois que les mots sont présent
    std::map<std::string, int> word_count;
    for (const auto& word : words) {
        word_count[word]++;
    }

    // Calcule le TF
    int total_words = words.size();
    for (auto word : word_count) {
        TF_map[word.first] = static_cast<double>(word.second) / total_words;
    }
    return TF_map;
}

std::map<std::string, double> computeIDF(const std::vector<std::map<std::string, double>>& documentsTF, int totalDocuments) {
    std::map<std::string, double> IDF_map;

    // Compte le nombre de documents contenant chaque mot
    std::map<std::string, int> doc_count;
    for (const auto& document : documentsTF) {
        for (const auto& word : document) {
            if (word.second > 0) {
                doc_count[word.first]++;
            }
        }
    }

    // Calcule l'IDF
    for (auto doc : doc_count) {
        IDF_map[doc.first] = std::log10(static_cast<double>(totalDocuments) / doc.second);
    }
    return IDF_map;
}

std::map<std::string, double> calculateTFIDF(const std::map<std::string, double>& tf, const std::map<std::string, double>& idf) {
    std::map<std::string, double> scores;

    // Calcule le score TF-IDF
    for (auto word_TF : tf) {
        auto word_IDF = idf.find(word_TF.first);
        if (word_IDF != idf.end()) {
            scores[word_TF.first] = word_TF.second * word_IDF->second;
        }
    }
    return scores;
}

void displayTFIDFScores(const std::map<std::string, double>& tfidfScores) {
    // Affiche les scores TF-IDF
    for (const auto& TFIDF : tfidfScores) {
        std::cout << TFIDF.first << " : " << TFIDF.second << std::endl;
    }
}

int main() {
    return 0;
}