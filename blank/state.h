#ifndef STATE_H
#define STATE_H

#include "screenshot.h"
#include "my_brain.h"

class Game
{
public:
	bool get_is_terminal() { return is_terminal; }
	vector<int> get_scores() { return scores; }

	vector<Tensor<Index, 3>> get_state(int window_number)
	{
		// windows are in place
		// 8, 59 -> 1471, 902

		auto matrix = ScreenCap(8, 59, 1471, 902);
		for (int i = 0; i < matrix.size() / 2; i++) {
			for (int j = 0; j < matrix[0].size() / 2; j++) {

			}
		}
		return matrix;
	}

private:
	bool is_terminal;
	vector<int> scores;
};


#endif
