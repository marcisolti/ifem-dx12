#pragma once

#include "Bool2Swizzle.hpp"
#include "Bool3Swizzle.hpp"
#include "Bool4Swizzle.hpp"
#include "Bool3.h"
#include "Bool4.h"

namespace Egg {
    namespace Math {

        class Bool3;
        class Bool4;

        class Bool2 {
        public:
            union {
                struct {
                    bool x;
                    bool y;
                };

                Bool2Swizzle<Bool2, 2, 0, 0> xx;
                Bool2Swizzle<Bool2, 2, 0, 1> xy;
                Bool2Swizzle<Bool2, 2, 1, 0> yx;
                Bool2Swizzle<Bool2, 2, 1, 1> yy;

                Bool3Swizzle<Bool3, 2, 0, 0, 0> xxx;
                Bool3Swizzle<Bool3, 2, 0, 0, 1> xxy;
                Bool3Swizzle<Bool3, 2, 0, 1, 0> xyx;
                Bool3Swizzle<Bool3, 2, 0, 1, 1> xyy;
                Bool3Swizzle<Bool3, 2, 1, 0, 0> yxx;
                Bool3Swizzle<Bool3, 2, 1, 0, 1> yxy;
                Bool3Swizzle<Bool3, 2, 1, 1, 0> yyx;
                Bool3Swizzle<Bool3, 2, 1, 1, 1> yyy;

                Bool4Swizzle<Bool4, 2, 0, 0, 0, 0> xxxx;
                Bool4Swizzle<Bool4, 2, 0, 0, 1, 0> xxxy;
                Bool4Swizzle<Bool4, 2, 0, 0, 0, 1> xxyx;
                Bool4Swizzle<Bool4, 2, 0, 0, 1, 1> xxyy;
                Bool4Swizzle<Bool4, 2, 0, 1, 0, 0> xyxx;
                Bool4Swizzle<Bool4, 2, 0, 1, 1, 0> xyxy;
                Bool4Swizzle<Bool4, 2, 0, 1, 0, 1> xyyx;
                Bool4Swizzle<Bool4, 2, 0, 1, 1, 1> xyyy;
                Bool4Swizzle<Bool4, 2, 1, 0, 0, 0> yxxx;
                Bool4Swizzle<Bool4, 2, 1, 0, 1, 0> yxxy;
                Bool4Swizzle<Bool4, 2, 1, 0, 0, 1> yxyx;
                Bool4Swizzle<Bool4, 2, 1, 0, 1, 1> yxyy;
                Bool4Swizzle<Bool4, 2, 1, 1, 0, 0> yyxx;
                Bool4Swizzle<Bool4, 2, 1, 1, 1, 0> yyxy;
                Bool4Swizzle<Bool4, 2, 1, 1, 0, 1> yyyx;
                Bool4Swizzle<Bool4, 2, 1, 1, 1, 1> yyyy;
            };

            Bool2(bool x, bool y);

            Bool2(const Bool2 & xy);

            Bool2();

            Bool2 & operator=(const Bool2 & rhs) noexcept;
Bool2 & operator=(bool rhs) noexcept;

            Bool2 operator||(const Bool2 & rhs) const noexcept;

            Bool2 operator&&(const Bool2 & rhs) const noexcept;

            Bool2 operator==(const Bool2 & rhs) const noexcept;

            Bool2 operator!=(const Bool2 & rhs) const noexcept;

            static Bool2 Random() noexcept;

            bool Any() const noexcept;

            bool All() const noexcept;

            Bool2 operator!() const noexcept;

            Bool2 & operator|=(const Bool2 & rhs) noexcept;

            Bool2 & operator&=(const Bool2 & rhs) noexcept;

            static const Bool2 One;
            static const Bool2 Zero;
            static const Bool2 UnitX;
            static const Bool2 UnitY;
        };
    }
}

