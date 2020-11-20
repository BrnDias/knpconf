#include <iostream>
#include "knapsack.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 3){
        cerr << "Invalid arguments!" << endl;
        exit(1);
    }

    const string input = argv[1], output = argv[2]; 

    Knapsack* knp = new Knapsack(input);

    return 0;
}
