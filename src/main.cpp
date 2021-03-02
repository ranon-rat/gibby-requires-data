#include <iostream>
#include <vector>
#include "neural.h"
using namespace std;

int main(){
    vector<int> v = {2, 2, 2};
    vector<double> v2 = {1234};

    /**
     * no instance of constructor "std::__1::vector<_Tp, _Allocator>::vector [with _Tp=int, _Allocator=std::__1::allocator<int>]" matches the argument list -- argument types are: (int, int, int, int, int)
    */
    layer x;
    x.generate_neural_network(1, v, 1);
    x.visualize();

    cout << "=========================" << endl;
    x.next_layer->input_nodes(v2);
    x.visualize();
    cout << "=========================" << endl;
    x.summation();
    x.visualize();

    //x.visualize();

    return 0;
}