#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <iterator>

#include "Card.h"
#include "NeutralCards.h"
#include "HunterCards.h"
#include "Player.h"

using namespace std;

const int SPACING = 30;
const int BADSPACE = 25;
const int MAXMONSTERS = 5;
const int FIELDSIZE = 165;
int myIndex = 0;
int cpuIndex = 0;



void printHand(vector<Card *> &h, char label){
    cout << "\t";
    for(int i = 0; i < h.size(); i++)
    {
        //cout.width(SPACING);
        cout << setw(SPACING) << left << setfill(' ') << h[i]->getName() << "   ";
    }
    cout << endl << label << "\t";

    for(int i = 0; i < h.size(); i++)
    {
        if(h[i]->getDescript().size() > SPACING)
            cout << setw(SPACING) << left << h[i]->getDescript().substr(0,SPACING) << "   ";
        else
            cout << setw(SPACING) << left << h[i]->getDescript() << "   ";
    }
    cout << endl << "\t";
    for(int i = 0; i < h.size(); i++)
    {
        if(h[i]->getDescript().size() > SPACING)
            cout << setw(SPACING) << left << h[i]->getDescript().substr(SPACING) << "   ";
        else
            cout << setw(SPACING) << left << ' ' << "   ";
            //cout << setw(SPACING) << left << ' ' << "   ";
    }
    cout << endl << "\t";
    for(int i = 0; i < h.size(); i++)
        cout << "Cost: " << setw(SPACING - 6) << left << h[i]->getCost() << "   ";
    cout << endl << endl;
}
void printMonsters(vector<Card *> &h, char label){
    cout << "\t";
    for(int i = 0; i < h.size(); i++)
    {
        //cout.width(SPACING);
        cout << setw(SPACING) << left << setfill(' ') << h[i]->getName() << "   ";
    }
    cout << endl << label << "\t";

    for(int i = 0; i < h.size(); i++)
    {
        if(h[i]->getDescript().size() > SPACING)
            cout << setw(SPACING) << left << h[i]->getDescript().substr(0,SPACING) << "   ";
        else
            cout << setw(SPACING) << left << h[i]->getDescript() << "   ";
    }
    cout << endl << "\t";
    for(int i = 0; i < h.size(); i++)
    {
        if(h[i]->getDescript().size() > SPACING)
            cout << setw(SPACING) << left << h[i]->getDescript().substr(SPACING) << "   ";
        else
            cout << setw(SPACING) << left << ' ' << "   ";
            //cout << setw(SPACING) << left << ' ' << "   ";
    }
    cout << endl << "\t";
    for(int i = 0; i < h.size(); i++)
        cout << "Attack: " << h[i]->getAttack() << "\tHealth: " << h[i]->getHealth() << "\t";
    cout << endl << endl;
}
void printField(vector<Card *> &h, vector<Card *> &c, vector<Card *> &mySide, vector<Card *> &cpuSide){
    cout << endl;
    for(int j = 0; j < 4; j++)
    {
        cout << '\t';
        for(int i = 0; i < c.size(); i++)
        {
            cout << setw(BADSPACE) << setfill('*');
            cout << '\t';
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 1; i <= 5; i++)
    {
        cout << '\t' << setw(BADSPACE/2) << setfill(' ');
        cout << i << setw(BADSPACE/2-1) << setfill(' ') << '\t';
    }
    cout << endl;
    cout << setw(FIELDSIZE) << setfill('-') << '-' << endl;
    cout << endl;
    printMonsters(cpuSide, 'A');
    cout <<  endl << setw(FIELDSIZE) << setfill('-') << '-' << endl;
    cout << endl;
    printMonsters(mySide, 'B');
    cout <<  endl << setw(FIELDSIZE) << setfill('-') << '-' << endl;
    cout << endl;
    printHand(h, 'C');
}
void initialMenu(int &cost, int cpuLife, int myLife){
    cout << "Cpu lifepoints: " << cpuLife << "\t\tMy lifepoints: " << myLife << endl;
    cout << "Current cost: " << cost << endl;
    cout << "Play a card [p]" << endl;
    cout << "Inspect the field [i]" << endl;
    cout << "Attack [a]" << endl;
    cout << "Use character special [s]" << endl;
    cout << "End your turn [e]" << endl;
    cout << setw(SPACING) << setfill('-') << '-' << endl;
    cout << "What would you like to do: ";
}
void inspectMenu(vector<Card *> &h, vector<Card *> &mySide, vector<Card *> &cpuSide){
    string temp;
    cout << "What card would you like to inspect [A1-C5]: ";
    getline(cin,temp);
    cin.sync();
    int location = atoi(&(*++temp.begin())) - 1;

    switch(toupper(*temp.begin()))
    {
    case 'A':
        if(location < cpuSide.size())
        {
            cpuSide[location]->printStats();
        }
        else
            cout << "There is no Card in this location..." << endl;
        break;
    case 'B':
        if(location < mySide.size())
        {
            mySide[location]->printStats();
        }
        else
            cout << "There is no Card in this location..." << endl;
        break;
    case 'C':
        if(location < h.size())
        {
            h[location]->printStats();
        }
        else
            cout << "There is no Card in this location..." << endl;
        break;
    default:
        cout << "There is no Card in this location..." << endl;
    }
}

bool lookForEffect(Card *datOne, string eff){ //Doesn't return position
    int i = 0;
    while(datOne->getEffect(i) != "\0")
    {
        if(datOne->getEffect(i).find(eff) != string::npos)
            return true;
        i++;
    }
    return false;
}
bool lookForEffect(Card *datOne, string eff, int *returnPos){
    int i = 0;
    while(datOne->getEffect(i) != "\0")
    {
        if(datOne->getEffect(i).find(eff) != string::npos)
        {
            *returnPos = i;
            return true;
        }
        i++;
    }
    return false;
}

void dealDamage(Card *cardB, int damage){
    if(lookForEffect(cardB, Card::keyEffects[1]))//checking divine shield
    {
        cardB->removeEffect(Card::keyEffects[1]);//using divine shield
    }
    else
        cardB->takeDamage(damage);
}
string targeting(vector<Card *> &mySide, vector<Card *> &cpuSide){
    string temp;
    cout << "Who would you like to attack [A1-B5, enemy]: ";
    getline(cin,temp);
    cin.sync();
    int location = atoi(&(*(temp.begin()+1))) - 1;

    bool taunting = false;
    int i = 0;
    while(i < cpuSide.size())
    {
        if(lookForEffect(cpuSide[i], Card::keyEffects[0]))//checking for taunt
        {
            taunting = true;
            break;
        }
        i++;
    }

    switch(toupper(*temp.begin()))
    {
    case 'A':
        if(taunting == lookForEffect(cpuSide[location], Card::keyEffects[0]))
            return temp;
        else
            return "Taunt Error";
        break;
    case 'B':
        return temp;
        break;
    case 'E':
        if(!taunting)
            return temp;
        else
            return "Taunt Error";
        break;
    }
}
void attackMenu(Player &cpu, vector<Card *> &mySide, vector<Card *> &cpuSide){
    int plusLocation;
    bool tryAgain = true;

    while(tryAgain)
    {
        try
        {
            cout << setw(SPACING) << setfill('-') << '-' << endl;
            cout << "Who would you like to attack with [1-" << mySide.size() << "]: ";
            cin >> plusLocation;
            cin.sync();
            if(cin.fail())
            {
                throw 0;
            }else tryAgain = false;
        }
        catch(int)
        {
            cin.clear();
            cin.ignore(1000,10);
            cout<<"Invalid input for Attack Target"<<endl;
        }
    }

    if(plusLocation > 0 && plusLocation <= mySide.size())
    {
        if(mySide[plusLocation-1]->getHasAttack() < 1)
            cout << "You can't attack with this minion." << endl;
        else
        {
            string temp = targeting(mySide, cpuSide);
            int location = -1;
            if(temp.size() > 1)
                location = atoi(&(*(temp.begin()+1))) - 1;
            switch(toupper(temp.at(0)))
            {
            case 'A':
                if(location >= 0 && location < cpuSide.size())
                {
                    dealDamage(cpuSide[location], mySide[plusLocation-1]->getAttack());
                    dealDamage(mySide[plusLocation-1], cpuSide[location]->getAttack());
                    mySide[plusLocation-1]->setHasAttack(mySide[plusLocation-1]->getHasAttack()-1);
                }
                else
                    cout << "Da Fudge you looking, bro??" << endl;
                break;
            case 'B':
                if(location >= 0 && location < mySide.size() && location != plusLocation-1)
                {
                    dealDamage(mySide[location], mySide[plusLocation-1]->getAttack());
                    dealDamage(mySide[plusLocation-1], mySide[location]->getAttack());
                    mySide[plusLocation-1]->setHasAttack(mySide[plusLocation-1]->getHasAttack()-1);
                }
                else
                    cout << "Da Fudge you looking, bro??" << endl;
                break;
            case 'E':
                cpu.takeDamage(mySide[plusLocation-1]->getAttack());
                mySide[plusLocation-1]->setHasAttack(mySide[plusLocation-1]->getHasAttack()-1);
                break;
            case 'T':
                cout << temp << endl;
                break;
            }
        }
    }
    else
        cout << "Da Fudge you looking, bro??" << endl;
}
bool spell(Card *cardB, vector<Card *> &mySide, vector<Card *> &cpuSide, Player &me, Player &cpu){
    string descript = cardB->getDescript();
    for(int i = 0; i < descript.size(); i++)
    {
        descript.at(i) = tolower(descript.at(i));
    }
    if(descript.find("damage") != string::npos)
    {
        int dam = atoi(&(descript.at(descript.find("damage")-2)));

        if(descript.find("hero") != string::npos)
        {
            cout << descript << '\t' << descript.find("hero") << endl;
            cpu.takeDamage(dam);
            return true;
        }
        if(descript.find("random") != string::npos)
        {
            if(descript.rfind("two",descript.find("random")) != string::npos)
            {
                if(cpuSide.size() > 1)
                {
                    int ran1 = rand()%(cpuSide.size());
                    int ran2;
                    do{
                        ran2 = rand()%(cpuSide.size());
                    }while(ran1 == ran2);
                    dealDamage(cpuSide[ran1],dam);
                    dealDamage(cpuSide[ran2],dam);
                    return true;
                }
                else
                {
                    cout << "Not enough enemies..." << endl;
                    return false;
                }
            }
            else
            {
                int r = rand()%(cpuSide.size()+1);
                if(r == cpuSide.size())
                    cpu.takeDamage(dam);
                else
                    dealDamage(cpuSide[r],dam);
                return true;
            }
        }
        else //if not random...
        {
            string temp;
            cout << "What card would you like to damage [A1-B5, enemy]: ";
            getline(cin,temp);
            cin.sync();
            int location = atoi(&(*(temp.begin()+1))) - 1;

            switch(toupper(*temp.begin()))
            {
            case 'A':
                if(location < cpuSide.size())
                {
                    if(descript.find("adjacent") != string::npos)
                    {
                        int damA = descript.at(descript.rfind("damage")-2);
                        if(location > 0)
                            dealDamage(cpuSide[location-1],damA);
                        if(location < cpuSide.size()-1)
                            dealDamage(cpuSide[location+1],damA);
                    }
                    dealDamage(cpuSide[location], dam);
                    return true;
                }
                else
                {
                    cout << "There is no Card in this location..." << endl;
                    return false;
                }
                break;
            case 'B':
                if(location < mySide.size())
                {
                    if(descript.find("adjacent") != string::npos)
                    {
                        int damA = descript.at(descript.rfind("damage")-2);
                        if(location > 0)
                            dealDamage(mySide[location-1],damA);
                        if(location < mySide.size()-1)
                            dealDamage(mySide[location+1],damA);
                    }
                    dealDamage(mySide[location], dam);
                    return true;
                }
                else
                {
                    cout << "There is no Card in this location..." << endl;
                    return false;
                }
                break;
            case 'E':
                cpu.takeDamage(dam);
                return true;
                break;
            default:
                cout << "There is no Card in this location..." << endl;
                return false;
            }
        }
    }//End of damage

    if(descript.find("destroy") != string::npos)
    {
        if(cpuSide.size() > 0)
        {
            if(descript.find("random") != string::npos)
            {
                int ran = rand()%(cpuSide.size());
                cpuSide[ran]->setHealthMax(0);
                return true;
            }
            else
            {
                int location;
                cout << "What card would you like to destroy [1-" << cpuSide.size() <<"]: ";
                cin >> location;
                cin.sync();
                if(location > 0 && location <= cpuSide.size())
                {
                    cpuSide[location-1]->setHealthMax(0);
                    return true;
                }
                else
                {
                    cout << "Da Fudge you looking, bro??" << endl;
                    return false;
                }
            }
        }
    }//End of destroy

    if(descript.find("health") != string::npos)
    {
        string temp;
        cout << "What card would you like to change [A1-B5]: ";
        getline(cin,temp);
        cin.sync();
        int location = atoi(&(*(temp.begin()+1))) - 1;

        switch(toupper(*temp.begin()))
        {
        case 'A':
            if(location < cpuSide.size())
            {
                cpuSide[location]->setHealthMax(1);
                return true;
            }
            else
            {
                cout << "There is no Card in this location..." << endl;
                return false;
            }
            break;
        case 'B':
            if(location < mySide.size())
            {
                mySide[location]->setHealthMax(1);
                return true;
            }
            else
            {
                cout << "There is no Card in this location..." << endl;
                return false;
            }
            break;
        default:
            cout << "There is no Card in this location..." << endl;
            return false;
        }
    }
}

void resetHasAttack(vector<Card *> &mySide){
    for(int i = 0; i < mySide.size(); i++)
    {
        if(lookForEffect(mySide[i], Card::keyEffects[5]))
        {
            mySide[i]->setHasAttack(2);
        }
        else
        {
            mySide[i]->setHasAttack(1);
        }
    }
}
void subtractOtherMinions(vector<Card *> &mySide, int deadPos){
    int effPos;
    lookForEffect(mySide[deadPos], "other minions", &effPos);
    string::const_iterator it = mySide[deadPos]->getEffect(effPos).begin();
    it += mySide[deadPos]->getEffect(effPos).find("/");//at the /
    int a = atoi(&(*(it-1)));
    if(*(it-2) == '-')//2 before /
        a*=(-1);
    int h = atoi(&(*(it+2)));//back two at / and after 2 at num
    if(*(it+1) == '-')
        h*=(-1);
    for(int j = 0; j < mySide.size(); j++)
    {
        if(j != deadPos)
        {
            mySide[j]->setAttack(mySide[j]->getAttack() - a);
            mySide[j]->setHealthMax(mySide[j]->getHealthMax() - h);
            while(mySide[j]->getHealthMax() < mySide[j]->getHealth())
                mySide[j]->setDamC(mySide[j]->getDamC()-1);
        }
    }
}
void checkDead(vector<Card *> &mySide, vector<Card *> &cpuSide){
    for(int i = 0; i < mySide.size(); i++)
    {
        if(mySide[i]->getHealth() <= 0)
        {
            if(lookForEffect(mySide[i], "other minions"))
                subtractOtherMinions(mySide, i);

            mySide.erase(mySide.begin()+i);
            --i;
        }
    }
    for(int i = 0; i < cpuSide.size(); i++)
    {
        if(cpuSide[i]->getHealth() <= 0)
        {
            cpuSide.erase(cpuSide.begin()+i);
            --i;
        }
    }
}
void additionMinions(vector<Card *> &mySide){
    int i = 0;
    int effPos;
    while(i < mySide.size())
    {
        if(lookForEffect(mySide[i], "other minions", &effPos))
        {
            string::const_iterator it = mySide[i]->getEffect(effPos).begin();
            it += mySide[i]->getEffect(effPos).find("/");//at the /
            int a = atoi(&(*(it-1)));
            if(*(it-2) == '-')
                a*=(-1);
            int h = atoi(&(*(it+2)));
            if(*(it+1) == '-')
                h*=(-1);
            if(i != mySide.size()-1)
            {
                mySide[mySide.size()-1]->setAttack(mySide[mySide.size()-1]->getAttack() + a);
                mySide[mySide.size()-1]->setHealthMax(mySide[mySide.size()-1]->getHealthMax() + h);
            }
        }
        i++;
    }
}

void checkOtherMinions(vector<Card *> &mySide){
    int i = mySide.size()-1;
    int effPos;

    if(lookForEffect(mySide[i], "other minions", &effPos))
    {
        string::const_iterator it = mySide[i]->getEffect(effPos).begin();
        it += mySide[i]->getEffect(effPos).find("/");//at the /
        int a = atoi(&(*(it-1)));
        if(*(it-2) == '-')
            a*=(-1);
        int h = atoi(&(*(it+2)));
        if(*(it+1) == '-')
            h*=(-1);
        for(int j = 0; j < mySide.size(); j++)
        {
            if(j != i)
            {
                mySide[j]->setAttack(mySide[j]->getAttack() + a);
                mySide[j]->setHealthMax(mySide[j]->getHealthMax() + h);
            }
        }
    }
}

//Boolean attempt! JK Char attempt!
char checkPlay(Card* temp, vector<Card *> &h, vector<Card *> &mySide, vector<Card *> &cpuSide, Player &me, Player &cpu, int &cost, int location){
    if(mySide.size() <= 5 || temp->getEffect(0) == Card::keyEffects[6])
    {
        if(cost >= temp->getCost())
        {
            if(temp->getEffect(0) != Card::keyEffects[6]) //Everything, but spells
            {
                if(lookForEffect(temp, Card::keyEffects[2]))//Battlecry
                {
                    string lowerDescript = temp->getDescript();
                    for(int i = 0; i < lowerDescript.size(); i++)
                        lowerDescript.at(i) = tolower(lowerDescript.at(i));
                    if(lowerDescript.find("draw") != string::npos)
                    {
                        for(int i = 0; i < atoi(&lowerDescript.at(lowerDescript.find("draw")+5)); i++)
                            h.push_back(me.returnCard(myIndex++));
                    }
                    if(lowerDescript.find("silence") != string::npos)
                    {
                        if(mySide.size() > 0 || cpuSide.size() > 0)
                        {
                            string t;
                            cout << "What card would you like to silence [A1-B5]: ";
                            getline(cin,t);
                            cin.sync();
                            int location = atoi(&(*(t.begin()+1))) - 1;

                            switch(toupper(*t.begin()))
                            {
                            case 'A':
                                if(location < cpuSide.size())
                                {
                                    cpuSide[location]->clearEffects();
                                    dynamic_cast<NeutralCards *>(cpuSide[location])->reset();
                                }
                                else
                                {
                                    cout << "There is no Card in this location..." << endl;
                                    return 'X';
                                }
                                break;
                            case 'B':
                                if(location < mySide.size())
                                {
                                    mySide[location]->clearEffects();
                                    dynamic_cast<NeutralCards *>(mySide[location])->reset();
                                }
                                else
                                {
                                    cout << "There is no Card in this location..." << endl;
                                    return 'X';
                                }
                                break;
                            default:
                                cout << "There is no Card in this location..." << endl;
                                return 'X';
                            }
                        }
                        else//nothing to copy
                        {
                            cout << "There are no cards to silence... " << endl;
                            return 'X';
                        }
                    }//Silence
                    if(lowerDescript.find("copy") != string::npos)
                    {
                        if(mySide.size() > 0 || cpuSide.size() > 0)
                        {
                            string t;
                            cout << "What card would you like to copy [A1-B5]: ";
                            getline(cin,t);
                            cin.sync();
                            int location = atoi(&(*(t.begin()+1))) - 1;

                            switch(toupper(*t.begin()))
                            {
                            case 'A':
                                if(location < cpuSide.size())
                                {
                                    *temp = cpuSide[location];
                                }
                                else
                                {
                                    cout << "There is no Card in this location..." << endl;
                                    return 'X';
                                }
                                break;
                            case 'B':
                                if(location < mySide.size())
                                {
                                    *temp = mySide[location];
                                }
                                else
                                {
                                    cout << "There is no Card in this location..." << endl;
                                    return 'X';
                                }
                                break;
                            default:
                                cout << "There is no Card in this location..." << endl;
                                return 'X';
                            }
                        }
                        else//nothing to copy
                        {
                            cout << "There are no cards to copy... " << endl;
                            return 'X';
                        }
                    }
                    if(lowerDescript.find("charge") != string::npos)
                        temp->setHasAttack(1);

                }//Battlecry Effects
                cost -= temp->getCost();
                mySide.push_back(temp);
                h.erase(h.begin()+location);
                if(lookForEffect(temp, "other minions"))//adding effect
                    checkOtherMinions(mySide);
                return 'M';
            }//played card
            else //Spell card
            {
                if(spell(temp, mySide, cpuSide, me, cpu))
                {
                    checkDead(mySide, cpuSide);
                    if(location != -1) //Checking for Hero special
                        h.erase(h.begin()+location);
                    cost -= temp->getCost();
                    return 'C';
                }
                else
                    return 'X';
            }
        }
        else
            cout << "Insufficient cost..." << endl;
    }//Field is full
    else
        cout << "No more room on the field!" << endl;
    return 'X';
}
void playMinionEffects(vector<Card *> &mySide, vector<Card *> &cpuSide, Player &cpu){
    int i = 0;
    int effPos;
    while(i < mySide.size())
    {
        if(lookForEffect(mySide[i], "Summon", &effPos))
        {
            if(i != mySide.size()-1)
            {
                int dam = atoi(&(mySide[i]->getEffect(effPos).at(mySide[i]->getEffect(effPos).find("damage")-2)));
                int r = rand()%(cpuSide.size()+1);
                if(r == cpuSide.size())
                    cpu.takeDamage(dam);
                else
                    cpuSide[r]->takeDamage(dam);
            }
        }
        i++;
    }
}
void playCardEffects(vector<Card *> &mySide){
    int i = 0;
    int effPos;
    while(i < mySide.size())
    {
        if(lookForEffect(mySide[i], "gain", &effPos))
        {
            char t = mySide[i]->getEffect(effPos).at(mySide[i]->getEffect(effPos).find("/")-1);
            int a = atoi(&t);
            if(mySide[i]->getEffect(effPos).at(mySide[i]->getEffect(effPos).find("/")-2) == '-')
                a*=(-1);
            t = mySide[i]->getEffect(effPos).at(mySide[i]->getEffect(effPos).find("/")+2);
            int h = atoi(&t);
            if(mySide[i]->getEffect(effPos).at(mySide[i]->getEffect(effPos).find("/")+1) == '-')
                h*=(-1);
            mySide[i]->setAttack(mySide[i]->getAttack() + a);
            mySide[i]->setHealthMax(mySide[i]->getHealth() + h);
        }
        i++;
    }
}
int playMenu(vector<Card *> &h){
    int temp;
    cout << setw(SPACING) << setfill('-') << '-' << endl;
    cout << "What card would you like to play [1 - " << h.size() << "]: ";
    cin >> temp;
    cin.sync();
    if(temp > 0 && temp <= h.size())
    {
        return temp-1;
    }
    else
    {
        cout << "Invalid input..." << endl;
        return 0;
    }
}

int main()
{
    vector<Card *> myHand;
    vector<Card *> cpuHand;
    vector<Card *> mySide;
    vector<Card *> cpuSide;
    Player me(0);
    Player cpu(0);
    int costForTurn = 0;
    char command = ' ';

    for(int i = 0; i < 3; i++)
    {
        myHand.push_back(me.returnCard(myIndex++));
        cpuHand.push_back(cpu.returnCard(cpuIndex++));
    }

    for(int i = 0; i < 3; i++)
    {
        cpuSide.push_back(new NeutralCards(rand()%Card::CARDID));
    }
    while(me.returnLife() > 0 && cpu.returnLife() > 0)
    {
        if(mySide.size() > 0)
        {
            resetHasAttack(mySide);
        }

        costForTurn = me.returnCost();
        myHand.push_back(me.returnCard(myIndex++));

        do
        {
            printField(myHand,cpuHand, mySide, cpuSide);
            initialMenu(costForTurn, cpu.returnLife(), me.returnLife());
            cin >> command;
            cin.sync();
            switch(tolower(command))
            {
            case 'a':
            {
                if(mySide.size() > 0)
                {
                    attackMenu(cpu, mySide, cpuSide);
                    checkDead(mySide, cpuSide);
                }
                break;
            }
            case 'p':
            {
                int local = playMenu(myHand);
                switch(checkPlay(myHand[local], myHand, mySide, cpuSide, me, cpu, costForTurn, local))
                {
                case 'M':
                    playMinionEffects(mySide, cpuSide, cpu);
                    additionMinions(mySide);
                case 'C':
                    playCardEffects(mySide);
                    checkDead(mySide, cpuSide);

                    break;
                default:
                    break;
                }
                break;
            }
            case 's':
            {
                checkPlay(me.returnCard(-1), myHand, mySide, cpuSide, me, cpu, costForTurn, -1);
                break;
            }
            case 'i':
            {
                inspectMenu(myHand, mySide, cpuSide);
                break;
            }
            }//Switch
            cout << endl;
            if(me.returnLife() <= 0 || cpu.returnLife() <= 0)
                break;

        }while(tolower(command) != 'e');

        me.costIncrement();
        cpu.costIncrement();
        //cpuHand.push_back(cpu.returnCard(cpuIndex++));
    }
    return 0;
}
