#include <iostream>
#include <cstdlib>

#include "Utilisateur.h"
#include "Image.h"

using namespace std;

int main()
{
        Image Photo;
        Photo.SetNbr_telechargement();
        cout << Photo.GetNbr_telechargement() << endl;
        Photo.afficherDetails();
        /*
        Utilisateur Profil;
        string option;

        cout <<" \t\t\t\t\ =================================="<< endl;
        cout <<"\t\t\t\t\|                                  |"<< endl;
        cout <<"\t\t\t\t\|  :) Bienvenue sur PICTERMINAL    |"<< endl;
        cout <<"\t\t\t\t\|                                  |"<< endl;
        cout <<" \t\t\t\t\ =================================="<< endl;

        cout << "\t\t\t\t\~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t\t\t\t\t\t\[1]-  Se connecter" << endl;
        cout << "\t\t\t\t\t\t\[2]-  S'Inscrire  " << endl;
        cout << "\t\t\t\t\t\t\[-1]- Quitter     " << endl;
        cout << "\t\t\t\t\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" <<endl;

        cout << "Entrez un choix : ";
        cin >> option;

        if (option=="1")
        {
                system("clear");
                Profil = Profil.seConnecter();
        }
        else if (option=="2")
        {
                system("clear");
                Profil = Profil.Inscription();
        }

        else
        {
                return 0;
        }
        Profil.afficherGalerie();
        */
        return 0;
}