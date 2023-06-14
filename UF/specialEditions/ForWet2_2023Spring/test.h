#include <stdio.h>
#include <string>

#ifndef recordPlace_
#define recordPlace_
class recordPlace
{
private:
    int data;
    std::string info;
public:
    recordPlace(int d = 0, std::string info = "") : data(d), info(info){}
    ~recordPlace() = default;
    void extraCalc(recordPlace&);
    recordPlace& operator+=(const recordPlace& obj);
    recordPlace& operator-=(const recordPlace& obj);
    recordPlace& operator=(const recordPlace& obj) = default;
    friend recordPlace operator+(const recordPlace& obj1, const recordPlace& obj2);
    friend recordPlace operator-(const recordPlace& obj1, const recordPlace& obj2);
    friend recordPlace operator%(const recordPlace& obj1, const recordPlace& obj2);


};

void recordPlace::extraCalc(recordPlace&)
{
    this->info += " <+> extraCalc";
}

recordPlace& recordPlace::operator-=(const recordPlace& obj)
{
    this->data -= obj.data;
    return *this;
}

recordPlace& recordPlace::operator+=(const recordPlace& obj)
{
    this->data += obj.data;
    return *this;
}

recordPlace operator+(const recordPlace& obj1, const recordPlace& obj2)
{
    recordPlace temp;
    temp = obj1;
    temp += obj2;
    return temp;
}

recordPlace operator-(const recordPlace& obj1, const recordPlace& obj2)
{
    recordPlace temp;
    temp = obj1;
    temp -= obj2;
    return temp;
}
recordPlace operator%(const recordPlace& obj1, const recordPlace& obj2)
{
    recordPlace temp;
    temp = obj1;
    temp.info += obj2.info;
    temp.info += " <+> extraCalc";
    return temp;
}

#endif