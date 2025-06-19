#include "PowerUp.h"
#include <cmath>

PowerUp::PowerUp(float xPos, float yPos, PowerUpType powerType) {
    x = xPos;
    y = yPos;
    type = powerType;
    rotation = 0.0f;
    spawnTime = GetTime();
    active = true;
    size = 30.0f;
}

void PowerUp::Update() {
    if (!active) return;

    rotation += GetFrameTime() * 90.0f; // 90 derece/saniye dönüş

    // 15 saniye sonra kaybolur
    if (GetTime() - spawnTime > 15.0f) {
        active = false;
    }
}

void PowerUp::Draw() const {
    if (!active) return;

    // Glow efekti
    DrawCircleLines(static_cast<int>(x), static_cast<int>(y),
        static_cast<int>(size + sin(GetTime() * 5) * 3), WHITE);

    switch (type) {
    case PowerUpType::SHOE: // 👠 Ayakkabı
        DrawEllipse(static_cast<int>(x), static_cast<int>(y), 20, 8, RED);
        DrawRectangle(static_cast<int>(x + 15), static_cast<int>(y - 3), 8, 6, BROWN);
        break;

    case PowerUpType::JACKET: // 🧥 Ceket
        DrawRectangle(static_cast<int>(x - 15), static_cast<int>(y - 10), 30, 25, BLUE);
        DrawRectangle(static_cast<int>(x - 20), static_cast<int>(y - 5), 10, 20, BLUE); // Sol kol
        DrawRectangle(static_cast<int>(x + 15), static_cast<int>(y - 5), 10, 20, BLUE); // Sağ kol
        break;

    case PowerUpType::DRESS: // 👗 Elbise
        DrawCircle(static_cast<int>(x), static_cast<int>(y - 10), 8, PINK);
        DrawRectangle(static_cast<int>(x - 12), static_cast<int>(y), 24, 20, PINK);
        break;

    case PowerUpType::NECKLACE: // 💎 Kolye
        // DrawPoly yerine alternatif çizim
    {
        Vector2 center = { x, y };
        float radius = 8.0f;
        int sides = 4;
        float angle = (45 + rotation) * DEG2RAD;

        Vector2 points[4];
        for (int i = 0; i < sides; i++) {
            float currentAngle = angle + (i * 2 * PI / sides);
            points[i].x = center.x + radius * cos(currentAngle);
            points[i].y = center.y + radius * sin(currentAngle);
        }

        // Elmas şekli çiz
        for (int i = 0; i < sides; i++) {
            int next = (i + 1) % sides;
            DrawLine(static_cast<int>(points[i].x), static_cast<int>(points[i].y),
                static_cast<int>(points[next].x), static_cast<int>(points[next].y), YELLOW);
        }

        DrawCircle(static_cast<int>(x), static_cast<int>(y - 15), 3, GOLD);
    }
    break;

    case PowerUpType::HAT: // 🎩 Şapka
        DrawRectangle(static_cast<int>(x - 15), static_cast<int>(y), 30, 8, BLACK);
        DrawRectangle(static_cast<int>(x - 10), static_cast<int>(y - 15), 20, 15, BLACK);
        break;

    case PowerUpType::BAG: // 👜 Çanta
        DrawRectangle(static_cast<int>(x - 12), static_cast<int>(y - 8), 24, 16, PURPLE);
        DrawRectangle(static_cast<int>(x - 8), static_cast<int>(y - 12), 16, 4, PURPLE);
        break;
    }
}

bool PowerUp::IsActive() const {
    return active;
}

void PowerUp::Deactivate() {
    active = false;
}

PowerUpType PowerUp::GetType() const {
    return type;
}

bool PowerUp::IsExpired() const {
    return GetTime() - spawnTime > 15.0f;
}

Rectangle PowerUp::GetBounds() const {
    return { x - size / 2, y - size / 2, size, size };
}