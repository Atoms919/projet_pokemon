#include "feu.h"

Feu::Feu(const string& nom, const string& t2, int pv, const string& attaque, int degat) : Pokemon(nom,"Feu",t2,pv,attaque,degat){};
string* Feu::getType() const {return new string("Feu");};

void Feu::attaquer(Pokemon* cible)
{
    int pv = cible->getPv();
    map<string, float> mult = cible->multiplicateur_attaque();
    int degat_attaque = degat*mult["Feu"];
    int pv_final = pv - degat_attaque;
    if (pv_final<0) pv_final = 0;
    cible->setPv(pv_final);
    if(mult["Feu"]>1)
    {
        cout<<"C'est super efficace (x"<<mult["Feu"]<<")! ";
    }
    else if (mult["Feu"]<1)
    {
        cout<<"C'est peu efficace (x"<<mult["Feu"]<<")! ";
    }
    cout<<"Cette attaque inflige "<<degat_attaque<<" degats."<<endl;
};

void Feu::interagir() const{
    cout << "🔥 ["<<*nom<<"] crache une petite flamme pour te montrer son affection." << endl;
}