#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <map>
#include "GameSession.h"

using namespace std;

class TextureManager
{
public:
	bool loadTexture(const char* fileName, string id, SDL_Renderer* ren);
	void drawTexture(string id, int x, int y, int width, int height, // x, y can be changed with the point struct
		SDL_Renderer* ren, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawOneFrameFromTexture(string id, int x, int y, int width, int height, // x, y can be changed with the point struct
		int currentRow, int currentFrame, SDL_Renderer* ren, SDL_RendererFlip flip = SDL_FLIP_NONE);
	SDL_Texture* getTextureByID(string ID);


	static TextureManager* Instance()
	{
		if (instance == 0)
		{
			instance = new TextureManager();
			return instance;
		}

		return instance;
	}

private:

	map<string, SDL_Texture*> textureMap;
	TextureManager() {}
	static TextureManager* instance;

};
