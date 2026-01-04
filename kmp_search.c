#include "search.h"
#include <stdlib.h>
#include <string.h>

// build the "longest prefix suffix" table (lps)
static void build_lps(const char *pattern, size_t pat_len, size_t *lps) {
    size_t len = 0;
    lps[0] = 0;

    for (size_t i = 1; i < pat_len; ) 
    {
        if (pattern[i] == pattern[len]) 
        {
            len++;
            lps[i] = len;
            i++;
        } 
        else 
        {
            if (len != 0) 
                len = lps[len - 1];
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search algorithm
char *kmp_search(char *text, size_t text_len, const char *pattern, size_t pat_len) 
{
    if (pat_len == 0 || text_len < pat_len)
        return NULL;

    size_t *lps = (size_t *)malloc(pat_len * sizeof(size_t));
    if (!lps) return NULL;

    build_lps(pattern, pat_len, lps);

    size_t i = 0; // index for text
    size_t j = 0; // index for pattern

    while (i < text_len) {
        if (text[i] == pattern[j]) 
        {
            i++;
            j++;
        }

        if (j == pat_len) 
        {
            free(lps);
            return text + (i - j); // match found
        } 
        else if (i < text_len && text[i] != pattern[j]) 
        {
            if (j != 0) 
                j = lps[j - 1];
            else 
                i++;
        }
    }

    free(lps);
    return NULL; // no match
}