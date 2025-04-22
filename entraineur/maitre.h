#pragma once 
#include "../main.h"
#include "entraineur.h"

class Maitre: public Entraineur{
    private: 
        double boost; 
    public:
        double getBoost() const;
        void setBoost(double val);

        Maitre(const string& nom, vector<Pokemon*> equipe, double b);

};