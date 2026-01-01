/*===================================================================
    boyer_moore.c
    Boyer–Moore search using the Bad-Character rule.

    prototype:
      char *boyer_moore_search(char *text, size_t text_len,
                               const char *pattern, size_t pat_len);

    Behavior:
      - returns pointer to the first occurrence of pattern inside text
      - returns NULL on invalid input or if no match found
      - pattern/text are treated as raw bytes (text may not be null-terminated)
===================================================================*/
#include <stddef.h>
#include <string.h> /* for size_t */
#include "search.h"

char *boyer_moore_search(char *text, size_t text_len,
                         const char *pattern, size_t pat_len)
{
    // sanity checks 
    if (text == NULL || pattern == NULL)
        return NULL;

    // define : empty pattern or pattern longer than text => not found 
    if (pat_len == 0 || pat_len > text_len)
        return NULL;


    /* Build the "bad character" lookup table used by Boyer-Moore.
   For every possible byte value (0–255), we store the index of the
   last time that character appears in the pattern. If a character
   does not appear in the pattern at all, its value remains -1.
*/
  
    int badchar[256];
    for (int i = 0; i < 256; ++i)
        badchar[i] = -1;

    for (size_t i = 0; i < pat_len; ++i) {
        unsigned char c = (unsigned char) pattern[i];
        badchar[c] = (int)i; 
    }

    /* Boyer-Moore search loop:
   - Align the pattern at position 's' in the text (0 .. text_len - pat_len).
   - Compare characters from right to left starting at j = pat_len - 1.
   - If a mismatch occurs at text[s + j], use the bad-character table
     to shift the pattern so that the mismatched text character aligns
     with its last occurrence in the pattern.
*/
    size_t s = 0;
    while (s + pat_len <= text_len) {
        int j = (int)pat_len - 1;

        // compare from right to left 
        while (j >= 0 && pattern[j] == text[s + (size_t)j])
            --j;

        if (j < 0) {
            // full match found at shift s 
            return text + s;
        } else {
            unsigned char bad_char = (unsigned char) text[s + (size_t)j];
            int last = badchar[bad_char]; // -1 if not present in pattern 
            int shift = j - last;
            if (shift < 1)
                shift = 1; // always move forward at least one 
            s += (size_t)shift;
        }
    }

    // not found 
    return NULL;
}
