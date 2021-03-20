#include "utils.h"

#if __linux__
#include <sys/stat.h>

i32 get_file_size(const char *file_path) {
    struct stat file_stat;
    if(stat(file_path,&file_stat) != 0) {
        return -1;
    }else {
        return file_stat.st_size;
    }
}

#endif

#if _WIN32 
    #error Unimplemented
#endif

#include <stdio.h>
#include <malloc.h>

char *load_file_into_ram(const char *file_path,i32 file_size) { 
    if(file_size == -1) {
        printf("Cannot get file size: %s\n", file_path);
        return nullptr;
    }   
    FILE *file = fopen(file_path,"rb");
    if(!file) {
        printf("File loading failed : %s\n", file_path);
        return nullptr;
    }

    char *file_buf = (char *)malloc(file_size * sizeof(char)); 
    if(!file_buf) {
        printf("File allocation failed %s\n",file_path);
        return nullptr;
    }
    i32 read_count = fread(file_buf,file_size,1,file);
    if(read_count != 1) {
        printf("File reading failed %s\n", file_path);
        free(file_buf);
        return nullptr;
    }
    fclose(file);
    file_buf[file_size] = '\0';
    return file_buf;
}

void free_buffer(char *file) {
    free(file);
}