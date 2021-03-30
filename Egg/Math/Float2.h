#pragma once

#include "Float2Swizzle.hpp"
#include "Float3Swizzle.hpp"
#include "Float4Swizzle.hpp"
#include "Bool2.h"
#include "Int2.h"
#include "Float3.h"
#include "Float4.h"

namespace Egg {
    namespace Math {

        class Float3;
        class Float4;
        class Bool2;
        class Bool3;
        class Bool4;
        class Int2;
        class Int3;
        class Int4;

        class Float2 {
        public:
            union {
                struct {
                    float x;
                    float y;
                };

                Float2Swizzle<Float2, Int2, Bool2, 2, 0, 0> xx;
                Float2Swizzle<Float2, Int2, Bool2, 2, 0, 1> xy;
                Float2Swizzle<Float2, Int2, Bool2, 2, 1, 0> yx;
                Float2Swizzle<Float2, Int2, Bool2, 2, 1, 1> yy;

                Float3Swizzle<Float3, Int3, Bool3, 2, 0, 0, 0> xxx;
                Float3Swizzle<Float3, Int3, Bool3, 2, 0, 0, 1> xxy;
                Float3Swizzle<Float3, Int3, Bool3, 2, 0, 1, 0> xyx;
                Float3Swizzle<Float3, Int3, Bool3, 2, 0, 1, 1> xyy;
                Float3Swizzle<Float3, Int3, Bool3, 2, 1, 0, 0> yxx;
                Float3Swizzle<Float3, Int3, Bool3, 2, 1, 0, 1> yxy;
                Float3Swizzle<Float3, Int3, Bool3, 2, 1, 1, 0> yyx;
                Float3Swizzle<Float3, Int3, Bool3, 2, 1, 1, 1> yyy;

                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 0, 0, 0> xxxx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 0, 1, 0> xxxy;
                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 0, 0, 1> xxyx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 0, 1, 1> xxyy;
                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 1, 0, 0> xyxx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 1, 1, 0> xyxy;
                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 1, 0, 1> xyyx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 0, 1, 1, 1> xyyy;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 0, 0, 0> yxxx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 0, 1, 0> yxxy;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 0, 0, 1> yxyx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 0, 1, 1> yxyy;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 1, 0, 0> yyxx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 1, 1, 0> yyxy;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 1, 0, 1> yyyx;
                Float4Swizzle<Float4, Int4, Bool4, 2, 1, 1, 1, 1> yyyy;
            };

            Float2(float x, float y);

            Float2(const Float2 & xy);

            Float2();

            Float2 & operator=(const Float2 & rhs) noexcept;
Float2 & operator=(float rhs) noexcept;

            Float2 & operator+=(const Float2 & rhs) noexcept;
Float2 & operator+=(float rhs) noexcept;

            Float2 & operator-=(const Float2 & rhs) noexcept;
Float2 & operator-=(float rhs) noexcept;

            Float2 & operator/=(const Float2 & rhs) noexcept;
Float2 & operator/=(float rhs) noexcept;

            Float2 & operator*=(const Float2 & rhs) noexcept;
Float2 & operator*=(float rhs) noexcept;

            Float2 operator*(const Float2 & rhs) const noexcept;

            Float2 operator/(const Float2 & rhs) const noexcept;

            Float2 operator+(const Float2 & rhs) const noexcept;

            Float2 operator-(const Float2 & rhs) const noexcept;

            Float2 Abs() const noexcept;

            Float2 Acos() const noexcept;

            Float2 Asin() const noexcept;

            Float2 Atan() const noexcept;

            Float2 Cos() const noexcept;

            Float2 Sin() const noexcept;

            Float2 Cosh() const noexcept;

            Float2 Sinh() const noexcept;

            Float2 Tan() const noexcept;

            Float2 Exp() const noexcept;

            Float2 Log() const noexcept;

            Float2 Log10() const noexcept;

            Float2 Fmod(const Float2 & rhs) const noexcept;

            Float2 Atan2(const Float2 & rhs) const noexcept;

            Float2 Pow(const Float2 & rhs) const noexcept;

            Float2 Sqrt() const noexcept;

            Float2 Clamp(const Float2 & low, const Float2 & high) const noexcept;

            float Dot(const Float2 & rhs) const noexcept;

            Float2 Sign() const noexcept;

            Int2 Round() const noexcept;

            Float2 Saturate() const noexcept;

            float LengthSquared() const noexcept;

            float Length() const noexcept;

            Float2 Normalize() const noexcept;

            Bool2 IsNan() const noexcept;

            Bool2 IsFinite() const noexcept;

            Bool2 IsInfinite() const noexcept;

            Float2 operator-() const noexcept;

            Float2 operator%(const Float2 & rhs) const noexcept;

            Float2 & operator%=(const Float2 & rhs) noexcept;

            Int2 Ceil() const noexcept;

            Int2 Floor() const noexcept;

            Float2 Exp2() const noexcept;

            Int2 Trunc() const noexcept;

            float Distance(const Float2 & rhs) const noexcept;

            Bool2 operator<(const Float2 & rhs) const noexcept;

            Bool2 operator>(const Float2 & rhs) const noexcept;

            Bool2 operator!=(const Float2 & rhs) const noexcept;

            Bool2 operator==(const Float2 & rhs) const noexcept;

            Bool2 operator>=(const Float2 & rhs) const noexcept;

            Bool2 operator<=(const Float2 & rhs) const noexcept;

            static Float2 Random(float lower = 0.0f, float upper = 1.0f) noexcept;

            Float2 operator+(float v) const noexcept;

            Float2 operator-(float v) const noexcept;

            Float2 operator*(float v) const noexcept;

            Float2 operator/(float v) const noexcept;

            Float2 operator%(float v) const noexcept;

            float Arg() const noexcept;

            Float2 Polar() const noexcept;

            Float2 ComplexMul(const Float2 & rhs) const noexcept;

            Float2 Cartesian() const noexcept;

            static const Float2 One;
            static const Float2 Zero;
            static const Float2 UnitX;
            static const Float2 UnitY;
        };
    }
}

