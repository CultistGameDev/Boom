#include <raylib-cpp.hpp>

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

    raylib::Camera3D camera;
    camera.SetPosition(Vector3(5, 5, 5));
    camera.SetTarget(Vector3(0, 0, 0));
    camera.SetUp(Vector3(0, 1, 0));
    camera.SetFovy(90);
    camera.SetProjection(CameraProjection::CAMERA_PERSPECTIVE);

    while (!window->ShouldClose()) {
        UpdateCamera(&camera, CameraMode::CAMERA_CUSTOM);

        window->BeginDrawing();
        window->ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawCube(Vector3(0, -10, 0), 20, 1, 20, BLUE);
        DrawCube(Vector3(3, -4, -2), 2, 2, 2, GREEN);
        DrawCube(Vector3(-2, -4, 0), 1, 1, 1, RED);
        EndMode3D();

        window->EndDrawing();
    }
#endif

    return 0;
}