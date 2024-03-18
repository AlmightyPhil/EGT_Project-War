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
				TextureManager::Instance()->loadTexture("textures/cards/deckZoneTexture.png", "deckZone", renderer);
				TextureManager::Instance()->loadTexture("textures/startButton.jpg", "startButton", renderer);
				TextureManager::Instance()->loadTexture("textures/cards/cardBackTexture.jpg", "cardBack", renderer);
				TextureManager::Instance()->loadTexture("textures/activePlayACardButton.png", "activePlayACardButton", renderer);
				TextureManager::Instance()->loadTexture("textures/inactivePlayACardButton.png", "inactivePlayACardButton", renderer);

				stack<string> temp = this->gameRound.gameBoard.dealersDeck.deck;

				for (int i = 0; i < 52/*this->gameRound.gameBoard.dealersDeck.deck.size()*/; i++)
				{
					string texturePath = string("textures/cards/") + temp.top() + ".png";
					TextureManager::Instance()->loadTexture(texturePath.c_str(), temp.top(), renderer);
					temp.pop();
				}

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
	// int currentWindowWidth, currentWindowHeight;
	SDL_GetWindowSize(window, &currentWindowWidth, &currentWindowHeight);

	// change background color
	
	//*
	TextureManager::Instance()->drawTexture("gameBoard", 0, 0, currentWindowWidth, currentWindowHeight, renderer);

	if(this->gameRound.gameBoard.getStartButtonState())
	{
		TextureManager::Instance()->drawTexture("startButton", this->gameRound.gameBoard.getStartButtonCoords().x, this->gameRound.gameBoard.getStartButtonCoords().y, 100, 40, renderer);

		
	}


	int sittedPlayers = this->gameRound.gameBoard.getSittedPlayers();

	if (this->gameRound.getGameState() != 0)
	{
		for (int i = 1; i <= sittedPlayers; i++)
		{

			TextureManager::Instance()->drawTexture("deckZone", this->gameRound.gameBoard.getPlayerPos(i).x, this->gameRound.gameBoard.getPlayerPos(i).y, 82, 112, renderer);
			if (this->gameRound.gameBoard.getPlayerPlayField(i - 1).getDeckCount() != 0)
			{
				TextureManager::Instance()->drawTexture("cardBack", this->gameRound.gameBoard.getPlayerPos(i).x, this->gameRound.gameBoard.getPlayerPos(i).y, 82, 112, renderer);
			}
		}

	}

	if (this->gameRound.getGameState() >= 2)
	{
		int buttonPosX;
		int buttonPosY;

		for (int i = 1; i <= sittedPlayers; i++)
		{
			buttonPosX = this->gameRound.gameBoard.getPlayerPos(i).x + this->gameRound.gameBoard.getPlayerPlayField(i-1).getPlayACardButtonCoordOffset().x;
			buttonPosY = this->gameRound.gameBoard.getPlayerPos(i).y + this->gameRound.gameBoard.getPlayerPlayField(i-1).getPlayACardButtonCoordOffset().y;

			// cout << "x: " << buttonPosX << " y: " << buttonPosY << endl;
			if(this->gameRound.gameBoard.getPlayerPlayField(i-1).isPlayACardButtonActive())
			{
				TextureManager::Instance()->drawTexture("activePlayACardButton", buttonPosX, buttonPosY, 60, 30, renderer);
			}
			else
			{
				TextureManager::Instance()->drawTexture("inactivePlayACardButton", buttonPosX, buttonPosY, 60, 30, renderer);
			}
			if (this->gameRound.currentPlayedCards[i-1] != " ")
			{
				TextureManager::Instance()->drawTexture(this->gameRound.currentPlayedCards[i-1], this->gameRound.gameBoard.getPlayFieldZones(i).x, this->gameRound.gameBoard.getPlayFieldZones(i).y, 82, 112, renderer);
			}

		}	

	}


	//*/

	/*
	//SDL_RenderClear(renderer);
	//TextureManager::Instance()->drawOneFrameFromTexture("kaiba-talk", 0, 0, 124, 130, 1, currentFrame, renderer);
	//TextureManager::Instance()->drawOneFrameFromTexture("yugi-talk", 0, 0, 124, 260, 1, currentFrame, renderer);
	//*/

	// SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

