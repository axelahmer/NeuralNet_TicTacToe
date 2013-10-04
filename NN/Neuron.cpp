#include "Neuron.h"
#include <cmath>

Neuron::Neuron()
{
	m_Output = 1;
}


void Neuron::setOutput(double x)
{
	m_Output = x;
}


vector<double> Neuron::getWeights()
{
	return m_Weights;
}


double Neuron::getOutput()
{
	return m_Output;
}

double* Neuron::getOutputP()
{
	return &m_Output;
}

void Neuron::addInput(double *input, double weight)
{
	m_Inputs.push_back(input);
	m_Weights.push_back(weight);
}

void Neuron::calculateOutput()
{
	if (m_Inputs.empty() == 0) //protects bias neurons
	{
		double sum = 0.0;
		for (unsigned int i=0 ; i < m_Inputs.size() ; i++)
		{
			sum += *m_Inputs[i] * m_Weights[i];
		}
		m_Output = tanh(sum);
	}
}