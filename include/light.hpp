#ifndef BOOMHEADSHOT_LIGHT_HPP
#define BOOMHEADSHOT_LIGHT_HPP

#include <raylib-cpp.hpp>

namespace BH {

constexpr int MAX_LIGHTS = 4;
enum class LightType { LIGHT_DIRECTIONAL = 0, LIGHT_POINT };

// Light data
class Light {
  public:
    Light(LightType type, Vector3 position, Vector3 target, Color color,
          Shader shader);

    void Update(Shader shader);

    LightType type;
    bool enabled;
    Vector3 position;
    Vector3 target;
    Color color;
    float attenuation;

    // Shader locations
    int enabledLoc;
    int typeLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int attenuationLoc;
};
} // namespace BH
// Light type

#endif