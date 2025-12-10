//replace.c



#include "replace.h"

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <errno.h>

//a replacement function.

int replace_in_file(const char *filename,

                    const char *original,

                    const char *replacement,

                    search_func_t search_func,

                    int replace_only_one,

                    int make_backup)

{

    FILE *in = fopen(filename, "rb");

    if (!in) 

    {

        perror("fopen (input)");

        exit(EXIT_FAILURE);

    }



    // build temporary file name

    char tmpname[4096];

    snprintf(tmpname, sizeof(tmpname), "%s.tmp", filename);



    FILE *out = fopen(tmpname, "wb");

    if (!out) 

    {

        perror("fopen (output)");

        fclose(in);

        exit(EXIT_FAILURE);

    }



    if (make_backup) {

        char backup_name[4096];

        snprintf(backup_name, sizeof(backup_name), "%s.bak", filename);

        if (rename(filename, backup_name) != 0) {

            perror("error creating backup");

            exit(EXIT_FAILURE);

        }

    }



    // read file into memory (for simplicity)

    fseek(in, 0, SEEK_END);

    long size = ftell(in);

    rewind(in);



    if (size <= 0) 

    {

        //fprintf(stderr, "Error: file is empty or unreadable.\n");

        perror("file is empty or unreadable");

        fclose(in);

        fclose(out);

        remove(tmpname);

        exit(EXIT_FAILURE);

    }



    char *buffer = (char *)malloc(size);

    if (!buffer) 

    {

        perror("error on malloc()");

        fclose(in);

        fclose(out);

        remove(tmpname);

        exit(EXIT_FAILURE);

    }



    if (fread(buffer, 1, size, in) != (size_t)size) 

    {

        perror("error on fread()");

        free(buffer);

        fclose(in);

        fclose(out);

        remove(tmpname);

        exit(EXIT_FAILURE);

    }



    fclose(in);



    // replacement process

    char *pos = buffer;

    size_t remaining = size;

    size_t orig_len = strlen(original);

    size_t repl_len = strlen(replacement);

    

    int replaced = EXIT_FAILURE;

    

    while (1) 

    {

        char *match = search_func(pos, remaining, original, orig_len);

        if (!match)

            break;



        size_t prefix_len = match - pos;

        fwrite(pos, 1, prefix_len, out);

        fwrite(replacement, 1, repl_len, out);



        size_t consumed = prefix_len + orig_len;

        pos += consumed;

        remaining -= consumed;



        replaced = EXIT_SUCCESS;



        // only one replacement

        if (replace_only_one) 

            break;  // stop after first replacement

    }



    // write the rest of the file

    fwrite(pos, 1, remaining, out);



    free(buffer);

    fclose(out);



    // replace original file with new one

    if (replaced == EXIT_SUCCESS) 

    {

        if (remove(filename) != 0) 

        {

            perror("error on remove()");

            exit(EXIT_FAILURE);

        }

        if (rename(tmpname, filename) != 0) 

        {

            perror("error on rename()");

            exit(EXIT_FAILURE);

        }

        printf("...replacement successful.\n");

    } 

    else 

    {

        remove(tmpname);

        printf("...no occurrences of '%s' found.\n", original);

    }



    //return replaced ? 0 : 1;

    return replaced;

}
