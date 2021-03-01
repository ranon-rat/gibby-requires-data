#include <iostream>
#include <vector>
#include "neural.h"
using namespace std;

int main(){
    vector<int> v;
    for (int i = 1; i <= 2; i++)
        v.push_back(i);

    /**
     * no instance of constructor "std::__1::vector<_Tp, _Allocator>::vector [with _Tp=int, _Allocator=std::__1::allocator<int>]" matches the argument list -- argument types are: (int, int, int, int, int)
    */
    layer x;
    x.generate_neural_network(1, v, 1);

    x.visualize();
    x.update_all_layers();
    x.visualize();
    //x.visualize();

    return 0;
}