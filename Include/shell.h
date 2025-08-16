
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#ifdef _WIN32
#define ENV_HOME "USERPROFILE"
#else
#define ENV_HOME "HOME"
#endif

#define STDIN_BUFFER_SIZE 1024
#define SH_SPLIT_LINE_BUFSIZE 64
#define SH_SPLIT_LINE_DELIMETER " \n\t\r\a"

void loop_shell(void);
char* sh_read_line(void);
char **sh_split_line(char* line);
int sh_execute(char** arguments);
int sh_launch(char **args);

int sh_cd(char** args);
int sh_help(char** args);
int sh_exit(char** args);
