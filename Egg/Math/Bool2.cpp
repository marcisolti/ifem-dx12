#include "Bool2.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Bool2::Bool2(bool x, bool y) : x { x }, y { y }{ }

        Bool2::Bool2(const Bool2 & xy) : x { xy.x }, y { xy.y }{ }

        Bool2::Bool2() : x{ false }, y{ false }{ }

        Bool2 & Bool2::operator=(const Bool2 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            return *this;
        }

        Bool2 & Bool2::operator=(bool rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            return *this;
        }

        Bool2 Bool2::operator||(const Bool2 & rhs) const noexcept {
            return Bool2 { this->x || rhs.x, this->y || rhs.y };
        }

        Bool2 Bool2::operator&&(const Bool2 & rhs) const noexcept {
            return Bool2 { this->x && rhs.x, this->y && rhs.y };
        }

        Bool2 Bool2::operator==(const Bool2 & rhs) const noexcept {
            return Bool2 { this->x == rhs.x, this->y == rhs.y };
        }

        Bool2 Bool2::operator!=(const Bool2 & rhs) const noexcept {
            return Bool2 { this->x != rhs.x, this->y != rhs.y };
        }

        Bool2 Bool2::Random() noexcept {
            return Bool2 { rand() % 2 == 0, rand() % 2 == 0 };
        }

        bool Bool2::Any() const noexcept {
            return x || y;
        }

        bool Bool2::All() const noexcept {
            return x &&  y;
        }

        Bool2 Bool2::operator!() const noexcept {
            return Bool2 {  !x,  !y };
        }

        Bool2 & Bool2::operator|=(const Bool2 & rhs) noexcept {
            x =x || rhs.x;
            y =y || rhs.y; 
            return *this;
        }

        Bool2 & Bool2::operator&=(const Bool2 & rhs) noexcept {
            x =x && rhs.x;
            y =y && rhs.y; 
            return *this;
        }

        const Bool2 Bool2::One { true, true };
        const Bool2 Bool2::Zero { false, false };
        const Bool2 Bool2::UnitX { true, false };
        const Bool2 Bool2::UnitY { false, true };
    }
}

