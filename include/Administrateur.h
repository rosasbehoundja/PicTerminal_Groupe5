#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include <Utilisateur.h>


class Administrateur : public Utilisateur
{
    public:
        Administrateur();
        Administrateur(string name, string email, string password);
        ~Administrateur();

    // :) Autres Methodes
        void approuverImage();
        void rejeterimage();
        void afficherStatistiques();
        void creerCategorie();
        void supprimerCategorie();
        void modifierCategorie();
        int getNextId() const;
        void afficherUtilisateurs() const;
        void ajouterUtilisateur() const;
        void modifierUtilisateur() const;
        void suspendreUtilisateur() const;
        void supprimerUtilisateur() const;

    protected:

    private:
        bool verifierExistenceUtilisateur(const string& userId) const;
};

#endif // ADMINISTRATEUR_H
