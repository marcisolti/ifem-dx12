#pragma once
namespace Egg {
    namespace Math {

        template<typename F, typename I, typename B, int nBase, int s0 = 0, int s1 = 0, int s2 = 0, int s3 = 0>
        class Float4Swizzle {
            float v[nBase];
        public:
            operator F () const noexcept {
                return F {
                    (s0 >= 0) ? v[s0] : ((s0 == -1) ? 0.0f : 1.0f),
                    (s1 >= 0) ? v[s1] : ((s1 == -1) ? 0.0f : 1.0f),
                    (s2 >= 0) ? v[s2] : ((s2 == -1) ? 0.0f : 1.0f),
                    (s3 >= 0) ? v[s3] : ((s3 == -1) ? 0.0f : 1.0f)
                };
            }
        Float4Swizzle & operator=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs.x;
            if(s1 >= 0) v[s1] = rhs.y;
            if(s2 >= 0) v[s2] = rhs.z;
            if(s3 >= 0) v[s3] = rhs.w;
            return *this;
        }

        Float4Swizzle & operator=(float rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs;
            if(s1 >= 0) v[s1] = rhs;
            if(s2 >= 0) v[s2] = rhs;
            if(s3 >= 0) v[s3] = rhs;
            return *this;
        }

        Float4Swizzle & operator+=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] += rhs.x;
            if(s1 >= 0) v[s1] += rhs.y;
            if(s2 >= 0) v[s2] += rhs.z;
            if(s3 >= 0) v[s3] += rhs.w;
            return *this;
        }

        Float4Swizzle & operator+=(float rhs) noexcept {
            if(s0 >= 0) v[s0] += rhs;
            if(s1 >= 0) v[s1] += rhs;
            if(s2 >= 0) v[s2] += rhs;
            if(s3 >= 0) v[s3] += rhs;
            return *this;
        }

        Float4Swizzle & operator-=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] -= rhs.x;
            if(s1 >= 0) v[s1] -= rhs.y;
            if(s2 >= 0) v[s2] -= rhs.z;
            if(s3 >= 0) v[s3] -= rhs.w;
            return *this;
        }

        Float4Swizzle & operator-=(float rhs) noexcept {
            if(s0 >= 0) v[s0] -= rhs;
            if(s1 >= 0) v[s1] -= rhs;
            if(s2 >= 0) v[s2] -= rhs;
            if(s3 >= 0) v[s3] -= rhs;
            return *this;
        }

        Float4Swizzle & operator/=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] /= rhs.x;
            if(s1 >= 0) v[s1] /= rhs.y;
            if(s2 >= 0) v[s2] /= rhs.z;
            if(s3 >= 0) v[s3] /= rhs.w;
            return *this;
        }

        Float4Swizzle & operator/=(float rhs) noexcept {
            if(s0 >= 0) v[s0] /= rhs;
            if(s1 >= 0) v[s1] /= rhs;
            if(s2 >= 0) v[s2] /= rhs;
            if(s3 >= 0) v[s3] /= rhs;
            return *this;
        }

        Float4Swizzle & operator*=(const F & rhs) noexcept {
            if(s0 >= 0) v[s0] *= rhs.x;
            if(s1 >= 0) v[s1] *= rhs.y;
            if(s2 >= 0) v[s2] *= rhs.z;
            if(s3 >= 0) v[s3] *= rhs.w;
            return *this;
        }

        Float4Swizzle & operator*=(float rhs) noexcept {
            if(s0 >= 0) v[s0] *= rhs;
            if(s1 >= 0) v[s1] *= rhs;
            if(s2 >= 0) v[s2] *= rhs;
            if(s3 >= 0) v[s3] *= rhs;
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
            return F { (t.x < low.x) ? low.x: ((t.x > high.x) ? high.x :t.x), (t.y < low.y) ? low.y: ((t.y > high.y) ? high.y :t.y), (t.z < low.z) ? low.z: ((t.z > high.z) ? high.z :t.z), (t.w < low.w) ? low.w: ((t.w > high.w) ? high.w :t.w) };
        }

        float Dot(const F & rhs) const noexcept {
            F t = *this;
            return t.x * rhs.x + t.y * rhs.y + t.z * rhs.z + t.w * rhs.w;
        }

        F Sign() const noexcept {
            F t = *this;
            return F { (t.x > 0.0f) ? 1.0f : ((t.x < 0.0f) ? -1.0f : 0.0f), (t.y > 0.0f) ? 1.0f : ((t.y < 0.0f) ? -1.0f : 0.0f), (t.z > 0.0f) ? 1.0f : ((t.z < 0.0f) ? -1.0f : 0.0f), (t.w > 0.0f) ? 1.0f : ((t.w < 0.0f) ? -1.0f : 0.0f) };
        }

        I Round() const noexcept {
            F t = *this;
            return I { (int)(t.x + 0.5f), (int)(t.y + 0.5f), (int)(t.z + 0.5f), (int)(t.w + 0.5f) }; 
        }

        F Saturate() const noexcept {
            F t = *this;
            return t.Clamp(F { 0, 0, 0, 0 }, F { 1, 1, 1, 1 });
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
             return F { t.x / len , t.y / len , t.z / len , t.w / len  };
        }

        B IsNan() const noexcept {
            F t = *this;
            return B { std::isnan(t.x), std::isnan(t.y), std::isnan(t.z), std::isnan(t.w) };
        }

        B IsFinite() const noexcept {
            F t = *this;
            return B { std::isfinite(t.x), std::isfinite(t.y), std::isfinite(t.z), std::isfinite(t.w) };
        }

        B IsInfinite() const noexcept {
            F t = *this;
            return B { !std::isfinite(t.x), !std::isfinite(t.y), !std::isfinite(t.z), !std::isfinite(t.w) };
        }

        F operator-() const noexcept {
            F t = *this;
            return F { -t.x, -t.y, -t.z, -t.w };
        }

        F operator%(const F & rhs) const noexcept {
            F t = *this;
            return F { ::fmodf(t.x, rhs.x), ::fmodf(t.y, rhs.y), ::fmodf(t.z, rhs.z), ::fmodf(t.w, rhs.w) };
        }

        I Ceil() const noexcept {
            F t = *this;
            return I { (int)::ceil(t.x), (int)::ceil(t.y), (int)::ceil(t.z), (int)::ceil(t.w) };
        }

        I Floor() const noexcept {
            F t = *this;
            return I { (int)::floor(t.x), (int)::floor(t.y), (int)::floor(t.z), (int)::floor(t.w) };
        }

        F Exp2() const noexcept {
            F t = *this;
            return F { ::pow(2.0f,t.x), ::pow(2.0f,t.y), ::pow(2.0f,t.z), ::pow(2.0f,t.w) };
        }

        I Trunc() const noexcept {
            F t = *this;
            return I { (int)t.x, (int)t.y, (int)t.z, (int)t.w };
        }

        float Distance(const F & rhs) const noexcept {
            F t = *this;
            return (( F )(*this) - rhs).Length();
        }

        B operator<(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x < rhs.x, t.y < rhs.y, t.z < rhs.z, t.w < rhs.w };
        }

        B operator>(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x > rhs.x, t.y > rhs.y, t.z > rhs.z, t.w > rhs.w };
        }

        B operator!=(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x != rhs.x, t.y != rhs.y, t.z != rhs.z, t.w != rhs.w };
        }

        B operator==(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x == rhs.x, t.y == rhs.y, t.z == rhs.z, t.w == rhs.w };
        }

        B operator>=(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x >= rhs.x, t.y >= rhs.y, t.z >= rhs.z, t.w >= rhs.w };
        }

        B operator<=(const F & rhs) const noexcept {
            F t = *this;
            return B { t.x <= rhs.x, t.y <= rhs.y, t.z <= rhs.z, t.w <= rhs.w };
        }


        F operator+(float v) const noexcept {
            F t = *this;
            return F { t.x + v , t.y + v , t.z + v , t.w + v  };
        }

        F operator-(float v) const noexcept {
            F t = *this;
            return F { t.x - v , t.y - v , t.z - v , t.w - v  };
        }

        F operator*(float v) const noexcept {
            F t = *this;
            return F { t.x * v , t.y * v , t.z * v , t.w * v  };
        }

        F operator/(float v) const noexcept {
            F t = *this;
            return F { t.x / v , t.y / v , t.z / v , t.w / v  };
        }

        F operator%(float v) const noexcept {
            F t = *this;
            return F { ::fmodf(t.x, v), ::fmodf(t.y, v), ::fmodf(t.z, v), ::fmodf(t.w, v) };
        }

        F operator!() const noexcept {
            F t = *this;
            return F { -t.x, -t.y, -t.z, t.w }; 
        }

        };
    }
}

