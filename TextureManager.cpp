#include "TextureManager.h"

bool TextureManager::loadTexture(const char* fileName, string id, SDL_Renderer* ren)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	if (tempSurface == 0) return false;

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (tex != 0)
	{
		textureMap[id] = tex;
		return true;

	}

	return false; // something went wrong
}

void TextureManager::drawTexture(string id, int x, int y, int width, int height,
	SDL_Renderer* ren, SDL_RendererFlip flip)
{
	//*
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	//*/

	// SDL_RenderCopyEx е почти като SDL_RenderCopy. Просто взима бонус параметри - ъгъл, център на въртене и флип флаг
	SDL_RenderCopyEx(ren, textureMap[id], NULL, &destRect, 0, 0, flip); // NULL instead of &srcRect to fit on screen

}

void TextureManager::drawOneFrameFromTexture(string id, int x, int y, int width, int height,
	int currentRow, int currentFrame, SDL_Renderer* ren, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(ren, textureMap[id], &srcRect, &destRect/*&srcRect*/, 0, 0, flip);
}

SDL_Texture* TextureManager::getTextureByID(string ID)
{
	SDL_Texture* temp = this->textureMap.find(ID)->second;
	return temp;
}

TextureManager* TextureManager::instance = 0;