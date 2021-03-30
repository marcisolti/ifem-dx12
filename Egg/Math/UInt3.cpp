#include "UInt3.h"
#include <cmath>

namespace Egg {
    namespace Math {

        UInt3::UInt3(unsigned int x, unsigned int y, unsigned int z) : x { x }, y { y }, z { z }{ }

        UInt3::UInt3(unsigned int x, const UInt2 & yz) : x { x }, y { yz.x }, z { yz.y }{ }

        UInt3::UInt3(const UInt2 & xy, unsigned int z) : x { xy.x }, y { xy.y }, z { z }{ }

        UInt3::UInt3(const UInt3 & xyz) : x { xyz.x }, y { xyz.y }, z { xyz.z }{ }

        UInt3::UInt3() : x{ 0U }, y{ 0U }, z{ 0U }{ }

        UInt3 & UInt3::operator=(const UInt3 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator=(unsigned int rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            return *this;
        }

        UInt3 & UInt3::operator+=(const UInt3 & rhs) noexcept {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator+=(unsigned int rhs) noexcept {
            this->x += rhs;
            this->y += rhs;
            this->z += rhs;
            return *this;
        }

        UInt3 & UInt3::operator-=(const UInt3 & rhs) noexcept {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator-=(unsigned int rhs) noexcept {
            this->x -= rhs;
            this->y -= rhs;
            this->z -= rhs;
            return *this;
        }

        UInt3 & UInt3::operator/=(const UInt3 & rhs) noexcept {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator/=(unsigned int rhs) noexcept {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            return *this;
        }

        UInt3 & UInt3::operator*=(const UInt3 & rhs) noexcept {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator*=(unsigned int rhs) noexcept {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            return *this;
        }

        UInt3 & UInt3::operator%=(const UInt3 & rhs) noexcept {
            this->x %= rhs.x;
            this->y %= rhs.y;
            this->z %= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator%=(unsigned int rhs) noexcept {
            this->x %= rhs;
            this->y %= rhs;
            this->z %= rhs;
            return *this;
        }

        UInt3 & UInt3::operator|=(const UInt3 & rhs) noexcept {
            this->x |= rhs.x;
            this->y |= rhs.y;
            this->z |= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator|=(unsigned int rhs) noexcept {
            this->x |= rhs;
            this->y |= rhs;
            this->z |= rhs;
            return *this;
        }

        UInt3 & UInt3::operator&=(const UInt3 & rhs) noexcept {
            this->x &= rhs.x;
            this->y &= rhs.y;
            this->z &= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator&=(unsigned int rhs) noexcept {
            this->x &= rhs;
            this->y &= rhs;
            this->z &= rhs;
            return *this;
        }

        UInt3 & UInt3::operator^=(const UInt3 & rhs) noexcept {
            this->x ^= rhs.x;
            this->y ^= rhs.y;
            this->z ^= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator^=(unsigned int rhs) noexcept {
            this->x ^= rhs;
            this->y ^= rhs;
            this->z ^= rhs;
            return *this;
        }

        UInt3 & UInt3::operator<<=(const UInt3 & rhs) noexcept {
            this->x <<= rhs.x;
            this->y <<= rhs.y;
            this->z <<= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator<<=(unsigned int rhs) noexcept {
            this->x <<= rhs;
            this->y <<= rhs;
            this->z <<= rhs;
            return *this;
        }

        UInt3 & UInt3::operator>>=(const UInt3 & rhs) noexcept {
            this->x >>= rhs.x;
            this->y >>= rhs.y;
            this->z >>= rhs.z;
            return *this;
        }

        UInt3 & UInt3::operator>>=(unsigned int rhs) noexcept {
            this->x >>= rhs;
            this->y >>= rhs;
            this->z >>= rhs;
            return *this;
        }

        UInt3 UInt3::operator*(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x * rhs.x, this->y * rhs.y, this->z * rhs.z };
        }

        UInt3 UInt3::operator/(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x / rhs.x, this->y / rhs.y, this->z / rhs.z };
        }

        UInt3 UInt3::operator+(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x + rhs.x, this->y + rhs.y, this->z + rhs.z };
        }

        UInt3 UInt3::operator-(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z };
        }

        UInt3 UInt3::operator%(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x % rhs.x, this->y % rhs.y, this->z % rhs.z };
        }

        UInt3 UInt3::operator|(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x | rhs.x, this->y | rhs.y, this->z | rhs.z };
        }

        UInt3 UInt3::operator&(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x & rhs.x, this->y & rhs.y, this->z & rhs.z };
        }

        UInt3 UInt3::operator^(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x ^ rhs.x, this->y ^ rhs.y, this->z ^ rhs.z };
        }

        UInt3 UInt3::operator<<(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x << rhs.x, this->y << rhs.y, this->z << rhs.z };
        }

        UInt3 UInt3::operator>>(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x >> rhs.x, this->y >> rhs.y, this->z >> rhs.z };
        }

        UInt3 UInt3::operator||(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x || rhs.x, this->y || rhs.y, this->z || rhs.z };
        }

        UInt3 UInt3::operator&&(const UInt3 & rhs) const noexcept {
            return UInt3 { this->x && rhs.x, this->y && rhs.y, this->z && rhs.z };
        }

        Bool3 UInt3::operator<(const UInt3 & rhs) const noexcept {
            return Bool3 { x < rhs.x, y < rhs.y, z < rhs.z };
        }

        Bool3 UInt3::operator>(const UInt3 & rhs) const noexcept {
            return Bool3 { x > rhs.x, y > rhs.y, z > rhs.z };
        }

        Bool3 UInt3::operator!=(const UInt3 & rhs) const noexcept {
            return Bool3 { x != rhs.x, y != rhs.y, z != rhs.z };
        }

        Bool3 UInt3::operator==(const UInt3 & rhs) const noexcept {
            return Bool3 { x == rhs.x, y == rhs.y, z == rhs.z };
        }

        Bool3 UInt3::operator>=(const UInt3 & rhs) const noexcept {
            return Bool3 { x >= rhs.x, y >= rhs.y, z >= rhs.z };
        }

        Bool3 UInt3::operator<=(const UInt3 & rhs) const noexcept {
            return Bool3 { x <= rhs.x, y <= rhs.y, z <= rhs.z };
        }

        UInt3 UInt3::operator~() const noexcept {
            return UInt3 { ~x, ~y, ~z };
        }

        UInt3 UInt3::operator!() const noexcept {
            return UInt3 { !x, !y, !z };
        }

        UInt3 UInt3::operator++() noexcept {
            return UInt3 { ++x, ++y, ++z };
        }

        UInt3 UInt3::operator++(int) noexcept {
            return UInt3 { x++, y++, z++ };
        }

        UInt3 UInt3::operator--() noexcept {
            return UInt3 { --x, --y, --z };
        }

        UInt3 UInt3::operator--(int) noexcept {
            return UInt3 { x--, y--, z-- };
        }

        UInt3 UInt3::Random(unsigned int lower, unsigned int upper) noexcept {
            unsigned int range = upper - lower + 1;
             return UInt3 {  rand() % range + lower,
             rand() % range + lower,
             rand() % range + lower };
        }

        const UInt3 UInt3::One { 1, 1, 1 };
        const UInt3 UInt3::Zero { 0, 0, 0 };
        const UInt3 UInt3::UnitX { 1, 0, 0 };
        const UInt3 UInt3::UnitY { 0, 1, 0 };
        const UInt3 UInt3::UnitZ { 0, 0, 1 };
    }
}

