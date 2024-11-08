#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <iostream>
using  namespace std;

class Utilisateur
{
    public:
    // :) Constructeurs
        Utilisateur();
        Utilisateur(string id, string name, string email, string password);
        Utilisateur(string id, string name, string email, string password,bool statut);

    // :)Destructeur
        ~Utilisateur();

    // :) Autres methodes
        Utilisateur seConnecter();
        Utilisateur Inscription();

        void afficherProfil() const;

        void afficherGalerie() const;
        void afficherToutesLesImages() const;
        void telechargerImage() const;
        void televerserImage() const;

        void ajouterAuxFavoris() const;
        void retirerDesFavoris() const;
        void afficherFavoris() const;
        bool estDansFavoris(int imageId) const;
        
        bool verifierExistenceImage(int imageId) const;
        bool isAdmin() const;

    // :) Accesseurs
        string GetiD() const;
        string GetNom() const;
        string GetEmail() const;
        bool GetStatut () const;
        string GetPassword() const;

    // :) Mutateurs
        void SetPassword(string val);
        void SetiD(string val);
        void SetStatut(bool val);
        void SetNom(string val);
        void SetEmail(string val);

    protected:
        string iD;
        string Nom;
        string Email;
        string Password;
        bool Statut;
        

    private:
       
};

#endif // UTILISATEUR_H
