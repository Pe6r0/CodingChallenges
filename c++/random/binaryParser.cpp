//item 4 : create a basic fixed array template
#include <string>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <type_traits>
#include <iterator>
#include <vector>
#include <iostream>
#include <bitset>
#include <memory>

class Binary
{
public:
    template <typename T>
    Binary(T i)
    {
        T tmp = i;
        int index = 0;
        _d.resize(1);
        while (tmp != 0)
        {
            T quotient = tmp / 2;
            T remainder = tmp % 2;
            if (index == CHAR_BIT)
            {
                _d.resize(_d.size() + 1);
                index = 0;
            }
            _d[_d.size() - 1][index] = remainder;
            tmp = quotient;
            index++;
        }
    }
    
    void print()
    {
        for (auto c = _d.rbegin(); c != _d.rend(); ++c)
        {
            std::cout << *c;
            std::cout << ' ';
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::bitset<CHAR_BIT>> _d;
};

/*template <typename T>
inline std::ostream& operator<<(std::ostream &out, const Binary<T>& c)
{
    out << _d;
    return out;
}*/


int main()
{
    Binary biggest(INT_MAX);
    Binary one(2442);
    Binary two(23);
    Binary three(0);
    Binary four(2);

    one.print();
    two.print();
    biggest.print();
    /*std::cout << one << std::endl;
    std::cout << two << std::endl;
    std::cout << three << std::endl;
    std::cout << four << std::endl;*/
    return 0;
}

