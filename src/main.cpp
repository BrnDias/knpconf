#include "instance.hpp"
#include "branchandbound.hpp"
#include <iostream>

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
    bnb.save(output);
    bnb.verify(input);

    return 0;
}
