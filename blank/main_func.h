#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <tuple>
#include "send_event.h"
#include "screenshot.h"
#include "my_brain.h"


using std::vector;
using std::map;
using std::tuple;
using std::cout;
using std::endl;

int rand_int(int max)
{
    return rand() % max;
}

struct State
{
    bool is_terminal = true;
    vector<int> scores{ 1, 2, 3 };
};

State get_state()
{
    return State();
}

template<typename T>
vector<int> get_actions(vector<T> population, State state)
{
    return vector<int>{1, 2, 3, 4};
}

void execute(vector<int> actions)
{
    return;
}

template<typename T>
T create_offspring(T parent1, T parent2) {
    return parent1;
}
// everything above is placeholder

/*
DWORD initialize_window()
{
    // additional information
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD lpExitCode;
    //cout << "a1" << endl;
    // set the size of the structures
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
    //cout << "a2" << endl;
    //TCHAR szCmdline[]=TEXT("\"..\\12 orbits.exe\" -screen-width 720 -screen-height 400");
    TCHAR szCmdline[]=TEXT("\"..\\12 orbits.exe\"");
    // start the program up
    //cout << "a3" << endl;

    CreateProcess( NULL,   // the path
        szCmdline,      // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,         // Pointer to STARTUPINFO structure
        &pi          // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
    );

    //cout << "a4" << endl;
    if (!GetExitCodeThread(pi.hThread, &lpExitCode))
    {
        cout << GetLastError() << "!!!!!" << endl;
    }
    //cout << "a5" << endl;
    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    //cout << "a6" << endl;
    return lpExitCode;
}

void destroy_game(DWORD lpExitCode)
{
    ExitThread(u_int(lpExitCode));
}
*/


vector<int> prepare_windows()
{
    // Click 4 Play! buttons
    vector<vector<int>> args = { {900, 340, 310, 50},
                                {900, 340, 1050, 50},
                                {900, 340, 310, 490},
                                {900, 340, 1050, 490} };
    vector<int> player_color;
    for (auto el : args)
    {
        // Play!
        lmb_click_xy(1050, 730);
        Sleep(5000);

        // Start!
        lmb_click();
        Sleep(1000);

        // Play
        lmb_click_xy(1000, 500);
        Sleep(500);

        // Trails
        move_mouse(1200, 460);
        Sleep(200);
        lmb_click();
        Sleep(500);

        // Left arrow
        lmb_click_xy(750, 500);
        Sleep(200);

        // Next
        lmb_click_xy(1100, 620);
        Sleep(1000);


        for (char c = 2; c < 14; c++)
        {
            key_press(c);
        }
        Sleep(1000);

        auto matrix = ScreenCap(0, 0, 1920, 1080);
        int dw = 288;
        int dh = 28;

        map<tuple<int, int, int>, int> m; // map from colors to color_id
        m[{255,   0, 255}] = 0; // pink
        m[{ 62,  80, 255}] = 1; // light blue
        m[{  0, 170,   0}] = 2; // light green
        m[{255,  66,   0}] = 3; // vermillion
        m[{142,  70, 173}] = 4; // violet
        m[{  0, 160, 160}] = 5; // cyan
        m[{190,   0,   0}] = 6; // dark red
        m[{255, 130,   0}] = 7; // orange
        m[{ 70,   0, 148}] = 8; // dark indigo
        m[{128,  64,  64}] = 9; // brown
        m[{150, 125,   0}] = 10;// gold
        m[{ 25,  93,  42}] = 11;// dark green

        for (int w = 0; w < 2; w++) 
        {
            for (int h = 0; h < 6; h++) 
            {
                color c = matrix[750 + dw * w][435 + dh * h];
                player_color.push_back(m[{c.r, c.g, c.b}]);

            }
        }


        lmb_drag(el[0], el[1], el[2], el[3]);
        Sleep(150);
    }

    return player_color;
}

vector<MyBrain*> generate_initial_population(int amount, vector<int> player_color)
{
    vector<MyBrain*> population;
    cout << "player_color size: " << player_color.size() << endl;
    for (int i = 0; i < amount; i++)
    {
        cout << i << ": " << player_color[i] << endl;
        population.push_back(new MyBrain(player_color[i]));
    }
    return population;
}

template<typename T> // todo: state has bool is_terminal and vector<int> scores
void get_fitness_scores(vector<T> population)
{
    // todo: get_state(), get_actions(), execute
    auto state = get_state();
    while (!state.is_terminal)
    {
        auto actions = get_actions(population, state);
        execute(actions);
        state = get_state();
    }
    for (int i = 0; i < population.size(); i++)
    {
        population[i]->fitness_score = state.scores[i];
    }
}

template<typename T>
vector<T> select_best(vector<T> population, float threshold)
{
    // todo: operator< between T and T (used in sort)
    std::sort(population.begin(), population.end(), [](T a, T b) {return b->fitness_score < a->fitness_score; });
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

    int s = population.size();
    T offspring;
    for (int i = 0; i < best_count; i++) // from two best creatures
    {
        offspring = create_offspring(population[0], population[1]);
        population.push_back(offspring);
    }
    for (int i = 0; i < random_count; i++) // from two random creatures
    {
        offspring = create_offspring(population[rand_int(s)], population[rand_int(s)]);
        population.push_back(offspring);
    }
    for (int i = 0; i < entirely_new; i++) // entirely new
        population.push_back(T(rand_int(5)));

    return population;
}

template<typename T>
vector<T> mutate(vector<T> population) // is it all? todo: T.mutate()
{
    for (size_t i = 0; i < population.size(); i++)
        population[i]->mutate();
    return population;
}

#endif //MAIN_FUNC_H