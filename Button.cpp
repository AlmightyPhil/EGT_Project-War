#include "Button.h"

Button::Button()
{
}

Button::Button(int screenOffsetPosX, int screenOffsetPosY, vector<string> textureIDList)
{
	buttonShape.x = screenOffsetPosX;
	buttonShape.y = screenOffsetPosY;
	this->isClicked = 0;
	this->isReleased = 0;
	this->isActive = 0;
}

Button::~Button()
{
}

void Button::onClick()
{

}

void Button::initShape(int startX, int startY, double width, double height)
{
	this->buttonShape.x = startX;
	this->buttonShape.y = startY;
	this->buttonShape.w = width;
	this->buttonShape.h = height;
}

