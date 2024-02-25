#include <iostream>
#include <algorithm>    // std::shuffle

#include "PlayingCards.h"

PlayingCards::PlayingCards()
{
	this->formDeck();
}

void PlayingCards::formDeck()
{
	for (int i = 0; i < suit.size(); i++)
	{
		for (int k = 0; k < type.size(); k++)
		{
			string temp = this->type[k] + " " + this->suit[i];
			this->deck.push(temp);
		}
	}
}

void PlayingCards::showDeck()
{
	stack<string> temp = this->deck;

	for (int i = 0; i < deck.size(); i++)
	{
		cout << temp.top() << endl;
		temp.pop();
	}
}

void PlayingCards::shuffle()
{
	vector<string> temp;
	int size = deck.size();

	for (int i = 0; i < size; i++)
	{
		temp.push_back(deck.top());
		deck.pop();
	}

	random_shuffle(temp.begin(), temp.end());

	for (int i = 0; i < temp.size(); i++)
	{
		deck.push(temp[i]);
	}
}

string PlayingCards::getTopCard()
{
	string temp;
	temp = deck.top();
	deck.pop();

	return temp;
}
