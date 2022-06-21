#include <vector>
#include <assert.h>
#include <algorithm>

template <class T>
void bottomUpMergeSort(std::vector<T>& data) //counts the number of iterations also
{
    long iterations = 0;
    int pairsize = 1;
    int n = data.size();

    auto& sortTwoLists = [&](int pos1, int pairSize)
    {
        if (pos1 + pairSize > n)
        {
            return;
        }
        int pos2 = pos1 + pairSize;
        assert(pos1 < pos2);
        int end1 = std::min({ pos1 + pairSize, n });
        int end2 = std::min({ pos2 + pairSize, n });

        for (int i = pos1, j = pos2; i < end1 && j < end2;)
        {
            if (data[i] < data[j])
            {
                ++i;
                continue;
            }
            else
            {
                for (int t = i; t < j; ++t)
                {
                    std::swap(data[t], data[j]);
                }
                iterations += j - i;
                ++i;
                ++end1;
                ++j;
            }
        }
    };

    while(pairsize < n)
    {
        for (int i = 0; i < data.size(); i += pairsize * 2)
        {
            sortTwoLists(i, pairsize);
        }
        pairsize *= 2;
    }
}



int main()
{
    std::vector<int> test = { 4 ,3, 2, 1 };

    bottomUpMergeSort(test);
}
