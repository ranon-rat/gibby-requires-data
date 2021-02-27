#include <iostream>
#include <vector>
using namespace std;
// im using a class for have a default value
class node
{
public:
    float added_weight = 1,
          weigth = 1,
          input = 0;
};
// this is the layers of the neural network
struct layer
{
    bool last;
    vector<node> nodes;
    int id;
    layer *next_layer;
    // this add new nodes
    void add_nodes(int size)
    {
        node n;
        for (size; size > 0; size--)
            nodes.push_back(n);
    };
    //this change the weight of the node
    void change_weight_node(int id, float new_weight)
    {
        nodes.at(id).weigth = new_weight;
    }
};
class neural_network
{
    vector<vector<node> > layers;
};
/**
 * 
*/