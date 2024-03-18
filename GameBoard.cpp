#include "GameBoard.h"

GameBoard::GameBoard(vector<PlayerPlayField> pFields, PlayingCards deck) : playerFields(pFields), dealersDeck(deck), titleField("War!")
{
	//cout << this->playerFields.size();
	sittedPlayers = pFields.size();
	
	for (int i = 0; i < sittedPlayers; i++)
	{
		Coords temp = { 0.0, 0.0 };
		Button *tempButton = new Button();
		playersPos.push_back(temp);
		playFieldZones.push_back(temp);
		playerPlayACardButton.push_back(*tempButton);
	}

	this->setStartButtonCoordinates(currentWindowWidth - 200, currentWindowHeight - 100);
	this->startButtonVisible = 1;
	this->setSettingsButtonCoords(currentWindowWidth - 50, currentWindowHeight - 50);
	this->setScoreButtonCoords(currentWindowWidth - 100, currentWindowHeight - 50);
	
	this->sitPlayers();
}

GameBoard::~GameBoard()
{
}

void GameBoard::sitPlayers()
{
	switch(sittedPlayers)
	{
	case 1:
		cout << "Can not play solo! " << endl;
		break;
	case 2:
		cout << "Positioning two players.. " << endl;
		break;
	case 3:
		cout << "Positioning three players.. " << endl;

		playersPos[0].x = 50;
		playersPos[0].y = currentWindowHeight / 2 - 55 /* -40 if gonna be flipped 90 degrees */;
		playerFields[0].setDeckCounterFieldCoordOffset(25.0, 115.0);
		playerFields[0].setPlayACardButtonCoordOffset(10.0, 20.0);
		playFieldZones[0].x = currentWindowWidth / 2 - 40 - 10 - 80;
		playFieldZones[0].y = currentWindowHeight / 2 - 55;
		playerPlayACardButton[0].initShape(playersPos[0].x + this->playerFields[0].getPlayACardButtonCoordOffset().x,
											playersPos[0].y + this->playerFields[0].getPlayACardButtonCoordOffset().y, 
											this->playerFields[0].getPlayButtonRect().w, 
											this->playerFields[0].getPlayButtonRect().h);

		playersPos[1].x = currentWindowWidth / 2 - 40;
		playersPos[1].y = currentWindowHeight - 160;
		playerFields[1].setDeckCounterFieldCoordOffset(25.0, 115.0);
		playerFields[1].setPlayACardButtonCoordOffset(10.0, 20.0);
		playFieldZones[1].x = currentWindowWidth / 2 - 40;
		playFieldZones[1].y = currentWindowHeight / 2 - 55;
		playerPlayACardButton[1].initShape(playersPos[1].x + this->playerFields[1].getPlayACardButtonCoordOffset().x,
											playersPos[1].y + this->playerFields[1].getPlayACardButtonCoordOffset().y,
											this->playerFields[1].getPlayButtonRect().w,
											this->playerFields[1].getPlayButtonRect().h);


		playersPos[2].x = currentWindowWidth - 50 - 80 /* - 100 if flipped horizontally */;
		playersPos[2].y = currentWindowHeight / 2 - 55;
		playerFields[2].setDeckCounterFieldCoordOffset(25.0, 115.0);
		playerFields[2].setPlayACardButtonCoordOffset(10.0, 20.0);
		playFieldZones[2].x = currentWindowWidth / 2 + 40 + 10;
		playFieldZones[2].y = currentWindowHeight / 2 - 55;
		playerPlayACardButton[2].initShape(playersPos[2].x + this->playerFields[2].getPlayACardButtonCoordOffset().x,
											playersPos[2].y + this->playerFields[2].getPlayACardButtonCoordOffset().y,
											this->playerFields[2].getPlayButtonRect().w,
											this->playerFields[2].getPlayButtonRect().h);

		break;
	case 4:
		cout << "Positioning four players.. " << endl;
		break;
	case 5:
		cout << "Positioning five players.. " << endl;
		break;
	case 6:
		cout << "Positioning six players.. " << endl;
		break;
	default:
		cout << "Waiting for more players.. " << endl;
	}
}

void GameBoard::setTitle(string title)
{
	this->titleField = title;
}

void GameBoard::setPlayerPos(int playerID, double x, double y)
{
	this->playersPos[playerID - 1].x = x;
	this->playersPos[playerID - 1].y = y;
}

void GameBoard::setStartButtonCoordinates(double x, double y)
{
	this->startButtonCoordinates.x = x;
	this->startButtonCoordinates.y = y;
}

void GameBoard::setStartButtonVisibility(bool value)
{
	this->startButtonVisible = value;
}

void GameBoard::setScoreButtonCoords(double x, double y)
{
	this->scoreButtonCoordinates.x = x;
	this->scoreButtonCoordinates.y = y;
}

void GameBoard::setSettingsButtonCoords(double x, double y)
{
	this->settingsButtonCoordinates.x = x;
	this->settingsButtonCoordinates.y = y;
}

int GameBoard::getSittedPlayers()
{
	return this->sittedPlayers;
}

string GameBoard::getTitle()
{
	return this->titleField;
}

PlayerPlayField GameBoard::getPlayerPlayField(int index)
{
	return this->playerFields[index];
}

Coords GameBoard::getPlayerPos(int playerID)
{
	return this->playersPos[playerID - 1];
}

Coords GameBoard::getPlayFieldZones(int playerID)
{
	return this->playFieldZones[playerID-1];
}

Coords GameBoard::getStartButtonCoords()
{
	return this->startButtonCoordinates;
}

bool GameBoard::getStartButtonState()
{
	return this->startButtonVisible;
}

Coords GameBoard::getScoreButtonCoords()
{
	return this->scoreButtonCoordinates;
}

Coords GameBoard::getSettingsButtonCoords()
{
	return this->settingsButtonCoordinates;
}
