#pragma once

#include "SharedInfo.h"
#include "Button.h"
#include "PlayingCards.h"
#include "PlayerPlayField.h"

class GameBoard
{
public:

	GameBoard(vector<PlayerPlayField> pFields, PlayingCards deck);
	~GameBoard();
	friend class GameRound;
	void sitPlayers(); // positions the playerPlayFields, according to the number of players
	void setTitle(string title);
	void setPlayerPos(int playerID, double x, double y);
	void setStartButtonCoordinates(double x, double y);
	void setScoreButtonCoords(double x, double y);
	void setSettingsButtonCoords(double x, double y);
	string getTitle();
	Coords getPlayerPos(int playerID);
	Coords getStartButtonCoords();
	Coords getScoreButtonCoords();
	Coords getSettingsButtonCoords();
	PlayingCards dealersDeck;


private: 

	int sittedPlayers;
	string titleField; // round number during started game
	vector<PlayerPlayField> playerFields;
	vector<Coords> playersPos; // stores deck coordinates for every player inserted
	vector<Coords> playFieldZones;
	Coords startButtonCoordinates; // saves startButtonCoordinates position on the screen
	Coords scoreButtonCoordinates; // saves scoreButtonCoordinates position on the screen
	Coords settingsButtonCoordinates; // saves settingsButtonCoordinates position on the screen
	vector<Button> playerPlayACardButton;
};