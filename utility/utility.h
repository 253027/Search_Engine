#ifndef __UTILITY_HEAD_H__
#define __UTILITY_HEAD_H__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_CHECK(condition, msg, ...) errorif(condition, msg, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

void errorif(bool condition, const char *msg, const char *s1, int s2, const char *s3, ...);

#endif //__UTILITY_HEAD_H__