#include <iostream>
#include <string>

int main() {
    // Déclaration d'une chaîne de caractères
    std::string str = "Hello, world!";

    // Affichage de la chaîne de caractères
    std::cout << "Contenu de la chaine : " << str << std::endl;

    // Modification de la chaîne de caractères
    str += " Welcome to C++!";
    
    // Affichage de la chaîne de caractères modifiée
    std::cout << "Nouveau contenu de la chaine : " << str << std::endl;

    return 0;
}
