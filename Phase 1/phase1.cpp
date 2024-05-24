#include "phase1.hpp"
#include <filesystem>
#include <fstream>


void check_confidentiality(const std::string& file_path, std::vector<std::pair<std::string, int>>& confidential_files) {
    std::string extension = std::filesystem::path(file_path).extension().string();

    // Vérifation de la confidentialité pours les .html et .txt
    std::ifstream file_stream(file_path);
    if (file_stream.is_open()) {
        std::string first_line;
        std::getline(file_stream, first_line);
        if (first_line.find("Licence: free access") != 0) {
            bool found = false;
            for(auto& pair : confidential_files) {
                if(pair.first == extension) {
                    pair.second++;
                    found = true;
                    break;
                }
            }
            if(!found) {
                confidential_files.emplace_back(extension, 1);
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
    std::vector<std::pair<std::string, std::vector<std::pair<std::string, int>>>> file_counts;
    std::vector<std::pair<std::string, std::vector<std::pair<std::string, int>>>> confidential_files;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory_path)) {
        if (entry.is_directory()) {
            // Juste les fichiers dans les sous-dossiers
            continue;
        }

        std::string file_path = entry.path().string();
        std::string subfolders = entry.path().parent_path().filename().string();
        std::string extension = entry.path().extension().string();

        bool find = false;
        for(auto& folder : file_counts) {
            if(folder.first == subfolders) {
                bool found_ext = false;
                for(auto& pair : folder.second) {
                    if(pair.first == extension) {
                        pair.second++;
                        found_ext = true;
                        break;
                    }
                }
                if(!found_ext) {
                    folder.second.emplace_back(extension, 1);
                }
                find = true;
                break;
            }
        }
        if(!find) {
            file_counts.emplace_back(subfolders, std::vector<std::pair<std::string, int>>{{extension, 1}});
        }

        // Vérifie la confidentialité si .html ou .txt
        if (extension == ".html" || extension == ".txt") {
            find = false;
            for(auto& folder : confidential_files) {
                if(folder.first == subfolders) {
                    check_confidentiality(file_path, folder.second);
                    find = true;
                    break;
                }
            }
            if(!find) {
                std::vector<std::pair<std::string, int>> vec;
                check_confidentiality(file_path, vec);
                confidential_files.emplace_back(subfolders, vec);
            }
        } else {
            // Sinon le compteur de confidentialité est N/A
            bool found = false;
            for(auto& folder : confidential_files) {
                if(folder.first == subfolders) {
                    folder.second.emplace_back(extension, -1);
                    found = true;
                    break;
                }
            }
            if(!found) {
                confidential_files.emplace_back(subfolders, std::vector<std::pair<std::string, int>>{{extension, -1}});
            }
        }
    }

    // Affichage du rapport d’Analyse
    std::cout<<"Resume par Categorie"<<std::endl;
    for (const auto& folder : file_counts) {
        std::cout<<"\n"<<folder.first<<":"<<std::endl;
        for (const auto& pair : folder.second) {
            std::cout<<"- Nombre de fichiers: "<<pair.second<<std::endl;
            bool found = false;
            for(const auto& confidential_folder : confidential_files) {
                if(confidential_folder.first == folder.first) {
                    for(const auto& confidential_pair : confidential_folder.second) {
                        if(confidential_pair.first == pair.first) {
                            if(confidential_pair.second >= 0) {
                                std::cout<<"- Fichiers avec problemes de confidentialite: ";
                                if(confidential_pair.second == 0) {
                                    std::cout<<"0"<<std::endl;
                                } else {
                                    std::cout<<confidential_pair.second<<std::endl;
                                }
                            } else {
                                std::cout<<"- Fichiers avec problemes de confidentialite: N/A"<<std::endl;
                            }
                            found = true;
                            break;
                        }
                    }
                    break;
                }
            }
            if(!found) {
                std::cout<<"- Fichiers avec problemes de confidentialite: 0"<<std::endl;
            }
        }
    }
}

int main() {
    return 0;
}
