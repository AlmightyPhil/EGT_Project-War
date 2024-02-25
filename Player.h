#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player
{
public:

	Player(string n);
	~Player();
	void setName(string n);
	string getName();
	int getID();
	void addTextureToPlayer(string textureID);
	string getPlayerTexture(int numberID);
	void updateScore(int change);

private:

	string name;
	const int ID;
	static int currentID;
	vector<string> playerTextures;
	int score;

};