// will be used only if I manage to add the extra functionality I have planned for on time
void GameSession::update()
{
	/*
	cout << "SDL_TICKS           : " << SDL_GetTicks() << "\n";
	cout << "SDL_TICKS / 100     : " << int(SDL_GetTicks() / 100) << "\n";
	cout << "SDL_TICKS / 100 % 10: " << int(((SDL_GetTicks() / 100) % 5)) << "\n\n";
	//*/
	currentFrame = int(((SDL_GetTicks() / 100) % 5)); // /300(lower - faster animation) and % 10 for 10 frames in the animation
	//currentRow = int((()));

	/*
	c++;
	if (c % 50 == 0)
	{
		destinationRectangle.x++;
		//sourceRectangle.x++;
	}
	//*/
}

void GameSession::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT: running = false; break;
		case SDL_MOUSEBUTTONDOWN:
		{
			/*int msx, msy;

			cout << "mouse button down\n";

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				cout << "left button down at: " << msx << " " << msy << endl;
			}*/
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
			// bool isStartButtonClicked = 0;

			int msx, msy;
			
			//cout << "mouse button up\n";

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				int sittedPlayers = this->gameRound.gameBoard.getSittedPlayers();

				//cout << this->gameRound.activePlayers << endl;
				//cout << this->gameRound.playedPlayers << endl;

				clickableTexture = TextureManager::Instance()->getTextureByID("startButton");
				clickableRect.x = this->gameRound.gameBoard.getStartButtonCoords().x;
				clickableRect.y = this->gameRound.gameBoard.getStartButtonCoords().y;
				//cout << (isClickableTextureClicked(clickableTexture, &clickableRect, mouseDownX, mouseDownY, msx, msy) ? "CLICKED\n" : "NOT CLICKED\n");
				if (isClickableTextureClicked(clickableTexture, &clickableRect, mouseDownX, mouseDownY, msx, msy))
				{
					if (this->gameRound.isStarted() == 0 && this->gameRound.getGameState() == 0)
					{
						// isStartButtonClicked = 1;
						this->gameRound.setGameState(1);
						this->gameRound.changeStartedState();
						this->gameRound.gameBoard.setStartButtonVisibility(0);
						this->gameRound.updateGameState(1);
					}
				}

				// if all active players have played -> go to game state 3
				if (this->gameRound.activePlayers == 0 && /*this->gameRound.playedPlayers == sittedPlayers &&*/ this->gameRound.getGameState() == 2)
				{
//					this->gameRound.setGameState(3);
//					this->gameRound.updateGameState(3);
				}


				else if(this->gameRound.getGameState() == 2)
				{
					for (int i = 1; i <= sittedPlayers; i++)
					{
						clickableTexture = TextureManager::Instance()->getTextureByID("activePlayACardButton");
						clickableRect.x = this->gameRound.gameBoard.getPlayerPos(i).x + this->gameRound.gameBoard.getPlayerPlayField(i - 1).getPlayACardButtonCoordOffset().x;
						clickableRect.y = this->gameRound.gameBoard.getPlayerPos(i).y + this->gameRound.gameBoard.getPlayerPlayField(i - 1).getPlayACardButtonCoordOffset().y;

						if (isClickableTextureClicked(clickableTexture, &clickableRect, mouseDownX, mouseDownY, msx, msy))
						{

							if (this->gameRound.isStarted() != 0 && this->gameRound.gameBoard.playerFields[i - 1].isPlayACardButtonActive())
							{
								if (this->gameRound.gameBoard.playerFields[i - 1].getDeckCount() == 0 && this->gameRound.inWar()) this->gameRound.gameBoard.playerFields[i-1].placeCardInDeck(this->gameRound.gameBoard.dealersDeck.getTopCard());
								
								// playTopCard and push to both board vectors
								string temp = this->gameRound.gameBoard.playerFields[i-1].playTopCard();
								this->gameRound.currentPlayedCards[i - 1] = temp;
								this->gameRound.playedCards.push(temp);

								this->gameRound.gameBoard.playerFields[i - 1].setPlayACardButtonActiveState(0); // .getPlayerPlayField(i - 1).setPlayACardButtonActiveState(false);
								this->gameRound.activePlayers -= 1;
								this->gameRound.playedPlayers += 1;

								SDL_Delay(200);

								if (this->gameRound.activePlayers == 0 && /*this->gameRound.playedPlayers == sittedPlayers &&*/ this->gameRound.getGameState() == 2)
								{
                                    cout << "All players have played! Right Mouse Click to continue..\n";
//                                    this->gameRound.setGameState(3);
//                                    this->gameRound.updateGameState(3);
								}
							}

						}

					}
				}



				//cout << (isClickableTextureClicked(clickableTexture, &clickableRect, mouseDownX, mouseDownY, msx, msy) ? "CLICKED\n" : "NOT CLICKED\n");
				//cout << "Coordinates x: " << msx << " Coordinates y: " << msy << "\n";

            }; /*break;*/

			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				SDL_GetMouseState(&msx, &msy);
				//cout << msx << " " << msy << "\n";

                if (this->gameRound.activePlayers == 0 && /*this->gameRound.playedPlayers == sittedPlayers &&*/ this->gameRound.getGameState() == 2)
                {
                    this->gameRound.setGameState(3);
                    this->gameRound.updateGameState(3);
                }
			}; break;

		};

		default: break;
		}

		//Handle window events
		this->handleWindowEvent(event);
	}
}

