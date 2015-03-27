#include "NeuralNet.h"
#include "Population.h"
#include "Tournament.h"
#include "Tictactoe.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	
	// Neural Network Layer Sizes
	vector<int> top;
	top.push_back(10);
	top.push_back(11);
	top.push_back(5);
	top.push_back(10);

	// Initial Population Initialization
	double mean = 0;
	double sigma = 1;
	int popsize = 20;

	// Generative Parameters
	int gen_end = 20;
	int cullBreedSize = 10;
	int dnaCuts = 3;
	double mutationProb = 0.1;
	double mutationSigma = 0.1;

	// Tournament Scoring System
	int win = 3;
	int loss = 0;
	int draw = 1;

	vector<NeuralNet> bestNN;
	vector<NeuralNet> worstNN;

	Population P;
	P.initializePopulation(popsize,top,mean,sigma);
	Tournament T(P);
	T.setScoringSystem(win,loss,draw);

	for (int gen = 0 ; gen < gen_end ; gen++)
	{
		cout << "gen: " << gen << endl;

		T.setPlayers(P);
		T.playRoundRobin();

		P = T.getPop();
		P.sortByScore();

		bestNN.push_back(P.extractNN(0));
		worstNN.push_back(P.extractNN(popsize-1));

		P.cull(cullBreedSize);
		P.breed(cullBreedSize,dnaCuts,mutationProb,mutationSigma);
		P.removeScores();
	}

	
		cout << "gen: " << gen_end << endl;

		T.setPlayers(P);
		T.playRoundRobin();

		P = T.getPop();
		P.sortByScore();

		bestNN.push_back(P.extractNN(0));
		worstNN.push_back(P.extractNN(popsize-1));

	for (int i = 0 ; i < P.m_Pop.size() ; i++)
	cout << P.m_Pop[i].score << endl;

	string xo = "";
	cout << "Play as Naughts or Crosses? Crosses move first. (x/o) : ";
	getline(cin,xo);

	Tictactoe playerGame(&bestNN[0],xo);
	playerGame.board[0]=1;
	playerGame.board[7]=-1;
	playerGame.print2dBoard();

	system("pause");

	return 0;
}