#include "leader_gym.h"

string Leader_Gym::getBadge() const{
    return badge;
};

string Leader_Gym::getGymnase() const{
    return gymnase;
};

void Leader_Gym::setBadge(string val){
    badge = val;
};

void Leader_Gym::setGymnase(string val){
    gymnase = val;
};

Leader_Gym:: Leader_Gym(const string& nom, vector<Pokemon*> equipe, string b, string g):
Entraineur(new string(nom), equipe){
    badge = b;
    gymnase = g;
};