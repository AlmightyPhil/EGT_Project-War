// SDL_ProjectWar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//#include "Windows.h" // for Sleep()
#include "SharedInfo.h"
#include "PlayingCards.h"
#include "Player.h"
#include "PlayerPlayField.h"
#include "GameBoard.h"
#include "GameRound.h"
#include "GameSession.h"



GameSession* game = NULL;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;

int currentWindowWidth = WINDOW_WIDTH;
int currentWindowHeight = WINDOW_HEIGHT;
int playerOneTotalScore = 0;
int playerTwoTotalScore = 0;
int playerThreeTotalScore = 0;

int main(int argc, char* argv[])
{
    srand(time(0));

    // Testing PlayingCards
    //*

    PlayingCards pc1;

    //pc1.showDeck();
    //pc1.shuffle();
    cout << endl << endl;
    //pc1.showDeck();
    //cout << endl << endl;
    
    // Sleep(3000);
    //pc1.shuffle();
    //cout << endl << endl;
    //pc1.showDeck();

    //cout << endl << endl;
    //cout << pc1.getTopCard();
    //cout << "\nNew Deck:" << endl;
    //pc1.showDeck();

    //*/

    // Testing Player and PlayerPlayField
    //*

    Player p1("Kaiba");
    //cout << p1.getID() << endl << endl;

    Player p2("Yugi");
    //cout << p2.getID() << endl << endl;

    Player p3("Joey");
    //cout << p3.getID() << endl << endl;

    PlayerPlayField field1(p1);
    PlayerPlayField field2(p2);
    PlayerPlayField field3(p3);

    /*
    field1.placeCardInDeck(pc1.getTopCard());
    field2.placeCardInDeck(pc1.getTopCard());
    field3.placeCardInDeck(pc1.getTopCard());

    field1.placeCardInDeck(pc1.getTopCard());
    field2.placeCardInDeck(pc1.getTopCard());
    field3.placeCardInDeck(pc1.getTopCard());

    field1.placeCardInDeck(pc1.getTopCard());
    field2.placeCardInDeck(pc1.getTopCard());
    field3.placeCardInDeck(pc1.getTopCard());

    cout << field1.getDeckCount() << endl;
    cout << field2.getDeckCount() << endl;
    cout << field3.getDeckCount() << endl;

    field1.showPlayerDeck();
    field2.showPlayerDeck();
    field3.showPlayerDeck();
    //*/

    //field1.setPlayACardButtonCoordOffset(1.1, 2.2);
    //cout << endl << field1.getPlayACardButtonCoordOffset().y << endl;

    //field1.playTopCard();
    
    vector<PlayerPlayField> playerFields;
    playerFields.push_back(field1);
    playerFields.push_back(field2);
    playerFields.push_back(field3);


    PlayingCards pc2;
    //pc1.shuffle();

    GameBoard board(playerFields, pc2);
    
    GameRound gameRound(board);



    // board.dealersDeck.shuffle();

    // cout << gameRound.getPower("K Spades") << endl;
    // cout << gameRound.getPower("5 Clubs") << endl;
    

    //*/

    gameRound.updateGameState(0);

    game = new GameSession(gameRound);
    game->init("War", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

 

    while (game->isRunning())
    {
        game->handleEvents();
        //game->update(); // will be called only if I manage to add the extra functionality I want to
        game->render();

    }

    game->clean();

    return 0;
}
