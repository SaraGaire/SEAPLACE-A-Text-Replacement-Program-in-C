
#define _GNU_SOURCE



#include "search.h"

#include "replace.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <errno.h>

#include <unistd.h> // for getopt
//headers



  // main 

int main(int argc, char *argv[]) 

{

    int make_backup = 0;        //Flag to create a backup file before modifying

    int replace_only_one = 0;   // Flag to replace only the first occurrence

    search_func_t search_algorithm = sequential_search; // default



    // option

    int opt;

    while ((opt = getopt(argc, argv, "a:b1")) != -1) 

    {

        switch (opt) //algorithm search using the if else function looking for the copies

        {

            case 'a':

                if (strcmp(optarg, "seq") == 0) search_algorithm = sequential_search;

                else if (strcmp(optarg, "cbc") == 0) search_algorithm = sequential_search_cbc;

                else if (strcmp(optarg, "kmp") == 0) search_algorithm = kmp_search;

                else if (strcmp(optarg, "bm") == 0) search_algorithm = boyer_moore_search;

                else if (strcmp(optarg, "bm+") == 0) search_algorithm = boyer_moore_plus;

                else 

                {

                    fprintf(stderr, "unknown algorithm: %s\n", optarg);

                    return EXIT_FAILURE;

                }

                break;

            case '1':

                replace_only_one = 1;

                break;

            case 'b':

                make_backup = 1;

                break;

            default:

                fprintf(stderr, "Usage: %s [-a algorithm] [-b] [-1] <filename> <original> <replacement>\n", argv[0]);

                return EXIT_FAILURE;

        }

    }



    // argument validation

    if (argc - optind != 3) 

    {

        fprintf(stderr, "Usage: %s [-a algorithm] [-b] [-1] <filename> <original> <replacement>\n", argv[0]);

        return EXIT_FAILURE;

    }

  //extract argument

    const char *filename = argv[optind];

    const char *original = argv[optind + 1];

    const char *replacement = argv[optind + 2];



    int result = replace_in_file(filename,original,replacement,search_algorithm,

                                    replace_only_one,make_backup);

    return result;

}
//seq: Sequential (brute-force) search
//cbc: Sequential search with character-by-character comparison
//kmp: Knuth-Morris-Pratt algorithm (efficient for patterns with repetition)
//bm: Boyer-Moore algorithm (efficient for longer patterns)
//bm+: Enhanced Boyer-Moore
