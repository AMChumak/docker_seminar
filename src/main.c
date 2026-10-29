#include "text_stats.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    const char *path = argc > 1 ? argv[1] : "data/input.txt";

    struct text_stats stats;
    if (text_stats_from_file(path, &stats) != 0) {
        perror(path);
        return EXIT_FAILURE;
    }

    printf("Text report\n");
    printf("===========\n");
    printf("File: %s\n", path);
    printf("Lines: %zu\n", stats.lines);
    printf("Words: %zu\n", stats.words);
    printf("Bytes: %zu\n", stats.bytes);
    printf("Longest word: %zu\n", stats.longest_word);

    return EXIT_SUCCESS;
}
