#include "raylib-cpp.hpp"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

int screenWidth = 800;
int screenHeight = 450;

void UpdateDrawFrame(void);     // Update and Draw one frame

int main()
{
    raylib::Window window(screenWidth, screenHeight, "Boom Headsht");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    while (!window.ShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello World!", screenWidth / 2 - 16, screenHeight / 2 - 16, 32, BLACK);

        EndDrawing();
    }
#endif

    return 0;
}