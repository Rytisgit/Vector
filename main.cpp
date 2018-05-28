#include <iostream>
#include "Vector.h"
#include <vector>
#include <string>
int main() {
    Vector<std::string>a (10,"test");
//    for (auto num : a) {
//        std::cout<<num;
//
//    };

    a.push_back("thisisit");
    a.push_back("b");
    std::cout<<a[0];

   // for (auto num : a) { std::cout<<num; };
    std::cout<<std::endl<<a.capacity();
    std::cout<<std::endl<<"help"<<std::endl;
    a.shrink_to_fit();

    for (auto num : a) { std::cout<<num<<'\t'; };
    a.push_back("t");
    std::cout<<a.capacity();

   // a.operator=({'a','b','v'});3
    return 0;
    std::cout << "Hello, World!" << std::endl;

}