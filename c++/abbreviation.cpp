#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
std::string& deleteLower(string& a) //copy before
{
    auto size = std::distance(a.begin(),std::remove_if(a.begin(), a.end(), [](char& c){return islower(c);}));
    a.resize(size);
    return a;
}

std::string& capitalise(string& a, char b) //copy before
{
    for(auto i = a.begin(); i != a.end(); ++i)
    {
        if(islower(*i) && *i == tolower(b))
        {
            *i = toupper(*i);
        }
    }
    return a;
}

//failing a few test cases, no simple one to debug atm

string abbreviation(string a, string b) 
{
    std::cout << "comparing"  << a << " " << b << std::endl;
    auto lookAhead = [&b](auto&& lookAhead, string& t)
    {
        std::cout << t << ">>>" << std::endl;
        if(t == b)
        {
            std::cout << "yey" << std::endl;
            return true;
        }
        if(t.size() < b.size())
        {
            std::cout << "naysize" << std::endl;
            return false;
        }
        std::string deleteTest = t;
        if(deleteLower(deleteTest) == b)
        {
            std::cout << "deleting fixed it" << std::endl;
            return true;
        }
        for(int i = 0 ; i < t.size(); ++i)
        {
            if(islower(t[i]))
            {
                std::cout << "capitalizing" << std::endl;
                std::string capitalizeTest = t;
                capitalise(capitalizeTest, t[i]);
                if(lookAhead(lookAhead, capitalizeTest))
                {
                    return true;
                }
            }
            std::cout << ".";
        }
        std::cout << "shouldnt happen" << std::endl;
        return false;
    };

    if(a == b )
    {
        return "YES";
    }
    if(a.size() < b.size())
    {
        return "NO";
    }
    
    return lookAhead(lookAhead, a)? "YES" : "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

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
