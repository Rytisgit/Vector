#include <iostream>
#include "Vector.h"
#include <vector>
int main() {
    Vector<char>a (10,'a');
//    for (auto num : a) {
//        std::cout<<num;
//
//    };
    std::cout<<a.capacity();
    a.push_back('b');
    a.push_back('b');
    a.push_back('b');a.push_back('b');

    for (auto num : a) { std::cout<<num; };
    std::cout<<a.capacity();
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