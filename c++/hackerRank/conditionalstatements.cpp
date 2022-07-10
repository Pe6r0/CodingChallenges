#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    switch (n)
    {
        case 0:
        std::cout<< "zero" << std::endl;
        break;
        case 1:
        std::cout<< "one" << std::endl;
        break;
        case 2:
        std::cout<< "two" << std::endl;
        break;
        case 3:
        std::cout<< "three" << std::endl;
        break;
        case 4:
        std::cout<< "four" << std::endl;
        break;
        case 5:
        std::cout<< "five" << std::endl;
        break;
        case 6:
        std::cout<< "six" << std::endl;
        break;
        case 7:
        std::cout<< "seven" << std::endl;
        break;
        case 8:
        std::cout<< "eight" << std::endl;
        break;
        case 9:
        std::cout<< "nine" << std::endl;
        break;
        default:
        std::cout<< "Greater than 9" << std::endl;
        break;
        
    }

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
