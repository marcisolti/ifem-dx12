#include "Bool4.h"
#include <cmath>

namespace Egg {
    namespace Math {

        Bool4::Bool4(bool x, bool y, bool z, bool w) : x { x }, y { y }, z { z }, w { w }{ }

        Bool4::Bool4(bool x, bool y, const Bool2 & zw) : x { x }, y { y }, z { zw.x }, w { zw.y }{ }

        Bool4::Bool4(const Bool2 & xy, const Bool2 & zw) : x { xy.x }, y { xy.y }, z { zw.x }, w { zw.y }{ }

        Bool4::Bool4(const Bool2 & xy, bool z, bool w) : x { xy.x }, y { xy.y }, z { z }, w { w }{ }

        Bool4::Bool4(const Bool3 & xyz, bool w) : x { xyz.x }, y { xyz.y }, z { xyz.z }, w { w }{ }

        Bool4::Bool4(bool x, const Bool3 & yzw) : x { x }, y { yzw.x }, z { yzw.y }, w { yzw.z }{ }

        Bool4::Bool4(const Bool4 & xyzw) : x { xyzw.x }, y { xyzw.y }, z { xyzw.z }, w { xyzw.w }{ }

        Bool4::Bool4() : x{ false }, y{ false }, z{ false }, w{ false }{ }

        Bool4 & Bool4::operator=(const Bool4 & rhs) noexcept {
            this->x = rhs.x;
            this->y = rhs.y;
            this->z = rhs.z;
            this->w = rhs.w;
            return *this;
        }

        Bool4 & Bool4::operator=(bool rhs) noexcept {
            this->x = rhs;
            this->y = rhs;
            this->z = rhs;
            this->w = rhs;
            return *this;
        }

        Bool4 Bool4::operator||(const Bool4 & rhs) const noexcept {
            return Bool4 { this->x || rhs.x, this->y || rhs.y, this->z || rhs.z, this->w || rhs.w };
        }

        Bool4 Bool4::operator&&(const Bool4 & rhs) const noexcept {
            return Bool4 { this->x && rhs.x, this->y && rhs.y, this->z && rhs.z, this->w && rhs.w };
        }

        Bool4 Bool4::operator==(const Bool4 & rhs) const noexcept {
            return Bool4 { this->x == rhs.x, this->y == rhs.y, this->z == rhs.z, this->w == rhs.w };
        }

        Bool4 Bool4::operator!=(const Bool4 & rhs) const noexcept {
            return Bool4 { this->x != rhs.x, this->y != rhs.y, this->z != rhs.z, this->w != rhs.w };
        }

        Bool4 Bool4::Random() noexcept {
            return Bool4 { rand() % 2 == 0, rand() % 2 == 0, rand() % 2 == 0, rand() % 2 == 0 };
        }

        bool Bool4::Any() const noexcept {
            return x || y || z || w;
        }

        bool Bool4::All() const noexcept {
            return x &&  y &&  z &&  w;
        }

        Bool4 Bool4::operator!() const noexcept {
            return Bool4 {  !x,  !y,  !z,  !w };
        }

        Bool4 & Bool4::operator|=(const Bool4 & rhs) noexcept {
            x =x || rhs.x;
            y =y || rhs.y;
            z =z || rhs.z;
            w =w || rhs.w; 
            return *this;
        }

        Bool4 & Bool4::operator&=(const Bool4 & rhs) noexcept {
            x =x && rhs.x;
            y =y && rhs.y;
            z =z && rhs.z;
            w =w && rhs.w; 
            return *this;
        }

        const Bool4 Bool4::Zero { false, false, false, false };
        const Bool4 Bool4::UnitX { true, false, false, false };
        const Bool4 Bool4::UnitY { false, true, false, false };
        const Bool4 Bool4::UnitZ { false, false, true, false };
        const Bool4 Bool4::UnitW { false, false, false, true };
        const Bool4 Bool4::One { true, true, true, true };
    }
}

