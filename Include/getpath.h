
#ifndef GETPATH_H
#define GETPATH_H

#include "shell.h"
#define log(x) if(x) { perror("Penguin"); };

#define MAX_BYTES 1024
#define _512_BYTES 512
#define _64_BYTES 64

struct Path
{
    void (*copy_path) (struct Path *, const char*);
    void (*cstring_to_path) (struct Path *, const char *, char* );
    unsigned long(*path_size) (struct Path *);
    void (*print_path)   (struct Path *);

    char posix_path[MAX_BYTES];
};

char* getcwd__();
char* gethome__();
struct Path* constructor();
int string_compare(const char*, const char*);

#endif
