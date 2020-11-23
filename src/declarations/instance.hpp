#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "item.hpp"
#include <set>
#include <map>
#include <vector>
#include <string>

using namespace std;

bool cmpDensity(Item, Item);

class Instance
{
private:
    uint_fast16_t capacity;
    vector<Item> items;
    map<uint_fast16_t, set<uint_fast16_t>> conflits;

    // Singleton
    static Instance *instance;

    Instance(const string);
    ~Instance();

public:
    static void init(const string);
    static Instance *getInstance();

    uint_fast16_t getCapacity() const;
    map<uint_fast16_t, set<uint_fast16_t>> *getConflits();
    vector<Item> *getItems();
    Item *getItem(uint_fast16_t);

    const bool hasConflict(uint_fast16_t, uint_fast16_t);
};

#endif