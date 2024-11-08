#include "Utilisateur.h"
#include "Image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <filesystem>

using namespace std;

// :) Constructeurs
Utilisateur::Utilisateur() // constructeur par defaut
{
    iD = -1;
    Nom = "John";
    Email = "john@gmail.com";
    Password = "secret";
    Statut = false;
}

Utilisateur::Utilisateur(string id, string name, string email, string password) // constructeur utilise lors de l'inscription
{
    iD = id;
    Nom = name;
    Email = email;
    Password = password;
    Statut = false;
}
Utilisateur::Utilisateur(string id, string name, string email, string password,bool statut) // Constructeur utilise lors de la connexion
{
    iD = id;
    Nom = name;
    Email = email;
    Password = password;
    Statut = false;
}

// :)Destructeur
Utilisateur::~Utilisateur()
{

}

// :) Autres methodes
Utilisateur Utilisateur::seConnecter()
{
    Utilisateur user; // creer un utilisateur virtuel au debut
    string mail_co, passw_co; // donnees en entree
    string id, nom, mail, passw, statut;// variables de validation
    bool trouve = false;

    start:
    cout << "\t\t\t\t------------------------- MENU DE CONNEXION ------------------"<< endl;
    cout << "\t\t\tEntrez votre email : ";
    cin >> mail_co;
    cout << endl;
    cout << "\t\t\tEntrez votre mot de passe : ";
    cin >> passw_co;
    cout << endl;
    cout << "\t\t\t\t----------------------------------------------------------------" << endl;

    ifstream user_data("./data/users.csv");

    if (!user_data.is_open())
        cout << "!!!Erreur d'ouverture du Fichier users.csv";

    getline(user_data, id); // sauter la premiere ligne

    while ((user_data.peek()!=EOF))
    {
        getline(user_data, id, ',');
        getline(user_data, nom, ',');
        getline(user_data, mail, ',');
        getline(user_data, passw, ',');
        getline(user_data, statut, '\n');

        if ((mail_co == mail) && (passw_co== passw)) // si les entrees correspondent a un profil present dans le dataset
        {
            user = Utilisateur(id, nom, mail, passw, statut=="0");
            cout << "CONNECTE....." << endl;
            trouve = true;
            break;// notifier que l'utilisateur a ete retrouve dans le dataset
        }
        else if ((mail_co == mail) && (passw_co!= passw)) // si l'utilisateur a ete retrouve mais que son mot de passe ne correspond pas
        {
            cout << "Mot de passe incorrect.. veuillez ressayer svp";
            goto start;
        }
        else // si l'utilisateur n'a pas ete retrouve dans le dataset
        {
            trouve = false;
        }
    }
    if (trouve == false)
    {
        cout << "Utilisateur non trouve...";
        goto start;
    }
    user_data.close();// fermer le fichier
    return user;
}

Utilisateur Utilisateur::Inscription()
{
    Utilisateur user; // creer un utilisateur virtuel au debut
    string nom_in, mail_in, passw_in; // donnees en entree
    string id, nom, mail, passw, statut;// variables de validation
    bool trouve = false;

    start:
    cout << "\t\t\t\t------------------------- FORMULAIRE D'INSCRIPTION ------------------"<< endl;
    cout << "\t\t\tEntrez votre nom : ";
    cin >> nom_in;
    cout << endl;
    cout << "\t\t\tEntrez votre email : ";
    cin >> mail_in;
    cout << endl;
    cout << "\t\t\tEntrez votre mot de passe : ";
    cin >> passw_in;
    cout << endl;
    cout << "\t\t\t\t----------------------------------------------------------------------" << endl;

    // code pour gerer un nouvel iD automatiquement pour l'utilisateur
    int newID = 0;
    string line;
    ifstream readFile("./data/users.csv");
    while(getline(readFile, line))
        newID+=1;
    readFile.close();

    // creer le nouvel utilisateur
    user = Utilisateur(to_string(newID), nom_in, mail_in, passw_in);

    // sauvegarder ses informations dans le fichier user.csv
    ofstream user_data;
    user_data.open("./data/users.csv", ios::app);
    if(!user_data.is_open())
        cout << "!!! Erreur d'ouverture de fichier" << endl;
    else
    {
        user_data << newID << ',' << nom_in << ',' << mail_in << ',' << passw_in << ',' << user.GetStatut() << endl;
        cout << " Utilisateur Enregistre ...." <<  endl;
        this_thread::sleep_for(chrono::seconds(2)); // patienter deux secondes
    }
    user_data.close(); // fermer le fichier
    return user;
}

void Utilisateur::afficherProfil() const
{
    cout << "\t\t\t\t-------------------INFORMATIONS PROFIL------------------" << endl;
    cout << "\t\t\t Nom : " << GetNom();
    cout << "\t\t\t Email : " << GetEmail();
    cout << "\t\t\t Mot de passe : " << GetPassword();
    cout << endl;
    cout << "\t\t\t\t---------------------------------------------------------" << endl;
}

