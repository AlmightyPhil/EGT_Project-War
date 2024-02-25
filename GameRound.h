#pragma once

#include <string>
#include <map>

#include "GameBoard.h"

class GameRound
{

public:

	GameRound(GameBoard gameBoard);
	~GameRound();
	void updateGameState(int state);
	void resoveWar(); // could take vector<PlayerPlayField> playerFields from GameBoard and work with them
	void updateScore();
	void getPower(string cardID);
	bool allActivePlayersPlayed();
	void playACardButtonHandler(PlayerPlayField);
	GameBoard gameBoard;
	void changeStartedState();
	//void changeGameState(int);

private:

	void setPowers(); // links the IDs of the cards(string) with their respective power level
	int gameState;
	bool isStarted = 0;
	int activePlayers = 3; // could be an array of ints, storing player IDs, to be able to help when there is "war" between 2 players
	string playACardButton; // ID към текстура в TextureManager
	map<string, int> cardPowers; // stores the IDs of the cards(string) mapped to their according power count
	queue<string> playedCards;

};