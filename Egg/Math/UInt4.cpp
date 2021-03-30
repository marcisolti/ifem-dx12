#include "UInt4.h"
#include <cmath>

namespace Egg {
    namespace Math {

        UInt4::UInt4(unsigned int x, unsigned int y, unsigned int z, unsigned int w) : x { x }, y { y }, z { z }, w { w }{ }

        UInt4::UInt4(unsigned int x, unsigned int y, const UInt2 & zw) : x { x }, y { y }, z { zw.x }, w { zw.y }{ }

        UInt4::UInt4(const UInt2 & xy, const UInt2 & zw) : x { xy.x }, y { xy.y }, z { zw.x }, w { zw.y }{ }

        UInt4::UInt4(const UInt2 & xy, unsigned int z, unsigned int w) : x { xy.x }, y { xy.y }, z { z }, w { w }{ }

        UInt4::UInt4(const UInt3 & xyz, unsigned int w) : x { xyz.x }, y { xyz.y }, z { xyz.z }, w { w }{ }

        UInt4::UInt4(unsigned int x, const UInt3 & yzw) : x { x }, y { yzw.x }, z { yzw.y }, w { yzw.z }{ }

        UInt4::UInt4(const UInt4 & xyzw) : x { xyzw.x }, y { xyzw.y }, z { xyzw.z }, w { xyzw.w }{ }

        UInt4::UInt4() : x{ 0U }, y{ 0U }, z{ 0U }, w{ 0U }{ }

        UInt4 & UInt4::operator=(const UInt4 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            this->w = rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator=(unsigned int rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            this->w = rhs;
            return *this;
        }

        UInt4 & UInt4::operator+=(const UInt4 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            this->w += rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator+=(unsigned int rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            this->z += rhs;
            this->w += rhs;
            return *this;
        }

        UInt4 & UInt4::operator-=(const UInt4 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            this->w -= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator-=(unsigned int rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            this->z -= rhs;
            this->w -= rhs;
            return *this;
        }

        UInt4 & UInt4::operator/=(const UInt4 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;
            this->w /= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator/=(unsigned int rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            this->w /= rhs;
            return *this;
        }

        UInt4 & UInt4::operator*=(const UInt4 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;
            this->w *= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator*=(unsigned int rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            this->w *= rhs;
            return *this;
        }

        UInt4 & UInt4::operator%=(const UInt4 & rhs) noexcept {
            this->x %= rhs.x;
            this->y %= rhs.y;
            this->z %= rhs.z;
            this->w %= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator%=(unsigned int rhs) noexcept {
            this->x %= rhs;
            this->y %= rhs;
            this->z %= rhs;
            this->w %= rhs;
            return *this;
        }

        UInt4 & UInt4::operator|=(const UInt4 & rhs) noexcept {
            this->x |= rhs.x;
            this->y |= rhs.y;
            this->z |= rhs.z;
            this->w |= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator|=(unsigned int rhs) noexcept {
            this->x |= rhs;
            this->y |= rhs;
            this->z |= rhs;
            this->w |= rhs;
            return *this;
        }

        UInt4 & UInt4::operator&=(const UInt4 & rhs) noexcept {
            this->x &= rhs.x;
            this->y &= rhs.y;
            this->z &= rhs.z;
            this->w &= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator&=(unsigned int rhs) noexcept {
            this->x &= rhs;
            this->y &= rhs;
            this->z &= rhs;
            this->w &= rhs;
            return *this;
        }

        UInt4 & UInt4::operator^=(const UInt4 & rhs) noexcept {
            this->x ^= rhs.x;
            this->y ^= rhs.y;
            this->z ^= rhs.z;
            this->w ^= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator^=(unsigned int rhs) noexcept {
            this->x ^= rhs;
            this->y ^= rhs;
            this->z ^= rhs;
            this->w ^= rhs;
            return *this;
        }

        UInt4 & UInt4::operator<<=(const UInt4 & rhs) noexcept {
            this->x <<= rhs.x;
            this->y <<= rhs.y;
            this->z <<= rhs.z;
            this->w <<= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator<<=(unsigned int rhs) noexcept {
            this->x <<= rhs;
            this->y <<= rhs;
            this->z <<= rhs;
            this->w <<= rhs;
            return *this;
        }

        UInt4 & UInt4::operator>>=(const UInt4 & rhs) noexcept {
            this->x >>= rhs.x;
            this->y >>= rhs.y;
            this->z >>= rhs.z;
            this->w >>= rhs.w;
            return *this;
        }

        UInt4 & UInt4::operator>>=(unsigned int rhs) noexcept {
            this->x >>= rhs;
            this->y >>= rhs;
            this->z >>= rhs;
            this->w >>= rhs;
            return *this;
        }

        UInt4 UInt4::operator*(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w };
        }

        UInt4 UInt4::operator/(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x / rhs.x, this->y / rhs.y, this->z / rhs.z, this->w / rhs.w };
        }

        UInt4 UInt4::operator+(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w };
        }

        UInt4 UInt4::operator-(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w };
        }

        UInt4 UInt4::operator%(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x % rhs.x, this->y % rhs.y, this->z % rhs.z, this->w % rhs.w };
        }

        UInt4 UInt4::operator|(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x | rhs.x, this->y | rhs.y, this->z | rhs.z, this->w | rhs.w };
        }

        UInt4 UInt4::operator&(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x & rhs.x, this->y & rhs.y, this->z & rhs.z, this->w & rhs.w };
        }

        UInt4 UInt4::operator^(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x ^ rhs.x, this->y ^ rhs.y, this->z ^ rhs.z, this->w ^ rhs.w };
        }

        UInt4 UInt4::operator<<(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x << rhs.x, this->y << rhs.y, this->z << rhs.z, this->w << rhs.w };
        }

        UInt4 UInt4::operator>>(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x >> rhs.x, this->y >> rhs.y, this->z >> rhs.z, this->w >> rhs.w };
        }

