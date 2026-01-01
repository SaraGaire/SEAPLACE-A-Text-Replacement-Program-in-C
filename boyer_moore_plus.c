/*===================================================================
    boyer_moore_plus.c
    Boyer–Moore search using both:
      - Bad-character rule
      - Good-suffix rule 

    prototype:
      char *boyer_moore_plus(char *text, size_t text_len,
                             const char *pattern, size_t pat_len);

    Behavior:
      - returns pointer to first occurrence of pattern inside text
      - returns NULL on invalid input or if no match found
      - pattern/text are treated as raw bytes (text may not be null-terminated)
===================================================================*/
#include<stdio.h>
#include<stdlib.h>
#include <stddef.h>
#include <string.h>
#include "search.h"

// Build the bad-character lookup table for Boyer-Moore.
// For each possible byte value (0–255), store the last index where it
// appears in the pattern. If the character does not appear, keep -1.
static void preprocess_badchar(const unsigned char *pat, size_t m, int badchar[256])
{
    for (int i = 0; i < 256; ++i) badchar[i] = -1;
    for (size_t i = 0; i < m; ++i) {
        badchar[pat[i]] = (int)i;
    }
}

/* Preprocess strong good-suffix rule.
   Produces:
     - suffix[i]: length of longest suffix of pat[0..i] that is also a suffix of pat
     - bmGs[i]: shift distance when mismatch occurs at position i (0-based)
   Algorithm adapted from standard Boyer-Moore preprocessing.
*/
static void preprocess_good_suffix(const unsigned char *pat, size_t m, int *suffix, int *bmGs)
{
    // 1) compute suffixes 
    suffix[m - 1] = (int)m;
    int g = (int)m - 1;
    int f = 0;
    for (int i = (int)m - 2; i >= 0; --i) {
        if (i > g && suffix[i + (int)m - 1 - f] < i - g) {
            suffix[i] = suffix[i + (int)m - 1 - f];
        } else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && pat[g] == pat[g + (int)m - 1 - f]) --g;
            suffix[i] = f - g;
        }
    }

    // 2) compute bmGs (initial fill with m) 
    for (size_t i = 0; i < m; ++i) bmGs[i] = (int)m;

    // 3) case for suffixes that are also prefix 
    int j = 0;
    for (int i = (int)m - 1; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            for (; j < (int)m - 1 - i; ++j) {
                if (bmGs[j] == (int)m)
                    bmGs[j] = (int)m - 1 - i;
            }
        }
    }

    // 4) remaining positions 
    for (int i = 0; i <= (int)m - 2; ++i) {
        int idx = (int)m - 1 - suffix[i];
        if (idx >= 0 && idx < (int)m)
            bmGs[idx] = (int)m - 1 - i;
    }
}

char *boyer_moore_plus(char *text, size_t text_len,
                       const char *pattern, size_t pat_len)
{
    // sanity checks 
    if (text == NULL || pattern == NULL)
        return NULL;
    if (pat_len == 0 || pat_len > text_len)
        return NULL;

    size_t n = text_len;
    size_t m = pat_len;

    // treat pattern/text as unsigned bytes for indexing 
    const unsigned char *pat = (const unsigned char *)pattern;
    const unsigned char *txt = (const unsigned char *)text;

    // bad-character table 
    int badchar[256];
    preprocess_badchar(pat, m, badchar);

    // good-suffix tables (suffix and bmGs) 
    int *suffix = (int *)malloc(sizeof(int) * (size_t)m);
    if (!suffix) return NULL; /* malloc failure */
    int *bmGs = (int *)malloc(sizeof(int) * (size_t)m);
    if (!bmGs) { free(suffix); return NULL; }

    preprocess_good_suffix(pat, m, suffix, bmGs);

    /* Search loop */
    size_t s = 0; // shift of the pattern with respect to text 
    while (s + m <= n) {
        int j = (int)m - 1;

        // compare from right to left 
        while (j >= 0 && pat[j] == txt[s + (size_t)j]) --j;

        if (j < 0) {
            // match found at shift s 
            free(suffix);
            free(bmGs);
            return text + s;
        } else {
            unsigned char bc = txt[s + (size_t)j];
            int last = badchar[bc]; /* -1 if not in pattern */
            int bc_shift = j - last;
            if (bc_shift < 1) bc_shift = 1;

            int gs_shift = bmGs[j]; //good-suffix suggested shift 

            int shift = bc_shift > gs_shift ? bc_shift : gs_shift;
            s += (size_t)shift;
        }
    }

    free(suffix);
    free(bmGs);
    return NULL; // not found 
}