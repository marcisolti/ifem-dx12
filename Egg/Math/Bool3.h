#pragma once

#include "Bool2.h"
#include "Bool4.h"

namespace Egg {
    namespace Math {

        class Bool2;
        class Bool4;

        class Bool3 {
        public:
            union {
                struct {
                    bool x;
                    bool y;
                    bool z;
                };

                Bool2Swizzle<Bool2, 3, 0, 0> xx;
                Bool2Swizzle<Bool2, 3, 0, 1> xy;
                Bool2Swizzle<Bool2, 3, 0, 2> xz;
                Bool2Swizzle<Bool2, 3, 1, 0> yx;
                Bool2Swizzle<Bool2, 3, 1, 1> yy;
                Bool2Swizzle<Bool2, 3, 1, 2> yz;
                Bool2Swizzle<Bool2, 3, 2, 0> zx;
                Bool2Swizzle<Bool2, 3, 2, 1> zy;
                Bool2Swizzle<Bool2, 3, 2, 2> zz;

                Bool3Swizzle<Bool3, 3, 0, 0, 0> xxx;
                Bool3Swizzle<Bool3, 3, 0, 0, 1> xxy;
                Bool3Swizzle<Bool3, 3, 0, 0, 2> xxz;
                Bool3Swizzle<Bool3, 3, 0, 1, 0> xyx;
                Bool3Swizzle<Bool3, 3, 0, 1, 1> xyy;
                Bool3Swizzle<Bool3, 3, 0, 1, 2> xyz;
                Bool3Swizzle<Bool3, 3, 0, 2, 0> xzx;
                Bool3Swizzle<Bool3, 3, 0, 2, 1> xzy;
                Bool3Swizzle<Bool3, 3, 0, 2, 2> xzz;
                Bool3Swizzle<Bool3, 3, 1, 0, 0> yxx;
                Bool3Swizzle<Bool3, 3, 1, 0, 1> yxy;
                Bool3Swizzle<Bool3, 3, 1, 0, 2> yxz;
                Bool3Swizzle<Bool3, 3, 1, 1, 0> yyx;
                Bool3Swizzle<Bool3, 3, 1, 1, 1> yyy;
                Bool3Swizzle<Bool3, 3, 1, 1, 2> yyz;
                Bool3Swizzle<Bool3, 3, 1, 2, 0> yzx;
                Bool3Swizzle<Bool3, 3, 1, 2, 1> yzy;
                Bool3Swizzle<Bool3, 3, 1, 2, 2> yzz;
                Bool3Swizzle<Bool3, 3, 2, 0, 0> zxx;
                Bool3Swizzle<Bool3, 3, 2, 0, 1> zxy;
                Bool3Swizzle<Bool3, 3, 2, 0, 2> zxz;
                Bool3Swizzle<Bool3, 3, 2, 1, 0> zyx;
                Bool3Swizzle<Bool3, 3, 2, 1, 1> zyy;
                Bool3Swizzle<Bool3, 3, 2, 1, 2> zyz;
                Bool3Swizzle<Bool3, 3, 2, 2, 0> zzx;
                Bool3Swizzle<Bool3, 3, 2, 2, 1> zzy;
                Bool3Swizzle<Bool3, 3, 2, 2, 2> zzz;

