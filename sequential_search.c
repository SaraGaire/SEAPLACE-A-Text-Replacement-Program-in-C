/*===================================================================
    sequential_search.c (default)
    sequential searching using 'memcmp()'

    Searching for a substring (pattern) inside a larger string (text). 
    
    text: pointer to the main text where we search.
    text_len: length of the main text (not necessarily null-terminated).
    pattern: pointer to the substring we are searching for.
    pat_len: length of the substring.
===================================================================*/
#include <string.h>
#include "search.h"

char *sequential_search(char *text, size_t text_len, 
                        const char *pattern, size_t pat_len) 
{
    /* basic sanity checks */
    if (text == NULL || pattern == NULL)
        return NULL;
        
    // If the pattern has length 0, nothing to search 
    // If the pattern is longer than the text, not found 
    if (pat_len == 0 || pat_len > text_len)
        return NULL;

    // iterate over every possible starting position i in text 
    // where the pattern could fit.
    for (size_t i = 0; i + pat_len <= text_len; i++) 
        // memcmp compares pat_len bytes of memory starting 
        // at text + i and pattern
        if (memcmp(text + i, pattern, pat_len) == 0)
            return text + i; // found, pointer to e first character of the found pattern 

    // not found
    return NULL;
}