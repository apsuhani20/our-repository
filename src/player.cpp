#include "player.h"
#include <string>
#include <cstdlib>

using namespace std; 

Player::Player(){
    _stamina = 0;
    _gold = 0;
    _effect = "";


    Candy emptyCandy = {"", "", "", 0, ""};
    for(int i = 0; i < _max_candy_amount; i++){
        _inventory[i] = emptyCandy;
    }
}

Player::Player(string name, int stamina, double gold, string effect, Candy candy[], const int size){
    _name = name;
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
   

    for(int i = 0; i < _max_candy_amount && i < size; i++){
        _inventory[_candy_amount] = candy[i];
        if(candy[i].name != "" && candy[i].description != "" && candy[i].price != 0.0 && candy[i].candy_type != ""){
            _candy_amount ++;
        }
    }
}

void Player::setName(string name)
{
    _name = name;
}

string Player::getName()
{
    return _name;
}

int Player::getCandyAmount() const{
    return _candy_amount;
}

void Player::setStamina(int stamina){
    _stamina = stamina;
}

int Player::getStamina() const{
    return _stamina;
}

void Player::setGold(double gold){
    _gold = gold;
}

double Player::getGold() const{
    return _gold;
}

void Player::setEffect(string effect){
    _effect = effect;
}

string Player::getEffect() const{
    return _effect;
}


void Player::setCharacter(Character c)
{
    _character = c;
}

Character Player::getCharacter() const
{
    return _character;
}

void Player::setPosition(int position)
{
    _position = position;
}

int Player::getPosition() const{
    return _position;
}
void Player::printInventory(){
    string candy1 = _inventory[0].name;
    string candy2 = _inventory[1].name;
    string candy3 = _inventory[2].name;
    string candy4 = _inventory[3].name;
   
    if(candy1 == ""){
        candy1 = "Empty";
    }
    if(candy2 == ""){
        candy2 = "Empty";
    }
    if(candy3 == ""){
        candy3 = "Empty";
    }
    if(candy4 == ""){
        candy4 = "Empty";
    }

    cout << "|[" << candy1 << "]|[" << candy2 << "]|" << endl;
    cout << "|[" << candy3 << "]|[" << candy4 << "]|" << endl;
}

Candy Player::findCandy(string candy_name){
    string candy_lower = "";
    for(int i = 0; i < candy_name.length(); i++){
        char lower = tolower(candy_name[i]);
        candy_lower = candy_lower + lower;
    }
   
    Candy temp;

    for(int i = 0; i < _max_candy_amount; i++){
        string currentCandyName = _inventory[i].name;
        string current_candy_lower = "";
        for (int j = 0; j < currentCandyName.length(); j++) {
            current_candy_lower += tolower(currentCandyName[j]);
        }

        if (current_candy_lower == candy_lower) {
            temp = _inventory[i];
            return temp;
        }
    }

    return temp;
}


bool Player::addCandy(Candy candy){
    if(_candy_amount == 4){
        return false;
    } else{
        _inventory[_candy_amount] = candy;
        _candy_amount ++;
        return true;
    }
}

bool Player::removeCandy(string candy_name){
    string candy_name_lower = "";
    for(int i = 0; i < candy_name.length(); i++){
        char lower = tolower(candy_name[i]);
        candy_name_lower = candy_name_lower + lower;
    }
    int indexCandy = -1;
    for(int i = 0; i < _max_candy_amount; i++){
        string currentCandyName = _inventory[i].name;
        string current_candy_lower = "";
        for (int j = 0; j < currentCandyName.length(); j++) {
            current_candy_lower += tolower(currentCandyName[j]);
        }

        if (current_candy_lower == candy_name_lower) {
            indexCandy = i;
            break;
        }
    }

    if(indexCandy == -1){
        return false;
    } else{
        for (int i = indexCandy; i < _max_candy_amount - 1; i++) {
            _inventory[i] = _inventory[i + 1];
        }
        _candy_amount --;
        return true;
    }
}