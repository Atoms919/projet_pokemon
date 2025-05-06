#pragma once
#include "pokemon.h"

class Plante : public Pokemon
{
    public:
        Plante(const string& nom, const string& t2, int pv, const string& attaque, int degat);

        string* getType() const override;

        void attaquer(Pokemon* cible) override; 
        virtual void interagir() const override;

};


