#include "feu.h"

Feu::Feu(const string& nom, const string& t2, int pv, const string& attaque, int degat) : Pokemon(nom,"Feu",t2,pv,attaque,degat){};
string* Feu::getType() const {return new string("Feu");};

void Feu::attaquer(Pokemon* cible, float boost)
{
    int pv = cible->getPv();
    map<string, float> mult = cible->multiplicateur_attaque();
    int degat_attaque = degat*mult["Feu"]*boost;
    int pv_final = pv - degat_attaque;
    if (pv_final<0) pv_final = 0;
    cible->setPv(pv_final);
    if(mult["Feu"]>1)
    {
        cout<<"C'est super efficace (x"<<mult["Feu"]<<")! "<<endl;
    }
    else if (mult["Feu"]<1)
    {
        cout<<"C'est peu efficace (x"<<mult["Feu"]<<")! "<<endl;
    }
    if (boost != 1)
    {
        cout<<"Le pokemon est boosté son attaque infligera donc x"<<boost<<" degats!"<<endl;
        cout<<"Boost total : x"<<boost*mult["Feu"]<<endl;
    }
    cout<<"Cette attaque inflige "<<degat_attaque<<" degats."<<endl;
};

void Feu::interagir() const{
    cout << "🔥 ["<<*nom<<"] crache une petite flamme pour te montrer son affection." << endl;
}