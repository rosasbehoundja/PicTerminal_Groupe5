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
  

    protected:

    private:
};

#endif // ADMINISTRATEUR_H
