#include <iostream>
#include "neural_network.h"
#include "activation_funcs.h"
#include "math.h"

using namespace std;

void NeuralNetwork::new_neural_network(vector<int> nodesPerLayer, vector<int> activation_funcs)
{
    srand(time(NULL));
    activation_functions = activation_funcs;
    for (int l = 0; l < (int)nodesPerLayer.size() - 1; l++)
    {
        vector<float> bias_l;
        vector<vector<float>> weights_l;
        // i add to the bias of this layer a random value
        for (int n = 0; n < nodesPerLayer[l + 1]; n++)
        {

            bias_l.push_back(((float)rand() / (float)RAND_MAX) - 0.5);
        }
        // i need to generate the weights so this is really
        for (int n = 0; n < nodesPerLayer[l]; n++)
        {
            vector<float> weight_node;
            for (int w = 0; w < nodesPerLayer[l + 1]; w++)
            {
                weight_node.push_back(((float)rand() / (float)RAND_MAX) - 0.5);
            }

            weights_l.push_back(weight_node);
        }

        weights.push_back(weights_l);
        bias.push_back(bias_l);
    }
}
vector<vector<float>> NeuralNetwork::feed_foward(vector<float> input)
{
    vector<vector<float>> layers = {input};
    for (int l = 0; l < (int)bias.size(); l++)
    {
        vector<float> layer;
        // i hate this so much but I dont know what else i can do
        for (int n = 0; n < (int)bias[l].size(); n++)
        {

            layer.push_back(bias[l][n]);
        }
        // layer*weights

        for (int n = 0; n < (int)layers[l].size(); n++)
        {
            for (int w = 0; w < (int)bias[l].size(); w++)
            {
                layer[w] += weights[l][n][w] * layers[l][n];
            }
        }
        // a(layer+bias)
        for (int n = 0; n < (int)bias[l].size(); n++)
        {

            layer[n] = activation_func(activation_functions[l], layer[n]);
        }

        layers.push_back(layer);
    }

    return layers;
}
tuple<vector<vector<vector<float>>>, vector<vector<float>>> NeuralNetwork::backprop(vector<vector<float>> layers, vector<float> expected)
{
    vector<vector<vector<float>>> wd;
    vector<vector<float>> bd;
    vector<float> errors;

    for (int i = 0; i < (int)layers.back().size(); i++)
    {
        errors.push_back(layers.back()[i] - expected[i]);
    }

    for (int l = (int)bias.size() - 1; l >= 0; l--)
    {
        vector<float> grad;
        for (int n = 0; n < (int)bias[l].size(); n++)
        {
            grad.push_back(errors[n] * dev_activation_func(activation_functions[l], layers[l + 1][n]));
        }

        vector<vector<float>> deltgrad;
        for (int n = 0; n < (int)weights[l].size(); n++)
        {
            vector<float> deltgrad_node;

            for (int w = 0; w < (int)weights[l][n].size(); w++)
            {
                deltgrad_node.push_back(layers[l][n] * grad[w]);
            }
            deltgrad.push_back(deltgrad_node);
        }
        wd.insert(wd.begin(), deltgrad);
        bd.insert(bd.begin(), grad);
        if (!l)
            continue;
        vector<float> errcp = layers[l];
        for (int n = 0; n < (int)layers[l].size(); n++)
        {
            float err = 0;
            for (int i = 0; i < (int)errors.size(); i++)
            {
                err += weights[l][n][i] * errors[i];
            }
            errcp[n] = err;
        }
        errors = errcp;
    }
    return {wd, bd};
}
void NeuralNetwork::update(int size, float learning_rate, vector<vector<vector<float>>> wd, vector<vector<float>> bd)
{
    for (int l = 0; l < (int)bias.size(); l++)
    {
        // layer*weights
        for (int n = 0; n < (int)weights[l].size(); n++)
        {
            for (int w = 0; w < (int)weights[l][n].size(); w++)
            {
                weights[l][n][w] -= (wd[l][n][w] * learning_rate) / size;
            }
        }
        for (int n = 0; n < (int)bias[l].size(); n++)
        {

            bias[l][n] -= (bd[l][n] * learning_rate) / size;
        }
    }
}
void NeuralNetwork::train(float learning_rate, int epoch, vector<vector<float>> dataset, vector<vector<float>> expected)
{
    for (int e = 0; e < epoch; e++)
    {
        vector<vector<vector<float>>> wdsum;
        vector<vector<float>> bdsum;
        float err = 0;
        for (int d = 0; d < (int)dataset.size(); d++)
        {
            vector<vector<float>> layers = feed_foward(dataset[d]);

            auto bdanwd = backprop(layers, expected[d]);
            if (d == 0)
            {
                wdsum = get<0>(bdanwd);
                bdsum = get<1>(bdanwd);
                continue;
            }
            if (!(e % 10))
            {
                err += cost(expected[d], layers.front());
            }
            for (int l = 0; l < (int)bias.size(); l++)
            {

                // layer*weights
                for (int n = 0; n < (int)weights[l].size(); n++)
                {
                    for (int w = 0; w < (int)weights[l][n].size(); w++)
                    {
                        wdsum[l][n][w] += get<0>(bdanwd)[l][n][w];
                    }
                }
                for (int n = 0; n < (int)bias[l].size(); n++)
                {

                    bdsum[l][n] += get<1>(bdanwd)[l][n];
                }
            }
        }
        update(dataset.size(), learning_rate, wdsum, bdsum);
        if (!(e % 10))
        {
            printf("| error : %.6f |epoch %d\n", err, e);
        }
    }
}
vector<float> NeuralNetwork::predict(vector<float> input)
{
    return feed_foward(input).back();
}

void save_model(string filename, NeuralNetwork nn)
{
    remove(filename.c_str());
    ofstream model_file;
    model_file.open(filename, ios::app);
    model_file.write((char *)&nn, sizeof(nn));
    model_file.close();
}

NeuralNetwork open_model(string filename)
{

    NeuralNetwork NN;

    ifstream model_file;
    model_file.open(filename, std::ios::in);
    model_file.seekg(0);
    model_file.read((char *)&NN, sizeof(NN));
    model_file.close();
    return NN;
}