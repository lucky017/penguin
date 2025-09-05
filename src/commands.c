
char* builtin_cmd[] = {
    "cd",
    "ls",
    "cat",
    "help",
    "exit"
};
char *defined_cmd[] = {
    "flush"
};

const unsigned long sh_num_of_builtins = (sizeof(builtin_cmd)/sizeof(char*));
const unsigned long num_of_defined_cmd = (sizeof(defined_cmd)/sizeof(char*));

char* command_details[] = {
    "cd (change directory) - change current working directory",
    "ls (list) - lists files and directories within the file system",
    "cat (concatenate) - used to read the contents of files",
    "help - To help with commands",
    "exit - exit the shell"
};
