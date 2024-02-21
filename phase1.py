import zipfile
import os

def decompress_archive ( zip_path : str , extract_to : str ) -> None :
    """
    Decompresse l ’ archive ZIP specifiee dans le chemin zip_path
    vers le repertoire extract_to .
    : param zip_path : Chemin vers le fichier ZIP a decompresser
    : param extract_to : Repertoire de destination pour les fichiers
    extraits .
    """
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(extract_to)


def organize_files ( directory : str ) -> None :
    """
    Organise les fichiers dans le repertoire specifie en les
    classant dans des sous - dossiers selon leur type .
    : param directory : Chemin du repertoire contenant les fichiers a
    organiser .
    """
    # Dictionnaire des extensions de fichiers et de leurs catégories correspondantes
    file_types = {
        ".html": "HTML",
        ".txt": "Textes",
        ".mp3": "Audio",
        ".wav": "Audio",
        ".jpg": "Images",
        ".png": "Images"
    }

    # Parcourt tous les fichiers du répertoire
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        # Vérifie si le chemin est un fichier
        if os.path.isfile(file_path):
            # Récupère l'extension du fichier
            _, extension = os.path.splitext(filename)
            # Vérifie si l'extension est répertoriée dans le dictionnaire
            if extension in file_types:
                # Crée le dossier correspondant au type de fichier s'il n'existe pas encore
                folder_path = os.path.join(directory, file_types[extension])
                if not os.path.exists(folder_path):
                    os.makedirs(folder_path)
                # Déplace le fichier vers le dossier correspondant
                os.rename(file_path, os.path.join(folder_path, filename))


# Exemple d'utilisation
if __name__ == "__main__":
    # Décompresser l'archive
    decompress_archive("C:/Users\ethan\Downloads/phase1_resources.zip", "C:/Users\ethan\Downloads/test")

    # Organiser les fichiers
    organize_files("C:/Users\ethan\Downloads/test")