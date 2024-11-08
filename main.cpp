#include <iostream>
#include <cstdlib>

#include "Utilisateur.h"
#include "Image.h"
#include "Administrateur.h"

using namespace std;

// Fonctions pour les menus
void afficherMenuPrincipal();
void menuUtilisateur(Utilisateur& user);
void menuAdministrateur(Administrateur& admin);

// Fonction principale
int main() {
    string option;

    // Affichage du menu principal
    afficherMenuPrincipal();
    cout << "Entrez un choix : ";
    cin >> option;

    if (option == "1") {
        system("clear");
        Utilisateur user = Utilisateur().seConnecter(); // Fonction de connexion
        cout << user.isAdmin() << endl;
        if (user.isAdmin()) {
        Administrateur admin(user.GetNom(), user.GetEmail(), user.GetPassword());
        menuAdministrateur(admin);
        } else {
            menuUtilisateur(user);
        }
    } else if (option == "2") {
        system("clear");
        Utilisateur newUser = Utilisateur().Inscription(); // Fonction d'inscription
        menuUtilisateur(newUser);
    } else {
        cout << "Au revoir !" << endl;
        return 0;
    }

    return 0;
}

void afficherMenuPrincipal() {
    cout << " \t\t\t\t ==================================" << endl;
    cout << "\t\t\t\t|                                  |" << endl;
    cout << "\t\t\t\t|  :) Bienvenue sur PICTERMINAL    |" << endl;
    cout << "\t\t\t\t|                                  |" << endl;
    cout << " \t\t\t\t ==================================" << endl;
    cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t\t\t\t\t[1]-  Se connecter" << endl;
    cout << "\t\t\t\t\t\t[2]-  S'Inscrire  " << endl;
    cout << "\t\t\t\t\t\t[-1]- Quitter     " << endl;
    cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

// Menu pour les fonctionnalités de l'utilisateur
void menuUtilisateur(Utilisateur& user) {
    string option;

    do {
        cout << "\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~ MENU UTILISATEUR ~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t\t\t\t\t\t[1] - Afficher la galerie" << endl;
        cout << "\t\t\t\t\t\t[2] - Gérer les favoris" << endl;
        cout << "\t\t\t\t\t\t[3] - Afficher les favoris" << endl;
        cout << "\t\t\t\t\t\t[4] - Afficher la liste des images" << endl;
        cout << "\t\t\t\t\t\t[5] - Afficher profil" << endl;
        cout << "\t\t\t\t\t\t[6] - Telecharger une image" << endl;
        cout << "\t\t\t\t\t\t[7] - Televerser une image" << endl;
        cout << "\t\t\t\t\t\t[0] - Retour au menu principal" << endl;
        cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Entrez un choix : ";
        cin >> option;

        if (option == "1") {
            user.afficherGalerie();
        } else if (option == "2") {
            string subOption;
            cout << "\n\t\t\t\t~~~~ GESTION DES FAVORIS ~~~~" << endl;
            cout << "\t\t\t\t\t\t[1] - Ajouter une image aux favoris" << endl;
            cout << "\t\t\t\t\t\t[2] - Afficher les favoris" << endl;
            cout << "\t\t\t\t\t\t[3] - Supprimer une image des favoris" << endl;
            cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Entrez un choix : ";
            cin >> option;

            if (subOption == "1") user.ajouterAuxFavoris();
            else if (subOption == "2") user.afficherFavoris();
            else if (subOption == "3") user.retirerDesFavoris();

        } else if (option == "3") {
            user.afficherFavoris();
        }
        else if (option == "4") {
            user.afficherToutesLesImages();
        }
        else if (option == "5") {
            user.afficherProfil();
        }
        else if (option == "6") {
            user.telechargerImage();
        }
        else if (option == "7") {
            user.televerserImage();
        }
    } while (option != "0");
}

// Menu pour les fonctionnalités de l'administrateur
void menuAdministrateur(Administrateur& admin) {
    string option;

    do {
        cout << "\n\t\t\t\t~~~~~~~~~~~~~~~~~~~ MENU ADMINISTRATEUR ~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t\t\t\t\t\t[1] - Gérer les catégories" << endl;
        cout << "\t\t\t\t\t\t[2] - Approuver ou rejeter des images" << endl;
        cout << "\t\t\t\t\t\t[3] - Afficher les statistiques" << endl;
        cout << "\t\t\t\t\t\t[4] - Gérer les utilisateurs" << endl;
        cout << "\t\t\t\t\t\t[5] - Afficher la liste des images" << endl;
        cout << "\t\t\t\t\t\t[0] - Retour au menu principal" << endl;
        cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Entrez un choix : ";
        cin >> option;

        if (option == "1") {
            string subOption;
            cout << "\n\t\t\t\t~~~~ GESTION DES CATEGORIES ~~~~" << endl;
            cout << "\t\t\t\t\t\t[1] - Créer une catégorie" << endl;
            cout << "\t\t\t\t\t\t[2] - Modifier une catégorie" << endl;
            cout << "\t\t\t\t\t\t[3] - Supprimer une catégorie" << endl;
            cout << "\t\t\t\t\t\t[4] - Ajouter une image à une catégorie" << endl;
            cout << "\t\t\t\t\t\t[5] - Supprimer une image d'une catégorie" << endl;
            cout << "\t\t\t\t\t\t[6] - Afficher la liste des catégories" << endl;
            cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Entrez un choix : ";
            cin >> subOption;

            if (subOption == "1") admin.creerCategorie();
            else if (subOption == "2") admin.modifierCategorie();
            else if (subOption == "3") admin.supprimerCategorie();
            else if (subOption == "3") admin.supprimerCategorie();
            else if (subOption == "4") admin.ajouterImageCategorie();
            else if (subOption == "5") admin.supprimerImageCategorie();
            else if (subOption == "6") admin.afficherCategories();
        }
        else if (option == "2") {
            string subOption;
            cout << "\n\t\t\t\t~~~~ MODERATION DES IMAGES ~~~~" << endl;
            cout << "\t\t\t\t\t\t[1] - Approuver une image" << endl;
            cout << "\t\t\t\t\t\t[2] - Rejeter une image" << endl;
            cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Entrez un choix : ";
            cin >> subOption;

            if (subOption == "1") admin.approuverImage();
            else if (subOption == "2") admin.rejeterimage();
        }
        else if (option == "3") {
            admin.afficherStatistiques();
        }
        else if (option == "4") {
            string userOption;
            cout << "\n\t\t\t\t~~~~ GESTION DES UTILISATEURS ~~~~" << endl;
            cout << "\t\t\t\t\t\t[1] - Afficher les utilisateurs" << endl;
            cout << "\t\t\t\t\t\t[2] - Ajouter un utilisateur" << endl;
            cout << "\t\t\t\t\t\t[3] - Modifier un utilisateur" << endl;
            cout << "\t\t\t\t\t\t[4] - Suspendre un utilisateur" << endl;
            cout << "\t\t\t\t\t\t[5] - Supprimer un utilisateur" << endl;
            cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Entrez un choix : ";
            cin >> userOption;

            if (userOption == "1") admin.afficherUtilisateurs();
            else if (userOption == "2") admin.ajouterUtilisateur();
            else if (userOption == "3") admin.modifierUtilisateur();
            else if (userOption == "4") admin.suspendreUtilisateur();
            else if (userOption == "5") admin.supprimerUtilisateur();
        }
        else if (option == "5") {
            admin.afficherToutesLesImages();
        }
    } while (option != "0");
}
