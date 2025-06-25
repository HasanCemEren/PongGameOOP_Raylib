#pragma once
#include "Entity.h"
#include <raylib.h>  

class Ball : public Entity {
private:
    int radius;
    int originalRadius;
    int speedX, speedY;
    int originalSpeedX, originalSpeedY;
    float powerUpTimer;
    bool hasPowerUp;

public:
    Ball();
    void Update() override;
    void Draw() const override;
    void Reset();
    void ReverseSpeedX();
    int GetRadius() const;

    // Power-up functions
    void ApplySpeedBoost();
    void ApplySizeBoost();
    void UpdatePowerUp();
    Color GetBallColor() const; 
};