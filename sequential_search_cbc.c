
/*===================================================================
    sequential_search_cbc.c
    sequential search char-by-char
===================================================================*/
//#include <string.h>
#include "search.h"

char *sequential_search_cbc(char *text, size_t text_len,
                        const char *pattern, size_t pat_len)
{
    if (pat_len == 0 || pat_len > text_len)
        return NULL;

    for (size_t i = 0; i <= text_len - pat_len; i++) 
    {
        size_t j = 0;

        // compare byte-by-byte instead of memcmp()
        while (j < pat_len && text[i + j] == pattern[j]) 
            j++;

        if (j == pat_len) {
            // found match
            return text + i;
        }
    }
    return NULL;
}