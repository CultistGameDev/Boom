#include "light.hpp"

#include <iostream>
#include <utility>

using namespace BH;

static int lightsCount = 0; // Current amount of created lights

Light::Light(LightType type, Vec3f position, Vec3f target, Color4i color,
             const Shader& shader)
    : type(type), position(std::move(position)), target(std::move(target)),
      color(std::move(color)) {
    if (lightsCount < MAX_LIGHTS) {
        enabled = true;

        enabledLoc = GetShaderLocation(
            shader, TextFormat("lights[%i].enabled", lightsCount));
        typeLoc = GetShaderLocation(shader,
                                    TextFormat("lights[%i].type", lightsCount));
        positionLoc = GetShaderLocation(
            shader, TextFormat("lights[%i].position", lightsCount));
        targetLoc = GetShaderLocation(
            shader, TextFormat("lights[%i].target", lightsCount));
        colorLoc = GetShaderLocation(
            shader, TextFormat("lights[%i].color", lightsCount));

        attenuation = 0;

        Update(shader);

        lightsCount++;
    }
}

void Light::Update(const Shader& shader) const {
    SetShaderValue(shader, enabledLoc, &enabled, SHADER_UNIFORM_INT);
    SetShaderValue(shader, typeLoc, &type, SHADER_UNIFORM_INT);

    SetShaderValue(shader, positionLoc, position.Data(), SHADER_UNIFORM_VEC3);

    SetShaderValue(shader, targetLoc, target.Data(), SHADER_UNIFORM_VEC3);

    auto normcolor = BH::Color4f{static_cast<float>(color.R()) / 255.0f,
                                 static_cast<float>(color.G()) / 255.0f,
                                 static_cast<float>(color.B()) / 255.0f,
                                 static_cast<float>(color.A()) / 255.0f};

    SetShaderValue(shader, colorLoc, normcolor.Data(), SHADER_UNIFORM_VEC4);
}
