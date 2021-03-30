#pragma once

#include "Bool3.h"
#include "UInt2.h"
#include "UInt4.h"

namespace Egg {
    namespace Math {

        class UInt2;
        class UInt4;
        class Bool2;
        class Bool3;
        class Bool4;

        class UInt3 {
        public:
            union {
                struct {
                    unsigned int x;
                    unsigned int y;
                    unsigned int z;
                };

                UInt2Swizzle<UInt2, Bool2, 3, 0, 0> xx;
                UInt2Swizzle<UInt2, Bool2, 3, 0, 1> xy;
                UInt2Swizzle<UInt2, Bool2, 3, 0, 2> xz;
                UInt2Swizzle<UInt2, Bool2, 3, 1, 0> yx;
                UInt2Swizzle<UInt2, Bool2, 3, 1, 1> yy;
                UInt2Swizzle<UInt2, Bool2, 3, 1, 2> yz;
                UInt2Swizzle<UInt2, Bool2, 3, 2, 0> zx;
                UInt2Swizzle<UInt2, Bool2, 3, 2, 1> zy;
                UInt2Swizzle<UInt2, Bool2, 3, 2, 2> zz;

                UInt3Swizzle<UInt3, Bool3, 3, 0, 0, 0> xxx;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 0, 1> xxy;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 0, 2> xxz;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 1, 0> xyx;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 1, 1> xyy;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 1, 2> xyz;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 2, 0> xzx;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 2, 1> xzy;
                UInt3Swizzle<UInt3, Bool3, 3, 0, 2, 2> xzz;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 0, 0> yxx;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 0, 1> yxy;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 0, 2> yxz;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 1, 0> yyx;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 1, 1> yyy;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 1, 2> yyz;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 2, 0> yzx;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 2, 1> yzy;
                UInt3Swizzle<UInt3, Bool3, 3, 1, 2, 2> yzz;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 0, 0> zxx;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 0, 1> zxy;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 0, 2> zxz;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 1, 0> zyx;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 1, 1> zyy;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 1, 2> zyz;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 2, 0> zzx;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 2, 1> zzy;
                UInt3Swizzle<UInt3, Bool3, 3, 2, 2, 2> zzz;

                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 0, 0> xxxx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 1, 0> xxxy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 2, 0> xxxz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 0, 1> xxyx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 1, 1> xxyy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 2, 1> xxyz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 0, 2> xxzx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 1, 2> xxzy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 0, 2, 2> xxzz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 0, 0> xyxx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 1, 0> xyxy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 2, 0> xyxz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 0, 1> xyyx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 1, 1> xyyy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 2, 1> xyyz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 0, 2> xyzx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 1, 2> xyzy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 1, 2, 2> xyzz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 0, 0> xzxx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 1, 0> xzxy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 2, 0> xzxz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 0, 1> xzyx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 1, 1> xzyy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 2, 1> xzyz;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 0, 2> xzzx;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 1, 2> xzzy;
                UInt4Swizzle<UInt4, Bool4, 3, 0, 2, 2, 2> xzzz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 0, 0> yxxx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 1, 0> yxxy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 2, 0> yxxz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 0, 1> yxyx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 1, 1> yxyy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 2, 1> yxyz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 0, 2> yxzx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 1, 2> yxzy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 0, 2, 2> yxzz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 0, 0> yyxx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 1, 0> yyxy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 2, 0> yyxz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 0, 1> yyyx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 1, 1> yyyy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 2, 1> yyyz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 0, 2> yyzx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 1, 2> yyzy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 1, 2, 2> yyzz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 0, 0> yzxx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 1, 0> yzxy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 2, 0> yzxz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 0, 1> yzyx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 1, 1> yzyy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 2, 1> yzyz;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 0, 2> yzzx;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 1, 2> yzzy;
                UInt4Swizzle<UInt4, Bool4, 3, 1, 2, 2, 2> yzzz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 0, 0> zxxx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 1, 0> zxxy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 2, 0> zxxz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 0, 1> zxyx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 1, 1> zxyy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 2, 1> zxyz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 0, 2> zxzx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 1, 2> zxzy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 0, 2, 2> zxzz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 0, 0> zyxx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 1, 0> zyxy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 2, 0> zyxz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 0, 1> zyyx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 1, 1> zyyy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 2, 1> zyyz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 0, 2> zyzx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 1, 2> zyzy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 1, 2, 2> zyzz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 0, 0> zzxx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 1, 0> zzxy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 2, 0> zzxz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 0, 1> zzyx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 1, 1> zzyy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 2, 1> zzyz;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 0, 2> zzzx;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 1, 2> zzzy;
                UInt4Swizzle<UInt4, Bool4, 3, 2, 2, 2, 2> zzzz;
            };

