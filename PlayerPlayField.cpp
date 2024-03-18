#include "PlayerPlayField.h"

PlayerPlayField::PlayerPlayField(Player p1) : player(p1)
{
	this->setDeckCounterFieldCoordOffset(25.0, 115.0);
	this->setPlayACardButtonCoordOffset(10.0, 20.0);	
	this->playButtonRect.w = 100;
	this->playButtonRect.h = 40;
	this->setPlayACardButtonActiveState(1);
}

PlayerPlayField::~PlayerPlayField()
{
}

void PlayerPlayField::placeCardInDeck(string card)
{
	this->playerDeck.push(card);
	this->deckCounter++;
}

string PlayerPlayField::playTopCard()
{
	string temp;
	temp = this->playerDeck.front();
	this->playerDeck.pop();
	this->deckCounter--;

	return temp;
}

void PlayerPlayField::showPlayerDeck()
{
	queue<string> temp = this->playerDeck;

	cout << this->player.getName() << " deck countains: " << endl;

	for (int i = 0; i < this->playerDeck.size(); i++)
	{
		
		cout << temp.front() << endl;
		temp.pop();
	}
}

void PlayerPlayField::emptyDeck()
{
	while (!this->playerDeck.empty())
	{
		this->playerDeck.pop();
	}
}

void PlayerPlayField::setPlayACardButtonCoordOffset(double x, double y)
{
	this->playACardButtonCoordOffset.x = x;
	this->playACardButtonCoordOffset.y = y;
}

void PlayerPlayField::setPlayACardButtonActiveState(bool state)
{
	this->playACardButtonActive = state;
}

void PlayerPlayField::setDeckCounterFieldCoordOffset(double x, double y)
{
	this->deckCounterFieldCoordOffset.x = x;
	this->deckCounterFieldCoordOffset.y = y;
}

int PlayerPlayField::getDeckCount()
{
	return this->deckCounter;
}

Coords PlayerPlayField::getPlayACardButtonCoordOffset()
{
	return this->playACardButtonCoordOffset;
}

bool PlayerPlayField::isPlayACardButtonActive()
{
	return this->playACardButtonActive;
}

Coords PlayerPlayField::getDeckCounterFieldCoordOffset()
{
	return this->deckCounterFieldCoordOffset;
}



SDL_Rect PlayerPlayField::getPlayButtonRect()
{
	//Coords tempCoords;
	//tempCoords.x = this->playButtonRect.x;
	//tempCoords.y = this->playButtonRect.y;

	//return tempCoords;
	return this->playButtonRect;
}
