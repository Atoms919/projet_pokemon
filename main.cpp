#include "main.h"
#include "pokemon/pokemon.h"
#include "pokemon/feu.h"
#include "entraineur/joueur.h"
#include "pokemon/feu.h"
#include "pokemon/eau.h"
#include "entraineur/leader_gym.h"
#include "combat.h"
#include "entraineur/maitre.h"



Pokemon* creerPokemonDepuisLigne(const string& ligneCSV) {
    stringstream ss(ligneCSV);
    string nom, t1, t2, pvStr, attaque, degatStr;

    getline(ss, nom, ',');
    getline(ss, t1, ',');
    getline(ss, t2, ',');
    getline(ss, pvStr, ',');
    getline(ss, attaque, ',');
    getline(ss, degatStr, ',');

    int pv = stoi(pvStr);
    int degat = stoi(degatStr);

    if (t1 == "Feu") return new Feu(nom, t2, pv, attaque, degat);
    //ajouter les differents types;

    return nullptr;
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
    cout << "Nombre de badge gagne: " << j1->getNb_victoire() << endl;
    cout << "Nombre de badge gagne: " << j1->getNb_defaite() << endl;

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
    // vector<Pokemon*> pokemons;
    // ifstream fichier("data/pokemon.csv");
    // string ligne;

    //getline(fichier, ligne);//saute l'entete

    // while (getline(fichier, ligne)) {
    //     Pokemon* p = creerPokemonDepuisLigne(ligne);
    //     if (p != nullptr)
    //         pokemons.push_back(p);
    // }
    // //for (Pokemon* p : pokemons) {
    // //    p->afficher();
    // //}
    // pokemons[0]->afficher_Mult();Carapuce,Eau,,44,Pistolet à O,65


    Pokemon* salameche = new Feu("Salameche","Feu",300,"Flammeche",70);
    Pokemon* carapuce = new Eau("Carapuce","Eau",400,"Pistolet à O",65);

    Pokemon* carabaffe = new Eau("Carabaffe","Eau",59,"Hydrocanon",80);
    Pokemon* tortank = new Eau("Tortank","Eau",79,"Hydroblast",105);


    vector<Pokemon*> equipe;
    equipe.push_back(salameche);
    equipe.push_back(carapuce);

    vector<Pokemon*> equipe2;
    equipe2.push_back(carabaffe);
    equipe2.push_back(tortank);

    Joueur* sacha = new Joueur("sacha", equipe, 0,0,0);
    
    // AfficheStatPokemon(equipe);
    // ChangerOrdre(equipe, 0 ,1);
    // AfficheStatPokemon(equipe);
    // AfficherStatJoueur(sacha);

    
    Leader_Gym* pierre = new Leader_Gym("pierre", equipe2, "Roche", "Bleu");

    vector<Leader_Gym*> leaders;
    leaders.push_back(pierre);
    int choix;

    Pokemon* p1 = new Eau("Nidoran♀","Poison",55,"Dard-Venin",60);
    Pokemon* p2 = new Eau("Nidoran♀","Poison",55,"Dard-Venin",60);

    vector<Pokemon*> equipeMaitre;
    equipeMaitre.push_back(p1);
    equipeMaitre.push_back(p2);

    Maitre* regis = new Maitre("Regis", equipeMaitre, 0.25);
    vector<Maitre*> masters;
    masters.push_back(regis);
    do{ 
        afficherMenu();
        cin >> choix;
        

        switch(choix){
            case 1: 
                AfficheStatPokemon(equipe);
                pause();
                break;
            case 2:
                RecupPv(equipe);
                cout << "Les pokemons ont ete soignes" << endl;
                pause();
                break;
            case 3:
            int i1, i2;
                cout << "Entrer indice du premier Pokemon & echanger (0 à " << equipe.size()-1<< ") : ";
                cin >> i1;
                cout << "Et maintenant indice du second Pokemon : ";
                cin >> i2;
     
                ChangerOrdre(equipe, i1, i2);
                pause();
                break;
            case 4:
                AfficherStatJoueur(sacha);
                pause();
                break;

            case 5:
                cout << "\n Choisis un gymnase à affronter"<<endl;

                for(int i = 0; i <leaders.size(); i++){
                    cout << i+1 <<". "<< *leaders[i]->getNom() << " (" << leaders[i]->getBadge()<<")"<<endl; //getNom retourn un string donc *
                }
                cout << "0. Retour" << endl;
                int choix5;
                cin >> choix5;
                if(choix5> 0 && choix5<=leaders.size()){
                    Combat* c = new Combat(*sacha, *leaders[choix5 -1]);
                    (*c).demarrer();
                    RecupPv(equipe2); //obligatoire sinon rejoue contre pokemon 0pv => bug
                    
                }
                else {
                    cout << "Retour au menu principal." << endl;
                }
                pause();
                break;

            case 6: 
                cout << sacha->getNb_badge() <<endl;
                if(sacha->getNb_badge() == leaders.size()){
                    cout << "\n Choisis un maitre à affronter" << endl;
                    for(int i = 0; i<masters.size(); i ++){
                        Combat* c2 = new Combat(*sacha, *masters[i]);
                        c2->demarrer();
                        RecupPv(equipe2);
                    }

                } else {
                    cout <<"\n Vous n'avez pas obtenu tous les badges" << endl;
                }

                pause();
                break;
            
            case 7: 
                int choixInteragir;
                cout << "7. Interagir avec Pokémon ou Entraîneur vaincu" <<endl;
                cout << "➔ 1. Interagir avec un Pokémon" << endl;
                cout << "➔ 2. Interagir avec un Leader vaincu" << endl;
                cout << "votre choix: " << endl;

                cin >> choixInteragir;

                if(choixInteragir == 1){
                    int choixPokemon; 

                    cout << "Sélectionner un Pokemon: " <<endl;
                    for(int i = 0; i < sacha->getListe_pokemon().size();i++){
                        cout << i+1<<". " << *sacha->getListe_pokemon()[i]->getNom() << endl;

                    }
                    cin >> choixPokemon;
                    sacha->getListe_pokemon()[choixPokemon -1]->interagir();
                }
                pause();
                break;
                
                

        };

    } while (choix != 0);
    

    return 0;

};

//g++ main.cpp entraineur/entraineur.cpp entraineur/joueur.cpp pokemon/feu.cpp pokemon/pokemon.cpp -o main