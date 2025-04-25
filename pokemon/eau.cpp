#include "eau.h"

Eau::Eau(const string& nom, const string& t2, int pv, const string& attaque, int degat) : Pokemon(nom,"Eau",t2,pv,attaque,degat){};
string* Eau::getType() const {return new string("Eau");};

void Eau::attaquer(Pokemon* cible)
{
    int pv = cible->getPv();
    map<string, float> mult = cible->multiplicateur_attaque();
    int degat_attaque = degat*mult["Eau"];
    int pv_final = pv - degat_attaque;
    if (pv_final<0) pv_final = 0;
    cible->setPv(pv_final);
};