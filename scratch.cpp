#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>

namespace fs = std::filesystem;

void check_confidentiality(const std::string& file_path, std::map<std::string, int>& confidential_files) {
    std::string extension = fs::path(file_path).extension().string();

    // Vérifie les fichiers texte pour la confidentialité
    if (extension == ".html"  or extension == ".txt") {
        std::ifstream file_stream(file_path);
        if (file_stream.is_open()) {
            std::string first_line;
            std::getline(file_stream, first_line);
            if (first_line.find("Licence: free access") != 0) {
                confidential_files[extension]++;
            }
        }
    }
}

void analyze_folders(const std::string& directory_path) {
    /**
    * Parcourt les repertoires organises pour identifier le nombre
    de fichiers par categorie
    * ainsi que leur taille totale. Inclut une verification pour
    les fichiers texte contenant
    * la mention "Licence: free access" au debut du fichier.
    * Affiche un rapport detaille sur le contenu des dossiers
    analyses , incluant le nombre de fichiers
    * par categorie et les resultats de la verification de
    confidentialite .
    * @param directory_path Chemin du repertoire contenant les
    fichiers organises .
    */
    std::map<std::string, std::map<std::string, int>> file_counts;
    std::map<std::string, std::map<std::string, int>> confidential_files;

    for (const auto& entry : fs::recursive_directory_iterator(directory_path)) {
        if (entry.is_directory()) {
            // Uniquement les fichiers dans les sous-dossiers
            continue;
        }

        std::string file_path = entry.path().string();
        std::string subfolders = entry.path().parent_path().filename().string();
        std::string extension = entry.path().extension().string();

        file_counts[subfolders][extension]++;

        // Vérifie la confidentialité si .html ou .txt
        if (extension == ".html" or extension == ".txt") {
            check_confidentiality(file_path, confidential_files[subfolders]);
        } else {
            // Sinon le compteur de confidentialité est N/A
            confidential_files[subfolders][extension] = -1;
        }
    }

    // Affiche le rapport d'analyse
    std::cout<<"Resume par Categorie"<<std::endl;
    for (const auto& [folder, extensions] : file_counts) {
        std::cout<<"\n"<< folder<<":"<<std::endl;
        for (const auto& [extension, count] : extensions) {
            std::cout<<"- Nombre de fichiers: "<<count<<std::endl;
            if (confidential_files[folder][extension] >= 0) {
                std::cout<<"- Fichiers avec problemes de confidentialite: "<<confidential_files[folder][extension]<<std::endl;
            } else {
                std::cout<<"- Fichiers avec problemes de confidentialite: N/A"<<std::endl;
            }
        }
    }
}

int main() {
    std::string directory_path = "C:/Users/ethan/Downloads/test"; // Mettez ici le chemin absolu ou relatif du répertoire à analyser
    analyze_folders(directory_path);
    return 0;
}
