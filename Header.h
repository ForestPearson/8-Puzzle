#pragma once
/*
Author: Forest Pearson
Date:   1/29/2020
Desc:   A program that solves the 8-Puzzle by using best-first-search and a* with three different heuristics.
*/
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct State {
	State() {
		this->fvalue = 0;
		this->level = 0;
		this->parent = NULL;
		this->x = NULL;
		this->y = NULL;
	}
	int board[3][3] = { {} };
	int level;
	int fvalue;
	State* parent;
	int y;
	int x;
};
State greedy(State, State, int heuristic);
State aTiles(State, State); 
State aStar(State, State, int heuristic);
State aConflict(State, State);
bool compare(State* a, State* b);
void reconstruct(State* current);
void print(State);
bool isEqual(State, State);
int misplaced(State, State);
int manhattan(State, State);
int linearConflict(State, State);