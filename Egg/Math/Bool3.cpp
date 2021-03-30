#include "Bool3.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Bool3::Bool3(bool x, bool y, bool z) : x { x }, y { y }, z { z }{ }

        Bool3::Bool3(bool x, const Bool2 & yz) : x { x }, y { yz.x }, z { yz.y }{ }

        Bool3::Bool3(const Bool2 & xy, bool z) : x { xy.x }, y { xy.y }, z { z }{ }

        Bool3::Bool3(const Bool3 & xyz) : x { xyz.x }, y { xyz.y }, z { xyz.z }{ }

        Bool3::Bool3() : x{ false }, y{ false }, z{ false }{ }

        Bool3 & Bool3::operator=(const Bool3 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            return *this;
        }

        Bool3 & Bool3::operator=(bool rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            return *this;
        }

        Bool3 Bool3::operator||(const Bool3 & rhs) const noexcept {
            return Bool3 { this->x || rhs.x, this->y || rhs.y, this->z || rhs.z };
        }

        Bool3 Bool3::operator&&(const Bool3 & rhs) const noexcept {
            return Bool3 { this->x && rhs.x, this->y && rhs.y, this->z && rhs.z };
        }

        Bool3 Bool3::operator==(const Bool3 & rhs) const noexcept {
            return Bool3 { this->x == rhs.x, this->y == rhs.y, this->z == rhs.z };
        }

        Bool3 Bool3::operator!=(const Bool3 & rhs) const noexcept {
            return Bool3 { this->x != rhs.x, this->y != rhs.y, this->z != rhs.z };
        }

        Bool3 Bool3::Random() noexcept {
            return Bool3 { rand() % 2 == 0, rand() % 2 == 0, rand() % 2 == 0 };
        }

        bool Bool3::Any() const noexcept {
            return x || y || z;
        }

        bool Bool3::All() const noexcept {
            return x &&  y &&  z;
        }

        Bool3 Bool3::operator!() const noexcept {
            return Bool3 {  !x,  !y,  !z };
        }

        Bool3 & Bool3::operator|=(const Bool3 & rhs) noexcept {
            x =x || rhs.x;
            y =y || rhs.y;
            z =z || rhs.z; 
            return *this;
        }

        Bool3 & Bool3::operator&=(const Bool3 & rhs) noexcept {
            x =x && rhs.x;
            y =y && rhs.y;
            z =z && rhs.z; 
            return *this;
        }

        const Bool3 Bool3::One { true, true, true };
        const Bool3 Bool3::Zero { false, false, false };
        const Bool3 Bool3::UnitX { true, false, false };
        const Bool3 Bool3::UnitY { false, true, false };
        const Bool3 Bool3::UnitZ { false, false, true };
    }
}

