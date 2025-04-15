#pragma once
#include "main.h"

class Pokemon
{
    protected :
        string* nom;
        string* type;
        int pv;
        string* attaque;
        int degat;
    public :
        string* getNom() const;
        string* getType() const;
        int getPv() const;
        string* getAttaque() const;
        int getDegat() const;
        void setPv(int pv);
};