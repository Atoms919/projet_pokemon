#pragma once 
#include "../main.h"
#include "entraineur.h"

class Leader_Gym: public Entraineur{
    private:
        string badge;
        string gymnase;
    
    public:
        string getBadge() const;
        void setBadge(string val);
        string getGymnase() const;
        void setGymnase(string val);

        Leader_Gym(const string& nom, vector<Pokemon*> equipe, string b, string g);

};
