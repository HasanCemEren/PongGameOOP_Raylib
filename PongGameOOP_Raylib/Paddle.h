#pragma once
#include "Entity.h"

// Forward declaration - Ball sýnýfýný önceden tanýmlýyoruz
class Ball;

class Paddle : public Entity {
protected:
    float width, height;
    int speed;
    void LimitMovement();
public:
    Paddle(float x, float y);
    void Draw() const override;
    virtual void Update() override = 0;
    float GetWidth() const;
    float GetHeight() const;
};

class PlayerPaddle : public Paddle {
public:
    PlayerPaddle(float x, float y);
    void Update() override;
};

class CpuPaddle : public Paddle {
private:
    const Ball* ball;  // Artýk Ball forward declaration sayesinde tanýnýyor
public:
    CpuPaddle(float x, float y, const Ball* ballRef);
    void Update() override;
};