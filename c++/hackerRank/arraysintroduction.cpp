#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    size_t t = 0;
    std::cin >> t;
    std::vector<int> vec(t);
    int e = 0;
    
    for(int i = 0; i < t;++i)
    {
        std::cin >> e;
        vec[i] = e;
    }
    
    for(int i = t-1; i >= 0;--i)
    {
        std::cout << vec[i] << " ";
    }
    
    return 0;
}
