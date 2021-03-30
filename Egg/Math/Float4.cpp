#include "Float4.h"
#include <cmath>
#include <cfloat>

namespace Egg {
    namespace Math {

        Float4::Float4(float x, float y, float z, float w) : x { x }, y { y }, z { z }, w { w }{ }

        Float4::Float4(float x, float y, const Float2 & zw) : x { x }, y { y }, z { zw.x }, w { zw.y }{ }

        Float4::Float4(const Float2 & xy, const Float2 & zw) : x { xy.x }, y { xy.y }, z { zw.x }, w { zw.y }{ }

        Float4::Float4(const Float2 & xy, float z, float w) : x { xy.x }, y { xy.y }, z { z }, w { w }{ }

        Float4::Float4(const Float3 & xyz, float w) : x { xyz.x }, y { xyz.y }, z { xyz.z }, w { w }{ }

        Float4::Float4(float x, const Float3 & yzw) : x { x }, y { yzw.x }, z { yzw.y }, w { yzw.z }{ }

        Float4::Float4(const Float4 & xyzw) : x { xyzw.x }, y { xyzw.y }, z { xyzw.z }, w { xyzw.w }{ }

        Float4::Float4() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, w{ 0.0f }{ }

        Float4 & Float4::operator=(const Float4 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            this->w = rhs.w;
            return *this;
        }

        Float4 & Float4::operator=(float rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            this->w = rhs;
            return *this;
        }

        Float4 & Float4::operator+=(const Float4 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            this->w += rhs.w;
            return *this;
        }

        Float4 & Float4::operator+=(float rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            this->z += rhs;
            this->w += rhs;
            return *this;
        }

        Float4 & Float4::operator-=(const Float4 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            this->w -= rhs.w;
            return *this;
        }

        Float4 & Float4::operator-=(float rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            this->z -= rhs;
            this->w -= rhs;
            return *this;
        }

        Float4 & Float4::operator/=(const Float4 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;
            this->w /= rhs.w;
            return *this;
        }

        Float4 & Float4::operator/=(float rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            this->w /= rhs;
            return *this;
        }

        Float4 & Float4::operator*=(const Float4 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;
            this->w *= rhs.w;
            return *this;
        }

        Float4 & Float4::operator*=(float rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            this->w *= rhs;
            return *this;
        }

        Float4 Float4::operator*(const Float4 & rhs) const noexcept {
            return Float4 { this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w };
        }

        Float4 Float4::operator/(const Float4 & rhs) const noexcept {
            return Float4 { this->x / rhs.x, this->y / rhs.y, this->z / rhs.z, this->w / rhs.w };
        }

        Float4 Float4::operator+(const Float4 & rhs) const noexcept {
            return Float4 { this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w };
        }

        Float4 Float4::operator-(const Float4 & rhs) const noexcept {
            return Float4 { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w };
        }

        Float4 Float4::Abs() const noexcept {
            return Float4 { ::abs(this->x), ::abs(this->y), ::abs(this->z), ::abs(this->w) };
        }

        Float4 Float4::Acos() const noexcept {
            return Float4 { ::acos(this->x), ::acos(this->y), ::acos(this->z), ::acos(this->w) };
        }

        Float4 Float4::Asin() const noexcept {
            return Float4 { ::asin(this->x), ::asin(this->y), ::asin(this->z), ::asin(this->w) };
        }

        Float4 Float4::Atan() const noexcept {
            return Float4 { ::atan(this->x), ::atan(this->y), ::atan(this->z), ::atan(this->w) };
        }

        Float4 Float4::Cos() const noexcept {
            return Float4 { ::cos(this->x), ::cos(this->y), ::cos(this->z), ::cos(this->w) };
        }

        Float4 Float4::Sin() const noexcept {
            return Float4 { ::sin(this->x), ::sin(this->y), ::sin(this->z), ::sin(this->w) };
        }

        Float4 Float4::Cosh() const noexcept {
            return Float4 { ::cosh(this->x), ::cosh(this->y), ::cosh(this->z), ::cosh(this->w) };
        }

        Float4 Float4::Sinh() const noexcept {
            return Float4 { ::sinh(this->x), ::sinh(this->y), ::sinh(this->z), ::sinh(this->w) };
        }

