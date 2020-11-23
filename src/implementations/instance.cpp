#include "instance.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

bool cmpDensity(Item a, Item b)
{
    return ((double)a.second.first / a.second.second) > ((double)b.second.first / b.second.second);
};

Instance *Instance::instance = nullptr;

Instance::Instance(const string instance)
{
    // Read Instance
    ifstream file("./instances/" + instance);

    if (file.is_open())
    {
        uint_fast16_t value = 0, from = -1, to = -1;

        // Read capacity
        file >> this->capacity;

        uint_fast16_t size = 0;

        // Read number of items
        file >> size;

        this->items.reserve(size);

        // Read value
        for (uint_fast16_t i = 0; i < size; i++)
        {
            file >> value;
            items.push_back(make_pair(i, make_pair(value, 0)));
        }

        // Read weight
        for (uint_fast16_t i = 0; i < size; i++)
        {
            file >> items[i].second.second;
        }

        // Sort by density
        sort(items.begin(), items.end(), cmpDensity);

        // Read number of conflicts
        file >> size;

        // Read conflicts
        for (uint_fast16_t i = 0; i < size; i++)
        {
            file >> from;
            file >> to;

            this->conflits[from - 1].emplace(to - 1);
        }

        file.close();
    }
    else
    {
        cerr << "Unable to open file!" << endl;
        exit(1);
    }
}

Instance::~Instance()
{
}

void Instance::init(const string instance)
{
    if (!Instance::instance)
    {
        Instance::instance = new Instance(instance);
    }
}

Instance *Instance::getInstance()
{
    if (!Instance::instance)
    {
        cerr << "Instance not initialized!" << endl;
        exit(1);
    }
    return Instance::instance;
}

uint_fast16_t Instance::getCapacity() const
{
    return this->capacity;
}

map<uint_fast16_t, set<uint_fast16_t>> *Instance::getConflits()
{
    return &this->conflits;
}

vector<Item> *Instance::getItems()
{
    return &this->items;
}

Item *Instance::getItem(uint_fast16_t index)
{
    return &this->items[index];
}

/* vector<Item>::iterator Instance::getItemIterator(uint_fast16_t index)
{
    return this->items.begin() + index;
}
 */

const bool Instance::hasConflict(uint_fast16_t itemA, uint_fast16_t itemB)
{
    if (itemA < itemB)
    {
        return this->conflits[itemA].find(itemB) != this->conflits[itemA].end();
    }
    else
    {
        return this->conflits[itemB].find(itemA) != this->conflits[itemB].end();
    }
}