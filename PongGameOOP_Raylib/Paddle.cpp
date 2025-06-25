#include "Paddle.h"
#include <raylib.h>
#include "Ball.h"
#include <cmath>

Paddle::Paddle(float xPos, float yPos) {
    x = xPos;
    y = yPos;
    width = 25;
    height = 120;
    speed = 6;

    // Power-up initial values
    originalHeight = height;
    originalSpeed = static_cast<float>(speed);
    powerUpTimer = 0.0f;
    hasPowerUp = false;
    hasShield = false;
}

void Paddle::Draw() const {
    Color paddleColor = GetPaddleColor();

    // Glow effect while Power-Up is active
    if (hasPowerUp) {
        DrawRectangleRounded({ x - 2, y - 2, width + 4, height + 4 }, 0.8f, 0, Fade(paddleColor, 0.3f));
    }

    DrawRectangleRounded({ x, y, width, height }, 0.8f, 0, paddleColor);

    // Shield effect
    if (hasShield) {
        DrawCircleLines(static_cast<int>(x + width / 2), static_cast<int>(y + height / 2), 60, GOLD);
        DrawText("SHIELD", static_cast<int>(x - 10), static_cast<int>(y - 20), 12, GOLD);
    }

    // Power-up timer square
    if (hasPowerUp && powerUpTimer > 0) {
        float timerWidth = (powerUpTimer / 10.0f) * width;
        DrawRectangle(static_cast<int>(x), static_cast<int>(y - 8),
            static_cast<int>(timerWidth), 4, GREEN);
    }
}

void Paddle::ApplyPowerUp(PowerUpType type) {
    activePowerUp = type;
    hasPowerUp = true;
    powerUpTimer = 10.0f; // 10 sec.

    switch (type) {
    case PowerUpType::JACKET:
        height = originalHeight + 40; // Add height to paddle
        break;
    case PowerUpType::DRESS:
        speed = static_cast<int>(originalSpeed * 1.5f); // It gets velocity boost
        break;
    case PowerUpType::HAT:
        hasShield = true;
        break;
    default:
        break;
    }
}

void Paddle::UpdatePowerUp() {
    if (hasPowerUp && powerUpTimer > 0) {
        powerUpTimer -= GetFrameTime();

        if (powerUpTimer <= 0) {
            // Power-up has expired, go back to initial values.
            hasPowerUp = false;
            hasShield = false;
            height = originalHeight;
            speed = static_cast<int>(originalSpeed);
        }
    }
}

bool Paddle::HasShield() const {
    return hasShield;
}

void Paddle::UseShield() {
    hasShield = false;
    hasPowerUp = false;
    powerUpTimer = 0;
}

Color Paddle::GetPaddleColor() const {
    if (!hasPowerUp) return WHITE;

    switch (activePowerUp) {
    case PowerUpType::SHOE: return RED;
    case PowerUpType::JACKET: return BLUE;
    case PowerUpType::DRESS: return PINK;
    case PowerUpType::NECKLACE: return YELLOW;
    case PowerUpType::HAT: return PURPLE;
    case PowerUpType::BAG: return GREEN;
    default: return WHITE;
    }
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
    UpdatePowerUp();
}

CpuPaddle::CpuPaddle(float xPos, float yPos, const Ball* ballRef)
    : Paddle(xPos, yPos), ball(ballRef) {}

void CpuPaddle::Update() {
    if (y + height / 2 > ball->GetY()) y -= speed;
    if (y + height / 2 < ball->GetY()) y += speed;
    LimitMovement();
    UpdatePowerUp();
}