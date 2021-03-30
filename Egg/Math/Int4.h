#pragma once

#include "Int3.h"
#include "Bool4.h"
#include "Int4.h"

namespace Egg {
    namespace Math {

        class Int2;
        class Int3;
        class Bool2;
        class Bool3;
        class Bool4;

        class Int4 {
        public:
            union {
                struct {
                    int x;
                    int y;
                    int z;
                    int w;
                };

                Int2Swizzle<Int2, Bool2, 4, 0, 0> xx;
                Int2Swizzle<Int2, Bool2, 4, 0, 1> xy;
                Int2Swizzle<Int2, Bool2, 4, 0, 2> xz;
                Int2Swizzle<Int2, Bool2, 4, 0, 3> xw;
                Int2Swizzle<Int2, Bool2, 4, 1, 0> yx;
                Int2Swizzle<Int2, Bool2, 4, 1, 1> yy;
                Int2Swizzle<Int2, Bool2, 4, 1, 2> yz;
                Int2Swizzle<Int2, Bool2, 4, 1, 3> yw;
                Int2Swizzle<Int2, Bool2, 4, 2, 0> zx;
                Int2Swizzle<Int2, Bool2, 4, 2, 1> zy;
                Int2Swizzle<Int2, Bool2, 4, 2, 2> zz;
                Int2Swizzle<Int2, Bool2, 4, 2, 3> zw;
                Int2Swizzle<Int2, Bool2, 4, 3, 0> wx;
                Int2Swizzle<Int2, Bool2, 4, 3, 1> wy;
                Int2Swizzle<Int2, Bool2, 4, 3, 2> wz;
                Int2Swizzle<Int2, Bool2, 4, 3, 3> ww;

