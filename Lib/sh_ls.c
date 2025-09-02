
#include "../Include/getpath.h"
#include<dirent.h>

char** listdir(char *dir)
{
    struct dirent *obj;
    DIR *open_dir = opendir(dir);
    if(open_dir == NULL)
    {
        perror("Unknown Directory. Check the arguments again.\n");
        return NULL;
    }
    if(dir != NULL)
    {
        unsigned short max_size = 64;
        char **list = malloc(max_size * sizeof(char*)); 
        unsigned int i = 0;

        while((obj = readdir(open_dir)) != NULL)
        {
            char* str = malloc(strlen(obj->d_name) + 1);
            strcpy(str, obj->d_name);
            if(i >= max_size){
                max_size *= 2;
                list = realloc(list, max_size * sizeof(char*));
            }
            list[i++] = str;
        }
        list[i] = NULL;
        return list;
    }
    perror("Couldn't list the Directory. Check the Directory privilages.\n");
    return NULL;
}

size_t getsize(char** list)
{
    size_t size = 0;
    while(list != NULL) ++size;
    return size;
}

void freedir(char **list)
{
    if(list == NULL) return;
    for(int i=0; list[i] != NULL; ++i)
    {
        free(list[i]);
    }
    free(list);
}

void print(char **list)
{
    if(list == NULL) return;
    for(int i=0; list[i] != NULL; ++i)
    {
        printf("%s  ", list[i]);
    }
    putc('\n', stdout);
    fflush(stdout);
}

int sh_ls(char **args)
{
    struct Path *path = constructor();
    const char* path_buffer = args[1];

    path->cstring_to_path(path, path_buffer, getcwd__());
    char **list = listdir(path->posix_path);
    print(list);
    free(list);
    return 0;
}


