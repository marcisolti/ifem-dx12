#pragma once

#include <cmath>

namespace Egg {
    namespace Math {

        template<typename F, typename I, typename B, int nBase, int s0 = 0, int s1 = 0>
        class Float2Swizzle {
            float v[nBase];
        public:
            operator F () const noexcept {
                return F {
                    (s0 >= 0) ? v[s0] : ((s0 == -1) ? 0.0f : 1.0f),
                    (s1 >= 0) ? v[s1] : ((s1 == -1) ? 0.0f : 1.0f)
                };
            }
        Float2Swizzle & operator=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs.x;
            if(s1 >= 0) v[s1] = rhs.y;
            return *this;
        }

        Float2Swizzle & operator=(float rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs;
            if(s1 >= 0) v[s1] = rhs;
            return *this;
        }

        Float2Swizzle & operator+=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] += rhs.x;
            if(s1 >= 0) v[s1] += rhs.y;
            return *this;
        }

        Float2Swizzle & operator+=(float rhs) noexcept {
            if(s0 >= 0) v[s0] += rhs;
            if(s1 >= 0) v[s1] += rhs;
            return *this;
        }

        Float2Swizzle & operator-=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] -= rhs.x;
            if(s1 >= 0) v[s1] -= rhs.y;
            return *this;
        }

        Float2Swizzle & operator-=(float rhs) noexcept {
            if(s0 >= 0) v[s0] -= rhs;
            if(s1 >= 0) v[s1] -= rhs;
            return *this;
        }

        Float2Swizzle & operator/=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] /= rhs.x;
            if(s1 >= 0) v[s1] /= rhs.y;
            return *this;
        }

        Float2Swizzle & operator/=(float rhs) noexcept {
            if(s0 >= 0) v[s0] /= rhs;
            if(s1 >= 0) v[s1] /= rhs;
            return *this;
        }

        Float2Swizzle & operator*=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] *= rhs.x;
            if(s1 >= 0) v[s1] *= rhs.y;
            return *this;
        }

        Float2Swizzle & operator*=(float rhs) noexcept {
            if(s0 >= 0) v[s0] *= rhs;
            if(s1 >= 0) v[s1] *= rhs;
            return *this;
        }

        F operator*(const F & rhs) const noexcept {
            F t = *this;
            return t * rhs;
        }

        F operator/(const F & rhs) const noexcept {
            F t = *this;
            return t / rhs;
        }

        F operator+(const F & rhs) const noexcept {
            F t = *this;
            return t + rhs;
        }

        F operator-(const F & rhs) const noexcept {
            F t = *this;
            return t - rhs;
        }

        F Abs() const noexcept {
            F t = *this;
            return t.Abs();
        }

        F Acos() const noexcept {
            F t = *this;
            return t.Acos();
        }

        F Asin() const noexcept {
            F t = *this;
            return t.Asin();
        }

        F Atan() const noexcept {
            F t = *this;
            return t.Atan();
        }

        F Cos() const noexcept {
            F t = *this;
            return t.Cos();
        }

        F Sin() const noexcept {
            F t = *this;
            return t.Sin();
        }

        F Cosh() const noexcept {
            F t = *this;
            return t.Cosh();
        }

        F Sinh() const noexcept {
            F t = *this;
            return t.Sinh();
        }

        F Tan() const noexcept {
            F t = *this;
            return t.Tan();
        }

        F Exp() const noexcept {
            F t = *this;
            return t.Exp();
        }

        F Log() const noexcept {
            F t = *this;
            return t.Log();
        }

        F Log10() const noexcept {
            F t = *this;
            return t.Log10();
        }

        F Fmod(const F & rhs) const noexcept {
            F t = *this;
            return t.Fmod(rhs);
        }

        F Atan2(const F & rhs) const noexcept {
            F t = *this;
            return t.Atan2(rhs);
        }

        F Pow(const F & rhs) const noexcept {
            F t = *this;
            return t.Pow(rhs);
        }

        F Sqrt() const noexcept {
            F t = *this;
            return t.Sqrt();
        }

        F Clamp(const F & low, const F & high) const noexcept {
            F t = *this;
            return F { (t.x < low.x) ? low.x: ((t.x > high.x) ? high.x :t.x), (t.y < low.y) ? low.y: ((t.y > high.y) ? high.y :t.y) };
        }

        float Dot(const F & rhs) const noexcept {
            F t = *this;
            return t.x * rhs.x + t.y * rhs.y;
        }

        F Sign() const noexcept {
            F t = *this;
            return F { (t.x > 0.0f) ? 1.0f : ((t.x < 0.0f) ? -1.0f : 0.0f), (t.y > 0.0f) ? 1.0f : ((t.y < 0.0f) ? -1.0f : 0.0f) };
        }

        I Round() const noexcept {
            F t = *this;
            return I { (int)(t.x + 0.5f), (int)(t.y + 0.5f) }; 
        }

        F Saturate() const noexcept {
            F t = *this;
            return t.Clamp(F { 0, 0 }, F { 1, 1 });
        }

        float LengthSquared() const noexcept {
            F t = *this;
            return t.Dot(*this);
        }

        float Length() const noexcept {
            F t = *this;
            return ::sqrtf(t.LengthSquared());
        }

        F Normalize() const noexcept {
            F t = *this;
            float len = t.Length();
             return F { t.x / len , t.y / len  };
        }

        B IsNan() const noexcept {
            F t = *this;
            return B { std::isnan(t.x), std::isnan(t.y) };
        }

        B IsFinite() const noexcept {
            F t = *this;
            return B { std::isfinite(t.x), std::isfinite(t.y) };
        }

        B IsInfinite() const noexcept {
            F t = *this;
            return B { !std::isfinite(t.x), !std::isfinite(t.y) };
        }

        F operator-() const noexcept {
            F t = *this;
            return F { -t.x, -t.y };
        }

        F operator%(const F & rhs) const noexcept {
            F t = *this;
            return F { ::fmodf(t.x, rhs.x), ::fmodf(t.y, rhs.y) };
        }

        I Ceil() const noexcept {
            F t = *this;
            return I { (int)::ceil(t.x), (int)::ceil(t.y) };
        }

        I Floor() const noexcept {
            F t = *this;
            return I { (int)::floor(t.x), (int)::floor(t.y) };
        }

        F Exp2() const noexcept {
            F t = *this;
            return F { ::pow(2.0f,t.x), ::pow(2.0f,t.y) };
        }

        I Trunc() const noexcept {
            F t = *this;
            return I { (int)t.x, (int)t.y };
        }

        float Distance(const F & rhs) const noexcept {
            F t = *this;
            return (( F )(*this) - rhs).Length();
        }

        B operator<(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x < rhs.x, t.y < rhs.y };
        }

        B operator>(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x > rhs.x, t.y > rhs.y };
        }

        B operator!=(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x != rhs.x, t.y != rhs.y };
        }

        B operator==(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x == rhs.x, t.y == rhs.y };
        }

        B operator>=(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x >= rhs.x, t.y >= rhs.y };
        }

        B operator<=(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x <= rhs.x, t.y <= rhs.y };
        }


        F operator+(float v) const noexcept {
            F t = *this;
            return F { t.x + v , t.y + v  };
        }

        F operator-(float v) const noexcept {
            F t = *this;
            return F { t.x - v , t.y - v  };
        }

        F operator*(float v) const noexcept {
            F t = *this;
            return F { t.x * v , t.y * v  };
        }

        F operator/(float v) const noexcept {
            F t = *this;
            return F { t.x / v , t.y / v  };
        }

        F operator%(float v) const noexcept {
            F t = *this;
            return F { ::fmodf(t.x, v), ::fmodf(t.y, v) };
        }

        float Arg() const noexcept {
            F t = *this;
            return ::atan2(t.y, t.x);
        }

        F Polar() const noexcept {
            F t = *this;
            return F { t.Length(), t.Arg() };
        }

        F ComplexMul(const F & rhs) const noexcept {
            F t = *this;
            return F { t.x * rhs.x - t.y * rhs.y, t.x * rhs.y + t.y * rhs.x };
        }

        F Cartesian() const noexcept {
            F t = *this;
            return F { ::cosf(t.y), ::sinf(t.y) } * t.x;
        }

        };
    }
}

