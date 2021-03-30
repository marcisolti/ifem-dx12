#include "Float3.h"
#include <cmath>
#include <cfloat>

namespace Egg {
    namespace Math {

        Float3::Float3(float x, float y, float z) : x { x }, y { y }, z { z }{ }

        Float3::Float3(float x, const Float2 & yz) : x { x }, y { yz.x }, z { yz.y }{ }

        Float3::Float3(const Float2 & xy, float z) : x { xy.x }, y { xy.y }, z { z }{ }

        Float3::Float3(const Float3 & xyz) : x { xyz.x }, y { xyz.y }, z { xyz.z }{ }

        Float3::Float3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }{ }

		Float3::Float3(float x) :x { x }, y { x },z { x } {  }

        Float3 & Float3::operator=(const Float3 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            return *this;
        }

        Float3 & Float3::operator=(float rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            return *this;
        }

        Float3 & Float3::operator+=(const Float3 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            return *this;
        }

        Float3 & Float3::operator+=(float rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            this->z += rhs;
            return *this;
        }

        Float3 & Float3::operator-=(const Float3 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            return *this;
        }

        Float3 & Float3::operator-=(float rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            this->z -= rhs;
            return *this;
        }

        Float3 & Float3::operator/=(const Float3 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;
            return *this;
        }

        Float3 & Float3::operator/=(float rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            return *this;
        }

        Float3 & Float3::operator*=(const Float3 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;
            return *this;
        }

        Float3 & Float3::operator*=(float rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            return *this;
        }

        Float3 Float3::operator*(const Float3 & rhs) const noexcept {
            return Float3 { this->x * rhs.x, this->y * rhs.y, this->z * rhs.z };
        }

        Float3 Float3::operator/(const Float3 & rhs) const noexcept {
            return Float3 { this->x / rhs.x, this->y / rhs.y, this->z / rhs.z };
        }

        Float3 Float3::operator+(const Float3 & rhs) const noexcept {
            return Float3 { this->x + rhs.x, this->y + rhs.y, this->z + rhs.z };
        }

        Float3 Float3::operator-(const Float3 & rhs) const noexcept {
            return Float3 { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z };
        }

        Float3 Float3::Abs() const noexcept {
            return Float3 { ::abs(this->x), ::abs(this->y), ::abs(this->z) };
        }

        Float3 Float3::Acos() const noexcept {
            return Float3 { ::acos(this->x), ::acos(this->y), ::acos(this->z) };
        }

        Float3 Float3::Asin() const noexcept {
            return Float3 { ::asin(this->x), ::asin(this->y), ::asin(this->z) };
        }

        Float3 Float3::Atan() const noexcept {
            return Float3 { ::atan(this->x), ::atan(this->y), ::atan(this->z) };
        }

        Float3 Float3::Cos() const noexcept {
            return Float3 { ::cos(this->x), ::cos(this->y), ::cos(this->z) };
        }

        Float3 Float3::Sin() const noexcept {
            return Float3 { ::sin(this->x), ::sin(this->y), ::sin(this->z) };
        }

        Float3 Float3::Cosh() const noexcept {
            return Float3 { ::cosh(this->x), ::cosh(this->y), ::cosh(this->z) };
        }

        Float3 Float3::Sinh() const noexcept {
            return Float3 { ::sinh(this->x), ::sinh(this->y), ::sinh(this->z) };
        }

        Float3 Float3::Tan() const noexcept {
            return Float3 { ::tan(this->x), ::tan(this->y), ::tan(this->z) };
        }

        Float3 Float3::Exp() const noexcept {
            return Float3 { ::exp(this->x), ::exp(this->y), ::exp(this->z) };
        }

        Float3 Float3::Log() const noexcept {
            return Float3 { ::log(this->x), ::log(this->y), ::log(this->z) };
        }

        Float3 Float3::Log10() const noexcept {
            return Float3 { ::log10(this->x), ::log10(this->y), ::log10(this->z) };
        }

        Float3 Float3::Fmod(const Float3 & rhs) const noexcept {
            return Float3 { ::fmod(this->x, rhs.x), ::fmod(this->y, rhs.y), ::fmod(this->z, rhs.z) };
        }

