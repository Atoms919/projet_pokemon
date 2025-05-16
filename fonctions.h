#include "main.h"
#include "pokemon/pokemon.h"
#include "entraineur/joueur.h"
#include "pokemon/feu.h"
#include "pokemon/eau.h"
#include "pokemon/plante.h"
#include "entraineur/leader_gym.h"
#include "combat.h"
#include "entraineur/maitre.h"



map<string, Pokemon*> chargerPokedex(const string& nomFichier) {
    map<string, Pokemon*> pokedex;
    ifstream fichier(nomFichier);
    string ligne;
    getline(fichier, ligne); // sauter l'en-tête

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string nom, t1, t2, pvStr, attaque, degatStr;

        getline(ss, nom, ',');
        getline(ss, t1, ',');
        getline(ss, t2, ',');
        getline(ss, pvStr, ',');
        getline(ss, attaque, ',');
        getline(ss, degatStr, ',');

        int pv = stoi(pvStr);
        int degat = stoi(degatStr);

        Pokemon* p = nullptr;
        if (t1 == "Feu") p = new Feu(nom, t2, pv, attaque, degat);
        else if (t1 == "Eau") p = new Eau(nom, t2, pv, attaque, degat);
        else if (t1 == "Plante") p = new Plante(nom, t2, pv, attaque, degat);
        // ➕ ajouter autres types ici

        if (p != nullptr)
            pokedex[nom] = p;
    }

    return pokedex;
}

Pokemon* copierDepuisPokedex(const string& nom, const map<string, Pokemon*>& pokedex) {
    if (pokedex.count(nom)) {
        Pokemon* original = pokedex.at(nom);
        if (Feu* f = dynamic_cast<Feu*>(original)) return new Feu(*f);
        if (Eau* e = dynamic_cast<Eau*>(original)) return new Eau(*e);
        if (Plante* p = dynamic_cast<Plante*>(original)) return new Plante(*p);
    }
    return nullptr;
}


vector<Leader_Gym*> chargerLeadersDepuisCSV(const string& nomFichier, const map<string, Pokemon*>& pokedex) {
    vector<Leader_Gym*> leaders;
    ifstream fichier(nomFichier);
    string ligne;

    getline(fichier, ligne); // sauter l'entête

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string nom, gymnase, medaille;
        vector<Pokemon*> equipe;
        string champ;

        getline(ss, nom, ',');
        getline(ss, gymnase, ',');
        getline(ss, medaille, ',');

        while (getline(ss, champ, ',')) {
            if (!champ.empty() && pokedex.count(champ)) {
                Pokemon* copie = copierDepuisPokedex(champ, pokedex);
                if (copie) equipe.push_back(copie);
            }
        }

        leaders.push_back(new Leader_Gym(nom, equipe, medaille, gymnase));
    }

    return leaders;
}

vector<Maitre*> chargerMaitresDepuisCSV(const string& nomFichier, const map<string, Pokemon*>& pokedex) {
    vector<Maitre*> maitres;
    ifstream fichier(nomFichier);
    string ligne;

    getline(fichier, ligne); // sauter l'entête

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string nom;
        vector<Pokemon*> equipe;
        string champ;

        getline(ss, nom, ',');     

        while (getline(ss, champ, ',')) {
            if (!champ.empty() && pokedex.count(champ)) {
                Pokemon* copie = copierDepuisPokedex(champ, pokedex);
                if (copie) equipe.push_back(copie);
            }
        }

        maitres.push_back(new Maitre(nom, equipe, 1.25));
    }

    return maitres;
}



vector<Joueur*> chargerJoueursDepuisCSV(const string& nomFichier, const map<string, Pokemon*>& pokedex) {
    vector<Joueur*> joueurs;
    ifstream fichier(nomFichier);
    string ligne;

    getline(fichier, ligne); // sauter l'en-tête

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string nom, champ;
        vector<Pokemon*> equipe;

        getline(ss, nom, ',');

        while (getline(ss, champ, ',')) {
            if (!champ.empty() && pokedex.count(champ)) {
                Pokemon* copie = copierDepuisPokedex(champ, pokedex);
                if (copie) equipe.push_back(copie);
            }
        }

        // Valeurs de base : 0 badge, 0 victoire, 0 défaite
        joueurs.push_back(new Joueur(nom, equipe, 0, 0, 0));
    }

    return joueurs;
}



void AfficheStatPokemon(vector<Pokemon*> equipe){
    for(Pokemon* p: equipe){ 
        p->afficher();
    
    }
};

void RecupPv(vector<Pokemon*> equipe){
    for(Pokemon* p: equipe){
        p->setPv(p->getPvMax());
    }
};

void ChangerOrdre(vector<Pokemon*>& equipe, int idx1, int idx2){
    Pokemon* tmp = equipe[idx1];
    equipe[idx1] = equipe[idx2];
    equipe[idx2] = tmp;
}

void AfficherStatJoueur(Joueur* j1){
    cout << "Nombre de badge gagne: " << j1->getNb_badge() << endl;
    cout << "Nombre de victoire: " << j1->getNb_victoire() << endl;
    cout << "Nombre de défaite: " << j1->getNb_defaite() << endl;

};

// Fonction pour lancer une musique en arrière-plan
void playMusic(const string& filepath) {
    string command = "start \"musiquePokemon\" /min ffplay.exe -nodisp -autoexit \"" + filepath + "\"";
    system(command.c_str());
}

// Fonction pour arrêter la musique en cours
void stopMusic() {
    system("taskkill /IM ffplay.exe /F >nul 2>&1");
}