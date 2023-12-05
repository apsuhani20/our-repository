#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "board.h"
#include "game.h"
#include <cassert>


using namespace std;

void playRockPaperScissors(Player players[2]);
void calamities(Player p);
bool riddles(Player p);

int main()
{
    Player player;
    assert(player.getEffect() == "");
    assert(player.getGold() == 0);
    assert(player.getName() == "");
    player.setName("Billy Bob");
    assert(player.getName() == "Billy Bob");
    player.printInventory();
    Player player2;

    vector<Candy>candies;
    vector<Character>character;
    Game game(candies, character);
    candies = game.getCandies();
    character = game.getCharacters();

    Board board;
    board.addCandyStore();
    board.displayCandyOptions(0);
    board.drawCard(player);
    board.movePlayer(3, player);
    board.movePlayer(2, player2);
    board.displayBoard();
    
    return 0;

}

//This will be modified to play against the computer rather than another player
void playRockPaperScissors(Player players[2]){
    if(players[0].getCandyAmount() == 0 || players[1].getCandyAmount() == 0){
        cout << "Not enough candy!" << endl;
        return;
    }

    string bet1;
    Candy candyOne;
    bool bet1Found = false;
    cout << "Player 1 Inventory" << endl;
    players[0].printInventory();
    cout << "Player 1: Select candy to bet" << endl;
    getline(cin, bet1);

    while(bet1Found == false){
        candyOne = players[0].findCandy(bet1);

        if(candyOne.name == ""){
            cout << "Invalid selection!" << endl;
            getline(cin, bet1);
        } else{
            bet1Found = true;
        }
    }
   
    string bet2;
    Candy candyTwo;
    bool bet2Found = false;
    cout << "Player 2 Inventory" << endl;
    players[1].printInventory();
    cout << "Player 2: Select candy to bet" << endl;
    getline(cin, bet2);

    while(bet2Found == false){
        candyTwo = players[1].findCandy(bet2);

        if(candyTwo.name == ""){
            cout << "Invalid selection!" << endl;
            getline(cin, bet2);
        } else{
            bet2Found = true;
        }
    }

    bool p1Won = false;
    bool p2Won = false;

    do{
        char p1Choice;
        cout << "Player 1: Enter r, p, or s" << endl;
        cin >> p1Choice;

        while(cin.fail() || (p1Choice != 'r' && p1Choice != 'p' && p1Choice != 's')){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid selection!" << endl;
            cin >> p1Choice;
        }

        cin.ignore();
        char p2Choice;
        cout << "Player 2: Enter r, p, or s" << endl;
        cin >> p2Choice;

        while(cin.fail() || (p2Choice != 'r' && p2Choice != 'p' && p2Choice != 's')){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid selection!" << endl;
            cin >> p2Choice;
        }

        cin.ignore();

        if(p1Choice == p2Choice){
            cout << "Tie! Play again" << endl;
        } else if(p1Choice == 'r' && p2Choice == 'p'){
            cout << "Player 2 has won " << bet1 << " from player 1!" << endl;
            players[0].removeCandy(bet1);
            players[1].addCandy(candyOne);
            p2Won = true;
        } else if(p1Choice == 'r' && p2Choice == 's'){
            cout << "Player 1 has won " << bet2 << " from player 2!" << endl;
            players[1].removeCandy(bet2);
            players[0].addCandy(candyTwo);
            p1Won = true;
        } else if(p1Choice == 'p' && p2Choice == 'r'){
            cout << "Player 1 has won " << bet2 << " from player 2!" << endl;
            players[1].removeCandy(bet2);
            players[0].addCandy(candyTwo);
            p1Won = true;
        } else if(p1Choice == 'p' && p2Choice == 's'){
            cout << "Player 2 has won " << bet1 << " from player 1!" << endl;
            players[0].removeCandy(bet1);
            players[1].addCandy(candyOne);
            p2Won = true;
        } else if(p1Choice == 's' && p2Choice == 'r'){
            cout << "Player 2 has won " << bet1 << " from player 1!" << endl;
            players[0].removeCandy(bet1);
            players[1].addCandy(candyOne);
            p2Won = true;
        } else if(p1Choice == 's' && p2Choice == 'p'){
            cout << "Player 1 has won " << bet2 << " from player 2!" << endl;
            players[1].removeCandy(bet2);
            players[0].addCandy(candyTwo);
            p1Won = true;
        }
    } while(p1Won == false && p2Won == false);
}

bool riddles(Player p)
{
    /*
    if player decides to answer riddle after encountering a hidden treasure, then this function is called
    the function reads the riddles file, stores each part of the riddle into different arrays(riddle, answer)
    presents the next riddle in the array to the player and takes in their answer response
    if answer response matches the answer in the answers array, returns true and then handlehiddentreasures from the board class will be called in main
    otherwise it returns false and the next player's turn will start in the main
    */
   return true;
}

void calamities(Player p)
{
    /*
    in the main, if a random number generated is within 1-40, then it will call the calameties function
    the function generates another random number 
    if it is from 1-30, player loses a random amount from 1-10 of gold
    if it is 30-65, player loses a turn but if they will rock paper scissors they get the turn back
    if it is 65-80, player loses random amount 5-10 of stamina and skip a turn, but can recover damage if win rock paper scissors
    if it is 80-100, player loses a turn unless they use a magical candy from their inventory
    */
} 