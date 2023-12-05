#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "player.h"
#include "candyStore.h"

#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;



struct Tile
{
    string color;
    string tile_type;
    bool hasPlayer;
};


class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    Candystore _candystores[_MAX_CANDY_STORE];
    int _candy_store_count;
    int _player_position;
    

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();
    void handleHiddenTreasure(Player player);
    void drawCard(Player player);

    bool setPlayerPosition(int);

    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayerPosition() const;
    string getTileColor(int) const;

    bool addCandyStore();
    bool isPositionCandyStore(int position); 
    void displayCandyOptions(int storeIndex);

    bool movePlayer(int tile_to_move_forward, Player &player);
};

#endif