#include "HunterCards.h"

HunterCards::~HunterCards()
{
    //dtor
}

HunterCards::HunterCards(int id)
:Card(0)
{
    Card::setEffect(6);
    if(id < SPECIALID && id >= 0)
    {
        setName(names[id]);
        setDescript(description[id]);
//        setDamage(damageStat[id]);
        setCost(costStat[id]);
    }
    else if(id == -1)
    {
        setName("Da shot");
        setDescript("Deal 2 damage to enemy hero.");
//        setDamage(2);
        setCost(2);
    }
    else
        cout << "invalid id..." << id << endl;
}

/*
HunterCards::~HunterCards()
{
    //dtor
}
*/
string HunterCards::names[SPECIALID] = {"No Need Aim", "Two birds... Three stones", "Eye on the Target", "Shoot 'em", "Spray-shot"};
string HunterCards::description[SPECIALID] = {"Destroy a random enemy minion.", "Deal 3 damage to two random enemy minions.",
                                            "Change 1 minion's Health to 1.", "Deal 2 damage.",
                                            "Deal 5 damage to a minion and 2 damage to adjacent ones."};
//int HunterCards::damageStat[SPECIALID] = {-1, 3, 0, 2, 5};
int HunterCards::costStat[SPECIALID]   = {3, 4, 1, 1, 5};

