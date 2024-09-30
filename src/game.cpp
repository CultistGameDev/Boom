#include <raylib-cpp.hpp>

// Get float value from text
// NOTE: This function replaces atof() [stdlib.h]
// WARNING: Only '.' character is understood as decimal poi
static float TextToFloat(const char *text) {
    float value = 0.0f;
    float sign = 1.0f;

    if ((text[0] == '+') || (text[0] == '-')) {
        if (text[0] == '-')
            sign = -1.0f;
        text++;
    }

    int i = 0;
    for (; ((text[i] >= '0') && (text[i] <= '9')); i++)
        value = value * 10.0f + (float)(text[i] - '0');

    if (text[i++] != '.')
        value *= sign;
    else {
        float divisor = 10.0f;
        for (; ((text[i] >= '0') && (text[i] <= '9')); i++) {
            value += ((float)(text[i] - '0')) / divisor;
            divisor = divisor * 10.0f;
        }
    }

    return value;
}

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <memory>

#include "text.hpp"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

int screenWidth = 800;
int screenHeight = 450;

int main(int argc, char **argv) {
    const auto window = std::make_unique<raylib::Window>(
        screenWidth, screenHeight, "Boom Headshot");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    const BH::Text text("Hello World!", screenWidth / 2, screenHeight / 2, 32);

    DisableCursor();

    raylib::Camera3D camera;
    camera.SetPosition(Vector3(5, 5, 5));
    camera.SetTarget(Vector3(0, 0, 0));
    camera.SetUp(Vector3(0, 1, 0));
    camera.SetFovy(90);
    camera.SetProjection(CameraProjection::CAMERA_PERSPECTIVE);

    while (!window->ShouldClose()) {
        UpdateCamera(&camera, CameraMode::CAMERA_CUSTOM);

        window->BeginDrawing();
        window->ClearBackground(WHITE);

        BeginMode3D(camera);
        DrawCube(Vector3(0, -10, 0), 20, 1, 20, BLUE);
        DrawCube(Vector3(3, -4, -2), 2, 2, 2, GREEN);
        DrawCube(Vector3(-2, -4, 0), 1, 1, 1, RED);
        EndMode3D();

        GuiMessageBox((Rectangle){85, 70, 250.0f, 100.0f}, "#191#Message Box",
                      "Hi! This is a message!", "Nice;Cool");

        window->DrawFPS();

        window->EndDrawing();
    }
#endif

    return 0;
}