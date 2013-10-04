#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "NeuralNet.h"

using namespace std;

struct Player {

	
	NeuralNet NN;
	double score;

	Player(vector<int> topography) { NN.InitializeNeurons(topography); score = 0;}

};

struct greaterthan
{
	inline bool operator() (const Player& struct1, const Player& struct2)
    {
		return (struct1.score > struct2.score);
    }
};

class Population
{
private:

	
	vector<int> topog;
	Player createChild(NeuralNet *parent1, NeuralNet *parent2, int cuts, double prob, double sigma);
	
public:
	vector<Player> m_Pop; 

	void initializePopulation(int pop, vector<int> topography, double weightMean, double weightSigma);
	void sortByScore();
	void cull(int number);
	void breed(int number, int cuts, double prob, double sigma);
	void setPop(vector<Player> pop);
	void removeScores();
	NeuralNet extractNN(int index);

	int getSize();
	vector<Player> getPop();


};




#endif