#include "Float2.h"
#include <cmath>
#include <cfloat>

namespace Egg {
    namespace Math {

        Float2::Float2(float x, float y) : x { x }, y { y }{ }

        Float2::Float2(const Float2 & xy) : x { xy.x }, y { xy.y }{ }

        Float2::Float2() : x{ 0.0f }, y{ 0.0f }{ }

        Float2 & Float2::operator=(const Float2 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            return *this;
        }

        Float2 & Float2::operator=(float rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            return *this;
        }

        Float2 & Float2::operator+=(const Float2 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        Float2 & Float2::operator+=(float rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            return *this;
        }

        Float2 & Float2::operator-=(const Float2 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            return *this;
        }

        Float2 & Float2::operator-=(float rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            return *this;
        }

        Float2 & Float2::operator/=(const Float2 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            return *this;
        }

        Float2 & Float2::operator/=(float rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            return *this;
        }

        Float2 & Float2::operator*=(const Float2 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            return *this;
        }

        Float2 & Float2::operator*=(float rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            return *this;
        }

        Float2 Float2::operator*(const Float2 & rhs) const noexcept {
            return Float2 { this->x * rhs.x, this->y * rhs.y };
        }

        Float2 Float2::operator/(const Float2 & rhs) const noexcept {
            return Float2 { this->x / rhs.x, this->y / rhs.y };
        }

        Float2 Float2::operator+(const Float2 & rhs) const noexcept {
            return Float2 { this->x + rhs.x, this->y + rhs.y };
        }

        Float2 Float2::operator-(const Float2 & rhs) const noexcept {
            return Float2 { this->x - rhs.x, this->y - rhs.y };
        }

        Float2 Float2::Abs() const noexcept {
            return Float2 { ::abs(this->x), ::abs(this->y) };
        }

        Float2 Float2::Acos() const noexcept {
            return Float2 { ::acos(this->x), ::acos(this->y) };
        }

        Float2 Float2::Asin() const noexcept {
            return Float2 { ::asin(this->x), ::asin(this->y) };
        }

        Float2 Float2::Atan() const noexcept {
            return Float2 { ::atan(this->x), ::atan(this->y) };
        }

        Float2 Float2::Cos() const noexcept {
            return Float2 { ::cos(this->x), ::cos(this->y) };
        }

        Float2 Float2::Sin() const noexcept {
            return Float2 { ::sin(this->x), ::sin(this->y) };
        }

        Float2 Float2::Cosh() const noexcept {
            return Float2 { ::cosh(this->x), ::cosh(this->y) };
        }

        Float2 Float2::Sinh() const noexcept {
            return Float2 { ::sinh(this->x), ::sinh(this->y) };
        }

        Float2 Float2::Tan() const noexcept {
            return Float2 { ::tan(this->x), ::tan(this->y) };
        }

        Float2 Float2::Exp() const noexcept {
            return Float2 { ::exp(this->x), ::exp(this->y) };
        }

        Float2 Float2::Log() const noexcept {
            return Float2 { ::log(this->x), ::log(this->y) };
        }

        Float2 Float2::Log10() const noexcept {
            return Float2 { ::log10(this->x), ::log10(this->y) };
        }

        Float2 Float2::Fmod(const Float2 & rhs) const noexcept {
            return Float2 { ::fmod(this->x, rhs.x), ::fmod(this->y, rhs.y) };
        }

        Float2 Float2::Atan2(const Float2 & rhs) const noexcept {
            return Float2 { ::atan2(this->x, rhs.x), ::atan2(this->y, rhs.y) };
        }

        Float2 Float2::Pow(const Float2 & rhs) const noexcept {
            return Float2 { ::pow(this->x, rhs.x), ::pow(this->y, rhs.y) };
        }

        Float2 Float2::Sqrt() const noexcept {
            return Float2 { ::sqrtf(this->x), ::sqrtf(this->y) };
        }

        Float2 Float2::Clamp(const Float2 & low, const Float2 & high) const noexcept {
            return Float2 { (x < low.x) ? low.x: ((x > high.x) ? high.x :x), (y < low.y) ? low.y: ((y > high.y) ? high.y :y) };
        }

        float Float2::Dot(const Float2 & rhs) const noexcept {
            return x * rhs.x + y * rhs.y;
        }

        Float2 Float2::Sign() const noexcept {
            return Float2 { (x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f), (y > 0.0f) ? 1.0f : ((y < 0.0f) ? -1.0f : 0.0f) };
        }

        Int2 Float2::Round() const noexcept {
            return Int2 { (int)(x + 0.5f), (int)(y + 0.5f) }; 
        }

        Float2 Float2::Saturate() const noexcept {
            return Clamp(Float2 { 0, 0 }, Float2 { 1, 1 });
        }

        float Float2::LengthSquared() const noexcept {
            return Dot(*this);
        }

        float Float2::Length() const noexcept {
            return ::sqrtf(LengthSquared());
        }

        Float2 Float2::Normalize() const noexcept {
            float len = Length();
             return Float2 { x / len , y / len  };
        }

        Bool2 Float2::IsNan() const noexcept {
            return Bool2 { std::isnan(x), std::isnan(y) };
        }

        Bool2 Float2::IsFinite() const noexcept {
            return Bool2 { std::isfinite(x), std::isfinite(y) };
        }

        Bool2 Float2::IsInfinite() const noexcept {
            return Bool2 { !std::isfinite(x), !std::isfinite(y) };
        }

        Float2 Float2::operator-() const noexcept {
            return Float2 { -x, -y };
        }

        Float2 Float2::operator%(const Float2 & rhs) const noexcept {
            return Float2 { ::fmodf(x, rhs.x), ::fmodf(y, rhs.y) };
        }

        Float2 & Float2::operator%=(const Float2 & rhs) noexcept {
            x = ::fmodf(x, rhs.x);
            y = ::fmodf(y, rhs.y);
            return *this;
        }

        Int2 Float2::Ceil() const noexcept {
            return Int2 { (int)::ceil(x), (int)::ceil(y) };
        }

        Int2 Float2::Floor() const noexcept {
            return Int2 { (int)::floor(x), (int)::floor(y) };
        }

        Float2 Float2::Exp2() const noexcept {
            return Float2 { ::pow(2.0f,x), ::pow(2.0f,y) };
        }

        Int2 Float2::Trunc() const noexcept {
            return Int2 { (int)x, (int)y };
        }

        float Float2::Distance(const Float2 & rhs) const noexcept {
            return (( Float2 )(*this) - rhs).Length();
        }

        Bool2 Float2::operator<(const Float2 & rhs) const noexcept {
            return Bool2 { x < rhs.x, y < rhs.y };
        }

        Bool2 Float2::operator>(const Float2 & rhs) const noexcept {
            return Bool2 { x > rhs.x, y > rhs.y };
        }

        Bool2 Float2::operator!=(const Float2 & rhs) const noexcept {
            return Bool2 { x != rhs.x, y != rhs.y };
        }

        Bool2 Float2::operator==(const Float2 & rhs) const noexcept {
            return Bool2 { x == rhs.x, y == rhs.y };
        }

        Bool2 Float2::operator>=(const Float2 & rhs) const noexcept {
            return Bool2 { x >= rhs.x, y >= rhs.y };
        }

        Bool2 Float2::operator<=(const Float2 & rhs) const noexcept {
            return Bool2 { x <= rhs.x, y <= rhs.y };
        }

        Float2 Float2::Random(float lower, float upper) noexcept {
            float range = upper - lower;
            return Float2 {  rand() * range / RAND_MAX + lower,
             rand() * range / RAND_MAX + lower };
        }

        Float2 Float2::operator+(float v) const noexcept {
            return Float2 { x + v , y + v  };
        }

        Float2 Float2::operator-(float v) const noexcept {
            return Float2 { x - v , y - v  };
        }

        Float2 Float2::operator*(float v) const noexcept {
            return Float2 { x * v , y * v  };
        }

        Float2 Float2::operator/(float v) const noexcept {
            return Float2 { x / v , y / v  };
        }

        Float2 Float2::operator%(float v) const noexcept {
            return Float2 { ::fmodf(x, v), ::fmodf(y, v) };
        }

        float Float2::Arg() const noexcept {
            return ::atan2(y, x);
        }

        Float2 Float2::Polar() const noexcept {
            return Float2 { Length(), Arg() };
        }

        Float2 Float2::ComplexMul(const Float2 & rhs) const noexcept {
            return Float2 { x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x };
        }

        Float2 Float2::Cartesian() const noexcept {
            return Float2 { ::cosf(y), ::sinf(y) } * x;
        }

        const Float2 Float2::One { 1.0f, 1.0f };
        const Float2 Float2::Zero { 0.0f, 0.0f };
        const Float2 Float2::UnitX { 1.0f, 0.0f };
        const Float2 Float2::UnitY { 0.0f, 1.0f };
    }
}

