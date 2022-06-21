#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countInversions' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

long countInversions(vector<int> arr) 
{
    //funcionally complete but cannot pass all test cases due to timeout
    long iterations = 0;
    int pairsize = 1;
    int n = arr.size();

    auto sortTwoLists = [&](int pos1, int pairSize)
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
            if (arr[i] <= arr[j])
            {
                ++i;
                continue;
            }
            else
            {
                std::rotate(arr.rbegin() + (n - (j + 1)), arr.rbegin() + (n - j), arr.rbegin() + (n -i));
                iterations += j - i;
                ++i;
                ++end1;
                ++j;
            }
        }
    };
    
    while(pairsize < n)
    {
        for (int i = 0; i < arr.size(); i += pairsize * 2)
        {
            sortTwoLists(i, pairsize);
        }
        pairsize *= 2;
    }
    
    return iterations;
    
    //passes but takes too long
    long inversions = 0;
    bool flag = true;
    while(flag)
    {
        flag = false;
        for(int i = 0 ; i < arr.size() - 1; ++i)
        {
            if(arr[i] > arr[i+1])
            {
                std::swap(arr[i], arr[i+1]);
                inversions++;
                flag = true;
                break;
                
            }
        }
    }
    return inversions;
    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        long result = countInversions(arr);

        fout << result << "\n";
    }

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

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
