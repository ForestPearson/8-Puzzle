
/*
Author: Forest Pearson
Date:   1/29/2020
Desc:   A program that solves the 8-Puzzle by using best-first-search and a* with three different heuristics.
*/
#include "Header.h"
int main(void) {
	State desired;
	desired.x = 2;
	desired.y = 2;
	desired.board[0][0] = 1;
	desired.board[0][1] = 2;
	desired.board[0][2] = 3;
	desired.board[1][0] = 4;
	desired.board[1][1] = 5;
	desired.board[1][2] = 6;
	desired.board[2][0] = 7;
	desired.board[2][1] = 8;
	desired.board[2][2] = 0;
	std::cout << "\nThe desired format: ";
	print(desired);
	State* input = new State;
	int temp;
	int arr[10] = { 0 };//Temp arr for comparison to ensure that a digit is not repeated on the puzzle.
	int inputArr[9] = { -1 };//Input array the will be transformed into a 3x3 2d array.
	std::cout << "\nEnter a valid 8-Puzzle one digit at a time similar to the above format while entering 0 for the desired blank." << endl;
	for (int i = 0; i < 9; i++) {
		cin >> temp;
		while ((cin.fail()) || temp > 8 || temp <= -1 || arr[temp] == 1) {
			std::cout << "Error, please enter a valid number for the 8-puzzle." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> temp;
		}
		arr[temp] = 1;
		inputArr[i] = temp;
	}
	int inversions = 0;//Formula to check the inversions, done before transformation into a 2d array since it's cleaner. Inversions must be even to be valid.
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (i < j) {
				if (inputArr[i] > inputArr[j] && inputArr[i] != 0 && inputArr[j] != 0)
					inversions++;
			}
		}
	}
	if (inversions % 2 == 0) {
		cout << "This 8-puzzle has " << inversions << " inversions and is valid." << endl;
		for (int i = 0; i < 9; i++) {//Roundabout way of transforming the 1d array into a 3x3 2d array.
			if (i < 3) {
				input->board[0][i] = inputArr[i];
				if (inputArr[i] == 0) {
					input->x = i;
					input->y = 0;
				}
			}
			else if (i < 6) {
				input->board[1][i - 3] = inputArr[i];
				if (inputArr[i] == 0) {
					input->x = i - 3;
					input->y = 1;
				}
			}
			else if (i < 9) {
				input->board[2][i - 6] = inputArr[i];
				if (inputArr[i] == 0) {
					input->x = i - 6;
					input->y = 2;
				}
			}
		}
		temp = 0;
		cout << "Enter 0 for Best-first and 1 for A*:" << endl;//Beginning of if and while statements that guide the user through a menu to choose their desired sort and heuristic.
		cin >> temp;
		while (cin.fail() || !(temp == 0 || temp == 1)) {
			std::cout << "Error, please enter either 1 or 0." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> temp;
		}
		int heuristic = 0;
		if (temp == 0) {
			cout << "Choose your desired heuristic: \n 0) Out-of-place Tile \n 1) Manhattan \n 2) Linear Conflict\n";
			cin >> heuristic;
			while (cin.fail() || !(temp == 0 || temp == 1 || temp == 2)) {
				std::cout << "Error, please enter a number between 0 and 3." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> temp;
			}
			if (heuristic == 0) {
				std::cout << "\nResult of greedy best first using the misplaced tiles heuristic: " << "\n\nInitial step: 0\n";
				greedy(*input, desired, 0);
			}
			if (heuristic == 1) {
				std::cout << "\nResult of greedy best first using the Manhattan heuristic: " << "\n\nInitial step: 0\n";
				greedy(*input, desired, 1);
			}
			if (heuristic == 2) {
				std::cout << "\nResult of greedy best first using the linear conflict heuristic: " << "\n\nInitial step: 0\n";
				greedy(*input, desired, 2);
			}

		}
		if (temp == 1) {
			cout << "Choose your desired heuristic: \n 0) Out-of-place Tile \n 1) Manhattan \n 2) Linear Conflict\n";
			cin >> heuristic;
			while (cin.fail() || !(temp == 0 || temp == 1 || temp == 2)) {
				std::cout << "Error, please enter a number between 0 and 3." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> temp;
			}
			if (heuristic == 0) {
				std::cout << "\nResult of A* using the misplaced tiles heuristic: " << "\n\nInitial step: 0\n";
				aStar(*input, desired, 0);
			}
			if (heuristic == 1) {
				std::cout << "\nResult of A* using the Manhattan heuristic: " << "\n\nInitial step: 0\n";
				aStar(*input, desired, 1);
			}
			if (heuristic == 2) {
				std::cout << "\nResult of A* using the linear conflict heuristic: " << "\n\nInitial step: 0\n";
				aStar(*input, desired, 2);
			}

		}

	}
	else
		cout << "This 8-puzzle has " << inversions << " inversions and is invalid." << endl;

	delete input;
	return 42;
}