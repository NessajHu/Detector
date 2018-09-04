#include <iostream>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include <utility>

class integer
{
public:
    integer() : num(0){std::cout << "test" << std::endl;}
    //integer(integer && a): num(std::move(a.num)){}
    integer(int a) : num(a){std::cout << "test1" << std::endl;}
    integer(const integer& a) : num(a.num){std::cout << "test2" << " " <<num << std::endl;}
    int num;
    ~integer(){}
    friend integer operator+(const integer& a, const integer& b);
    friend std::ostream& operator<<(std::ostream& out, const integer& a);
};

std::ostream& operator<<(std::ostream& out, const integer& a)
{
    out << a.num;
    return out;
}

integer operator+(const integer& a, const integer& b)
{
    std::cout << a.num << " " << b.num << std::endl;
    return integer(a.num + b.num);
}

template<class... T>
auto sum(T... num)
{
    return (num + ...);
}

class People
{
private:
    int num;
public:
    People(int a) : num(a){std::cout << "this is constructor"<< std::endl;}
    People(const People& p) : num(p.num){std::cout << "copy cons" << p.num << std::endl;}
    People& operator=(const People& p){std::cout << "=" << p.num << std::endl; return *this;}
};

People f()
{
    People temp = People(0);
    std::cout << &temp << "f out" << std::endl;
    return temp;
}

template<class... T>
class Vector
{
    std::vector<typename std::common_type<T&&...>::type> buffer;
public:
    Vector(T&&... num) :
        buffer(std::vector<typename std::common_type<T&&...>::type>(0))
    {
        std::cout << sizeof...(T);
        std::cout << sizeof(typename std::common_type<T&&...>::type);
        std::cout << "temp" << std::endl;
        integer arr[] = {num...};
        std::cout << "---------------" << std::endl;
        //[[maybe_unused]] [[deprecated("To expand to pack, used , expression")]]
        //int array[] = {(buffer.push_back(num), i++)...};
        (buffer.push_back(num), ...);
        //int array[] is not necessary, because "(buffer.push_back(num), ...);" is effective
        std::cout << "temp" << std::endl;
    }
    int length()
    {
        return buffer.size();
    }
    void print()
    {
        for(auto &i : buffer)
        {
            std::cout << i << " ";
        }
    }
};

int main()
{
    integer a{1};
    integer b{2};
    //Vector temp{integer{1}, integer{2}};
    Vector temp{integer{1}, integer{2}, integer{3}};
    temp.print();
    std::vector<integer> te;
    te.push_back(integer{1});
    te.push_back(integer{2});
    te.push_back(integer{3});
    te.push_back(integer{4});
    /*istd::cout << "Hello, World!" << std::endl;
    int x;
    People t1 = f();
    std::cout << &t1 << "seperator" << std::endl;
    People t2(t1);
    t1 = t2;
    nteger a(68);
    integer b(2);
    integer c(3);
    std::cout << sum(a, b, c);*/
    //return a;
}