                Int3Swizzle<Int3, Bool3, 4, 0, 0, 0> xxx;
                Int3Swizzle<Int3, Bool3, 4, 0, 0, 1> xxy;
                Int3Swizzle<Int3, Bool3, 4, 0, 0, 2> xxz;
                Int3Swizzle<Int3, Bool3, 4, 0, 0, 3> xxw;
                Int3Swizzle<Int3, Bool3, 4, 0, 1, 0> xyx;
                Int3Swizzle<Int3, Bool3, 4, 0, 1, 1> xyy;
                Int3Swizzle<Int3, Bool3, 4, 0, 1, 2> xyz;
                Int3Swizzle<Int3, Bool3, 4, 0, 1, 3> xyw;
                Int3Swizzle<Int3, Bool3, 4, 0, 2, 0> xzx;
                Int3Swizzle<Int3, Bool3, 4, 0, 2, 1> xzy;
                Int3Swizzle<Int3, Bool3, 4, 0, 2, 2> xzz;
                Int3Swizzle<Int3, Bool3, 4, 0, 2, 3> xzw;
                Int3Swizzle<Int3, Bool3, 4, 0, 3, 0> xwx;
                Int3Swizzle<Int3, Bool3, 4, 0, 3, 1> xwy;
                Int3Swizzle<Int3, Bool3, 4, 0, 3, 2> xwz;
                Int3Swizzle<Int3, Bool3, 4, 0, 3, 3> xww;
                Int3Swizzle<Int3, Bool3, 4, 1, 0, 0> yxx;
                Int3Swizzle<Int3, Bool3, 4, 1, 0, 1> yxy;
                Int3Swizzle<Int3, Bool3, 4, 1, 0, 2> yxz;
                Int3Swizzle<Int3, Bool3, 4, 1, 0, 3> yxw;
                Int3Swizzle<Int3, Bool3, 4, 1, 1, 0> yyx;
                Int3Swizzle<Int3, Bool3, 4, 1, 1, 1> yyy;
                Int3Swizzle<Int3, Bool3, 4, 1, 1, 2> yyz;
                Int3Swizzle<Int3, Bool3, 4, 1, 1, 3> yyw;
                Int3Swizzle<Int3, Bool3, 4, 1, 2, 0> yzx;
                Int3Swizzle<Int3, Bool3, 4, 1, 2, 1> yzy;
                Int3Swizzle<Int3, Bool3, 4, 1, 2, 2> yzz;
                Int3Swizzle<Int3, Bool3, 4, 1, 2, 3> yzw;
                Int3Swizzle<Int3, Bool3, 4, 1, 3, 0> ywx;
                Int3Swizzle<Int3, Bool3, 4, 1, 3, 1> ywy;
                Int3Swizzle<Int3, Bool3, 4, 1, 3, 2> ywz;
                Int3Swizzle<Int3, Bool3, 4, 1, 3, 3> yww;
                Int3Swizzle<Int3, Bool3, 4, 2, 0, 0> zxx;
                Int3Swizzle<Int3, Bool3, 4, 2, 0, 1> zxy;
                Int3Swizzle<Int3, Bool3, 4, 2, 0, 2> zxz;
                Int3Swizzle<Int3, Bool3, 4, 2, 0, 3> zxw;
                Int3Swizzle<Int3, Bool3, 4, 2, 1, 0> zyx;
                Int3Swizzle<Int3, Bool3, 4, 2, 1, 1> zyy;
                Int3Swizzle<Int3, Bool3, 4, 2, 1, 2> zyz;
                Int3Swizzle<Int3, Bool3, 4, 2, 1, 3> zyw;
                Int3Swizzle<Int3, Bool3, 4, 2, 2, 0> zzx;
                Int3Swizzle<Int3, Bool3, 4, 2, 2, 1> zzy;
                Int3Swizzle<Int3, Bool3, 4, 2, 2, 2> zzz;
                Int3Swizzle<Int3, Bool3, 4, 2, 2, 3> zzw;
                Int3Swizzle<Int3, Bool3, 4, 2, 3, 0> zwx;
                Int3Swizzle<Int3, Bool3, 4, 2, 3, 1> zwy;
                Int3Swizzle<Int3, Bool3, 4, 2, 3, 2> zwz;
                Int3Swizzle<Int3, Bool3, 4, 2, 3, 3> zww;
                Int3Swizzle<Int3, Bool3, 4, 3, 0, 0> wxx;
                Int3Swizzle<Int3, Bool3, 4, 3, 0, 1> wxy;
                Int3Swizzle<Int3, Bool3, 4, 3, 0, 2> wxz;
                Int3Swizzle<Int3, Bool3, 4, 3, 0, 3> wxw;
                Int3Swizzle<Int3, Bool3, 4, 3, 1, 0> wyx;
                Int3Swizzle<Int3, Bool3, 4, 3, 1, 1> wyy;
                Int3Swizzle<Int3, Bool3, 4, 3, 1, 2> wyz;
                Int3Swizzle<Int3, Bool3, 4, 3, 1, 3> wyw;
                Int3Swizzle<Int3, Bool3, 4, 3, 2, 0> wzx;
                Int3Swizzle<Int3, Bool3, 4, 3, 2, 1> wzy;
                Int3Swizzle<Int3, Bool3, 4, 3, 2, 2> wzz;
                Int3Swizzle<Int3, Bool3, 4, 3, 2, 3> wzw;
                Int3Swizzle<Int3, Bool3, 4, 3, 3, 0> wwx;
                Int3Swizzle<Int3, Bool3, 4, 3, 3, 1> wwy;
                Int3Swizzle<Int3, Bool3, 4, 3, 3, 2> wwz;
                Int3Swizzle<Int3, Bool3, 4, 3, 3, 3> www;

