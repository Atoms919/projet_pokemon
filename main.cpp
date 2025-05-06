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
        string nom, badge;
        vector<Pokemon*> equipe;
        string champ;

        getline(ss, nom, ',');     // nom du maître
        getline(ss, badge, ',');   // badge ou titre (ex: "Pokémon Champion")

        while (getline(ss, champ, ',')) {
            if (!champ.empty() && pokedex.count(champ)) {
                Pokemon* copie = copierDepuisPokedex(champ, pokedex);
                if (copie) equipe.push_back(copie);
            }
        }

        maitres.push_back(new Maitre(nom, equipe, 0.25));
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
    for(Pokemon* p: equipe){ //pas encore faire si 2 type
        p->afficher();
    
    }
};

void RecupPv(vector<Pokemon*> equipe){
    for(Pokemon* p: equipe){
        p->setPv(p->getPvMax());
    }
};

//sans & modifie une copie
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

//void AffronterGymnase()

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

void afficherMenu() {
    cout << CYAN << "===============================" << RESET << endl;
    cout << BOLD << "         MENU PRINCIPAL        " << RESET << endl;
    cout << CYAN << "===============================" << RESET << endl;
    cout << GREEN << "1. Afficher equipe" << RESET << endl;
    cout << GREEN << "2. Soigner les Pokemon" << RESET << endl;
    cout << GREEN << "3. Changer ordre des Pokemon" << RESET << endl;
    cout << GREEN << "4. Voir les stats du joueur" << RESET << endl;
    cout << GREEN << "5. Affronter un gymnase" << RESET << endl;
    cout << GREEN << "6. Affronter un maitre" << RESET << endl;
    cout << GREEN << "7. Interagir avec les Pokemons ou entraineurs vaincus" << RESET << endl;
    cout << GREEN << "8. Changer de joueur" << RESET << endl;

    cout << YELLOW << "0. Quitter" << RESET << endl;
    cout << CYAN << "===============================" << RESET << endl;
    cout << "Votre choix : ";
}

