#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef enum { ROCK, PAPER, SCISSORS, NONE } Choice;

const char* DetermineWinner(Choice player1, Choice player2, Color* textColor) {
    if (player1 == player2) {
        *textColor = ORANGE;
        return "Draw!";
    }
    if ((player1 == ROCK && player2 == SCISSORS) ||
        (player1 == PAPER && player2 == ROCK) ||
        (player1 == SCISSORS && player2 == PAPER)) {
        *textColor = GREEN;
        return "Player 1 Wins!";
    }
    *textColor = RED;
    return "Player 2 Wins!";
}

int main() {
    int screenWidth = 1000;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rock, Paper, Scissors - Two Players");
    SetTargetFPS(60);

    Texture2D rockSprite = LoadTexture("resources/rock.png");
    Texture2D paperSprite = LoadTexture("resources/paper.png");
    Texture2D scissorsSprite = LoadTexture("resources/scissors.png");

    Choice player1Choice = NONE;
    Choice player2Choice = NONE;
    bool gameStarted = false;
    bool player1MadeChoice = false;
    bool player2MadeChoice = false;
    Color resultColor = BLACK;

    Rectangle resetButton = { screenWidth / 2 - 75, 300, 150, 50 };
    float cornerRadius = 0.4f;

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        bool hoveredReset = CheckCollisionPointRec(mousePoint, resetButton);

        if (IsKeyPressed(KEY_SPACE) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoveredReset)) {
            player1Choice = NONE;
            player2Choice = NONE;
            gameStarted = false;
            player1MadeChoice = false;
            player2MadeChoice = false;
            resultColor = BLACK;
        }

        if (!gameStarted) {
            if (!player1MadeChoice) {
                if (IsKeyPressed(KEY_R)) { player1Choice = ROCK; player1MadeChoice = true; }
                if (IsKeyPressed(KEY_P)) { player1Choice = PAPER; player1MadeChoice = true; }
                if (IsKeyPressed(KEY_S)) { player1Choice = SCISSORS; player1MadeChoice = true; }
            }
            if (player1MadeChoice && !player2MadeChoice) {
                if (IsKeyPressed(KEY_A)) { player2Choice = ROCK; player2MadeChoice = true; }
                if (IsKeyPressed(KEY_W)) { player2Choice = PAPER; player2MadeChoice = true; }
                if (IsKeyPressed(KEY_D)) { player2Choice = SCISSORS; player2MadeChoice = true; }
            }

            if (player1MadeChoice && player2MadeChoice) {
                gameStarted = true;
            }
        }

        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("Player 1: Press R - Rock, P - Paper, S - Scissors", 50, 150, 20, BLACK);
        DrawText("Player 2: Press A - Rock, W - Paper, D - Scissors", 50, 180, 20, BLACK);
        DrawText("Press SPACE or click reset to restart", 50, 210, 20, BLACK);

        if (!player1MadeChoice) {
            DrawText("Player 1, make your choice!", 50, 250, 20, RED);
        }
        else if (!gameStarted) {
            DrawText("Player 1 has chosen!", 50, 250, 20, GREEN);
        }

        if (player1MadeChoice && !player2MadeChoice) {
            DrawText("Player 2, make your choice!", 50, 280, 20, RED);
        }

        if (player1MadeChoice && player2MadeChoice) {
            DrawText("Both players have chosen!", 50, 310, 20, GREEN);
        }

        DrawRectangleRounded(resetButton, cornerRadius, 6, hoveredReset ? DARKGRAY : LIGHTGRAY);
        DrawText("Reset", resetButton.x + 40, resetButton.y + 15, 20, BLACK);

        if (gameStarted) {
            DrawText("Player 1's choice:", 200, 350, 20, BLACK);
            DrawText("Player 2's choice:", 600, 350, 20, BLACK);

            Vector2 player1Pos = { 200, 380 };
            Vector2 player2Pos = { 600, 380 };

            if (player1Choice == ROCK)
                DrawTexturePro(rockSprite, { 0, 0, (float)rockSprite.width, (float)rockSprite.height }, { player1Pos.x, player1Pos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (player1Choice == PAPER)
                DrawTexturePro(paperSprite, { 0, 0, (float)paperSprite.width, (float)paperSprite.height }, { player1Pos.x, player1Pos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (player1Choice == SCISSORS)
                DrawTexturePro(scissorsSprite, { 0, 0, (float)scissorsSprite.width, (float)scissorsSprite.height }, { player1Pos.x, player1Pos.y, 100, 100 }, { 0, 0 }, 0, WHITE);

            if (player2Choice == ROCK)
                DrawTexturePro(rockSprite, { 0, 0, (float)rockSprite.width, (float)rockSprite.height }, { player2Pos.x, player2Pos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (player2Choice == PAPER)
                DrawTexturePro(paperSprite, { 0, 0, (float)paperSprite.width, (float)paperSprite.height }, { player2Pos.x, player2Pos.y, 100, 100 }, { 0, 0 }, 0, WHITE);
            if (player2Choice == SCISSORS)
                DrawTexturePro(scissorsSprite, { 0, 0, (float)scissorsSprite.width, (float)scissorsSprite.height }, { player2Pos.x, player2Pos.y, 100, 100 }, { 0, 0 }, 0, WHITE);

            DrawText(DetermineWinner(player1Choice, player2Choice, &resultColor), screenWidth / 2 - 50, 500, 30, resultColor);
        }

        EndDrawing();
    }

    UnloadTexture(rockSprite);
    UnloadTexture(paperSprite);
    UnloadTexture(scissorsSprite);
    CloseWindow();
    return 0;
}
