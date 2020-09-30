#include<algorithm>

const int TOTAL_GENERATIONS = 1000;
const int POPULATION_SIZE = 12
const float THRESHOLD = 4.0 / 12;

template<typename T>
vector<T> generate_initial_population(int amount)
{
    // todo: T create_creature<T>()
    vector<T> population;
    for (int i = 0; i < amount; i++)
    {
        auto creature = create_creature<T>();
        population.push_back(creature);
    }
    return population;
}

template<typename T> // todo: state has bool is_terminal and vector<int> scores
vector<int> get_fitness_scores(vector<T> population)
{
    // todo: get_state(), get_actions(), execute
    auto state = get_state();
    while (!state.is_terminal)
    {
        auto actions = get_actions(population, state);
        execute(actions);
    }
    return state.scores;
}

template<typename T>
vector<T> select_best(vector<T> population, vector<int> fitness_scores, float threshold)
{
    // todo: operator< between T and T (used in sort)
    std::sort(population.begin(), population.end());
    threshold *= population.size();
    return vector<T>(population.begin(), population.begin() + int(threshold));
}

template<typename T>
vector<T> add_using_crossover(vector<T> population, int size) // is it balanced? maybe rework for size != 12
{
    // todo: T create_offspring(T t1, T t2), T create_creature()
    int diff = size - population.size();
    int mult = diff / 4;
    int add = diff % 4;
    
    int best_count = mult;
    int random_count = 2 * mult;
    int entirely_new = mult;
    if (add == 1)
    {
        best_count++;
    }
    else if (add > 1)
    {
        best_count++;
        random_count += add - 1;
    }
    
    T offspring;
    for (int i = 0; i < best_count; i++)
    {
        offspring = create_offspring(population[0], population[1]);
        population.push_back(offspring);
    }
    for (int i = 0; i < random_count; i++) // four children from random two creatures
    {
        offspring = create_offspring(population[rand_int(s)], population[rand_int(s)]);
        population.push_back(offspring);
    }
    for (int i = 0; i < entirely_new; i++)
    {
        offspring = create_creature<T>();
        population.push_back(offspring);
    }
    if (population.size() != size){
        throw std::exception("population size changed");
    }
    
    return population;
}

template<typename T>
void mutate(vector<T> population) // is it all? todo: T.mutate()
{
    for (int i = 0; i < population.size(); i++)
    {
        population[i].mutate();
    }
}

int main()
{
    // genetic algorithm
    auto population = generate_initial_population();
    for(int generation = 0; generation < TOTAL_GENERATIONS; generation++)
    {
        auto fitness_scores = get_fitness_scores(population);
        population = select_best(population, fitness_scores, THRESHOLD);
        population = add_using_crossover(population, THRESHOLD);
        mutate(population);
    }
}
