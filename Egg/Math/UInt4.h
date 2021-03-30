#pragma once

#include "Bool4.h"
#include "UInt2.h"
#include "UInt3.h"

namespace Egg {
    namespace Math {

        class UInt2;
        class UInt3;
        class Bool2;
        class Bool3;
        class Bool4;

        class UInt4 {
        public:
            union {
                struct {
                    unsigned int x;
                    unsigned int y;
                    unsigned int z;
                    unsigned int w;
                };

                UInt2Swizzle<UInt2, Bool2, 4, 0, 0> xx;
                UInt2Swizzle<UInt2, Bool2, 4, 0, 1> xy;
                UInt2Swizzle<UInt2, Bool2, 4, 0, 2> xz;
                UInt2Swizzle<UInt2, Bool2, 4, 0, 3> xw;
                UInt2Swizzle<UInt2, Bool2, 4, 1, 0> yx;
                UInt2Swizzle<UInt2, Bool2, 4, 1, 1> yy;
                UInt2Swizzle<UInt2, Bool2, 4, 1, 2> yz;
                UInt2Swizzle<UInt2, Bool2, 4, 1, 3> yw;
                UInt2Swizzle<UInt2, Bool2, 4, 2, 0> zx;
                UInt2Swizzle<UInt2, Bool2, 4, 2, 1> zy;
                UInt2Swizzle<UInt2, Bool2, 4, 2, 2> zz;
                UInt2Swizzle<UInt2, Bool2, 4, 2, 3> zw;
                UInt2Swizzle<UInt2, Bool2, 4, 3, 0> wx;
                UInt2Swizzle<UInt2, Bool2, 4, 3, 1> wy;
                UInt2Swizzle<UInt2, Bool2, 4, 3, 2> wz;
                UInt2Swizzle<UInt2, Bool2, 4, 3, 3> ww;

