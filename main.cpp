#include "Range.h"
using namespace view::experimental;
using namespace view::experimental2;
using namespace std;
class A{
    function<void()> f;
    vector<int> v;
public:
    A(vector<int> v){
        this->v=v;
    }
    void fun(function<void()> f){
        for(auto i:v){
            f();
        }
    }
};

int main() {
    list<int> hello{1,2,3,4,5};
    for(auto i:hello|filter<list<int>>([](auto x){return x%2==0;})|map<list<int>>([](auto x){return 2*x;})){
        std::cout<<i<<std::endl;
    }
    std::cout<<"------"<<std::endl;
    vector<int> hello1{1,2,3,4,5};
    for(auto i:hello1|filter<vector<int>>([](auto x){return x%2==0;})|map<vector<int>>([](auto x){return 2*x;})){
        std::cout<<i<<std::endl;
    }
    std::cout<<"------"<<std::endl;

    auto mx= hello|view::experimental::max();
    auto mn = hello|view::experimental::min();
    std::cout<<mx<<std::endl;
    std::cout<<mn<<std::endl;

    std::cout<<"------"<<std::endl;

//    for(auto i: getStream(hello).filter([](auto x){return x%2!=0;}).map([](auto x){return 3*x;})){
//        std::cout<<i<<std::endl;
//    }
    auto a =getStream(hello1).filter([](auto x){return x%2!=0;});//.map([](auto x){return 3*x;});
    a.max();
    std::cout<<"------"<<std::endl;
    std::cout<<"------"<<std::endl;

    A aa{vector<int>{1,2,3}};
    aa.fun([](){cout<<"*"<<endl;});

    return 0;
}