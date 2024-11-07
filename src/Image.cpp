#include "Image.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>

using namespace std;

// :) Constructeurs

Image::Image()
{
    ImageId = 1;
    Nom = "nature_01.jpg";
    Titre = "Forêt ensoleillée";
    Description = "Une belle forêt baignée de lumière" ;
    Nbr_telechargement = 0 ;
    iDCategorie = 1;
    Proprietaire = "Alice";
    est_Approuvee = true;
}
Image::Image(int ID, string nom, string titre, string descr, string propio)
{
    ImageId = ID;
    Nom = nom;
    Titre = titre;
    Description = descr;
    Nbr_telechargement = 0;
    iDCategorie = 6;
    Proprietaire = propio;
    est_Approuvee = false;
}

Image::Image(const Image& img)
{
    ImageId = img.ImageId;
    Nom = img.Nom;
    Titre = img.Titre;
    Description = img.Description;
    Nbr_telechargement = img.Nbr_telechargement;
    iDCategorie = img.iDCategorie;
    Proprietaire = img.Proprietaire;
    est_Approuvee = img.est_Approuvee;
}

// :) Destructeurs
Image::~Image()
{

}
// :)  Autres Methodes
void Image::afficherDetails() const
{
    cout << "-----------------------------Details Image--------------------------" << endl;
    cout << "ID : " << GetImageId() << endl;
    cout << "Nom : " << Getnom()<< endl;
    cout << "Titre : " << GetTitre()<< endl;
    cout << "Description : " << GetDescription()<< endl;
    cout << "Nbre_Telechargement : " << GetNbr_telechargement()<< endl;
    cout << "IdCategorie : " << GetiDCategorie()<< endl;
    cout << "Proprietaire : " << GetProprietaire()<< endl;
    cout << "EstApprouvee : " << Getest_Approuvee()<< endl;
    cout << "---------------------------------------------------------------------" << endl;
}

void Image::SaveInfos() const
{
    return;
}

void Image::incrementerTelechargements(Image img,int imageId) const
{
    img.SetNbr_telechargement(1);

    ifstream fichierLecture("./data/images.csv");
    ofstream fichierEcriture("./data/temp.csv");

    if (!fichierLecture.is_open() || !fichierEcriture.is_open()) {
        std::cerr << "Erreur d'ouverture du fichier." << std::endl;
        return;
    }

    string id, nom, titre, description, nbrTelechargement, catId, proprietaire, statut;

    while (getline(fichierLecture, id, ',') &&
           getline(fichierLecture, nom, ',') &&
           getline(fichierLecture, titre, ',') &&
           getline(fichierLecture, description, ',') &&
           getline(fichierLecture, nbrTelechargement, ',') &&
           getline(fichierLecture, catId, ',') &&
           getline(fichierLecture, proprietaire, ',') &&
           getline(fichierLecture, statut, '\n'))
    {
        // Vérification de l'ID de l'image
        if (id == to_string(imageId)) {
            int temp = stoi(nbrTelechargement); // Conversion en entier
            temp += 1;                          // Incrémentation
            nbrTelechargement = to_string(temp); // Reconversion en string
        }

        // Écriture de la ligne (modifiée ou non) dans le fichier temporaire
        fichierEcriture << id << "," << nom << "," << titre << "," << description << ","
                        << nbrTelechargement << "," << catId << "," << proprietaire << ","
                        << statut << endl;
    }

    fichierLecture.close();
    fichierEcriture.close();
    filesystem::remove("./data/images.csv");
    filesystem::rename("./data/temp.csv", "./data/images.csv");
}

// :) Accesseurs
int Image::GetImageId() const { return ImageId; }
string Image::Getnom() const { return Nom; }
string Image::GetTitre() const { return Titre; }
string Image::GetDescription() const { return Description; }
int Image::GetNbr_telechargement() const { return Nbr_telechargement; }
int Image::GetiDCategorie() const { return iDCategorie; }
string Image::GetProprietaire() const { return Proprietaire; }
bool Image::Getest_Approuvee() const { return est_Approuvee; }

// :) Mutateurs
void Image::Setnom(string val) { Nom = val; }
void Image::SetTitre(string val) { Titre = val; }
void Image::SetDescription(string val) { Description = val; }

void Image::SetNbr_telechargement(int val)
{
    Nbr_telechargement +=val;
}
void Image::SetiDCategorie(int val) { iDCategorie = val; }
void Image::SetProprietaire(string val) { Proprietaire = val; }
void Image::Setest_Approuvee(bool val) { est_Approuvee = val; }
