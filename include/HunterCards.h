#ifndef HUNTERCARDS_H
#define HUNTERCARDS_H

#include "Card.h"

using namespace std;

class HunterCards:public Card
{
    public:
        HunterCards(int = 0);
        virtual ~HunterCards();

        static string names[];
        static string description[];
        static int damageStat[];
        static int costStat[];
    private:
        //int damage;
        string heroEffect;
};
#endif // HUNTERCARDS_H
