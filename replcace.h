//replace inference algorithm
#ifndef REPLACE_H

#define REPLACE_H



#include "search.h"



// declare replace_in_file for use in main.c

int replace_in_file(const char *filename,

                    const char *original,

                    const char *replacement,

                    search_func_t search_func,

                    int replace_only_one,

                    int make_backup);



#endif // REPLACE_H
