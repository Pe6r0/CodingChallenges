#include <memory>
#include <bits/stdc++.h>
#include <list>

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
        if(flowerI < state._currentAvailability.size())
        {
            state._flower += 1;
            auto flowerOriginalcost = state._currentAvailability[flowerI];
            if (flowerOriginalcost == -1)
                return nullptr;
            int friendI = state._party;
            if(friendI < state._partyPurchaseHistory.size())
            {
                state._party += 1;
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
                
                return candidate.get();
            }
        }
        return nullptr;
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
        auto state = generateBranch(*expand);
        if(!state)
        {
            expandOptions.remove(expand);
        }
        for (auto& state : expand->_children)
        {
            bool insert = false;
            for(auto stateIn = expandOptions.begin(); stateIn != expandOptions.end(); ++stateIn)
            {
                if((*stateIn)->cost > state->cost)
                {
                    expandOptions.insert(stateIn, state.get());
                    insert = true;
                    break;
                }                
            }
            if(!insert)
            {
                expandOptions.push_back(state.get());
            }
        }
    }

    return expandOptions.front()->cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string c_temp_temp;
    getline(cin, c_temp_temp);

    vector<string> c_temp = split_string(c_temp_temp);

    vector<int> c(n);

    for (int i = 0; i < n; i++) {
        int c_item = stoi(c_temp[i]);

        c[i] = c_item;
    }

    int minimumCost = getMinimumCost(k, c);

    fout << minimumCost << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
