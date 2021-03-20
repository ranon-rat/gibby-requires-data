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

    layer x;
    x.generate_neural_network(1, v, 1);

    x.input_nodes(v2);
    x.update_all_layers();
    x.next_layer->summation();
    double l = 0;
    while (true)
    {
        cout << "============ summation ============ \n"
             << "input : ";
        cin >> l;
        if(!cin){
            cout<<"puth a number retard"<<endl;
        }

        x.input_nodes({l});
        x.summation();
        cout << "output : " << x.get_last()->nodes.at(0).input_node << endl;
        x.clear_all_nodes();
    }
    //x.visualize();

    return 0;
}