            UInt3(unsigned int x, unsigned int y, unsigned int z);

            UInt3(unsigned int x, const UInt2 & yz);

            UInt3(const UInt2 & xy, unsigned int z);

            UInt3(const UInt3 & xyz);

            UInt3();

            UInt3 & operator=(const UInt3 & rhs) noexcept;
UInt3 & operator=(unsigned int rhs) noexcept;

            UInt3 & operator+=(const UInt3 & rhs) noexcept;
UInt3 & operator+=(unsigned int rhs) noexcept;

            UInt3 & operator-=(const UInt3 & rhs) noexcept;
UInt3 & operator-=(unsigned int rhs) noexcept;

            UInt3 & operator/=(const UInt3 & rhs) noexcept;
UInt3 & operator/=(unsigned int rhs) noexcept;

            UInt3 & operator*=(const UInt3 & rhs) noexcept;
UInt3 & operator*=(unsigned int rhs) noexcept;

            UInt3 & operator%=(const UInt3 & rhs) noexcept;
UInt3 & operator%=(unsigned int rhs) noexcept;

            UInt3 & operator|=(const UInt3 & rhs) noexcept;
UInt3 & operator|=(unsigned int rhs) noexcept;

            UInt3 & operator&=(const UInt3 & rhs) noexcept;
UInt3 & operator&=(unsigned int rhs) noexcept;

            UInt3 & operator^=(const UInt3 & rhs) noexcept;
UInt3 & operator^=(unsigned int rhs) noexcept;

            UInt3 & operator<<=(const UInt3 & rhs) noexcept;
UInt3 & operator<<=(unsigned int rhs) noexcept;

            UInt3 & operator>>=(const UInt3 & rhs) noexcept;
UInt3 & operator>>=(unsigned int rhs) noexcept;

            UInt3 operator*(const UInt3 & rhs) const noexcept;

            UInt3 operator/(const UInt3 & rhs) const noexcept;

            UInt3 operator+(const UInt3 & rhs) const noexcept;

            UInt3 operator-(const UInt3 & rhs) const noexcept;

            UInt3 operator%(const UInt3 & rhs) const noexcept;

            UInt3 operator|(const UInt3 & rhs) const noexcept;

            UInt3 operator&(const UInt3 & rhs) const noexcept;

            UInt3 operator^(const UInt3 & rhs) const noexcept;

            UInt3 operator<<(const UInt3 & rhs) const noexcept;

            UInt3 operator>>(const UInt3 & rhs) const noexcept;

            UInt3 operator||(const UInt3 & rhs) const noexcept;

            UInt3 operator&&(const UInt3 & rhs) const noexcept;

            Bool3 operator<(const UInt3 & rhs) const noexcept;

            Bool3 operator>(const UInt3 & rhs) const noexcept;

            Bool3 operator!=(const UInt3 & rhs) const noexcept;

            Bool3 operator==(const UInt3 & rhs) const noexcept;

            Bool3 operator>=(const UInt3 & rhs) const noexcept;

            Bool3 operator<=(const UInt3 & rhs) const noexcept;

            UInt3 operator~() const noexcept;

            UInt3 operator!() const noexcept;

            UInt3 operator++() noexcept;

            UInt3 operator++(int) noexcept;

            UInt3 operator--() noexcept;

            UInt3 operator--(int) noexcept;

            static UInt3 Random(unsigned int lower = 0, unsigned int upper = 6) noexcept;

            static const UInt3 One;
            static const UInt3 Zero;
            static const UInt3 UnitX;
            static const UInt3 UnitY;
            static const UInt3 UnitZ;
        };
    }
}

