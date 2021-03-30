#pragma once

#include "Int2.h"
#include "Bool3.h"
#include "Int4.h"

namespace Egg {
    namespace Math {

        class Int2;
        class Int4;
        class Bool2;
        class Bool3;
        class Bool4;

        class Int3 {
        public:
            union {
                struct {
                    int x;
                    int y;
                    int z;
                };

                Int2Swizzle<Int2, Bool2, 3, 0, 0> xx;
                Int2Swizzle<Int2, Bool2, 3, 0, 1> xy;
                Int2Swizzle<Int2, Bool2, 3, 0, 2> xz;
                Int2Swizzle<Int2, Bool2, 3, 1, 0> yx;
                Int2Swizzle<Int2, Bool2, 3, 1, 1> yy;
                Int2Swizzle<Int2, Bool2, 3, 1, 2> yz;
                Int2Swizzle<Int2, Bool2, 3, 2, 0> zx;
                Int2Swizzle<Int2, Bool2, 3, 2, 1> zy;
                Int2Swizzle<Int2, Bool2, 3, 2, 2> zz;

                Int3Swizzle<Int3, Bool3, 3, 0, 0, 0> xxx;
                Int3Swizzle<Int3, Bool3, 3, 0, 0, 1> xxy;
                Int3Swizzle<Int3, Bool3, 3, 0, 0, 2> xxz;
                Int3Swizzle<Int3, Bool3, 3, 0, 1, 0> xyx;
                Int3Swizzle<Int3, Bool3, 3, 0, 1, 1> xyy;
                Int3Swizzle<Int3, Bool3, 3, 0, 1, 2> xyz;
                Int3Swizzle<Int3, Bool3, 3, 0, 2, 0> xzx;
                Int3Swizzle<Int3, Bool3, 3, 0, 2, 1> xzy;
                Int3Swizzle<Int3, Bool3, 3, 0, 2, 2> xzz;
                Int3Swizzle<Int3, Bool3, 3, 1, 0, 0> yxx;
                Int3Swizzle<Int3, Bool3, 3, 1, 0, 1> yxy;
                Int3Swizzle<Int3, Bool3, 3, 1, 0, 2> yxz;
                Int3Swizzle<Int3, Bool3, 3, 1, 1, 0> yyx;
                Int3Swizzle<Int3, Bool3, 3, 1, 1, 1> yyy;
                Int3Swizzle<Int3, Bool3, 3, 1, 1, 2> yyz;
                Int3Swizzle<Int3, Bool3, 3, 1, 2, 0> yzx;
                Int3Swizzle<Int3, Bool3, 3, 1, 2, 1> yzy;
                Int3Swizzle<Int3, Bool3, 3, 1, 2, 2> yzz;
                Int3Swizzle<Int3, Bool3, 3, 2, 0, 0> zxx;
                Int3Swizzle<Int3, Bool3, 3, 2, 0, 1> zxy;
                Int3Swizzle<Int3, Bool3, 3, 2, 0, 2> zxz;
                Int3Swizzle<Int3, Bool3, 3, 2, 1, 0> zyx;
                Int3Swizzle<Int3, Bool3, 3, 2, 1, 1> zyy;
                Int3Swizzle<Int3, Bool3, 3, 2, 1, 2> zyz;
                Int3Swizzle<Int3, Bool3, 3, 2, 2, 0> zzx;
                Int3Swizzle<Int3, Bool3, 3, 2, 2, 1> zzy;
                Int3Swizzle<Int3, Bool3, 3, 2, 2, 2> zzz;

