#include "Tictactoe.h"
#include "NeuralNet.h"

Tictactoe::Tictactoe(NeuralNet* NN1, NeuralNet* NN2)
{
	board.assign(9,0);
	board2.assign(9,0);
	history.reserve(9);

	p1 = NN1;
	p2 = NN2;
}

Tictactoe::Tictactoe(NeuralNet* NN, string xo)
{
	board.assign(9,0);
	board2.assign(9,0);
	history.reserve(9);
	if (xo.at(0) == 'x'){p2 = NN;}
	else if (xo.at(0) == 'o'){p2 = NN;}


}

bool Tictactoe::winCheck()
{

	if (board[0]+board[1]+board[2] == 3 ||
		board[3]+board[4]+board[5] == 3 ||
		board[6]+board[7]+board[8] == 3 ||
		board[0]+board[3]+board[6] == 3 ||
		board[1]+board[4]+board[7] == 3 ||
		board[2]+board[8]+board[5] == 3 ||
		board[0]+board[4]+board[8] == 3 ||
		board[2]+board[4]+board[6] == 3  ) {return true;}

	else if (board[0]+board[1]+board[2] == -3 ||
		board[3]+board[4]+board[5] == -3 ||
		board[6]+board[7]+board[8] == -3 ||
		board[0]+board[3]+board[6] == -3 ||
		board[1]+board[4]+board[7] == -3 ||
		board[2]+board[8]+board[5] == -3 ||
		board[0]+board[4]+board[8] == -3 ||
		board[2]+board[4]+board[6] == -3  ) {return true;}

	else {return false;}
}

bool Tictactoe::drawCheck()
{
	if (history.size() == 9 && winCheck() == false) {return true;}
	else {return false;}
}

void Tictactoe::playGame()
{
	vector<double> decisions;
	bool inProgress = true;
	while (inProgress == true)
	{
		if (winCheck() == false && drawCheck() == false)
		{
			//cout << "player 1 moved" << endl;
			p1->setInputs(board);
			p1->calculateForward();
			decisions = p1->getNNOutputs();
			makeMove(decisions, 1);
		}

		if (winCheck() == false && drawCheck() == false)
		{
			//cout << "player 2 moved" << endl;

			updateBoard2();
			p2->setInputs(board2);
			p2->calculateForward();
			decisions = p2->getNNOutputs();
			makeMove(decisions, -1);
		}
		else {inProgress = false;}
	}

}

void Tictactoe::makeMove(vector<double> decisions, int pieceValue)
{
int moveIndex = 0;
double max = -1;
for (unsigned int i = 0; i < decisions.size(); i++)
	{
		if (max < decisions[i] && board[i] == 0)
		{
			
			max = decisions[i];
			moveIndex = i;

		}
	}

board[moveIndex] = pieceValue;
history.push_back(moveIndex);
}

int Tictactoe::getResult()
{
if (drawCheck() == true) {return 0;}

else if (board[0]+board[1]+board[2] == 3 ||
		board[3]+board[4]+board[5] == 3 ||
		board[6]+board[7]+board[8] == 3 ||
		board[0]+board[3]+board[6] == 3 ||
		board[1]+board[4]+board[7] == 3 ||
		board[2]+board[8]+board[5] == 3 ||
		board[0]+board[4]+board[8] == 3 ||
		board[2]+board[4]+board[6] == 3 ) {return 1;}

else if (board[0]+board[1]+board[2] == -3 ||
		board[3]+board[4]+board[5] == -3 ||
		board[6]+board[7]+board[8] == -3 ||
		board[0]+board[3]+board[6] == -3 ||
		board[1]+board[4]+board[7] == -3 ||
		board[2]+board[8]+board[5] == -3 ||
		board[0]+board[4]+board[8] == -3 ||
		board[2]+board[4]+board[6] == -3 ) {return -1;}

}


void Tictactoe::printBoard()
{
	cout << endl;
	for (unsigned int i = 0 ; i < board.size() ; i++)
	{cout << board[i] << endl;}
}

void Tictactoe::updateBoard2()
{
	for (unsigned int i = 0 ; i < board.size() ; i++)
	{
		board2[i] = board[i] * (-1);
	}
}

void Tictactoe::print2dBoard()
{
	string xo;
	for (int i = 0 ; i<9 ; i++)
	{
		if(board[i] == 1){xo.append("X");}
		else if(board[i] == -1){xo.append("O");}
		else {xo.append(" ");}
	}



	cout << "   |   |"														<< endl
		 << " " << xo[0] << " | " << xo[1] << " | " << xo[2]				<< endl
		 << "---+---+---"													<< endl
		 << " " << xo[3] << " | " << xo[4] << " | " << xo[5]				<< endl
		 << "---+---+---"													<< endl
		 << " " << xo[6] << " | " << xo[7] << " | " << xo[8]				<< endl
		 << "   |   |"														<< endl;
}