                Int4Swizzle<Int4, Bool4, 4, 0, 0, 0, 0> xxxx;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 1, 0> xxxy;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 2, 0> xxxz;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 3, 0> xxxw;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 0, 1> xxyx;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 1, 1> xxyy;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 2, 1> xxyz;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 3, 1> xxyw;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 0, 2> xxzx;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 1, 2> xxzy;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 2, 2> xxzz;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 3, 2> xxzw;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 0, 3> xxwx;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 1, 3> xxwy;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 2, 3> xxwz;
                Int4Swizzle<Int4, Bool4, 4, 0, 0, 3, 3> xxww;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 0, 0> xyxx;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 1, 0> xyxy;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 2, 0> xyxz;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 3, 0> xyxw;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 0, 1> xyyx;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 1, 1> xyyy;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 2, 1> xyyz;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 3, 1> xyyw;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 0, 2> xyzx;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 1, 2> xyzy;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 2, 2> xyzz;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 3, 2> xyzw;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 0, 3> xywx;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 1, 3> xywy;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 2, 3> xywz;
                Int4Swizzle<Int4, Bool4, 4, 0, 1, 3, 3> xyww;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 0, 0> xzxx;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 1, 0> xzxy;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 2, 0> xzxz;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 3, 0> xzxw;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 0, 1> xzyx;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 1, 1> xzyy;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 2, 1> xzyz;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 3, 1> xzyw;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 0, 2> xzzx;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 1, 2> xzzy;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 2, 2> xzzz;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 3, 2> xzzw;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 0, 3> xzwx;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 1, 3> xzwy;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 2, 3> xzwz;
                Int4Swizzle<Int4, Bool4, 4, 0, 2, 3, 3> xzww;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 0, 0> xwxx;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 1, 0> xwxy;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 2, 0> xwxz;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 3, 0> xwxw;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 0, 1> xwyx;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 1, 1> xwyy;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 2, 1> xwyz;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 3, 1> xwyw;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 0, 2> xwzx;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 1, 2> xwzy;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 2, 2> xwzz;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 3, 2> xwzw;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 0, 3> xwwx;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 1, 3> xwwy;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 2, 3> xwwz;
                Int4Swizzle<Int4, Bool4, 4, 0, 3, 3, 3> xwww;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 0, 0> yxxx;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 1, 0> yxxy;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 2, 0> yxxz;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 3, 0> yxxw;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 0, 1> yxyx;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 1, 1> yxyy;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 2, 1> yxyz;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 3, 1> yxyw;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 0, 2> yxzx;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 1, 2> yxzy;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 2, 2> yxzz;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 3, 2> yxzw;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 0, 3> yxwx;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 1, 3> yxwy;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 2, 3> yxwz;
                Int4Swizzle<Int4, Bool4, 4, 1, 0, 3, 3> yxww;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 0, 0> yyxx;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 1, 0> yyxy;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 2, 0> yyxz;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 3, 0> yyxw;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 0, 1> yyyx;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 1, 1> yyyy;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 2, 1> yyyz;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 3, 1> yyyw;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 0, 2> yyzx;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 1, 2> yyzy;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 2, 2> yyzz;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 3, 2> yyzw;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 0, 3> yywx;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 1, 3> yywy;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 2, 3> yywz;
                Int4Swizzle<Int4, Bool4, 4, 1, 1, 3, 3> yyww;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 0, 0> yzxx;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 1, 0> yzxy;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 2, 0> yzxz;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 3, 0> yzxw;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 0, 1> yzyx;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 1, 1> yzyy;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 2, 1> yzyz;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 3, 1> yzyw;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 0, 2> yzzx;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 1, 2> yzzy;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 2, 2> yzzz;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 3, 2> yzzw;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 0, 3> yzwx;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 1, 3> yzwy;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 2, 3> yzwz;
                Int4Swizzle<Int4, Bool4, 4, 1, 2, 3, 3> yzww;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 0, 0> ywxx;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 1, 0> ywxy;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 2, 0> ywxz;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 3, 0> ywxw;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 0, 1> ywyx;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 1, 1> ywyy;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 2, 1> ywyz;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 3, 1> ywyw;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 0, 2> ywzx;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 1, 2> ywzy;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 2, 2> ywzz;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 3, 2> ywzw;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 0, 3> ywwx;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 1, 3> ywwy;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 2, 3> ywwz;
                Int4Swizzle<Int4, Bool4, 4, 1, 3, 3, 3> ywww;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 0, 0> zxxx;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 1, 0> zxxy;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 2, 0> zxxz;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 3, 0> zxxw;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 0, 1> zxyx;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 1, 1> zxyy;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 2, 1> zxyz;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 3, 1> zxyw;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 0, 2> zxzx;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 1, 2> zxzy;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 2, 2> zxzz;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 3, 2> zxzw;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 0, 3> zxwx;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 1, 3> zxwy;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 2, 3> zxwz;
                Int4Swizzle<Int4, Bool4, 4, 2, 0, 3, 3> zxww;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 0, 0> zyxx;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 1, 0> zyxy;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 2, 0> zyxz;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 3, 0> zyxw;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 0, 1> zyyx;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 1, 1> zyyy;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 2, 1> zyyz;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 3, 1> zyyw;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 0, 2> zyzx;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 1, 2> zyzy;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 2, 2> zyzz;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 3, 2> zyzw;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 0, 3> zywx;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 1, 3> zywy;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 2, 3> zywz;
                Int4Swizzle<Int4, Bool4, 4, 2, 1, 3, 3> zyww;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 0, 0> zzxx;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 1, 0> zzxy;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 2, 0> zzxz;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 3, 0> zzxw;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 0, 1> zzyx;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 1, 1> zzyy;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 2, 1> zzyz;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 3, 1> zzyw;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 0, 2> zzzx;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 1, 2> zzzy;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 2, 2> zzzz;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 3, 2> zzzw;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 0, 3> zzwx;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 1, 3> zzwy;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 2, 3> zzwz;
                Int4Swizzle<Int4, Bool4, 4, 2, 2, 3, 3> zzww;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 0, 0> zwxx;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 1, 0> zwxy;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 2, 0> zwxz;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 3, 0> zwxw;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 0, 1> zwyx;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 1, 1> zwyy;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 2, 1> zwyz;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 3, 1> zwyw;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 0, 2> zwzx;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 1, 2> zwzy;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 2, 2> zwzz;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 3, 2> zwzw;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 0, 3> zwwx;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 1, 3> zwwy;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 2, 3> zwwz;
                Int4Swizzle<Int4, Bool4, 4, 2, 3, 3, 3> zwww;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 0, 0> wxxx;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 1, 0> wxxy;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 2, 0> wxxz;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 3, 0> wxxw;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 0, 1> wxyx;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 1, 1> wxyy;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 2, 1> wxyz;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 3, 1> wxyw;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 0, 2> wxzx;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 1, 2> wxzy;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 2, 2> wxzz;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 3, 2> wxzw;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 0, 3> wxwx;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 1, 3> wxwy;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 2, 3> wxwz;
                Int4Swizzle<Int4, Bool4, 4, 3, 0, 3, 3> wxww;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 0, 0> wyxx;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 1, 0> wyxy;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 2, 0> wyxz;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 3, 0> wyxw;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 0, 1> wyyx;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 1, 1> wyyy;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 2, 1> wyyz;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 3, 1> wyyw;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 0, 2> wyzx;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 1, 2> wyzy;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 2, 2> wyzz;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 3, 2> wyzw;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 0, 3> wywx;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 1, 3> wywy;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 2, 3> wywz;
                Int4Swizzle<Int4, Bool4, 4, 3, 1, 3, 3> wyww;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 0, 0> wzxx;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 1, 0> wzxy;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 2, 0> wzxz;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 3, 0> wzxw;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 0, 1> wzyx;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 1, 1> wzyy;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 2, 1> wzyz;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 3, 1> wzyw;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 0, 2> wzzx;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 1, 2> wzzy;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 2, 2> wzzz;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 3, 2> wzzw;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 0, 3> wzwx;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 1, 3> wzwy;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 2, 3> wzwz;
                Int4Swizzle<Int4, Bool4, 4, 3, 2, 3, 3> wzww;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 0, 0> wwxx;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 1, 0> wwxy;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 2, 0> wwxz;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 3, 0> wwxw;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 0, 1> wwyx;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 1, 1> wwyy;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 2, 1> wwyz;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 3, 1> wwyw;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 0, 2> wwzx;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 1, 2> wwzy;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 2, 2> wwzz;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 3, 2> wwzw;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 0, 3> wwwx;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 1, 3> wwwy;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 2, 3> wwwz;
                Int4Swizzle<Int4, Bool4, 4, 3, 3, 3, 3> wwww;
            };

