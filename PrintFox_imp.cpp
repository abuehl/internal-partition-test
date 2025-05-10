module;

#include <iostream>

module A;

import :PrintFox;
import :Fox;

namespace A
{

void print_age(Fox& f)
{
    std::cout << f.age;
}

}
