#include <iostream>
#include <unordered_map>

//manual calculation of the square root using binary search and memorization

namespace 
{
    std::unordered_map<double, double> _memory;
    double _epsilon = 0.00000001;
}

double squareRoot(double n)
{
    auto res = _memory.find(n);
    if (res != _memory.end())
    {
        return res->second;
    }
    if (n < 0)
    {
        throw std::exception("negative number");
    }
    double result = 0;

    for(double discrepancy = n - result * result, increment = n/2.0; std::abs(discrepancy) > _epsilon; discrepancy = n - result * result, increment /= 2)
    {
        result += discrepancy > 0 ? increment : -increment;
    }

    _memory[n] = result;
    return result;
}

int main()
{
    double number;
    std::cin >> number;

    std::cout << squareRoot(number) << std::endl;

    return 0;
}