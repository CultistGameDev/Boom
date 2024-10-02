#ifndef BOOMHEADSHOT_LIGHT_HPP
#define BOOMHEADSHOT_LIGHT_HPP

#include "color.hpp"
#include "vector.hpp"

namespace BH {

constexpr int MAX_LIGHTS = 4;
enum class LightType { LIGHT_DIRECTIONAL = 0, LIGHT_POINT };

// Light data
class Light {
  public:
    Light(LightType type, Vec3f position, Vec3f target, Color4i color);
    void Update() const;

    LightType type;
    bool enabled;
    Vec3f position;
    Vec3f target;
    Color4i color;
    float attenuation;

    int enabledLoc = 0;
    int typeLoc = 0;
    int positionLoc = 0;
    int targetLoc = 0;
    int colorLoc = 0;
    int attenuationLoc = 0;
};

} // namespace BH

#endif
