#include "Ball.h"
#include "GameState.h"
#include <raylib.h>
#include <cmath>

Ball::Ball() {
    radius = 20;
    originalRadius = radius;
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    speedX = 5;
    speedY = 5;
    originalSpeedX = 5;
    originalSpeedY = 5;
    powerUpTimer = 0.0f;
    hasPowerUp = false;
}

void Ball::Update() {
    x += speedX;
    y += speedY;

    // Update Power-up timing
    UpdatePowerUp();

    // Wall collision
    if (y + radius >= GetScreenHeight() || y - radius <= 0)
        speedY *= -1;

    // CPU Win condition
    if (x + radius >= GetScreenWidth()) {
        GameState::cpuScore++;
        Reset();
    }

    // Player Win condition 
    if (x - radius <= 0) {
        GameState::playerScore++;
        Reset();
    }
}

void Ball::Draw() const {
    Color ballColor = GetBallColor();
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, ballColor);

    // Glow effect while Power-up active
    if (hasPowerUp) {
        DrawCircleLines(x, y, radius + 5, Fade(ballColor, 0.5f));
    }
}

void Ball::Reset() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    radius = originalRadius;
    hasPowerUp = false;
    powerUpTimer = 0.0f;

    int xDirection = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    int yDirection = (GetRandomValue(0, 1) == 0) ? -1 : 1;

    speedX = originalSpeedX * xDirection;
    speedY = originalSpeedY * yDirection;
}

void Ball::ReverseSpeedX() {
    speedX *= -1;
}

int Ball::GetRadius() const {
    return radius;
}

void Ball::ApplySpeedBoost() {
    speedX = static_cast<int>(speedX * 1.3f);
    speedY = static_cast<int>(speedY * 1.3f);
    hasPowerUp = true;
    powerUpTimer = 10.0f;
}

void Ball::ApplySizeBoost() {
    radius = static_cast<int>(originalRadius * 1.5f);
    hasPowerUp = true;
    powerUpTimer = 10.0f;
}

void Ball::UpdatePowerUp() {
    if (hasPowerUp && powerUpTimer > 0) {
        powerUpTimer -= GetFrameTime();

        if (powerUpTimer <= 0) {
            hasPowerUp = false;
            radius = originalRadius;
            // It's not go back to original speed to protect the momentum.
        }
    }
}

Color Ball::GetBallColor() const {
    if (radius > originalRadius) return YELLOW;
    return WHITE;
}