void pause() {
    cout << "\nAppuyez sur Entrée pour revenir au menu...";
    cin.ignore(1000, '\n');
    cin.get();
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    
    map<string, Pokemon*> pokedex = chargerPokedex("data/pokemon.csv");
    vector<Leader_Gym*> tousLesLeaders = chargerLeadersDepuisCSV("data/leaders.csv", pokedex);
    vector<Joueur*> tousLesJoueurs = chargerJoueursDepuisCSV("data/joueur.csv", pokedex);
    Joueur* joueurActif = tousLesJoueurs[0]; // Par défaut : Sacha
    vector<Maitre*> maitres = chargerMaitresDepuisCSV("data/maitres.csv", pokedex);

    int choix;
    do {
        afficherMenu();
        cin >> choix;
    
        switch(choix){
            case 1: 
                AfficheStatPokemon(joueurActif->getListe_pokemon());
                pause();
                break;
    
            case 2:
                RecupPv(joueurActif->getListe_pokemon());
                cout << "Les pokemons ont ete soignes" << endl;
                pause();
                break;
    
            case 3:
                int i1, i2;
                cout << "Entrer indice du premier Pokemon & echanger (0 à " << joueurActif->getListe_pokemon().size()-1 << ") : ";
                cin >> i1;
                cout << "Et maintenant indice du second Pokemon : ";
                cin >> i2;
                ChangerOrdre(joueurActif->getListe_pokemon(), i1, i2);
                pause();
                break;
    
            case 4:
                AfficherStatJoueur(joueurActif);
                pause();
                break;
    
            case 5:
                cout << "\nChoisis un gymnase à affronter :" << endl;
                for (size_t i = 0; i < tousLesLeaders.size(); ++i) {
                    cout << i + 1 << ". " << *tousLesLeaders[i]->getNom()
                         << " - " << tousLesLeaders[i]->getGymnase() << endl;
                }
    
                cout << "0. Retour" << endl;
                int choix5;
                cin >> choix5;
    
                if (choix5 > 0 && choix5 <= tousLesLeaders.size()) {
                    Leader_Gym* leaderChoisi = tousLesLeaders[choix5 - 1];
                    Combat* c = new Combat(*joueurActif, *leaderChoisi);
                    c->demarrer();
                    RecupPv(leaderChoisi->getListe_pokemon());
                } else {
                    cout << "Retour au menu principal." << endl;
                }
                pause();
                break;
    
            case 6:
                    cout << joueurActif->getNb_badge() << " badge(s) obtenu(s)." << endl;

                    if (joueurActif->getNb_badge() == tousLesLeaders.size()) {
                        cout << "\nChoisis un maître à affronter :" << endl;
                    
                        for (size_t i = 0; i < maitres.size(); ++i) {
                            cout << i + 1 << ". " << *maitres[i]->getNom() << endl;
                        }
                    
                        cout << "0. Retour" << endl;
                        int choixMaitre;
                        cin >> choixMaitre;
                
                    if (choixMaitre > 0 && choixMaitre <= maitres.size()) {
                        Maitre* maitreChoisi = maitres[choixMaitre - 1];
                        Combat* c = new Combat(*joueurActif, *maitreChoisi);
                        c->demarrer();
                        RecupPv(maitreChoisi->getListe_pokemon());
                    } else {
                        cout << "Retour au menu principal." << endl;
                    }
                
                } else {
                    cout << "\nVous n'avez pas obtenu tous les badges pour affronter un maître." << endl;
                }
                pause();
                break;
            
            case 7:
                int choixInteragir;
                cout << "7. Interagir avec Pokémon ou Entraîneur vaincu" << endl;
                cout << "-> 1. Interagir avec un Pokémon" << endl;
                cout << "-> 2. Interagir avec un Leader vaincu" << endl;
                cout << "Votre choix : ";
                cin >> choixInteragir;
    
                if (choixInteragir == 1) {
                    int choixPokemon;
                    cout << "Sélectionner un Pokémon :" << endl;
                    for (int i = 0; i < joueurActif->getListe_pokemon().size(); i++) {
                        cout << i + 1 << ". " << *joueurActif->getListe_pokemon()[i]->getNom() << endl;
                    }
                    cin >> choixPokemon;
                    joueurActif->getListe_pokemon()[choixPokemon - 1]->interagir();
                }
                else if (choixInteragir == 2) {
                    vector<Entraineur*> vaincus = joueurActif->getVaincus();
                    if (vaincus.empty()) {
                        cout << "Aucun leader vaincu pour l’instant." << endl;
                    } else {
                        cout << "Choisis un leader à saluer : " << endl;
                        for (int i = 0; i < vaincus.size(); ++i) {
                            cout << i + 1 << ". " << *vaincus[i]->getNom() << endl;
                        }
                        int choixLeader;
                        cin >> choixLeader;
                        vaincus[choixLeader - 1]->interagir();
                    }
                }
                pause();
                break;
    
            case 8:
                cout << "\nChoisissez un joueur parmi ceux disponibles :" << endl;
                for (size_t i = 0; i < tousLesJoueurs.size(); ++i) {
                    cout << i + 1 << ". " << *tousLesJoueurs[i]->getNom() << endl;
                }
                cout << "Votre choix : ";
                int choixJ;
                cin >> choixJ;
    
                if (choixJ >= 1 && choixJ <= tousLesJoueurs.size()) {
                    joueurActif = tousLesJoueurs[choixJ - 1];
                    cout << "Vous incarnez maintenant : " << *joueurActif->getNom() << endl;
                } else {
                    cout << "Choix invalide. Aucun changement effectué." << endl;
                }
                pause();
                break;
        }
    
    } while (choix != 0);
    

    return 0;

};

//g++ main.cpp entraineur/entraineur.cpp entraineur/joueur.cpp pokemon/feu.cpp pokemon/eau.cpp pokemon/plante.cpp pokemon/pokemon.cpp entraineur/leader_gym.cpp combat.cpp entraineur/maitre.cpp -o main