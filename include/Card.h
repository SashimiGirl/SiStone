#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Card
{
    public:
        Card(int, int, string, string);
        Card(int = 0);
        virtual ~Card();
        void setCost(int = 0);
        void setEffect(int);
        void setEffect(string);
        void removeEffect(string);
        void setName(string n) {name = n;}
        void setDescript(string d) {descript = d;}
        void printEffects();
        void printStats();

        void takeDamage(int damage);
        void setAttack(int a) {attack = a;}
        void setHealthMax(int h) {healthMax = h;}
        void setDamC(int dc) {damCounter = dc;}
        void setHasAttack(int ha) {hasAttack = ha;}
        void clearEffects(){effects.clear();}
        Card operator=(Card *right);

        int getAttack() {return attack;}
        int getHealth() {return healthMax - damCounter;}
        int getHealthMax() {return healthMax;}
        int getHasAttack() {return hasAttack;}
        int getDamC() {return damCounter;}
        int getCost() {return cost;}
        string getName() {return name;}
        string getEffect(int i);
        string getDescript() {return descript;}

        static const int CARDID = 10;
        static const int SPECIALID = 5;
        static string keyEffects[];
    private:
        string name;
        string descript;
        int cost;
        int attack;
        int healthMax;
        int hasAttack;
        int damCounter;
        //int rarity;
        vector<string> effects;
};

#endif // CARD_H
