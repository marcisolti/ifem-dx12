#pragma once

#include "Int2Swizzle.hpp"
#include "Int3Swizzle.hpp"
#include "Int4Swizzle.hpp"
#include "Bool2.h"
#include "Int3.h"
#include "Int4.h"

namespace Egg {
    namespace Math {

        class Int3;
        class Int4;
        class Bool2;
        class Bool3;
        class Bool4;

        class Int2 {
        public:
            union {
                struct {
                    int x;
                    int y;
                };

                Int2Swizzle<Int2, Bool2, 2, 0, 0> xx;
                Int2Swizzle<Int2, Bool2, 2, 0, 1> xy;
                Int2Swizzle<Int2, Bool2, 2, 1, 0> yx;
                Int2Swizzle<Int2, Bool2, 2, 1, 1> yy;

                Int3Swizzle<Int3, Bool3, 2, 0, 0, 0> xxx;
                Int3Swizzle<Int3, Bool3, 2, 0, 0, 1> xxy;
                Int3Swizzle<Int3, Bool3, 2, 0, 1, 0> xyx;
                Int3Swizzle<Int3, Bool3, 2, 0, 1, 1> xyy;
                Int3Swizzle<Int3, Bool3, 2, 1, 0, 0> yxx;
                Int3Swizzle<Int3, Bool3, 2, 1, 0, 1> yxy;
                Int3Swizzle<Int3, Bool3, 2, 1, 1, 0> yyx;
                Int3Swizzle<Int3, Bool3, 2, 1, 1, 1> yyy;

                Int4Swizzle<Int4, Bool4, 2, 0, 0, 0, 0> xxxx;
                Int4Swizzle<Int4, Bool4, 2, 0, 0, 1, 0> xxxy;
                Int4Swizzle<Int4, Bool4, 2, 0, 0, 0, 1> xxyx;
                Int4Swizzle<Int4, Bool4, 2, 0, 0, 1, 1> xxyy;
                Int4Swizzle<Int4, Bool4, 2, 0, 1, 0, 0> xyxx;
                Int4Swizzle<Int4, Bool4, 2, 0, 1, 1, 0> xyxy;
                Int4Swizzle<Int4, Bool4, 2, 0, 1, 0, 1> xyyx;
                Int4Swizzle<Int4, Bool4, 2, 0, 1, 1, 1> xyyy;
                Int4Swizzle<Int4, Bool4, 2, 1, 0, 0, 0> yxxx;
                Int4Swizzle<Int4, Bool4, 2, 1, 0, 1, 0> yxxy;
                Int4Swizzle<Int4, Bool4, 2, 1, 0, 0, 1> yxyx;
                Int4Swizzle<Int4, Bool4, 2, 1, 0, 1, 1> yxyy;
                Int4Swizzle<Int4, Bool4, 2, 1, 1, 0, 0> yyxx;
                Int4Swizzle<Int4, Bool4, 2, 1, 1, 1, 0> yyxy;
                Int4Swizzle<Int4, Bool4, 2, 1, 1, 0, 1> yyyx;
                Int4Swizzle<Int4, Bool4, 2, 1, 1, 1, 1> yyyy;
            };

            Int2(int x, int y);

            Int2(const Int2 & xy);

            Int2();

            Int2 & operator=(const Int2 & rhs) noexcept;
Int2 & operator=(int rhs) noexcept;

            Int2 & operator+=(const Int2 & rhs) noexcept;
Int2 & operator+=(int rhs) noexcept;

            Int2 & operator-=(const Int2 & rhs) noexcept;
Int2 & operator-=(int rhs) noexcept;

            Int2 & operator/=(const Int2 & rhs) noexcept;
Int2 & operator/=(int rhs) noexcept;

            Int2 & operator*=(const Int2 & rhs) noexcept;
Int2 & operator*=(int rhs) noexcept;

            Int2 & operator%=(const Int2 & rhs) noexcept;
Int2 & operator%=(int rhs) noexcept;

            Int2 & operator|=(const Int2 & rhs) noexcept;
Int2 & operator|=(int rhs) noexcept;

            Int2 & operator&=(const Int2 & rhs) noexcept;
Int2 & operator&=(int rhs) noexcept;

            Int2 & operator^=(const Int2 & rhs) noexcept;
Int2 & operator^=(int rhs) noexcept;

            Int2 & operator<<=(const Int2 & rhs) noexcept;
Int2 & operator<<=(int rhs) noexcept;

            Int2 & operator>>=(const Int2 & rhs) noexcept;
Int2 & operator>>=(int rhs) noexcept;

            Int2 operator*(const Int2 & rhs) const noexcept;

            Int2 operator/(const Int2 & rhs) const noexcept;

            Int2 operator+(const Int2 & rhs) const noexcept;

            Int2 operator-(const Int2 & rhs) const noexcept;

            Int2 operator%(const Int2 & rhs) const noexcept;

            Int2 operator|(const Int2 & rhs) const noexcept;

            Int2 operator&(const Int2 & rhs) const noexcept;

            Int2 operator^(const Int2 & rhs) const noexcept;

            Int2 operator<<(const Int2 & rhs) const noexcept;

            Int2 operator>>(const Int2 & rhs) const noexcept;

            Int2 operator||(const Int2 & rhs) const noexcept;

            Int2 operator&&(const Int2 & rhs) const noexcept;

            Bool2 operator<(const Int2 & rhs) const noexcept;

            Bool2 operator>(const Int2 & rhs) const noexcept;

            Bool2 operator!=(const Int2 & rhs) const noexcept;

            Bool2 operator==(const Int2 & rhs) const noexcept;

            Bool2 operator>=(const Int2 & rhs) const noexcept;

            Bool2 operator<=(const Int2 & rhs) const noexcept;

            Int2 operator~() const noexcept;

            Int2 operator!() const noexcept;

            Int2 operator++() noexcept;

            Int2 operator++(int) noexcept;

            Int2 operator--() noexcept;

            Int2 operator--(int) noexcept;

            static Int2 Random(int lower = 0, int upper = 6) noexcept;

            Int2 operator-() const noexcept;

            static const Int2 One;
            static const Int2 Zero;
            static const Int2 UnitX;
            static const Int2 UnitY;
        };
    }
}

