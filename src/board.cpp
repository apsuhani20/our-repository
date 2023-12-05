#include "Board.h"
#include <cstdlib>
#include <ctime>

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player_position = 0;
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    if (position == _player_position)
    {
        cout << "X";
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position = new_position;
        return true;
    }
    return false;
}

string Board::getTileColor(int position) const
{
    if(position>=0 && position < _BOARD_SIZE)
    {
        return _tiles[position].color;
    }

    return "";
}


int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition() const
{
    return _player_position;
}

bool Board::addCandyStore()
{
    srand(time(0));

    vector<int>magentaPositions;
    vector<int>greenPositions;
    vector<int>bluePositions;

    for(int i = 0; i<=82; i++)
    {
        if(i%3 == 0)
        {
            if(i<=27)
                magentaPositions.push_back(i);
        }
        else if((i&3) == 1)
        {
            if(i>=28 && i<=54)
                greenPositions.push_back(i);
        }
        else if(i%3 == 2)
        {
            if(i>=55)
                bluePositions.push_back(i);
        }
    }


    int position1 = magentaPositions.at(rand() % magentaPositions.size());
    int position2 = greenPositions.at(rand() % greenPositions.size());
    int position3 = bluePositions.at(rand() % bluePositions.size());

    _candy_store_position[0] = position1;
    _candy_store_position[1] = position2;
    _candy_store_position[2] = position3;

    _candystores[0].setStoreName("Sugar Rush");
    _candystores[1].setStoreName("Candy Craze");
    _candystores[2].setStoreName("Tempting Treats");

    //cout << _candy_store_position[0] << " " << _candy_store_position[1] << " " << _candy_store_position[2];

    return true;


}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

void Board::displayCandyOptions(int storeIndex)
{      
   _candystores[storeIndex].displayCandy();
}


bool Board::movePlayer(int tile_to_move_forward, Player &player)
{
    int new_player_position = tile_to_move_forward + _player_position;
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_position = new_player_position;

    Tile newTile = _tiles[new_player_position];

    if(newTile.tile_type == "hidden treasure tile")
    {
        handleHiddenTreasure(player);
    }

    if(newTile.hasPlayer)//me
    {
        //if there is a player already on the tile, they can take from 5-30 coins randomly from the other player's gold stock and move it to theirs
        //if the player has a shield however, they can avoid the attack (no gold taken), and the first player on the tile moves back one tile
        
    }

     // Handle special tiles based on their type
    if (newTile.tile_type == "shortcut tile")//me
    {
        // Handle shortcut logic
        if (_player_position + 4 >= _BOARD_SIZE)
        {
            // If the player is less than 4 tiles from the castle, move to the castle
            _player_position = _BOARD_SIZE - 1;
        }
        else
        {
            _player_position += 4;
        }
    }
    else if (newTile.tile_type == "ice cream stop tile")
    {
        //Gives the player an additional turn by calling the draw card function again
        cout << "You landed on an ice cream stop. You get an extra card draw" << endl;
        drawCard(player);
    }
    else if (newTile.tile_type == "gumdrop forest tile")
    {
        //change player position to 4 steps back
            //if the player is less than 4 tiles from the start, taken back to start
        //remove a random number between 5 and 10 from their gold
    }
    else if (newTile.tile_type == "gingerbread house tile")//me
    {
        //take the player back to their previous position and remove an immunit candy from the player's inventory
    }
    else
    {
        // Regular tile, just move the player to the new position
        _player_position = new_player_position;
    }

    return true;
}

void Board::handleHiddenTreasure(Player player)
{
     //**must get riddle correct**
    //determines a random number from 1-100 to get the random percentage
    /*if under or equal to 30, staminal refills a random amount from 10 to 30
    if it is between 30 and 40, then it adds a random amount of gold from 20-40
    if it is between 40 and 70, it gives the player the shield
    if it is between 70 and 100, then it generates another random number between 1 and 100, 
    it is is under or equal to 70, the player gets Jellybean of vigor, but above 70 to 100 get treasure hunter's truffle*/

}

void Board::drawCard(Player p)
{
   srand(time(0));
   int num = rand()%3+1;
   string card;

   if(num == 1)
   {
    card = "Cotton Candy Magenta";
   }
   else if(num == 2)
   {
    card = "Minty Green";
   }
   else if(num == 3)
   {
    card = "Bubblegum Blue";
   }
   cout << "You drew " << card << "."  << endl;

    string current= getTileColor(getPlayerPosition());
    if(current == "MAGENTA")
    {
        if(num == 1)
        {
            movePlayer(3, p);
        }
        else if(num == 2)
        {
            movePlayer(1, p);
        }
        else if(num == 3)
        {
            movePlayer(2, p);
        }
    }
    else if(current == "GREEN")
    {
        if(num == 1)
        {
            movePlayer(2, p);
        }
        else if(num == 2)
        {
            movePlayer(3, p);
        }
        else if(num == 3)
        {
            movePlayer(1, p);
        }
    }
    else if(current == "BLUE")
    {
          if(num == 1)
        {
            movePlayer(1, p);
        }
        else if(num == 2)
        {
            movePlayer(2, p);
        }
        else if(num == 3)
        {
            movePlayer(3, p);
        }
    }

}