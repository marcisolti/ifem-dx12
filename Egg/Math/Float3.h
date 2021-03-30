#pragma once

#include "Float2.h"
#include "Bool3.h"
#include "Int3.h"
#include "Float2.h"
#include "Float4.h"

namespace Egg {
    namespace Math {

        class Float2;
        class Float4;
        class Bool2;
        class Bool3;
        class Bool4;
        class Int2;
        class Int3;
        class Int4;

        class Float3 {
        public:
            union {
                struct {
                    float x;
                    float y;
                    float z;
                };

                Float2Swizzle<Float2, Int2, Bool2, 3, 0, 0> xx;
                Float2Swizzle<Float2, Int2, Bool2, 3, 0, 1> xy;
                Float2Swizzle<Float2, Int2, Bool2, 3, 0, 2> xz;
                Float2Swizzle<Float2, Int2, Bool2, 3, 1, 0> yx;
                Float2Swizzle<Float2, Int2, Bool2, 3, 1, 1> yy;
                Float2Swizzle<Float2, Int2, Bool2, 3, 1, 2> yz;
                Float2Swizzle<Float2, Int2, Bool2, 3, 2, 0> zx;
                Float2Swizzle<Float2, Int2, Bool2, 3, 2, 1> zy;
                Float2Swizzle<Float2, Int2, Bool2, 3, 2, 2> zz;

                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 0, 0> xxx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 0, 1> xxy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 0, 2> xxz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 1, 0> xyx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 1, 1> xyy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 1, 2> xyz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 2, 0> xzx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 2, 1> xzy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 0, 2, 2> xzz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 0, 0> yxx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 0, 1> yxy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 0, 2> yxz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 1, 0> yyx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 1, 1> yyy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 1, 2> yyz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 2, 0> yzx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 2, 1> yzy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 1, 2, 2> yzz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 0, 0> zxx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 0, 1> zxy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 0, 2> zxz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 1, 0> zyx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 1, 1> zyy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 1, 2> zyz;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 2, 0> zzx;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 2, 1> zzy;
                Float3Swizzle<Float3, Int3, Bool3, 3, 2, 2, 2> zzz;

                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 0, 0> xxxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 1, 0> xxxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 2, 0> xxxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 0, 1> xxyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 1, 1> xxyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 2, 1> xxyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 0, 2> xxzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 1, 2> xxzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 0, 2, 2> xxzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 0, 0> xyxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 1, 0> xyxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 2, 0> xyxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 0, 1> xyyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 1, 1> xyyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 2, 1> xyyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 0, 2> xyzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 1, 2> xyzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 1, 2, 2> xyzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 0, 0> xzxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 1, 0> xzxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 2, 0> xzxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 0, 1> xzyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 1, 1> xzyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 2, 1> xzyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 0, 2> xzzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 1, 2> xzzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 0, 2, 2, 2> xzzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 0, 0> yxxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 1, 0> yxxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 2, 0> yxxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 0, 1> yxyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 1, 1> yxyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 2, 1> yxyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 0, 2> yxzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 1, 2> yxzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 0, 2, 2> yxzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 0, 0> yyxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 1, 0> yyxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 2, 0> yyxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 0, 1> yyyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 1, 1> yyyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 2, 1> yyyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 0, 2> yyzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 1, 2> yyzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 1, 2, 2> yyzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 0, 0> yzxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 1, 0> yzxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 2, 0> yzxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 0, 1> yzyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 1, 1> yzyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 2, 1> yzyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 0, 2> yzzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 1, 2> yzzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 1, 2, 2, 2> yzzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 0, 0> zxxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 1, 0> zxxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 2, 0> zxxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 0, 1> zxyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 1, 1> zxyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 2, 1> zxyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 0, 2> zxzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 1, 2> zxzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 0, 2, 2> zxzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 0, 0> zyxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 1, 0> zyxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 2, 0> zyxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 0, 1> zyyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 1, 1> zyyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 2, 1> zyyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 0, 2> zyzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 1, 2> zyzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 1, 2, 2> zyzz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 0, 0> zzxx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 1, 0> zzxy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 2, 0> zzxz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 0, 1> zzyx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 1, 1> zzyy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 2, 1> zzyz;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 0, 2> zzzx;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 1, 2> zzzy;
                Float4Swizzle<Float4, Int4, Bool4, 3, 2, 2, 2, 2> zzzz;
            };

            Float3(float x, float y, float z);

