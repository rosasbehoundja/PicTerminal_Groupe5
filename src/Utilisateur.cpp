#include "Utilisateur.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include <chrono>

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

void Utilisateur::afficherGalerie() const
{
    // recuperer images de images.csv
    ifstream image_data("./data/images.csv");
    string idImage,nom,titre,description,nbr_telechargement,idCategories,proprietaire,statut;

    if (!image_data.is_open())
        cout << "Error File Opening!";

    cout << "\n\t~~~~~~~~~~~~~ TOUTES LES IMAGES PUBLIQUES ~~~~~~~~~~~~" << endl;


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

void Utilisateur::telechargerImage() const
{

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
