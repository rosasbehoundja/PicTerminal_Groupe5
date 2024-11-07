#include "Administrateur.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <filesystem>

using namespace std;

//  :) Constructeurs

Administrateur::Administrateur() :Utilisateur()
{

}
Administrateur::Administrateur(string name, string email, string password)
    : Utilisateur(to_string(getNextId()), name, email, password, true)
{

}

// :) Destructeur
Administrateur::~Administrateur()
{

}

// :)Autres Methodes
void Administrateur::approuverImage() 
{
    int imageId;
    cout << "Entrez l'ID de l'image à approuver : ";
    cin >> imageId;

    ifstream fichierImages("./data/images.csv");
    ofstream fichierTemp("./data/temp.csv");

    if (fichierImages.is_open() && fichierTemp.is_open()) {
        string id, nom, titre, description, nbrTelechargement, idCategorie, proprietaire, statut;
        bool trouve = false;

    while (fichierImages.peek()!= EOF)
        {
            getline(fichierImages, id, ',');
            getline(fichierImages, nom, ',');
            getline(fichierImages, titre, ',');
            getline(fichierImages, description, ',');
            getline(fichierImages, nbrTelechargement, ',');
            getline(fichierImages, idCategorie, ',');
            getline(fichierImages, proprietaire, ',');
            getline(fichierImages, statut, '\n');

            if (id == to_string(imageId)) {
                fichierTemp << id << "," << nom << "," << titre << "," << description << "," << nbrTelechargement << "," << idCategorie << "," << proprietaire << ",1" << endl;
                cout << "L'image '" << titre << "' a été approuvée." << endl;
                trouve = true;
            } else {
                fichierTemp << id << "," << nom << "," << titre << "," << description << "," << nbrTelechargement << "," << idCategorie << "," << proprietaire << "," << statut << endl;
            }
        }

        if (!trouve) {
            cout << "Image introuvable." << endl;
        }
    } else {
        cout << "Erreur lors de l'ouverture des fichiers." << endl;
    }

    fichierImages.close();
    fichierTemp.close();

    filesystem::remove("./data/images.csv");
    filesystem::rename("./data/temp.csv", "./data/images.csv");
}
void Administrateur::rejeterimage() 
{
    int imageId;
    cout << "Entrez l'ID de l'image à rejeter : ";
    cin >> imageId;

    ifstream fichierImages("./data/images.csv");
    ofstream fichierTemp("./data/temp.csv");

    if (fichierImages.is_open() && fichierTemp.is_open()) {
        string ligne, id, nom, titre, description, nbrTelechargement, idCategorie, proprietaire, statut;
        bool trouve = false;

    while (fichierImages.peek()!= EOF)
        {
            getline(fichierImages, id, ',');
            getline(fichierImages, nom, ',');
            getline(fichierImages, titre, ',');
            getline(fichierImages, description, ',');
            getline(fichierImages, nbrTelechargement, ',');
            getline(fichierImages, idCategorie, ',');
            getline(fichierImages, proprietaire, ',');
            getline(fichierImages, statut, '\n');

            if (id == to_string(imageId)) {
                fichierTemp << id << "," << nom << "," << titre << "," << description << "," << nbrTelechargement << "," << idCategorie << "," << proprietaire << ",0" << endl;
                cout << "L'image '" << titre << "' a été rejetée." << endl;
                trouve = true;
            } else {
                fichierTemp << id << "," << nom << "," << titre << "," << description << "," << nbrTelechargement << "," << idCategorie << "," << proprietaire << "," << statut << endl;
            }
        }
        if (!trouve) {
            cout << "Image introuvable." << endl;
        }
    } else {
        cout << "Erreur lors de l'ouverture des fichiers." << endl;
    }

    fichierImages.close();
    fichierTemp.close();

    filesystem::remove("./data/images.csv");
    filesystem::rename("./data/temp.csv", "./data/images.csv");
}

