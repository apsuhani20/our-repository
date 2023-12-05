#include "candyStore.h"
#include <cstdlib>
#include <fstream>
#include <sstream>


Candystore::Candystore()
{
    srand(static_cast<unsigned>(time(nullptr)));
    _store_name = "Cool Candies Store";
    vector<Candy>allCandies = readCandiesFromFile();
    pickRandomCandies(allCandies);

}
Candystore::Candystore(string name)
{
    srand(static_cast<unsigned>(time(nullptr)));
    _store_name = name;
    vector<Candy>allCandies = readCandiesFromFile();
    pickRandomCandies(allCandies);
}
void Candystore::setStoreName(string name)
{
    _store_name = name;
}

string Candystore::getStoreName()const{
    return _store_name;
}

vector<Candy> Candystore::readCandiesFromFile()
{
    vector<Candy> candies;
    ifstream file("candy.txt"); // Assuming the file is named "candies.txt"

    if (file.is_open())
    {
        string line;
        getline(file, line);
        while (getline(file, line))
        {
            istringstream iss(line);
            Candy candy;

            getline(iss, candy.name, '|');
            getline(iss, candy.description, '|');
            getline(iss, candy.effect_type, '|');
            string effectVal;
            getline(iss,effectVal, '|');
            candy.effect_value = stoi(effectVal);
            getline(iss, candy.candy_type, '|');
            string price;
            getline(iss, price, '|');
            candy.price = stoi(price);
            

            candies.push_back(candy);
        }
        file.close();
    }
    return candies;
}

void Candystore::pickRandomCandies(const vector<Candy> allCandies)
{
    vector<Candy> shuffledCandies = allCandies;
    
    int indexCandy1;
    int indexCandy2;
    int indexCandy3;

    do
    {
      indexCandy1 = rand() % shuffledCandies.size();
      indexCandy2 = rand() % shuffledCandies.size();
      indexCandy3 = rand() % shuffledCandies.size();
    } while (indexCandy3 == indexCandy2== indexCandy1);

    _candies[0] = shuffledCandies[indexCandy1];
    _candies[1] = shuffledCandies[indexCandy2];
    _candies[2] = shuffledCandies[indexCandy3];

}

void Candystore::displayCandy()
{
    
    
    cout << "Name: " << getStoreName() << endl;
    cout << "Candies For Sale:"  << endl;
    pickRandomCandies(readCandiesFromFile());
    for(int i = 0; i<3; i++)
    {
        cout << _candies[i].name << "|Description: " << _candies[i].description << "|Effect type and Value: " << _candies[i].effect_type << " " << _candies[i].effect_value << "|Candy type: " << _candies[i].candy_type<< "|Price: " << _candies[i].price << endl;

    }

}