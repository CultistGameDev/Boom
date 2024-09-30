#include "light.hpp"

using namespace BH;

static int lightsCount = 0; // Current amount of created lights

Light::Light(LightType type, Vector3 position, Vector3 target, Color color,
             Shader shader) {
    if (lightsCount < MAX_LIGHTS) {
        enabled = true;
        type = type;
        position = position;
        target = target;
        color = color;

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

        Update(shader);

        lightsCount++;
    }
}

void Light::Update(Shader shader) {
    //    SetShaderValue(shader, enabledLoc, &enabled, SHADER_UNIFORM_INT);
    //    SetShaderValue(shader, typeLoc, &type, SHADER_UNIFORM_INT);
    //
    //    float position[3] = {position.x, position.y, position.z};
    //    SetShaderValue(shader, positionLoc, position, SHADER_UNIFORM_VEC3);
    //
    //    // Send to shader light target position values
    //    float target[3] = {target.x, target.y, target.z};
    //    SetShaderValue(shader, targetLoc, target, SHADER_UNIFORM_VEC3);
    //
    //    // Send to shader light color values
    //    float color[4] = {(float)color.r / (float)255, (float)color.g /
    //    (float)255,
    //                      (float)color.b / (float)255, (float)color.a /
    //                      (float)255};
    //    SetShaderValue(shader, colorLoc, color, SHADER_UNIFORM_VEC4);
}