            Int4(int x, int y, int z, int w);

            Int4(int x, int y, const Int2 & zw);

            Int4(const Int2 & xy, const Int2 & zw);

            Int4(const Int2 & xy, int z, int w);

            Int4(const Int3 & xyz, int w);

            Int4(int x, const Int3 & yzw);

            Int4(const Int4 & xyzw);

            Int4();

            Int4 & operator=(const Int4 & rhs) noexcept;
Int4 & operator=(int rhs) noexcept;

            Int4 & operator+=(const Int4 & rhs) noexcept;
Int4 & operator+=(int rhs) noexcept;

            Int4 & operator-=(const Int4 & rhs) noexcept;
Int4 & operator-=(int rhs) noexcept;

            Int4 & operator/=(const Int4 & rhs) noexcept;
Int4 & operator/=(int rhs) noexcept;

            Int4 & operator*=(const Int4 & rhs) noexcept;
Int4 & operator*=(int rhs) noexcept;

            Int4 & operator%=(const Int4 & rhs) noexcept;
Int4 & operator%=(int rhs) noexcept;

            Int4 & operator|=(const Int4 & rhs) noexcept;
Int4 & operator|=(int rhs) noexcept;

            Int4 & operator&=(const Int4 & rhs) noexcept;
Int4 & operator&=(int rhs) noexcept;

