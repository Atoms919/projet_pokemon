#include "entraineur.h"

string* Entraineur::getNom() const {return nom;};
vector<Pokemon*>& Entraineur::getListe_pokemon() {return liste_pokemon;};

void Entraineur::interagir() const {
    cout << *nom << " pense que tu as un grand potentiel" << endl;    
};

Entraineur::Entraineur(string* n, vector<Pokemon*> lp){
    nom = n;
    liste_pokemon = lp;
};

