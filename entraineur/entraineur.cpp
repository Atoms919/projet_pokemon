#include "entraineur.h"

string* Entraineur::getNom() const {return nom;};
vector<Pokemon*> Entraineur::getListe_pokemon() const {return liste_pokemon;};
Entraineur::Entraineur(string* n, vector<Pokemon*> lp){
    nom = n;
    liste_pokemon = lp;
};