#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "Player.h"

using namespace std;

class PlayingCards
{
public:

	PlayingCards();
	//~PlayingCards();
	void showDeck(); // помощна функция, не е нужна за заданието
	void shuffle();
	string getTopCard();
	stack<string> deck;

private:

	void formDeck();
	vector<string> type = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	vector<string> suit = { "Spades", "Diamonds", "Hearts", "Clubs" };
	
};