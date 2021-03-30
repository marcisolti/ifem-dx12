#pragma once

#include "UInt2Swizzle.hpp"
#include "UInt3Swizzle.hpp"
#include "UInt4Swizzle.hpp"
#include "Bool1.h"

namespace Egg {
    namespace Math {

        class UInt1 {
        public:
            union {
                struct {
                    unsigned int x;
                };
            };

            UInt1(unsigned int x);

            UInt1();

            UInt1 & operator=(const UInt1 & rhs) noexcept;
UInt1 & operator=(unsigned int rhs) noexcept;

            UInt1 & operator+=(const UInt1 & rhs) noexcept;
UInt1 & operator+=(unsigned int rhs) noexcept;

            UInt1 & operator-=(const UInt1 & rhs) noexcept;
UInt1 & operator-=(unsigned int rhs) noexcept;

            UInt1 & operator/=(const UInt1 & rhs) noexcept;
UInt1 & operator/=(unsigned int rhs) noexcept;

            UInt1 & operator*=(const UInt1 & rhs) noexcept;
UInt1 & operator*=(unsigned int rhs) noexcept;

            UInt1 & operator%=(const UInt1 & rhs) noexcept;
UInt1 & operator%=(unsigned int rhs) noexcept;

            UInt1 & operator|=(const UInt1 & rhs) noexcept;
UInt1 & operator|=(unsigned int rhs) noexcept;

            UInt1 & operator&=(const UInt1 & rhs) noexcept;
UInt1 & operator&=(unsigned int rhs) noexcept;

            UInt1 & operator^=(const UInt1 & rhs) noexcept;
UInt1 & operator^=(unsigned int rhs) noexcept;

            UInt1 & operator<<=(const UInt1 & rhs) noexcept;
UInt1 & operator<<=(unsigned int rhs) noexcept;

            UInt1 & operator>>=(const UInt1 & rhs) noexcept;
UInt1 & operator>>=(unsigned int rhs) noexcept;

            UInt1 operator*(const UInt1 & rhs) const noexcept;

            UInt1 operator/(const UInt1 & rhs) const noexcept;

            UInt1 operator+(const UInt1 & rhs) const noexcept;

            UInt1 operator-(const UInt1 & rhs) const noexcept;

            UInt1 operator%(const UInt1 & rhs) const noexcept;

            UInt1 operator|(const UInt1 & rhs) const noexcept;

            UInt1 operator&(const UInt1 & rhs) const noexcept;

            UInt1 operator^(const UInt1 & rhs) const noexcept;

            UInt1 operator<<(const UInt1 & rhs) const noexcept;

            UInt1 operator>>(const UInt1 & rhs) const noexcept;

            UInt1 operator||(const UInt1 & rhs) const noexcept;

            UInt1 operator&&(const UInt1 & rhs) const noexcept;

            Bool1 operator<(const UInt1 & rhs) const noexcept;

            Bool1 operator>(const UInt1 & rhs) const noexcept;

            Bool1 operator!=(const UInt1 & rhs) const noexcept;

            Bool1 operator==(const UInt1 & rhs) const noexcept;

            Bool1 operator>=(const UInt1 & rhs) const noexcept;

            Bool1 operator<=(const UInt1 & rhs) const noexcept;

            UInt1 operator~() const noexcept;

            UInt1 operator!() const noexcept;

            UInt1 operator++() noexcept;

            UInt1 operator++(int) noexcept;

            UInt1 operator--() noexcept;

            UInt1 operator--(int) noexcept;

            static UInt1 Random(unsigned int lower = 0, unsigned int upper = 6) noexcept;

        };
    }
}

