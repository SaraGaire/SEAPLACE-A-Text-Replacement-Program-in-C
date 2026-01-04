#include "search.h"
#include <stddef.h>
#include <string.h>
#include <sys/types.h>

#define ALPHABET_SIZE 256  // all possible byte values

// Preprocess pattern: build last occurrence table
static void build_last_occurrence(const char *pattern, size_t pat_len, int last_occ[ALPHABET_SIZE]) 
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        last_occ[i] = -1; // default: character not in pattern

    for (size_t i = 0; i < pat_len; i++)
        last_occ[(unsigned char)pattern[i]] = (int)i;
}

char *boyer_moore_search(char *text, size_t text_len, const char *pattern, size_t pat_len) 
{
    if (pat_len == 0 || text_len < pat_len)
        return NULL;

    int last_occ[ALPHABET_SIZE];
    build_last_occurrence(pattern, pat_len, last_occ);

    size_t i = 0; // index in text

    while (i <= text_len - pat_len) {
        ssize_t j = pat_len - 1;

        // compare pattern from right to left
        while (j >= 0 && pattern[j] == text[i + j])
            j--;

        if (j < 0) {
            return text + i; // match found
        } else {
            // shift pattern so that bad character aligns or move by 1 if character not in pattern
            int shift = j - last_occ[(unsigned char)text[i + j]];
            i += (shift > 0) ? shift : 1;
        }
    }

    return NULL; // no match
}