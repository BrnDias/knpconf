#include "branchandbound.hpp"
#include "instance.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>

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

    /* for (auto &&i : itemsCopy)
    {
        cout << i.first << " " << i.second.first << " " << i.second.second << " " << (double)i.second.first / i.second.second << endl;
    }
    cout << endl; */

    /* for (auto &&i : remaining)
    {
        cout << i.first << " " << i.second.first << " " << i.second.second << " " << (double)i.second.first / i.second.second << endl;
    }
    cout << endl; */

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
    // Root node
    Node *root = new Node(), *newNode = nullptr;

    root->setUpperBound(1.0);

    tree.push(root);

    while (!tree.empty())
    {
        root = tree.top();
        tree.pop();

        // BOUND (invalid): if Upper Bound < incumbent solution
        if (root->getUpperBound() > this->incumbentSolution.getTotalValue())
        {

            for (auto i = *root->getRemaining(); i != Instance::getInstance()->getItems()->end(); ++i)
            {
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
}

void BranchAndBound::print()
{
    cout << "=======================================" << endl;
    cout << "Value: " << this->incumbentSolution.getTotalValue() << endl;
    cout << "Weight: " << this->incumbentSolution.getTotalWeight() << endl;
    for (auto &&i : *this->incumbentSolution.getItems())
    {
        cout << i->first << " " << i->second.first << " " << i->second.second << " " << (double)i->second.first / i->second.second << endl;
    }
}