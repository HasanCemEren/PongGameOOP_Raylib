#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "ScoreBoard.h"
#include "MainMenu.h"
#include "PowerUp.h"
#include <vector>

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

    // Power-up system
    std::vector<PowerUp> powerUps;
    float powerUpSpawnTimer;
    static const float POWER_UP_SPAWN_INTERVAL; //Its static becasue everyone has the same value

    void HandleMainMenu();
    void HandleGameplay();
    void ResetGame();

    // Power-up functions
    void UpdatePowerUps();
    void SpawnRandomPowerUp();
    void CheckPowerUpCollisions();
    void ApplyPowerUpToPlayer(PowerUpType type, bool isPlayer1);
    void DrawPowerUpInfo() const;

public:
    Game();
    void Run();
    std::vector<Entity*> entities = { &ball, &player, &cpu }; //Polym. structure
};