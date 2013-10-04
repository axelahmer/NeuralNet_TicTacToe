#include "Tournament.h"
#include "Tictactoe.h"
#include <vector>
#include <cmath>



Tournament::Tournament(Population pop)
{
	m_Players = pop;
	m_ScoringSystem.reserve(3);
}


void Tournament::setPlayers(Population pop)
{
	m_Players = pop;
}

void Tournament::setScoringSystem(int win, int loss, int draw)
{
	m_ScoringSystem.push_back(win);
	m_ScoringSystem.push_back(loss);
	m_ScoringSystem.push_back(draw);
}

void Tournament::playRoundRobin()
{
	vector<Player*> A;
	vector<Player*> B;
	int popSize = m_Players.getSize();
	int cut = m_Players.getSize()/2;
	int result;

	vector<Player> Pop = m_Players.getPop();

	for (int k = 0 ; k < cut ; k++)
	{

		A.push_back(&Pop[k]);
		B.push_back(&Pop[popSize-k-1]);

	}
	
	int rounds = popSize - 1;

	for (int r = 0 ; r < rounds ; r++)
	{
		//cout << "round: " << r+1 << " / " << rounds << endl;
		for (int i = 0 ; i < cut ; i++)
		{
			Tictactoe TTT(&(*A[i]).NN, &(*B[i]).NN);
			TTT.playGame();
			result = TTT.getResult();
			if (result == 1)		{(*A[i]).score += m_ScoringSystem[0]; (*B[i]).score += m_ScoringSystem[1]; }
			else if (result == -1)	{(*A[i]).score += m_ScoringSystem[1]; (*B[i]).score += m_ScoringSystem[0]; }
			else					{(*A[i]).score += m_ScoringSystem[2]; (*B[i]).score += m_ScoringSystem[2];}
		}

		A.insert(A.begin()+1,1,B[0]); 
		B.erase(B.begin());
		B.push_back(A[A.size()-1]);
		A.pop_back();

	}

	m_Players.setPop(Pop);
}

Population Tournament::getPop()
{
	return m_Players;
}