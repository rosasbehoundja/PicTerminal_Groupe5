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
    : Utilisateur(to_string(getNextUserId()), name, email, password, true)
{

}

// :) Destructeur
Administrateur::~Administrateur()
{

}

// :)Autres Methodes

// ################################################ Gestion des Images #####################################################
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

// ################################################# Affichage des statistiques ##############################################
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

// ################################################# Gestion des categories ##################################################
void Administrateur::afficherCategories() 
{
    string id, nom;

    ifstream readFile("./data/categories.csv");
    while(readFile.peek() != EOF)
    {
        getline(readFile, id, ',');
        getline(readFile, nom, '\n');

        cout << id << ":" << nom << endl;
    }
    readFile.close();
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

void Administrateur::ajouterImageCategorie() {

        string imageId, categorieId;

        cout << "Entrez l'ID de votre Image : ";
        getline(cin, imageId);
        cout << "EEntrez l'ID de la categorie : ";
        getline(cin, categorieId);
        cout << endl;

        ifstream fichierLecture("images.csv");
        ofstream fichierEcriture("temp.csv");
        
        string id, nom, titre, description, nbrTelechargement, proprietaire, statut ,catId;
        
        while (fichierLecture.peek()!= EOF)
        {
            getline(fichierLecture, id, ',');
            getline(fichierLecture, nom, ',');
            getline(fichierLecture, titre, ',');
            getline(fichierLecture, description, ',');
            getline(fichierLecture, nbrTelechargement, ',');
            getline(fichierLecture, catId, ',');
            getline(fichierLecture, proprietaire, ',');
            getline(fichierLecture, statut, '\n');            
            
            if (id == imageId) {
                catId = categorieId;
            }
            fichierEcriture << id << "," << nom << "," << titre << "," << description << "," 
                            << nbrTelechargement << "," << catId << "," << proprietaire << "," << statut << std::endl;
        }
        
        fichierLecture.close();
        fichierEcriture.close();

        filesystem::rename("temp.csv", "images.csv");
    }

// Supprimer une image d'une catégorie
void Administrateur::supprimerImageCategorie() {
        
        string imageId, categorieId;

        cout << "Entrez l'ID de votre Image : ";
        getline(cin, imageId);
        cout << endl;

        ifstream fichierLecture("images.csv");
        ofstream fichierEcriture("temp.csv");
        
        string id, nom, titre, description, nbrTelechargement, proprietaire, statut ,catId;
        
        while (fichierLecture.peek()!= EOF)
        {
            getline(fichierLecture, id, ',');
            getline(fichierLecture, nom, ',');
            getline(fichierLecture, titre, ',');
            getline(fichierLecture, description, ',');
            getline(fichierLecture, nbrTelechargement, ',');
            getline(fichierLecture, catId, ',');
            getline(fichierLecture, proprietaire, ',');
            getline(fichierLecture, statut, '\n');            
            
            if (id == imageId) {
                catId = categorieId; // Mise à jour de la catégorie
            }
            fichierEcriture << id << "," << nom << "," << titre << "," << description << "," 
                            << nbrTelechargement << "," << "6" << "," << proprietaire << "," << statut << std::endl;
        }
        
        fichierLecture.close();
        fichierEcriture.close();
        
        // Remplacement du fichier original par le fichier temporaire
        filesystem::rename("temp.csv", "images.csv");
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

int Administrateur::getNextUserId() const{
    ifstream fichierUsers("./data/users.csv");
    string ligne;
    int newID = 0;
    while(fichierUsers.peek()!=EOF)
    {
        getline(fichierUsers, ligne);
        newID+=1;
    }
    fichierUsers.close();

    return newID;
}


// ############################################### Gestion des utilisateurs #################################################
void Administrateur::afficherUtilisateurs() const {
    ifstream usersFile("./data/users.csv");
    string id, nom, email, password, statut;
    
    cout << "\n\t~~~~~~~~~~~~~ LISTE DES UTILISATEURS ~~~~~~~~~~~~" << endl;
    cout << "\t" << left << setw(5) << "ID" << setw(20) << "Nom" << setw(30) 
         << "Email" << setw(10) << "Statut" << endl;
    cout << "\t" << string(65, '-') << endl;
    
    while (usersFile.peek() != EOF) {
        getline(usersFile, id, ',');
        getline(usersFile, nom, ',');
        getline(usersFile, email, ',');
        getline(usersFile, password, ',');
        getline(usersFile, statut);
        
        string statutText = (statut == "1") ? "Administrateur" : "Utilisateur";
        cout << "\t" << left << setw(5) << id << setw(20) << nom 
             << setw(30) << email << setw(10) << statutText << endl;
    }
    cout << "\t" << string(65, '-') << endl;
    usersFile.close();
}

void Administrateur::ajouterUtilisateur() const {
    string nom, email, password;
    
    cout << "Entrez le nom de l'utilisateur : ";
    cin >> nom;
    cout << "Entrez l'email de l'utilisateur : ";
    cin >> email;
    cout << "Entrez le mot de passe de l'utilisateur : ";
    cin >> password;
    
    // Générer un nouvel ID
    int newId = 0;
    string line;
    ifstream readFile("./data/users.csv");
    while(getline(readFile, line)) newId++;
    readFile.close();
    
    ofstream usersFile("./data/users.csv", ios::app);
    if (usersFile.is_open()) {
        usersFile << newId << "," << nom << "," << email << "," << password << ",1" << endl;
        cout << "Utilisateur ajouté avec succès!" << endl;
    } else {
        cout << "Erreur lors de l'ajout de l'utilisateur." << endl;
    }
    usersFile.close();
}

void Administrateur::modifierUtilisateur() const {
    string userId;
    cout << "Entrez l'ID de l'utilisateur à modifier : ";
    cin >> userId;
    
    if (!verifierExistenceUtilisateur(userId)) {
        cout << "Utilisateur introuvable." << endl;
        return;
    }
    
    string nouveauNom, nouvelEmail, nouveauPassword;
    cout << "Nouveau nom (ou entrée pour garder l'ancien) : ";
    cin.ignore();
    getline(cin, nouveauNom);
    cout << "Nouvel email (ou entrée pour garder l'ancien) : ";
    getline(cin, nouvelEmail);
    cout << "Nouveau mot de passe (ou entrée pour garder l'ancien) : ";
    getline(cin, nouveauPassword);
    
    ifstream usersIn("./data/users.csv");
    ofstream usersTemp("./data/users_temp.csv");
    
    string id, nom, email, password, statut;
    while (usersIn.peek() != EOF) {
        getline(usersIn, id, ',');
        getline(usersIn, nom, ',');
        getline(usersIn, email, ',');
        getline(usersIn, password, ',');
        getline(usersIn, statut,'\n');
        
        if (id == userId) {
            usersTemp << id << ","
                     << (nouveauNom.empty() ? nom : nouveauNom) << ","
                     << (nouvelEmail.empty() ? email : nouvelEmail) << ","
                     << (nouveauPassword.empty() ? password : nouveauPassword) << ","
                     << statut << endl;
        } else {
            usersTemp << id << "," << nom << "," << email << "," 
                     << password << "," << statut << endl;
        }
    }
    
    usersIn.close();
    usersTemp.close();
    
    filesystem::remove("./data/users.csv");
    filesystem::rename("./data/users_temp.csv", "./data/users.csv");
    
    cout << "Utilisateur modifié avec succès!" << endl;
}

void Administrateur::suspendreUtilisateur() const {
    string userId;
    cout << "Entrez l'ID de l'utilisateur à suspendre/réactiver : ";
    cin >> userId;
    
    if (!verifierExistenceUtilisateur(userId)) {
        cout << "Utilisateur introuvable." << endl;
        return;
    }
    
    ifstream usersIn("./data/users.csv");
    ofstream usersTemp("./data/users_temp.csv");
    
    string id, nom, email, password, statut;
    while (usersIn.peek() != EOF) {
        getline(usersIn, id, ',');
        getline(usersIn, nom, ',');
        getline(usersIn, email, ',');
        getline(usersIn, password, ',');
        getline(usersIn, statut,'\n');
    {
        
        if (id == userId) {
            string nouveauStatut = (statut == "1") ? "0" : "1";
            usersTemp << id << "," << nom << "," << email << "," 
                     << password << "," << nouveauStatut << endl;
            cout << "Utilisateur " << (nouveauStatut == "1" ? "réactivé" : "suspendu") 
                 << " avec succès!" << endl;
        } else {
            usersTemp << id << "," << nom << "," << email << "," 
                     << password << "," << statut << endl;
        }
    }
    
    usersIn.close();
    usersTemp.close();
    
    filesystem::remove("./data/users.csv");
    filesystem::rename("./data/users_temp.csv", "./data/users.csv");
    }
}

void Administrateur::supprimerUtilisateur() const {
    string userId;
    cout << "Entrez l'ID de l'utilisateur à supprimer : ";
    cin >> userId;
    
    if (!verifierExistenceUtilisateur(userId)) {
        cout << "Utilisateur introuvable." << endl;
        return;
    }
    
    ifstream usersIn("./data/users.csv");
    ofstream usersTemp("./data/users_temp.csv");
    
    string id, ligne;
    while (getline(usersIn, id, ',') && getline(usersIn, ligne)) {
        if (id != userId) {
            usersTemp << id << "," << ligne << endl;
        }
    }
    
    usersIn.close();
    usersTemp.close();
    
    filesystem::remove("./data/users.csv");
    filesystem::rename("./data/users_temp.csv", "./data/users.csv");
    
    cout << "Utilisateur supprimé avec succès!" << endl;
}

bool Administrateur::verifierExistenceUtilisateur(const string& userId) const {
    ifstream usersFile("./data/users.csv");
    string id, nom, email, password, statut;
    
    while (usersFile.peek() != EOF) {
        getline(usersFile, id, ',');
        getline(usersFile, nom, ',');
        getline(usersFile, email, ',');
        getline(usersFile, password, ',');
        getline(usersFile, statut,'\n');
        if (id == userId) {
            usersFile.close();
            return true;
        }
    }
    usersFile.close();
    return false;
}