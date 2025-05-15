#pragma once
#include "pokemon.h"

class Eau : public Pokemon
{
    public:
        Eau(const string& nom, const string& t2, int pv, const string& attaque, int degat);

        string* getType() const override;

        void attaquer(Pokemon* cible, float boost = 1) override; 
        virtual void interagir() const override;

};