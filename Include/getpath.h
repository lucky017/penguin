
#ifndef GETPATH_H
#define GETPATH_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "shell.h"
#define log(x) if(x) { perror("Penguin"); };

#define MAX_BYTES 1024
#define _512_BYTES 512
#define _64_BYTES 64

struct Path
{
    void (*copy_path) (struct Path *, const char*);
    void (*insert_new_path) (struct Path *,const char*);
    void (*remove_path)  (struct Path *);
    void (*get_new_path) (struct Path *, const char *);
    void (*insert_home) (struct Path *, const char *);
    unsigned long(*path_size) (struct Path *);
    void (*print)   (struct Path *);

    char posix_path[MAX_BYTES];
};

struct Path* init();
int stringcompare(const char*, const char*);

char* getcwd__();
char* gethome__();
 
#endif
