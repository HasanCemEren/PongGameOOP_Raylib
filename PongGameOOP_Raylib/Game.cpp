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
            // TODO: Pause menüsü
            break;

        case GameStateEnum::GAME_OVER:
            // TODO: Game Over ekraný
            break;
        }

        EndDrawing();
    }
}

void Game::HandleMainMenu() {
    mainMenu.Update();
    mainMenu.Draw();

    // ENTER tuþuna basýlýnca seçeneði iþle
    if (IsKeyPressed(KEY_ENTER)) {
        int selected = mainMenu.GetSelectedOption();

        switch (selected) {
        case 0: // Start Game
            currentState = GameStateEnum::PLAYING;
            ResetGame();
            break;

        case 1: // Settings
            // TODO: Settings menüsü
            break;

        case 2: // Quit
            // Oyunu kapat - main loop'tan çýk
            // Bu durumda WindowShouldClose() true döndürecek
            break;
        }
    }
}

void Game::HandleGameplay() {
    // ESC tuþu ile ana menüye dön
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

    // ESC tuþu bilgisi
    DrawText("ESC - Main Menu", 10, 10, 20, LIGHTGRAY);
}

void Game::ResetGame() {
    ball.Reset();
    // Skorlarý sýfýrlamak isterseniz Score namespace'ini güncelleyin
}