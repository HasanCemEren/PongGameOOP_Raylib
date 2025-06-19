#pragma once
#include "Entity.h"

class Ball : public Entity {
private:
    int radius;
    int speedX, speedY;
public:
    Ball();
    void Update() override;
    void Draw() const override;
    void Reset();
    void ReverseSpeedX(); // Yeni fonksiyon - paddle collision için
    int GetRadius() const;
};