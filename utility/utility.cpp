#include "utility.h"

void errorif(bool condition, const char *msg, const char *s1, int s2, const char *s3, ...)
{
    if (!condition)
        return;
    va_list valst;
    va_start(valst, s3);
    char buf[2048];
    int len = snprintf(buf, 2047, "< %s %d %s > ", s1, s2, s3);
    vsnprintf(buf + len, 2047, msg, valst);
    va_end(valst);
    perror(buf);
    ::exit(EXIT_FAILURE);
}