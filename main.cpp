#include "Range.h"
using namespace view;


int main() {
    vector<int> hello{1,2,3,4,5};
    for(auto i:hello|filter<int>([](auto x){return x%2==0;})|map<int>([](auto x){return 2*x;})){
        std::cout<<i<<std::endl;
    }


    auto mx= hello|view::max();
    auto mn = hello|view::min();
    std::cout<<mx<<std::endl;
    std::cout<<mn<<std::endl;
    return 0;
}