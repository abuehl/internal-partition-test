module A:PrintFox;

// uncomment one of the two imports below

// if we import :Fox, the program compiles fine
//import :Fox;

// if we instead import :Fox_forward, it fails to compile!
import :Fox_forward;

// errors:
// A.cpp(11,9): error C2079: 'f' uses undefined class 'A::Fox'
// A.cpp(12,5): error C2664: 'void A::print_age(A::Fox &)': cannot convert argument 1 from 'int' to 'A::Fox &'


namespace A
{

void print_age(Fox&);

}