        Float4 Float4::Tan() const noexcept {
            return Float4 { ::tan(this->x), ::tan(this->y), ::tan(this->z), ::tan(this->w) };
        }

        Float4 Float4::Exp() const noexcept {
            return Float4 { ::exp(this->x), ::exp(this->y), ::exp(this->z), ::exp(this->w) };
        }

        Float4 Float4::Log() const noexcept {
            return Float4 { ::log(this->x), ::log(this->y), ::log(this->z), ::log(this->w) };
        }

        Float4 Float4::Log10() const noexcept {
            return Float4 { ::log10(this->x), ::log10(this->y), ::log10(this->z), ::log10(this->w) };
        }

        Float4 Float4::Fmod(const Float4 & rhs) const noexcept {
            return Float4 { ::fmod(this->x, rhs.x), ::fmod(this->y, rhs.y), ::fmod(this->z, rhs.z), ::fmod(this->w, rhs.w) };
        }

        Float4 Float4::Atan2(const Float4 & rhs) const noexcept {
            return Float4 { ::atan2(this->x, rhs.x), ::atan2(this->y, rhs.y), ::atan2(this->z, rhs.z), ::atan2(this->w, rhs.w) };
        }

        Float4 Float4::Pow(const Float4 & rhs) const noexcept {
            return Float4 { ::pow(this->x, rhs.x), ::pow(this->y, rhs.y), ::pow(this->z, rhs.z), ::pow(this->w, rhs.w) };
        }

        Float4 Float4::Sqrt() const noexcept {
            return Float4 { ::sqrtf(this->x), ::sqrtf(this->y), ::sqrtf(this->z), ::sqrtf(this->w) };
        }

        Float4 Float4::Clamp(const Float4 & low, const Float4 & high) const noexcept {
            return Float4 { (x < low.x) ? low.x: ((x > high.x) ? high.x :x), (y < low.y) ? low.y: ((y > high.y) ? high.y :y), (z < low.z) ? low.z: ((z > high.z) ? high.z :z), (w < low.w) ? low.w: ((w > high.w) ? high.w :w) };
        }

        float Float4::Dot(const Float4 & rhs) const noexcept {
            return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
        }

        Float4 Float4::Sign() const noexcept {
            return Float4 { (x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f), (y > 0.0f) ? 1.0f : ((y < 0.0f) ? -1.0f : 0.0f), (z > 0.0f) ? 1.0f : ((z < 0.0f) ? -1.0f : 0.0f), (w > 0.0f) ? 1.0f : ((w < 0.0f) ? -1.0f : 0.0f) };
        }

        Int4 Float4::Round() const noexcept {
            return Int4 { (int)(x + 0.5f), (int)(y + 0.5f), (int)(z + 0.5f), (int)(w + 0.5f) }; 
        }

        Float4 Float4::Saturate() const noexcept {
            return Clamp(Float4 { 0, 0, 0, 0 }, Float4 { 1, 1, 1, 1 });
        }

        float Float4::LengthSquared() const noexcept {
            return Dot(*this);
        }

        float Float4::Length() const noexcept {
            return ::sqrtf(LengthSquared());
        }

        Float4 Float4::Normalize() const noexcept {
            float len = Length();
             return Float4 { x / len , y / len , z / len , w / len  };
        }

        Bool4 Float4::IsNan() const noexcept {
            return Bool4 { std::isnan(x), std::isnan(y), std::isnan(z), std::isnan(w) };
        }

        Bool4 Float4::IsFinite() const noexcept {
            return Bool4 { std::isfinite(x), std::isfinite(y), std::isfinite(z), std::isfinite(w) };
        }

        Bool4 Float4::IsInfinite() const noexcept {
            return Bool4 { !std::isfinite(x), !std::isfinite(y), !std::isfinite(z), !std::isfinite(w) };
        }

        Float4 Float4::operator-() const noexcept {
            return Float4 { -x, -y, -z, -w };
        }

        Float4 Float4::operator%(const Float4 & rhs) const noexcept {
            return Float4 { ::fmodf(x, rhs.x), ::fmodf(y, rhs.y), ::fmodf(z, rhs.z), ::fmodf(w, rhs.w) };
        }

