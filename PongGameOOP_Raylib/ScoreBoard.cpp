#include "ScoreBoard.h"
#include "GameState.h"
#include <raylib.h>

void ScoreBoard::Draw() const {
    int screenWidth = GetScreenWidth();
    DrawText(TextFormat("%i", GameState::cpuScore), screenWidth / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", GameState::playerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
}
