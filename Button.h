#pragma once

#include <string>
#include <vector>

#include <SDL.h>

using namespace std;

enum ButtonState { ACTIVE=0, INACTIVE=1, HOVER=2, PRESSED=3}; // normal state?

class Button
{
public:

	Button();
	Button(int screenOffsetPosX, int screenOffsetPosY, vector<string> textureIDList); // might need some way to interact with some kind of behaviour
	~Button();
	void onClick();
	void initShape(int startX, int startY, double width, double height);

private:

	SDL_Rect buttonShape;
	bool isClicked;
	bool isReleased;
	bool isActive;
	vector<string> textureIDList;

};