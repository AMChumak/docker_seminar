#include "text_stats.h"

#include <ctype.h>
#include <stdio.h>

int text_stats_from_file(const char *path, struct text_stats *result)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        return -1;
    }

    struct text_stats stats = {0};
    size_t current_word = 0;
    int in_word = 0;
    int ch;
    int saw_any = 0;
    int last_char = '\n';

    while ((ch = fgetc(file)) != EOF) {
        saw_any = 1;
        last_char = ch;
        stats.bytes++;

        if (ch == '\n') {
            stats.lines++;
        }

        if (isspace((unsigned char)ch)) {
            if (in_word) {
                if (current_word > stats.longest_word) {
                    stats.longest_word = current_word;
                }
                current_word = 0;
                in_word = 0;
            }
        } else {
            if (!in_word) {
                stats.words++;
                in_word = 1;
            }
            current_word++;
        }
    }

    if (in_word && current_word > stats.longest_word) {
        stats.longest_word = current_word;
    }

    if (saw_any && last_char != '\n') {
        stats.lines++;
    }

    if (ferror(file)) {
        fclose(file);
        return -1;
    }

    fclose(file);
    *result = stats;
    return 0;
}
