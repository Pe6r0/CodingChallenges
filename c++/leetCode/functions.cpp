#include <iostream>
#include <cstdio>
#include <math.h>
using namespace std;

/*
Add `int max_of_four(int a, int b, int c, int d)` here.
*/

int max_of_four(const int a,const int b,const int c,const int d)
{
    return std::max(std::max(a,b),std::max(c,d));
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d", ans);
    
    return 0;
}