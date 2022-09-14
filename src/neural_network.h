#include <fstream>
#include <vector>
#include <tuple>
#define SIGMOID 1
#define TANH 2
#define RELU 3
class NeuralNetwork{
public :
  
    std::vector<std::vector<std::vector<float>>> weights;
    std::vector<std::vector<float>> bias;
    std::vector<int> activation_functions;
    void new_neural_network(std::vector<int> nodesPerLayer,std::vector<int> activation_funcs);
    std::vector <std::vector<float>> feed_foward(std::vector<float>);
    std::tuple< std::vector<std::vector<std::vector<float>>> , std::vector<std::vector<float>> > backprop(std::vector<std::vector<float>> layers,std::vector<float>expected);
    void train(float learning_rate,int epoch,std::vector<std::vector<float>> dataset,std::vector<std::vector<float>> expected);
    std::vector<float> predict( std::vector<float> input);
    void update(int size,float learning_rate,std::vector<std::vector<std::vector<float>>>wd , std::vector<std::vector<float>>bd);
};
    void save_model(std::string filename,NeuralNetwork nn);

NeuralNetwork open_model(std::string filename);