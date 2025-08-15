
#include "shell.h"

int sh_cd(char **args)
{
    char path[1024], cwd[1024], *home;
    home = (char*)HOME_DIR();
    if(getcwd(cwd,sizeof(cwd)) == NULL){
        perror("Penguin");
    }
    if(!home){
        fprintf(stderr, "Home directory not set to Environment($PATH)\n");
        return 0;
    }
    if(args[1]){
        const char c = args[1][0];
        char buffer[512];
        if(c == '/'){
            strcpy(buffer, args[1]);
            printf("%s\n", buffer);
        }
    }
    printf("%s\n", path);
    //if(chdir(path) != 0) perror("Penguin");
    return 1;
}



