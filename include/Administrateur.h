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

        void afficherCategories();
        void creerCategorie();
        void supprimerCategorie();
        void modifierCategorie();
        void ajouterImageCategorie();
        void supprimerImageCategorie();

        int getNextId() const;
        int getNextUserId() const;

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