            Int4 & operator^=(const Int4 & rhs) noexcept;
Int4 & operator^=(int rhs) noexcept;

            Int4 & operator<<=(const Int4 & rhs) noexcept;
Int4 & operator<<=(int rhs) noexcept;

            Int4 & operator>>=(const Int4 & rhs) noexcept;
Int4 & operator>>=(int rhs) noexcept;

            Int4 operator*(const Int4 & rhs) const noexcept;

            Int4 operator/(const Int4 & rhs) const noexcept;

            Int4 operator+(const Int4 & rhs) const noexcept;

            Int4 operator-(const Int4 & rhs) const noexcept;

            Int4 operator%(const Int4 & rhs) const noexcept;

            Int4 operator|(const Int4 & rhs) const noexcept;

            Int4 operator&(const Int4 & rhs) const noexcept;

            Int4 operator^(const Int4 & rhs) const noexcept;

            Int4 operator<<(const Int4 & rhs) const noexcept;

            Int4 operator>>(const Int4 & rhs) const noexcept;

            Int4 operator||(const Int4 & rhs) const noexcept;

            Int4 operator&&(const Int4 & rhs) const noexcept;

            Bool4 operator<(const Int4 & rhs) const noexcept;

            Bool4 operator>(const Int4 & rhs) const noexcept;

            Bool4 operator!=(const Int4 & rhs) const noexcept;

            Bool4 operator==(const Int4 & rhs) const noexcept;

            Bool4 operator>=(const Int4 & rhs) const noexcept;

            Bool4 operator<=(const Int4 & rhs) const noexcept;

            Int4 operator~() const noexcept;

            Int4 operator!() const noexcept;

            Int4 operator++() noexcept;

            Int4 operator++(int) noexcept;

            Int4 operator--() noexcept;

            Int4 operator--(int) noexcept;

            static Int4 Random(int lower = 0, int upper = 6) noexcept;

            Int4 operator-() const noexcept;

            static const Int4 One;
            static const Int4 Zero;
            static const Int4 UnitX;
            static const Int4 UnitY;
            static const Int4 UnitZ;
            static const Int4 UnitW;
        };
    }
}

