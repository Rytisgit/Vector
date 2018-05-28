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
    std::cout<<a.capacity();
    a.push_back("btest");
    a.push_back("b");


    for (auto num : a) { std::cout<<num; };
    std::cout<<std::endl<<a.capacity();
    std::cout<<std::endl;
    a.shrink_to_fit();
    for (auto num : a) { std::cout<<num; };
    std::cout<<a.capacity();
    std::vector<int> b;
    b.begin();
    int best = 12;
    ~best;
   // a.operator=({'a','b','v'});
    std::cout << "Hello, World!" << std::endl;
    return 0;
}