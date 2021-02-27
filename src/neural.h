#include <iostream>
#include <vector>
using namespace std;
// im using a class for have a default value
class node
{
public:
    float added_weight_node = 1;
    float weigth = 1;
    float input_node = 0;
    void adding(vector<node> node_vector)
    {

        for (int i = 0; i < node_vector.size(); i++)
        {
            input_node += (node_vector.at(i).weigth * node_vector.at(i).input_node) * node_vector.at(i).added_weight_node;
        }
    }
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
        for (*size; *size > 0; *size--)
            nodes.push_back(n);
    };

    //this change the weight of the node
    void change_weight_nodes()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            nodes.at(i).weigth += -1 + (rand() % 140) * 0.0223;
            nodes.at(i).added_weight_node += -1 + (rand() % 140) * 0.0123;
        }
    }
    // this is for add a new layer
    void add_new_layer(vector<int> *size_nodes_layer)
    {

        // this is the new layer
        layer new_layer = {
            id + 1,                    // 1->2->3->4->5
            !size_nodes_layer->size(), //if x>0=true else = false
        };

        // this is for add the nodes to the new layer
        int *value = &size_nodes_layer->at(0);
        new_layer.add_nodes(value);
        // this change the weight and the added weight for generate a new layer with new  values
        new_layer.change_weight_nodes();
        // this erase the first value of size:nodes_layer
        size_nodes_layer->erase(size_nodes_layer->begin()); // this reduce the code
                                                            //if x>0 do this else do this
        if (size_nodes_layer->size())
        {
            // basic concurrency
            new_layer.add_new_layer(size_nodes_layer);
            next_layer = &new_layer;
        }
    }
    // this is for get the last value
    layer get_last()
    {
        
            return next_layer->get_last();
        
    }
    // this made the summation and the send you the output
    void summation()
    {
        if (!last)
        {
            //wx1*wx2*wx3*wx4*wx5
            /**         xw \
             *    / xw<-xw<-xw
             * xw<- xw<-xw<-xw->xw
             *    \ xw<-xw<-xw 
             *          xw /
            */
            for (int i = 0; i < next_layer->nodes.size(); i++)
            {
                next_layer->nodes.at(i).adding(nodes);
            }
            next_layer->summation();
        }
    }
    void visualize()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes.at(i).input_node << " " << (nodes.at(i).weigth);
        }
        if (next_layer != NULL)
        {
            cout << endl;
            next_layer->visualize();
        }
    }
};
/**
 * 
*/