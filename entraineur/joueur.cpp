#include "joueur.h"
#include "entraineur.h"

int Joueur::getNb_badge() const{return nb_badge;};
int Joueur::getNb_victoire() const{return nb_victoire;};
int Joueur::getNb_defaite() const{return nb_defaite;};
void Joueur::setNb_badge(int nb){nb_badge=nb;};
void Joueur::setNb_victoire(int nb){nb_victoire=nb;};
void Joueur::setNb_defaite(int nb){nb_defaite=nb;};

Joueur::Joueur(const string& nom, vector<Pokemon*> equipe, int badge, int victoire, int defaite):
Entraineur(new string(nom), equipe){
    nb_badge = badge;
    nb_victoire = victoire;
    nb_defaite = defaite;
};