// Created by tomasz on 02.06.19.

#pragma once

#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, N, ...) N
#define COUNT_VARARGS(...) _GET_NTH_ARG(__VA_ARGS__, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define _GLUE_(x, y) x##y
#define _GLUE(x, y) _GLUE_(x, y)

#define _CALL_MACRO_X_FOR_1(x, _1) x(_1)
#define _CALL_MACRO_X_FOR_2(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_1(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_3(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_2(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_4(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_3(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_5(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_4(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_6(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_5(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_7(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_6(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_8(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_7(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_9(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_8(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_10(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_9(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_11(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_10(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_12(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_11(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_13(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_12(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_14(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_13(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_15(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_14(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_16(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_15(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_17(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_16(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_18(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_17(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_19(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_18(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_20(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_19(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_21(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_20(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_22(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_21(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_23(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_22(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_24(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_23(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_25(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_24(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_26(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_25(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_27(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_26(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_28(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_27(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_29(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_28(x, __VA_ARGS__)
#define _CALL_MACRO_X_FOR_30(x, _1, ...) x(_1); _CALL_MACRO_X_FOR_29(x, __VA_ARGS__)

#define CALL_MACRO_X_FOR_EACH(x, ...) _GLUE(_CALL_MACRO_X_FOR_, COUNT_VARARGS(__VA_ARGS__)) (x, __VA_ARGS__)



inline std::string __className(const std::string& prettyFunction){
    size_t colons = prettyFunction.find( "::" );
    if( colons == std::string::npos )
        return "::";
    size_t begin = prettyFunction.substr( 0, colons ).rfind( " " ) + 1;
    size_t end = colons - begin;

    return prettyFunction.substr( begin, end );
}
#define __CLASS_NAME__ __className(__PRETTY_FUNCTION__)