                UInt3Swizzle<UInt3, Bool3, 4, 0, 0, 0> xxx;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 0, 1> xxy;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 0, 2> xxz;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 0, 3> xxw;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 1, 0> xyx;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 1, 1> xyy;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 1, 2> xyz;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 1, 3> xyw;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 2, 0> xzx;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 2, 1> xzy;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 2, 2> xzz;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 2, 3> xzw;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 3, 0> xwx;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 3, 1> xwy;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 3, 2> xwz;
                UInt3Swizzle<UInt3, Bool3, 4, 0, 3, 3> xww;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 0, 0> yxx;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 0, 1> yxy;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 0, 2> yxz;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 0, 3> yxw;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 1, 0> yyx;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 1, 1> yyy;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 1, 2> yyz;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 1, 3> yyw;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 2, 0> yzx;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 2, 1> yzy;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 2, 2> yzz;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 2, 3> yzw;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 3, 0> ywx;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 3, 1> ywy;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 3, 2> ywz;
                UInt3Swizzle<UInt3, Bool3, 4, 1, 3, 3> yww;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 0, 0> zxx;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 0, 1> zxy;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 0, 2> zxz;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 0, 3> zxw;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 1, 0> zyx;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 1, 1> zyy;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 1, 2> zyz;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 1, 3> zyw;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 2, 0> zzx;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 2, 1> zzy;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 2, 2> zzz;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 2, 3> zzw;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 3, 0> zwx;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 3, 1> zwy;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 3, 2> zwz;
                UInt3Swizzle<UInt3, Bool3, 4, 2, 3, 3> zww;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 0, 0> wxx;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 0, 1> wxy;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 0, 2> wxz;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 0, 3> wxw;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 1, 0> wyx;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 1, 1> wyy;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 1, 2> wyz;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 1, 3> wyw;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 2, 0> wzx;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 2, 1> wzy;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 2, 2> wzz;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 2, 3> wzw;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 3, 0> wwx;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 3, 1> wwy;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 3, 2> wwz;
                UInt3Swizzle<UInt3, Bool3, 4, 3, 3, 3> www;

                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 0, 0> xxxx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 1, 0> xxxy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 2, 0> xxxz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 3, 0> xxxw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 0, 1> xxyx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 1, 1> xxyy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 2, 1> xxyz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 3, 1> xxyw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 0, 2> xxzx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 1, 2> xxzy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 2, 2> xxzz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 3, 2> xxzw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 0, 3> xxwx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 1, 3> xxwy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 2, 3> xxwz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 0, 3, 3> xxww;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 0, 0> xyxx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 1, 0> xyxy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 2, 0> xyxz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 3, 0> xyxw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 0, 1> xyyx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 1, 1> xyyy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 2, 1> xyyz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 3, 1> xyyw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 0, 2> xyzx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 1, 2> xyzy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 2, 2> xyzz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 3, 2> xyzw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 0, 3> xywx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 1, 3> xywy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 2, 3> xywz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 1, 3, 3> xyww;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 0, 0> xzxx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 1, 0> xzxy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 2, 0> xzxz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 3, 0> xzxw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 0, 1> xzyx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 1, 1> xzyy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 2, 1> xzyz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 3, 1> xzyw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 0, 2> xzzx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 1, 2> xzzy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 2, 2> xzzz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 3, 2> xzzw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 0, 3> xzwx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 1, 3> xzwy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 2, 3> xzwz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 2, 3, 3> xzww;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 0, 0> xwxx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 1, 0> xwxy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 2, 0> xwxz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 3, 0> xwxw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 0, 1> xwyx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 1, 1> xwyy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 2, 1> xwyz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 3, 1> xwyw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 0, 2> xwzx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 1, 2> xwzy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 2, 2> xwzz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 3, 2> xwzw;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 0, 3> xwwx;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 1, 3> xwwy;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 2, 3> xwwz;
                UInt4Swizzle<UInt4, Bool4, 4, 0, 3, 3, 3> xwww;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 0, 0> yxxx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 1, 0> yxxy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 2, 0> yxxz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 3, 0> yxxw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 0, 1> yxyx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 1, 1> yxyy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 2, 1> yxyz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 3, 1> yxyw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 0, 2> yxzx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 1, 2> yxzy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 2, 2> yxzz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 3, 2> yxzw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 0, 3> yxwx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 1, 3> yxwy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 2, 3> yxwz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 0, 3, 3> yxww;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 0, 0> yyxx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 1, 0> yyxy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 2, 0> yyxz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 3, 0> yyxw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 0, 1> yyyx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 1, 1> yyyy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 2, 1> yyyz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 3, 1> yyyw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 0, 2> yyzx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 1, 2> yyzy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 2, 2> yyzz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 3, 2> yyzw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 0, 3> yywx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 1, 3> yywy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 2, 3> yywz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 1, 3, 3> yyww;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 0, 0> yzxx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 1, 0> yzxy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 2, 0> yzxz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 3, 0> yzxw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 0, 1> yzyx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 1, 1> yzyy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 2, 1> yzyz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 3, 1> yzyw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 0, 2> yzzx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 1, 2> yzzy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 2, 2> yzzz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 3, 2> yzzw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 0, 3> yzwx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 1, 3> yzwy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 2, 3> yzwz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 2, 3, 3> yzww;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 0, 0> ywxx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 1, 0> ywxy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 2, 0> ywxz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 3, 0> ywxw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 0, 1> ywyx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 1, 1> ywyy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 2, 1> ywyz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 3, 1> ywyw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 0, 2> ywzx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 1, 2> ywzy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 2, 2> ywzz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 3, 2> ywzw;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 0, 3> ywwx;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 1, 3> ywwy;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 2, 3> ywwz;
                UInt4Swizzle<UInt4, Bool4, 4, 1, 3, 3, 3> ywww;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 0, 0> zxxx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 1, 0> zxxy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 2, 0> zxxz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 3, 0> zxxw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 0, 1> zxyx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 1, 1> zxyy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 2, 1> zxyz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 3, 1> zxyw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 0, 2> zxzx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 1, 2> zxzy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 2, 2> zxzz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 3, 2> zxzw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 0, 3> zxwx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 1, 3> zxwy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 2, 3> zxwz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 0, 3, 3> zxww;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 0, 0> zyxx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 1, 0> zyxy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 2, 0> zyxz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 3, 0> zyxw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 0, 1> zyyx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 1, 1> zyyy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 2, 1> zyyz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 3, 1> zyyw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 0, 2> zyzx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 1, 2> zyzy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 2, 2> zyzz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 3, 2> zyzw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 0, 3> zywx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 1, 3> zywy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 2, 3> zywz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 1, 3, 3> zyww;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 0, 0> zzxx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 1, 0> zzxy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 2, 0> zzxz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 3, 0> zzxw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 0, 1> zzyx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 1, 1> zzyy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 2, 1> zzyz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 3, 1> zzyw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 0, 2> zzzx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 1, 2> zzzy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 2, 2> zzzz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 3, 2> zzzw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 0, 3> zzwx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 1, 3> zzwy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 2, 3> zzwz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 2, 3, 3> zzww;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 0, 0> zwxx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 1, 0> zwxy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 2, 0> zwxz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 3, 0> zwxw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 0, 1> zwyx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 1, 1> zwyy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 2, 1> zwyz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 3, 1> zwyw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 0, 2> zwzx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 1, 2> zwzy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 2, 2> zwzz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 3, 2> zwzw;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 0, 3> zwwx;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 1, 3> zwwy;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 2, 3> zwwz;
                UInt4Swizzle<UInt4, Bool4, 4, 2, 3, 3, 3> zwww;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 0, 0> wxxx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 1, 0> wxxy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 2, 0> wxxz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 3, 0> wxxw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 0, 1> wxyx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 1, 1> wxyy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 2, 1> wxyz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 3, 1> wxyw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 0, 2> wxzx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 1, 2> wxzy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 2, 2> wxzz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 3, 2> wxzw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 0, 3> wxwx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 1, 3> wxwy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 2, 3> wxwz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 0, 3, 3> wxww;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 0, 0> wyxx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 1, 0> wyxy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 2, 0> wyxz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 3, 0> wyxw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 0, 1> wyyx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 1, 1> wyyy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 2, 1> wyyz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 3, 1> wyyw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 0, 2> wyzx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 1, 2> wyzy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 2, 2> wyzz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 3, 2> wyzw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 0, 3> wywx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 1, 3> wywy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 2, 3> wywz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 1, 3, 3> wyww;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 0, 0> wzxx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 1, 0> wzxy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 2, 0> wzxz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 3, 0> wzxw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 0, 1> wzyx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 1, 1> wzyy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 2, 1> wzyz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 3, 1> wzyw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 0, 2> wzzx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 1, 2> wzzy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 2, 2> wzzz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 3, 2> wzzw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 0, 3> wzwx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 1, 3> wzwy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 2, 3> wzwz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 2, 3, 3> wzww;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 0, 0> wwxx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 1, 0> wwxy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 2, 0> wwxz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 3, 0> wwxw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 0, 1> wwyx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 1, 1> wwyy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 2, 1> wwyz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 3, 1> wwyw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 0, 2> wwzx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 1, 2> wwzy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 2, 2> wwzz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 3, 2> wwzw;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 0, 3> wwwx;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 1, 3> wwwy;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 2, 3> wwwz;
                UInt4Swizzle<UInt4, Bool4, 4, 3, 3, 3, 3> wwww;
            };

