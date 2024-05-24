#include "analyse_sentiments.hpp"
#include <fstream>


void SentimentDictionary::load(const std::string& positivePath, const std::string& negativePath) {
    std::ifstream positiveFile(positivePath);
    if (!positiveFile.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier " + positivePath + " des mots positifs.");
    } else {
        std::string word;
        // Ajoute le mot tant qu'il y a un mot 
        while (positiveFile >> word) {
            positiveWords.push_back(word);
        }
        positiveFile.close();
    }

    std::ifstream negativeFile(negativePath);
    if (!negativeFile.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier " + negativePath + " des mots négatifs.");
    } else {
        std::string word;
        // Ajoute le mot tant qu'il y a un mot 
        while (negativeFile >> word) {
            negativeWords.push_back(word);
        }
        negativeFile.close();
    }
}

bool SentimentDictionary::isPositive(const std::string& word) const {
    for (const auto& positiveWord : positiveWords) {
        if (positiveWord == word) {
            return true;
        }
    }
    return false;
}

bool SentimentDictionary::isNegative(const std::string& word) const {
    for (const auto& negativeWord : negativeWords) {
        if (negativeWord == word) {
            return true;
        }
    }
    return false;
}


AnalysisResult::AnalysisResult() : positiveCount(0), negativeCount(0) {}

void AnalysisResult::incrementPositiveCount() {
    positiveCount++;
}

void AnalysisResult::incrementNegativeCount() {
    negativeCount++;
}

std::string AnalysisResult::getOverallSentiment() const {
    /*
    Détermine si le texte est positif, negatif ou neutre
    */

    if (positiveCount > negativeCount) {
        return "Positif";
    } else if (positiveCount < negativeCount) {
        return "Negatif";
    } else {
        return "Neutre";
    }
}


AnalysisResult SentimentAnalyzer::analyze(const SentimentDictionary& dictionary, const std::string& filePath) const {
    AnalysisResult result;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Le fichier " << filePath << " n'a pas pu etre ouvert." << std::endl;
        return result;
    }

    std::string word;
    // Tant qu'il y a un mot, on vérifie s'il est dans le dicionnaire et on met à jour 
    // le comptage des mots positifs et négatifs
    while (file >> word) {
        word = cleanWord(word);
        if (dictionary.isPositive(word)) {
            result.incrementPositiveCount();
        }
        if (dictionary.isNegative(word)) {
            result.incrementNegativeCount();
        }
    }

    file.close();
    return result;
}

std::string SentimentAnalyzer::cleanWord(const std::string& word) const {
    /*
    Fonction qui prend un mot de type string en paramètre, le met en minuscule et enlève les signes de ponctuations.
    */
    std::string cleanedWord;
    for (char c : word) {
        if (std::isalnum(c)) { // Vérifie si le caractère est une lettre ou un chiffre
            cleanedWord += std::tolower(c);
        }
    }
    return cleanedWord;
}

int main() {
    return 0;
}