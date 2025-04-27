#pragma once 
#include "main.h"
#include "entraineur/entraineur.h"
#include "entraineur/joueur.h"

class Combat {
private: 
    Joueur& joueur;         // Référence au joueur
    Entraineur& adversaire; // Référence à l'adversaire

public:
    Combat(Joueur& j, Entraineur& e);

    Joueur& getJoueur();
    Entraineur& getEntraineur();

    void setJoueur(Joueur& v);
    void setEntraineur(Entraineur& v);

    bool demarrer(); // Lancer le combat
};
