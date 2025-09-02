
#include "../Include/getpath.h"

typedef struct Path path;
void copy_path(path *, const char*);
void print_path(path *);
unsigned long path_size(path *);
void string_to_path(path *, const char *, char *);


void remove_path(path *);
void insert_new_path(path *,const char*);
static inline int get_dir_length(const char **src_path);
static inline char* get_dir_name(const char* src_path, int length);
static inline void final_path(path *p, const char *src_path);

path* constructor()
{
    struct Path* self = (path*)malloc(sizeof(path));
    self->copy_path = copy_path;
    self->print_path = print_path;
    self->path_size = path_size;
    self->cstring_to_path = string_to_path;
    return self;
}

void copy_path(path *p, const char *src_path)
{
    snprintf(p->posix_path, MAX_BYTES, "%s", src_path);
}

void string_to_path(path *p, const char *src_path, char *DEFAULT_PATH)
{
    char *cwd = getcwd__();
    char *home = gethome__();
    
    if(src_path == NULL){
        p->copy_path(p, DEFAULT_PATH);
        return;
    }

    if(src_path[0] == '/')
        p->posix_path[0] = '/';
    else if(src_path[0] == '~' && src_path[1] == '/'){
        p->copy_path(p, home);
        ++src_path;
    }
    else
        p->copy_path(p, cwd); 
    
    final_path(p, src_path);
    free(cwd);
}

void print_path(path *p)
{
    printf("PATH = %s\n", p->posix_path);
    fflush(stdout);
}

unsigned long path_size(path *p)
{
    return strlen(p->posix_path);
}

int string_compare(const char* a, const char* b) {
    if (a == NULL || b == NULL)
        return 0;
    fflush(stdout);
    
    while (*a != '\0' && *b != '\0') {
        if (*a != *b) return 0;
        ++a;
        ++b;
    }
    
    if (*a == '\0' && *b == '\0')
        return 1;
    return 0;
}



char* getcwd__()
{
    //free the memory
    char *ptr =  getcwd(NULL, 0);
    log(ptr == NULL);
    return ptr;
}

char* gethome__()
{
    char* ptr = getenv(ENV_HOME);
    log(ptr == NULL);
    return ptr;
}

void insert_new_path(path *p, const char *dir)
{
    char *ptr = p->posix_path + p->path_size(p);
    
    if(*(ptr-1) != '/') *ptr++ = '/';
    strncpy(ptr, dir, strlen(dir));
    if(*(ptr-1) != '/') *ptr++ = '/';
    
    *(ptr + strlen(dir)) = '\0';
}

void remove_path(path *p)
{
    char *ptr = p->posix_path;
    char *dir = ptr + p->path_size(p)-1;
    
    while (dir > ptr && *dir == '/') --dir;
    while (dir > ptr && *dir != '/') --dir;
    *(dir + 1) = '\0';
}

static inline int get_dir_length(const char **src_path)
{
    const char *ptr = *src_path;
    if(*ptr == '\0') return -1;
    int i = 0;

    while (*ptr == '/') ++ptr;
    const char* temp = ptr;
    while (*temp != '/' && *temp != '\0'){
        ++i; ++temp;
    }
    *src_path = ptr;
    return i;
}

static inline char* get_dir_name(const char* src_path, int length)
{
    char* temp_dir = (char*)malloc(length+1);
    log(!temp_dir);
    
    strncpy(temp_dir, src_path, length);
    temp_dir[length] = '\0';
    return temp_dir;
}

static inline void final_path(path *p, const char *src_path)
{
    while (*src_path != '\0') {
        int length = get_dir_length(&src_path);
       
        log(length == -1);
        if(length == 0) break;
        char *local_dir = get_dir_name(src_path, length);
        src_path = src_path + length;
        
        if (string_compare(local_dir, ".")) continue;
        else if (string_compare(local_dir, ".."))
            remove_path(p);
        else insert_new_path(p, local_dir);
        free(local_dir);
    }
}



