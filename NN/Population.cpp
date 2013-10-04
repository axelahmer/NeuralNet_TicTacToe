#include "Population.h"
#include <algorithm>






void Population::initializePopulation(int pop, vector<int> topography, double weightMean, double weightSigma)
{
	topog = topography;
	Player A(topography);
		
	m_Pop.assign(pop, A);
	
	for (unsigned int i = 0; i < m_Pop.capacity() ; i++)
	{
		m_Pop[i].NN.ConnectForward(weightMean, weightSigma);
		m_Pop[i].NN.ConnectLayers(0, m_Pop[i].NN.m_Layers.size()-1, weightMean, weightSigma);
		m_Pop[i].NN.calculateForward();
	}
}


Player Population::createChild(NeuralNet *parent1, NeuralNet *parent2, int cuts, double prob, double sigma)
{
	
	Player child(topog);
	child.score = 0;
	
	child.NN = *parent1;
	child.NN.setDNA(child.NN.mixDNA(parent1->getDNA(),parent2->getDNA(),cuts));
	child.NN.setDNA(child.NN.mutateDNA(child.NN.getDNA(),prob,sigma));

	return child;
}


void Population::sortByScore()
{
	sort(m_Pop.begin(),m_Pop.end(),greaterthan());
}

void Population::cull(int number)
{
	for (unsigned int i = 0 ; i < number ; i++)
	{
		m_Pop.pop_back();
	}
}
	

void Population::breed(int number, int cuts, double prob, double sigma)
{
	srand(0);
	int numParents = m_Pop.size();
	int p1 = 0;
	int p2 = 0;
	for (unsigned int i = 0 ; i < number ; i++)
	{
		while (p1 == p2)
		{
			p1 = rand()%(numParents);
			p2 = rand()%(numParents);
		}

		m_Pop.push_back( createChild(&m_Pop[p1].NN ,&m_Pop[p2].NN, cuts, prob, sigma) );
	}
}


int Population::getSize()
{
	return m_Pop.size();
}

vector<Player> Population::getPop()
{
	return m_Pop;
}


void Population::setPop(vector<Player> pop)
{
	m_Pop = pop;
}

void Population::removeScores()
{
	for (unsigned int i = 0 ; i < m_Pop.size() ; i++)
	{
		m_Pop[i].score = 0;
	}
}


NeuralNet Population::extractNN(int index)
{
	return m_Pop[index].NN;
}