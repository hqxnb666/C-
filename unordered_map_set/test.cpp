#include "HashTable.h"
#include <iostream>
#include "my_unordered_map.h"
#include "my_unordered_set.h"

void Test2()
{
   // hash_bucket::HashTable<int,int> h1;
   // int a[] = { 1,3,5,7,8,9,10,23,24,53,4,6,34 };
    //for (auto e : a)
   // {
    //    h1.Insert({ e,e });
   // }
    //h1.Find(4)
    bit::unordered_map < std::string, int > h1;
    h1.insert({ "string",1 });
    h1.insert({ "int",2 });
    h1.insert({ "short",3 });
    h1.insert({ "long",4 });
    bit::unordered_map<std::string, int>::iterator it = h1.begin();
    while (it != h1.end())
    {
        it->second += 1;
        ++it;
   }
    for (auto e : h1)
    {
        std::cout << h1["string"];
    }

  
}
int main()
{
   //open_address::Test2();
    Test2();
    return 0;
}
