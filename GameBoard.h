#pragma once

#include "SharedInfo.h"
#include "Button.h"
#include "PlayingCards.h"
#include "PlayerPlayField.h"

//using namespace std;

class GameBoard
{
public:

	GameBoard(vector<PlayerPlayField> pFields, PlayingCards deck);
	~GameBoard();
	friend class GameRound;
	void sitPlayers(); // positions the playerPlayFields, according to the number of players // might add argument and might need to be moved to game session
	void setTitle(string title);
	void setPlayerPos(int playerID, double x, double y);
	void setStartButtonCoordinates(double x, double y);
	void setStartButtonVisibility(bool value);
	void setScoreButtonCoords(double x, double y);
	void setSettingsButtonCoords(double x, double y);
	int getSittedPlayers();
	string getTitle();
	PlayerPlayField getPlayerPlayField(int index);
	Coords getPlayerPos(int playerID);
	Coords getPlayFieldZones(int playerID);
	Coords getStartButtonCoords();
	bool getStartButtonState();
	Coords getScoreButtonCoords();
	Coords getSettingsButtonCoords();
	PlayingCards dealersDeck;
	vector<PlayerPlayField> playerFields;

private: 

	// might need to know/store the coords of the rectangles of the played on the board cards
	int sittedPlayers;
	string titleField; // round number during started game

	vector<Coords> playersPos; // stores deck coordinates for every player inserted
	vector<Coords> playFieldZones;
	Coords startButtonCoordinates; // saves startButtonCoordinates position on the screen
	bool startButtonVisible;
	Coords scoreButtonCoordinates; // saves scoreButtonCoordinates position on the screen
	Coords settingsButtonCoordinates; // saves settingsButtonCoordinates position on the screen
	vector<Button> playerPlayACardButton;
};