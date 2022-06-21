#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <algorithm>
#include <bitset>
#include <memory>

struct State
{
    State* _parent = nullptr;
    std::vector<State*> _children;

    std::vector<int> _currentAvailability; //-1 means it's been purchased
    std::vector<int> _partyPurchaseHistory; //vector of friends with how many flowers each bought
    int depth = 0;
    int cost = 0;
    }
};


int costFlowerFunction(int numberOfSalesForThatCustomer, int price)
{
    return (numberOfSalesForThatCustomer + 1) * price;
}


int getMinimumCost(int k, std::vector<int> c) //number of friends and each flower's original price
{
    auto rootNode = std::make_unique<State>();

    const auto generateBranches = [&](State& state) //branches are done by each friend purchasing a flower until all flowers are purchased.
    {
        for (const auto& flower : state._currentAvailability)
        {
            for (const auto& partyMember : state._partyPurchaseHistory)
            {
                auto candidate = std::make_unique<State>();
                state._children.push_back(&*candidate);
                
                candidate->_parent = &state;
                candidate->_currentAvailability = state._currentAvailability;
                candidate->_partyPurchaseHistory = state._partyPurchaseHistory;
                candidate->depth += 1;
                //purchase of flower by partyMember
                state._currentAvailability


            }

        }
    };

    //generate branches? keep picking the lowest cost from the entire tree.
}



int main()
{
    std::string one = "ADDCDDCDD";
    std::string two = "ZQEADDCDD";

    findBiggestCommonChild(one, two);
}
