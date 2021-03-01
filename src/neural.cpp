#include "neural.h"

#include <iostream>

void node::adding(const std::vector<node>& nodes) {
    for (const auto& node : nodes) {
        input_node += node.weight * node.input_node * node.added_weight_node;
    }
}

// layer

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

layer& layer::get_last() {
    layer* p_last = this;
    for (; p_last->next_layer; p_last = next_layer.get())
        ;
    return *p_last;
}

void layer::add_layers(const std::vector<int>& layer_sizes) {
    layer* p_last = &get_last();
    // note that layer_sizes.size() must not exceed INT_MAX
    for (int i = 0; i < static_cast<int>(layer_sizes.size()); i++) {                        
        layer* p_new_layer = new layer;
        p_new_layer->id = this->id + i;
        p_new_layer->add_nodes(layer_sizes[i]);
        p_new_layer->randomize_weights();
        std::shared_ptr<layer> layer(p_new_layer);
        p_last->next_layer = std::move(layer);
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

void layer::visualize() {
    std::cout << "=================================================\n";
    for (auto i : nodes)
        std::cout << i.weight << " " << i.input_node << " ";
    if (!next_layer) return;
    std::cout << "the id is " << id << std::endl;
    next_layer->visualize();
}
