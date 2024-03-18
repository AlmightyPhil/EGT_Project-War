#include "GameRound.h"

GameRound::GameRound(GameBoard gameBoard) : gameBoard(gameBoard)
{
	this->setPowers();
	this->gameState = 0;
	this->activePlayers = this->gameBoard.playerFields.size(); // could be this->gameBoard.getSittedPlayers()

	this->currentPlayedCards.clear();
	this->playedCardsPowers.clear();
	this->activePlayersVector.clear();
	this->playersScores.clear();


	for (int i = 0; i < this->activePlayers; i++)
	{
		
		this->currentPlayedCards.push_back(" ");
		this->playedCardsPowers.push_back(0);
		this->activePlayersVector.push_back(1);
		this->playersScores.push_back(0);
	}

}

GameRound::~GameRound()
{
}

int GameRound::getPower(string cardID)
{
	//*
	map<string, int>::iterator it;
	it = this->cardPowers.find(cardID);

	int temp = 0;

	if (it != cardPowers.end())
	{
		temp = it->second;
	}
	//*/

	//int temp = this->cardPowers.find(cardID)->second;
	//cout << "Card power is: " << temp << endl;
	return temp;
}

void GameRound::updateGameState(int state)
{
	switch (state)
	{
	case 0:
		cout << "Waiting for game start.. " << endl;
		// cout << this->started << endl;

		/*
		if (this->started == 1)
		{
			this->gameState = 1;
			this->changeStartedState();
			this->gameBoard.setStartButtonVisibility(0);
		}

		updateGameState(this->gameState);
		*/
		break;
	case 1:
		cout << "Dealing cards.." << endl;

		if (this->started == 1 && this->gameState == 1)
		{

			// Test block
            /*

			this->gameBoard.playerFields[0].placeCardInDeck("A Spades");
			this->gameBoard.playerFields[1].placeCardInDeck("A Clubs");
			this->gameBoard.playerFields[2].placeCardInDeck("A Hearts");

			this->gameBoard.playerFields[0].placeCardInDeck("A Spades");
			this->gameBoard.playerFields[1].placeCardInDeck("K Clubs");
			this->gameBoard.playerFields[2].placeCardInDeck("A Hearts");

			this->gameBoard.playerFields[0].placeCardInDeck("6 Spades");
			this->gameBoard.playerFields[1].placeCardInDeck("4 Clubs");
			this->gameBoard.playerFields[2].placeCardInDeck("6 Hearts");

            //this->gameBoard.playerFields[0].placeCardInDeck("J Spades");
			this->gameBoard.playerFields[1].placeCardInDeck("9 Clubs");
            this->gameBoard.playerFields[2].placeCardInDeck("7 Hearts");

			//*/

			this->gameBoard.dealersDeck.shuffle();

			// Deal Cards
            //*
            int numOfCardsToDealPerPlayer = 4;

            for (int i = 0; i < numOfCardsToDealPerPlayer; i++)
			{
				for (int k = 0; k < this->activePlayers; k++)
				{
					this->gameBoard.playerFields[k].placeCardInDeck(this->gameBoard.dealersDeck.getTopCard());
				}
			}
			//*/

			this->gameState = 2;
			this->updateGameState(2);
		}

		break;
	case 2:

		// Recalculate dead players
		this->deadPlayers = 0;

		if (this->started == 1 && this->gameState == 2)
		{

			for (int i = 0; i < this->gameBoard.getSittedPlayers(); i++)
			{
				if (this->activePlayersVector[i] == 0 && !inWar() && this->gameBoard.playerFields[i].getDeckCount() == 0)
				{
					this->deadPlayers++;
				}
			}

			// If only one person is alive -> declare him winner and move to state 8
			if (this->deadPlayers == this->gameBoard.getSittedPlayers() - 1)
			{
				cout << "We have a winner!" << endl;
				this->setGameState(8);
				this->updateGameState(this->getGameState());
				break;
			}

		}
		cout << "Waiting all players to play a card.. " << endl;
		if (this->started == 1 && this->gameState == 2)
		{
			for ( int i = 0; i < this->gameBoard.getSittedPlayers(); i++)
			{
				//*
				if (this->gameBoard.playerFields[i].getDeckCount() == 0 && this->playedCards.empty() && warFlag == 0)
				{
					this->gameBoard.playerFields[i].setPlayACardButtonActiveState(0);
				}
				else
				{
					this->gameBoard.playerFields[i].setPlayACardButtonActiveState(this->activePlayersVector[i]);
				}
				//*/
			}
		}
		break;
	case 3:
		cout << "Deciding who takes.." << endl;
		if (this->started == 1 && this->gameState == 3)
		{

			for (int i = 0; i < this->gameBoard.getSittedPlayers(); i++)
			{
				int temp = this->getPower(this->currentPlayedCards[i]);
				// cout << i << " player has value: " << temp << endl;
				this->playedCardsPowers[i] = temp;
			}

			if (this->playedPlayers == 2 && this->activePlayers == 0)
			{
				int cPower1 = this->playedCardsPowers[0];
				int cPower2 = this->playedCardsPowers[1];
				int cPower3 = this->playedCardsPowers[2];

				if (this->activePlayersVector[0] == 1 && this->activePlayersVector[1] == 1)
				{
					cout << "Resolving war between player 1 and player 2.." << endl;

					if (cPower1 > cPower2)
					{
						cout << "Player 1 takes.." << endl;

						this->warFlag = 0;
						this->givePlayedCards(1);
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(111);
						this->gameState = 2;
						this->updateGameState(2);
						//break;

					}
					else if(cPower1 < cPower2)
					{
						cout << "Player 2 takes.." << endl;

						this->warFlag = 0;
						this->givePlayedCards(2);
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(111);
						this->gameState = 2;
						this->updateGameState(2);
						//break;
					}
					else if(cPower1 == cPower2)
					{
                        if (this->warFlag)
                        {
                            cout << "The war between player 1 and player 2 keeps taking victims.." << endl;
                        }
                        else
                        {
                            cout << "A new conflict between player 1 and player 2 arises!" << endl;
                        }

						this->warFlag = 1;
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(110);
						this->gameState = 2;
						this->updateGameState(2);

					}
					break;

                }
                else if (this->activePlayersVector[0] == 1 && this->activePlayersVector[2] == 1)
				{
					cout << "Resolving war between player 1 and player 3.." << endl;

					if (cPower1 > cPower3)
					{
						cout << "Player 1 takes.." << endl;

						this->warFlag = 0;
						this->givePlayedCards(1);
						this->clearPlayedCardsFromPlayField();
						// this->calculateOutcome();
						this->setActivePlayers(111);
						this->gameState = 2;
						this->updateGameState(2);
					}
					else if (cPower1 < cPower3)
					{
						cout << "Player 3 takes.." << endl;

						this->warFlag = 0;
						this->givePlayedCards(3);
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(111);
						this->gameState = 2;
						this->updateGameState(2);
					}
					else if (cPower1 == cPower3)
					{
                        if (this->warFlag)
                        {
                            cout << "The war between player 1 and player 3 keeps taking victims.." << endl;
                        }
                        else
                        {
                            cout << "A new conflict between player 1 and player 3 arises!" << endl;
                        }

						this->warFlag = 1;
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(101);
						this->gameState = 2;
						this->updateGameState(2);
					}
					break;
                }
                else if (this->activePlayersVector[1] == 1 && this->activePlayersVector[2] == 1)
				{
					cout << "Resolving war between player 2 and player 3.." << endl;

					if (cPower2 > cPower3)
					{
						cout << "Player 2 takes.." << endl;

						this->warFlag = 0;
						this->givePlayedCards(2);
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(111);
						this->gameState = 2;
						this->updateGameState(2);
					}
					else if (cPower2 < cPower3)
					{
						cout << "Player 3 takes.." << endl;

						this->warFlag = 0;
						this->givePlayedCards(3);
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(111);
						this->gameState = 2;
						this->updateGameState(2);
					}
					else if (cPower2 == cPower3)
					{
                        if (this->warFlag)
                        {
                            cout << "The war between player 2 and player 3 keeps taking victims.." << endl;
                        }
                        else
                        {
                            cout << "A new conflict between player 2 and player 3 arises!" << endl;
                        }

						this->warFlag = 1;
						this->clearPlayedCardsFromPlayField();
						this->setActivePlayers(1011);
						this->gameState = 2;
						this->updateGameState(2);
					}
					break;
				}

			}

            else if (this->playedPlayers == 3 && this->activePlayers == 0)
			{
				//int highest = this->playedCardsPowers[0];

				int cPower1 = this->playedCardsPowers[0];
				int cPower2 = this->playedCardsPowers[1];
				int cPower3 = this->playedCardsPowers[2];

				if (cPower2 > cPower1 && cPower2 > cPower3)
				{
					cout << "Player 2 takes from first try.." << endl;					

					this->warFlag = 0;
					this->givePlayedCards(2);
					this->clearPlayedCardsFromPlayField();
                    this->setActivePlayers(1111111111);


					this->gameState = 2;
					this->updateGameState(2);
				}
				else if (cPower3 > cPower1 && cPower3 > cPower2)
				{
					cout << "Player 3 takes from first try.." << endl;

					this->warFlag = 0;
					this->givePlayedCards(3);
					this->clearPlayedCardsFromPlayField();
					this->setActivePlayers(111);

					this->gameState = 2;
					this->updateGameState(2);
				}
				else if (cPower1 > cPower2 && cPower1 > cPower3)
				{
					cout << "Player 1 takes from first try.." << endl;

					this->warFlag = 0;
					this->givePlayedCards(1);
					this->clearPlayedCardsFromPlayField();
					this->setActivePlayers(111);

					this->gameState = 2;
					this->updateGameState(2);
				}
				else if (cPower1 == cPower2 && cPower1 > cPower3)
				{
					cout << "War between player 1 and player 2!" << endl;

					this->warFlag = 1;
					this->clearPlayedCardsFromPlayField();
					this->setActivePlayers(110);
					this->gameState = 2;
					this->updateGameState(2);
					
				}
				else if (cPower1 == cPower3 && cPower1 > cPower2)
				{
					cout << "War between player 1 and player 3!" << endl;

					this->warFlag = 1;
					this->clearPlayedCardsFromPlayField();
					this->setActivePlayers(101);
					this->gameState = 2;
					this->updateGameState(2);

				}
				else if (cPower2 == cPower3 && cPower2 > cPower1)
				{
					cout << "War between player 2 and player 3!" << endl;

					this->warFlag = 1;
					this->clearPlayedCardsFromPlayField();
					this->setActivePlayers(1011);
					this->gameState = 2;
					this->updateGameState(2);

				}
				else if (cPower1 == cPower2 && cPower2 == cPower3)
				{
					cout << "Triple war!!!" << endl;

					this->warFlag = 1;
					this->clearPlayedCardsFromPlayField();
					this->setActivePlayers(111);	

					this->gameState = 2;
					this->updateGameState(this->gameState);

				}
			}

            else
            {
                   cout << "You broke the game, good job.." << endl;
            }
		}
		break;
	case 4:
		cout << "Waiting for a coffee.. " << endl;
		break;
	case 5:
		cout << "Waiting for a sandwitch.. " << endl;
		break;
	case 6:
		cout << "Waiting for a cigar.. " << endl;
		break;
	case 7:
		cout << "Cleaning Battlefield from the victims.. " << endl;

		this->gameState = 2;
		this->updateGameState(this->gameState);

		break;
	case 8:
		cout << "Game ended. Updating score.. " << endl;
		this->gameState = 0;
		this->started = 0; // very important to be before setActivePlayers
        this->setActivePlayers(111111);
		//*
		for (int i = 0; i < this->gameBoard.getSittedPlayers(); i++)
		{
			while (this->gameBoard.playerFields[i].getDeckCount() != 0)
			{
				this->gameBoard.dealersDeck.deck.push(this->gameBoard.playerFields[i].playTopCard());
			}
		}
		//*/

		//*
		this->currentPlayedCards.clear();
		this->playedCardsPowers.clear();
		this->activePlayersVector.clear();
		this->playersScores.clear();


		for (int i = 0; i < this->activePlayers; i++)
		{

			this->currentPlayedCards.push_back(" ");
			this->playedCardsPowers.push_back(0);
			this->activePlayersVector.push_back(1);
			this->playersScores.push_back(0);
		}
		//*/
		this->gameBoard.setStartButtonVisibility(1);
		updateGameState(this->gameState);
		break;
	default:
		cout << " Invalid Game State! " << endl;
	}
}

