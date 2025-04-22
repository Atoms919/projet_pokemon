#include "maitre.h"

double Maitre::getBoost() const{
    return boost;
};

void Maitre::setBoost(double val){
    boost = val;
};

Maitre::Maitre(const string& nom, vector<Pokemon*> equipe, double b):
Entraineur(new string(nom), equipe){
    boost = b;
};