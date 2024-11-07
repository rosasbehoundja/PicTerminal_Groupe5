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
        void telechargerImage() const;
        void televerserImage() const;


    // :) Accesseurs
        string GetiD() const;
        string GetNom() const;
        string GetEmail() const;
        bool GetStatut();
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
