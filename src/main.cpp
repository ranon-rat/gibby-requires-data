#include <iostream>
#include <vector>
#include "neural.h"
using namespace std;

int main(){
    vector<int> v;
    for (int i = 0; i <= 14; i++)
        v.push_back(i);

    /**
     * no instance of constructor "std::__1::vector<_Tp, _Allocator>::vector [with _Tp=int, _Allocator=std::__1::allocator<int>]" matches the argument list -- argument types are: (int, int, int, int, int)
    */
    layer x;
    x.add_new_layer(&v);
    x.summation();
  
    /*layer x2 = x.get_last();
    for (int i = 0; i < x2.nodes.size(); i++)
    {
        cout << x2.nodes.at(i).input_node << endl;
    }*/
    return 0;
}