// ############################################ Interactions avec les images ################################################
void Utilisateur::afficherGalerie() const
{
    // recuperer images de images.csv
    ifstream image_data("./data/images.csv");
    string idImage,nom,titre,description,nbr_telechargement,idCategories,proprietaire,statut;

    if (!image_data.is_open())
        cout << "Error File Opening!";

    cout << "\n\t~~~~~~~~~~~~~ MA GALERIE ~~~~~~~~~~~~" << endl;


    cout << "\t" << left << setw(5) << "ID" << setw(25) << "Titre" << setw(20) << "Catégorie" << right << setw(10) << "Note" << setw(15) << "Téléchargement" << endl;
    cout << "\t" << string(75, '-') << endl;

    getline(image_data, idImage);
    // afficher toutes les images
    while (image_data.peek()!= EOF)
    {
        getline(image_data, idImage, ',');
        getline(image_data, nom, ',');
        getline(image_data, titre, ',');
        getline(image_data, description, ',');
        getline(image_data, nbr_telechargement, ',');
        getline(image_data, idCategories, ',');
        getline(image_data, proprietaire, ',');
        getline(image_data, statut, '\n');

        if (GetNom()== proprietaire && statut == "1")// si l'image est publique et approuvee, l'afficher
        {
            cout << "\t" << left << setw(5) << idImage << setw(25) << titre << setw(20) << idCategories << right << setw(10) << nbr_telechargement << setw(15) << endl;
            cout << "\t" << string(75, '-') << endl;
        }
    }
    image_data.close();
    return;
}


void Utilisateur::telechargerImage() const {
    int imageId;
    cout << "\nEntrez l'ID de l'image à télécharger : ";
    cin >> imageId;
    
    if (!verifierExistenceImage(imageId)) {
        cout << "Image introuvable." << endl;
        return;
    }
    
    cout << "Téléchargement en cours";
    for(int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "." << flush;
    }
    cout << endl;

    Image img;
    img.incrementerTelechargements(img, imageId);
    
    cout << "Téléchargement terminé avec succès!" << endl;
}
void Utilisateur::afficherToutesLesImages() const
{
    // recuperer images de images.csv
    ifstream image_data("./data/images.csv");
    string idImage,nom,titre,description,nbr_telechargement,idCategories,proprietaire,statut;

    if (!image_data.is_open())
        cout << "Error File Opening!";

    cout << "\n\t~~~~~~~~~~~~~ TOUTES LES IMAGES ~~~~~~~~~~~~" << endl;


    cout << "\t" << left << setw(5) << "ID" << setw(25) << "Titre" << setw(20) << "Catégorie" << right << setw(10) << "Note" << setw(15) << "Téléchargement" << endl;
    cout << "\t" << string(75, '-') << endl;

    getline(image_data, idImage);
    // afficher toutes les images
    while (image_data.peek()!= EOF)
    {
        getline(image_data, idImage, ',');
        getline(image_data, nom, ',');
        getline(image_data, titre, ',');
        getline(image_data, description, ',');
        getline(image_data, nbr_telechargement, ',');
        getline(image_data, idCategories, ',');
        getline(image_data, proprietaire, ',');
        getline(image_data, statut, '\n');

        if (statut == "1")// si l'image est publique et approuvee, l'afficher
        {
            cout << "\t" << left << setw(5) << idImage << setw(25) << titre << setw(20) << idCategories << right << setw(10) << nbr_telechargement << setw(15) << endl;
            cout << "\t" << string(75, '-') << endl;
        }
    }
    image_data.close();
    return;
}

void Utilisateur::televerserImage() const
{
    string nom_fichier, titre, description;

    cout << "\n~~~~~~~~~~~~~ TELEVERSER UNE IMAGE ~~~~~~~~~~~~" << endl;
    cout << "Nom (exemple: sunset.jpg) : ";
    getline(cin, nom_fichier);
    cout << "Titre : ";
    getline(cin, titre);
    cout << "Description : ";
    getline(cin, description);
    cout << endl;
    
    try {
        // nouvel ID image
        int newID = 1;
        string line;
        ifstream readFile("./data/images.csv");
        while(getline(readFile, line)) newID++;
        readFile.close();
        
        // ajouter image a images.csv
        ofstream imageFile;
        imageFile.open("./data/images.csv", ios::app);
        if(!imageFile.is_open()) return;
        
        // imgID,Nom,Titre,Description,Nbr_telechargement,Note,Est_approuvee,Est_publique,Categorie
        imageFile << newID << "," 
                 << nom_fichier << "," 
                 << titre << "," 
                 << description << ","
                 << "0" << "," // Nbr_telechargement initial
                 << "6" << "," // categorie initiale
                 << GetNom() << "," // proprietaire
                 << false // Est_approuvee initial
                 << endl;
        
        imageFile.close();
        cout << "\nImage enregistree..." << endl;
        return;
    }
    catch(...) {
        cout << "\nErreur lors du telechargement de l'image." << endl;
        return;
    }
    return;
}
// ########################################### gestion des favoris #########################################################
void Utilisateur::ajouterAuxFavoris(int imageId) const {
    if (!verifierExistenceImage(imageId)) {
        cout << "Image introuvable." << endl;
        return;
    }
    
    if (estDansFavoris(imageId)) {
        cout << "Cette image est déjà dans vos favoris." << endl;
        return;
    }
    
    ofstream favorisFile("./data/favoris.csv", ios::app);
    if (favorisFile.is_open()) {
        favorisFile << GetiD() << "," << imageId << endl;
        cout << "Image ajoutée aux favoris avec succès!" << endl;
    } else {
        cout << "Erreur lors de l'ajout aux favoris." << endl;
    }
    favorisFile.close();
}


