#include "NeutralCards.h"

NeutralCards::NeutralCards(int c, int e, string n, string d, int a, int h)
:Card(c,e,n,d)
{
    setAttack(a);
    setHealthMax(h);
    //type = t;
}

NeutralCards::NeutralCards(int id)
:Card(0)
{
    if(id < CARDID)
    {
        setName(names[id]);
        setDescript(description[id]);
        setAttack(attackStat[id]);
        setHealthMax(healthStat[id]);
        setCost(costStat[id]);
        switch(id)
        {
        case 0:
            setEffect(0);
            break;
        case 1:
            setEffect(1);
            break;
        case 2:
        case 3:
        case 6:
        case 7:
            setEffect(2);
            break;
        case 4:
            setEffect("Play a card, gain +1/+1");
            break;
        case 8:
            setEffect("Your other minions have +1/+1");
            break;
        case 9:
            setEffect("Summon a minion, deal 1 damage to random enemy");
            break;
        case 5:
            setEffect(5);
            break;
        }
    }
    else
        cout << "invalid id..." << endl;
}

Card* NeutralCards::reset()
{
    int i = 0;
    while(this->getName() != NeutralCards::names[i])
        i++;
    this->setAttack(NeutralCards::attackStat[i]);
    this->setHealthMax(NeutralCards::healthStat[i]);
    while(this->getHealthMax() < this->getHealth())
    {
        this->setDamC(this->getDamC()-1);
    }
    return this;
}

NeutralCards::~NeutralCards()
{
    //dtor
}

string NeutralCards::names[CARDID] = {"Thomas the Tank", "Divine David", "Quick Vic", "Linda the Librarian", "Card Shark Candice",
                                    "Taz the Terror", "Savvy Sven", "Copy Kat",
                                    "King Kyle", "Dirty D"};
string NeutralCards::description[CARDID] = {"Taunt", "Divine Shield", "Charge", "Battlecry: Silence a minion", "Whenever you play a card, gain +1/+1",
                                        "Windfury", "Battlecry: Draw 1 card.", "Battlecry: Choose a minion and become a copy of it.",
                                        "Your other minions have +1/+1", "After you summon a minion, deal 1 damage to a random enemy."};
int NeutralCards::attackStat[CARDID] = {1, 2, 2, 2, 2, 2, 3, 1, 4, 2};
int NeutralCards::healthStat[CARDID] = {2, 1, 1, 2, 2, 1, 2, 1, 4, 3};
int NeutralCards::costStat[CARDID]   = {1, 2, 2, 3, 3, 2, 4, 5, 6, 3};

