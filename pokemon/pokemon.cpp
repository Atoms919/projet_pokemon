#include "pokemon.h"

string* Pokemon::getNom() const {return nom;};
int Pokemon::getPv() const {return pv;};
string* Pokemon::getAttaque() const {return attaque;};
int Pokemon::getDegat() const {return degat;};
void Pokemon::setPv(int pv) {this->pv = pv;};

Pokemon::Pokemon(const string& nom, const string& t1, const string& t2, int pv, const string& attaque, int degat) 
{
    this->nom = new string(nom);
    type1 = new string(t1);
    type2 = new string(t2);
    this->pv = pv;
    this->attaque = new string(attaque);
    this->degat = degat;
};

void Pokemon::afficher() const {
    cout << *nom << " (" << *type1;
    if (!type2->empty()) cout << "/" << *type2;
    cout << ") PV: " << pv << ", Attaque: " << *attaque << " (" << degat << ")"<<endl;
}


