#include "analyse_sentiments.hpp"
#include <fstream>


void loadSentimentDictionary(SentimentDictionary& dictionary, const std::string& positivePath, const std::string& negativePath) {
    std::ifstream positiveFile(positivePath);
    if (!positiveFile.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier des mots positifs." << std::endl;
    } else {
        std::string word;
        while (positiveFile >> word) {
            dictionary.positiveWords.push_back(word);
        }
        positiveFile.close();
    } 

    std::ifstream negativeFile(negativePath);
    if (!negativeFile.is_open()) {
         std::cerr << "Impossible d'ouvrir le fichier des mots negatifs." << std::endl;
    } else {
        std::string word;
        while (negativeFile >> word) {
            dictionary.negativeWords.push_back(word);
        }
        negativeFile.close();
    }
}

std::string clean_word(std::string word){
        for (char& c : word) {
            c = std::tolower(c);
        }
        // Enlève les signes de ponctuation
        std::string clean_word;
        for (char& c : word) {
            if (std::isalnum(c)) { // Vérifie si le caractère est une lettre ou un chiffre
                clean_word += c;
            }
        }
    return clean_word;
}

AnalysisResult analyzeSentiment(const SentimentDictionary& dictionary, const std::string& filePath) {
    AnalysisResult result;
    result.positiveCount = 0;
    result.negativeCount = 0;

    std::ifstream file(filePath);
    if (!file.is_open()){
        std::cerr << "Le fichier n'a pas pu etre ouvert." << std::endl;
    } else {
        std::string word;
        while (file >> word) {
            word = clean_word(word);
            std::cout << word << std::endl;
            for (const auto &posWord : dictionary.positiveWords) {
                if (posWord == word) {
                    result.positiveCount++;
                    break;
                }
            }
            for (const auto &negWord : dictionary.negativeWords) {
                if (negWord == word) {
                    result.negativeCount++;
                    break;
                }
            }
        }
        file.close();

        // Détermine si le texte est positif, negatif ou neutre
        if (result.positiveCount > result.negativeCount) {
            result.overallSentiment = "Positif";
        } else if (result.positiveCount < result.negativeCount) {
            result.overallSentiment = "Negatif";
        } else {
            result.overallSentiment = "Neutre";
        }
    }
    return result;
}

int main(){
    return 0;
}