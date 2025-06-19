#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "ScoreBoard.h"
#include "MainMenu.h"

enum class GameStateEnum {
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
private:
    Ball ball;
    PlayerPaddle player;
    CpuPaddle cpu;
    ScoreBoard scoreboard;
    MainMenu mainMenu;
    GameStateEnum currentState;

    void HandleMainMenu();
    void HandleGameplay();
    void ResetGame();

public:
    Game();
    void Run();
};