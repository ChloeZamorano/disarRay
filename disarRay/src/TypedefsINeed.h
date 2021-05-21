#pragma once

#include <cstdint>
#include <math.h>
#include <xstring>

typedef std::int8_t   i8;
typedef std::uint8_t  u8;

typedef std::int16_t  i16;
typedef std::uint16_t u16;

typedef std::int32_t  i32;
typedef std::uint32_t u32;

typedef std::int64_t  i64;
typedef std::uint64_t u64;

typedef std::int64_t  i64;
typedef std::uint64_t u64;


// TODO: Do something about these not being fixed width.
typedef float_t     f32;
typedef double_t    f64;
typedef long double f128;


typedef std::basic_string<char>     str8;
typedef std::basic_string<char16_t> str16;
typedef std::basic_string<char32_t> str32;


#define interc(x, y)	reinterpret_cast	<x>(y)
#define constc(x, y)	const_cast			<x>(y)
#define dync(x, y)		dynamic_cast		<x>(y)
#define statc(x, y)		static_cast			<x>(y)
