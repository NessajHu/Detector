#include <iostream>

enum class Month
{
    January = 1,
    Febuary,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

class Int
{
public:
    int num;
    Int() = delete;
    Int(int a) : num(a){}
    explicit operator int() const {return num;}
};

void monthTest(Month a)
{
    if(a == Month::January)
    {
        std::cout << "January" << std::endl;
    }
}

/*
 * for class Base, if virtual functions definition are all in *.h
 * compiler will show the warning -Weak-vtables, because compiler does not know which *.cpp will emit the vtable,
 * so it will happen thar it emits a copy to all of *.cpp(translation unit), and the linker gets to deal with it
 *
 * BUT, Qt Creator maybe has a bug, in this example, all source code is in a *.cpp, in standalone clang, it works correctly,
 * but in Qt Creator it will show the useless warning.
 * The bug is repoted as QTCREATORBUG_19741, which URL is https://bugreports.qt.io/browse/QTCREATORBUG-19741
*/
class Base
{
public:
    int num;
    Base(int a) : num(a){}
    virtual void print() const;
    virtual ~Base();
};
/*
void Base::print() const
{
    std::cout << "this is base calling!" << std::endl;
}
*/
Base::~Base(){}
class Derived : public Base
{
public:
    Derived(int a) : Base(a) {}
    void print() const;
};

void Derived::print() const
{
    std::cout << "this is derived callint" << std::endl;
}

void tem(const Base& a)
{
    a.print();
}

int main()
{
    Derived ab{5};
    tem(ab);
    Int a{5};
    const int temp = 5;
    const int &t = temp;
    std::cout << temp << &temp << std::endl;
    const_cast<int&>(t) = 6;
    std::cout << temp << &temp << std::endl;
    int b = static_cast<int>(a);
    std::cout << b << std::endl;
    monthTest(Month::April);
    std::cout << "Hello World" << std::endl;
    monthTest(Month::January);
    return 0;
}
