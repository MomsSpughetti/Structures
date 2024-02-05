#include "iostream"
#include "stdlib.h"
#include"UFW2T.h"


class funcObject
{

public:
    funcObject() = default;
    funcObject(int n) : num(n){}
    friend funcObject operator+(const funcObject& obj1, const funcObject& obj2);
    funcObject& operator+=(const funcObject& obj);
    friend funcObject operator-(const funcObject& obj1, const funcObject& obj2);
    funcObject& operator-=(const funcObject& obj);
private:
int num;
};


funcObject& funcObject::operator+=(const funcObject& obj)
{
    this->num += obj.num;
    return *this;
}

funcObject operator+(const funcObject& obj1, const funcObject& obj2)
{
    funcObject temp;
    temp += obj1;
    temp += obj2;
    return temp;
}

funcObject& funcObject::operator-=(const funcObject& obj)
{
    this->num -= obj.num;
    return *this;

}

funcObject operator-(const funcObject& obj1, const funcObject& obj2)
{
    funcObject temp;
    temp -= obj1;
    temp -= obj2;
    return temp;
}