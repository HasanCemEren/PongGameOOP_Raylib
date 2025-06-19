#include "Paddle.h"
#include <raylib.h>
#include "Ball.h"

Paddle::Paddle(float xPos, float yPos) {
    x = xPos;
    y = yPos;
    width = 25;
    height = 120;
    speed = 6;
}

void Paddle::Draw() const {
    DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8f, 0, WHITE);
}

void Paddle::LimitMovement() {
    if (y < 0) y = 0;
    if (y + height > GetScreenHeight()) y = GetScreenHeight() - height;
}

float Paddle::GetWidth() const { return width; }
float Paddle::GetHeight() const { return height; }

PlayerPaddle::PlayerPaddle(float xPos, float yPos) : Paddle(xPos, yPos) {}

void PlayerPaddle::Update() {
    if (IsKeyDown(KEY_UP)) y -= speed;
    if (IsKeyDown(KEY_DOWN)) y += speed;
    LimitMovement();
}

CpuPaddle::CpuPaddle(float xPos, float yPos, const Ball* ballRef)
    : Paddle(xPos, yPos), ball(ballRef) {}

void CpuPaddle::Update() {
    if (y + height / 2 > ball->GetY()) y -= speed;
    if (y + height / 2 < ball->GetY()) y += speed;
    LimitMovement();
}