void Administrateur::afficherStatistiques() {

    int totalImages = 0;
    ifstream fichierImages("./data/images.csv");
    string ligne, id, nom, titre, description, nbrTelechargement, idCategorie, proprietaire, statut;
    if (fichierImages.is_open()) {
        while (getline(fichierImages, ligne)) {
            totalImages++;
        }
    }
    fichierImages.close();
    cout << "Nombre total d'images téléchargées : " << totalImages << endl;

    // Images les plus telechargees
    vector<pair<int, string>> imagesPopulaires;
    fichierImages.open("./data/images.csv");
    if (fichierImages.is_open()) {
        getline(fichierImages, ligne); 
        while (fichierImages.peek()!= EOF)
        {
            getline(fichierImages, id, ',');
            getline(fichierImages, nom, ',');
            getline(fichierImages, titre, ',');
            getline(fichierImages, description, ',');
            getline(fichierImages, nbrTelechargement, ',');
            getline(fichierImages, idCategorie, ',');
            getline(fichierImages, proprietaire, ',');
            getline(fichierImages, statut, '\n');

            imagesPopulaires.emplace_back(stoi(nbrTelechargement), titre);
        }
    }
    fichierImages.close();
    sort(imagesPopulaires.begin(), imagesPopulaires.end(), greater<pair<int, string>>());
    cout << "Images les plus populaires :" << endl;
    for (const auto& [nbrTelechargement, titre] : imagesPopulaires) {
        cout << "- " << titre << " (" << nbrTelechargement << " téléchargements)" << endl;
    }

    // Images par Categories
    map<string, int> imagesParCategorie;
    fichierImages.open("./data/images.csv");
    if (fichierImages.is_open()) {
        getline(fichierImages, ligne); 
    while (fichierImages.peek()!= EOF)
        {
            getline(fichierImages, id, ',');
            getline(fichierImages, nom, ',');
            getline(fichierImages, titre, ',');
            getline(fichierImages, description, ',');
            getline(fichierImages, nbrTelechargement, ',');
            getline(fichierImages, idCategorie, ',');
            getline(fichierImages, proprietaire, ',');
            getline(fichierImages, statut, '\n');

            imagesParCategorie[idCategorie]++;
        }
    }
    fichierImages.close();
    cout << "Nombre d'images par catégorie :" << endl;
    for (const auto& [categorie, nbr] : imagesParCategorie) {
        cout << "- Catégorie " << categorie << " : " << nbr << " images" << endl;
    }

    // Activité des utilisateurs
    map<string, int> imagesParUtilisateur;
    fichierImages.open("./data/images.csv");
    if (fichierImages.is_open()) {
        getline(fichierImages, ligne); 
    while (fichierImages.peek()!= EOF)
        {
            getline(fichierImages, id, ',');
            getline(fichierImages, nom, ',');
            getline(fichierImages, titre, ',');
            getline(fichierImages, description, ',');
            getline(fichierImages, nbrTelechargement, ',');
            getline(fichierImages, idCategorie, ',');
            getline(fichierImages, proprietaire, ',');
            getline(fichierImages, statut, '\n');
            imagesParUtilisateur[proprietaire]++;
        }
    }
    fichierImages.close();
    cout << "Activité des utilisateurs :" << endl;
    for (const auto& [utilisateur, nbr] : imagesParUtilisateur) {
        cout << "- " << utilisateur << " a téléchargé " << nbr << " images" << endl;
    }
}

void Administrateur::creerCategorie() {
    string nouveauNom;
    cout << "Entrez le nom de la nouvelle catégorie : ";
    cin >> nouveauNom;

    // code pour gerer un nouvel iD automatiquement pour l'utilisateur
    int newID = 0;
    string line;
    ifstream readFile("./data/categories.csv");
    while(getline(readFile, line))
        newID+=1;
    readFile.close();

    ofstream fichierCategories("./data/categories.csv", ios::app);
    if (fichierCategories.is_open()) {
        fichierCategories << newID << ',' << nouveauNom << endl;
        cout << "La catégorie '" << nouveauNom << "' a été créée avec succès." << endl;
    } else {
        cout << "Erreur lors de l'ouverture du fichier categories.csv" << endl;
    }
    fichierCategories.close();
}

void Administrateur::modifierCategorie() {
    int categorieId;
    string nouveauNom;

    cout << "Entrez l'ID de la catégorie à modifier : ";
    cin >> categorieId;

    cout << "Entrez le nouveau nom de la catégorie : ";
    cin >> nouveauNom;

    ifstream fichierCategories("./data/categories.csv");
    ofstream fichierTemp("./data/temp.csv");

    if (fichierCategories.is_open() && fichierTemp.is_open()) {
        string id, nom;
        bool trouve = false;

        while (fichierCategories.peek() !=EOF) {
            getline(fichierCategories, id, ',');
            getline(fichierCategories, nom, '\n');

            if (id == to_string(categorieId)) {
                fichierTemp << categorieId << "," << nouveauNom << endl;
                cout << "La catégorie '" << nom << "' a été modifiée en '" << nouveauNom << "'." << endl;
                trouve = true;
            } else {
                fichierTemp << id << "," << nom << endl;
            }
        }

        if (!trouve) {
            cout << "Catégorie introuvable." << endl;
        }
    } else {
        cout << "Erreur lors de l'ouverture des fichiers." << endl;
    }

    fichierCategories.close();
    fichierTemp.close();

    filesystem::remove("./data/categories.csv");
    filesystem::rename("./data/temp.csv", "./data/categories.csv");
}

void Administrateur::supprimerCategorie() {
    int categorieId;
    cout << "Entrez l'ID de la catégorie à supprimer : ";
    cin >> categorieId;

    ifstream fichierCategories("./data/categories.csv");
    ofstream fichierTemp("./data/temp.csv");

    if (fichierCategories.is_open() && fichierTemp.is_open()) {
        string ligne, id, nom;
        bool trouve = false;

    while (fichierCategories.peek() !=EOF) {
            getline(fichierCategories, id, ',');
            getline(fichierCategories, nom, '\n');

            if (id != to_string(categorieId)) {
                fichierTemp << id << "," << nom << endl;
            } else {
                cout << "La catégorie '" << nom << "' a été supprimée." << endl;
                trouve = true;
            }
        }
        if (!trouve) {
            cout << "Catégorie introuvable." << endl;
        }
    } else {
        cout << "Erreur lors de l'ouverture des fichiers." << endl;
    }

    fichierCategories.close();
    fichierTemp.close();

    filesystem::remove("./data/categories.csv");
    filesystem::rename("./data/temp.csv", "./data/categories.csv");
}

// Methode pour recuperer les prochains iD
int Administrateur::getNextId() const{
    ifstream fichierCategories("./data/categories.csv");
    string ligne;
    int newID = 0;
    while(fichierCategories.peek()!=EOF)
    {
        getline(fichierCategories, ligne);
        newID+=1;
    }
    fichierCategories.close();

    return newID;
}