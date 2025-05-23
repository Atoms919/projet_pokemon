#pragma once
#include "../main.h"
#include "faiblesse_resistance.h"
#include <string>
#include "../interagir.h"

class Pokemon: public Interagir
{
    protected :
        string* nom;
        string* type1;
        string* type2;
        int pv;
        int PvMax;
        string* attaque;
        int degat;
    public :
        virtual string* getType() const = 0;

        string* getNom() const;
        int getPv() const;
        int getPvMax() const;
        string* getAttaque() const;
        int getDegat() const;
        void setPv(int pv);

        Pokemon(const string& nom, const string& t1, const string& t2, int pv, const string& attaque, int degat);

        void afficher() const;

        map<string, float> multiplicateur_attaque() const;

        void afficher_Mult() const;
        map<string, float> getFaiblesses() const;
        map<string, float> getResistances() const;

        virtual void attaquer(Pokemon* cible, float boost = 1) = 0; 

        virtual void interagir() const override;
        
};