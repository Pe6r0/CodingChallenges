#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */
 
 bool getBiggestSubStringOrBust(int pos1, int pos2, int del1, int del2, int delMax, int n, const std::string& one, const std::string& two)
{
    if (pos1 == n && pos2 == n)
    {
        return true;
    }

    if (one[pos1] == two[pos2])
    {
        return getBiggestSubStringOrBust(++pos1, ++pos2, del1, del2, delMax, n, one, two);
    }
    else {
        if (del1 >= delMax && del2 >= delMax)
        {
            return false;
        }
        if (del1 >= delMax)
        {
            return getBiggestSubStringOrBust( pos1, ++pos2, del1, ++del2, delMax, n, one, two);
        }
        if (del2 >= delMax)
        {
            return getBiggestSubStringOrBust(++pos1, pos2, ++del1, del2, delMax, n, one, two);
        }
        
        return getBiggestSubStringOrBust(pos1, ++pos2, del1, ++del2, delMax, n, one, two) || getBiggestSubStringOrBust(++pos1, pos2, ++del1, del2, delMax, n, one, two);
    }
}

int commonChild(string one, string two)
{
    //timeout on some tests but finishes succesfully on rest
    size_t n = one.size();
    size_t biggestChild = n;
    assert(one.size() == two.size());
    if (one == two)
    {
        return biggestChild;
    }

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
                    if (getBiggestSubStringOrBust(startPositionOne, startPositionTwo, numberOfDeletions1, numberOfDeletions2, numberOfAllowedDeletions, n, one, two))
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
    return 0;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

    return 0;
}
