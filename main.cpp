#include <iostream>
#include <string>
#include <concepts>

template <typename T>
concept ComplexConcept = (!std::has_virtual_destructor<T>::value) && requires(T v)
{
    { v.hash() } -> std::convertible_to<long>;
    { v.toString() } -> std::same_as<std::string>;
};

template <ComplexConcept T>
void checkConcept(T& t)
{
    std::cout << t.hash() << '\n'
              << t.toString() << '\n'
              << std::has_virtual_destructor<T>::value;
}

class Test1
{
public:
    ~Test1() = default;
    long hash() { return 13579; };
    std::string toString() { return "Correct"; };
};

class Test2
{
public:
    virtual ~Test2() = default; //<!>
    long hash() { return 24680; };
    std::string toString() { return "Incorrect"; };
};

class Test3
{
public:
    ~Test3() = default;
    std::string hash() { return "1135813"; }; //<!>
    std::string toString() { return "Incorrect"; };
};

class Test4
{
public:
    ~Test4() = default;
    long hash() { return 1861; };
    long toString() { return 1961; }; //<!>
};

int main()
{
    Test1 v1;
    checkConcept(v1);

    Test2 v2;
    //!has_virtual_destructor<T>::value
    //checkConcept(v2); 

    Test3 v3;
    //convertible_to<long>
    //checkConcept(v3);

    Test4 v4;
    //same_as<string>
    //checkConcept(v4);
    return 0;
}