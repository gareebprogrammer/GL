#ifndef TEXTURE_H
#define TEXTURE_H

#include "types.h"

class Texture {
 private:
  u32 m_tex_ID;
  i32 m_tex_width;
  i32 m_tex_height;
  i32 m_tex_channels;
 public :
  bool load_texture(const char *file_path);
  void apply();
};

#endif
