#ifndef BRANCH_AND_BOUND_HPP
#define BRANCH_AND_BOUND_HPP

#include "node.hpp"
#include <chrono>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class BranchAndBound
{
private:
    // Time
    const double timeLimit = 771.0;
    chrono::time_point<std::chrono::high_resolution_clock> startTime;
    bool timeLimitReached();

    // Bnb
    Knapsack incumbentSolution;
    priority_queue<Node *, vector<Node *>, greater<vector<Node *>::value_type>> tree;

    // Upper Bound
    double knpFrac(Knapsack *, vector<Item>::iterator);

    // Lower Bound

public:
    BranchAndBound();
    ~BranchAndBound();

    void run();
    void save(const string);
    void verify(const string);
};

#endif