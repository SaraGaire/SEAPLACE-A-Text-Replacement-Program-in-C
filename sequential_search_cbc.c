/*===================================================================
    sequential_search_cbc.c
    sequential searching character-by-character (CBC)

    Returns:
      - pointer to the first occurrence of pattern inside text
      - NULL if not found or invalid input

    Notes:
      - text: pointer to the main text in memory (may not be null-terminated)
      - text_len: length of text in bytes
      - pattern: pointer to the substring we search for
      - pat_len: length of the substring in bytes
===================================================================*/
#include <stddef.h>
#include "search.h"

char *sequential_search_cbc(char *text, size_t text_len,
                            const char *pattern, size_t pat_len)
{
    // basic sanity checks 
    if (text == NULL || pattern == NULL)
        return NULL;

    // empty pattern or pattern longer than text -> not found  
    if (pat_len == 0 || pat_len > text_len)
        return NULL;

    // For each possible start position i in text where pattern can fit 
    for (size_t i = 0; i + pat_len <= text_len; ++i) {
        size_t j = 0;

        // compare pattern character-by-character 
        while (j < pat_len && text[i + j] == pattern[j]) {
            ++j;
        }

        if (j == pat_len) {
            // full match found 
            return text + i;
        }
        /* otherwise continue with next i */
    }

    // no match found 
    return NULL;
}