#include <iostream>
#include "neural_network.h"
#include <vector>
using namespace std;
int main()
{
    vector<vector<float>> dataset{
        {0, 1},
        {1, 0},
        {0, 0},
        {1, 1},
    };
    vector<vector<float>> expected{
        {1},
        {1},
        {0},
        {0},
    };
    NeuralNetwork nn;

    nn.new_neural_network({2, 3, 1}, {SIGMOID, SIGMOID});
    nn.train(0.5, 10000, dataset, expected);
    cout << "\n";
    for (int i = 0; i < (int)dataset.size(); i++)
    {
        printf("| input: %.1f,%.1f |expected: %.1f | output: %.6f\n", dataset[i][0], dataset[i][1], expected[i][0], nn.predict(expected[i])[0]);
    }
    return 0;
}