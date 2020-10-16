#include "main_func.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

const int TOTAL_WINDOWS = 4;

const int TOTAL_GENERATIONS = 0;
const int POPULATION_SIZE = 12;
const float THRESHOLD = 4.0 / 12;

int main()
{
    // genetic algorithm
    //cout << 'a' << endl;
    //vector<DWORD> exit_codes;
    //for (int i = 0; i < TOTAL_WINDOWS; i++){
    //    exit_codes.push_back(initialize_window());
    //}
    
    prepare_windows();
    
    auto population = generate_initial_population<my_class>(POPULATION_SIZE);
    //cout << 'c' << endl;
    for(int generation = 0; generation < TOTAL_GENERATIONS; generation++)
    {
        auto fitness_scores = get_fitness_scores<my_class>(population);
        population = select_best<my_class>(population, fitness_scores, THRESHOLD);
        population = add_using_crossover<my_class>(population, POPULATION_SIZE);
        population = mutate<my_class>(population);
        for (auto el : population){
            cout << el.a << endl;
        }
        cout << endl;
    }
    
    //cout << 'd' << endl;
    //for (int i = 0; i < TOTAL_WINDOWS; i++){
    //    destroy_game(exit_codes[i]);
    //}
    return 0;
}
