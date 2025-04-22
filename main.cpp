#include "main.h"
#include "pokemon/pokemon.h"
#include "pokemon/feu.h"

Pokemon* creerPokemonDepuisLigne(const string& ligneCSV) {
    stringstream ss(ligneCSV);
    string nom, t1, t2, pvStr, attaque, degatStr;

    getline(ss, nom, ',');
    getline(ss, t1, ',');
    getline(ss, t2, ',');
    getline(ss, pvStr, ',');
    getline(ss, attaque, ',');
    getline(ss, degatStr, ',');

    int pv = stoi(pvStr);
    int degat = stoi(degatStr);

    if (t1 == "Feu") return new Feu(nom, t2, pv, attaque, degat);
    //ajouter les differents types;

    return nullptr;
}

main()
{
    vector<Pokemon*> pokemons;
    ifstream fichier("data/pokemon.csv");
    string ligne;

    getline(fichier, ligne);//saute l'entete

    while (getline(fichier, ligne)) {
        Pokemon* p = creerPokemonDepuisLigne(ligne);
        if (p != nullptr)
            pokemons.push_back(p);
    }
    //for (Pokemon* p : pokemons) {
    //    p->afficher();
    //}
    pokemons[0]->afficher_Mult();
}

//g++ main.cpp entraineur/entraineur.cpp entraineur/joueur.cpp pokemon/feu.cpp pokemon/pokemon.cpp -o main