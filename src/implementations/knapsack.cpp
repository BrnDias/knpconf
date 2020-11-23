#include "knapsack.hpp"
#include "instance.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>

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

double Knapsack::fractionalKnapsack(vector<Item>::iterator begin) const
{
    double totalValue = this->totalValue;
    uint_fast16_t totalWeight = this->totalWeight,
                  newWeight = this->totalWeight;

    vector<Item> knapsackCopy, remaining;
    vector<Item> itemsCopy;

    copy(begin, Instance::getInstance()->getItems()->end(), back_inserter(itemsCopy));

    sort(itemsCopy.begin(), itemsCopy.end(), cmpIndex);
    knapsackCopy.reserve(this->items.size());
    transform(this->items.begin(), this->items.end(),
              back_inserter(knapsackCopy), [](Item *item) { return *item; });

    set_difference(itemsCopy.begin(), itemsCopy.end(),
                   knapsackCopy.begin(), knapsackCopy.end(),
                   back_inserter(remaining), cmpIndex);

    /* for (auto &&i : itemsCopy)
    {
        cout << i.first << " " << i.second.first << " " << i.second.second << " " << (double)i.second.first / i.second.second << endl;
    }
    cout << endl; */

    for (auto &&i : remaining)
    {
        cout << i.first << " " << i.second.first << " " << i.second.second << " " << (double)i.second.first / i.second.second << endl;
    }
    cout << endl;

    sort(remaining.begin(), remaining.end(), cmpDensity);

    bool add = true;
    for (auto &&newItem : remaining)
    {
        if (totalWeight >= Instance::getInstance()->getCapacity())
        {
            break;
        }

        add = true;

        // Verify Conflicts
        for (auto &&knpItem : this->items)
        {
            if (Instance::getInstance()->hasConflict(newItem.first, knpItem->first))
            {
                add = false;
                break;
            }
        }

        if (add)
        {
            newWeight = newItem.second.second + totalWeight;

            if (newWeight <= Instance::getInstance()->getCapacity())
            {

                totalValue += newItem.second.first;
                totalWeight = newWeight;
            }
            else
            {
                totalValue += (Instance::getInstance()->getCapacity() - totalWeight) * ((double)newItem.second.first / newItem.second.second);
                totalWeight = Instance::getInstance()->getCapacity();
            }
        }
    }

    return totalValue;
}