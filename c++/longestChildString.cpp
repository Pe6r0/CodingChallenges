#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include <algorithm>
#include <bitset>

size_t findBiggestCommonChild(std::string& one, std::string&two)
{
    size_t n = one.size();
    size_t biggestChild = n;
    assert(one.size() == two.size());
    if (one == two)
    {
        return biggestChild;
    }

    auto getBiggestSubStringOrBust = [&](auto&& getBiggestSubStringOrBust, int pos1, int pos2, int del1, int del2, int delMax)
    {
        if (pos1 == n && pos2 == n)
        {
            return true;
        }

        if (one[pos1] == two[pos2])
        {
            return getBiggestSubStringOrBust(getBiggestSubStringOrBust, ++pos1, ++pos2, del1, del2, delMax);
        }
        else {
            if (del1 >= delMax && del2 >= delMax)
            {
                return false;
            }
            if (del1 >= delMax)
            {
                return getBiggestSubStringOrBust(getBiggestSubStringOrBust, pos1, ++pos2, del1, ++del2, delMax);
            }
            if (del2 >= delMax)
            {
                return getBiggestSubStringOrBust(getBiggestSubStringOrBust, ++pos1, pos2, ++del1, del2, delMax);
            }
            return getBiggestSubStringOrBust(getBiggestSubStringOrBust, pos1, ++pos2, del1, ++del2, delMax) || getBiggestSubStringOrBust(getBiggestSubStringOrBust, ++pos1, pos2, ++del1, del2, delMax);
        }
    };


    for(int numberOfAllowedDeletions = 0; numberOfAllowedDeletions < n; ++numberOfAllowedDeletions)
    {
        for (int startPositionOne = 0; startPositionOne < n; ++startPositionOne)
        {
            for (int startPositionTwo = 0 ; startPositionTwo < n ; ++startPositionTwo)
            {
                int numberOfDeletions1 = startPositionOne;
                int numberOfDeletions2 = startPositionTwo;
                if (numberOfDeletions1 > numberOfAllowedDeletions || numberOfDeletions2 > numberOfAllowedDeletions)
                {
                    break;
                }
                if (one[startPositionOne] == two[startPositionTwo])
                {
                    //look ahead with the alloted deletions
                    if (getBiggestSubStringOrBust(getBiggestSubStringOrBust, startPositionOne, startPositionTwo, numberOfDeletions1, numberOfDeletions2, numberOfAllowedDeletions))
                    {
                        return biggestChild - numberOfAllowedDeletions;
                    }
                }
                else 
                {
                    continue;
                    //advance the lowest, if equal advance both.
                    //attempt one advance

                    //attempt right advance

                    //advance both


                }
            }
        }
    }
    /*
    auto& testStrings = [&](const std::vector<bool>& ignorePositions1, const std::vector<bool>& ignorePositions2)
    {
        for (int i = 0, j = 0; i < n || j < n;)
        {
            if (!ignorePositions1[i])
            {
                i++;
                continue;
            }
            if (!ignorePositions2[i])
            {
                j++;
                continue;
            }
            if (one[i] != two[j])
            {
                return false;
            }
        }
        return true;
    };

    while (biggestChild > 0)
    {
        int positionsToIgnore = n - biggestChild;
        const std::vector<bool> ignorePositions1(n, false);
        const std::vector<bool> ignorePositions2(n, false);

        --biggestChild;
    }*/
}



int main()
{
    std::string one = "ADDCDDCDD";
    std::string two = "ZQEADDCDD";

    findBiggestCommonChild(one, two);
}
