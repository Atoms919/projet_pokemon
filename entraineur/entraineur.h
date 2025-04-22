#pragma once
#include "../main.h"
#include "../pokemon/pokemon.h"

class Entraineur
{
    protected:
        string* nom;
        vector<Pokemon*> liste_pokemon;
    public:
        string* getNom() const;
        vector<Pokemon*> getListe_pokemon() const;
        Entraineur(string* n, vector<Pokemon*> lp);
};