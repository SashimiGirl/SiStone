#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Card.h"
#include "NeutralCards.h"
#include "HunterCards.h"

using namespace std;

class Player
{
    public:
        Player(int = 0);
        virtual ~Player();

        void setDeck(int h);
        void shuffleDeck();
        void costIncrement();
        void operator-=(Player right);
        void takeDamage(int);

        Card* returnCard(int index);
        int returnCost() {return costMax;}
        int returnLife() {return lifePts;}
        int returnDamage() {return heroDamage;}

    private:
        Card *hero;
        int heroDamage;
        int lifePts;
        int costMax;
        vector<Card*> deck;
};

#endif // PLAYER_H
