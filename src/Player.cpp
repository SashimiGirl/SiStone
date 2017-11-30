#include "Player.h"

Player::Player(int h)
{
    costMax = 1;
    switch(h)
    {
    case 0:
        hero = new HunterCards(-1);
        break;
    /*
    case 1:
        hero = new PriestCards();
        */
    }
    lifePts = 20;
    setDeck(h);
    shuffleDeck();
}

Player::~Player()
{
    //dtor
}

void Player::costIncrement()
{
    if(costMax < 10)
        costMax++;
}

void Player::setDeck(int h)
{
    srand(time(NULL));
    for(int i = 0; i < 30; i++)
    {
        int j = rand()%10;
        if(j%2)
            deck.push_back(new NeutralCards(rand()%Card::CARDID));
        else
        {
            switch(h)
            {
            case 0:
                deck.push_back(new HunterCards(rand()%Card::SPECIALID));
                break;
            //case 1:
                //deck.push_back(new PriestCards(rand()%SPECIALID))
            }
        }
    }
}

void Player::shuffleDeck()
{
    srand(time(NULL));
    for(int i = 0; i < deck.size(); i++)
    {
        int j = rand()%deck.size();
        Card *temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

Card* Player::returnCard(int index)
{
    if(index >= 0 && index < deck.size())
        return deck[index];
    if(index == -1)
        return hero;
}


void Player::takeDamage(int damage)
{
    lifePts -= damage;
}

void Player::operator-=(Player right)
{
    this->takeDamage(right.returnDamage());
}
