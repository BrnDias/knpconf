#ifndef NODE_HPP
#define NODE_HPP

#include "item.hpp"
#include "knapsack.hpp"
#include <vector>

using namespace std;

class Node
{
private:
    Knapsack solution;
    double upperBound;
    vector<Item>::iterator remaining;

public:
    Node();
    Node(Node &);
    ~Node();

    Knapsack *getSolution();
    void setSolution(const Knapsack);

    double getUpperBound() const;
    void setUpperBound(const double);

    // Lower bound = solution's totalVbalue()
    uint_fast16_t getLowerBound() const;

    vector<Item>::iterator *getRemaining();
    void setRemaining(const vector<Item>::iterator);

    friend bool operator<(const Node &a, const Node &b);
    friend bool operator>(const Node &a, const Node &b);
};

#endif