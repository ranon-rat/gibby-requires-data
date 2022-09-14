#include "vector"
#include "math.h"
#define SIGMOID 1
#define TANH 2
#define RELU 3
//i need to use this kind of stuff for making it for more general use
float activation_func(int func, float x)
{
    float value = 0;
    switch (func)
    {
    case SIGMOID:
        value = 1 / (1 + exp(x * (-1)));
        break;
    case TANH:
        value = tanh(x);
        break;
    case RELU:
        value = x > 0 ? x : 0;
        break;
    default:
        break;
    }
    return value;
}
float dev_activation_func(int func, float x)
{
    float value = 0;
    switch (func)
    {
    case SIGMOID:
        value = x * (1 - x);
        break;
    case TANH:
        value = 1 - (x * x);
        break;
    case RELU:
        value = x > 0 ? 1 : 0;
        break;
    default:
        break;
    }
    return value;
}
//this is really simple
float cost(std::vector<float> target, std::vector<float> output)
{
    float err = 0;
    for (int i = 0; i < (int)target.size(); i++)
    {
        err += pow(output[i] - target[i], 2);
    }
    return err;
}