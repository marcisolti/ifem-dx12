#pragma once
namespace Egg {
    namespace Math {

        template<typename I, typename B, int nBase, int s0 = 0, int s1 = 0, int s2 = 0>
        class Int3Swizzle {
            int v[nBase];
        public:
            operator I () const noexcept {
                return I {
                    (s0 >= 0) ? v[s0] : ((s0 == -1) ? 0.0f : 1.0f),
                    (s1 >= 0) ? v[s1] : ((s1 == -1) ? 0.0f : 1.0f),
                    (s2 >= 0) ? v[s2] : ((s2 == -1) ? 0.0f : 1.0f)
                };
            }
        Int3Swizzle & operator=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs.x;
            if(s1 >= 0) v[s1] = rhs.y;
            if(s2 >= 0) v[s2] = rhs.z;
            return *this;
        }

        Int3Swizzle & operator=(int rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs;
            if(s1 >= 0) v[s1] = rhs;
            if(s2 >= 0) v[s2] = rhs;
            return *this;
        }

        Int3Swizzle & operator+=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] += rhs.x;
            if(s1 >= 0) v[s1] += rhs.y;
            if(s2 >= 0) v[s2] += rhs.z;
            return *this;
        }

        Int3Swizzle & operator+=(int rhs) noexcept {
            if(s0 >= 0) v[s0] += rhs;
            if(s1 >= 0) v[s1] += rhs;
            if(s2 >= 0) v[s2] += rhs;
            return *this;
        }

        Int3Swizzle & operator-=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] -= rhs.x;
            if(s1 >= 0) v[s1] -= rhs.y;
            if(s2 >= 0) v[s2] -= rhs.z;
            return *this;
        }

        Int3Swizzle & operator-=(int rhs) noexcept {
            if(s0 >= 0) v[s0] -= rhs;
            if(s1 >= 0) v[s1] -= rhs;
            if(s2 >= 0) v[s2] -= rhs;
            return *this;
        }

        Int3Swizzle & operator/=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] /= rhs.x;
            if(s1 >= 0) v[s1] /= rhs.y;
            if(s2 >= 0) v[s2] /= rhs.z;
            return *this;
        }

        Int3Swizzle & operator/=(int rhs) noexcept {
            if(s0 >= 0) v[s0] /= rhs;
            if(s1 >= 0) v[s1] /= rhs;
            if(s2 >= 0) v[s2] /= rhs;
            return *this;
        }

        Int3Swizzle & operator*=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] *= rhs.x;
            if(s1 >= 0) v[s1] *= rhs.y;
            if(s2 >= 0) v[s2] *= rhs.z;
            return *this;
        }

        Int3Swizzle & operator*=(int rhs) noexcept {
            if(s0 >= 0) v[s0] *= rhs;
            if(s1 >= 0) v[s1] *= rhs;
            if(s2 >= 0) v[s2] *= rhs;
            return *this;
        }

        Int3Swizzle & operator|=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] |= rhs.x;
            if(s1 >= 0) v[s1] |= rhs.y;
            if(s2 >= 0) v[s2] |= rhs.z;
            return *this;
        }

        Int3Swizzle & operator|=(int rhs) noexcept {
            if(s0 >= 0) v[s0] |= rhs;
            if(s1 >= 0) v[s1] |= rhs;
            if(s2 >= 0) v[s2] |= rhs;
            return *this;
        }

        Int3Swizzle & operator&=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] &= rhs.x;
            if(s1 >= 0) v[s1] &= rhs.y;
            if(s2 >= 0) v[s2] &= rhs.z;
            return *this;
        }

        Int3Swizzle & operator&=(int rhs) noexcept {
            if(s0 >= 0) v[s0] &= rhs;
            if(s1 >= 0) v[s1] &= rhs;
            if(s2 >= 0) v[s2] &= rhs;
            return *this;
        }

        Int3Swizzle & operator^=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] ^= rhs.x;
            if(s1 >= 0) v[s1] ^= rhs.y;
            if(s2 >= 0) v[s2] ^= rhs.z;
            return *this;
        }

        Int3Swizzle & operator^=(int rhs) noexcept {
            if(s0 >= 0) v[s0] ^= rhs;
            if(s1 >= 0) v[s1] ^= rhs;
            if(s2 >= 0) v[s2] ^= rhs;
            return *this;
        }

        Int3Swizzle & operator<<=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] <<= rhs.x;
            if(s1 >= 0) v[s1] <<= rhs.y;
            if(s2 >= 0) v[s2] <<= rhs.z;
            return *this;
        }

        Int3Swizzle & operator<<=(int rhs) noexcept {
            if(s0 >= 0) v[s0] <<= rhs;
            if(s1 >= 0) v[s1] <<= rhs;
            if(s2 >= 0) v[s2] <<= rhs;
            return *this;
        }

        Int3Swizzle & operator>>=(const I & rhs) noexcept {
            if(s0 >= 0) v[s0] >>= rhs.x;
            if(s1 >= 0) v[s1] >>= rhs.y;
            if(s2 >= 0) v[s2] >>= rhs.z;
            return *this;
        }

        Int3Swizzle & operator>>=(int rhs) noexcept {
            if(s0 >= 0) v[s0] >>= rhs;
            if(s1 >= 0) v[s1] >>= rhs;
            if(s2 >= 0) v[s2] >>= rhs;
            return *this;
        }

        I operator*(const I & rhs) const noexcept {
            I t = *this;
            return t * rhs;
        }

        I operator/(const I & rhs) const noexcept {
            I t = *this;
            return t / rhs;
        }

        I operator+(const I & rhs) const noexcept {
            I t = *this;
            return t + rhs;
        }

        I operator-(const I & rhs) const noexcept {
            I t = *this;
            return t - rhs;
        }

        I operator%(const I & rhs) const noexcept {
            I t = *this;
            return t % rhs;
        }

        I operator|(const I & rhs) const noexcept {
            I t = *this;
            return t | rhs;
        }

        I operator&(const I & rhs) const noexcept {
            I t = *this;
            return t & rhs;
        }

        I operator^(const I & rhs) const noexcept {
            I t = *this;
            return t ^ rhs;
        }

        I operator<<(const I & rhs) const noexcept {
            I t = *this;
            return t << rhs;
        }

        I operator>>(const I & rhs) const noexcept {
            I t = *this;
            return t >> rhs;
        }

        I operator||(const I & rhs) const noexcept {
            I t = *this;
            return t || rhs;
        }

        I operator&&(const I & rhs) const noexcept {
            I t = *this;
            return t && rhs;
        }

        B operator<(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x < rhs.x, t.y < rhs.y, t.z < rhs.z };
        }

        B operator>(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x > rhs.x, t.y > rhs.y, t.z > rhs.z };
        }

        B operator!=(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x != rhs.x, t.y != rhs.y, t.z != rhs.z };
        }

        B operator==(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x == rhs.x, t.y == rhs.y, t.z == rhs.z };
        }

        B operator>=(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x >= rhs.x, t.y >= rhs.y, t.z >= rhs.z };
        }

        B operator<=(const I & rhs) const noexcept {
            I t = *this;
            return B { t.x <= rhs.x, t.y <= rhs.y, t.z <= rhs.z };
        }

        I operator~() const noexcept {
            I t = *this;
            return I { ~t.x, ~t.y, ~t.z };
        }

        I operator!() const noexcept {
            I t = *this;
            return I { !t.x, !t.y, !t.z };
        }

        I operator++() noexcept {
            I t = *this;
            return I { ++t.x, ++t.y, ++t.z };
        }

        I operator++(int) noexcept {
            I t = *this;
            return I { t.x++, t.y++, t.z++ };
        }

        I operator--() noexcept {
            I t = *this;
            return I { --t.x, --t.y, --t.z };
        }

        I operator--(int) noexcept {
            I t = *this;
            return I { t.x--, t.y--, t.z-- };
        }


        I operator-() const noexcept {
            I t = *this;
            return I { -t.x, -t.y, -t.z };
        }

        };
    }
}

