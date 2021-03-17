#include <memory>
#include <vector>

// im using a class for have a default value
class node {
   public:
    double added_weight_node = 1;
    double weight = 1;
    double input_node = 0;
    void adding(const std::vector<node>& nodes);
};
// this is the layers of the neural network
struct layer {
    int id;
    std::vector<node> nodes;
    layer *next_layer = nullptr;
    // this is for get the last value
    layer *get_last();
    // this declare the inputs
    void input_nodes(std::vector<double>);
    // this add new nodes
    void add_nodes(int size);
    // this change the weight of the node
    void randomize_weights();
    void generate_neural_network(int, std::vector<int>, int);
    // this is for add a new layer
    void add_layers(std::vector<int> &size_nodes_layer);
    // this made the summation and the send you the output
    void update_all_layers();
    void summation();
    void visualize();
    void clear_all_nodes();
};
