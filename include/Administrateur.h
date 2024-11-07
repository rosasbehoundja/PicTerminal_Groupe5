#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include <Utilisateur.h>


class Administrateur : public Utilisateur
{
    public:
        Administrateur(string id, string name, string email, string password,bool statut);
        ~Administrateur();

    // :) Autres Methodes
        void approuverImage() const;
        void rejeterimage() const;
        void afficherStatistiques() const;
        void creerCategorie() const;
        void supprimerCategorie() const;
        void modifierCategorie() const;
        int getNextId() const;

    protected:

    private:
};

#endif // ADMINISTRATEUR_H
