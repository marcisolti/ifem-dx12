#include "Float1.h"
#include <cmath>
#include <cfloat>

namespace Egg {
    namespace Math {

        Float1::Float1(float x) : x { x }{ }

        Float1::Float1() : x{ 0.0f }{ }

        Float1 & Float1::operator=(const Float1 & rhs) noexcept {
            this->x = rhs.x;
            return *this;
        }

        Float1 & Float1::operator=(float rhs) noexcept {
            this->x = rhs;
            return *this;
        }

        Float1 & Float1::operator+=(const Float1 & rhs) noexcept {
            this->x += rhs.x;
            return *this;
        }

        Float1 & Float1::operator+=(float rhs) noexcept {
            this->x += rhs;
            return *this;
        }

        Float1 & Float1::operator-=(const Float1 & rhs) noexcept {
            this->x -= rhs.x;
            return *this;
        }

        Float1 & Float1::operator-=(float rhs) noexcept {
            this->x -= rhs;
            return *this;
        }

        Float1 & Float1::operator/=(const Float1 & rhs) noexcept {
            this->x /= rhs.x;
            return *this;
        }

        Float1 & Float1::operator/=(float rhs) noexcept {
            this->x /= rhs;
            return *this;
        }

        Float1 & Float1::operator*=(const Float1 & rhs) noexcept {
            this->x *= rhs.x;
            return *this;
        }

        Float1 & Float1::operator*=(float rhs) noexcept {
            this->x *= rhs;
            return *this;
        }

        Float1 Float1::operator*(const Float1 & rhs) const noexcept {
            return Float1 { this->x * rhs.x };
        }

        Float1 Float1::operator/(const Float1 & rhs) const noexcept {
            return Float1 { this->x / rhs.x };
        }

        Float1 Float1::operator+(const Float1 & rhs) const noexcept {
            return Float1 { this->x + rhs.x };
        }

        Float1 Float1::operator-(const Float1 & rhs) const noexcept {
            return Float1 { this->x - rhs.x };
        }

        Float1 Float1::Abs() const noexcept {
            return Float1 { ::abs(this->x) };
        }

        Float1 Float1::Acos() const noexcept {
            return Float1 { ::acos(this->x) };
        }

        Float1 Float1::Asin() const noexcept {
            return Float1 { ::asin(this->x) };
        }

        Float1 Float1::Atan() const noexcept {
            return Float1 { ::atan(this->x) };
        }

        Float1 Float1::Cos() const noexcept {
            return Float1 { ::cos(this->x) };
        }

        Float1 Float1::Sin() const noexcept {
            return Float1 { ::sin(this->x) };
        }

        Float1 Float1::Cosh() const noexcept {
            return Float1 { ::cosh(this->x) };
        }

        Float1 Float1::Sinh() const noexcept {
            return Float1 { ::sinh(this->x) };
        }

        Float1 Float1::Tan() const noexcept {
            return Float1 { ::tan(this->x) };
        }

        Float1 Float1::Exp() const noexcept {
            return Float1 { ::exp(this->x) };
        }

        Float1 Float1::Log() const noexcept {
            return Float1 { ::log(this->x) };
        }

        Float1 Float1::Log10() const noexcept {
            return Float1 { ::log10(this->x) };
        }

        Float1 Float1::Fmod(const Float1 & rhs) const noexcept {
            return Float1 { ::fmod(this->x, rhs.x) };
        }

        Float1 Float1::Atan2(const Float1 & rhs) const noexcept {
            return Float1 { ::atan2(this->x, rhs.x) };
        }

        Float1 Float1::Pow(const Float1 & rhs) const noexcept {
            return Float1 { ::pow(this->x, rhs.x) };
        }

        Float1 Float1::Sqrt() const noexcept {
            return Float1 { ::sqrtf(this->x) };
        }

        Float1 Float1::Clamp(const Float1 & low, const Float1 & high) const noexcept {
            return Float1 { (x < low.x) ? low.x: ((x > high.x) ? high.x :x) };
        }

        float Float1::Dot(const Float1 & rhs) const noexcept {
            return x * rhs.x;
        }

        Float1 Float1::Sign() const noexcept {
            return Float1 { (x > 0.0f) ? 1.0f : ((x < 0.0f) ? -1.0f : 0.0f) };
        }

        Int1 Float1::Round() const noexcept {
            return Int1 { (int)(x + 0.5f) }; 
        }

        Float1 Float1::Saturate() const noexcept {
            return Clamp(Float1 { 0 }, Float1 { 1 });
        }

        float Float1::LengthSquared() const noexcept {
            return Dot(*this);
        }

        float Float1::Length() const noexcept {
            return ::sqrtf(LengthSquared());
        }

        Float1 Float1::Normalize() const noexcept {
            float len = Length();
             return Float1 { x / len  };
        }

        Bool1 Float1::IsNan() const noexcept {
            return Bool1 { std::isnan(x) };
        }

        Bool1 Float1::IsFinite() const noexcept {
            return Bool1 { std::isfinite(x) };
        }

        Bool1 Float1::IsInfinite() const noexcept {
            return Bool1 { !std::isfinite(x) };
        }

        Float1 Float1::operator-() const noexcept {
            return Float1 { -x };
        }

        Float1 Float1::operator%(const Float1 & rhs) const noexcept {
            return Float1 { ::fmodf(x, rhs.x) };
        }

        Float1 & Float1::operator%=(const Float1 & rhs) noexcept {
            x = ::fmodf(x, rhs.x);
            return *this;
        }

        Int1 Float1::Ceil() const noexcept {
            return Int1 { (int)::ceil(x) };
        }

        Int1 Float1::Floor() const noexcept {
            return Int1 { (int)::floor(x) };
        }

        Float1 Float1::Exp2() const noexcept {
            return Float1 { ::pow(2.0f,x) };
        }

        Int1 Float1::Trunc() const noexcept {
            return Int1 { (int)x };
        }

        float Float1::Distance(const Float1 & rhs) const noexcept {
            return (( Float1 )(*this) - rhs).Length();
        }

        Bool1 Float1::operator<(const Float1 & rhs) const noexcept {
            return Bool1 { x < rhs.x };
        }

        Bool1 Float1::operator>(const Float1 & rhs) const noexcept {
            return Bool1 { x > rhs.x };
        }

        Bool1 Float1::operator!=(const Float1 & rhs) const noexcept {
            return Bool1 { x != rhs.x };
        }

        Bool1 Float1::operator==(const Float1 & rhs) const noexcept {
            return Bool1 { x == rhs.x };
        }

        Bool1 Float1::operator>=(const Float1 & rhs) const noexcept {
            return Bool1 { x >= rhs.x };
        }

        Bool1 Float1::operator<=(const Float1 & rhs) const noexcept {
            return Bool1 { x <= rhs.x };
        }

        Float1 Float1::Random(float lower, float upper) noexcept {
            float range = upper - lower;
            return Float1 {  rand() * range / RAND_MAX + lower };
        }

    }
}

