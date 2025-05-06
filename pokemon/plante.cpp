#include "plante.h"

Plante::Plante(const string& nom, const string& t2, int pv, const string& attaque, int degat) : Pokemon(nom,"Plante",t2,pv,attaque,degat){};
string* Plante::getType() const {return new string("Plante");};

void Plante::attaquer(Pokemon* cible)
{
    int pv = cible->getPv();
    map<string, float> mult = cible->multiplicateur_attaque();
    int degat_attaque = degat*mult["Plante"];
    int pv_final = pv - degat_attaque;
    if (pv_final<0) pv_final = 0;
    cible->setPv(pv_final);
};

void Plante::interagir() const{
    cout << "🌿 ["<<*nom<<"] fait pousser une petite fleur à tes pieds en guise de salut." << endl;
}