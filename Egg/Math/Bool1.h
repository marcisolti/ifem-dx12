#pragma once

#include "Bool2Swizzle.hpp"
#include "Bool3Swizzle.hpp"
#include "Bool4Swizzle.hpp"

namespace Egg {
    namespace Math {

        class Bool1 {
        public:
            union {
                struct {
                    bool x;
                };
            };

            Bool1(bool x);

            Bool1();

            Bool1 & operator=(const Bool1 & rhs) noexcept;
Bool1 & operator=(bool rhs) noexcept;

            Bool1 operator||(const Bool1 & rhs) const noexcept;

            Bool1 operator&&(const Bool1 & rhs) const noexcept;

            Bool1 operator==(const Bool1 & rhs) const noexcept;

            Bool1 operator!=(const Bool1 & rhs) const noexcept;

            static Bool1 Random() noexcept;

            bool Any() const noexcept;

            bool All() const noexcept;

            Bool1 operator!() const noexcept;

            Bool1 & operator|=(const Bool1 & rhs) noexcept;

            Bool1 & operator&=(const Bool1 & rhs) noexcept;

        };
    }
}

