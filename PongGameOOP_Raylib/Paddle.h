#pragma once
#include <raylib.h>

class Paddle {
protected:
    void LimitMovement();
public:
    float x, y;
    float width, height;
    int speed;

    void Draw();
    virtual void Update();
};

class CpuPaddle : public Paddle {
public:
    void Update(int ball_y);
};
