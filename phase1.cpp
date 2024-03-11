#include <string >
#include <filesystem >
#include <iostream>

namespace fs = std:: filesystem;

void analyze_folders(const std:: string& directory_path) {
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

    for (const auto& entry : fs::directory_iterator(directory_path)) {
        if (fs::is_regular_file(entry)) {
            // Obtenir l'extension du fichier
            std::string extension = entry.path().extension().string();
            // Supprimer le point de l'extension
            if (!extension.empty() && extension[0] == '.')
                extension = extension.substr(1);
            // Ajouter l'extension à l'ensemble
            extension.insert(extension);
        }
    }

}

int main(){
    const std::string directory_path = "C:/Users/ethan/Downloads/test";
    analyze_folders(directory_path);
    return 0;
}