#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

using namespace std;

struct Candy
{
    string name; //name of candy
    string description; //description of candy
    string effect_type;
    int effect_value;
    string candy_type; //type of candy
    int price; //price of candy

};

struct Character
{
    string character_name;
    int stamina;
    int gold;
    string inventory[9];

};

class Player
{
    private:
        const static int _max_candy_amount = 9;
        Candy _inventory[_max_candy_amount];
        string _name;
        string _effect;
        Character _character;
        int _stamina;
        int _gold;
        int _candy_amount;
        int _position;
        
        
        
        
    public:
       Player();
        Player(string name, int stamina, double gold, string effect, Candy candy[], const int size);

        int getCandyAmount() const;
        void setStamina(int stamina);
        void setPosition(int position);
        int getPosition() const;
        int getStamina() const;
        void setGold(double gold);
        double getGold() const;
        void setName(string name);
        string getName() const;
        void setCharacter(Character c);
        Character getCharacter() const;
        string getName();
        
        void setEffect(string effect);
        string getEffect() const;

        void printInventory();
        Candy findCandy(string candy_name);
        bool addCandy(Candy candy);
        bool removeCandy(string candy_name);    
    
};
#endif