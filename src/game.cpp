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

#include "color.hpp"
#include "light.hpp"
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
    camera.SetPosition(Vector3(2.0f, 4.0f, 6.0f));
    camera.SetTarget(Vector3(0.0f, 0.5f, 0.0f));
    camera.SetUp(Vector3(0.0f, 1.0f, 0.0f));
    camera.SetFovy(45);
    camera.SetProjection(CameraProjection::CAMERA_PERSPECTIVE);

    BH::Colorf ambient{0.1f, 0.1f, 0.1f, 1.0f};

    const Shader& shader =
        LoadShader("data/shaders/lighting.vert", "data/shaders/lighting.frag");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, ambient.Data(), SHADER_UNIFORM_VEC4);
    std::vector<BH::Light> lights;
    lights.reserve(4);
    lights.emplace_back(BH::LightType::LIGHT_POINT,
                        BH::Vec3f{-2.0f, 1.0f, -2.0f}, BH::Vec3f(),
                        BH::Colori{253, 249, 0, 255}, shader);
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{2.0f, 1.0f, 2.0f},
                        BH::Vec3f(), BH::Colori{253, 249, 0, 255}, shader);
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{2.0f, 1.0f, 2.0f},
                        BH::Vec3f(), BH::Colori{230, 41, 55, 255}, shader);
    lights.emplace_back(BH::LightType::LIGHT_POINT,
                        BH::Vec3f{-2.0f, 1.0f, 2.0f}, BH::Vec3f(),
                        BH::Colori{41, 230, 55, 255}, shader);

    bool showMessageBox = true;

    for (int i = 0; i < 4; i++) {
        lights[i].Update(shader);
    }

    while (!window->ShouldClose()) {
        if (!showMessageBox) {
            UpdateCamera(&camera, CameraMode::CAMERA_CUSTOM);
        }

        BH::Vec3f cameraPos{camera.position.x, camera.position.y,
                            camera.position.z};
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW],
                       cameraPos.Data(), SHADER_UNIFORM_VEC3);

        window->BeginDrawing();
        window->ClearBackground(WHITE);

        BeginMode3D(camera);
        BeginShaderMode(shader);
        DrawPlane(Vector3Zero(), (Vector2){10.0, 10.0}, WHITE);
        DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);
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

        window->EndDrawing();
    }
#endif

    UnloadShader(shader);
    window->Close();

    return 0;
}