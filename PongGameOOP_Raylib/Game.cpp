#include "Game.h"
#include <raylib.h>

Game::Game()
    : player(GetScreenWidth() - 35, GetScreenHeight() / 2 - 60),
    cpu(10, GetScreenHeight() / 2 - 60, &ball),
    currentState(GameStateEnum::MAIN_MENU) {}

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

        case GameStateEnum::PAUSED:
            // TODO: Pause men�s�
            break;

        case GameStateEnum::GAME_OVER:
            // TODO: Game Over ekran�
            break;
        }

        EndDrawing();
    }
}

void Game::HandleMainMenu() {
    mainMenu.Update();
    mainMenu.Draw();

    // ENTER tu�una bas�l�nca se�ene�i i�le
    if (IsKeyPressed(KEY_ENTER)) {
        int selected = mainMenu.GetSelectedOption();

        switch (selected) {
        case 0: // Start Game
            currentState = GameStateEnum::PLAYING;
            ResetGame();
            break;

        case 1: // Settings
            // TODO: Settings men�s�
            break;

        case 2: // Quit
            // Oyunu kapat - main loop'tan ��k
            // Bu durumda WindowShouldClose() true d�nd�recek
            break;
        }
    }
}

void Game::HandleGameplay() {
    // ESC tu�u ile ana men�ye d�n
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentState = GameStateEnum::MAIN_MENU;
        return;
    }

    // Update
    ball.Update();
    player.Update();
    cpu.Update();

    // Collision Detection
    if (CheckCollisionCircleRec({ ball.GetX(), ball.GetY() }, ball.GetRadius(),
        { player.GetX(), player.GetY(), player.GetWidth(), player.GetHeight() })) {
        ball.ReverseSpeedX();
    }

    if (CheckCollisionCircleRec({ ball.GetX(), ball.GetY() }, ball.GetRadius(),
        { cpu.GetX(), cpu.GetY(), cpu.GetWidth(), cpu.GetHeight() })) {
        ball.ReverseSpeedX();
    }

    // Draw
    ClearBackground(DARKGREEN);
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);
    ball.Draw();
    player.Draw();
    cpu.Draw();
    scoreboard.Draw();

    // ESC tu�u bilgisi
    DrawText("ESC - Main Menu", 10, 10, 20, LIGHTGRAY);
}

void Game::ResetGame() {
    ball.Reset();
    // Skorlar� s�f�rlamak isterseniz Score namespace'ini g�ncelleyin
}