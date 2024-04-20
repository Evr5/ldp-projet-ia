#include "analyse_sentiments.hpp"
#include <fstream>


void loadSentimentDictionary(SentimentDictionary& dictionary, const std::string& positivePath, const std::string& negativePath) {
    std::ifstream positiveFile(positivePath);

    if (!positiveFile.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier " << positivePath << " des mots positifs." << std::endl;
    } else {
        std::string word;
        // Ajoute le mot au dictionnaire tant qu'il y a un mot 
        while (positiveFile >> word) {
            dictionary.positiveWords.push_back(word);
        }
        positiveFile.close();
    } 

    std::ifstream negativeFile(negativePath);
    if (!negativeFile.is_open()) {
         std::cerr << "Impossible d'ouvrir le fichier " << negativePath << " des mots negatifs." << std::endl;
    } else {
        std::string word;
        // Ajoute le mot au dictionnaire tant qu'il y a un mot
        while (negativeFile >> word) {
            dictionary.negativeWords.push_back(word);
        }
        negativeFile.close();
    }
}

std::string clean_word(std::string word){
    /*
    Fonction qui prend un mot de type string en paramètre, le met en minuscule et enlève les signes de ponctuations.
    */
        for (char& c : word) {
            c = std::tolower(c);
        }
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
        std::cerr << "Le fichier " << filePath << " n'a pas pu etre ouvert." << std::endl;
    } else {
        std::string word;
        // Tant qu'il y a un mot, on vérifie s'il est dans le dicionnaire et om met à jour 
        // le comptage des mots positifs et négatifs
        while (file >> word) {
            word = clean_word(word);
            for (const auto &positiveWord : dictionary.positiveWords) {
                if (positiveWord == word) {
                    result.positiveCount++;
                }
            }
            for (const auto &negativeWord : dictionary.negativeWords) {
                if (negativeWord == word) {
                    result.negativeCount++;
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

int main() {
    return 0;
}
