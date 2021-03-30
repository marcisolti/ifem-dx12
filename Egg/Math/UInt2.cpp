#include "UInt2.h"
#include <cmath>

namespace Egg {
    namespace Math {

        UInt2::UInt2(unsigned int x, unsigned int y) : x { x }, y { y }{ }

        UInt2::UInt2(const UInt2 & xy) : x { xy.x }, y { xy.y }{ }

        UInt2::UInt2() : x{ 0U }, y{ 0U }{ }

        UInt2 & UInt2::operator=(const UInt2 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator=(unsigned int rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            return *this;
        }

        UInt2 & UInt2::operator+=(const UInt2 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator+=(unsigned int rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            return *this;
        }

        UInt2 & UInt2::operator-=(const UInt2 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator-=(unsigned int rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            return *this;
        }

        UInt2 & UInt2::operator/=(const UInt2 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator/=(unsigned int rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            return *this;
        }

        UInt2 & UInt2::operator*=(const UInt2 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator*=(unsigned int rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            return *this;
        }

        UInt2 & UInt2::operator%=(const UInt2 & rhs) noexcept {
            this->x %= rhs.x;
            this->y %= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator%=(unsigned int rhs) noexcept {
            this->x %= rhs;
            this->y %= rhs;
            return *this;
        }

        UInt2 & UInt2::operator|=(const UInt2 & rhs) noexcept {
            this->x |= rhs.x;
            this->y |= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator|=(unsigned int rhs) noexcept {
            this->x |= rhs;
            this->y |= rhs;
            return *this;
        }

        UInt2 & UInt2::operator&=(const UInt2 & rhs) noexcept {
            this->x &= rhs.x;
            this->y &= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator&=(unsigned int rhs) noexcept {
            this->x &= rhs;
            this->y &= rhs;
            return *this;
        }

        UInt2 & UInt2::operator^=(const UInt2 & rhs) noexcept {
            this->x ^= rhs.x;
            this->y ^= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator^=(unsigned int rhs) noexcept {
            this->x ^= rhs;
            this->y ^= rhs;
            return *this;
        }

        UInt2 & UInt2::operator<<=(const UInt2 & rhs) noexcept {
            this->x <<= rhs.x;
            this->y <<= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator<<=(unsigned int rhs) noexcept {
            this->x <<= rhs;
            this->y <<= rhs;
            return *this;
        }

        UInt2 & UInt2::operator>>=(const UInt2 & rhs) noexcept {
            this->x >>= rhs.x;
            this->y >>= rhs.y;
            return *this;
        }

        UInt2 & UInt2::operator>>=(unsigned int rhs) noexcept {
            this->x >>= rhs;
            this->y >>= rhs;
            return *this;
        }

        UInt2 UInt2::operator*(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x * rhs.x, this->y * rhs.y };
        }

        UInt2 UInt2::operator/(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x / rhs.x, this->y / rhs.y };
        }

        UInt2 UInt2::operator+(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x + rhs.x, this->y + rhs.y };
        }

        UInt2 UInt2::operator-(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x - rhs.x, this->y - rhs.y };
        }

        UInt2 UInt2::operator%(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x % rhs.x, this->y % rhs.y };
        }

        UInt2 UInt2::operator|(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x | rhs.x, this->y | rhs.y };
        }

        UInt2 UInt2::operator&(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x & rhs.x, this->y & rhs.y };
        }

        UInt2 UInt2::operator^(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x ^ rhs.x, this->y ^ rhs.y };
        }

        UInt2 UInt2::operator<<(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x << rhs.x, this->y << rhs.y };
        }

        UInt2 UInt2::operator>>(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x >> rhs.x, this->y >> rhs.y };
        }

        UInt2 UInt2::operator||(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x || rhs.x, this->y || rhs.y };
        }

        UInt2 UInt2::operator&&(const UInt2 & rhs) const noexcept {
            return UInt2 { this->x && rhs.x, this->y && rhs.y };
        }

        Bool2 UInt2::operator<(const UInt2 & rhs) const noexcept {
            return Bool2 { x < rhs.x, y < rhs.y };
        }

        Bool2 UInt2::operator>(const UInt2 & rhs) const noexcept {
            return Bool2 { x > rhs.x, y > rhs.y };
        }

        Bool2 UInt2::operator!=(const UInt2 & rhs) const noexcept {
            return Bool2 { x != rhs.x, y != rhs.y };
        }

        Bool2 UInt2::operator==(const UInt2 & rhs) const noexcept {
            return Bool2 { x == rhs.x, y == rhs.y };
        }

        Bool2 UInt2::operator>=(const UInt2 & rhs) const noexcept {
            return Bool2 { x >= rhs.x, y >= rhs.y };
        }

        Bool2 UInt2::operator<=(const UInt2 & rhs) const noexcept {
            return Bool2 { x <= rhs.x, y <= rhs.y };
        }

        UInt2 UInt2::operator~() const noexcept {
            return UInt2 { ~x, ~y };
        }

        UInt2 UInt2::operator!() const noexcept {
            return UInt2 { !x, !y };
        }

        UInt2 UInt2::operator++() noexcept {
            return UInt2 { ++x, ++y };
        }

        UInt2 UInt2::operator++(int) noexcept {
            return UInt2 { x++, y++ };
        }

        UInt2 UInt2::operator--() noexcept {
            return UInt2 { --x, --y };
        }

        UInt2 UInt2::operator--(int) noexcept {
            return UInt2 { x--, y-- };
        }

        UInt2 UInt2::Random(unsigned int lower, unsigned int upper) noexcept {
            unsigned int range = upper - lower + 1;
             return UInt2 {  rand() % range + lower,
             rand() % range + lower };
        }

        const UInt2 UInt2::One { 1, 1 };
        const UInt2 UInt2::Zero { 0, 0 };
        const UInt2 UInt2::UnitX { 1, 0 };
        const UInt2 UInt2::UnitY { 0, 1 };
    }
}

