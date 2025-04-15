#pragma once
#include "entraineur.h"

class Joueur : public Entraineur
{
    private:
        int nb_badge;
        int nb_victoire;
        int nb_defaite;
    public:
        int getNb_badge() const;
        int getNb_victoire() const;
        int getNb_defaite() const;
        void setNb_badge(int nb);
        void setNb_victoire(int nb);
        void setNb_defaite(int nb);

        Joueur(const string& nom, vector<Pokemon*> equipe, int badge, int victoire, int defaite);
};