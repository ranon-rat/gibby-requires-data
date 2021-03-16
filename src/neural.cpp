#include "neural.h"
#include <iostream>
#include <stdexcept>
void node::adding(const std::vector<node>& nodes) {
    for (const auto &n : nodes)
    {
        input_node += (n.weight * n.input_node) / added_weight_node;
    }
}

//=============layer=================\/
layer *layer::get_last()
{
    layer *p_last = this;
    for (; p_last->next_layer; p_last = p_last->next_layer)
        ;
    return p_last;
}
void layer::input_nodes(std::vector<double> n)
{
    if (n.size() != nodes.size())
        throw std::invalid_argument("the size is different");
    for (int i = 0; i < n.size(); i++)
        nodes.at(i).input_node = n.at(i);
}

void layer::add_nodes(int amount) {
    node n;
    for (int i = 0; i < amount; i++) nodes.push_back(n);
}

void layer::randomize_weights() {
    for (auto& node : nodes) {
        node.weight  += -1 + (std::rand() % 140) * 0.0223;
        node.added_weight_node  += -1 + (std::rand() % 140) * 0.0123;
    }
}

void layer::add_layers(const std::vector<int>& layer_sizes) {
    layer* p_last = get_last();
    // note that layer_sizes.size() must not exceed INT_MAX
    for (int i = 0; i < static_cast<int>(layer_sizes.size()); i++) {                        
        layer* p_new_layer = new layer;
        p_new_layer->id = p_last->id + 1;
        p_new_layer->add_nodes(layer_sizes[i]);
        p_new_layer->randomize_weights();
        p_last->next_layer = p_new_layer;
        p_last = p_new_layer;
    }
}
void layer::update_all_layers()
{
    randomize_weights();
    if (!next_layer)
        return;
    next_layer->update_all_layers();
}
void layer::summation() {
    if (!next_layer) return;
    for (auto& node : next_layer->nodes) {
        node.adding(this->nodes);
    }
}
void layer::generate_neural_network(int inputs_size, std::vector<int> hidden_layers, int outputs_size)
{
		id = 0;
    std::vector<int> v = {inputs_size};
    v.insert(std::end(v), std::begin(hidden_layers), std::end(hidden_layers));
    v.push_back(outputs_size);
    add_layers(v);
}
void layer::visualize() {
    std::cout << "The id is " << id << std::endl;
    for (auto i : nodes)
        std::cout << "the weight is " << i.weight << " \nthe input is " << i.input_node << std::endl;
    if (!next_layer) return;
    std::cout << "=================================================\n";
    next_layer->visualize();
}
