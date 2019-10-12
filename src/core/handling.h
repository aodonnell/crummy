#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define CleanErrno() (errno == 0 ? "None" : strerror(errno))
#define LogError(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, CleanErrno(), ##__VA_ARGS__)
#define assertf(A, M, ...) if(!(A)) {LogError(M, ##__VA_ARGS__); assert(A); }