#pragma once

#include <queue>
#include <SDL.h>
#include "Player.h"
#include "Coords.h"

class PlayerPlayField // links the player to his playing deck and positions the rest of the interface according to the deck position
{

public:

	PlayerPlayField(Player p1);
	~PlayerPlayField();
	void placeCardInDeck(string card); // will be used both when cards are being dealt at start and when winning a simple battle
	string playTopCard();
	void showPlayerDeck(); // helping mehtod that is not in the task
	void setPlayACardButtonCoordOffset(double x, double y);
	void setDeckCounterFieldCoordOffset(double x, double y);
	int getDeckCount();
	Coords getPlayACardButtonCoordOffset();
	Coords getDeckCounterFieldCoordOffset();
	SDL_Rect getPlayButtonRect();

private:

	Player player;
	queue<string> playerDeck;
	int deckCounter = 0;
	Coords playACardButtonCoordOffset;// saves how many pixels is the offset from the positon of the deck
	SDL_Rect playButtonRect;
	Coords deckCounterFieldCoordOffset;

};