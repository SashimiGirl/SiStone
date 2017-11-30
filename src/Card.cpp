#include "Card.h"

const int SIZE = 7;
//                                  0           1               2          3        4           5         6
string Card::keyEffects[SIZE] = {"Taunt", "Divine Shield", "Battlecry", "Gain", "Summon", "Windfury", "Spell"};
//                                  0           1             2 3 6 7      8       4 9          5

Card::Card(int c, int e, string n, string d)
{
    setCost(c);
    if(e < SIZE)
        setEffect(e);
    setName(n);
    setDescript(d);
}

Card::Card(int n)
{
    setCost(n);
    setName("");
    setDescript("");
    setAttack(0);
    setHealthMax(0);
    setDamC(0);
    setHasAttack(-1);
}

Card::~Card()
{
    //dtor
}
void Card::printStats()
{
    cout << getName() << endl;
    cout << getDescript() << endl;
    cout << "Cost: " << getCost() << endl;
    cout << "Attack: " << attack << "\t" << "Health: " << healthMax-damCounter << endl << endl;
    printEffects();
}

Card Card::operator=(Card *right)
{
    this->setAttack(right->getAttack());
    this->setHealthMax(right->getHealthMax());
    this->setDamC(right->getDamC());

    int i = 0;
    while(right->getEffect(i) != "\0")
    {
        this->setEffect(right->getEffect(i++));
    }
    return *this;
}

string Card::getEffect(int i)
{
    if(i >= effects.size())
        return "\0";
    else
        return effects[i];
}

void Card::printEffects()
{
    if(effects.size() > 0)
        for(int i = 0; i < effects.size(); i++)
        {
            cout << effects[i] << " ";
        }
    cout << endl;
}

void Card::setCost(int c)
{
    if(c < 0)
        c = 0;
    cost = c;
}

void Card::takeDamage(int damage)
{
    damCounter += damage;
}

void Card::setEffect(string s)
{
    if(effects.size() > 0)
    {
        int i = 0;
        for(i; i < effects.size(); i++)
            if(s == effects[i])
                break;
        if(i == effects.size())
            effects.push_back(s);
    }
    else
        effects.push_back(s);
}

void Card::setEffect(int e)
{
    if(effects.size() > 0)
    {
        for(int i = 0; i < effects.size(); i++)
            if(keyEffects[e] == effects[i])
            {
                if(e == 3 || e == 4)
                {
                    effects.push_back(keyEffects[e]);
                    break;
                }
                else
                    break;
            }
    }
    else
        effects.push_back(keyEffects[e]);
}

void Card::removeEffect(string s)
{
    if(effects.size() > 0)
    {
        for(int i = 0; i < effects.size(); i++)
            if(s == effects[i])
            {
                effects.erase(effects.begin()+i);
                break;
            }

    }
}
