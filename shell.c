
#include "shell.h"

const char* HOME_DIR(){
    return getenv(ENV_HOME);
}

char* builtin_cmd[] = {
    "cd",
    "help",
    "exit"
};

const size_t sh_num_of_builtins = (sizeof(builtin_cmd)/sizeof(char*));
int (*builtin_func[]) (char **) = {
    &sh_cd,
    &sh_help,
    &sh_exit
};

int sh_cd(char **args)
{
    char path[1024];
    if(args[1] == NULL || args[1][0] == '~'){
        char* home = (char*)HOME_DIR();
        if(!home){
            fprintf(stderr, "Home directory not set to ENVIRONMENT\n");
            return 0;
        }
        if(args[1] == NULL || args[1][1] == '\0'){
            strncpy(path, home, sizeof(path));
        } else{
            snprintf(path, sizeof(path), "%s%s", home, args[1]+1);
        }
        if(chdir(path) != 0) perror("Penguin");
    } else{
        if(chdir(args[1]) != 0) perror("Penguin");
    }
    return 1;
}

int sh_help(char **args)
{
    printf("Lucky - The Author of Shell Penguin\n");
    printf("Type the command need to execute with it's specified arguments and hit Enter\n");
    printf("The following are builtin commands: \n");

    for(int i = 0; i < sh_num_of_builtins; i++){
        printf(" %s\n", builtin_cmd[i]);
    }

    //printf("Use the man command for information on other programs\n");
    return 1;
}

int sh_exit(char **args){
    return -1;
}

int sh_execute(char **args)
{
    if(args[0] == NULL){
        return 0;
    }
    for(int i = 0; i < sh_num_of_builtins; i++){
        if(strcmp(args[0], builtin_cmd[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    return sh_launch(args);
}

void loop_shell(void)
{
    char* line;
    char** args;
    int status;
    do{
        printf("[Penguin@] ");
        line = sh_read_line();
        args = sh_split_line(line);
        status = sh_execute(args);

        free(line);
        free(args);
        if(status == -1) exit(0);
    } while(true);
}

char* sh_read_line(void)
{
    unsigned int buffer_size = STDIN_BUFFER_SIZE;
    int position = 0;
    int c = 0;
    
    char* buffer = malloc(buffer_size * sizeof(char));
    if(!buffer){
        fprintf(stderr, "Penguin: Error Creating Buffer\n");
        exit(EXIT_FAILURE);
    }
    while(true){
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            break;
        } else{
            buffer[position] = c;
        }
        position++;
        
        if(position >= buffer_size){
            buffer_size += (STDIN_BUFFER_SIZE >> 1);
            buffer = realloc(buffer, buffer_size);
            if(!buffer){
                fprintf(stderr, "Error: Problem allocating more buffer...\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return buffer;
}

char** sh_split_line(char* line)
{
    int buffer_size = SH_SPLIT_LINE_BUFSIZE, position = 0;
    char** token_buffer = malloc(buffer_size * sizeof(char*));
    char* token;

    if(!token_buffer){
        fprintf(stderr, "Penguin: Error Splitting line\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, SH_SPLIT_LINE_DELIMETER);
    while(token != NULL){
        token_buffer[position] = token;
        position++;
        if(position >= buffer_size){
            buffer_size += SH_SPLIT_LINE_BUFSIZE >>1;
            token_buffer = realloc(token_buffer, buffer_size * sizeof(char*));
            if(!token_buffer){
                fprintf(stdin, "Penguin: Error realloc the token_buffer.\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, SH_SPLIT_LINE_DELIMETER);
    }
    token_buffer[position] = NULL;
    return token_buffer;
}

int sh_launch(char **args)
{
    pid_t pid, wpid;
    int status = 0;

    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) == -1)
            perror("Error Child Process\n");
        exit(EXIT_FAILURE);
    } else if(pid < 0){
        perror("Error Process id is less than zero\n");
    } else{
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}



