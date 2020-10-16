// 12 orbits AI project

// system includes

#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

// project includes 

#include "main_func.h"
#include "screenshot.h"
#include "my_brain.h"
/*#include "opennn.h"
using OpenNN::PerceptronLayer;
using OpenNN::ConvolutionalLayer;
using OpenNN::NeuralNetwork;
using OpenNN::Vector;
using OpenNN::Tensor;*/

const int TOTAL_WINDOWS = 4;

const int TOTAL_GENERATIONS = 0;
const int POPULATION_SIZE = 12;
const float THRESHOLD = 4.0 / 12;

int main()
{
    cout << endl << "12 orbits  AI learning" << endl << endl;
    // genetic algorithm
    //cout << 'a' << endl;
    //vector<DWORD> exit_codes;
    //for (int i = 0; i < TOTAL_WINDOWS; i++){
    //    exit_codes.push_back(initialize_window());
    //}


    cout << "Windows are moving" << endl;
    //prepare_windows();
    cout << "Moved windows successfully" << endl << endl;

    auto population = generate_initial_population<my_class>(POPULATION_SIZE);
    cout << "Generated population successfully" << endl << "Starting learning" << endl;

    for (int generation = 0; generation < TOTAL_GENERATIONS; generation++)
    {
        auto fitness_scores = get_fitness_scores<my_class>(population);
        population = select_best<my_class>(population, fitness_scores, THRESHOLD);
        population = add_using_crossover<my_class>(population, POPULATION_SIZE);
        population = mutate<my_class>(population);
        for (auto el : population) {
            cout << el.a << endl;
        }
        cout << endl;
    }
    cout << "Learning ended" << endl;
    auto matrix = ScreenCap(100, 500, 300, 400); // vector<vector<color>>

    MyBrain b;

    for (int i = 0; i < 1000; i++)
    {
        matrix = ScreenCap(100, 500, 300, 400);
        Tensor<float, 2> inp(1, 10);
        for (int j = 0; j < 10; j++)
        {
            cout << matrix[100][19 * j].r << " " << matrix[100][19 * j].g << " " << matrix[100][19 * j].b << endl;
            inp(0, j) = matrix[100][19*j].r + matrix[100][19*j].g + matrix[100][19*j].b;
            inp(0, j) /= 256 * 3;
        }
        Tensor<float, 2> ans = b.my_func(inp);
        cout << "iteration" << i << endl << ans << endl << endl;
        
    }
    cout << matrix.size() << ' ' << matrix[0].size() << endl;
    cout << "The project ended successfully" << endl;
    return 0;

    //testing purposes
    // IT WORKS!!!
    /*ofstream fout;
    fout.open("img.txt");
    fout << 1920 << ' ' << 1080 << endl;

    for(auto row:matrix){
        for(auto c:row){
            fout << c.r << ' ' << c.g << ' ' << c.b << ' ';
        }
        fout << endl;
    }
    fout.close();
    return 0;
    */
    //cout << 'd' << endl;
    //for (int i = 0; i < TOTAL_WINDOWS; i++){
    //    destroy_game(exit_codes[i]);
    //}
}
