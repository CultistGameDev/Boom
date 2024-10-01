#ifndef BOOMHEADSHOT_VECTOR_HPP
#define BOOMHEADSHOT_VECTOR_HPP

#include <array>
#include <cassert>
#include <concepts>

namespace BH {
template <typename T, size_t N>
    requires(N > 0 && (std::integral<T> || std::floating_point<T>))
class Vec {
  public:
    Vec() = default;
    Vec(std::initializer_list<T> values) {
        assert(values.size() == N);

        int i = 0;
        for (const T& value : values) {
            m_Values[i] = value;
            ++i;
        }
    }
    Vec(const Vec<T, N>& other) noexcept { m_Values = other.m_Values; }
    Vec(Vec<T, N>&& other) noexcept { m_Values = std::move(other.m_Values); }

    T& operator[](size_t i) noexcept {
        assert(i >= 0 && i < N);
        return m_Values[i];
    }

    const T *Data() const noexcept { return m_Values.data(); }

  protected:
    std::array<T, N> m_Values;
};

template <typename T> class Vec2 : public Vec<T, 2> {
  public:
    Vec2() : Vec<T, 2>() {}
    Vec2(T x, T y) : Vec<T, 2>({x, y}) {}
    Vec2(std::initializer_list<T> values) : Vec<T, 2>(values) {}

    [[nodiscard]] T X() const { return this->m_Values[0]; }
    [[nodiscard]] T Y() const { return this->m_Values[1]; }
    T X(T value) { return this->m_Values[0] = value; }
    T Y(T value) { return this->m_Values[1] = value; }

    [[nodiscard]] T R() const { return this->m_Values[0]; }
    [[nodiscard]] T G() const { return this->m_Values[1]; }
    T R(T value) { return this->m_Values[0] = value; }
    T G(T value) { return this->m_Values[1] = value; }
};

template <typename T> class Vec3 : public Vec<T, 3> {
  public:
    Vec3() : Vec<T, 3>() {}
    Vec3(T x, T y, T z) : Vec<T, 3>({x, y, z}) {}
    Vec3(std::initializer_list<T> values) : Vec<T, 3>(values) {}

    Vec<T, 2>&& ToVec2() const { return Vec<T, 2>{X(), Y()}; }

    static Vec<T, 3>& Zero() { return Vec<T, 3>(); }

    [[nodiscard]] Vector3 ToVector2() const { return Vector3{X(), Y()}; }
    [[nodiscard]] Vector3 ToVector3() const { return Vector3{X(), Y(), Z()}; }

    [[nodiscard]] T X() const { return this->m_Values[0]; }
    [[nodiscard]] T Y() const { return this->m_Values[1]; }
    [[nodiscard]] T Z() const { return this->m_Values[2]; }
    T X(T value) { return this->m_Values[0] = value; }
    T Y(T value) { return this->m_Values[1] = value; }
    T Z(T value) { return this->m_Values[2] = value; }

    [[nodiscard]] T R() const { return this->m_Values[0]; }
    [[nodiscard]] T G() const { return this->m_Values[1]; }
    [[nodiscard]] T B() const { return this->m_Values[2]; }
    T R(T value) { return this->m_Values[0] = value; }
    T G(T value) { return this->m_Values[1] = value; }
    T B(T value) { return this->m_Values[2] = value; }
};

template <typename T> class Vec4 : public Vec<T, 4> {
  public:
    Vec4() : Vec<T, 4>() {}
    Vec4(T x, T y, T z, T w) : Vec<T, 4>({x, y, z, w}) {}
    Vec4(std::initializer_list<T> values) : Vec<T, 4>(values) {}

    Vec<T, 2>&& ToVec2() const { return Vec<T, 2>{X(), Y()}; }
    Vec<T, 3>&& ToVec3() const { return Vec<T, 2>{X(), Y(), Z()}; }

    [[nodiscard]] T X() const { return this->m_Values[0]; }
    [[nodiscard]] T Y() const { return this->m_Values[1]; }
    [[nodiscard]] T Z() const { return this->m_Values[2]; }
    [[nodiscard]] T W() const { return this->m_Values[3]; }
    T X(T value) { return this->m_Values[0] = value; }
    T Y(T value) { return this->m_Values[1] = value; }
    T Z(T value) { return this->m_Values[2] = value; }
    T W(T value) { return this->m_Values[3] = value; }

    [[nodiscard]] T R() const { return this->m_Values[0]; }
    [[nodiscard]] T G() const { return this->m_Values[1]; }
    [[nodiscard]] T B() const { return this->m_Values[2]; }
    [[nodiscard]] T A() const { return this->m_Values[3]; }
    T R(T value) { return this->m_Values[0] = value; }
    T G(T value) { return this->m_Values[1] = value; }
    T B(T value) { return this->m_Values[2] = value; }
    T A(T value) { return this->m_Values[3] = value; }
};

using Vec2f = Vec2<float>;
using Vec3f = Vec3<float>;
using Vec4f = Vec4<float>;

using Vec2i = Vec2<int>;
using Vec3i = Vec3<int>;
using Vec4i = Vec4<int>;
} // namespace BH

#endif // BOOMHEADSHOT_VECTOR_HPP
