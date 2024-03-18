#pragma once

#include <string>
#include <map>

#include "GameBoard.h"

// enum CardPowers { two, three, four, five, six, seven, eight, nine, ten, J, Q, K, A };

class GameRound
{

public:

	GameRound(GameBoard gameBoard);
	~GameRound();
	void updateGameState(int state); // could be void switchGameState(int) and do set at the same time
	void setGameState(int state); // could be changeGameState
	void resoveWar(); // should take vector<PlayerPlayField> playerFields from GameBoard and work with them
	void updateScore();
	int getPower(string cardID);
	int getGameState();
	bool allActivePlayersPlayed();
	void playACardButtonHandler(PlayerPlayField);
	void changeStartedState();
	bool isStarted();
	void printCardPowersMap();
	void clearPlayedCardsFromPlayField();
	void setActivePlayers(int activePlayersLine);
	void givePlayedCards(int playerID);
	void calculateOutcome();
	bool inWar();
	GameBoard gameBoard;
	int activePlayers = 0; // could be an array of ints, storing player IDs, to be able to help when there is "war" between 2 players
	int playedPlayers = 0; // variable to help store how many of the active players already played a card
	queue<string> playedCards;
	vector<string> currentPlayedCards;
	vector<int> playedCardsPowers;
	vector<bool> activePlayersVector;

private:

	void setPowers(); // links the IDs of the cards(string) with their respective power level
	int gameState;
	bool started = 0;
	bool warFlag;
	int deadPlayers;
	//vector<bool> deadPlayersVector;
	vector<int> playersScores;
	vector<int> gameOverOrder; // could be just some activity check(inactive + not in war) only for the first time, then update score

	// string playACardButton; // ID към текстура в TextureManager
	map<string, int> cardPowers; // stores the IDs of the cards(string) mapped to their according power count


};