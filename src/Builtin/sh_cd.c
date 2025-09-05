
#define SH_CD
#include "../../Include/getpath.h"

int sh_cd(char **args)
{
    int result = 0;
    struct Path *PATH = constructor();
    const char *path_buffer = args[1];
    
    PATH->cstring_to_path(PATH, path_buffer, gethome__());
    PATH->print_path(PATH);
    
    if(chdir(PATH->posix_path))  result = 1;
    destructor(PATH);
    return result;
}


