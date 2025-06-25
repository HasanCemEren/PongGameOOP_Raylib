#include "MainMenu.h"
#include <raylib.h>

MainMenu::MainMenu() {
    selectedOption = 0;
    totalOptions = 3; // Start Game, Settings, Quit
}

void MainMenu::Update() {
    // Keyboard navigation
    if (IsKeyPressed(KEY_UP)) {
        selectedOption--;
        if (selectedOption < 0) selectedOption = totalOptions - 1;
    }

    if (IsKeyPressed(KEY_DOWN)) {
        selectedOption++;
        if (selectedOption >= totalOptions) selectedOption = 0;
    }
}

void MainMenu::Draw() const {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Background
    ClearBackground(DARKGREEN);

    // Title H1
    const char* title = "Style Smash";
    int titleSize = 80;
    int titleWidth = MeasureText(title, titleSize);
    DrawText(title, (screenWidth - titleWidth) / 2, screenHeight / 4, titleSize, YELLOW);

    // H2
    const char* subtitle = "Made with Raylib & C++";
    int subtitleSize = 20;
    int subtitleWidth = MeasureText(subtitle, subtitleSize);
    DrawText(subtitle, (screenWidth - subtitleWidth) / 2, screenHeight / 4 + 100, subtitleSize, LIGHTGRAY);

    // Menu Options
    const char* options[] = {
        "Start Game",
        "Settings",
        "Quit"
    };

    int optionSize = 40;
    int startY = screenHeight / 2 + 50;
    int spacing = 70;

    for (int i = 0; i < totalOptions; i++) {
        Color color = (i == selectedOption) ? YELLOW : WHITE; //Quick if statement.
        int optionWidth = MeasureText(options[i], optionSize);
        int x = (screenWidth - optionWidth) / 2;
        int y = startY + i * spacing;

        // Arrow for selected one
        if (i == selectedOption) {
            DrawText(">", x - 50, y, optionSize, YELLOW);
            DrawText("<", x + optionWidth + 20, y, optionSize, YELLOW);
        }

        DrawText(options[i], x, y, optionSize, color);
    }

    // Gameplay infos
    const char* controls = "Use UP/DOWN arrows to navigate, ENTER to select";
    int controlSize = 16;
    int controlWidth = MeasureText(controls, controlSize);
    DrawText(controls, (screenWidth - controlWidth) / 2, screenHeight - 50, controlSize, GRAY);
}

int MainMenu::GetSelectedOption() const {
    return selectedOption;
}

void MainMenu::Reset() {
    selectedOption = 0;
}