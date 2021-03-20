#ifndef UTILS_H
#define UTILS_H

#include "types.h"

//returns size of file on success or -1 //
i32 get_file_size(const char *file_path);

//retuns nullptr on failure else buf filled with data //
char *load_file_into_ram(const char *file_path,i32 file_size);

// free file //
void free_buffer(char *file);

#endif