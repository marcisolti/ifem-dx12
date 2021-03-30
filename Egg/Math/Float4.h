#pragma once

#include "Float2.h"
#include "Float3.h"
#include "Bool4.h"
#include "Int4.h"

namespace Egg {
    namespace Math {

        class Float2;
        class Float3;
        class Bool2;
        class Bool3;
        class Bool4;
        class Int2;
        class Int3;
        class Int4;

        class Float4 {
        public:
            union {
                struct {
                    float x;
                    float y;
                    float z;
                    float w;
                };

                Float2Swizzle<Float2, Int2, Bool2, 4, 0, 0> xx;
                Float2Swizzle<Float2, Int2, Bool2, 4, 0, 1> xy;
                Float2Swizzle<Float2, Int2, Bool2, 4, 0, 2> xz;
                Float2Swizzle<Float2, Int2, Bool2, 4, 0, 3> xw;
                Float2Swizzle<Float2, Int2, Bool2, 4, 1, 0> yx;
                Float2Swizzle<Float2, Int2, Bool2, 4, 1, 1> yy;
                Float2Swizzle<Float2, Int2, Bool2, 4, 1, 2> yz;
                Float2Swizzle<Float2, Int2, Bool2, 4, 1, 3> yw;
                Float2Swizzle<Float2, Int2, Bool2, 4, 2, 0> zx;
                Float2Swizzle<Float2, Int2, Bool2, 4, 2, 1> zy;
                Float2Swizzle<Float2, Int2, Bool2, 4, 2, 2> zz;
                Float2Swizzle<Float2, Int2, Bool2, 4, 2, 3> zw;
                Float2Swizzle<Float2, Int2, Bool2, 4, 3, 0> wx;
                Float2Swizzle<Float2, Int2, Bool2, 4, 3, 1> wy;
                Float2Swizzle<Float2, Int2, Bool2, 4, 3, 2> wz;
                Float2Swizzle<Float2, Int2, Bool2, 4, 3, 3> ww;

                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 0, 0> xxx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 0, 1> xxy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 0, 2> xxz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 0, 3> xxw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 1, 0> xyx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 1, 1> xyy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 1, 2> xyz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 1, 3> xyw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 2, 0> xzx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 2, 1> xzy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 2, 2> xzz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 2, 3> xzw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 3, 0> xwx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 3, 1> xwy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 3, 2> xwz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 0, 3, 3> xww;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 0, 0> yxx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 0, 1> yxy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 0, 2> yxz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 0, 3> yxw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 1, 0> yyx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 1, 1> yyy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 1, 2> yyz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 1, 3> yyw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 2, 0> yzx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 2, 1> yzy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 2, 2> yzz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 2, 3> yzw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 3, 0> ywx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 3, 1> ywy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 3, 2> ywz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 1, 3, 3> yww;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 0, 0> zxx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 0, 1> zxy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 0, 2> zxz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 0, 3> zxw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 1, 0> zyx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 1, 1> zyy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 1, 2> zyz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 1, 3> zyw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 2, 0> zzx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 2, 1> zzy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 2, 2> zzz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 2, 3> zzw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 3, 0> zwx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 3, 1> zwy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 3, 2> zwz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 2, 3, 3> zww;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 0, 0> wxx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 0, 1> wxy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 0, 2> wxz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 0, 3> wxw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 1, 0> wyx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 1, 1> wyy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 1, 2> wyz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 1, 3> wyw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 2, 0> wzx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 2, 1> wzy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 2, 2> wzz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 2, 3> wzw;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 3, 0> wwx;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 3, 1> wwy;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 3, 2> wwz;
                Float3Swizzle<Float3, Int3, Bool3, 4, 3, 3, 3> www;

                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 0, 0> xxxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 1, 0> xxxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 2, 0> xxxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 3, 0> xxxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 0, 1> xxyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 1, 1> xxyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 2, 1> xxyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 3, 1> xxyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 0, 2> xxzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 1, 2> xxzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 2, 2> xxzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 3, 2> xxzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 0, 3> xxwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 1, 3> xxwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 2, 3> xxwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 0, 3, 3> xxww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 0, 0> xyxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 1, 0> xyxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 2, 0> xyxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 3, 0> xyxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 0, 1> xyyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 1, 1> xyyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 2, 1> xyyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 3, 1> xyyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 0, 2> xyzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 1, 2> xyzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 2, 2> xyzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 3, 2> xyzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 0, 3> xywx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 1, 3> xywy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 2, 3> xywz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 1, 3, 3> xyww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 0, 0> xzxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 1, 0> xzxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 2, 0> xzxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 3, 0> xzxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 0, 1> xzyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 1, 1> xzyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 2, 1> xzyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 3, 1> xzyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 0, 2> xzzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 1, 2> xzzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 2, 2> xzzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 3, 2> xzzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 0, 3> xzwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 1, 3> xzwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 2, 3> xzwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 2, 3, 3> xzww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 0, 0> xwxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 1, 0> xwxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 2, 0> xwxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 3, 0> xwxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 0, 1> xwyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 1, 1> xwyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 2, 1> xwyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 3, 1> xwyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 0, 2> xwzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 1, 2> xwzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 2, 2> xwzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 3, 2> xwzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 0, 3> xwwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 1, 3> xwwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 2, 3> xwwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 0, 3, 3, 3> xwww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 0, 0> yxxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 1, 0> yxxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 2, 0> yxxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 3, 0> yxxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 0, 1> yxyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 1, 1> yxyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 2, 1> yxyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 3, 1> yxyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 0, 2> yxzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 1, 2> yxzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 2, 2> yxzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 3, 2> yxzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 0, 3> yxwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 1, 3> yxwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 2, 3> yxwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 0, 3, 3> yxww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 0, 0> yyxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 1, 0> yyxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 2, 0> yyxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 3, 0> yyxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 0, 1> yyyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 1, 1> yyyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 2, 1> yyyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 3, 1> yyyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 0, 2> yyzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 1, 2> yyzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 2, 2> yyzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 3, 2> yyzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 0, 3> yywx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 1, 3> yywy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 2, 3> yywz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 1, 3, 3> yyww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 0, 0> yzxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 1, 0> yzxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 2, 0> yzxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 3, 0> yzxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 0, 1> yzyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 1, 1> yzyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 2, 1> yzyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 3, 1> yzyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 0, 2> yzzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 1, 2> yzzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 2, 2> yzzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 3, 2> yzzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 0, 3> yzwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 1, 3> yzwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 2, 3> yzwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 2, 3, 3> yzww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 0, 0> ywxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 1, 0> ywxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 2, 0> ywxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 3, 0> ywxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 0, 1> ywyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 1, 1> ywyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 2, 1> ywyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 3, 1> ywyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 0, 2> ywzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 1, 2> ywzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 2, 2> ywzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 3, 2> ywzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 0, 3> ywwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 1, 3> ywwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 2, 3> ywwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 1, 3, 3, 3> ywww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 0, 0> zxxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 1, 0> zxxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 2, 0> zxxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 3, 0> zxxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 0, 1> zxyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 1, 1> zxyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 2, 1> zxyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 3, 1> zxyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 0, 2> zxzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 1, 2> zxzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 2, 2> zxzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 3, 2> zxzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 0, 3> zxwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 1, 3> zxwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 2, 3> zxwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 0, 3, 3> zxww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 0, 0> zyxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 1, 0> zyxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 2, 0> zyxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 3, 0> zyxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 0, 1> zyyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 1, 1> zyyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 2, 1> zyyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 3, 1> zyyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 0, 2> zyzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 1, 2> zyzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 2, 2> zyzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 3, 2> zyzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 0, 3> zywx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 1, 3> zywy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 2, 3> zywz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 1, 3, 3> zyww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 0, 0> zzxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 1, 0> zzxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 2, 0> zzxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 3, 0> zzxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 0, 1> zzyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 1, 1> zzyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 2, 1> zzyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 3, 1> zzyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 0, 2> zzzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 1, 2> zzzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 2, 2> zzzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 3, 2> zzzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 0, 3> zzwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 1, 3> zzwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 2, 3> zzwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 2, 3, 3> zzww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 0, 0> zwxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 1, 0> zwxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 2, 0> zwxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 3, 0> zwxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 0, 1> zwyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 1, 1> zwyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 2, 1> zwyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 3, 1> zwyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 0, 2> zwzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 1, 2> zwzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 2, 2> zwzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 3, 2> zwzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 0, 3> zwwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 1, 3> zwwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 2, 3> zwwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 2, 3, 3, 3> zwww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 0, 0> wxxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 1, 0> wxxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 2, 0> wxxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 3, 0> wxxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 0, 1> wxyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 1, 1> wxyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 2, 1> wxyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 3, 1> wxyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 0, 2> wxzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 1, 2> wxzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 2, 2> wxzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 3, 2> wxzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 0, 3> wxwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 1, 3> wxwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 2, 3> wxwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 0, 3, 3> wxww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 0, 0> wyxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 1, 0> wyxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 2, 0> wyxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 3, 0> wyxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 0, 1> wyyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 1, 1> wyyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 2, 1> wyyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 3, 1> wyyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 0, 2> wyzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 1, 2> wyzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 2, 2> wyzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 3, 2> wyzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 0, 3> wywx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 1, 3> wywy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 2, 3> wywz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 1, 3, 3> wyww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 0, 0> wzxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 1, 0> wzxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 2, 0> wzxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 3, 0> wzxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 0, 1> wzyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 1, 1> wzyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 2, 1> wzyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 3, 1> wzyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 0, 2> wzzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 1, 2> wzzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 2, 2> wzzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 3, 2> wzzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 0, 3> wzwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 1, 3> wzwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 2, 3> wzwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 2, 3, 3> wzww;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 0, 0> wwxx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 1, 0> wwxy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 2, 0> wwxz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 3, 0> wwxw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 0, 1> wwyx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 1, 1> wwyy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 2, 1> wwyz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 3, 1> wwyw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 0, 2> wwzx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 1, 2> wwzy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 2, 2> wwzz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 3, 2> wwzw;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 0, 3> wwwx;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 1, 3> wwwy;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 2, 3> wwwz;
                Float4Swizzle<Float4, Int4, Bool4, 4, 3, 3, 3, 3> wwww;
            };

