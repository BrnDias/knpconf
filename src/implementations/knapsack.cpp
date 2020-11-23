#include "knapsack.hpp"
#include "instance.hpp"
#include <algorithm>
#include <iterator>

bool cmpIndex(Item a, Item b)
{
    return a.first < b.first;
};

bool cmpPtrIndex(Item *a, Item *b)
{
    return a->first < b->first;
};

bool cmpPtrDensity(Item *a, Item *b)
{
    return ((double)a->second.first / a->second.second) > ((double)b->second.first / b->second.second);
};

Knapsack::Knapsack()
{
    totalWeight = 0;
    totalValue = 0;
}

Knapsack::Knapsack(const Knapsack &old)
{
    this->totalWeight = old.totalWeight;
    this->totalValue = old.totalValue;
    this->items = old.items;
}

Knapsack::~Knapsack()
{
}

uint_fast16_t Knapsack::getTotalWeight() const
{
    return this->totalWeight;
}

uint_fast16_t Knapsack::getTotalValue() const
{
    return this->totalValue;
}

vector<Item *> *Knapsack::getItems()
{
    return &this->items;
}

bool Knapsack::addItem(Item *item)
{
    // Weigth
    if (item->second.second + this->totalWeight > Instance::getInstance()->getCapacity())
    {
        return false;
    }
    // Conflicts
    for (auto &&i : this->items)
    {
        // Overflow or conflict
        if (Instance::getInstance()->hasConflict(item->first, i->first))
        {
            return false;
        }
    }
    // Add + update
    this->totalValue += item->second.first;
    this->totalWeight += item->second.second;
    this->items.push_back(item);

    sort(this->items.begin(), this->items.end(), cmpPtrIndex);
    return true;
}