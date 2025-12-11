/*===================================================================
    sequential_search.c (default)
    sequential searching using 'memcmp()'
===================================================================*/
#include <string.h>
#include "search.h"

char *sequential_search(char *text, size_t text_len, 
                        const char *pattern, size_t pat_len) 
{
    if (pat_len == 0 || pat_len > text_len)
        return NULL;

    for (size_t i = 0; i + pat_len <= text_len; i++) 
        if (memcmp(text + i, pattern, pat_len) == 0)
            return text + i;
    return NULL;
}