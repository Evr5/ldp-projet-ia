import zipfile
import os

def decompress_archive ( zip_path : str , extract_to : str ) -> None :
    """
    Decompresse l’archive ZIP specifiee dans le chemin zip_path
    vers le repertoire extract_to.
    : param zip_path : Chemin vers le fichier ZIP a decompresser
    : param extract_to : Repertoire de destination pour les fichiers
    extraits.
    """
    with zipfile.ZipFile(zip_path, 'r') as zip:
        zip.extractall(extract_to)


def organize_files ( directory : str ) -> None :
    """
    Organise les fichiers dans le repertoire specifie en les
    classant dans des sous - dossiers selon leur type.
    : param directory : Chemin du repertoire contenant les fichiers a
    organiser.
    """
    # Dictionnaire des extensions avec leurs types de dossiers
    file_types = {".html": "HTML", ".txt": "Textes", ".mp3": "Audio", ".jpg": "Images", ".png": "Images", ".mp4": "Videos", ".pdf": "Documents"}
    for file in os.listdir(directory):
        file_path = os.path.join(directory, file)
        _, extension = os.path.splitext(file)   # Récupère l'extension du fichier
        if extension in file_types:
            folder = os.path.join(directory, file_types[extension]) # Création du dossier
            if not os.path.exists(folder):
                os.makedirs(folder)
            os.rename(file_path, os.path.join(folder, file))    # Déplace le fichier dans le dossier


organize_files("C:/Users/ethan/Downloads/test")
