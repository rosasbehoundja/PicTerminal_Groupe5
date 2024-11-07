#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
using  namespace std;

class Image
{
    public:
    // :) Constructeurs
        Image();
        Image(int ID, string nom, string titre, string descr, string propio);
        Image(const Image& other);

    // :) Destructeurs
        ~Image();

    // :)  Autres Methodes
        void afficherDetails() const;
        void incrementerTelechargements(Image img,int val) const;
        void SaveInfos() const;

    // :) Accesseurs
        int GetImageId() const;
        string Getnom() const;
        string GetTitre() const;
        string GetDescription() const;
        int GetNbr_telechargement() const;
        int GetiDCategorie() const;
        string GetProprietaire() const;
        bool Getest_Approuvee() const;

    // :) Mutateurs
        void Setnom(string val) ;
        void SetTitre(string val) ;
        void SetDescription(string val) ;
        void SetNbr_telechargement(int val=1);
        void SetProprietaire(string val) ;
        void Setest_Approuvee(bool val);
        void SetiDCategorie(int val);

    protected:

    private:
        int ImageId;
        string Nom;
        string Titre;
        string Description;
        int Nbr_telechargement;
        int iDCategorie;
        string Proprietaire;
        bool est_Approuvee;
};

#endif // IMAGE_H