void GameRound::setGameState(int state)
{
	this->gameState = state;
}

void GameRound::setPowers()
{
	PlayingCards tempDeck = this->gameBoard.dealersDeck;

	for (int i = 1; i <= 4; i++)
	{	
		for (int k = 13; k > 0; k--)
		{
			string temp = tempDeck.getTopCard();
			//cout << endl << endl << endl << endl << temp << endl << endl;
			this->cardPowers.insert({ temp, k });
		}
	}
}



int GameRound::getGameState()
{
	return this->gameState;
}

void GameRound::changeStartedState()
{
	this->started = !this->started;
}

bool GameRound::isStarted()
{
	return this->started;
}

void GameRound::printCardPowersMap()
{
	cout << "KEY\tELEMENT\n";
	for (auto itr = this->cardPowers.begin(); itr != this->cardPowers.end(); ++itr) {
		cout << itr->first
			<< '\t' << itr->second << '\n';
	}
}

void GameRound::clearPlayedCardsFromPlayField()
{
	for (int i = 0; i < this->currentPlayedCards.size(); i++)
	{
		this->currentPlayedCards[i] = " ";
		this->playedCardsPowers[i] = 0;

	}
}

void GameRound::setActivePlayers(int activePlayersLine)
{
	this->activePlayers = 0;
	this->playedPlayers = 0;

	int tempLine = activePlayersLine;
	int i = 0;

	do
	{

        if (this->gameBoard.playerFields[this->activePlayersVector.size() - i - 1].getDeckCount() == 0 && !warFlag && this->isStarted())
		{
			this->activePlayersVector[this->activePlayersVector.size() - i - 1] = 0;

		}

		else
		{
			if (tempLine % 10 == 1) this->activePlayers++;
			this->activePlayersVector[this->activePlayersVector.size() - i - 1] = tempLine % 10;
		
		}
		
		i++;
		tempLine = tempLine / 10;

    } while (i < this->activePlayersVector.size());

}

void GameRound::givePlayedCards(int playerID)
{
	while (!this->playedCards.empty())
	{
		this->gameBoard.playerFields[playerID - 1].placeCardInDeck(this->playedCards.front());
		this->playedCards.pop();
	}
}

void GameRound::calculateOutcome()
{
	for (int i = 0; i < this->gameBoard.getSittedPlayers(); i++)
	{
	
		if (this->activePlayersVector[i] == 1 && this->gameBoard.playerFields[i].getDeckCount() == 0)
		{
			this->activePlayersVector[i] = 0;
			this->activePlayers -= 1;
		}

	}
}

bool GameRound::inWar()
{
	return this->warFlag;
}
