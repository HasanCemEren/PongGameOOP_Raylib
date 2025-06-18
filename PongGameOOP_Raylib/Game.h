#pragma once
#include "Ball.h"
#include "Paddle.h"

class Game {
public:
    Ball ball;
    Paddle player;
    CpuPaddle cpu;

    void Init(int screenWidth, int screenHeight);
    void Update();
    void Draw(int screenWidth, int screenHeight);
};