                Int4Swizzle<Int4, Bool4, 3, 0, 0, 0, 0> xxxx;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 1, 0> xxxy;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 2, 0> xxxz;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 0, 1> xxyx;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 1, 1> xxyy;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 2, 1> xxyz;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 0, 2> xxzx;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 1, 2> xxzy;
                Int4Swizzle<Int4, Bool4, 3, 0, 0, 2, 2> xxzz;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 0, 0> xyxx;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 1, 0> xyxy;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 2, 0> xyxz;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 0, 1> xyyx;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 1, 1> xyyy;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 2, 1> xyyz;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 0, 2> xyzx;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 1, 2> xyzy;
                Int4Swizzle<Int4, Bool4, 3, 0, 1, 2, 2> xyzz;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 0, 0> xzxx;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 1, 0> xzxy;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 2, 0> xzxz;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 0, 1> xzyx;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 1, 1> xzyy;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 2, 1> xzyz;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 0, 2> xzzx;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 1, 2> xzzy;
                Int4Swizzle<Int4, Bool4, 3, 0, 2, 2, 2> xzzz;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 0, 0> yxxx;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 1, 0> yxxy;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 2, 0> yxxz;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 0, 1> yxyx;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 1, 1> yxyy;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 2, 1> yxyz;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 0, 2> yxzx;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 1, 2> yxzy;
                Int4Swizzle<Int4, Bool4, 3, 1, 0, 2, 2> yxzz;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 0, 0> yyxx;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 1, 0> yyxy;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 2, 0> yyxz;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 0, 1> yyyx;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 1, 1> yyyy;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 2, 1> yyyz;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 0, 2> yyzx;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 1, 2> yyzy;
                Int4Swizzle<Int4, Bool4, 3, 1, 1, 2, 2> yyzz;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 0, 0> yzxx;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 1, 0> yzxy;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 2, 0> yzxz;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 0, 1> yzyx;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 1, 1> yzyy;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 2, 1> yzyz;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 0, 2> yzzx;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 1, 2> yzzy;
                Int4Swizzle<Int4, Bool4, 3, 1, 2, 2, 2> yzzz;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 0, 0> zxxx;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 1, 0> zxxy;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 2, 0> zxxz;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 0, 1> zxyx;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 1, 1> zxyy;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 2, 1> zxyz;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 0, 2> zxzx;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 1, 2> zxzy;
                Int4Swizzle<Int4, Bool4, 3, 2, 0, 2, 2> zxzz;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 0, 0> zyxx;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 1, 0> zyxy;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 2, 0> zyxz;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 0, 1> zyyx;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 1, 1> zyyy;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 2, 1> zyyz;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 0, 2> zyzx;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 1, 2> zyzy;
                Int4Swizzle<Int4, Bool4, 3, 2, 1, 2, 2> zyzz;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 0, 0> zzxx;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 1, 0> zzxy;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 2, 0> zzxz;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 0, 1> zzyx;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 1, 1> zzyy;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 2, 1> zzyz;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 0, 2> zzzx;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 1, 2> zzzy;
                Int4Swizzle<Int4, Bool4, 3, 2, 2, 2, 2> zzzz;
            };

            Int3(int x, int y, int z);

            Int3(int x, const Int2 & yz);

            Int3(const Int2 & xy, int z);

            Int3(const Int3 & xyz);

            Int3();

            Int3 & operator=(const Int3 & rhs) noexcept;
Int3 & operator=(int rhs) noexcept;

            Int3 & operator+=(const Int3 & rhs) noexcept;
Int3 & operator+=(int rhs) noexcept;

            Int3 & operator-=(const Int3 & rhs) noexcept;
Int3 & operator-=(int rhs) noexcept;

            Int3 & operator/=(const Int3 & rhs) noexcept;
Int3 & operator/=(int rhs) noexcept;

            Int3 & operator*=(const Int3 & rhs) noexcept;
Int3 & operator*=(int rhs) noexcept;

            Int3 & operator%=(const Int3 & rhs) noexcept;
Int3 & operator%=(int rhs) noexcept;

            Int3 & operator|=(const Int3 & rhs) noexcept;
Int3 & operator|=(int rhs) noexcept;

            Int3 & operator&=(const Int3 & rhs) noexcept;
Int3 & operator&=(int rhs) noexcept;

            Int3 & operator^=(const Int3 & rhs) noexcept;
Int3 & operator^=(int rhs) noexcept;

            Int3 & operator<<=(const Int3 & rhs) noexcept;
Int3 & operator<<=(int rhs) noexcept;

            Int3 & operator>>=(const Int3 & rhs) noexcept;
Int3 & operator>>=(int rhs) noexcept;

            Int3 operator*(const Int3 & rhs) const noexcept;

            Int3 operator/(const Int3 & rhs) const noexcept;

            Int3 operator+(const Int3 & rhs) const noexcept;

            Int3 operator-(const Int3 & rhs) const noexcept;

            Int3 operator%(const Int3 & rhs) const noexcept;

            Int3 operator|(const Int3 & rhs) const noexcept;

            Int3 operator&(const Int3 & rhs) const noexcept;

            Int3 operator^(const Int3 & rhs) const noexcept;

            Int3 operator<<(const Int3 & rhs) const noexcept;

            Int3 operator>>(const Int3 & rhs) const noexcept;

            Int3 operator||(const Int3 & rhs) const noexcept;

            Int3 operator&&(const Int3 & rhs) const noexcept;

            Bool3 operator<(const Int3 & rhs) const noexcept;

            Bool3 operator>(const Int3 & rhs) const noexcept;

            Bool3 operator!=(const Int3 & rhs) const noexcept;

            Bool3 operator==(const Int3 & rhs) const noexcept;

            Bool3 operator>=(const Int3 & rhs) const noexcept;

            Bool3 operator<=(const Int3 & rhs) const noexcept;

            Int3 operator~() const noexcept;

            Int3 operator!() const noexcept;

            Int3 operator++() noexcept;

            Int3 operator++(int) noexcept;

            Int3 operator--() noexcept;

            Int3 operator--(int) noexcept;

            static Int3 Random(int lower = 0, int upper = 6) noexcept;

            Int3 operator-() const noexcept;

            static const Int3 One;
            static const Int3 Zero;
            static const Int3 UnitX;
            static const Int3 UnitY;
            static const Int3 UnitZ;
        };
    }
}