        Float4 & Float4::operator%=(const Float4 & rhs) noexcept {
            x = ::fmodf(x, rhs.x);
            y = ::fmodf(y, rhs.y);
            z = ::fmodf(z, rhs.z);
            w = ::fmodf(w, rhs.w);
            return *this;
        }

        Int4 Float4::Ceil() const noexcept {
            return Int4 { (int)::ceil(x), (int)::ceil(y), (int)::ceil(z), (int)::ceil(w) };
        }

        Int4 Float4::Floor() const noexcept {
            return Int4 { (int)::floor(x), (int)::floor(y), (int)::floor(z), (int)::floor(w) };
        }

        Float4 Float4::Exp2() const noexcept {
            return Float4 { ::pow(2.0f,x), ::pow(2.0f,y), ::pow(2.0f,z), ::pow(2.0f,w) };
        }

        Int4 Float4::Trunc() const noexcept {
            return Int4 { (int)x, (int)y, (int)z, (int)w };
        }

        float Float4::Distance(const Float4 & rhs) const noexcept {
            return (( Float4 )(*this) - rhs).Length();
        }

        Bool4 Float4::operator<(const Float4 & rhs) const noexcept {
            return Bool4 { x < rhs.x, y < rhs.y, z < rhs.z, w < rhs.w };
        }

        Bool4 Float4::operator>(const Float4 & rhs) const noexcept {
            return Bool4 { x > rhs.x, y > rhs.y, z > rhs.z, w > rhs.w };
        }

        Bool4 Float4::operator!=(const Float4 & rhs) const noexcept {
            return Bool4 { x != rhs.x, y != rhs.y, z != rhs.z, w != rhs.w };
        }

        Bool4 Float4::operator==(const Float4 & rhs) const noexcept {
            return Bool4 { x == rhs.x, y == rhs.y, z == rhs.z, w == rhs.w };
        }

        Bool4 Float4::operator>=(const Float4 & rhs) const noexcept {
            return Bool4 { x >= rhs.x, y >= rhs.y, z >= rhs.z, w >= rhs.w };
        }

        Bool4 Float4::operator<=(const Float4 & rhs) const noexcept {
            return Bool4 { x <= rhs.x, y <= rhs.y, z <= rhs.z, w <= rhs.w };
        }

        Float4 Float4::Random(float lower, float upper) noexcept {
            float range = upper - lower;
            return Float4 {  rand() * range / RAND_MAX + lower,
             rand() * range / RAND_MAX + lower,
             rand() * range / RAND_MAX + lower,
             rand() * range / RAND_MAX + lower };
        }

        Float4 Float4::operator+(float v) const noexcept {
            return Float4 { x + v , y + v , z + v , w + v  };
        }

        Float4 Float4::operator-(float v) const noexcept {
            return Float4 { x - v , y - v , z - v , w - v  };
        }

        Float4 Float4::operator*(float v) const noexcept {
            return Float4 { x * v , y * v , z * v , w * v  };
        }

        Float4 Float4::operator/(float v) const noexcept {
            return Float4 { x / v , y / v , z / v , w / v  };
        }

        Float4 Float4::operator%(float v) const noexcept {
            return Float4 { ::fmodf(x, v), ::fmodf(y, v), ::fmodf(z, v), ::fmodf(w, v) };
        }

        Float4 Float4::operator!() const noexcept {
            return Float4 { -x, -y, -z, w }; 
        }

        const Float4 Float4::UnitX { 1.0f, 0.0f, 0.0f, 0.0f };
        const Float4 Float4::UnitY { 0.0f, 1.0f, 0.0f, 0.0f };
        const Float4 Float4::UnitZ { 0.0f, 0.0f, 1.0f, 0.0f };
        const Float4 Float4::UnitW { 0.0f, 0.0f, 0.0f, 1.0f };
        const Float4 Float4::Zero { 0.0f, 0.0f, 0.0f, 0.0f };
        const Float4 Float4::One { 1.0f, 1.0f, 1.0f, 1.0f };
        const Float4 Float4::Identity { 0.0f, 0.0f, 0.0f, 1.0f };
    }
}

