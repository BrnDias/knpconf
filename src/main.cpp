#include <iostream>
#include "instance.hpp"
#include "branchandbound.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cerr << "Invalid arguments!" << endl;
        exit(1);
    }

    const string input = argv[1], output = argv[2];

    Instance::init(input);

    Instance::getInstance();

    BranchAndBound bnb = BranchAndBound();

    bnb.run();
    bnb.print();

    /* cout << "original 1: " << Instance::getInstance()->getItems()->at(2).first << endl
         << endl;

    auto x = Instance::getInstance()->getItem(2);

    set<Item *> items;
    //Knapsack *knp = new Knapsack();
    items.emplace(x);

    cout
        << "original 2: " << (*items.begin())->second.first << endl
        << endl;

    (*items.begin())->second.first = 15;
    cout << "original 1: " << Instance::getInstance()->getItems()->at(2).first << endl
         << endl;
    cout << "original 2: " << (*items.begin())->second.first << endl
         << endl;
 */

    /* for (auto &&i : *Instance::getInstance()->getItems())
    {
        cout << i.first << " " << i.second.first << " " << i.second.second << " " << (double)i.second.first / i.second.second << endl;
    }

    Knapsack knp = Knapsack();
    cout << endl;
    cout << knp.addItem(Instance::getInstance()->getItem(0)) << endl;
    cout << knp.addItem(Instance::getInstance()->getItem(3)) << endl;
    cout << endl;

    for (auto &&i : *knp.getItems())
    {
        cout << i->first << " " << i->second.first << " " << i->second.second << " " << (double)i->second.first / i->second.second << endl;
    }
    cout << endl;

    cout << knp.fractionalKnapsack(Instance::getInstance()->getItems()->begin() + 3) << endl
         << endl; */

    /* cout << "original: " << Instance::getInstance()->getItems()->at(2).first << endl
         << endl;

    pair<const uint_fast16_t, pair<uint_fast16_t, uint_fast16_t>> *item = Instance::getInstance()->getItem(2);

    item->second.first = 10;
    cout << "copia: " << item->second.first << endl
         << endl;
    cout
        << "original: " << Instance::getInstance()->getItems()->at(2).first << endl
        << endl;
 */
    return 0;
}
