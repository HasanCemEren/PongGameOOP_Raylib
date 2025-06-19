#pragma once
#include "Entity.h"
#include "PowerUp.h"

class Ball;

class Paddle : public Entity {
protected:
    float width, height;
    int speed;

    // Power-up özellikleri
    float originalHeight;
    float originalSpeed;
    float powerUpTimer;
    PowerUpType activePowerUp;
    bool hasPowerUp;
    bool hasShield;

    void LimitMovement();

public:
    Paddle(float x, float y);
    void Draw() const override;
    virtual void Update() override = 0;
    float GetWidth() const;
    float GetHeight() const;

    // Power-up fonksiyonlarý
    void ApplyPowerUp(PowerUpType type);
    void UpdatePowerUp();
    bool HasShield() const;
    void UseShield();
    Color GetPaddleColor() const;
};

class PlayerPaddle : public Paddle {
public:
    PlayerPaddle(float x, float y);
    void Update() override;
};

class CpuPaddle : public Paddle {
private:
    const Ball* ball;
public:
    CpuPaddle(float x, float y, const Ball* ballRef);
    void Update() override;
};