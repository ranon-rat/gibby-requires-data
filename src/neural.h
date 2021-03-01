#include <memory>
#include <vector>

// im using a class for have a default value
class node {
   public:
    double added_weight_node = 1;
    double weight = 1;
    double input_node = 1;
    void adding(const std::vector<node>& nodes);
};
// this is the layers of the neural network
struct layer {
    int id;
    std::vector<node> nodes;
    std::shared_ptr<layer> next_layer = nullptr;
    // this add new nodes
    void add_nodes(int size);
    // this change the weight of the node
    void randomize_weights();
    // this is for add a new layer
    void add_layers(const std::vector<int>& size_nodes_layer);
    // this is for get the last value
    layer& get_last();

    // this made the summation and the send you the output
    void summation();
    void visualize();
};