#include <memory>
//#include <bits/stdc++.h>
#include <list>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

struct State
{
    State* _parent = nullptr;
    std::vector<std::unique_ptr<State>> _children;

    std::vector<int> _currentAvailability; //-1 means it's been purchased
    std::vector<int> _partyPurchaseHistory; //vector of friends with how many flowers each bought
    int depth = 0;
    int cost = 0;
    int _party = 0;
    int _flower = 0;

};

int costFlowerFunction(int numberOfSalesForThatCustomer, int price)
{
    return (numberOfSalesForThatCustomer + 1) * price;
}

int getMinimumCost(int k, std::vector<int> c) //number of friends and each flower's original price
{
    const auto generateBranch = [&](State& state)->State*
    {
        int flowerI = state._flower;
        int friendI = state._party;

        if (flowerI == c.size())
        {
            state._flower = -1;
            return nullptr;
        }
        if (friendI == k)
        {
            state._flower += 1;
            state._party = 0;
            return nullptr;
        }
        state._party += 1;

        auto flowerOriginalcost = state._currentAvailability[flowerI];
        if (flowerOriginalcost == -1)
            return nullptr;

        auto candidate = unique_ptr<State>(new State());

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

        return state._children.back().get();
    };

    //generate branches? keep picking the lowest cost from the entire tree.

    auto rootNode = unique_ptr<State>(new State());
    rootNode->_currentAvailability = c;
    rootNode->_partyPurchaseHistory = std::vector<int>(k, 0);
    rootNode->depth = 0;
    rootNode->cost = 0;

    std::vector<int> emptycondition(c.size(), -1);

    std::list<State*> expandOptions;

    expandOptions.push_back(rootNode.get());

    while (expandOptions.front()->_currentAvailability != emptycondition)
    {
        auto expand = expandOptions.front();
        std::cout << "checking";
        int pu = 0;
        for (auto f : expand->_partyPurchaseHistory)
        {
            pu += f;
            std::cout << " " << f;
        }
        std::cout << " " << pu << std::endl;

        auto state = generateBranch(*expand);
        if (expand->_flower == -1)
        {
            expandOptions.remove(expand);
            continue;
        }
        if (state == nullptr)
        {
            continue;
        }
        if (state->_currentAvailability == emptycondition)
        {
            return state->cost;
        }
        for (auto& state : expand->_children)
        {
            bool insert = false;
            for (auto stateIn = expandOptions.begin(); stateIn != expandOptions.end(); ++stateIn)
            {
                if ((*stateIn)->cost > state->cost)
                {
                    expandOptions.insert(stateIn, state.get());
                    insert = true;
                    break;
                }
            }
            if (!insert)
            {
                expandOptions.push_back(state.get());
            }
        }
    }

    return expandOptions.front()->cost;
}

int main()
{
    int friends = 3;
    std::vector<int> prices = { 1,3,5,7,9 };
    int minimumCost = getMinimumCost(friends, prices);

    cout << minimumCost << "\n";

    return 0;
}
