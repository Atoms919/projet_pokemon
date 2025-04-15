#include "feu.h"

Feu::Feu(const string& nom, const string& t2, int pv, const string& attaque, int degat) : Pokemon(nom,"Feu",t2,pv,attaque,degat){};
string* Feu::getType() const {return new string("Feu");};