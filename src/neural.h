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
    int id;
    bool last;
    vector<node> nodes;
    layer *next_layer;
    // this add new nodes
    void add_nodes(int *size)
    {
        node n;
        for (size; size > 0; *size--)
            nodes.push_back(n);
    };
    //this change the weight of the node
    void change_weight_node(int id, float new_weight)
    {
        nodes.at(id).weigth = new_weight;
    }
    // this is for add a new layer
    void add_new_layer(int *number_of_layers, vector<int> *size_nodes_layer)
    {

        // this is the new layer
        layer new_layer = {
            id + 1,             // 1->2->3->4->5
            !*number_of_layers, //if x>0=true else = false
        };

        // this is for add the nodes to the new layer
        int *value = &size_nodes_layer->at(0);
        new_layer.add_nodes(value);

        // this erase the first value of size:nodes_layer
        size_nodes_layer->erase(size_nodes_layer->begin());
        next_layer = &new_layer;

        // this add a new value
        new_layer.add_new_layer(number_of_layers, size_nodes_layer);
    }
};
class neural_network
{
    vector<vector<node> > layers;
};
/**
 * 
*/