#pragma once

#include "CVersion.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#ifndef __cplusplus
#include <stdint.h>
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
#endif

char32_t utf8_decode(const char* restrict text, size_t* restrict bytes_used);

size_t strlen16(const char16_t* str);
char16_t* strcpy16(char16_t* restrict dest, const char16_t* restrict src);
char16_t* strncpy16(char16_t* restrict dest, const char16_t* restrict src, size_t n);
size_t strlcpy16(char16_t* restrict dest, const char16_t* restrict src, size_t n);

#ifdef __cplusplus
}
#endif