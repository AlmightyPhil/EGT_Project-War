#include "SharedInfo.h"
#include "GameSession.h"

GameSession::GameSession(GameRound gr) : gameRound(gr)
{
	GameSession::window = NULL;
	GameSession::renderer = NULL;
	GameSession::running = true;
	GameSession::currentFrame = 0;
	//GameSession::sourceRectangle = NULL;
	//GameSession::destinationRectangle = NULL;
}

GameSession::~GameSession()
{
}

bool GameSession::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "STD init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window != 0) // window init success
		{
			cout << "window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0) // renderer init success
			{
				cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 15, 109, 0, 255);

				TextureManager::Instance()->loadTexture("textures/background.jpg", "gameBoard", renderer);
				TextureManager::Instance()->loadTexture("textures/startButton.jpg", "startButton", renderer);
				TextureManager::Instance()->loadTexture("textures/activePlayACardButton.png", "activePlayACardButton", renderer);
				TextureManager::Instance()->loadTexture("textures/inactivePlayACardButton.png", "inactivePlayACardButton", renderer);
			}
			else
			{
				cout << "renderer init failed\n";
				return false;
			}
		}
		else
		{
			cout << "window init failed\n";
			return false;
		}
	}
	else
	{
		cout << "STD init fail\n";
		return false;
	}

	cout << "init success\n";
	running = true;
	return true;

}

void GameSession::render()
{

	SDL_GetWindowSize(window, &currentWindowWidth, &currentWindowHeight);

	SDL_RenderClear(renderer);
	TextureManager::Instance()->drawTexture("gameBoard", 0, 0, currentWindowWidth, currentWindowHeight, renderer);

	TextureManager::Instance()->drawTexture("startButton", this->gameRound.gameBoard.getStartButtonCoords().x, this->gameRound.gameBoard.getStartButtonCoords().y, 100, 40, renderer);

	SDL_RenderPresent(renderer);
}

// will be used only if I manage to add the extra functionality I have planned for on time
void GameSession::update()
{
	currentFrame = int(((SDL_GetTicks() / 100) % 5)); // /300(lower - faster animation) and % 10 for 10 frames in the animation

}

void GameSession::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: running = false; break;
		case SDL_MOUSEBUTTONDOWN:
		{
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				mouseDownX = msx;
				mouseDownY = msy;

			}
		}; break;
		case SDL_MOUSEBUTTONUP:
		{
			bool isStartButtonClicked = 0;

			int msx, msy;
			cout << "mouse button up\n";

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);

				clickableTexture = TextureManager::Instance()->getTextureByID("startButton");
				clickableRect.x = this->gameRound.gameBoard.getStartButtonCoords().x;
				clickableRect.y = this->gameRound.gameBoard.getStartButtonCoords().y;
				if (isClickableTextureClicked(clickableTexture, &clickableRect, mouseDownX, mouseDownY, msx, msy))
				{
					isStartButtonClicked = 1;
					//this->gameRound.changeStartedState();
					this->gameRound.updateGameState(isStartButtonClicked);
				}

			}; break;

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				SDL_GetMouseState(&msx, &msy);
			}; break;

		};

		default: break;
		}
	}
}

void GameSession::clean()
{
	cout << "cleaning game\n";

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool GameSession::isRunning()
{
	return GameSession::running;
}

bool GameSession::isClickableTextureClicked(SDL_Texture* t, SDL_Rect* r, int xDown, int yDown, int xUp, int yUp)
{
	int tw, th;
	SDL_QueryTexture(t, 0, 0, &tw, &th);

	if ((xDown > r->x && xDown < (r->x + tw)) && (xUp > r->x && xUp < (r->x + tw)) &&
		(yDown > r->y && yDown < (r->y + th)) && (yUp > r->y && yUp < (r->y + th)))
	{
		//click coordinates within texture location
		return true;
	}

	return false;
}