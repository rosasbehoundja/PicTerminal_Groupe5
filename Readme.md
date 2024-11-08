# PicTerminal 📸

## Description

PicTerminal est une application CLI (Command Line Interface) pour l'administration d'une plateforme de téléchargement d'images, inspirée de services populaires tels que Pixabay, Iwaria et Unsplash. Cette solution permet de gérer efficacement une bibliothèque d'images via une interface en ligne de commande.

## Fonctionnalités

- 👤 Gestion des utilisateurs (inscription, connexion)
- 📥 Téléchargement d'images
- 🔑 Système de droits d'accès (administrateur/utilisateur)
- 📊 Suivi des téléchargements
- 💜 Gestion des favoris
- 🚩 Gestion des Categories

## Prérequis

- Git
- Compilateur C++ (GCC recommandé)
- Code::Blocks (Editeur recommande)
- Make (optionnel)

## Installation

1. Clonez le dépôt :
```bash
git clone https://github.com/rosasbehoundja/PicTerminal.git
cd PicTerminal
```

2. Compilez le projet :
```bash
# Instructions de compilation à venir
```

## Contribution

Pour contribuer au projet, veuillez suivre ces étapes :

1. Créez et basculez sur une nouvelle branche :
```bash
git branch <NOM_DE_VOTRE_BRANCHE>
git checkout <NOM_DE_VOTRE_BRANCHE>
```
   ou en une seule commande :
```bash
git checkout -b <NOM_DE_VOTRE_BRANCHE>
```

2. Effectuez vos modifications

3. Committez et poussez vos changements :
```bash
git add .
git commit -m "Description détaillée de vos modifications"
git push -u origin <NOM_DE_VOTRE_BRANCHE>
```

4. Créez une Pull Request sur GitHub

## Structure du Projet

```
PicTerminal/
├── src/
│   ├── Administrateur.cpp
│   ├── Image.cpp
│   └── Utilisateur.cpp
├── include/
│   ├── Administrateur.h
│   ├── Iamge.h
│   └── Htilisateur.h
├── data/
│   ├── categories.csv
│   ├── favoris.csv
│   ├── images.csv
│   └── users.csv
├── main.cpp
└── Readme.md

```

## Licence

Ce projet est sous licence [à spécifier]

## Contact

- Auteur :  Rosas Behoundja
- Email : [Rosas Perrier](perrierosas@gmail.com)
- GitHub : [@rosasbehoundja](https://github.com/rosasbehoundja)

## Remerciements

Merci à tous les contributeurs qui participent à l'amélioration de ce projet.

---
⚠️ Ce projet est en développement actif. N'hésitez pas à signaler des bugs ou à proposer des améliorations via les issues GitHub.