            Float3(float x, const Float2 & yz);

            Float3(const Float2 & xy, float z);

            Float3(const Float3 & xyz);

            Float3();

			explicit Float3(float x);

            Float3 & operator=(const Float3 & rhs) noexcept;
Float3 & operator=(float rhs) noexcept;

            Float3 & operator+=(const Float3 & rhs) noexcept;
Float3 & operator+=(float rhs) noexcept;

            Float3 & operator-=(const Float3 & rhs) noexcept;
Float3 & operator-=(float rhs) noexcept;

            Float3 & operator/=(const Float3 & rhs) noexcept;
Float3 & operator/=(float rhs) noexcept;

            Float3 & operator*=(const Float3 & rhs) noexcept;
Float3 & operator*=(float rhs) noexcept;

            Float3 operator*(const Float3 & rhs) const noexcept;

            Float3 operator/(const Float3 & rhs) const noexcept;

            Float3 operator+(const Float3 & rhs) const noexcept;

            Float3 operator-(const Float3 & rhs) const noexcept;

            Float3 Abs() const noexcept;

            Float3 Acos() const noexcept;

            Float3 Asin() const noexcept;

            Float3 Atan() const noexcept;

            Float3 Cos() const noexcept;

            Float3 Sin() const noexcept;

            Float3 Cosh() const noexcept;

            Float3 Sinh() const noexcept;

            Float3 Tan() const noexcept;

            Float3 Exp() const noexcept;

            Float3 Log() const noexcept;

            Float3 Log10() const noexcept;

            Float3 Fmod(const Float3 & rhs) const noexcept;

            Float3 Atan2(const Float3 & rhs) const noexcept;

            Float3 Pow(const Float3 & rhs) const noexcept;

            Float3 Sqrt() const noexcept;

            Float3 Clamp(const Float3 & low, const Float3 & high) const noexcept;

            float Dot(const Float3 & rhs) const noexcept;

            Float3 Sign() const noexcept;

            Int3 Round() const noexcept;

            Float3 Saturate() const noexcept;

            float LengthSquared() const noexcept;

            float Length() const noexcept;

            Float3 Normalize() const noexcept;

            Bool3 IsNan() const noexcept;

            Bool3 IsFinite() const noexcept;

            Bool3 IsInfinite() const noexcept;

            Float3 operator-() const noexcept;

            Float3 operator%(const Float3 & rhs) const noexcept;

            Float3 & operator%=(const Float3 & rhs) noexcept;

            Int3 Ceil() const noexcept;

            Int3 Floor() const noexcept;

            Float3 Exp2() const noexcept;

            Int3 Trunc() const noexcept;

            float Distance(const Float3 & rhs) const noexcept;

            Bool3 operator<(const Float3 & rhs) const noexcept;

            Bool3 operator>(const Float3 & rhs) const noexcept;

            Bool3 operator!=(const Float3 & rhs) const noexcept;

            Bool3 operator==(const Float3 & rhs) const noexcept;

            Bool3 operator>=(const Float3 & rhs) const noexcept;

            Bool3 operator<=(const Float3 & rhs) const noexcept;

            static Float3 Random(float lower = 0.0f, float upper = 1.0f) noexcept;

            Float3 operator+(float v) const noexcept;

            Float3 operator-(float v) const noexcept;

            Float3 operator*(float v) const noexcept;

            Float3 operator/(float v) const noexcept;

            Float3 operator%(float v) const noexcept;

            Float3 Cross(const Float3 & rhs) const noexcept;

            static const Float3 UnitX;
            static const Float3 UnitY;
            static const Float3 UnitZ;
            static const Float3 Zero;
            static const Float3 One;
            static const Float3 Black;
            static const Float3 Navy;
            static const Float3 Blue;
            static const Float3 DarkGreen;
            static const Float3 Teal;
            static const Float3 Azure;
            static const Float3 Green;
            static const Float3 Cyan;
            static const Float3 Maroon;
            static const Float3 Purple;
            static const Float3 SlateBlue;
            static const Float3 Olive;
            static const Float3 Gray;
            static const Float3 Cornflower;
            static const Float3 Aquamarine;
            static const Float3 Red;
            static const Float3 DeepPink;
            static const Float3 Magenta;
            static const Float3 Orange;
            static const Float3 Coral;
            static const Float3 Mallow;
            static const Float3 Yellow;
            static const Float3 Gold;
            static const Float3 White;
            static const Float3 Silver;
        };
    }
}

