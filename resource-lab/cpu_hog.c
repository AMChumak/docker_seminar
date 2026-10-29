#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static long parse_seconds(const char *text)
{
    char *end = NULL;
    errno = 0;
    long value = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || value <= 0) {
        return -1;
    }
    return value;
}

int main(int argc, char **argv)
{
    long seconds = 60;
    if (argc > 1) {
        seconds = parse_seconds(argv[1]);
        if (seconds < 0) {
            fprintf(stderr, "usage: %s [seconds]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    printf("cpu-hog: pid=%ld, duration=%ld seconds\n", (long)getpid(), seconds);
    fflush(stdout);

    struct timespec start;
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0) {
        perror("clock_gettime");
        return EXIT_FAILURE;
    }

    volatile uint64_t value = 1;
    for (;;) {
        for (unsigned i = 0; i < 1000000U; ++i) {
            value = value * 1664525U + 1013904223U;
        }

        struct timespec now;
        if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) {
            perror("clock_gettime");
            return EXIT_FAILURE;
        }
        if ((now.tv_sec - start.tv_sec) >= seconds) {
            break;
        }
    }

    printf("cpu-hog: finished (%llu)\n", (unsigned long long)value);
    return EXIT_SUCCESS;
}
