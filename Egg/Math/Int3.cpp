#include "Int3.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Int3::Int3(int x, int y, int z) : x { x }, y { y }, z { z }{ }

        Int3::Int3(int x, const Int2 & yz) : x { x }, y { yz.x }, z { yz.y }{ }

        Int3::Int3(const Int2 & xy, int z) : x { xy.x }, y { xy.y }, z { z }{ }

        Int3::Int3(const Int3 & xyz) : x { xyz.x }, y { xyz.y }, z { xyz.z }{ }

        Int3::Int3() : x{ 0 }, y{ 0 }, z{ 0 }{ }

        Int3 & Int3::operator=(const Int3 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            return *this;
        }

        Int3 & Int3::operator=(int rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            return *this;
        }

        Int3 & Int3::operator+=(const Int3 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            return *this;
        }

        Int3 & Int3::operator+=(int rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            this->z += rhs;
            return *this;
        }

        Int3 & Int3::operator-=(const Int3 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            return *this;
        }

        Int3 & Int3::operator-=(int rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            this->z -= rhs;
            return *this;
        }

        Int3 & Int3::operator/=(const Int3 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;
            return *this;
        }

        Int3 & Int3::operator/=(int rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            return *this;
        }

        Int3 & Int3::operator*=(const Int3 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;
            return *this;
        }

        Int3 & Int3::operator*=(int rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            return *this;
        }

        Int3 & Int3::operator%=(const Int3 & rhs) noexcept {
            this->x %= rhs.x;
            this->y %= rhs.y;
            this->z %= rhs.z;
            return *this;
        }

        Int3 & Int3::operator%=(int rhs) noexcept {
            this->x %= rhs;
            this->y %= rhs;
            this->z %= rhs;
            return *this;
        }

        Int3 & Int3::operator|=(const Int3 & rhs) noexcept {
            this->x |= rhs.x;
            this->y |= rhs.y;
            this->z |= rhs.z;
            return *this;
        }

        Int3 & Int3::operator|=(int rhs) noexcept {
            this->x |= rhs;
            this->y |= rhs;
            this->z |= rhs;
            return *this;
        }

        Int3 & Int3::operator&=(const Int3 & rhs) noexcept {
            this->x &= rhs.x;
            this->y &= rhs.y;
            this->z &= rhs.z;
            return *this;
        }

        Int3 & Int3::operator&=(int rhs) noexcept {
            this->x &= rhs;
            this->y &= rhs;
            this->z &= rhs;
            return *this;
        }

        Int3 & Int3::operator^=(const Int3 & rhs) noexcept {
            this->x ^= rhs.x;
            this->y ^= rhs.y;
            this->z ^= rhs.z;
            return *this;
        }

        Int3 & Int3::operator^=(int rhs) noexcept {
            this->x ^= rhs;
            this->y ^= rhs;
            this->z ^= rhs;
            return *this;
        }

        Int3 & Int3::operator<<=(const Int3 & rhs) noexcept {
            this->x <<= rhs.x;
            this->y <<= rhs.y;
            this->z <<= rhs.z;
            return *this;
        }

        Int3 & Int3::operator<<=(int rhs) noexcept {
            this->x <<= rhs;
            this->y <<= rhs;
            this->z <<= rhs;
            return *this;
        }

        Int3 & Int3::operator>>=(const Int3 & rhs) noexcept {
            this->x >>= rhs.x;
            this->y >>= rhs.y;
            this->z >>= rhs.z;
            return *this;
        }

        Int3 & Int3::operator>>=(int rhs) noexcept {
            this->x >>= rhs;
            this->y >>= rhs;
            this->z >>= rhs;
            return *this;
        }

        Int3 Int3::operator*(const Int3 & rhs) const noexcept {
            return Int3 { this->x * rhs.x, this->y * rhs.y, this->z * rhs.z };
        }

        Int3 Int3::operator/(const Int3 & rhs) const noexcept {
            return Int3 { this->x / rhs.x, this->y / rhs.y, this->z / rhs.z };
        }

        Int3 Int3::operator+(const Int3 & rhs) const noexcept {
            return Int3 { this->x + rhs.x, this->y + rhs.y, this->z + rhs.z };
        }

        Int3 Int3::operator-(const Int3 & rhs) const noexcept {
            return Int3 { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z };
        }

        Int3 Int3::operator%(const Int3 & rhs) const noexcept {
            return Int3 { this->x % rhs.x, this->y % rhs.y, this->z % rhs.z };
        }

        Int3 Int3::operator|(const Int3 & rhs) const noexcept {
            return Int3 { this->x | rhs.x, this->y | rhs.y, this->z | rhs.z };
        }

        Int3 Int3::operator&(const Int3 & rhs) const noexcept {
            return Int3 { this->x & rhs.x, this->y & rhs.y, this->z & rhs.z };
        }

        Int3 Int3::operator^(const Int3 & rhs) const noexcept {
            return Int3 { this->x ^ rhs.x, this->y ^ rhs.y, this->z ^ rhs.z };
        }

        Int3 Int3::operator<<(const Int3 & rhs) const noexcept {
            return Int3 { this->x << rhs.x, this->y << rhs.y, this->z << rhs.z };
        }

        Int3 Int3::operator>>(const Int3 & rhs) const noexcept {
            return Int3 { this->x >> rhs.x, this->y >> rhs.y, this->z >> rhs.z };
        }

        Int3 Int3::operator||(const Int3 & rhs) const noexcept {
            return Int3 { this->x || rhs.x, this->y || rhs.y, this->z || rhs.z };
        }

        Int3 Int3::operator&&(const Int3 & rhs) const noexcept {
            return Int3 { this->x && rhs.x, this->y && rhs.y, this->z && rhs.z };
        }

        Bool3 Int3::operator<(const Int3 & rhs) const noexcept {
            return Bool3 { x < rhs.x, y < rhs.y, z < rhs.z };
        }

        Bool3 Int3::operator>(const Int3 & rhs) const noexcept {
            return Bool3 { x > rhs.x, y > rhs.y, z > rhs.z };
        }

        Bool3 Int3::operator!=(const Int3 & rhs) const noexcept {
            return Bool3 { x != rhs.x, y != rhs.y, z != rhs.z };
        }

        Bool3 Int3::operator==(const Int3 & rhs) const noexcept {
            return Bool3 { x == rhs.x, y == rhs.y, z == rhs.z };
        }

        Bool3 Int3::operator>=(const Int3 & rhs) const noexcept {
            return Bool3 { x >= rhs.x, y >= rhs.y, z >= rhs.z };
        }

        Bool3 Int3::operator<=(const Int3 & rhs) const noexcept {
            return Bool3 { x <= rhs.x, y <= rhs.y, z <= rhs.z };
        }

        Int3 Int3::operator~() const noexcept {
            return Int3 { ~x, ~y, ~z };
        }

        Int3 Int3::operator!() const noexcept {
            return Int3 { !x, !y, !z };
        }

        Int3 Int3::operator++() noexcept {
            return Int3 { ++x, ++y, ++z };
        }

        Int3 Int3::operator++(int) noexcept {
            return Int3 { x++, y++, z++ };
        }

        Int3 Int3::operator--() noexcept {
            return Int3 { --x, --y, --z };
        }

        Int3 Int3::operator--(int) noexcept {
            return Int3 { x--, y--, z-- };
        }

        Int3 Int3::Random(int lower, int upper) noexcept {
            int range = upper - lower + 1;
             return Int3 {  rand() % range + lower,
             rand() % range + lower,
             rand() % range + lower };
        }

        Int3 Int3::operator-() const noexcept {
            return Int3 { -x, -y, -z };
        }

        const Int3 Int3::One { 1, 1, 1 };
        const Int3 Int3::Zero { 0, 0, 0 };
        const Int3 Int3::UnitX { 1, 0, 0 };
        const Int3 Int3::UnitY { 0, 1, 0 };
        const Int3 Int3::UnitZ { 0, 0, 1 };
    }
}

