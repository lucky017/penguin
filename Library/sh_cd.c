#include "../Include/getpath.h"


int sh_cd(char **args)
{
    struct Path *PATH = init();
    const char *path_buffer = args[1];
    PATH->get_new_path(PATH, path_buffer);
    PATH->print(PATH);
    log(chdir(PATH->posix_path));
    return 1;
}



