#include "plante.h"

Plante::Plante(const string& nom, const string& t2, int pv, const string& attaque, int degat) : Pokemon(nom,"Plante",t2,pv,attaque,degat){};
string* Plante::getType() const {return new string("Plante");};

void Plante::attaquer(Pokemon* cible, float boost)
{
    int pv = cible->getPv();
    map<string, float> mult = cible->multiplicateur_attaque();
    int degat_attaque = degat*mult["Plante"]*boost;
    int pv_final = pv - degat_attaque;
    if (pv_final<0) pv_final = 0;
    cible->setPv(pv_final);
    if(mult["Plante"]>1)
    {
        cout<<"C'est super efficace (x"<<mult["Plante"]<<")! "<<endl;
    }
    else if (mult["Plante"]<1)
    {
        cout<<"C'est peu efficace (x"<<mult["Plante"]<<")! "<<endl;
    }
    if (boost != 1)
    {
        cout<<"Le pokemon est boosté son attaque infligera donc x"<<boost<<" degats!"<<endl;
        cout<<"Boost total : x"<<boost*mult["Plante"]<<endl;
    }
    cout<<"Cette attaque inflige "<<degat_attaque<<" degats."<<endl;
};

void Plante::interagir() const{
    cout << "🌿 ["<<*nom<<"] fait pousser une petite fleur à tes pieds en guise de salut." << endl;
}