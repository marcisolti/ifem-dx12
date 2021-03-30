#include "UInt1.h"
#include <cmath>

namespace Egg {
    namespace Math {

        UInt1::UInt1(unsigned int x) : x { x }{ }

        UInt1::UInt1() : x{ 0U }{ }

        UInt1 & UInt1::operator=(const UInt1 & rhs) noexcept {
            this->x = rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator=(unsigned int rhs) noexcept {
            this->x = rhs;
            return *this;
        }

        UInt1 & UInt1::operator+=(const UInt1 & rhs) noexcept {
            this->x += rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator+=(unsigned int rhs) noexcept {
            this->x += rhs;
            return *this;
        }

        UInt1 & UInt1::operator-=(const UInt1 & rhs) noexcept {
            this->x -= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator-=(unsigned int rhs) noexcept {
            this->x -= rhs;
            return *this;
        }

        UInt1 & UInt1::operator/=(const UInt1 & rhs) noexcept {
            this->x /= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator/=(unsigned int rhs) noexcept {
            this->x /= rhs;
            return *this;
        }

        UInt1 & UInt1::operator*=(const UInt1 & rhs) noexcept {
            this->x *= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator*=(unsigned int rhs) noexcept {
            this->x *= rhs;
            return *this;
        }

        UInt1 & UInt1::operator%=(const UInt1 & rhs) noexcept {
            this->x %= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator%=(unsigned int rhs) noexcept {
            this->x %= rhs;
            return *this;
        }

        UInt1 & UInt1::operator|=(const UInt1 & rhs) noexcept {
            this->x |= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator|=(unsigned int rhs) noexcept {
            this->x |= rhs;
            return *this;
        }

        UInt1 & UInt1::operator&=(const UInt1 & rhs) noexcept {
            this->x &= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator&=(unsigned int rhs) noexcept {
            this->x &= rhs;
            return *this;
        }

        UInt1 & UInt1::operator^=(const UInt1 & rhs) noexcept {
            this->x ^= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator^=(unsigned int rhs) noexcept {
            this->x ^= rhs;
            return *this;
        }

        UInt1 & UInt1::operator<<=(const UInt1 & rhs) noexcept {
            this->x <<= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator<<=(unsigned int rhs) noexcept {
            this->x <<= rhs;
            return *this;
        }

        UInt1 & UInt1::operator>>=(const UInt1 & rhs) noexcept {
            this->x >>= rhs.x;
            return *this;
        }

        UInt1 & UInt1::operator>>=(unsigned int rhs) noexcept {
            this->x >>= rhs;
            return *this;
        }

        UInt1 UInt1::operator*(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x * rhs.x };
        }

        UInt1 UInt1::operator/(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x / rhs.x };
        }

        UInt1 UInt1::operator+(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x + rhs.x };
        }

        UInt1 UInt1::operator-(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x - rhs.x };
        }

        UInt1 UInt1::operator%(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x % rhs.x };
        }

        UInt1 UInt1::operator|(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x | rhs.x };
        }

        UInt1 UInt1::operator&(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x & rhs.x };
        }

        UInt1 UInt1::operator^(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x ^ rhs.x };
        }

        UInt1 UInt1::operator<<(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x << rhs.x };
        }

        UInt1 UInt1::operator>>(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x >> rhs.x };
        }

        UInt1 UInt1::operator||(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x || rhs.x };
        }

        UInt1 UInt1::operator&&(const UInt1 & rhs) const noexcept {
            return UInt1 { this->x && rhs.x };
        }

        Bool1 UInt1::operator<(const UInt1 & rhs) const noexcept {
            return Bool1 { x < rhs.x };
        }

        Bool1 UInt1::operator>(const UInt1 & rhs) const noexcept {
            return Bool1 { x > rhs.x };
        }

        Bool1 UInt1::operator!=(const UInt1 & rhs) const noexcept {
            return Bool1 { x != rhs.x };
        }

        Bool1 UInt1::operator==(const UInt1 & rhs) const noexcept {
            return Bool1 { x == rhs.x };
        }

        Bool1 UInt1::operator>=(const UInt1 & rhs) const noexcept {
            return Bool1 { x >= rhs.x };
        }

        Bool1 UInt1::operator<=(const UInt1 & rhs) const noexcept {
            return Bool1 { x <= rhs.x };
        }

        UInt1 UInt1::operator~() const noexcept {
            return UInt1 { ~x };
        }

        UInt1 UInt1::operator!() const noexcept {
            return UInt1 { !x };
        }

        UInt1 UInt1::operator++() noexcept {
            return UInt1 { ++x };
        }

        UInt1 UInt1::operator++(int) noexcept {
            return UInt1 { x++ };
        }

        UInt1 UInt1::operator--() noexcept {
            return UInt1 { --x };
        }

        UInt1 UInt1::operator--(int) noexcept {
            return UInt1 { x-- };
        }

        UInt1 UInt1::Random(unsigned int lower, unsigned int upper) noexcept {
            unsigned int range = upper - lower + 1;
             return UInt1 {  rand() % range + lower };
        }

    }
}

