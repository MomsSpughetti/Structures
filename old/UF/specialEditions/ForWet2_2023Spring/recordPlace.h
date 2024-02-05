#ifndef _RP_
#define _RP_
#include <ostream>
#define Zero 0
#define NOTEXIST -1
class recordPlace
{
private:
    int r_id;
    int helperToCalcHeightOfRecord;
    //next members are valid for the root only
    int columnHeight;
    int columnIndex;
public:
    recordPlace(int r_id = NOTEXIST, int colH = NOTEXIST, int colIn = NOTEXIST) : helperToCalcHeightOfRecord(Zero), columnHeight(colH), columnIndex(colIn){}
    ~recordPlace() = default;
    void extraCalc(recordPlace&, bool);
    recordPlace& operator+=(const recordPlace& obj);
    recordPlace& operator-=(const recordPlace& obj);
    recordPlace& operator=(const recordPlace& obj) = default;
    friend recordPlace operator+(const recordPlace& obj1, const recordPlace& obj2);
    friend recordPlace operator-(const recordPlace& obj1, const recordPlace& obj2);
    friend recordPlace operator%(const recordPlace& obj1, const recordPlace& obj2);
    friend std::ostream& operator<<(std::ostream&, const recordPlace&);
};

void recordPlace::extraCalc(recordPlace& NewRootRecord, bool is_B_BiggerThan_A)
{
    if (is_B_BiggerThan_A)
    {
        this->helperToCalcHeightOfRecord += (NewRootRecord.columnHeight - NewRootRecord.helperToCalcHeightOfRecord);
        NewRootRecord.columnHeight += this->columnHeight;
    } else {
        NewRootRecord.helperToCalcHeightOfRecord += this->columnHeight;
        this->helperToCalcHeightOfRecord -= NewRootRecord.helperToCalcHeightOfRecord;
        NewRootRecord.columnHeight += this->columnHeight;
        NewRootRecord.columnIndex = this->columnIndex;
    }
    
}

recordPlace& recordPlace::operator-=(const recordPlace& obj)
{
    this->helperToCalcHeightOfRecord -= obj.helperToCalcHeightOfRecord;
    return *this;
}

recordPlace& recordPlace::operator+=(const recordPlace& obj)
{
    this->helperToCalcHeightOfRecord += obj.helperToCalcHeightOfRecord;
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
    return temp;
}

std::ostream& operator<<(std::ostream& os, const recordPlace& obj){
    os << obj.helperToCalcHeightOfRecord;
    return os;
}

#endif