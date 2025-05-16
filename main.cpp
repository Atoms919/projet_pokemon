#include "fonctions.h"


#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

void afficherMenu() {
    cout << CYAN << "===============================" << RESET << endl;
    cout << BOLD << "         MENU PRINCIPAL        " << RESET << endl;
    cout << CYAN << "===============================" << RESET << endl;
    cout << GREEN << "1. Afficher l'équipe" << RESET << endl;
    cout << GREEN << "2. Soigner les Pokémons" << RESET << endl;
    cout << GREEN << "3. Changer l'ordre des Pokémons" << RESET << endl;
    cout << GREEN << "4. Voir les stats du joueur" << RESET << endl;
    cout << GREEN << "5. Affronter un gymnase" << RESET << endl;
    cout << GREEN << "6. Affronter un maitre" << RESET << endl;
    cout << GREEN << "7. Interagir avec les Pokémons ou entraineurs vaincus" << RESET << endl;
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
    joueurActif->setNb_badge(tousLesLeaders.size()); //pour pouvoir affronter les maitres



    playMusic("musique/generique.mp3");
    int choix;
    do {
       
        afficherMenu();
        cin >> choix;
    
        switch(choix){
            case 1: 
                cout << CYAN << "===============================" << RESET << endl;
                cout << BOLD << "        AFFICHER EQUIPE        " << RESET << endl;
                cout << CYAN << "===============================" << RESET << endl;

                AfficheStatPokemon(joueurActif->getListe_pokemon());
                pause();
                break;
    
            case 2:
                cout << CYAN << "===============================" << RESET << endl;
                cout << BOLD << "     SOIGNER LES POKEMON       " << RESET << endl;
                cout << CYAN << "===============================" << RESET << endl;

                RecupPv(joueurActif->getListe_pokemon());
                cout << "Les pokémons ont été soignés" << endl;
                pause();
                break;
    
            case 3:
                cout << CYAN << "===============================" << RESET << endl;
                cout << BOLD << "  CHANGER ORDRE DES POKEMON    " << RESET << endl;
                cout << CYAN << "===============================" << RESET << endl;

                int i1, i2;
                cout << "Entrer indice du premier Pokemon à échanger (0 à " << joueurActif->getListe_pokemon().size()-1 << ") : ";
                cin >> i1;
                cout << "Et maintenant indice du second Pokemon : ";
                cin >> i2;
                ChangerOrdre(joueurActif->getListe_pokemon(), i1, i2);
                pause();
                break;
    
            case 4:
                cout << CYAN << "===============================" << RESET << endl;
                cout << BOLD << "   VOIR LES STATS DU JOUEUR    " << RESET << endl;
                cout << CYAN << "===============================" << RESET << endl;

                AfficherStatJoueur(joueurActif);
                pause();
                break;
    
            case 5:
                cout << CYAN << "===============================" << RESET << endl;
                cout << BOLD << "   AFFRONTER UN GYMNASE        " << RESET << endl;
                cout << CYAN << "===============================" << RESET << endl;

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
                    stopMusic();
                    playMusic("musique/combat_ost.mp3");

                    c->demarrer();
                    RecupPv(leaderChoisi->getListe_pokemon());
                } else {
                    cout << "Retour au menu principal." << endl;
                }

                stopMusic();
                playMusic("musique/generique.mp3");
                pause();
                break;
    
            case 6:
                    cout << CYAN << "===============================" << RESET << endl;
                    cout << BOLD << "   AFFRONTER UN MAITRE         " << RESET << endl;
                    cout << CYAN << "===============================" << RESET << endl;

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
                        stopMusic();
                        stopMusic();
                        playMusic("musique/combat-maitre.mp3");
                        c->demarrer();
                        RecupPv(maitreChoisi->getListe_pokemon());
                    } else {
                        cout << "Retour au menu principal." << endl;
                    }
                
                } else {
                    cout << "\nVous n'avez pas obtenu tous les badges pour affronter un maître." << endl;
                }

                stopMusic();
                playMusic("musique/generique.mp3");
                pause();
                break;
            
            case 7:
                cout << CYAN << "===============================" << RESET << endl;
                cout << BOLD << " INTERACTIONS POST-COMBAT      " << RESET << endl;
                cout << CYAN << "===============================" << RESET << endl;

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
                cout << CYAN << "===============================" << RESET << endl;
                cout << BOLD << "     CHANGER DE JOUEUR         " << RESET << endl;
                cout << CYAN << "===============================" << RESET << endl;

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
    
    stopMusic();

    return 0;

};

//g++ main.cpp entraineur/entraineur.cpp entraineur/joueur.cpp pokemon/feu.cpp pokemon/eau.cpp pokemon/plante.cpp pokemon/pokemon.cpp entraineur/leader_gym.cpp combat.cpp entraineur/maitre.cpp -o main