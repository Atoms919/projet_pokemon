#pragma once
#include "../main.h"
#include "../pokemon/pokemon.h"
#include "../interagir.h"

class Entraineur: public Interagir
{
    protected:
        string* nom;
        vector<Pokemon*> liste_pokemon;
    public:
        string* getNom() const;
        vector<Pokemon*>& getListe_pokemon();
        virtual void interagir() const override;

        Entraineur(string* n, vector<Pokemon*> lp);
};