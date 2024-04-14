#include "tf_idf.hpp"
#include <vector>
#include <fstream>
#include <iostream>

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