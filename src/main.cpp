#include <iostream>
#include <vector>
#include "neural.h"
using namespace std;

int main(){
    vector<int> v = {4, 4, 4};
    vector<double> v2 = {1};

    /**
     * no instance of constructor "std::__1::vector<_Tp, _Allocator>::vector [with _Tp=int, _Allocator=std::__1::allocator<int>]" matches the argument list -- argument types are: (int, int, int, int, int)
    */
    layer x;
    x.generate_neural_network(1, v, 1);
    x.visualize();
    x.input_nodes(v2);
    cout << "=========================" << endl;
    x.visualize();

    //x.visualize();

    return 0;
}