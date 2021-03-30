#pragma once

#include "Int2Swizzle.hpp"
#include "Int3Swizzle.hpp"
#include "Int4Swizzle.hpp"
#include "Bool1.h"

namespace Egg {
    namespace Math {

        class Int1 {
        public:
            union {
                struct {
                    int x;
                };
            };

            Int1(int x);

            Int1();

            Int1 & operator=(const Int1 & rhs) noexcept;
Int1 & operator=(int rhs) noexcept;

            Int1 & operator+=(const Int1 & rhs) noexcept;
Int1 & operator+=(int rhs) noexcept;

            Int1 & operator-=(const Int1 & rhs) noexcept;
Int1 & operator-=(int rhs) noexcept;

            Int1 & operator/=(const Int1 & rhs) noexcept;
Int1 & operator/=(int rhs) noexcept;

            Int1 & operator*=(const Int1 & rhs) noexcept;
Int1 & operator*=(int rhs) noexcept;

            Int1 & operator%=(const Int1 & rhs) noexcept;
Int1 & operator%=(int rhs) noexcept;

            Int1 & operator|=(const Int1 & rhs) noexcept;
Int1 & operator|=(int rhs) noexcept;

            Int1 & operator&=(const Int1 & rhs) noexcept;
Int1 & operator&=(int rhs) noexcept;

            Int1 & operator^=(const Int1 & rhs) noexcept;
Int1 & operator^=(int rhs) noexcept;

            Int1 & operator<<=(const Int1 & rhs) noexcept;
Int1 & operator<<=(int rhs) noexcept;

            Int1 & operator>>=(const Int1 & rhs) noexcept;
Int1 & operator>>=(int rhs) noexcept;

            Int1 operator*(const Int1 & rhs) const noexcept;

            Int1 operator/(const Int1 & rhs) const noexcept;

            Int1 operator+(const Int1 & rhs) const noexcept;

            Int1 operator-(const Int1 & rhs) const noexcept;

            Int1 operator%(const Int1 & rhs) const noexcept;

            Int1 operator|(const Int1 & rhs) const noexcept;

            Int1 operator&(const Int1 & rhs) const noexcept;

            Int1 operator^(const Int1 & rhs) const noexcept;

            Int1 operator<<(const Int1 & rhs) const noexcept;

            Int1 operator>>(const Int1 & rhs) const noexcept;

            Int1 operator||(const Int1 & rhs) const noexcept;

            Int1 operator&&(const Int1 & rhs) const noexcept;

            Bool1 operator<(const Int1 & rhs) const noexcept;

            Bool1 operator>(const Int1 & rhs) const noexcept;

            Bool1 operator!=(const Int1 & rhs) const noexcept;

            Bool1 operator==(const Int1 & rhs) const noexcept;

            Bool1 operator>=(const Int1 & rhs) const noexcept;

            Bool1 operator<=(const Int1 & rhs) const noexcept;

            Int1 operator~() const noexcept;

            Int1 operator!() const noexcept;

            Int1 operator++() noexcept;

            Int1 operator++(int) noexcept;

            Int1 operator--() noexcept;

            Int1 operator--(int) noexcept;

            static Int1 Random(int lower = 0, int upper = 6) noexcept;

            Int1 operator-() const noexcept;

        };
    }
}

