/*
 * fibonacci.c - calculates the nth Fibonacci sequence number.
 * Copyright (C) 2025 asdftowel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Formula constants */
#define G_RATIO 1.6180339887498948
#define SQRT_5  2.2360679774997897

/* Check if standard version is at least C99 */
#if __STDC_VERSION__ < 199901L
#error "This program requires support for C99 or higher."
#elif __STDC_VERSION__ < 202311L
#include <stdbool.h> /* To use human-readable booleans */
#endif

/* For GNU-compatible compilers: check if -ffast-math is enabled */
#ifdef __RECIPROCAL_MATH__
#warning "It appears that you have enabled fast math. This may cause \
the results to be inaccurate."
#endif

/* Compiler-dependent optimization hints */
#ifdef __GNUC__
#define PURE __attribute__ ((pure))
#define CONST __attribute__ ((const))
#elif __STDC_VERSION__ >= 202311L
#define PURE [[reproducible]]
#define CONST [[unsequenced]]
#else
#define PURE
#define CONST
#endif

PURE static inline bool verify_arg(char const * restrict const arg) {
    size_t const str_size = strlen(arg);
    bool result;
    /*
     * Splitting these conditions into separate branches
     * makes the function harder to read due to multiple
     * identical assignments.
     */
    if (
        /* The argument is either too short or too long */
        ((str_size == 0) | (str_size > 2)) ||
        /* The argument isn't a non-negative integer */
        (!isdigit(arg[0]) | ((str_size == 2) && !isdigit(arg[1]))) ||
        /*
         * The argument is greater than 93:
         * fibonacci(94) is greater than the maximum value
         * of unsigned long long (assuming standard-defined
         * ULLONG_MAX >= (uint64_t)-1)
         */
        ((arg[0] == '9') & (arg[1] > '3'))
    ) {
        result = false;
    } else {
        result = true;
    }
    return result;
}

CONST static inline unsigned long long fibonacci(int const n) {
    /*
     * Computes the nth Fibonacci number.
     * See rounding-based formula:
     * https://en.wikipedia.org/wiki/Fibonacci_sequence
     */
    return (unsigned long long)round(pow(G_RATIO, (double)n) / SQRT_5);
}

int main(int argc, char **argv) {
    int exit_code = EXIT_SUCCESS;
    if ((argc == 2) && verify_arg(argv[1])) {
        printf("fibonacci(%s) = %llu\n", argv[1], fibonacci(atoi(argv[1])));
    } else {
        puts(
            "The only argument must be a non-negative integer lesser than 93."
        );
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
