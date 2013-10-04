#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include "NeuralNet.h"

using namespace std;


class Tictactoe
{
private:

	
	
	
	void makeMove(vector<double> decisions, int pieceValue);

public:

	vector<int> board;
	vector<int> board2;
	vector<int> history;
	NeuralNet* p1;
	NeuralNet* p2;
	bool winCheck();
	bool drawCheck();

	Tictactoe(NeuralNet* NN1, NeuralNet* NN2);
	Tictactoe(NeuralNet* NN, string xo);
	void playGame();
	int getResult();
	void printBoard();
	void updateBoard2();
	void print2dBoard();
	


};

#endif