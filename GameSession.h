#pragma once

#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <map>

#include "Button.h"
#include "TextureManager.h"
#include "GameBoard.h"
#include "GameRound.h"

class GameSession
{

public:

	GameSession(GameRound gr);
	~GameSession();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	bool isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown, int xUp, int yUp);
	//Button isClickableButtonClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown, int xUp, int yUp);

private:

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	int currentFrame;
	SDL_Texture* clickableTexture;
	SDL_Rect clickableRect;
	int mouseDownX;
	int mouseDownY;
	GameRound gameRound;

};