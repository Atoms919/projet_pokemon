#pragma once
#include "entraineur.h"
#include "../main.h"

class Joueur : public Entraineur
{
    private:
        int nb_badge;
        int nb_victoire;
        int nb_defaite;
        vector<string> leaders_vaincus; 

    public:
        int getNb_badge() const;
        int getNb_victoire() const;
        int getNb_defaite() const;
        void setNb_badge(int nb);
        void setNb_victoire(int nb);
        void setNb_defaite(int nb);

        bool aVaincu(string nomLeader) const;
        void ajouterLeaderVaincu(string nomLeader);

        bool besoinSoin();

        Joueur(const string& nom, vector<Pokemon*> equipe, int badge, int victoire, int defaite);
};