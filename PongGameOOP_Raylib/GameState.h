#pragma once

enum class GameStateEnum {
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

//I used extern to avoid linker problems. If we use playerScore more than pne time this will make some linker problem to us.
namespace GameState {
    extern int playerScore;
    extern int cpuScore;
}