            Float4(float x, float y, float z, float w);

            Float4(float x, float y, const Float2 & zw);

            Float4(const Float2 & xy, const Float2 & zw);

            Float4(const Float2 & xy, float z, float w);

            Float4(const Float3 & xyz, float w);

            Float4(float x, const Float3 & yzw);

            Float4(const Float4 & xyzw);

            Float4();

            Float4 & operator=(const Float4 & rhs) noexcept;
Float4 & operator=(float rhs) noexcept;

            Float4 & operator+=(const Float4 & rhs) noexcept;
Float4 & operator+=(float rhs) noexcept;

            Float4 & operator-=(const Float4 & rhs) noexcept;
Float4 & operator-=(float rhs) noexcept;

            Float4 & operator/=(const Float4 & rhs) noexcept;
Float4 & operator/=(float rhs) noexcept;

            Float4 & operator*=(const Float4 & rhs) noexcept;
Float4 & operator*=(float rhs) noexcept;

            Float4 operator*(const Float4 & rhs) const noexcept;

            Float4 operator/(const Float4 & rhs) const noexcept;

            Float4 operator+(const Float4 & rhs) const noexcept;

            Float4 operator-(const Float4 & rhs) const noexcept;

            Float4 Abs() const noexcept;

            Float4 Acos() const noexcept;

