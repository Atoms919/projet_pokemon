#include "combat.h"


Combat::Combat(Joueur& j, Entraineur& e) : joueur(j), adversaire(e) {}

Joueur& Combat::getJoueur() {
    return joueur;
}

Entraineur& Combat::getEntraineur() {
    return adversaire;
}

void Combat::setJoueur(Joueur& v) {
    joueur = v;
}

void Combat::setEntraineur(Entraineur& v) {
    adversaire = v;
}

void afficherVie(Pokemon* p) {
    int pv_actuel = p->getPv();
    int pv_max = p->getPvMax();
    int barre = 20; // Longueur de la barre d'affichage
    int remplissage = (pv_actuel * barre) / pv_max;

    cout << "[";
    for (int i = 0; i < remplissage; ++i) cout << "-";
    for (int i = remplissage; i < barre; ++i) cout << " ";
    cout << "] (" << pv_actuel << "/" << pv_max << " PV)" << endl;
}

void pause(int milliseconds) {
    clock_t end_time = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    while (clock() < end_time) ;
}

bool Combat::demarrer() {
    cout << "===============================" << endl;
    cout << "Debut du combat entre " << *joueur.getNom() << " et " << *adversaire.getNom() << " !" << endl;
    cout << "===============================" << endl;

    vector<Pokemon*> equipe_joueur = joueur.getListe_pokemon();
    vector<Pokemon*> equipe_adversaire = adversaire.getListe_pokemon();

    int idx_joueur = 0;
    int idx_adv = 0;

    while (idx_joueur < equipe_joueur.size() && idx_adv < equipe_adversaire.size()) {
        Pokemon* p_joueur = equipe_joueur[idx_joueur];
        Pokemon* p_adv = equipe_adversaire[idx_adv];

        cout << "\n" << *joueur.getNom() << " utilise " << *p_joueur->getNom() << " !" << endl;
        cout << *adversaire.getNom() << " utilise " << *p_adv->getNom() << " !" << endl;

        pause(400);
        while (p_joueur->getPv() > 0 && p_adv->getPv() > 0) {
            // Joueur attaque
            cout << *p_joueur->getNom() << " attaque " << *p_adv->getNom() << " !" << endl;
            p_joueur->attaquer(p_adv);
            cout << "[Joueur]"<<*p_joueur->getNom() << " : ";
            afficherVie(p_joueur);
            cout << "[Leader]"<< *p_adv->getNom() << " : ";
            afficherVie(p_adv);

            pause(400);
            
            if (p_adv->getPv() <= 0) {
                cout << *p_adv->getNom() << " est K.O !" << endl;
                idx_adv++;
                break;
            }

            // Adversaire attaque   
            cout << *p_adv->getNom() << " attaque " << *p_joueur->getNom() << " !" << endl;
            p_adv->attaquer(p_joueur);

            cout << "[Joueur]"<<*p_joueur->getNom() << " : ";
            afficherVie(p_joueur);
            cout << "[Leader]"<< *p_adv->getNom() << " : ";
            afficherVie(p_adv);

            pause(400);

           
            if (p_joueur->getPv() <= 0) {
                cout << *p_joueur->getNom() << " est K.O !" << endl;
                idx_joueur++;
                break;
            }
        }
    }

    // Fin du combat
    if (idx_joueur >= equipe_joueur.size()) {
        cout << "\nDéfaite... " << *adversaire.getNom() << " t'a vaincu !" << endl;
        joueur.setNb_defaite(joueur.getNb_defaite() + 1);
        return false;
    } else {
        cout << "\nVictoire ! Tu as battu " << *adversaire.getNom() << " !" << endl;
        joueur.setNb_victoire(joueur.getNb_victoire() + 1);
        return true;
    }
}
