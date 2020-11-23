#ifndef KNAPSACK_HPP
#define KNAPSACK_HPP

#include "item.hpp"
#include <vector>

using namespace std;

bool cmpIndex(Item, Item);
bool cmpPtrIndex(Item *, Item *);
bool cmpPtrDensity(Item *, Item *);

class Knapsack
{
private:
    uint_fast16_t totalWeight;
    uint_fast16_t totalValue;
    vector<Item *> items;

public:
    Knapsack();
    Knapsack(const Knapsack &);
    ~Knapsack();

    uint_fast16_t getTotalWeight() const;
    uint_fast16_t getTotalValue() const;
    vector<Item *> *getItems();

    bool addItem(Item *);
    double fractionalKnapsack(vector<Item>::iterator) const;
};

#endif