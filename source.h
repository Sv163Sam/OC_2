#include <Windows.h>
#include <iostream>

#ifndef UNTITLED_SOURCE_H
#define UNTITLED_SOURCE_H

void pow_();
void sum_();
void sqrt_();

union int_convert{//buffer for reading
    int value = 0;
    BYTE bytes[sizeof(int)];//char
};

union double_convert{
    double value = 0.0;
    byte bytes[sizeof(double)];
};

void print_mes(const std::string &str)
{
    std::cout << "\n" << str << std::endl;
}

void print_value(const std::string &str, size_t value)
{
    std::cout << "\n" << str << value << std::endl;
}

void cin_value(int &value)
{
    std::cin >> value;
}



#endif //UNTITLED_SOURCE_H
