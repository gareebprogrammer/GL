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
#include <windows.h>

i32 get_file_size(const char *file_path) {
  WIN32_FILE_ATTRIBUTE_DATA    fileInfo;
  if(GetFileAttributesEx(file_path, GetFileExInfoStandard, &fileInfo))
    {
      i32 nSize = (i32)fileInfo.nFileSizeLow;
        return nSize;
    }else {
       return -1;
    } 
}
#endif

#include<spdlog/spdlog.h>
#include <malloc.h>

char *load_file_into_ram(const char *file_path,i32 file_size) { 
    if(file_size == -1) {
        spdlog::error("Cannot get file size: {}", file_path);
        return nullptr;
    }   
    FILE *file = fopen(file_path,"rb");
    if(!file) {
        spdlog::error("File loading failed : {}", file_path);
        return nullptr;
    }

    char *file_buf = (char *)malloc(file_size+1 * sizeof(char)); 
    if(!file_buf) {
        spdlog::error("File allocation failed : {}",file_path);
        return nullptr;
    }
    size_t read_count = fread(file_buf,file_size,1,file);
    if(read_count != 1) {
      spdlog::error("File reading failed : {}", file_path);
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