            Float4 Asin() const noexcept;

            Float4 Atan() const noexcept;

            Float4 Cos() const noexcept;

            Float4 Sin() const noexcept;

            Float4 Cosh() const noexcept;

            Float4 Sinh() const noexcept;

            Float4 Tan() const noexcept;

            Float4 Exp() const noexcept;

            Float4 Log() const noexcept;

            Float4 Log10() const noexcept;

            Float4 Fmod(const Float4 & rhs) const noexcept;

            Float4 Atan2(const Float4 & rhs) const noexcept;

            Float4 Pow(const Float4 & rhs) const noexcept;

            Float4 Sqrt() const noexcept;

            Float4 Clamp(const Float4 & low, const Float4 & high) const noexcept;

            float Dot(const Float4 & rhs) const noexcept;

            Float4 Sign() const noexcept;

            Int4 Round() const noexcept;

            Float4 Saturate() const noexcept;

            float LengthSquared() const noexcept;

            float Length() const noexcept;

            Float4 Normalize() const noexcept;

            Bool4 IsNan() const noexcept;

            Bool4 IsFinite() const noexcept;

            Bool4 IsInfinite() const noexcept;

            Float4 operator-() const noexcept;

            Float4 operator%(const Float4 & rhs) const noexcept;

            Float4 & operator%=(const Float4 & rhs) noexcept;

            Int4 Ceil() const noexcept;

            Int4 Floor() const noexcept;

            Float4 Exp2() const noexcept;

            Int4 Trunc() const noexcept;

            float Distance(const Float4 & rhs) const noexcept;

            Bool4 operator<(const Float4 & rhs) const noexcept;

            Bool4 operator>(const Float4 & rhs) const noexcept;

            Bool4 operator!=(const Float4 & rhs) const noexcept;

            Bool4 operator==(const Float4 & rhs) const noexcept;

            Bool4 operator>=(const Float4 & rhs) const noexcept;

            Bool4 operator<=(const Float4 & rhs) const noexcept;

            static Float4 Random(float lower = 0.0f, float upper = 1.0f) noexcept;

            Float4 operator+(float v) const noexcept;

            Float4 operator-(float v) const noexcept;

            Float4 operator*(float v) const noexcept;

            Float4 operator/(float v) const noexcept;

            Float4 operator%(float v) const noexcept;

            Float4 operator!() const noexcept;

            static const Float4 UnitX;
            static const Float4 UnitY;
            static const Float4 UnitZ;
            static const Float4 UnitW;
            static const Float4 Zero;
            static const Float4 One;
            static const Float4 Identity;
        };
    }
}

