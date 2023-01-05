
#include "funcObject.h"
#include "UFW2T.h"

class forE  //like player
{
    public:
    forE(int id, funcObject extra) : id(id), extra(extra){}
    private:
        int id;
        funcObject extra;

};

int main()
{
    UnionFind<int, forE*, funcObject> uf;
    int count = 300;

    for (int i = 0; i < 300; i++)
    {
        funcObject e(i*100);
        uf.Insert(i, new forE(i, e), e);
    }

    std::cout << uf;
    std::cout << "--------------------------------------------------------" << std::endl;
    for (int i = 0; i < count; i+=2)
    {
        uf.Union(i, i+1);
    }

    
    std::cout << uf;
    std::cout << "--------------------------------------------------------" << std::endl;
    for (int i = 0; i < count; i+=4)
    {
        uf.Union(i, i+2);
    }
    std::cout << uf;
    std::cout << "--------------------------------------------------------" << std::endl;    for (int i = 0; i < count; i+=8)
    {
        uf.Union(i, i+4);
    }
    std::cout << uf;
    std::cout << "--------------------------------------------------------" << std::endl;
    for (int i = 0; i < count; i+=16)
    {
        uf.Union(i, i+8);
    }
    std::cout << uf;
    std::cout << "--------------------------------------------------------" << std::endl;
    for (int i = 0; i < count; i+=32)
    {
        uf.Union(i, i+16);
    }
    std::cout << uf;
    std::cout << "--------------------------------------------------------" << std::endl;

    return 0;
}