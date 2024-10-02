#include "light.hpp"

#include <iostream>
#include <utility>

using namespace BH;

static int lightsCount = 0; // Current amount of created lights

Light::Light(LightType type, Vec3f position, Vec3f target, Color4i color)
    : type(type), position(std::move(position)), target(std::move(target)),
      color(std::move(color)) {
}

void Light::Update() const {}
