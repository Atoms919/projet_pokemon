#include "eau.h"

Eau::Eau(const string& nom, const string& t2, int pv, const string& attaque, int degat) : Pokemon(nom,"Eau",t2,pv,attaque,degat){};
string* Eau::getType() const {return new string("Eau");};

void Eau::attaquer(Pokemon* cible, float boost)
{
    int pv = cible->getPv();
    map<string, float> mult = cible->multiplicateur_attaque();
    int degat_attaque = degat*mult["Eau"]*boost;
    int pv_final = pv - degat_attaque;
    if (pv_final<0) pv_final = 0;
    cible->setPv(pv_final);
    if(mult["Eau"]>1)
    {
        cout<<"C'est super efficace (x"<<mult["Eau"]<<")! "<<endl;
    }
    else if (mult["Eau"]<1)
    {
        cout<<"C'est peu efficace (x"<<mult["Eau"]<<")! "<<endl;
    }
    if (boost != 1)
    {
        cout<<"Le pokemon est boosté son attaque infligera donc x"<<boost<<" degats!"<<endl;
        cout<<"Boost total : x"<<boost*mult["Eau"]<<endl;
    }
    cout<<"Cette attaque inflige "<<degat_attaque<<" degats."<<endl;
};

void Eau::interagir() const{
    cout << "💧 ["<<*nom<<"] fait gicler de l’eau fraîche autour de toi, joyeux comme un poisson dans l’eau." << endl;
}