
/*
Author: Forest Pearson
Date:   1/29/2020
Desc:   A program that solves the 8-Puzzle by using best-first-search and a* with three different heuristics.
*/

#include "Header.h"
//The A* sort that operates on three different heuristics.
State aStar(State start, State end, int heuristic) {
	vector<State*> open;
	vector<State*> closed;
	State* current;
	int tentativeScore = 0;
	State* temp = new State;
	int temporary;
	int j = 0;
	int turns = 0;
	open.push_back(new State(start));

	while (!open.empty()) {
		sort(open.begin(), open.end(), compare);//Sorts the vector so the lowest value can be taken off the back.
		current = open.back();
		if (isEqual(*current, end)) {
			reconstruct(current);//Reconstructs for visual output for the user.
			if (heuristic == 0) {
				cout << "\nA* with the out-of-place tile heuristic took " << turns << " total steps to finish and " << current->level << " local steps." << endl;
			}
			if (heuristic == 1) {
				cout << "\nA* with the Manhattan heuristic took " << turns << " total steps to finish and " << current->level << " local steps." << endl;
			}
			if (heuristic == 2) {
				cout << "\nA* with the linear conflict heuristic took " << turns << " total steps to finish and " << current->level << " local steps." << endl;
			}
			return *current;
		}
		if (turns > 100000) {
			turns++;
		}
		turns++;
		open.pop_back();
		closed.push_back(current);//Puts the current node onto the closed list indicating it has been expanded.

		if (current->x > 0) {//Repeated three more times for each different direction, this creates all possible children for the state.
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			temporary = current->board[current->y][current->x - 1];
			temp->board[current->y][current->x - 1] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {//Grabs the f(n) value which varies depending on the chosen heuristic
				tentativeScore = misplaced(*temp, end) + current->level;
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end) + current->level;
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end) + current->level;
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;//Creates a new state and pushes it onto the open vector if it was not in the open list already with a better score or in the closed list.
				newState->parent = current;
				newState->x = current->x - 1;
				newState->y = current->y;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
		if (current->x < 2) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			temporary = current->board[current->y][current->x + 1];
			temp->board[current->y][current->x + 1] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {
				tentativeScore = misplaced(*temp, end) + current->level;
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end) + current->level;
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end) + current->level;
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;
				newState->parent = current;
				newState->x = current->x + 1;
				newState->y = current->y;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
		if (current->y > 0) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			int temporary = current->board[current->y - 1][current->x];
			temp->board[current->y - 1][current->x] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {
				tentativeScore = misplaced(*temp, end) + current->level;
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end) + current->level;
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end) + current->level;
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;
				newState->parent = current;
				newState->x = current->x;
				newState->y = current->y - 1;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
		if (current->y < 2) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			int temporary = current->board[current->y + 1][current->x];
			temp->board[current->y + 1][current->x] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {
				tentativeScore = misplaced(*temp, end) + current->level;
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end) + current->level;
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end) + current->level;
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;
				newState->parent = current;
				newState->x = current->x;
				newState->y = current->y + 1;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
	}
	return start;//Returns the starting state in case of failure.
}
//The best-first sort that operates on three different heuristics.
State greedy(State start, State end, int heuristic) {
	vector<State*> open;
	vector<State*> closed;
	State* current;
	int tentativeScore = 0;
	State* temp = new State;
	int temporary;
	int j = 0;
	int turns = 0;
	open.push_back(new State(start));

	while (!open.empty()) {
		sort(open.begin(), open.end(), compare);//Sorts the vector so the lowest value can be taken off the back.
		current = open.back();
		if (isEqual(*current, end)) {
			reconstruct(current); //Reconstructs for visual output for the user.
			if (heuristic == 0) {
				cout << "\nBest-first with the out-of-place tile heuristic took " << turns << " total steps to finish and " << current->level << " local steps." << endl;
			}
			if (heuristic == 1) {
				cout << "\nBest-first with the Manhattan heuristic took " << turns << " total steps to finish and " << current->level << " local steps." << endl;
			}
			if (heuristic == 2) {
				cout << "\nBest-first with the linear conflict heuristic took " << turns << " total steps to finish and " << current->level << " local steps." << endl;
			}
			return *current;
		}
		if (turns > 100000) {
			turns++;
		}
		turns++;
		open.pop_back();
		closed.push_back(current);//Puts the current node onto the closed list indicating it has been expanded.

		if (current->x > 0) {//Repeated three more times for each different direction, this creates all possible children for the state.
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			temporary = current->board[current->y][current->x - 1];//Temp Board to see a childs value.
			temp->board[current->y][current->x - 1] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {//Grabs the f(n) value which varies depending on the chosen heuristic
				tentativeScore = misplaced(*temp, end);
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end);
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end);
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;//Creates a new state and pushes it onto the open vector if it was not in the open list already with a better score or in the closed list.
				newState->parent = current;
				newState->x = current->x - 1;
				newState->y = current->y;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
		if (current->x < 2) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			temporary = current->board[current->y][current->x + 1];
			temp->board[current->y][current->x + 1] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {
				tentativeScore = misplaced(*temp, end);
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end);
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end);
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;
				newState->parent = current;
				newState->x = current->x + 1;
				newState->y = current->y;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
		if (current->y > 0) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			int temporary = current->board[current->y - 1][current->x];
			temp->board[current->y - 1][current->x] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {
				tentativeScore = misplaced(*temp, end);
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end);
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end);
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;
				newState->parent = current;
				newState->x = current->x;
				newState->y = current->y - 1;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
		if (current->y < 2) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					temp->board[i][j] = current->board[i][j];
				}
			}
			int temporary = current->board[current->y + 1][current->x];
			temp->board[current->y + 1][current->x] = 0;
			temp->board[current->y][current->x] = temporary;
			if (heuristic == 0) {
				tentativeScore = misplaced(*temp, end);
			}
			if (heuristic == 1) {
				tentativeScore = manhattan(*temp, end);
			}
			if (heuristic == 2) {
				tentativeScore = linearConflict(*temp, end);
			}
			j = 0;
			for (size_t i = 0; i < open.size(); i++) {
				if (isEqual(*temp, *open[i])) {
					if (tentativeScore >= open[i]->fvalue)
						j = 1;
				}
			}
			for (size_t i = 0; i < closed.size(); i++) {
				if (isEqual(*temp, *closed[i])) {
					j = 1;
				}
			}
			if (j == 0) {
				State* newState = new State();
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						newState->board[i][j] = temp->board[i][j];
					}
				}
				newState->fvalue = tentativeScore;
				newState->parent = current;
				newState->x = current->x;
				newState->y = current->y + 1;
				newState->level = current->level;
				newState->level++;
				open.push_back(newState);
			}
		}
	}
	return start; //Returns the starting state in case of failure.
}
//The linear conflict heuristic that checks if two tiles when swapped are both in the valid position and adds that X2 to the manhattan count.
int linearConflict(State curr, State end) {
	int count = 0;
	int conflicts = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			for (int d = 0; d < 3; d++) {
				for (int g = 0; g < 3; g++) {
					if (curr.board[i][j] == end.board[d][g]) {
						count += (abs(i - d) + abs(j - g));
					}
				}
			}

		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i > 0) {
				if (curr.board[j][i - 1] == end.board[j][i] && curr.board[j][i] == end.board[j][i - 1]) {
					conflicts++;
				}
			}
			if (i < 2) {
				if (curr.board[j][i + 1] == end.board[j][i] && curr.board[j][i] == end.board[j][i + 1]) {
					conflicts++;
				}
			}
			if (j > 0) {
				if (curr.board[j - 1][i] == end.board[j][i] && curr.board[j][i] == end.board[j - 1][i]) {
					conflicts++;
				}
			}
			if (j < 2) {
				if (curr.board[j + 1][i] == end.board[j][i] && curr.board[j][i] == end.board[j + 1][i]) {
					conflicts++;
				}
			}
		}
	}
	return (count + 2 * (conflicts));
}
//The manhattan heuristic.
int manhattan(State curr, State end) {
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			for (int d = 0; d < 3; d++) {
				for (int g = 0; g < 3; g++) {
					if (curr.board[i][j] == end.board[d][g]) {
						count += (abs(i - d) + abs(j - g));
					}
				}
			}

		}
	}
	return count;
}
//Reconstructs and prints the States history using its parent.
void reconstruct(State* current) {
	vector<State> temp;
	if (current->parent != NULL) {
		reconstruct(current->parent);
		cout << "\n";
		print(*current);
	}
	if (current->parent == NULL) {
		print(*current);
	}
}
//Compare for function for the std sort function used in BFS and A*.
bool compare(State* a, State* b) {
	if (a->fvalue > b->fvalue)
		return true;
	else
		return false;
}
//Prints the provided puzzle state in the required format.
void print(struct State value) {
	cout << "(";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (value.board[i][j] != 0) {
				cout << value.board[i][j] << " ";
			}
			else
				cout << "b" << " ";
		}
	}
	cout << ")";
}
//Checks if the provided state of the puzzle is the same as the desired end state.
bool isEqual(State curr, State desired) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (curr.board[i][j] != desired.board[i][j])
				return false;
		}
	}
	return true;
}
//The Out-of-place Tile heuristic
int misplaced(State curr, State desired) {
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (curr.board[i][j] != desired.board[i][j])
				count++;
		}
	}
	return count;
}