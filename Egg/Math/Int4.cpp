#include "Int4.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Int4::Int4(int x, int y, int z, int w) : x { x }, y { y }, z { z }, w { w }{ }

        Int4::Int4(int x, int y, const Int2 & zw) : x { x }, y { y }, z { zw.x }, w { zw.y }{ }

        Int4::Int4(const Int2 & xy, const Int2 & zw) : x { xy.x }, y { xy.y }, z { zw.x }, w { zw.y }{ }

        Int4::Int4(const Int2 & xy, int z, int w) : x { xy.x }, y { xy.y }, z { z }, w { w }{ }

        Int4::Int4(const Int3 & xyz, int w) : x { xyz.x }, y { xyz.y }, z { xyz.z }, w { w }{ }

        Int4::Int4(int x, const Int3 & yzw) : x { x }, y { yzw.x }, z { yzw.y }, w { yzw.z }{ }

        Int4::Int4(const Int4 & xyzw) : x { xyzw.x }, y { xyzw.y }, z { xyzw.z }, w { xyzw.w }{ }

        Int4::Int4() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 }{ }

        Int4 & Int4::operator=(const Int4 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            this->w = rhs.w;
            return *this;
        }

        Int4 & Int4::operator=(int rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            this->w = rhs;
            return *this;
        }

        Int4 & Int4::operator+=(const Int4 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            this->w += rhs.w;
            return *this;
        }

        Int4 & Int4::operator+=(int rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            this->z += rhs;
            this->w += rhs;
            return *this;
        }

        Int4 & Int4::operator-=(const Int4 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            this->w -= rhs.w;
            return *this;
        }

        Int4 & Int4::operator-=(int rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            this->z -= rhs;
            this->w -= rhs;
            return *this;
        }

        Int4 & Int4::operator/=(const Int4 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;
            this->w /= rhs.w;
            return *this;
        }

        Int4 & Int4::operator/=(int rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            this->w /= rhs;
            return *this;
        }

        Int4 & Int4::operator*=(const Int4 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;
            this->w *= rhs.w;
            return *this;
        }

        Int4 & Int4::operator*=(int rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            this->w *= rhs;
            return *this;
        }

        Int4 & Int4::operator%=(const Int4 & rhs) noexcept {
            this->x %= rhs.x;
            this->y %= rhs.y;
            this->z %= rhs.z;
            this->w %= rhs.w;
            return *this;
        }

        Int4 & Int4::operator%=(int rhs) noexcept {
            this->x %= rhs;
            this->y %= rhs;
            this->z %= rhs;
            this->w %= rhs;
            return *this;
        }

        Int4 & Int4::operator|=(const Int4 & rhs) noexcept {
            this->x |= rhs.x;
            this->y |= rhs.y;
            this->z |= rhs.z;
            this->w |= rhs.w;
            return *this;
        }

        Int4 & Int4::operator|=(int rhs) noexcept {
            this->x |= rhs;
            this->y |= rhs;
            this->z |= rhs;
            this->w |= rhs;
            return *this;
        }

        Int4 & Int4::operator&=(const Int4 & rhs) noexcept {
            this->x &= rhs.x;
            this->y &= rhs.y;
            this->z &= rhs.z;
            this->w &= rhs.w;
            return *this;
        }

        Int4 & Int4::operator&=(int rhs) noexcept {
            this->x &= rhs;
            this->y &= rhs;
            this->z &= rhs;
            this->w &= rhs;
            return *this;
        }

        Int4 & Int4::operator^=(const Int4 & rhs) noexcept {
            this->x ^= rhs.x;
            this->y ^= rhs.y;
            this->z ^= rhs.z;
            this->w ^= rhs.w;
            return *this;
        }

        Int4 & Int4::operator^=(int rhs) noexcept {
            this->x ^= rhs;
            this->y ^= rhs;
            this->z ^= rhs;
            this->w ^= rhs;
            return *this;
        }

        Int4 & Int4::operator<<=(const Int4 & rhs) noexcept {
            this->x <<= rhs.x;
            this->y <<= rhs.y;
            this->z <<= rhs.z;
            this->w <<= rhs.w;
            return *this;
        }

        Int4 & Int4::operator<<=(int rhs) noexcept {
            this->x <<= rhs;
            this->y <<= rhs;
            this->z <<= rhs;
            this->w <<= rhs;
            return *this;
        }

        Int4 & Int4::operator>>=(const Int4 & rhs) noexcept {
            this->x >>= rhs.x;
            this->y >>= rhs.y;
            this->z >>= rhs.z;
            this->w >>= rhs.w;
            return *this;
        }

        Int4 & Int4::operator>>=(int rhs) noexcept {
            this->x >>= rhs;
            this->y >>= rhs;
            this->z >>= rhs;
            this->w >>= rhs;
            return *this;
        }

        Int4 Int4::operator*(const Int4 & rhs) const noexcept {
            return Int4 { this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w };
        }

        Int4 Int4::operator/(const Int4 & rhs) const noexcept {
            return Int4 { this->x / rhs.x, this->y / rhs.y, this->z / rhs.z, this->w / rhs.w };
        }

        Int4 Int4::operator+(const Int4 & rhs) const noexcept {
            return Int4 { this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w };
        }

        Int4 Int4::operator-(const Int4 & rhs) const noexcept {
            return Int4 { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w };
        }

        Int4 Int4::operator%(const Int4 & rhs) const noexcept {
            return Int4 { this->x % rhs.x, this->y % rhs.y, this->z % rhs.z, this->w % rhs.w };
        }

        Int4 Int4::operator|(const Int4 & rhs) const noexcept {
            return Int4 { this->x | rhs.x, this->y | rhs.y, this->z | rhs.z, this->w | rhs.w };
        }

        Int4 Int4::operator&(const Int4 & rhs) const noexcept {
            return Int4 { this->x & rhs.x, this->y & rhs.y, this->z & rhs.z, this->w & rhs.w };
        }

        Int4 Int4::operator^(const Int4 & rhs) const noexcept {
            return Int4 { this->x ^ rhs.x, this->y ^ rhs.y, this->z ^ rhs.z, this->w ^ rhs.w };
        }

        Int4 Int4::operator<<(const Int4 & rhs) const noexcept {
            return Int4 { this->x << rhs.x, this->y << rhs.y, this->z << rhs.z, this->w << rhs.w };
        }

        Int4 Int4::operator>>(const Int4 & rhs) const noexcept {
            return Int4 { this->x >> rhs.x, this->y >> rhs.y, this->z >> rhs.z, this->w >> rhs.w };
        }

        Int4 Int4::operator||(const Int4 & rhs) const noexcept {
            return Int4 { this->x || rhs.x, this->y || rhs.y, this->z || rhs.z, this->w || rhs.w };
        }

        Int4 Int4::operator&&(const Int4 & rhs) const noexcept {
            return Int4 { this->x && rhs.x, this->y && rhs.y, this->z && rhs.z, this->w && rhs.w };
        }

        Bool4 Int4::operator<(const Int4 & rhs) const noexcept {
            return Bool4 { x < rhs.x, y < rhs.y, z < rhs.z, w < rhs.w };
        }

        Bool4 Int4::operator>(const Int4 & rhs) const noexcept {
            return Bool4 { x > rhs.x, y > rhs.y, z > rhs.z, w > rhs.w };
        }

        Bool4 Int4::operator!=(const Int4 & rhs) const noexcept {
            return Bool4 { x != rhs.x, y != rhs.y, z != rhs.z, w != rhs.w };
        }

        Bool4 Int4::operator==(const Int4 & rhs) const noexcept {
            return Bool4 { x == rhs.x, y == rhs.y, z == rhs.z, w == rhs.w };
        }

        Bool4 Int4::operator>=(const Int4 & rhs) const noexcept {
            return Bool4 { x >= rhs.x, y >= rhs.y, z >= rhs.z, w >= rhs.w };
        }

        Bool4 Int4::operator<=(const Int4 & rhs) const noexcept {
            return Bool4 { x <= rhs.x, y <= rhs.y, z <= rhs.z, w <= rhs.w };
        }

        Int4 Int4::operator~() const noexcept {
            return Int4 { ~x, ~y, ~z, ~w };
        }

        Int4 Int4::operator!() const noexcept {
            return Int4 { !x, !y, !z, !w };
        }

        Int4 Int4::operator++() noexcept {
            return Int4 { ++x, ++y, ++z, ++w };
        }

        Int4 Int4::operator++(int) noexcept {
            return Int4 { x++, y++, z++, w++ };
        }

        Int4 Int4::operator--() noexcept {
            return Int4 { --x, --y, --z, --w };
        }

        Int4 Int4::operator--(int) noexcept {
            return Int4 { x--, y--, z--, w-- };
        }

        Int4 Int4::Random(int lower, int upper) noexcept {
            int range = upper - lower + 1;
             return Int4 {  rand() % range + lower,
             rand() % range + lower,
             rand() % range + lower,
             rand() % range + lower };
        }

        Int4 Int4::operator-() const noexcept {
            return Int4 { -x, -y, -z, -w };
        }

        const Int4 Int4::One { 1, 1, 1, 1 };
        const Int4 Int4::Zero { 0, 0, 0, 0 };
        const Int4 Int4::UnitX { 1, 0, 0, 0 };
        const Int4 Int4::UnitY { 0, 1, 0, 0 };
        const Int4 Int4::UnitZ { 0, 0, 1, 0 };
        const Int4 Int4::UnitW { 0, 0, 0, 1 };
    }
}

