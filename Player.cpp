#include "Player.h"

int Player::currentID = 0;

Player::Player(string n) : ID(++currentID)
{
	this->setName(n);
	this->score = 0;
}

Player::~Player()
{
}

void Player::setName(string n)
{
	this->name = n;
}

string Player::getName()
{
	return this->name;
}

int Player::getID()
{
	return this->ID;
}

void Player::addTextureToPlayer(string textureID)
{
	this->playerTextures.push_back(textureID);
}

string Player::getPlayerTexture(int numberID)
{
	return this->playerTextures[numberID];
}

void Player::updateScore(int change)
{
	this->score += change;
}
