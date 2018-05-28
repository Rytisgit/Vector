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
void checka (Vector<int> &a){
    Timer t;
    for(int i = 0;i<100000000;i++){
        a.push_back(20);
    }
    std::cout<<std::endl;
}
void checkb (std::vector<int> &b){
    Timer t;
    for(int i = 0;i<100000000;i++){
        b.push_back(20);
    }
   // std::cout<<b.capacity();

}
int main() {
    Vector<int>a;
    std::vector<int> b;
    checka(a);
    checkb(b);
    return 0;

}