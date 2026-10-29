#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static long parse_positive(const char *text)
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
    long mib = 128;
    long seconds = 60;

    if (argc > 1) mib = parse_positive(argv[1]);
    if (argc > 2) seconds = parse_positive(argv[2]);
    if (mib < 0 || seconds < 0) {
        fprintf(stderr, "usage: %s [MiB] [seconds]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((uint64_t)mib > SIZE_MAX / (1024U * 1024U)) {
        fprintf(stderr, "requested allocation is too large\n");
        return EXIT_FAILURE;
    }

    size_t bytes = (size_t)mib * 1024U * 1024U;
    printf("memory-hog: pid=%ld, allocating %ld MiB for %ld seconds\n", (long)getpid(), mib, seconds);
    fflush(stdout);

    unsigned char *memory = malloc(bytes);
    if (memory == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < bytes; i += 4096U) {
        memory[i] = (unsigned char)(i / 4096U);
    }
    if (bytes > 0) memory[bytes - 1] = 1;

    printf("memory-hog: allocation touched, sleeping\n");
    fflush(stdout);
    sleep((unsigned)seconds);
    printf("memory-hog: finished, marker=%u\n", (unsigned)memory[bytes - 1]);

    free(memory);
    return EXIT_SUCCESS;
}
