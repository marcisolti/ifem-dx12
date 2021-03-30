#pragma once

#include "Float2Swizzle.hpp"
#include "Float3Swizzle.hpp"
#include "Float4Swizzle.hpp"
#include "Bool1.h"
#include "Int1.h"
#include "Float2.h"
#include "Float3.h"
#include "Float4.h"

namespace Egg {
    namespace Math {

        class Float1 {
        public:
            union {
                struct {
                    float x;
                };
            };

            Float1(float x);

            Float1();

            Float1 & operator=(const Float1 & rhs) noexcept;
Float1 & operator=(float rhs) noexcept;

            Float1 & operator+=(const Float1 & rhs) noexcept;
Float1 & operator+=(float rhs) noexcept;

            Float1 & operator-=(const Float1 & rhs) noexcept;
Float1 & operator-=(float rhs) noexcept;

            Float1 & operator/=(const Float1 & rhs) noexcept;
Float1 & operator/=(float rhs) noexcept;

            Float1 & operator*=(const Float1 & rhs) noexcept;
Float1 & operator*=(float rhs) noexcept;

            Float1 operator*(const Float1 & rhs) const noexcept;

            Float1 operator/(const Float1 & rhs) const noexcept;

            Float1 operator+(const Float1 & rhs) const noexcept;

            Float1 operator-(const Float1 & rhs) const noexcept;

            Float1 Abs() const noexcept;

            Float1 Acos() const noexcept;

            Float1 Asin() const noexcept;

            Float1 Atan() const noexcept;

            Float1 Cos() const noexcept;

            Float1 Sin() const noexcept;

            Float1 Cosh() const noexcept;

            Float1 Sinh() const noexcept;

            Float1 Tan() const noexcept;

            Float1 Exp() const noexcept;

            Float1 Log() const noexcept;

            Float1 Log10() const noexcept;

            Float1 Fmod(const Float1 & rhs) const noexcept;

            Float1 Atan2(const Float1 & rhs) const noexcept;

            Float1 Pow(const Float1 & rhs) const noexcept;

            Float1 Sqrt() const noexcept;

            Float1 Clamp(const Float1 & low, const Float1 & high) const noexcept;

            float Dot(const Float1 & rhs) const noexcept;

            Float1 Sign() const noexcept;

            Int1 Round() const noexcept;

            Float1 Saturate() const noexcept;

            float LengthSquared() const noexcept;

            float Length() const noexcept;

            Float1 Normalize() const noexcept;

            Bool1 IsNan() const noexcept;

            Bool1 IsFinite() const noexcept;

            Bool1 IsInfinite() const noexcept;

            Float1 operator-() const noexcept;

            Float1 operator%(const Float1 & rhs) const noexcept;

            Float1 & operator%=(const Float1 & rhs) noexcept;

            Int1 Ceil() const noexcept;

            Int1 Floor() const noexcept;

            Float1 Exp2() const noexcept;

            Int1 Trunc() const noexcept;

            float Distance(const Float1 & rhs) const noexcept;

            Bool1 operator<(const Float1 & rhs) const noexcept;

            Bool1 operator>(const Float1 & rhs) const noexcept;

            Bool1 operator!=(const Float1 & rhs) const noexcept;

            Bool1 operator==(const Float1 & rhs) const noexcept;

            Bool1 operator>=(const Float1 & rhs) const noexcept;

            Bool1 operator<=(const Float1 & rhs) const noexcept;

            static Float1 Random(float lower = 0.0f, float upper = 1.0f) noexcept;

        };
    }
}

