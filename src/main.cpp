#include <iostream>
#include <vector>
#include "neural.h"
using namespace std;

int main(){
    vector<int> v = {2, 2, 2};
    vector<double> v2 = {0.1};

    /**
     * no instance of constructor "std::__1::vector<_Tp, _Allocator>::vector [with _Tp=int, _Allocator=std::__1::allocator<int>]" matches the argument list -- argument types are: (int, int, int, int, int)
    */
    cout << "============STARTING=============" << endl;
    layer x;
    x.generate_neural_network(1, v, 1);
    x.visualize();

    cout << "=============INPUTS============" << endl;
    x.next_layer->input_nodes(v2);
    x.visualize();
    cout << "==============SUMMATION===========" << endl;
    x.next_layer->summation();
    layer *i = x.get_last();
    cout << i->nodes.at(0).input_node << endl;

    //x.visualize();

    return 0;
}