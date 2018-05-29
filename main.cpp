#include <iostream>
#include "Vector.h"
#include <vector>
#include <string>
#include <chrono>

struct Timer{
    using clock = std::chrono::steady_clock;
    std::chrono::time_point<clock> start,end;
    Timer(){
        /// starts timing in constructor
        start = clock::now();
    }
    ~Timer(){
        ///outputs time since constructor in destructor
        end =  clock::now();
        std::cout<<(double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/1000000000<<" ";
    }
};
void checka (Vector<int> &a, int sz){
    Timer t;
    for(int i = 0;i<sz;i++){
        a.push_back(20);
    }
   // std::cout<<std::endl;
}
void checkb (std::vector<int> &b, int sz){
    Timer t;
    for(int i = 0;i<sz;i++){
        b.push_back(20);
    }
   // std::cout<<b.capacity();

}
int main() {
    Vector<int>a;
    std::vector<int> b;
    int sz = 10000;
    for(int i =0;i<5;i++){
        std::cout<<sz<<"   Custom:";
        checka(a, sz);
        a.clear();
        std::cout<<"\tstd::vector:";
        checkb(b,sz);
        std::cout<<"\n";
        b.clear();
        sz*=10;
    }

    a.shrink_to_fit();
    return 0;

}