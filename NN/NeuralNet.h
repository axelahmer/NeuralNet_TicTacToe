#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include "Neuron.h"
#include <stdio.h>     
#include <time.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

using namespace std;

typedef vector<Neuron> Layer; 

class NeuralNet
{
private:
		
	double createWeight(double mean, double sigma);

public:
	vector<Layer> m_Layers;

	//Initializers
	//NeuralNet(vector<int> input);
	void InitializeNeurons(vector<int> input);

	//Connection functions
	void ConnectNeurons(int L1, int N1, int L2, int N2, double mean, double sigma);
	void ConnectLayers(int L1, int L2, double mean, double sigma);
	void ConnectForward(double mean, double sigma);

	//Setting functions
	void setInputs(vector<double> inputs);
	void setInputs(vector<int> inputs);
	void zeroLayer(int layer);
	void setNeuronOutput(int L, int N, double val);
	void setBiasOutputs();
	void setDNA(vector<double> dna);

	//Calculation functions
	void calculateLayerOutputs(int layer);
	void calculateForward();
	
	//Print functions
	void printNNOutputs();
	void printWeights(int layer, int neuron);

	//Get functions
	vector<double> getDNA();
	vector<double> getNNOutputs();

	//breeding
	vector<double> mixDNA(vector<double> dna1, vector<double> dna2, int cuts);
	vector<double> mutateDNA(vector<double> dna, double prob, double sigma);
	
};

#endif