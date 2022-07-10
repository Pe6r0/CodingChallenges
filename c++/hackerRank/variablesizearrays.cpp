#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void fillData(std::vector<int>& output)
{
    size_t s = 0;
    std::cin >> s;
    output.clear();
    output.reserve(s);

    for(int i = 0 ; i < s; ++i)
    {
        int e = 0;
        std::cin >> e;
        output.push_back(e);
    }
}


int main() {
    int n = 0;
    int q = 0;
    std::cin >> n;  
    std::cin >> q;
    
    std::vector<std::vector<int>> result(n);
    for(int i = 0 ; i < n ; ++i)
    {
        fillData(result[i]);
    }
    
    int x= 0;
    int y= 0;
    for(int i=0;  i < q;++i)
    {
        std::cin >> x;
        std::cin >> y;
        
        std::cout << result[x][y]<<std::endl;
    }
    
    
    return 0;
}
