#ifndef NEUTRALCARDS_H
#define NEUTRALCARDS_H

#include <string>
#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class NeutralCards:public Card
{
    public:
        NeutralCards(int c, int e, string n, string d, int a, int h);
        NeutralCards(int );
        void printStats();
        virtual ~NeutralCards();
        Card* reset();

        static string names[];
        static string description[];
        static int attackStat[];
        static int healthStat[];
        static int costStat[];
};

#endif // NEUTRALCARDS_H
