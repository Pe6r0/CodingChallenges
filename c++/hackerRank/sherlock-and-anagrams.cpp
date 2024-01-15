#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'sherlockAndAnagrams' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int sherlockAndAnagrams(string s) {
    auto result = 0;
    //get all substrings
    for(size_t a = 0 ; a < s.size() -1; ++a)
    {
        //std::cout << "->"  << std::endl;
        for(size_t b = 1 ; a + b <= s.size(); ++b)
        {
            //std::cout << "++"  << std::endl;
            //get substring
            unordered_map<char, int> index;
            for(size_t i = 0; i < b; ++i)
            {
                //std::cout<< "index added :" << s[a+i] <<std::endl;
                index[s[a+i]]++;
            }
            
            //test for anagram
            for(size_t shift = 1; a + shift + b <= s.size(); ++shift)            
            {
                //std::cout << "shift" <<shift << std::endl;
                unordered_map<char, int> indexTest = index;
                
                bool flag = true;
                for(size_t i = 0; i < b; ++i)
                {
                    auto found = indexTest.find(s[a+shift+i]);
                    if(found == indexTest.end() || (*found).second == 0)
                    {
                        //std::cout << "not anagram break"  << std::endl;
                        flag = false;
                        break;
                    }
                    else
                    {
                        if((*found).second == 1)
                        {
                            //std::cout << "remove" << s[a+shift+i] << std::endl;
                            indexTest.erase(found);
                        }
                        else
                        {
                            indexTest[s[a+shift+i]]--;
                            //std::cout << "decrement:" <<s[a+shift+i] << ", " << indexTest[s[a+shift+i]]<< std::endl;
                        }
                        
                    }
                }
                //std::cout << "size" << indexTest.size() << std::endl;
                if(flag && indexTest.empty())
                {
                    //std::cout << "anagram"  << std::endl;
                    result++;
                }
                
            }
        }
    }
    
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

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
