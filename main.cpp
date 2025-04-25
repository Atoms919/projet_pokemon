#include "main.h"
#include "pokemon/pokemon.h"
#include "pokemon/feu.h"
#include "entraineur/joueur.h"
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

void AfficheStat(vector<Pokemon*> equipe){
    for(Pokemon* p: equipe){ //pas encore faire si 2 type
        p->afficher();
    
    }
};

//devrait faire un attribut pv max
void RecupPv(vector<Pokemon*> pokemon){

} 

int main()
{
    // vector<Pokemon*> pokemons;
    // ifstream fichier("data/pokemon.csv");
    // string ligne;

    getline(fichier, ligne);//saute l'entete

    // while (getline(fichier, ligne)) {
    //     Pokemon* p = creerPokemonDepuisLigne(ligne);
    //     if (p != nullptr)
    //         pokemons.push_back(p);
    // }
    // //for (Pokemon* p : pokemons) {
    // //    p->afficher();
    // //}
    // pokemons[0]->afficher_Mult();

    Pokemon* salameche = new Feu("Salamèche","Feu",39,"Flammèche",70);
    vector<Pokemon*> equipe;
    equipe.push_back(salameche);

    Joueur* sacha = new Joueur("sacha", equipe, 0,0,0);

    AfficheStat(equipe);
  
    return 0;

};

//g++ main.cpp entraineur/entraineur.cpp entraineur/joueur.cpp pokemon/feu.cpp pokemon/pokemon.cpp -o main