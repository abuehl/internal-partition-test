This small C++ 20 project using C++ modules demonstrates a compiler
error present in:

    Microsoft (R) C/C++ Optimizing Compiler Version 19.43.34810 for x64

The program fails to compile with the follwoing compiler errors:

    A.cpp(11,9): error C2079: 'f' uses undefined class 'A::Fox'
    A.cpp(12,5): error C2664: 'void A::print_age(A::Fox &)': cannot convert argument 1 from 'int' to 'A::Fox &'

The program has a `main()` function in `internal-partition-test.cpp`. There, a module `A` is imported. Function `A::Test()` is called, which is defined in `A.cpp` as


    module A;

    import :Fox;
    import :PrintFox;

    namespace A
    {

    void Test()
    {
        Fox f;
        print_age(f);
    }

    }

`:Fox` and `:PrintFox` are internal partitions of module A.

`Fox.cpp` defines class Fox:

    module A:Fox;

    namespace A
    {

    class Fox
    {
    public:
        int age{ 0 };
    };

    }

`PrintFox.cpp` is an internal partition which declares function `print_age(Fox&)`:


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


`Fox_forward.cpp` is an internal partition, which only forward declares `class Fox`:

    module A:Fox_forward;

    namespace A
    {

    class Fox;

    }

The program should compile fine, if :Fox_forward is imported in PrintFox.cpp.

The compiler fails to accept a forward declaration in one internal partion of a class defined in a different internal partition of the same module.

The project was created with Microsoft Visual Studio Community 2022 (64-bit) Version 17.13.6.
Open the file `internal-partition-test.sln`.