        Float3 Float3::Atan2(const Float3 & rhs) const noexcept {
            return Float3 { ::atan2(this->x, rhs.x), ::atan2(this->y, rhs.y), ::atan2(this->z, rhs.z) };
        }

        Float3 Float3::Pow(const Float3 & rhs) const noexcept {
            return Float3 { ::pow(this->x, rhs.x), ::pow(this->y, rhs.y), ::pow(this->z, rhs.z) };
        }

        Float3 Float3::Sqrt() const noexcept {
            return Float3 { ::sqrtf(this->x), ::sqrtf(this->y), ::sqrtf(this->z) };
        }

        Float3 Float3::Clamp(const Float3 & low, const Float3 & high) const noexcept {
            return Float3 { (x < low.x) ? low.x: ((x > high.x) ? high.x :x), (y < low.y) ? low.y: ((y > high.y) ? high.y :y), (z < low.z) ? low.z: ((z > high.z) ? high.z :z) };
        }

        float Float3::Dot(const Float3 & rhs) const noexcept {
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        Float3 Float3::Sign() const noexcept {
            return Float3 { (x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f), (y > 0.0f) ? 1.0f : ((y < 0.0f) ? -1.0f : 0.0f), (z > 0.0f) ? 1.0f : ((z < 0.0f) ? -1.0f : 0.0f) };
        }

        Int3 Float3::Round() const noexcept {
            return Int3 { (int)(x + 0.5f), (int)(y + 0.5f), (int)(z + 0.5f) }; 
        }

        Float3 Float3::Saturate() const noexcept {
            return Clamp(Float3 { 0, 0, 0 }, Float3 { 1, 1, 1 });
        }

        float Float3::LengthSquared() const noexcept {
            return Dot(*this);
        }

        float Float3::Length() const noexcept {
            return ::sqrtf(LengthSquared());
        }

        Float3 Float3::Normalize() const noexcept {
            float len = Length();
             return Float3 { x / len , y / len , z / len  };
        }

        Bool3 Float3::IsNan() const noexcept {
            return Bool3 { std::isnan(x), std::isnan(y), std::isnan(z) };
        }

        Bool3 Float3::IsFinite() const noexcept {
            return Bool3 { std::isfinite(x), std::isfinite(y), std::isfinite(z) };
        }

        Bool3 Float3::IsInfinite() const noexcept {
            return Bool3 { !std::isfinite(x), !std::isfinite(y), !std::isfinite(z) };
        }

        Float3 Float3::operator-() const noexcept {
            return Float3 { -x, -y, -z };
        }

        Float3 Float3::operator%(const Float3 & rhs) const noexcept {
            return Float3 { ::fmodf(x, rhs.x), ::fmodf(y, rhs.y), ::fmodf(z, rhs.z) };
        }

        Float3 & Float3::operator%=(const Float3 & rhs) noexcept {
            x = ::fmodf(x, rhs.x);
            y = ::fmodf(y, rhs.y);
            z = ::fmodf(z, rhs.z);
            return *this;
        }

        Int3 Float3::Ceil() const noexcept {
            return Int3 { (int)::ceil(x), (int)::ceil(y), (int)::ceil(z) };
        }

        Int3 Float3::Floor() const noexcept {
            return Int3 { (int)::floor(x), (int)::floor(y), (int)::floor(z) };
        }

        Float3 Float3::Exp2() const noexcept {
            return Float3 { ::pow(2.0f,x), ::pow(2.0f,y), ::pow(2.0f,z) };
        }

        Int3 Float3::Trunc() const noexcept {
            return Int3 { (int)x, (int)y, (int)z };
        }

        float Float3::Distance(const Float3 & rhs) const noexcept {
            return (( Float3 )(*this) - rhs).Length();
        }

        Bool3 Float3::operator<(const Float3 & rhs) const noexcept {
            return Bool3 { x < rhs.x, y < rhs.y, z < rhs.z };
        }

        Bool3 Float3::operator>(const Float3 & rhs) const noexcept {
            return Bool3 { x > rhs.x, y > rhs.y, z > rhs.z };
        }

        Bool3 Float3::operator!=(const Float3 & rhs) const noexcept {
            return Bool3 { x != rhs.x, y != rhs.y, z != rhs.z };
        }

        Bool3 Float3::operator==(const Float3 & rhs) const noexcept {
            return Bool3 { x == rhs.x, y == rhs.y, z == rhs.z };
        }

        Bool3 Float3::operator>=(const Float3 & rhs) const noexcept {
            return Bool3 { x >= rhs.x, y >= rhs.y, z >= rhs.z };
        }

        Bool3 Float3::operator<=(const Float3 & rhs) const noexcept {
            return Bool3 { x <= rhs.x, y <= rhs.y, z <= rhs.z };
        }

        Float3 Float3::Random(float lower, float upper) noexcept {
            float range = upper - lower;
            return Float3 {  rand() * range / RAND_MAX + lower,
             rand() * range / RAND_MAX + lower,
             rand() * range / RAND_MAX + lower };
        }

        Float3 Float3::operator+(float v) const noexcept {
            return Float3 { x + v , y + v , z + v  };
        }

        Float3 Float3::operator-(float v) const noexcept {
            return Float3 { x - v , y - v , z - v  };
        }

        Float3 Float3::operator*(float v) const noexcept {
            return Float3 { x * v , y * v , z * v  };
        }

        Float3 Float3::operator/(float v) const noexcept {
            return Float3 { x / v , y / v , z / v  };
        }

        Float3 Float3::operator%(float v) const noexcept {
            return Float3 { ::fmodf(x, v), ::fmodf(y, v), ::fmodf(z, v) };
        }

        Float3 Float3::Cross(const Float3 & rhs) const noexcept {
            return Float3 { y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x };
        }

        const Float3 Float3::UnitX { 1.0f, 0.0f, 0.0f };
        const Float3 Float3::UnitY { 0.0f, 1.0f, 0.0f };
        const Float3 Float3::UnitZ { 0.0f, 0.0f, 1.0f };
        const Float3 Float3::Zero { 0.0f, 0.0f, 0.0f };
        const Float3 Float3::One { 1.0f, 1.0f, 1.0f };
        const Float3 Float3::Black { 0.0f, 0.0f, 0.0f };
        const Float3 Float3::Navy { 0.0f, 0.0f, 0.5f };
        const Float3 Float3::Blue { 0.0f, 0.0f, 1.0f };
        const Float3 Float3::DarkGreen { 0.0f, 0.5f, 0.0f };
        const Float3 Float3::Teal { 0.0f, 0.5f, 0.5f };
        const Float3 Float3::Azure { 0.0f, 0.5f, 1.0f };
        const Float3 Float3::Green { 0.0f, 1.0f, 0.0f };
        const Float3 Float3::Cyan { 0.0f, 1.0f, 1.0f };
        const Float3 Float3::Maroon { 0.5f, 0.0f, 0.0f };
        const Float3 Float3::Purple { 0.5f, 0.0f, 0.5f };
        const Float3 Float3::SlateBlue { 0.5f, 0.0f, 1.0f };
        const Float3 Float3::Olive { 0.5f, 0.5f, 0.0f };
        const Float3 Float3::Gray { 0.5f, 0.5f, 0.5f };
        const Float3 Float3::Cornflower { 0.5f, 0.5f, 1.0f };
        const Float3 Float3::Aquamarine { 0.5f, 1.0f, 0.75f };
        const Float3 Float3::Red { 1.0f, 0.0f, 0.0f };
        const Float3 Float3::DeepPink { 1.0f, 0.0f, 0.5f };
        const Float3 Float3::Magenta { 1.0f, 0.0f, 1.0f };
        const Float3 Float3::Orange { 1.0f, 0.5f, 0.0f };
        const Float3 Float3::Coral { 1.0f, 0.5f, 0.31f };
        const Float3 Float3::Mallow { 1.0f, 0.5f, 1.0f };
        const Float3 Float3::Yellow { 1.0f, 1.0f, 0.0f };
        const Float3 Float3::Gold { 1.0f, 1.0f, 0.5f };
        const Float3 Float3::White { 1.0f, 1.0f, 1.0f };
        const Float3 Float3::Silver { 0.75f, 0.75f, 0.75f };
    }
}

