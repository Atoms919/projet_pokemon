#pragma once
#include "../main.h"
#include <string>

class Pokemon
{
    protected :
        string* nom;
        string* type1;
        string* type2;
        int pv;
        string* attaque;
        int degat;
    public :
        virtual string* getType() const = 0;

        string* getNom() const;
        int getPv() const;
        string* getAttaque() const;
        int getDegat() const;
        void setPv(int pv);

        Pokemon(const string& nom, const string& t1, const string& t2, int pv, const string& attaque, int degat);

        void afficher() const;
};