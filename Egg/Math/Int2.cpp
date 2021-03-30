#include "Int2.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Int2::Int2(int x, int y) : x { x }, y { y }{ }

        Int2::Int2(const Int2 & xy) : x { xy.x }, y { xy.y }{ }

        Int2::Int2() : x{ 0 }, y{ 0 }{ }

        Int2 & Int2::operator=(const Int2 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            return *this;
        }

        Int2 & Int2::operator=(int rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            return *this;
        }

        Int2 & Int2::operator+=(const Int2 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        Int2 & Int2::operator+=(int rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            return *this;
        }

        Int2 & Int2::operator-=(const Int2 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            return *this;
        }

        Int2 & Int2::operator-=(int rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            return *this;
        }

        Int2 & Int2::operator/=(const Int2 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            return *this;
        }

        Int2 & Int2::operator/=(int rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            return *this;
        }

        Int2 & Int2::operator*=(const Int2 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            return *this;
        }

        Int2 & Int2::operator*=(int rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            return *this;
        }

        Int2 & Int2::operator%=(const Int2 & rhs) noexcept {
            this->x %= rhs.x;
            this->y %= rhs.y;
            return *this;
        }

        Int2 & Int2::operator%=(int rhs) noexcept {
            this->x %= rhs;
            this->y %= rhs;
            return *this;
        }

        Int2 & Int2::operator|=(const Int2 & rhs) noexcept {
            this->x |= rhs.x;
            this->y |= rhs.y;
            return *this;
        }

        Int2 & Int2::operator|=(int rhs) noexcept {
            this->x |= rhs;
            this->y |= rhs;
            return *this;
        }

        Int2 & Int2::operator&=(const Int2 & rhs) noexcept {
            this->x &= rhs.x;
            this->y &= rhs.y;
            return *this;
        }

        Int2 & Int2::operator&=(int rhs) noexcept {
            this->x &= rhs;
            this->y &= rhs;
            return *this;
        }

        Int2 & Int2::operator^=(const Int2 & rhs) noexcept {
            this->x ^= rhs.x;
            this->y ^= rhs.y;
            return *this;
        }

        Int2 & Int2::operator^=(int rhs) noexcept {
            this->x ^= rhs;
            this->y ^= rhs;
            return *this;
        }

        Int2 & Int2::operator<<=(const Int2 & rhs) noexcept {
            this->x <<= rhs.x;
            this->y <<= rhs.y;
            return *this;
        }

        Int2 & Int2::operator<<=(int rhs) noexcept {
            this->x <<= rhs;
            this->y <<= rhs;
            return *this;
        }

        Int2 & Int2::operator>>=(const Int2 & rhs) noexcept {
            this->x >>= rhs.x;
            this->y >>= rhs.y;
            return *this;
        }

        Int2 & Int2::operator>>=(int rhs) noexcept {
            this->x >>= rhs;
            this->y >>= rhs;
            return *this;
        }

        Int2 Int2::operator*(const Int2 & rhs) const noexcept {
            return Int2 { this->x * rhs.x, this->y * rhs.y };
        }

        Int2 Int2::operator/(const Int2 & rhs) const noexcept {
            return Int2 { this->x / rhs.x, this->y / rhs.y };
        }

        Int2 Int2::operator+(const Int2 & rhs) const noexcept {
            return Int2 { this->x + rhs.x, this->y + rhs.y };
        }

        Int2 Int2::operator-(const Int2 & rhs) const noexcept {
            return Int2 { this->x - rhs.x, this->y - rhs.y };
        }

        Int2 Int2::operator%(const Int2 & rhs) const noexcept {
            return Int2 { this->x % rhs.x, this->y % rhs.y };
        }

        Int2 Int2::operator|(const Int2 & rhs) const noexcept {
            return Int2 { this->x | rhs.x, this->y | rhs.y };
        }

        Int2 Int2::operator&(const Int2 & rhs) const noexcept {
            return Int2 { this->x & rhs.x, this->y & rhs.y };
        }

        Int2 Int2::operator^(const Int2 & rhs) const noexcept {
            return Int2 { this->x ^ rhs.x, this->y ^ rhs.y };
        }

        Int2 Int2::operator<<(const Int2 & rhs) const noexcept {
            return Int2 { this->x << rhs.x, this->y << rhs.y };
        }

        Int2 Int2::operator>>(const Int2 & rhs) const noexcept {
            return Int2 { this->x >> rhs.x, this->y >> rhs.y };
        }

        Int2 Int2::operator||(const Int2 & rhs) const noexcept {
            return Int2 { this->x || rhs.x, this->y || rhs.y };
        }

        Int2 Int2::operator&&(const Int2 & rhs) const noexcept {
            return Int2 { this->x && rhs.x, this->y && rhs.y };
        }

        Bool2 Int2::operator<(const Int2 & rhs) const noexcept {
            return Bool2 { x < rhs.x, y < rhs.y };
        }

        Bool2 Int2::operator>(const Int2 & rhs) const noexcept {
            return Bool2 { x > rhs.x, y > rhs.y };
        }

        Bool2 Int2::operator!=(const Int2 & rhs) const noexcept {
            return Bool2 { x != rhs.x, y != rhs.y };
        }

        Bool2 Int2::operator==(const Int2 & rhs) const noexcept {
            return Bool2 { x == rhs.x, y == rhs.y };
        }

        Bool2 Int2::operator>=(const Int2 & rhs) const noexcept {
            return Bool2 { x >= rhs.x, y >= rhs.y };
        }

        Bool2 Int2::operator<=(const Int2 & rhs) const noexcept {
            return Bool2 { x <= rhs.x, y <= rhs.y };
        }

        Int2 Int2::operator~() const noexcept {
            return Int2 { ~x, ~y };
        }

        Int2 Int2::operator!() const noexcept {
            return Int2 { !x, !y };
        }

        Int2 Int2::operator++() noexcept {
            return Int2 { ++x, ++y };
        }

        Int2 Int2::operator++(int) noexcept {
            return Int2 { x++, y++ };
        }

        Int2 Int2::operator--() noexcept {
            return Int2 { --x, --y };
        }

        Int2 Int2::operator--(int) noexcept {
            return Int2 { x--, y-- };
        }

        Int2 Int2::Random(int lower, int upper) noexcept {
            int range = upper - lower + 1;
             return Int2 {  rand() % range + lower,
             rand() % range + lower };
        }

        Int2 Int2::operator-() const noexcept {
            return Int2 { -x, -y };
        }

        const Int2 Int2::One { 1, 1 };
        const Int2 Int2::Zero { 0, 0 };
        const Int2 Int2::UnitX { 1, 0 };
        const Int2 Int2::UnitY { 0, 1 };
    }
}

