#include "knapsack.hpp"
#include <iostream>
#include <fstream>

Knapsack::Knapsack(const string instance)
{
    cout << "New instance of Knapsack" << endl;
    // Read Instance

    ifstream file(instance);
    string line = "";

    if (file.is_open()){

        while (getline(file,line))
        {
        cout << line << endl;
        }
        file.close();

    }else{
        cerr << "Unable to open file" << endl;
    }

}

/* Knapsack::~Knapsack()
{
    delete[] this->conflits;
} */