void Utilisateur::retirerDesFavoris(int imageId) const {
    if (!estDansFavoris(imageId)) {
        cout << "Cette image n'est pas dans vos favoris." << endl;
        return;
    }
    string id, ligne;
    ifstream favorisIn("./data/favoris.csv");
    ofstream favorisTemp("./data/temp.csv");
    
    string userId, imgId;
    while (favorisIn.peek() != EOF) {

        getline(favorisIn, userId, ',');
        getline(favorisIn, imgId,'\n');
        if (!(userId == GetiD() && imgId == to_string(imageId))) {
            favorisTemp << userId << "," << imgId << endl;
        }
    }
    favorisIn.close();
    favorisTemp.close();
    
    filesystem::remove("./data/favoris.csv");
    filesystem::rename("./data/temp.csv", "./data/favoris.csv");
    
    cout << "Image retirée des favoris avec succès!" << endl;
}


void Utilisateur::afficherFavoris() const {
    cout << "\n\t~~~~~~~~~~~~~ MES FAVORIS ~~~~~~~~~~~~" << endl;
    cout << "\t" << left << setw(5) << "ID" << setw(25) << "Titre" << setw(20) << "Catégorie" << endl;
    cout << "\t" << string(50, '-') << endl;
    
    ifstream favorisFile("./data/favoris.csv");
    string userId, imageId;
    
    while (favorisFile.peek() != EOF) {

        getline(favorisFile, userId, ',');
        getline(favorisFile, imageId,'\n');
        if (userId == GetiD()) {

            //details de l'image
            ifstream imagesFile("./data/images.csv");
            string id, nom, titre, description, downloads, categorie, proprietaire, statut;
            
            while (imagesFile.peek() != EOF) {
                getline(imagesFile, id, ',');
                getline(imagesFile, nom, ',');
                getline(imagesFile, titre, ',');
                getline(imagesFile, description, ',');
                getline(imagesFile, downloads, ',');
                getline(imagesFile, categorie, ',');
                getline(imagesFile, proprietaire, ',');
                getline(imagesFile, statut,'\n');
                
                if (id == imageId) {
                    cout << "\t" << left << setw(5) << id << setw(25) << titre << setw(20) << categorie << endl;
                    break;
                }
            }
            imagesFile.close();
        }
    }
    favorisFile.close();
    cout << "\t" << string(50, '-') << endl;
}

bool Utilisateur::estDansFavoris(int imageId) const {
    ifstream favorisFile("./data/favoris.csv");
    string userId, imgId;
    
    while (favorisFile.peek() != EOF) {

        getline(favorisFile, userId, ',');
        getline(favorisFile, imgId,'\n');
        if (userId == GetiD() && imgId == to_string(imageId)) {
            favorisFile.close();
            return true;
        }
    }
    favorisFile.close();
    return false;
}

bool Utilisateur::verifierExistenceImage(int imageId) const {
    ifstream imagesFile("./data/images.csv");
    string id, ligne;
    
    while (imagesFile.peek() !=EOF) {

        getline(imagesFile, id, ',');
        getline(imagesFile, ligne);
        if (id == to_string(imageId)) {
            imagesFile.close();
            return true;
        }
    }
    imagesFile.close();
    return false;
}


// :) Accesseurs | Getters
string Utilisateur::GetiD() const { return iD; }
string Utilisateur::GetNom() const { return Nom; }
string Utilisateur::GetEmail() const { return Email; }
bool Utilisateur::GetStatut() { return Statut; }
string Utilisateur::GetPassword() const { return Password; }


// :) Mutateurs | Setters
void Utilisateur::SetPassword(string val) { Password = val; }
void Utilisateur::SetiD(string val) { iD = val; }
void Utilisateur::SetStatut(bool val) { Statut = val; }
void Utilisateur::SetNom(string val) { Nom = val; }
void Utilisateur::SetEmail(string val) { Email = val; }
