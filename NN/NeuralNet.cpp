#include "NeuralNet.h"
#include <boost\random.hpp>
#include <boost\random\normal_distribution.hpp>
#include <vector>
#include <algorithm>

//NeuralNet::NeuralNet(vector<int> input)
//{
//	for (unsigned int i = 0 ; i<input.size() ; i++)
//	{
//		Layer temp(input[i]);
//		m_Layers.push_back(temp);
//	}
//}

void NeuralNet::InitializeNeurons(vector<int> input)
{
		for (unsigned int i = 0 ; i<input.size() ; i++)
	{
		Layer temp(input[i]);
		m_Layers.push_back(temp);
	}
}

double NeuralNet::createWeight(double mean, double sigma)
{
 typedef boost::normal_distribution<double> NormalDistribution;
 typedef boost::mt19937 RandomGenerator;
 typedef boost::variate_generator<RandomGenerator&, \
                         NormalDistribution> GaussianGenerator;
 
  /** Initiate Random Number generator with current time */
  static RandomGenerator rng(static_cast<unsigned> (time(0)));
 
  /* Choose Normal Distribution */
  NormalDistribution gaussian_dist(mean, sigma);
 
  /* Create a Gaussian Random Number generator
   *  by binding with previously defined
   *  normal distribution object
   */
  GaussianGenerator generator(rng, gaussian_dist);
 
  // sample from the distribution
  return generator();
}

void NeuralNet::ConnectNeurons(int L1, int N1, int L2, int N2, double mean, double sigma)
{
	double weight = createWeight(mean, sigma);
	m_Layers[L2][N2].addInput(m_Layers[L1][N1].getOutputP() , weight);
}

void NeuralNet::ConnectLayers(int L1, int L2, double mean, double sigma)
{

		for (unsigned int i=0 ; i < m_Layers[L1].size() ; i++)
	{
		for (unsigned int j=0 ; j < m_Layers[L2].size()-1 ; j++) //j-1: does not connect to forward bias
		{
			ConnectNeurons(L1, i, L2, j, mean, sigma);
		}
	}
}

void NeuralNet::ConnectForward(double mean, double sigma)
{
	for (unsigned int i=0 ; i < m_Layers.size()-1 ; i++)
	{
		ConnectLayers(i, i+1, mean, sigma);
	}
}

void NeuralNet::setNeuronOutput(int L, int N, double val)
{
	m_Layers[L][N].setOutput(val);
}

void NeuralNet::setInputs(vector<double> inputs)
{
	for (unsigned int i = 0 ; i < inputs.size() ;  i++)
	{
		m_Layers[0][i].setOutput(inputs[i]);
	}
}

void NeuralNet::setInputs(vector<int> inputs)
{
	for (unsigned int i = 0 ; i < inputs.size() ;  i++)
	{
		m_Layers[0][i].setOutput(inputs[i]);
	}
}

void NeuralNet::zeroLayer(int layer) //zeros whole layer, including any biases
{
	for (unsigned int i=0 ; i < m_Layers[layer].size() ; i++) 
	{
		setNeuronOutput(layer, i, 0.0);
	}
	
}

void NeuralNet::setBiasOutputs()//sets bias in every layer, including final.
{
	for (unsigned int i=0 ; i < m_Layers.size()  ; i++) 
	{
		m_Layers[i].back().setOutput(1);
	}
}

void NeuralNet::calculateLayerOutputs(int layer)
{
	for (unsigned int i=0 ; i < m_Layers[layer].size() ; i++)
	{
		m_Layers[layer][i].calculateOutput();
	}
}

void NeuralNet::calculateForward()
{
	for (unsigned int i = 1 ; i < m_Layers.size() ; i++)
	{
		calculateLayerOutputs(i);
	}
}

void NeuralNet::printNNOutputs()
{
	for (unsigned int i=0 ; i<m_Layers.size() ; i++)
	{
		
		for (unsigned int j=0 ; j<m_Layers[i].size() ; j++)
		{
			cout << m_Layers[i][j].getOutput() << endl;
		}
		cout << endl;
	}
}

void NeuralNet::printWeights(int layer, int neuron)
{
	if (m_Layers[layer][neuron].getWeights().size() == 0)
	{
		cout << "no weights" << endl << endl;
	}
	else
	{
		for (unsigned int k=0 ; k < m_Layers[layer][neuron].getWeights().size() ; k++)
		{
			cout << m_Layers[layer][neuron].getWeights()[k] << endl;
		}
		cout << endl;
	}
}

vector<double> NeuralNet::getDNA()
{
	vector<double> DNA;
	
	for (unsigned int i=1 ; i < m_Layers.size() ; i++)
	{
		for (unsigned int j=0 ; j < m_Layers[i].size() ; j++)
		{
			for (unsigned int k=0 ; k < m_Layers[i][j].getWeights().size() ; k++)
			{
				DNA.push_back(m_Layers[i][j].getWeights()[k]);
			}
		}
	}

	return DNA;
}

void NeuralNet::setDNA(vector<double> dna)
{
	int it = 0;
	for (unsigned int i=1 ; i < m_Layers.size() ; i++)
	{
		for (unsigned int j=0 ; j < m_Layers[i].size() ; j++)
		{
			for (unsigned int k=0 ; k < m_Layers[i][j].getWeights().size() ; k++)
			{
				m_Layers[i][j].m_Weights[k] = dna[it];
				it++;
			}
		}
	}
}

vector<double> NeuralNet::getNNOutputs()
{
	vector<double> outputs;

	for (unsigned int j=0 ; j<m_Layers[m_Layers.size()-1].size()-1 ; j++)
	{
		outputs.push_back( m_Layers[m_Layers.size()-1][j].getOutput() );
	}

	return outputs;
}


vector<double> NeuralNet::mixDNA(vector<double> dna1, vector<double> dna2, int cuts)
{
	/*int length = dna1.size();

	srand(time(0));
	int c = rand()%(length);
	int check= 0;
	vector<int> cut;
	vector<double> dna;


	cut.push_back(c);

	while (cut.size() != cuts)
	{
		c = rand()%(length);
		for (unsigned int k = 0 ; k < cut.size() ; k++){check += (c == cut[k]);}
		if (check != 0){cut.push_back(c);}
		check = 0;
	}

	int randParent = rand()%(2);

	if (randParent == 1)
	{
		for (unsigned int i = 0 ; i < length ; i++)
		{

			dna.push_back()
		}
	}

	else
	{

	}
	*/
	return dna1;
}

vector<double> NeuralNet::mutateDNA(vector<double> dna, double prob, double sigma)
{
	srand (time(0));
	double r;

	for (unsigned int i = 0 ; i<dna.size() ; i++)
	{
		r = (double)rand()/RAND_MAX;
		if (r < prob) {dna[i] = createWeight(dna[i], sigma);}
	}
	
	return dna;
}