#include "search.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define ALPHABET_SIZE 256

// Bad character table
static void build_bad_char(const char *pattern, size_t pat_len, int bad_char[ALPHABET_SIZE]) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        bad_char[i] = -1;
    for (size_t i = 0; i < pat_len; i++)
        bad_char[(unsigned char)pattern[i]] = (int)i;
}

// Good suffix preprocessing
static void build_good_suffix(const char *pattern, size_t pat_len, int *shift) {
    int i = (int)pat_len;
    int j = (int)pat_len + 1;
    int *border_pos = (int *)malloc((pat_len + 1) * sizeof(int));

    border_pos[i] = j;

    while (i > 0) {
        while (j <= (int)pat_len && pattern[i - 1] != pattern[j - 1])
            j = border_pos[j];
        i--;
        j--;
        border_pos[i] = j;
    }

    for (size_t k = 0; k <= (size_t)pat_len; k++)
        shift[k] = (int)pat_len;

    j = border_pos[0];
    for (ssize_t i = 0; i < (ssize_t)pat_len; i++) {
        if (shift[i] == (int)pat_len)
            shift[i] = j;
        if (i == j)
            j = border_pos[j];
    }

    free(border_pos);
}

char *boyer_moore_plus(char *text, size_t text_len, const char *pattern, size_t pat_len) {
    if (pat_len == 0 || text_len < pat_len)
        return NULL;

    int bad_char[ALPHABET_SIZE];
    build_bad_char(pattern, pat_len, bad_char);

    int *good_suffix = (int *)malloc(pat_len * sizeof(int));
    if (!good_suffix)
        return NULL;

    build_good_suffix(pattern, pat_len, good_suffix);

    size_t s = 0; // shift of pattern with respect to text

    while (s <= text_len - pat_len) {
        ssize_t j = (ssize_t)pat_len - 1;

        // Compare from right to left
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0) {
            free(good_suffix);
            return text + s; // match found
        } else {
            int bc_shift = j - bad_char[(unsigned char)text[s + j]];
            int gs_shift = good_suffix[j];
            s += (bc_shift > gs_shift) ? bc_shift : gs_shift;
        }
    }

    free(good_suffix);
    return NULL; // no match
}
