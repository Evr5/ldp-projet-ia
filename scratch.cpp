#include <iostream>
#include <filesystem>
#include <set> // Utilisé pour stocker les extensions uniques

namespace fs = std::filesystem;

int main() {
    fs::path directoryPath = "C:/Users/ethan/Downloads/test"; // Remplacez cela par votre chemin de répertoire
    std::set<std::string> extensions; // Utilisation d'un ensemble pour stocker les extensions uniques

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            // Obtenir l'extension du fichier
            std::string extension = entry.path().extension().string();
            // Supprimer le point de l'extension
            if (!extension.empty() && extension[0] == '.')
                extension = extension.substr(1);
            // Ajouter l'extension à l'ensemble
            extensions.insert(extension);
        }

    }

    // Affichage des extensions uniques
    std::cout << "Extensions presentes dans le repertoire : " << std::endl;
    for (const auto& ext : extensions) {
        std::cout << ext << std::endl;
    }

    return 0;
}
