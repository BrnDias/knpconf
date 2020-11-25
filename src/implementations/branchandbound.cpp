#include "branchandbound.hpp"
#include "instance.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>

BranchAndBound::BranchAndBound()
{
    this->incumbentSolution = Knapsack();
}

BranchAndBound::~BranchAndBound()
{
}

bool BranchAndBound::timeLimitReached()
{
    auto currentTime = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = currentTime - this->startTime;

    if (elapsed.count() >= this->timeLimit)
    {
        return true;
    }
    return false;
}

double BranchAndBound::knpFrac(Knapsack *knapsack, vector<Item>::iterator begin)
{
    double totalValue = knapsack->getTotalValue();
    uint_fast16_t totalWeight = knapsack->getTotalWeight(),
                  newWeight = knapsack->getTotalWeight();

    vector<Item> knapsackCopy, remaining;
    vector<Item> itemsCopy;

    copy(begin, Instance::getInstance()->getItems()->end(), back_inserter(itemsCopy));

    sort(itemsCopy.begin(), itemsCopy.end(), cmpIndex);
    knapsackCopy.reserve(knapsack->getItems()->size());
    transform(knapsack->getItems()->begin(), knapsack->getItems()->end(),
              back_inserter(knapsackCopy), [](Item *item) { return *item; });

    set_difference(itemsCopy.begin(), itemsCopy.end(),
                   knapsackCopy.begin(), knapsackCopy.end(),
                   back_inserter(remaining), cmpIndex);

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
        for (auto &&knpItem : *knapsack->getItems())
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

void BranchAndBound::run()
{
    // Start time counter
    this->startTime = chrono::high_resolution_clock::now();

    // Root node
    Node *root = new Node(),
         *newNode = nullptr;

    root->setUpperBound(1.0);

    tree.push(root);

    bool timeEnded = false;

    while (!tree.empty() && !timeEnded)
    {
        root = tree.top();
        tree.pop();

        // BOUND (invalid): if Upper Bound < incumbent solution
        if (root->getUpperBound() > this->incumbentSolution.getTotalValue())
        {

            // Root node expansion
            for (auto i = *root->getRemaining(); i != Instance::getInstance()->getItems()->end(); ++i)
            {
                // TIME LIMIT
                /* timeEnded = this->timeLimitReached();
                if (timeEnded)
                {
                    break;
                } */

                newNode = new Node(*root);

                // BOUND (invalid): if there's a conflict OR
                // BOUND (invalid): if new weigth > max capacity
                if (!newNode->getSolution()->addItem(&*i))
                {
                    delete newNode;
                    continue;
                }

                *newNode->getRemaining() = next(i);

                newNode->setUpperBound(this->knpFrac(newNode->getSolution(), *newNode->getRemaining()));

                // BOUND (invalid): if Upper Bound < incumbent solution
                if (newNode->getUpperBound() <= this->incumbentSolution.getTotalValue())
                {
                    delete newNode;
                    continue;
                }

                // BOUND (valid): if limits are equals
                if (newNode->getLowerBound() == newNode->getUpperBound())
                {
                    if (this->incumbentSolution.getTotalValue() < newNode->getSolution()->getTotalValue())
                    {
                        this->incumbentSolution = *newNode->getSolution();
                    }
                    delete newNode;
                    continue;
                }

                // BOUND (valid): if there is no elements
                if (*newNode->getRemaining() == Instance::getInstance()->getItems()->end())
                {
                    if (this->incumbentSolution.getTotalValue() < newNode->getSolution()->getTotalValue())
                    {
                        this->incumbentSolution = *newNode->getSolution();
                    }
                    delete newNode;
                    continue;
                }

                tree.push(newNode);
            }
        }

        delete root;
    }

    while (!tree.empty())
    {
        root = tree.top();
        tree.pop();
        delete root;
    }
}

void BranchAndBound::save(const string output)
{
    // Read Instance
    ofstream file("./outputs/" + output);

    if (file.is_open())
    {
        // Write profit
        file << this->incumbentSolution.getTotalValue() << " ";

        // Write totoal items
        file << this->incumbentSolution.getItems()->size();

        // Write items
        for (auto &&i : *this->incumbentSolution.getItems())
        {
            file << " " << i->first + 1;
        }

        file.close();
    }
    else
    {
        cerr << "Unable to create file!" << endl;
        exit(1);
    }
}

void BranchAndBound::verify(const string input)
{
    cout << "=================================================================" << endl;
    cout << "INSTANCE: " << input << endl
         << endl;

    bool hasConflict = false;

    cout << "Profit:          " << this->incumbentSolution.getTotalValue() << endl;
    cout << "Max capacity:    " << Instance::getInstance()->getCapacity() << endl;
    cout << "Solution weight: " << this->incumbentSolution.getTotalWeight() << endl
         << endl;

    cout << "Conflicts: " << endl;

    for (auto i = this->incumbentSolution.getItems()->begin(); i != this->incumbentSolution.getItems()->end(); ++i)
    {
        for (auto j = next(i); j != this->incumbentSolution.getItems()->end(); ++j)
        {
            if (Instance::getInstance()->hasConflict((*i)->first, (*j)->first))
            {
                cout << "(" << (*i)->first + 1 << ", " << (*j)->first << ")" << endl;
                hasConflict = true;
            }
        }
    }
    if (!hasConflict)
    {
        cout << "Conflicts not found!" << endl;
    }
    cout << endl;
}