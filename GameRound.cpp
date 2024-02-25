#include "GameRound.h"

GameRound::GameRound(GameBoard gameBoard) : gameBoard(gameBoard)
{
	this->setPowers();
	this->gameState = 0;

}

GameRound::~GameRound()
{
}

void GameRound::updateGameState(int state)
{
	switch (state)
	{
	case 0:
		cout << " State: waiting for game start.. " << endl;
		cout << this->isStarted << endl;
		if (this->isStarted == 1)
		{
			this->gameState = 1;
			updateGameState(this->gameState);
		}
		break;
	case 1:
		cout << " Waiting all players to play a card " << endl;
		break;
	case 2:
		cout << " Waiting war between player 1 and 2 to be resolved " << endl;
		break;
	case 3:
		cout << " Waiting war between player 1 and 3 to be resolved " << endl;
		break;
	case 4:
		cout << " Waiting war between player 2 and 3 to be resolved " << endl;
		break;
	case 5:
		cout << " Waiting war between player 1, 2 and 3 to be resolved " << endl;
		break;
	case 6:
		cout << " Game ended. Updating score.. " << endl;
		this->gameState = 0;
		break;
	default:
		cout << " Invalid Game State! " << endl;
	}
}

void GameRound::setPowers()
{
	for (int i = 1; i <= 4; i++)
	{	
		for (int k = 13; k > 0; k--)
		{
			string temp = gameBoard.dealersDeck.getTopCard();
			cout << endl << endl << endl << endl << temp << endl << endl;
			cardPowers.insert({ temp, k });
		}
	}
}

void GameRound::getPower(string cardID)
{
	int temp = cardPowers.find(cardID)->second;
	cout << temp << endl;
}

void GameRound::changeStartedState()
{
	this->isStarted = 1;
}
