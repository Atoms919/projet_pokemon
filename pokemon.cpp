#include "pokemon.h"

string* Pokemon::getNom() const {return nom;};
string* Pokemon::getType() const {return type;};
int Pokemon::getPv() const {return pv;};
string* Pokemon::getAttaque() const {return attaque;};
int Pokemon::getDegat() const {return degat;};
void Pokemon::setPv(int pv) {this->pv = pv;};