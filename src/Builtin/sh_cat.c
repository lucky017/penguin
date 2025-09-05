
#include "../../Include/getpath.h"
#include<sys/stat.h>

int sh_cat(char **args)
{
    const char *arg = args[1];
    log(arg == NULL);
    
    struct Path* path = constructor();    
    path->cstring_to_path(path, arg, getcwd__());
    
    struct stat buffer;
    log(stat(path->posix_path, &buffer) == -1);
    if(!S_ISREG(buffer.st_mode)){
        fprintf(stderr, "The argument is not a file. please check the argument\n");
        destructor(path); 
        return EXIT_FAILURE;
    }
    FILE* file = fopen(path->posix_path, "r");
    log(file == NULL);
    
    char ptr[128];
    while(fgets(ptr, 124, file))
        printf("%s", ptr);
    fclose(file);
    destructor(path);
    return EXIT_SUCCESS;
}
