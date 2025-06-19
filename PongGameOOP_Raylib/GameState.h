#pragma once

// Oyun durumlarý
enum class GameStateEnum {
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

// Score namespace'i eski GameState namespace'i yerine
namespace GameState {
    extern int playerScore;
    extern int cpuScore;
}