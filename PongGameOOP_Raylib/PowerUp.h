#pragma once
#include "Entity.h"
#include <raylib.h>

enum class PowerUpType {
    SHOE,     // Ayakkabэ - Top hэzlanэr
    JACKET,   // Ceket - Paddle uzar  
    DRESS,    // Elbise - Paddle hэzlanэr
    NECKLACE, // Kolye - Top bьyьr
    HAT,      // Юapka - Kalkan
    BAG       // Зanta - Double points
};

class PowerUp : public Entity {
private:
    PowerUpType type;
    float rotation;
    float spawnTime;
    bool active;
    float size;

public:
    PowerUp(float xPos, float yPos, PowerUpType powerType);
    void Update() override;
    void Draw() const override;
    bool IsActive() const;
    void Deactivate();
    PowerUpType GetType() const;
    bool IsExpired() const;
    Rectangle GetBounds() const;
};

