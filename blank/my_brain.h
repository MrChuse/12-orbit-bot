#ifndef MY_BRAIN_H
#define MY_BRAIN_H

#include "neural_network.h"
using OpenNN::PerceptronLayer;
using OpenNN::ConvolutionalLayer;
using OpenNN::NeuralNetwork;
using OpenNN::type;
using Eigen::Index;
using Eigen::Tensor;

class MyBrain
{
public:
    MyBrain(int conv_num = 1) : conv_num(conv_num)
    {
        Tensor<Index, 1> architecture(3);
        architecture(0) = 3;
        architecture(1) = 5;
        architecture(2) = 1;

        nn = new NeuralNetwork(NeuralNetwork::Classification, architecture);

    }

    ~MyBrain()
    {
        delete nn;
    }

    int get_layers()
    {
        return 3;
    }

    Tensor<type, 2> my_func(Tensor<type, 2> t)
    {
        return nn->calculate_outputs(t);
    }

private:
    NeuralNetwork* nn;

    int conv_num;
};

#endif