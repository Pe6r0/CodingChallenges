#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the countTriplets function below.
bool satisfiesCondition(long a, long b, long c, long r)
{
    return a * r == b && b * r == c;
}


long countTriplets(vector<long> arr, long r) {
    long result = 0;
    //runs 80% of tests
    std::map<long, vector<long>> indices;

    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        indices[*i].push_back(std::distance(arr.begin(), i));
    }
    for (int ai = 0; ai < arr.size() - 2; ++ai)
    {
        auto b = indices.find(arr[ai] * r);
        if (b != indices.end())
        {
            auto c = indices.find(arr[ai] * r * r);
            if (c != indices.end())
            {
                for (int bi : b->second)
                {
                    for (int ci : c->second)
                    {
                        if (ai < bi && bi < ci)
                        {
                            result++;
                        }
                    }
                }
            }
        }
    }
    return result;
    //too slow
    //std::cout << "=r: " << r << std::endl;
    for (int a = 0; a < arr.size() - 2; ++a)
    {
        for (int b = 1; b < arr.size() - 1; ++b)
        {
            for (int c = 2; c < arr.size(); ++c)
            {

                if (satisfiesCondition(arr[a], arr[b], arr[c], r))
                {
                    result++;
                    //std::cout << ":result "<<arr[a] << " "<< arr[b]  << " " << arr[c] << std::endl;
                    //break;
                }
                std::cout << ":notresult " << arr[a] << " " << arr[b] << " " << arr[c] << std::endl;
                if (arr[b] * r < arr[c])
                {
                    //std::cout << "++b "<< arr[b]<< std::endl;
                    break;
                }
            }
            if (arr[a] * r < arr[b])
            {
                //std::cout << "++a "<< arr[a]<< std::endl;
                break;
            }
        }
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nr_temp;
    getline(cin, nr_temp);

    vector<string> nr = split(rtrim(nr_temp));

    int n = stoi(nr[0]);

    long r = stol(nr[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    long ans = countTriplets(arr, r);

    fout << ans << "\n";

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
