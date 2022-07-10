#include <iostream>
#include <cstdio>
using namespace std;

int main() {
char c = ' ';
double d = 0.0;
long l = 0;
int i = 0;
float f = 0.f;

scanf("%d %ld %c %f %lf", &i, &l, &c, &f, &d);


std::cout << i <<std::endl << l <<std::endl<< c <<std::endl;
std::cout.precision(3);
std::cout << std::fixed << f <<std::endl;
std::cout.precision(9);
std::cout << std::fixed << d << std::endl;
    return 0;
}