        UInt4 UInt4::operator||(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x || rhs.x, this->y || rhs.y, this->z || rhs.z, this->w || rhs.w };
        }

        UInt4 UInt4::operator&&(const UInt4 & rhs) const noexcept {
            return UInt4 { this->x && rhs.x, this->y && rhs.y, this->z && rhs.z, this->w && rhs.w };
        }

        Bool4 UInt4::operator<(const UInt4 & rhs) const noexcept {
            return Bool4 { x < rhs.x, y < rhs.y, z < rhs.z, w < rhs.w };
        }

        Bool4 UInt4::operator>(const UInt4 & rhs) const noexcept {
            return Bool4 { x > rhs.x, y > rhs.y, z > rhs.z, w > rhs.w };
        }

        Bool4 UInt4::operator!=(const UInt4 & rhs) const noexcept {
            return Bool4 { x != rhs.x, y != rhs.y, z != rhs.z, w != rhs.w };
        }

        Bool4 UInt4::operator==(const UInt4 & rhs) const noexcept {
            return Bool4 { x == rhs.x, y == rhs.y, z == rhs.z, w == rhs.w };
        }

        Bool4 UInt4::operator>=(const UInt4 & rhs) const noexcept {
            return Bool4 { x >= rhs.x, y >= rhs.y, z >= rhs.z, w >= rhs.w };
        }

        Bool4 UInt4::operator<=(const UInt4 & rhs) const noexcept {
            return Bool4 { x <= rhs.x, y <= rhs.y, z <= rhs.z, w <= rhs.w };
        }

        UInt4 UInt4::operator~() const noexcept {
            return UInt4 { ~x, ~y, ~z, ~w };
        }

        UInt4 UInt4::operator!() const noexcept {
            return UInt4 { !x, !y, !z, !w };
        }

        UInt4 UInt4::operator++() noexcept {
            return UInt4 { ++x, ++y, ++z, ++w };
        }

        UInt4 UInt4::operator++(int) noexcept {
            return UInt4 { x++, y++, z++, w++ };
        }

        UInt4 UInt4::operator--() noexcept {
            return UInt4 { --x, --y, --z, --w };
        }

        UInt4 UInt4::operator--(int) noexcept {
            return UInt4 { x--, y--, z--, w-- };
        }

        UInt4 UInt4::Random(unsigned int lower, unsigned int upper) noexcept {
            unsigned int range = upper - lower + 1;
             return UInt4 {  rand() % range + lower,
             rand() % range + lower,
             rand() % range + lower,
             rand() % range + lower };
        }

        const UInt4 UInt4::One { 1, 1, 1, 1 };
        const UInt4 UInt4::Zero { 0, 0, 0, 0 };
        const UInt4 UInt4::UnitX { 1, 0, 0, 0 };
        const UInt4 UInt4::UnitY { 0, 1, 0, 0 };
        const UInt4 UInt4::UnitZ { 0, 0, 1, 0 };
        const UInt4 UInt4::UnitW { 0, 0, 0, 1 };
    }
}

