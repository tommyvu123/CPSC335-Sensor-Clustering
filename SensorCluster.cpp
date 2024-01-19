#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int nic) 
    {
        return (nic / 100000 % 10);
    }


// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int nic) 
    {
        return (nic / 10000 % 10);
    }



// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int nic) 
    {
        return (nic / 1000 % 10);
    }

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int nic) 
    {
        return (nic / 100 % 10);
    }

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int nic) {
    return (nic / 10 % 10);
}

// function to return the hash value based on the sixth digit
unsigned int hashfct6(unsigned int nic) {
    return (nic / 1 % 10);
}

// Constructor for struct Item
Item::Item(string itemName, unsigned int nic) :itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
    ifstream myfile(filename);

    if (myfile.is_open()) {
        cout << "Successfully opened file " << filename << endl;
        string itemName;
        unsigned int nic;
        while (myfile >> itemName >> nic) {
            if (itemName.size() > 0)
                addItem(itemName, nic);
        }
        myfile.close();
    }
    else
        throw std::invalid_argument("Could not open file " + filename);
}

void SensorNIC::addItem(string itemName, unsigned int nic) {
    Item item(itemName, nic);
    hT1.insert(std::make_pair(nic, item));
    hT2.insert(std::make_pair(nic, item));
    hT3.insert(std::make_pair(nic, item));
    hT4.insert(std::make_pair(nic, item));
    hT5.insert(std::make_pair(nic, item));
    hT6.insert(std::make_pair(nic, item));
}

bool SensorNIC::removeItem(unsigned int nic) {
    // TODO: implement this function, then delete the return statement below

   // function that removes the sensor specified by the nic value from the network
   // if sensor is found, then it is removed and the function returns true
   // else returns false
    auto it = hT1.find(nic);
    if (hT1.find(nic) != hT1.end())
    {
        hT1.erase(nic);
        hT2.erase(nic);
        hT3.erase(nic);
        hT4.erase(nic);
        hT5.erase(nic);
        hT6.erase(nic);
    }
    return true;
}
unsigned int SensorNIC::calc_balance(CustomHashTable h)
{
    unsigned int max = h.bucket_size(0);
    unsigned int min = h.bucket_size(0);
    unsigned int balance = 0;
    for (unsigned int i = 0; i < 10; ++i)
    {
        if (min > h.bucket_size(i))
            min = h.bucket_size(i);
        if (max < h.bucket_size(i))
            max = h.bucket_size(i);
    }
    return (max - min);
}

unsigned int SensorNIC::bestHashing() {
    // TODO: implement this function, then delete the return statement below

    // function that decides the best hash function, i.e. the ones among
    // fct1-fct6 that creates the most balanced sensor network for the current
    // set of NIC addresses, i.e. data member allItems

    unsigned int best = 0;
    unsigned int h[]{
        calc_balance(hT1), calc_balance(hT2), calc_balance(hT3),
        calc_balance(hT4), calc_balance(hT5), calc_balance(hT6) };
    // Hints:
    // Calculate the balance of each hashtable, one by one.
    for (unsigned int i = 1; i < 6; i++)
    {
        if (h[best] > h[i])
            best = i;
    }
    // Then, calculate the lowest balance
    return best + 1;
}


// ALREADY COMPLETED
size_t SensorNIC::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size()) || (hT1.size() != hT6.size()))
        throw std::length_error("Hash table sizes are not the same");

    return hT1.size();
}
