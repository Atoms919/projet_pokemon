#pragma once
#include "pokemon.h"

class Feu : public Pokemon
{
    public:
        Feu(const string& nom, const string& t2, int pv, const string& attaque, int degat);

        string* getType() const override;

        void attaquer(Pokemon* cible) override; 
};
