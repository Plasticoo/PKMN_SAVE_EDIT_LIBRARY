#ifndef __DEFINES_H_
#define __DEFINES_H_

#define uint8_t  u8
#define uint16_t u16
#define uint32_t u32
#define uint64_t u64

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
