#ifndef NEURON_H
#define NEURON_H

#include <vector>

using namespace std;

class Neuron
{
private:
		


public:
	double m_Output;
	vector<double*> m_Inputs;
	vector<double> m_Weights;



	Neuron();
	void setOutput(double x);
	vector<double> getWeights();
	double getOutput();
	double* getOutputP();
	void addInput(double *input, double weight);
	void calculateOutput();

};

#endif