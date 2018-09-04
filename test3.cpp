#include <iostream>

class Int
{
public:
    Int(){std::cout << "This is Int Default Constructor Calling!" << std::endl;}
    Int(const Int &a [[maybe_unused]]){}

    ~Int(){std::cout << "Destructor of Int" << std::endl;}
};

template<typename T>
void f([[maybe_unused]]T a)
{
    std::cout << "T" << std::endl;
    std::cout << a << std::endl;
}

template<>
void f<int>([[maybe_unused]]int a)
{
    std::cout << "int" << std::endl;
    std::cout << a << std::endl;
}

template<>
void f<Int>([[maybe_unused]]Int a)
{
    std::cout << "Int" << std::endl;
}

struct Inte
{
    int num;
};

struct aaa : public Inte
{
    int temp;
};

class Integ
{
public:
    int num;
    Integ(int a) : num(a){}
    Int a;
    ~Integ(){std::cout << "Destructor of Integ" << std::endl;}
};

class aa : public Integ
{

};


int main()
{
    //Int a{};
    /*
     * Int a();
     * It will be treated as fuction declaration
    */
    /*[[maybe_unused]]aaa as = {{5}, 5};
    [[maybe_unused]]aa sd = {5};
    std::cout << "this is a C++17 new Standard Test" << sd.num << std::endl;
    Int b;
    int c = 818'198'499;
    double d = 818'198'499;
    f(b);
    f(c);
    f(d);
    std::cout << "Hello World!" << std::endl;*/
    Integ adda(5);
    //when the destuctor of a member is called, the destructor of the member of the object is called too.
    return 0;
}
