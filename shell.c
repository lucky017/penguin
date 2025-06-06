
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define STDIN_BUFFER_SIZE 1024
#define SH_SPLIT_LINE_BUFSIZE 64
#define SH_SPLIT_LINE_DELIMETER " \n\t\r\a"


void loop_shell(void);
char* sh_read_line(void);
char **sh_split_line(char* line);
int sh_execute(char** arguments);
int sh_launch(char **args);

// function declarations
int sh_cd(char** args);
int sh_help(char** args);
int sh_exit(char** args);

/*
 * Builtin commands
*/
char* builtin_cmd[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &sh_cd,
    &sh_help,
    &sh_exit
};

int sh_num_of_builtins()
{

    return sizeof(builtin_cmd) / sizeof(char*);
}

int main(int argc, char** argv)
{
    //loop until the end
    loop_shell();

    return EXIT_SUCCESS;
}

int sh_cd(char **args)
{
    if(args[1] == NULL){
        fprintf(stderr, "Penguin: no command found\nExpected command is \"cd\"\n");
    } else{
        if(chdir(args[1]) != 0){
            perror("Penguin");
        }
    }
    return 1;
}

int sh_help(char **args)
{
    printf("Lucky - The Author of Shell Penguin\n");
    printf("Type the command need to execute with it's specified arguments and hit Enter\n");
    printf("The following are builtin commands: \n");

    for(int i = 0; i < sh_num_of_builtins(); i++){
        printf(" --%s\n", builtin_cmd[i]);
    }

    printf("Use the man command for information on other programs\n");
    return 1;
}

int sh_exit(char **args){
    return 0;
}

int sh_execute(char **args)
{
    if(args[0] == NULL){
        return 0;
    }
    for(int i = 0; i < sh_num_of_builtins(); i++){
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
    } while(status);
}

// read the lines from the stdin buffer and return the buffer until End of File(EOF)
//
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
    while(1){
        c = getchar();

        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        } else{
            buffer[position] = c;
        }
        position++;
        
        if(position >= buffer_size){
            buffer_size += STDIN_BUFFER_SIZE >> 2;
            buffer = realloc(buffer, buffer_size);
            if(!buffer){
                fprintf(stderr, "Penguin: Buffer Exceeded!!\nCan't Allocate More Buffer\n");
                exit(EXIT_FAILURE);
            }
        }        
    }
}

// Split the token(each word) as command and arguments using the return function of sh_read_line
// 
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
            buffer_size += SH_SPLIT_LINE_BUFSIZE >>2;
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



