#ifndef TEXT_STATS_H
#define TEXT_STATS_H

#include <stddef.h>

struct text_stats {
    size_t lines;
    size_t words;
    size_t bytes;
    size_t longest_word;
};

int text_stats_from_file(const char *path, struct text_stats *result);

#endif
