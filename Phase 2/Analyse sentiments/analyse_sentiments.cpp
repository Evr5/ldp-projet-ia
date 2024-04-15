#include "analyse_sentiments.hpp"
#include <fstream>

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