#include "pokemon.h"

string* Pokemon::getNom() const {return nom;};
int Pokemon::getPv() const {return pv;};
string* Pokemon::getAttaque() const {return attaque;};
int Pokemon::getDegat() const {return degat;};
void Pokemon::setPv(int pv) {this->pv = pv;};

Pokemon::Pokemon(const string& nom, const string& t1, const string& t2, int pv, const string& attaque, int degat) 
{
    this->nom = new string(nom);
    type1 = new string(t1);
    type2 = new string(t2);
    this->pv = pv;
    this->attaque = new string(attaque);
    this->degat = degat;
};

void Pokemon::afficher() const {
    cout << *nom << " (" << *type1;
    if (!type2->empty()) cout << "/" << *type2;
    cout << ") PV: " << pv << ", Attaque: " << *attaque << " (" << degat << ")"<<endl;
}

map<string, float> Pokemon::multiplicateur_attaque() const{
    map<string, float> mult = {
        {"Feu", 1},
        {"Eau", 1},
        {"Plante", 1},
        {"Électrik", 1},
        {"Glace", 1},
        {"Combat", 1},
        {"Poison", 1},
        {"Sol", 1},
        {"Vol", 1},
        {"Psy", 1},
        {"Insecte", 1},
        {"Roche", 1},
        {"Spectre", 1},
        {"Dragon", 1},
        {"Ténèbres", 1},
        {"Acier", 1},
        {"Fée", 1}
    };

    vector<string> faiblesse_1 = FAIBLESSES.find(*type1)->second;
    vector<string> resistance_1 = RESISTANCES.find(*type1)->second;

    for (const string& type : faiblesse_1) {
        mult[type] *= 2.0;
    }
    for (const string& type : resistance_1) {
        mult[type] *= 0.5;
    }

    if(type2!=nullptr&&*type2!="")
    {
        vector<string> faiblesse_2 = FAIBLESSES.find(*type2)->second;
        vector<string> resistance_2 = RESISTANCES.find(*type2)->second;
        
        for (const string& type : faiblesse_2) {
            mult[type] *= 2.0;
        }
        for (const string& type : resistance_2) {
            mult[type] *= 0.5;
        }
    }

    return mult;
}

void Pokemon::afficher_Mult() const
{
    map<string, float> mult = multiplicateur_attaque();

    for (const auto& pair : mult)
    {
        cout << pair.first << " : " << pair.second << endl;
    }
}

map<string, float> Pokemon::getFaiblesses() const
{
    map<string, float> mult = multiplicateur_attaque();
    map<string, float> faiblesses;

    for (const auto& pair : mult)
    {
        if (pair.second > 1.0f)
        {
            faiblesses[pair.first] = pair.second;
        }
    }

    return faiblesses;
}

map<string, float> Pokemon::getResistances() const
{
    map<string, float> mult = multiplicateur_attaque();
    map<string, float> resistances;

    for (const auto& pair : mult)
    {
        if (pair.second < 1.0f)
        {
            resistances[pair.first] = pair.second;
        }
    }

    return resistances;
}

