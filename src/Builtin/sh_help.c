
#include "../../Include/shell.h"

extern int sh_num_of_builtins;
extern char* builtin_cmd[];
extern char* command_details[];


int sh_help(char **args)
{
    if(args[1] != NULL){
        perror("The Arguments to this command is NULL. Type and execute with no arguments \
                \n\tlike \"help\"\n");
        return 1;
    }
    fputs("\nThe Built-in Commands for the penguin are: \n", stdout);
    for(int i=0; i<sh_num_of_builtins; ++i){
        printf("%s\n", command_details[i]);
    }
    return 1;
}
