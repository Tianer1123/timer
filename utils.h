#ifndef __UTILS_H
#define __UTILS_H
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/types.h>

#ifndef likely
    #define likely(x)       __builtin_expect((x),1)
#endif
#ifndef unlikely
    #define unlikely(x)     __builtin_expect((x),0)
#endif

#define true  1
#define false 0

//#define jiffies ((rte_rdtsc() / rte_get_timer_hz()) * 1000)
#define HZ_1S   1000
#define swap_u32(a, b)  do { __u32 t = a; a = b; b = t; } while(0)
#define swap___u16(a, b)  do { __u32 t = a; a = b; b = t; } while(0)

#define smp_mb()    barrier()
#define smp_rmb()   barrier()
#define smp_wmb()   barrier()

#define min(a, b) ((a) < (b) ? (a) : (b))
#define countof(array) (sizeof (array) / sizeof ((array)[0]))
/* Compile read-write barrier */
#define barrier() asm volatile("": : :"memory")

/* Pause instruction to prevent excess processor bus usage */
//#define cpu_relax() asm volatile("pause\n": : :"memory")
#define cpu_relax() barrier()

/*
 * Check at compile time that something is of a particular type.
 * Always evaluates to 1 so you may use it easily in comparisons.
 **/
#define typecheck(type,x) \
({  type __dummy; \
    typeof(x) __dummy2; \
    (void)(&__dummy == &__dummy2); \
    1; \
})

/*
 * Check at compile time that 'function' is a certain type, or is a pointer
 * to that type (needs to use typedef for the function type.)
 **/
#define typecheck_fn(type,function) \
({  typeof(type) __tmp = function; \
    (void)__tmp; \
})

#define time_after(a,b)     \
    (typecheck(unsigned long, a) && \
     typecheck(unsigned long, b) && \
     ((long)(b) - (long)(a) < 0))
#define time_before(a,b)    time_after(b,a)

#define time_after_eq(a,b)  \
    (typecheck(unsigned long, a) && \
     typecheck(unsigned long, b) && \
     ((long)(a) - (long)(b) >= 0))
#define time_before_eq(a,b) time_after_eq(b,a)

/*
 *  * Calculate whether a is in the range of [b, c].
 *   */
#define time_in_range(a,b,c) \
    (time_after_eq(a,b) && \
     time_before_eq(a,c))

/*
 *  * Calculate whether a is in the range of [b, c).
 *   */
#define time_in_range_open(a,b,c) \
    (time_after_eq(a,b) && \
     time_before(a,c))

/* Same as above, but does so with platform independent 64bit types.
 *  * These must be used when utilizing jiffies_64 (i.e. return value of
 *   * get_jiffies_64() */
#define time_after64(a,b)   \
    (typecheck(__u64, a) && \
     typecheck(__u64, b) && \
     ((__s64)(b) - (__s64)(a) < 0))
#define time_before64(a,b)  time_after64(b,a)

#define time_after_eq64(a,b)    \
    (typecheck(__u64, a) && \
     typecheck(__u64, b) && \
     ((__s64)(a) - (__s64)(b) >= 0))
#define time_before_eq64(a,b)   time_after_eq64(b,a)
/*
 *  * These four macros compare jiffies and 'a' for convenience.
 *   */

/* time_is_before_jiffies(a) return true if a is before jiffies */
#define time_is_before_jiffies(a) time_after(jiffies, a)

/* time_is_after_jiffies(a) return true if a is after jiffies */
#define time_is_after_jiffies(a) time_before(jiffies, a)

/* time_is_before_eq_jiffies(a) return true if a is before or equal to jiffies*/
#define time_is_before_eq_jiffies(a) time_after_eq(jiffies, a)

/* time_is_after_eq_jiffies(a) return true if a is after or equal to jiffies*/
#define time_is_after_eq_jiffies(a) time_before_eq(jiffies, a)

/*
 *  * Have the 32 bit jiffies value wrap 5 minutes after boot
 *   * so jiffies wrap bugs show up earlier.
 *    */
#define INITIAL_JIFFIES ((unsigned long)(unsigned int) (-300*HZ))

#define __be32 uint32_t
#define bool int

#define BITS_PER_LONG __WORDSIZE

#endif /* __UTILS_H */
