
#ifndef GETPATH_H
#define GETPATH_H

#include "shell.h"
#define log(x) if(x) { perror("Penguin"); };

#define MAX_BYTES 1024
#define _512_BYTES 512
#define _64_BYTES 64

struct Path
{
    void (*copy_path) (struct Path *obj, const char *src);
    void (*cstring_to_path) (struct Path *obj, const char *arg, char *def_path);
    unsigned long(*path_size) (struct Path *obj);
    void (*print_path)   (struct Path *obj);

    char posix_path[MAX_BYTES];
};

char* getcwd__();
char* gethome__();
struct Path* constructor();
void destructor(struct Path *obj);
int string_compare(const char *path1, const char *path2);

#endif
