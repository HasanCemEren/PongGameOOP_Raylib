#pragma once
#include <raylib.h>

class Ball {
public:
    float x, y;
    int speedX, speedY;
    int radius;

    void Draw();
    void Update();
    void ResetBall();
};
