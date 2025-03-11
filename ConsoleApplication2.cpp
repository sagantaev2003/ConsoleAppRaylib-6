#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef enum { ROCK, PAPER, SCISSORS, NONE } Choice;

Choice GetComputerChoice() {
    return (Choice)(rand() % 3);
}

const char* GetResult(Choice player, Choice computer, Color* textColor) {
    if (player == computer) {
        *textColor = ORANGE;
        return "Draw!";
    }
    if ((player == ROCK && computer == SCISSORS) ||
        (player == PAPER && computer == ROCK) ||
        (player == SCISSORS && computer == PAPER)) {
        *textColor = GREEN;
        return "You Win!";
    }
    *textColor = RED;
    return "You Lose!";
}

int main() {
    int screenWidth = 1000;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rock, Paper, Scissors - Sagantay Adil CS-104(s)");
    SetTargetFPS(60);
    srand(static_cast<unsigned int>(time(NULL)));

    Texture2D rockSprite = LoadTexture("resources/rock.png");
    Texture2D paperSprite = LoadTexture("resources/paper.png");
    Texture2D scissorsSprite = LoadTexture("resources/scissors.png");

    Choice playerChoice = NONE;
    Choice computerChoice = NONE;
    bool gameStarted = false;
    bool selectionMade = false;
    Color resultColor = BLACK;

    Rectangle rockButton = { screenWidth / 2 - 225, 200, 100, 50 };
    Rectangle paperButton = { screenWidth / 2 - 50, 200, 100, 50 };
    Rectangle scissorsButton = { screenWidth / 2 + 125, 200, 120, 50 };
    Rectangle resetButton = { screenWidth / 2 - 75, 300, 150, 50 };

    float cornerRadius = 0.4f;  // Радиус округления кнопок

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        bool hoveredRock = CheckCollisionPointRec(mousePoint, rockButton);
        bool hoveredPaper = CheckCollisionPointRec(mousePoint, paperButton);
        bool hoveredScissors = CheckCollisionPointRec(mousePoint, scissorsButton);
        bool hoveredReset = CheckCollisionPointRec(mousePoint, resetButton);

        if (IsKeyPressed(KEY_SPACE) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoveredReset)) {
            playerChoice = NONE;
            computerChoice = NONE;
            gameStarted = false;
            selectionMade = false;
            resultColor = BLACK;
        }

        if (!gameStarted && !selectionMade) {
            if (IsKeyPressed(KEY_R)) playerChoice = ROCK;
            if (IsKeyPressed(KEY_P)) playerChoice = PAPER;
            if (IsKeyPressed(KEY_S)) playerChoice = SCISSORS;

            if (playerChoice != NONE) {
                computerChoice = GetComputerChoice();
                gameStarted = true;
                selectionMade = true;
            }
        }

        if (!selectionMade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (hoveredRock) playerChoice = ROCK;
            if (hoveredPaper) playerChoice = PAPER;
            if (hoveredScissors) playerChoice = SCISSORS;

            if (playerChoice != NONE) {
                computerChoice = GetComputerChoice();
                gameStarted = true;
                selectionMade = true;
            }
        }

        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("Press R - Rock, P - Paper, S - Scissors to play or click buttons", screenWidth / 2 - 300, 150, 20, BLACK);
        DrawText("Press SPACE or click reset to restart", screenWidth / 2 - 200, 265, 20, BLACK);

        Color buttonColor = LIGHTGRAY;
        Color hoverColor = DARKGRAY;

        // Рисуем кнопки с округлением
        DrawRectangleRounded(rockButton, cornerRadius, 6, hoveredRock ? hoverColor : buttonColor);
        DrawRectangleRounded(paperButton, cornerRadius, 6, hoveredPaper ? hoverColor : buttonColor);
        DrawRectangleRounded(scissorsButton, cornerRadius, 6, hoveredScissors ? hoverColor : buttonColor);
        DrawRectangleRounded(resetButton, cornerRadius, 6, hoveredReset ? hoverColor : buttonColor);

        DrawText("Rock", rockButton.x + 25, rockButton.y + 15, 20, BLACK);
        DrawText("Paper", paperButton.x + 25, paperButton.y + 15, 20, BLACK);
        DrawText("Scissors", scissorsButton.x + 15, scissorsButton.y + 15, 20, BLACK);
        DrawText("Reset", resetButton.x + 40, resetButton.y + 15, 20, BLACK);

        if (gameStarted) {
            DrawText("Your choice:", screenWidth / 2 - 200, 350, 20, BLACK);
            DrawText("Computer choice:", screenWidth / 2 + 50, 350, 20, BLACK);

            Vector2 playerPos = { screenWidth / 2 - 200, 380 };
            Vector2 computerPos = { screenWidth / 2 + 50, 380 };

            if (playerChoice == ROCK)
                DrawTexturePro(rockSprite, { 0, 0, (float)rockSprite.width, (float)rockSprite.height }, { playerPos.x, playerPos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (playerChoice == PAPER)
                DrawTexturePro(paperSprite, { 0, 0, (float)paperSprite.width, (float)paperSprite.height }, { playerPos.x, playerPos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (playerChoice == SCISSORS)
                DrawTexturePro(scissorsSprite, { 0, 0, (float)scissorsSprite.width, (float)scissorsSprite.height }, { playerPos.x, playerPos.y, 100, 100 }, { 0, 0 }, 0, WHITE);

            if (computerChoice == ROCK)
                DrawTexturePro(rockSprite, { 0, 0, (float)rockSprite.width, (float)rockSprite.height }, { computerPos.x, computerPos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (computerChoice == PAPER)
                DrawTexturePro(paperSprite, { 0, 0, (float)paperSprite.width, (float)paperSprite.height }, { computerPos.x, computerPos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (computerChoice == SCISSORS)
                DrawTexturePro(scissorsSprite, { 0, 0, (float)scissorsSprite.width, (float)scissorsSprite.height }, { computerPos.x, computerPos.y, 100, 100 }, { 0, 0 }, 0, WHITE);

            DrawText(GetResult(playerChoice, computerChoice, &resultColor), screenWidth / 2 - 50, 500, 30, resultColor);
        }

        EndDrawing();
    }

    UnloadTexture(rockSprite);
    UnloadTexture(paperSprite);
    UnloadTexture(scissorsSprite);
    CloseWindow();
    return 0;
}