void GameSession::handleWindowEvent(SDL_Event& event)
{
		//Window event occured
		if (event.type == SDL_WINDOWEVENT)
		{
			//Caption update flag for moving mouse out/in screen, etc
			//bool updateCaption = false;

			switch (event.window.event)
			{
				//Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			{
				cout << "Window resized! " << endl;

				currentWindowWidth = event.window.data1;
				currentWindowHeight = event.window.data2;
				SDL_RenderPresent(renderer);

				//this->setStartButtonCoordinates(currentWindowWidth - 200, currentWindowHeight - 100);
				//this->setSettingsButtonCoords(currentWindowWidth - 50, currentWindowHeight - 50);
				//this->setScoreButtonCoords(currentWindowWidth - 100, currentWindowHeight - 50);
				this->gameRound.gameBoard.setStartButtonCoordinates(currentWindowWidth - 200, currentWindowHeight - 100);
				this->gameRound.gameBoard.setSettingsButtonCoords(currentWindowWidth - 50, currentWindowHeight - 50);
				this->gameRound.gameBoard.setScoreButtonCoords(currentWindowWidth - 100, currentWindowHeight - 50);

				this->gameRound.gameBoard.sitPlayers();

				/*
				for (int i = 1; i <= this->gameRound.gameBoard.getSittedPlayers(); i++)
				{
					//this->gameRound.gameBoard.setPlayerPos(i, );
					
				}
				//*/

				break;
			}
			default: break;
			}
		}

}

void GameSession::clean()
{
	cout << "cleaning game\n";

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
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

	//(r->x) (r->x + tw)
	//(r->y) (r->y + th)

	//if ((xDown > r->x && xDown < (r->x + tw)) && (xUp > r->x && xUp < (r->x + tw)) &&
	//	(yDown > r->y && yDown < (r->y + th)) && (yUp > r->y && yUp < (r->y + th)))
	if ((xDown > r->x && xDown < (r->x + tw)) && (xUp > r->x && xUp < (r->x + tw)) &&
		(yDown > r->y && yDown < (r->y + th)) && (yUp > r->y && yUp < (r->y + th)))
	{
		//click coordinates within texture location
		return true;
	}

	return false;
}
