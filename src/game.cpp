#include <array>

#include <raylib-cpp.hpp>

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

#include "vector.hpp"

constexpr int screenWidth = 800;
constexpr int screenHeight = 450;

int main(int argc, char **argv) {
    const auto window = std::make_unique<raylib::Window>(
        screenWidth, screenHeight, "Boom Headshot");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    BH::Vec2f v(0.1f, 1.2f);
    v.X(2.4f);

    raylib::Camera3D camera;
    camera.SetPosition(Vector3(5, 5, 5));
    camera.SetTarget(Vector3(0, 0, 0));
    camera.SetUp(Vector3(0, 1, 0));
    camera.SetFovy(90);
    camera.SetProjection(CameraProjection::CAMERA_PERSPECTIVE);

    std::array<float, 4> ambient{0.1f, 0.1f, 0.1f, 1.0f};

    Shader shader =
        LoadShader("data/shaders/lighting.vert", "data/shaders/lighting.frag");
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, ambient.data(), SHADER_UNIFORM_VEC4);

    bool showMessageBox = true;

    while (!window->ShouldClose()) {
        if (!showMessageBox) {
            UpdateCamera(&camera, CameraMode::CAMERA_CUSTOM);
        }

        window->BeginDrawing();
        window->ClearBackground(WHITE);

        BeginMode3D(camera);
        BeginShaderMode(shader);
        DrawCube(Vector3(0, -10, 0), 20, 1, 20, BLUE);
        DrawCube(Vector3(3, -4, -2), 2, 2, 2, GREEN);
        DrawCube(Vector3(-2, -4, 0), 1, 1, 1, RED);
        EndShaderMode();
        EndMode3D();

        if (showMessageBox) {
            if (GuiMessageBox((Rectangle){85, 70, 250.0f, 100.0f},
                              "#191#Message Box", "Hi! This is a message!",
                              "Nice;Cool") >= 0) {
                showMessageBox = false;
                DisableCursor();
            }
        }

        DrawText(TextFormat("%.1f %.1f", v.X(), v.Y()), 0, 0, 32, BLACK);

        window->EndDrawing();
    }
#endif

    UnloadShader(shader);
    window->Close();

    return 0;
}