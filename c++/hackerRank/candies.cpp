#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'candies' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER_ARRAY arr
 */

long candies(int n, vector<int> arr) {
    
    long result = 0;
    
    std::vector<int> candies(arr.size());
    
    result += arr.size(); //minimum
    
    for(size_t i = 0 ; i < arr.size(); ++i)
    {
        //std::cout << "i:" << i << ": " << arr[i] << std::endl;
        
        if(i >= 1) //check before
        {
            if(arr[i-1] > arr[i]) //score bigger on the before kid
            {
                if(candies[i-1] > candies[i]) // before kid more candies
                {
                    //std::cout << "score bigger before and before has more candies" << std::endl;

                    continue;
                }
                if(candies[i-1] <= candies[i]) // before kid fewer candies
                {
                    //std::cout << "score bigger before and before has less candies. incrementing candies before" << std::endl;

                    auto diff = candies[i] - candies[i-1] + 1;
                    candies[i-1] += diff;
                    result += diff;
                    i--;
                    i--;
                    continue;
                }
            }
            if(arr[i-1] < arr[i])
            {
                if(candies[i-1] >= candies[i])
                {
                    //std::cout << "score lower before and before has more candies. incrementing current" << std::endl;
                    auto diff = candies[i-1] - candies[i] + 1;
                    candies[i] += diff;
                    result += diff;
                    i--;
                    continue;
                }
                if(candies[i-1] < candies[i])
                {
                    //std::cout << "score lower before and before has less candies." << std::endl;

                    continue;
                }
            }
        }
        
        if(i < arr.size() - 1) //check after
        {
            if(arr[i+1] > arr[i]) //score bigger on the after kid
            {
                if(candies[i+1] > candies[i]) // after kid more candies
                {
                    //std::cout << "score bigger after and after has more candies" << std::endl;
                    continue;
                }
                if(candies[i+1] <= candies[i]) // after kid fewer candies
                {
                    //std::cout << "score bigger after and after has less candies. incrementing after" << std::endl;
                    auto diff = candies[i] - candies[i+1] + 1;
                    candies[i+1] += diff;
                    result += diff;
                    continue;
                }
            }
            if(arr[i+1] < arr[i]) //score bigger on the current kid
            {
                if(candies[i+1] >= candies[i]) // after kid more candies
                {
                    //std::cout << "score bigger current and after has more candies. incrementing current" << std::endl;
                    auto diff = candies[i+1] - candies[i] + 1;
                    candies[i] += diff;
                    result += diff;
                    i--;
                    continue;
                }
                if(candies[i+1] < candies[i]) // before kid fewer candies
                {
                    //std::cout << "score lower after and after has fewer candies" << std::endl;
                    continue;
                }
            }
        }
    }
    
    return result;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        string arr_item_temp;
        getline(cin, arr_item_temp);

        int arr_item = stoi(ltrim(rtrim(arr_item_temp)));

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
