#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <spdlog/spdlog.h>
#include <glad/glad.h>

bool Texture::load_texture(const char *file_path) {
  glGenTextures(1, &m_tex_ID);
  glBindTexture(GL_TEXTURE_2D, m_tex_ID); 
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unsigned char *data = stbi_load(file_path,&m_tex_width,&m_tex_height,&m_tex_channels,0);
  if(data) {
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_tex_width, m_tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   glGenerateMipmap(GL_TEXTURE_2D);
  }else {
    spdlog::error("Failed to load texture : {}",file_path);
    return false;
  }
  stbi_image_free(data);
  return true;
}

void Texture::apply() {
  glBindTexture(GL_TEXTURE_2D,m_tex_ID);
}
