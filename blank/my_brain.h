#ifndef MY_BRAIN_H
#define MY_BRAIN_H

#include "neural_network.h"
using OpenNN::PerceptronLayer;
using OpenNN::ConvolutionalLayer;
using OpenNN::NeuralNetwork;
using OpenNN::type;
using Eigen::Index;
using Eigen::Tensor;

#include <iostream>
using std::cout;
using std::endl;

class MyBrain
{
public:
    int fitness_score = -1;

    MyBrain(int color_id = -1, int conv_num = 1) : color_id(color_id), conv_num(conv_num)
    {
        Tensor<Index, 1> input_variables_dimensions(3);
        input_variables_dimensions(0) = 3;
        input_variables_dimensions(1) = 5;
        input_variables_dimensions(2) = 1;

        nn = new NeuralNetwork();

    }

    ~MyBrain()
    {
        delete nn;
    }

    void mutate() {
        return;
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
    int color_id;
    int conv_num;
};

#endif