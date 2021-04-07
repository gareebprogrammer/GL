#ifndef TEXTURE_H
#define TEXTURE_H

#include "types.h"
#include <vector>

struct TexInfo {
  u32 tex_ID;
  i32 tex_width;
  i32 tex_height;
  i32 tex_channels;  
};

class Texture {
 private:
  std::vector<TexInfo> m_textures;
 public :
  u32 get_id(size_t index) {
    return m_textures[index].tex_ID;
  }
  bool  push_jpeg_tex(const char *file_path);
  bool  push_png_tex(const char *file_path);
  void apply();
};

#endif
