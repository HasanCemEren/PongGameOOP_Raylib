#include "Game.h"
#include <raylib.h>
#include <cstdlib>
#include <ctime>

const float Game::POWER_UP_SPAWN_INTERVAL = 8.0f; // Power-up spawn every 8 seconds

Game::Game()
    : player(GetScreenWidth() - 35, GetScreenHeight() / 2 - 60),
    cpu(10, GetScreenHeight() / 2 - 60, &ball),
    currentState(GameStateEnum::MAIN_MENU),
    powerUpSpawnTimer(0.0f) {

    //Giving Defaults
    srand(time(NULL));
}

void Game::Run() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        switch (currentState) {
        case GameStateEnum::MAIN_MENU:
            HandleMainMenu();
            break;

        case GameStateEnum::PLAYING:
            HandleGameplay();
            break;
        }

        EndDrawing();
    }
}

void Game::HandleMainMenu() {
    mainMenu.Update();
    mainMenu.Draw();

    if (IsKeyPressed(KEY_ENTER)) {
        int selected = mainMenu.GetSelectedOption();

        switch (selected) {
        case 0: // Start Game
            currentState = GameStateEnum::PLAYING;
            ResetGame();
            break;

        }
    }
}

void Game::HandleGameplay() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentState = GameStateEnum::MAIN_MENU;
        return;
    }

    // Update
    for (auto* entity : entities) {
        entity->Update();
    }
    UpdatePowerUps();

    // Collision Detection
    if (CheckCollisionCircleRec({ ball.GetX(), ball.GetY() }, ball.GetRadius(),
        { player.GetX(), player.GetY(), player.GetWidth(), player.GetHeight() })) {

        // Shield control
        if (player.HasShield()) {
            player.UseShield();
        }
        ball.ReverseSpeedX();
    }

    if (CheckCollisionCircleRec({ ball.GetX(), ball.GetY() }, ball.GetRadius(),
        { cpu.GetX(), cpu.GetY(), cpu.GetWidth(), cpu.GetHeight() })) {

        // Shield control
        if (cpu.HasShield()) {
            cpu.UseShield();
        }
        ball.ReverseSpeedX();
    }

    CheckPowerUpCollisions();

    // Draw
    ClearBackground(DARKGREEN);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);

    // Draw Power-Ups
    for (const auto& powerUp : powerUps) {
        if (powerUp.IsActive()) {
            powerUp.Draw();
        }
    }

    for (auto* entity : entities) {
        entity->Draw();
    }
    scoreboard.Draw(); //We cannot involve this because it

    DrawPowerUpInfo();

    // Extra Drawings
    DrawText("ESC - Main Menu", 10, 10, 20, LIGHTGRAY);
    DrawText("Fashion Power-Ups Active!", GetScreenWidth() / 2 - 100, 10, 20, YELLOW);
}

void Game::UpdatePowerUps() {
    // Power-up spawn timer
    powerUpSpawnTimer += GetFrameTime();
    if (powerUpSpawnTimer >= POWER_UP_SPAWN_INTERVAL) {
        SpawnRandomPowerUp();
        powerUpSpawnTimer = 0.0f;
    }

    //Update power-ups and clear expired ones
    for (auto it = powerUps.begin(); it != powerUps.end();) {
        if (it->IsActive()) {
            it->Update();
            ++it;
        }
        else {
            it = powerUps.erase(it);
        }
    }
}

void Game::SpawnRandomPowerUp() {
    //Spawn in an area in the middle of the screen
    float minX = GetScreenWidth() * 0.3f;
    float maxX = GetScreenWidth() * 0.7f;
    float minY = GetScreenHeight() * 0.2f;
    float maxY = GetScreenHeight() * 0.8f;

    float x = minX + (rand() % (int)(maxX - minX)); //Generate random value with help of ai
    float y = minY + (rand() % (int)(maxY - minY));

    PowerUpType type = static_cast<PowerUpType>(rand() % 6);

    powerUps.emplace_back(x, y, type);
}

void Game::CheckPowerUpCollisions() {
    Rectangle ballRect = {
        ball.GetX() - ball.GetRadius(),
        ball.GetY() - ball.GetRadius(),
        ball.GetRadius() * 2.0f,
        ball.GetRadius() * 2.0f
    };

    for (auto& powerUp : powerUps) {
        if (powerUp.IsActive() && CheckCollisionRecs(ballRect, powerUp.GetBounds())) {
            // Give power-up to the nearest player
            float distToPlayer = abs(ball.GetX() - (player.GetX() + player.GetWidth() / 2));
            float distToCpu = abs(ball.GetX() - (cpu.GetX() + cpu.GetWidth() / 2));

            bool isPlayerCloser = distToPlayer < distToCpu;
            ApplyPowerUpToPlayer(powerUp.GetType(), isPlayerCloser);

            powerUp.Deactivate();
            break;
        }
    }
}

void Game::ApplyPowerUpToPlayer(PowerUpType type, bool isPlayer1) {
    switch (type) {
    case PowerUpType::SHOE:
        // The ball increase the velocity(global effect)
        ball.ApplySpeedBoost();
        break;

    case PowerUpType::JACKET:
        // Paddle length increases
        if (isPlayer1) {
            player.ApplyPowerUp(type);
        }
        else {
            cpu.ApplyPowerUp(type);
        }
        break;

    case PowerUpType::DRESS:
        // Paddle boost its speed
        if (isPlayer1) {
            player.ApplyPowerUp(type);
        }
        else {
            cpu.ApplyPowerUp(type);
        }
        break;

    case PowerUpType::NECKLACE:
        // The ball be bigger
        ball.ApplySizeBoost();
        break;

    case PowerUpType::HAT:
        // Shield
        if (isPlayer1) {
            player.ApplyPowerUp(type);
        }
        else {
            cpu.ApplyPowerUp(type);
        }
        break;

    case PowerUpType::BAG:
        // Double points
        if (isPlayer1) {
            player.ApplyPowerUp(type);
        }
        else {
            cpu.ApplyPowerUp(type);
        }
        break;
    }
}

void Game::DrawPowerUpInfo() const {
    // Power-up legend
    int legendY = GetScreenHeight() - 120;
    DrawText("FASHION POWER-UPS:", 10, legendY, 16, WHITE);

    const char* powerUpDescriptions[] = {
        "Shoe: Ball Speed+",
        "Jacket: Paddle Size+",
        "Dress: Paddle Speed+",
        "Necklace: Ball Size+",
        "Hat: Shield",
        "Bag: Double Points"
    };

    for (int i = 0; i < 6; i++) {
        DrawText(powerUpDescriptions[i], 10, legendY + 20 + i * 15, 12, LIGHTGRAY);
    }

    // Active power-up counter
    int activePowerUps = 0;
    for (const auto& powerUp : powerUps) {
        if (powerUp.IsActive()) activePowerUps++;
    }

    DrawText(TextFormat("Active Power-Ups: %d", activePowerUps),
        GetScreenWidth() - 200, legendY, 16, YELLOW);
}

void Game::ResetGame() {
    ball.Reset();
    powerUps.clear();
    powerUpSpawnTimer = 0.0f;
}