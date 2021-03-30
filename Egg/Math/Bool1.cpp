#include "Bool1.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Bool1::Bool1(bool x) : x { x }{ }

        Bool1::Bool1() : x{ false }{ }

        Bool1 & Bool1::operator=(const Bool1 & rhs) noexcept {
            this->x = rhs.x;
            return *this;
        }

        Bool1 & Bool1::operator=(bool rhs) noexcept {
            this->x = rhs;
            return *this;
        }

        Bool1 Bool1::operator||(const Bool1 & rhs) const noexcept {
            return Bool1 { this->x || rhs.x };
        }

        Bool1 Bool1::operator&&(const Bool1 & rhs) const noexcept {
            return Bool1 { this->x && rhs.x };
        }

        Bool1 Bool1::operator==(const Bool1 & rhs) const noexcept {
            return Bool1 { this->x == rhs.x };
        }

        Bool1 Bool1::operator!=(const Bool1 & rhs) const noexcept {
            return Bool1 { this->x != rhs.x };
        }

        Bool1 Bool1::Random() noexcept {
            return Bool1 { rand() % 2 == 0 };
        }

        bool Bool1::Any() const noexcept {
            return x;
        }

        bool Bool1::All() const noexcept {
            return x;
        }

        Bool1 Bool1::operator!() const noexcept {
            return Bool1 {  !x };
        }

        Bool1 & Bool1::operator|=(const Bool1 & rhs) noexcept {
            x =x || rhs.x; 
            return *this;
        }

        Bool1 & Bool1::operator&=(const Bool1 & rhs) noexcept {
            x =x && rhs.x; 
            return *this;
        }

    }
}

