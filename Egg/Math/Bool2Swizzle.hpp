#pragma once
namespace Egg {
    namespace Math {

        template<typename B, int nBase, int s0 = 0, int s1 = 0>
        class Bool2Swizzle {
            bool v[nBase];
        public:
            operator B () const noexcept {
                return B {
                    (s0 >= 0) ? v[s0] : ((s0 == -1) ? 0.0f : 1.0f),
                    (s1 >= 0) ? v[s1] : ((s1 == -1) ? 0.0f : 1.0f)
                };
            }
        Bool2Swizzle & operator=(const B & rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs.x;
            if(s1 >= 0) v[s1] = rhs.y;
            return *this;
        }

        Bool2Swizzle & operator=(bool rhs) noexcept {
            if(s0 >= 0) v[s0] = rhs;
            if(s1 >= 0) v[s1] = rhs;
            return *this;
        }

        B operator||(const B & rhs) const noexcept {
            B t = *this;
            return t || rhs;
        }

        B operator&&(const B & rhs) const noexcept {
            B t = *this;
            return t && rhs;
        }

        B operator==(const B & rhs) const noexcept {
            B t = *this;
            return t == rhs;
        }

        B operator!=(const B & rhs) const noexcept {
            B t = *this;
            return t != rhs;
        }


        bool Any() const noexcept {
            B t = *this;
            return t.x || t.y;
        }

        bool All() const noexcept {
            B t = *this;
            return t.x &&  t.y;
        }

        B operator!() const noexcept {
            B t = *this;
            return B {  !t.x,  !t.y };
        }

        B & operator|=(const B & rhs) noexcept {
            B t = *this;
            t.x =t.x || rhs.x;
            t.y =t.y || rhs.y; 
            return *this;
        }

        B & operator&=(const B & rhs) noexcept {
            B t = *this;
            t.x =t.x && rhs.x;
            t.y =t.y && rhs.y; 
            return *this;
        }

        };
    }
}

