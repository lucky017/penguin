
#include "../Include/shell.h"

int sh_exit(char **args)
{
    if(args[1] != NULL){
        perror("Got a Syntax error. Maybe you want to execute \"exit\"\n");
        return 0;
    }
    return -1;
}
