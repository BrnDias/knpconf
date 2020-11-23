#include "node.hpp"
#include "instance.hpp"

Node::Node()
{
    this->solution = Knapsack();
    this->upperBound = 0.00;
    this->remaining = Instance::getInstance()->getItems()->begin();
}

Node::Node(Node &node)
{
    this->solution = *node.getSolution();
    this->upperBound = node.getUpperBound();
    this->remaining = *node.getRemaining();
}

Node::~Node()
{
}

Knapsack *Node::getSolution()
{
    return &this->solution;
}

void Node::setSolution(const Knapsack solution)
{
    this->solution = solution;
}

double Node::getUpperBound() const
{
    return this->upperBound;
}

void Node::setUpperBound(const double upperBound)
{
    this->upperBound = upperBound;
}

uint_fast16_t Node::getLowerBound() const
{
    return this->solution.getTotalValue();
}

vector<Item>::iterator *Node::getRemaining()
{
    return &this->remaining;
}

void Node::setRemaining(const vector<Item>::iterator remaining)
{
    this->remaining = remaining;
}

bool operator<(const Node &a, const Node &b)
{
    return a.getUpperBound() < b.getUpperBound();
}

bool operator>(const Node &a, const Node &b)
{
    return a.getUpperBound() > b.getUpperBound();
}