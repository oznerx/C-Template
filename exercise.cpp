#include "Calculadora.hpp"
#include <iostream>

int main()
{
    Calculadora c(4,5);

    std::cout << "Calculadora aritmética\n";
    std::cout << "======================\n";

    std::cout << "4+5=" << c.suma() << "\n";
    std::cout << "4*5=" << c.multiplica() << "\n";

    std::cout << "4-5=" << c.resta() << "\n";
    std::cout << "4/5=" << c.divide() << "\n";
}