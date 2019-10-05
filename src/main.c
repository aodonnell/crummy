#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main(int argc, char* argv[])
{
    InitWindow(screenWidth, screenHeight, "crummy");

    Texture2D cowboi = LoadTexture("assets/cowboy.png");

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(cowboi, screenWidth/2 - cowboi.width/2, screenHeight/2 - cowboi.height/2, WHITE);

        EndDrawing();
    }
    
    return 0;
}