#include "Ball.h"
#include "GameState.h"
#include <raylib.h>

Ball::Ball() {
    radius = 20;
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    speedX = 5;
    speedY = 5;
}

void Ball::Update() {
    x += speedX;
    y += speedY;

    // Üst ve alt duvarlara çarpma - Y hýzýný ters çevir
    if (y + radius >= GetScreenHeight() || y - radius <= 0)
        speedY *= -1;

    // Sað duvara çarpma - CPU kazanýr
    if (x + radius >= GetScreenWidth()) {
        GameState::cpuScore++;
        Reset();
    }

    // Sol duvara çarpma - Player kazanýr  
    if (x - radius <= 0) {
        GameState::playerScore++;
        Reset();
    }
}

void Ball::Draw() const {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, YELLOW);
}

void Ball::Reset() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    // Random yön seçimi - daha temiz kod
    int xDirection = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    int yDirection = (GetRandomValue(0, 1) == 0) ? -1 : 1;

    speedX = 5 * xDirection;
    speedY = 5 * yDirection;
}

// Paddle collision için - sadece X hýzýný ters çevir
void Ball::ReverseSpeedX() {
    speedX *= -1;
}

int Ball::GetRadius() const {
    return radius;
}