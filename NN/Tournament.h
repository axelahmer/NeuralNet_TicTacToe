#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <vector>
#include "Population.h"


class Tournament
{
private:

Population m_Players;
vector<int> m_ScoringSystem;

public:

	Tournament(Population pop);
	void setScoringSystem(int win, int loss, int draw);
	void playRoundRobin();
	Population getPop();
	void setPlayers(Population pop);



};

#endif