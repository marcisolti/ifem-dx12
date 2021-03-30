#pragma once

#include "UInt2Swizzle.hpp"
#include "UInt3Swizzle.hpp"
#include "UInt4Swizzle.hpp"
#include "Bool2.h"
#include "UInt3.h"
#include "UInt4.h"

namespace Egg {
    namespace Math {

        class UInt3;
        class UInt4;
        class Bool2;
        class Bool3;
        class Bool4;

        class UInt2 {
        public:
            union {
                struct {
                    unsigned int x;
                    unsigned int y;
                };

                UInt2Swizzle<UInt2, Bool2, 2, 0, 0> xx;
                UInt2Swizzle<UInt2, Bool2, 2, 0, 1> xy;
                UInt2Swizzle<UInt2, Bool2, 2, 1, 0> yx;
                UInt2Swizzle<UInt2, Bool2, 2, 1, 1> yy;

                UInt3Swizzle<UInt3, Bool3, 2, 0, 0, 0> xxx;
                UInt3Swizzle<UInt3, Bool3, 2, 0, 0, 1> xxy;
                UInt3Swizzle<UInt3, Bool3, 2, 0, 1, 0> xyx;
                UInt3Swizzle<UInt3, Bool3, 2, 0, 1, 1> xyy;
                UInt3Swizzle<UInt3, Bool3, 2, 1, 0, 0> yxx;
                UInt3Swizzle<UInt3, Bool3, 2, 1, 0, 1> yxy;
                UInt3Swizzle<UInt3, Bool3, 2, 1, 1, 0> yyx;
                UInt3Swizzle<UInt3, Bool3, 2, 1, 1, 1> yyy;

                UInt4Swizzle<UInt4, Bool4, 2, 0, 0, 0, 0> xxxx;
                UInt4Swizzle<UInt4, Bool4, 2, 0, 0, 1, 0> xxxy;
                UInt4Swizzle<UInt4, Bool4, 2, 0, 0, 0, 1> xxyx;
                UInt4Swizzle<UInt4, Bool4, 2, 0, 0, 1, 1> xxyy;
                UInt4Swizzle<UInt4, Bool4, 2, 0, 1, 0, 0> xyxx;
                UInt4Swizzle<UInt4, Bool4, 2, 0, 1, 1, 0> xyxy;
                UInt4Swizzle<UInt4, Bool4, 2, 0, 1, 0, 1> xyyx;
                UInt4Swizzle<UInt4, Bool4, 2, 0, 1, 1, 1> xyyy;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 0, 0, 0> yxxx;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 0, 1, 0> yxxy;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 0, 0, 1> yxyx;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 0, 1, 1> yxyy;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 1, 0, 0> yyxx;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 1, 1, 0> yyxy;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 1, 0, 1> yyyx;
                UInt4Swizzle<UInt4, Bool4, 2, 1, 1, 1, 1> yyyy;
            };

            UInt2(unsigned int x, unsigned int y);

            UInt2(const UInt2 & xy);

            UInt2();

            UInt2 & operator=(const UInt2 & rhs) noexcept;
UInt2 & operator=(unsigned int rhs) noexcept;

            UInt2 & operator+=(const UInt2 & rhs) noexcept;
UInt2 & operator+=(unsigned int rhs) noexcept;

            UInt2 & operator-=(const UInt2 & rhs) noexcept;
UInt2 & operator-=(unsigned int rhs) noexcept;

            UInt2 & operator/=(const UInt2 & rhs) noexcept;
UInt2 & operator/=(unsigned int rhs) noexcept;

            UInt2 & operator*=(const UInt2 & rhs) noexcept;
UInt2 & operator*=(unsigned int rhs) noexcept;

            UInt2 & operator%=(const UInt2 & rhs) noexcept;
UInt2 & operator%=(unsigned int rhs) noexcept;

            UInt2 & operator|=(const UInt2 & rhs) noexcept;
UInt2 & operator|=(unsigned int rhs) noexcept;

            UInt2 & operator&=(const UInt2 & rhs) noexcept;
UInt2 & operator&=(unsigned int rhs) noexcept;

            UInt2 & operator^=(const UInt2 & rhs) noexcept;
UInt2 & operator^=(unsigned int rhs) noexcept;

            UInt2 & operator<<=(const UInt2 & rhs) noexcept;
UInt2 & operator<<=(unsigned int rhs) noexcept;

            UInt2 & operator>>=(const UInt2 & rhs) noexcept;
UInt2 & operator>>=(unsigned int rhs) noexcept;

            UInt2 operator*(const UInt2 & rhs) const noexcept;

            UInt2 operator/(const UInt2 & rhs) const noexcept;

            UInt2 operator+(const UInt2 & rhs) const noexcept;

            UInt2 operator-(const UInt2 & rhs) const noexcept;

            UInt2 operator%(const UInt2 & rhs) const noexcept;

            UInt2 operator|(const UInt2 & rhs) const noexcept;

            UInt2 operator&(const UInt2 & rhs) const noexcept;

            UInt2 operator^(const UInt2 & rhs) const noexcept;

            UInt2 operator<<(const UInt2 & rhs) const noexcept;

            UInt2 operator>>(const UInt2 & rhs) const noexcept;

            UInt2 operator||(const UInt2 & rhs) const noexcept;

            UInt2 operator&&(const UInt2 & rhs) const noexcept;

            Bool2 operator<(const UInt2 & rhs) const noexcept;

            Bool2 operator>(const UInt2 & rhs) const noexcept;

            Bool2 operator!=(const UInt2 & rhs) const noexcept;

            Bool2 operator==(const UInt2 & rhs) const noexcept;

            Bool2 operator>=(const UInt2 & rhs) const noexcept;

            Bool2 operator<=(const UInt2 & rhs) const noexcept;

            UInt2 operator~() const noexcept;

            UInt2 operator!() const noexcept;

            UInt2 operator++() noexcept;

            UInt2 operator++(int) noexcept;

            UInt2 operator--() noexcept;

            UInt2 operator--(int) noexcept;

            static UInt2 Random(unsigned int lower = 0, unsigned int upper = 6) noexcept;

            static const UInt2 One;
            static const UInt2 Zero;
            static const UInt2 UnitX;
            static const UInt2 UnitY;
        };
    }
}