            UInt4(unsigned int x, unsigned int y, unsigned int z, unsigned int w);

            UInt4(unsigned int x, unsigned int y, const UInt2 & zw);

            UInt4(const UInt2 & xy, const UInt2 & zw);

            UInt4(const UInt2 & xy, unsigned int z, unsigned int w);

            UInt4(const UInt3 & xyz, unsigned int w);

            UInt4(unsigned int x, const UInt3 & yzw);

            UInt4(const UInt4 & xyzw);

            UInt4();

            UInt4 & operator=(const UInt4 & rhs) noexcept;
UInt4 & operator=(unsigned int rhs) noexcept;

            UInt4 & operator+=(const UInt4 & rhs) noexcept;
UInt4 & operator+=(unsigned int rhs) noexcept;

            UInt4 & operator-=(const UInt4 & rhs) noexcept;
UInt4 & operator-=(unsigned int rhs) noexcept;

            UInt4 & operator/=(const UInt4 & rhs) noexcept;
UInt4 & operator/=(unsigned int rhs) noexcept;

            UInt4 & operator*=(const UInt4 & rhs) noexcept;
UInt4 & operator*=(unsigned int rhs) noexcept;

            UInt4 & operator%=(const UInt4 & rhs) noexcept;
UInt4 & operator%=(unsigned int rhs) noexcept;

            UInt4 & operator|=(const UInt4 & rhs) noexcept;
UInt4 & operator|=(unsigned int rhs) noexcept;

            UInt4 & operator&=(const UInt4 & rhs) noexcept;
UInt4 & operator&=(unsigned int rhs) noexcept;

            UInt4 & operator^=(const UInt4 & rhs) noexcept;
UInt4 & operator^=(unsigned int rhs) noexcept;

            UInt4 & operator<<=(const UInt4 & rhs) noexcept;
UInt4 & operator<<=(unsigned int rhs) noexcept;

            UInt4 & operator>>=(const UInt4 & rhs) noexcept;
UInt4 & operator>>=(unsigned int rhs) noexcept;

            UInt4 operator*(const UInt4 & rhs) const noexcept;

            UInt4 operator/(const UInt4 & rhs) const noexcept;

            UInt4 operator+(const UInt4 & rhs) const noexcept;

            UInt4 operator-(const UInt4 & rhs) const noexcept;

            UInt4 operator%(const UInt4 & rhs) const noexcept;

            UInt4 operator|(const UInt4 & rhs) const noexcept;

            UInt4 operator&(const UInt4 & rhs) const noexcept;

            UInt4 operator^(const UInt4 & rhs) const noexcept;

            UInt4 operator<<(const UInt4 & rhs) const noexcept;

            UInt4 operator>>(const UInt4 & rhs) const noexcept;

            UInt4 operator||(const UInt4 & rhs) const noexcept;

            UInt4 operator&&(const UInt4 & rhs) const noexcept;

            Bool4 operator<(const UInt4 & rhs) const noexcept;

            Bool4 operator>(const UInt4 & rhs) const noexcept;

            Bool4 operator!=(const UInt4 & rhs) const noexcept;

            Bool4 operator==(const UInt4 & rhs) const noexcept;

            Bool4 operator>=(const UInt4 & rhs) const noexcept;

            Bool4 operator<=(const UInt4 & rhs) const noexcept;

            UInt4 operator~() const noexcept;

            UInt4 operator!() const noexcept;

            UInt4 operator++() noexcept;

            UInt4 operator++(int) noexcept;

            UInt4 operator--() noexcept;

            UInt4 operator--(int) noexcept;

            static UInt4 Random(unsigned int lower = 0, unsigned int upper = 6) noexcept;

            static const UInt4 One;
            static const UInt4 Zero;
            static const UInt4 UnitX;
            static const UInt4 UnitY;
            static const UInt4 UnitZ;
            static const UInt4 UnitW;
        };
    }
}

