#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include <cstdint>
#include <map>
#include <vector>

using namespace std; 

class Knapsack
{
private:
    uint_fast16_t capacity;
    map<uint_fast16_t, pair<uint_fast8_t, uint_fast16_t>> items;
    vector<uint_fast16_t> conflits[];

public:
    Knapsack(const string);
    ~Knapsack();
};

#endif