                Bool4Swizzle<Bool4, 3, 0, 0, 0, 0> xxxx;
                Bool4Swizzle<Bool4, 3, 0, 0, 1, 0> xxxy;
                Bool4Swizzle<Bool4, 3, 0, 0, 2, 0> xxxz;
                Bool4Swizzle<Bool4, 3, 0, 0, 0, 1> xxyx;
                Bool4Swizzle<Bool4, 3, 0, 0, 1, 1> xxyy;
                Bool4Swizzle<Bool4, 3, 0, 0, 2, 1> xxyz;
                Bool4Swizzle<Bool4, 3, 0, 0, 0, 2> xxzx;
                Bool4Swizzle<Bool4, 3, 0, 0, 1, 2> xxzy;
                Bool4Swizzle<Bool4, 3, 0, 0, 2, 2> xxzz;
                Bool4Swizzle<Bool4, 3, 0, 1, 0, 0> xyxx;
                Bool4Swizzle<Bool4, 3, 0, 1, 1, 0> xyxy;
                Bool4Swizzle<Bool4, 3, 0, 1, 2, 0> xyxz;
                Bool4Swizzle<Bool4, 3, 0, 1, 0, 1> xyyx;
                Bool4Swizzle<Bool4, 3, 0, 1, 1, 1> xyyy;
                Bool4Swizzle<Bool4, 3, 0, 1, 2, 1> xyyz;
                Bool4Swizzle<Bool4, 3, 0, 1, 0, 2> xyzx;
                Bool4Swizzle<Bool4, 3, 0, 1, 1, 2> xyzy;
                Bool4Swizzle<Bool4, 3, 0, 1, 2, 2> xyzz;
                Bool4Swizzle<Bool4, 3, 0, 2, 0, 0> xzxx;
                Bool4Swizzle<Bool4, 3, 0, 2, 1, 0> xzxy;
                Bool4Swizzle<Bool4, 3, 0, 2, 2, 0> xzxz;
                Bool4Swizzle<Bool4, 3, 0, 2, 0, 1> xzyx;
                Bool4Swizzle<Bool4, 3, 0, 2, 1, 1> xzyy;
                Bool4Swizzle<Bool4, 3, 0, 2, 2, 1> xzyz;
                Bool4Swizzle<Bool4, 3, 0, 2, 0, 2> xzzx;
                Bool4Swizzle<Bool4, 3, 0, 2, 1, 2> xzzy;
                Bool4Swizzle<Bool4, 3, 0, 2, 2, 2> xzzz;
                Bool4Swizzle<Bool4, 3, 1, 0, 0, 0> yxxx;
                Bool4Swizzle<Bool4, 3, 1, 0, 1, 0> yxxy;
                Bool4Swizzle<Bool4, 3, 1, 0, 2, 0> yxxz;
                Bool4Swizzle<Bool4, 3, 1, 0, 0, 1> yxyx;
                Bool4Swizzle<Bool4, 3, 1, 0, 1, 1> yxyy;
                Bool4Swizzle<Bool4, 3, 1, 0, 2, 1> yxyz;
                Bool4Swizzle<Bool4, 3, 1, 0, 0, 2> yxzx;
                Bool4Swizzle<Bool4, 3, 1, 0, 1, 2> yxzy;
                Bool4Swizzle<Bool4, 3, 1, 0, 2, 2> yxzz;
                Bool4Swizzle<Bool4, 3, 1, 1, 0, 0> yyxx;
                Bool4Swizzle<Bool4, 3, 1, 1, 1, 0> yyxy;
                Bool4Swizzle<Bool4, 3, 1, 1, 2, 0> yyxz;
                Bool4Swizzle<Bool4, 3, 1, 1, 0, 1> yyyx;
                Bool4Swizzle<Bool4, 3, 1, 1, 1, 1> yyyy;
                Bool4Swizzle<Bool4, 3, 1, 1, 2, 1> yyyz;
                Bool4Swizzle<Bool4, 3, 1, 1, 0, 2> yyzx;
                Bool4Swizzle<Bool4, 3, 1, 1, 1, 2> yyzy;
                Bool4Swizzle<Bool4, 3, 1, 1, 2, 2> yyzz;
                Bool4Swizzle<Bool4, 3, 1, 2, 0, 0> yzxx;
                Bool4Swizzle<Bool4, 3, 1, 2, 1, 0> yzxy;
                Bool4Swizzle<Bool4, 3, 1, 2, 2, 0> yzxz;
                Bool4Swizzle<Bool4, 3, 1, 2, 0, 1> yzyx;
                Bool4Swizzle<Bool4, 3, 1, 2, 1, 1> yzyy;
                Bool4Swizzle<Bool4, 3, 1, 2, 2, 1> yzyz;
                Bool4Swizzle<Bool4, 3, 1, 2, 0, 2> yzzx;
                Bool4Swizzle<Bool4, 3, 1, 2, 1, 2> yzzy;
                Bool4Swizzle<Bool4, 3, 1, 2, 2, 2> yzzz;
                Bool4Swizzle<Bool4, 3, 2, 0, 0, 0> zxxx;
                Bool4Swizzle<Bool4, 3, 2, 0, 1, 0> zxxy;
                Bool4Swizzle<Bool4, 3, 2, 0, 2, 0> zxxz;
                Bool4Swizzle<Bool4, 3, 2, 0, 0, 1> zxyx;
                Bool4Swizzle<Bool4, 3, 2, 0, 1, 1> zxyy;
                Bool4Swizzle<Bool4, 3, 2, 0, 2, 1> zxyz;
                Bool4Swizzle<Bool4, 3, 2, 0, 0, 2> zxzx;
                Bool4Swizzle<Bool4, 3, 2, 0, 1, 2> zxzy;
                Bool4Swizzle<Bool4, 3, 2, 0, 2, 2> zxzz;
                Bool4Swizzle<Bool4, 3, 2, 1, 0, 0> zyxx;
                Bool4Swizzle<Bool4, 3, 2, 1, 1, 0> zyxy;
                Bool4Swizzle<Bool4, 3, 2, 1, 2, 0> zyxz;
                Bool4Swizzle<Bool4, 3, 2, 1, 0, 1> zyyx;
                Bool4Swizzle<Bool4, 3, 2, 1, 1, 1> zyyy;
                Bool4Swizzle<Bool4, 3, 2, 1, 2, 1> zyyz;
                Bool4Swizzle<Bool4, 3, 2, 1, 0, 2> zyzx;
                Bool4Swizzle<Bool4, 3, 2, 1, 1, 2> zyzy;
                Bool4Swizzle<Bool4, 3, 2, 1, 2, 2> zyzz;
                Bool4Swizzle<Bool4, 3, 2, 2, 0, 0> zzxx;
                Bool4Swizzle<Bool4, 3, 2, 2, 1, 0> zzxy;
                Bool4Swizzle<Bool4, 3, 2, 2, 2, 0> zzxz;
                Bool4Swizzle<Bool4, 3, 2, 2, 0, 1> zzyx;
                Bool4Swizzle<Bool4, 3, 2, 2, 1, 1> zzyy;
                Bool4Swizzle<Bool4, 3, 2, 2, 2, 1> zzyz;
                Bool4Swizzle<Bool4, 3, 2, 2, 0, 2> zzzx;
                Bool4Swizzle<Bool4, 3, 2, 2, 1, 2> zzzy;
                Bool4Swizzle<Bool4, 3, 2, 2, 2, 2> zzzz;
            };

            Bool3(bool x, bool y, bool z);

            Bool3(bool x, const Bool2 & yz);

            Bool3(const Bool2 & xy, bool z);

            Bool3(const Bool3 & xyz);

            Bool3();

            Bool3 & operator=(const Bool3 & rhs) noexcept;
Bool3 & operator=(bool rhs) noexcept;

            Bool3 operator||(const Bool3 & rhs) const noexcept;

            Bool3 operator&&(const Bool3 & rhs) const noexcept;

            Bool3 operator==(const Bool3 & rhs) const noexcept;

            Bool3 operator!=(const Bool3 & rhs) const noexcept;

            static Bool3 Random() noexcept;

            bool Any() const noexcept;

            bool All() const noexcept;

            Bool3 operator!() const noexcept;

            Bool3 & operator|=(const Bool3 & rhs) noexcept;

            Bool3 & operator&=(const Bool3 & rhs) noexcept;

            static const Bool3 One;
            static const Bool3 Zero;
            static const Bool3 UnitX;
            static const Bool3 UnitY;
            static const Bool3 UnitZ;
        };
    }
}

