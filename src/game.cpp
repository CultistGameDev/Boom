#include <iostream>

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

    BH::Vec2f v(0.1f, 1.2f);
    v.X(2.4f);

    raylib::Camera3D camera;
    camera.SetPosition(Vector3(2.0f, 4.0f, 6.0f));
    camera.SetTarget(Vector3(0.0f, 0.5f, 0.0f));
    camera.SetUp(Vector3(0.0f, 1.0f, 0.0f));
    camera.SetFovy(45);
    camera.SetProjection(CameraProjection::CAMERA_PERSPECTIVE);

    BH::Color4f ambient{0.1f, 0.1f, 0.1f, 1.0f};

    const Shader& shader =
        LoadShader("data/shaders/lighting.vert", "data/shaders/lighting.frag");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, ambient.Data(), SHADER_UNIFORM_VEC4);
    std::vector<BH::Light> lights;
    lights.reserve(4);
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{-2, 1, -2},
                        BH::Vec3f(), BH::Color4i{253, 249, 0, 255}, shader);
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{2, 1, 2},
                        BH::Vec3f(), BH::Color4i{253, 249, 0, 255}, shader);
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{-2, 1, 2},
                        BH::Vec3f(), BH::Color4i{230, 41, 55, 255}, shader);
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{2, 1, -2},
                        BH::Vec3f(), BH::Color4i{41, 230, 55, 255}, shader);

    bool showMessageBox = true;

    SetTargetFPS(60);

    while (!window->ShouldClose()) {
        UpdateCamera(&camera, CameraMode::CAMERA_ORBITAL);

        BH::Vec3f cameraPos{camera.position.x, camera.position.y,
                            camera.position.z};
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW],
                       cameraPos.Data(), SHADER_UNIFORM_VEC3);

        for (const BH::Light& light : lights) {
            light.Update(shader);
        }

        window->BeginDrawing();
        window->ClearBackground(WHITE);

        BeginMode3D(camera);
        BeginShaderMode(shader);
        DrawPlane(Vector3Zero(), (Vector2){10.0, 10.0}, WHITE);
        DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);
        EndShaderMode();
        for (int i = 0; i < 4; i++) {
            const BH::Light& light = lights[i];
            if (lights[i].enabled) {
                DrawSphereEx(light.position.ToVector3(), 0.2f, 8, 8,
                             (Color){(unsigned char)light.color.R(),
                                     (unsigned char)light.color.G(),
                                     (unsigned char)light.color.B(),
                                     (unsigned char)light.color.A()});
            } else {
                DrawSphereWires(
                    light.position.ToVector3(), 0.2f, 8, 8,
                    ColorAlpha((Color){(unsigned char)light.color.R(),
                                       (unsigned char)light.color.G(),
                                       (unsigned char)light.color.B(),
                                       (unsigned char)light.color.A()},
                               0.3));
            }
        }

        DrawGrid(10, 1.0f);

        EndMode3D();

        window->EndDrawing();
    }
#endif

    UnloadShader(shader);
    window->Close();

    return 0;
}