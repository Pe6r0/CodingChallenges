#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <algorithm>
#include <bitset>
#include <memory>
#include <iostream>
#include <list>

struct State
{
    State* _parent = nullptr;
    std::vector<std::unique_ptr<State>> _children;

    std::vector<int> _currentAvailability; //-1 means it's been purchased
    std::vector<int> _partyPurchaseHistory; //vector of friends with how many flowers each bought
    int depth = 0;
    int cost = 0;

};

int costFlowerFunction(int numberOfSalesForThatCustomer, int price)
{
    return (numberOfSalesForThatCustomer + 1) * price;
}

int getMinimumCost(int k, std::vector<int> c) //number of friends and each flower's original price
{
    //potential venues for improvement, make generation more fluid instead of Row lookahead
    const auto generateBranches = [&](State& state) //branches are done by each friend purchasing a flower until all flowers are purchased.
    {
        for (size_t flowerI = 0; flowerI < state._currentAvailability.size(); ++flowerI)
        {
            auto flowerOriginalcost = state._currentAvailability[flowerI];
            if (flowerOriginalcost == -1)
                continue;
            for (size_t friendI = 0; friendI < state._partyPurchaseHistory.size(); ++friendI)
            {
                auto candidate = std::make_unique<State>();

                candidate->_parent = &state;
                candidate->_currentAvailability = state._currentAvailability;
                candidate->_partyPurchaseHistory = state._partyPurchaseHistory;
                candidate->cost = state.cost;
                candidate->depth = state.depth;
                //purchase of flower by partyMember
                auto numberOfFlowersBoughtByPartyMember = state._partyPurchaseHistory[friendI];
                int price = costFlowerFunction(numberOfFlowersBoughtByPartyMember, flowerOriginalcost);
                candidate->_currentAvailability[flowerI] = -1;
                candidate->_partyPurchaseHistory[friendI] += 1;
                candidate->cost += price;
                candidate->depth += 1;

                state._children.push_back(std::move(candidate));

                std::sort(state._children.begin(), state._children.end(), [&](const std::unique_ptr<State>& a, const std::unique_ptr<State>& b) { return a->cost < b->cost; });
            }
        }
    };

    //generate branches? keep picking the lowest cost from the entire tree.

    auto rootNode = std::make_unique<State>();
    rootNode->_currentAvailability = c;
    rootNode->_partyPurchaseHistory = std::vector<int>(k, 0);
    rootNode->depth = 0;
    rootNode->cost = 0;

    generateBranches(*(rootNode.get()));

    std::vector<int> emptycondition(c.size(), -1);

    std::list<State*> expandOptions;
    for (auto& state : rootNode->_children)
    {
        expandOptions.push_back(state.get());
    }

    while (expandOptions.front()->_currentAvailability != emptycondition)
    {
        auto expand = expandOptions.front();
        generateBranches(*expand);
        for (auto& state : expand->_children)
        {
            expandOptions.push_back(state.get());
        }
        expandOptions.remove(expand);
        expandOptions.sort([&](const State* a, const State* b) { return a->cost < b->cost; });

    }

    return expandOptions.front()->cost;
}

int main()
{
    int friends = 3;
    std::vector<int> flowerPrices = {1, 2, 3};
    std::cout << ":" << std::endl;
    std::cout << getMinimumCost(friends, flowerPrices) << std::endl;
}
