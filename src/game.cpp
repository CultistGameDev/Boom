#include <vector>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#include "color.hpp"
#include "light.hpp"
#include "vector.hpp"

constexpr int screenWidth = 800;
constexpr int screenHeight = 450;

int main(int argc, char **argv) {
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else

    BH::Vec2f v(0.1f, 1.2f);
    v.X(2.4f);

    BH::Color4f ambient{0.1f, 0.1f, 0.1f, 1.0f};

    std::vector<BH::Light> lights;
    lights.reserve(4);
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{-2, 1, -2},
                        BH::Vec3f(), BH::Color4i{253, 249, 0, 255});
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{2, 1, 2},
                        BH::Vec3f(), BH::Color4i{253, 249, 0, 255});
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{-2, 1, 2},
                        BH::Vec3f(), BH::Color4i{230, 41, 55, 255});
    lights.emplace_back(BH::LightType::LIGHT_POINT, BH::Vec3f{2, 1, -2},
                        BH::Vec3f(), BH::Color4i{41, 230, 55, 255});

#endif
    return 0;
}
