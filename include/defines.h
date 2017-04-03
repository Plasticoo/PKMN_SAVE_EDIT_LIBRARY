#ifndef __DEFINES_H_
#define __DEFINES_H_

/*
#define uint8_t  u8
#define uint16_t u16
#define uint32_t u32
#define uint64_t u64
*/

#include <inttypes.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define FILE_OPEN_ERR 1
#define FILE_SIZE_ERR 2

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

// debug string
#define PDEBUG(fmt, ...)                                                \
    do { if (DEBUG_TEST) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__,  \
                                 __LINE__, __func__, ##__VA_ARGS__); } while (0)

#endif
