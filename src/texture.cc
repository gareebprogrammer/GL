#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <spdlog/spdlog.h>
#include <glad/glad.h>

bool Texture::push_jpeg_tex(const char *file_path) {
  TexInfo temp_info;
  glGenTextures(1, &temp_info.tex_ID);
  glBindTexture(GL_TEXTURE_2D, temp_info.tex_ID); 
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(file_path,&temp_info.tex_width,&temp_info.tex_height,&temp_info.tex_channels,0);
  if(data) {
   spdlog::info("Texture: {} is loaded with Width: {} and Height: {}",m_textures.size() + 1 ,temp_info.tex_width,temp_info.tex_width);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, temp_info.tex_width, temp_info.tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   glGenerateMipmap(GL_TEXTURE_2D);
   m_textures.push_back(temp_info);
  }else {
    spdlog::error("Failed to load texture : {}",file_path);
    return false;
  }
  stbi_image_free(data);
  return true;
}

bool Texture::push_png_tex(const char *file_path) {
  TexInfo temp_info;
  glGenTextures(1, &temp_info.tex_ID);
  glBindTexture(GL_TEXTURE_2D, temp_info.tex_ID); 
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(file_path,&temp_info.tex_width,&temp_info.tex_height,&temp_info.tex_channels,0);
  if(data) {
   spdlog::info("Texture: {} is loaded with Width: {} and Height: {}",m_textures.size() + 1,temp_info.tex_width,temp_info.tex_width);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, temp_info.tex_width, temp_info.tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   glGenerateMipmap(GL_TEXTURE_2D);
   m_textures.push_back(temp_info);
  }else {
    spdlog::error("Failed to load texture : {}",file_path);
    return false;
  }
  stbi_image_free(data);
  return true;
}

void Texture::apply() {
  for(i32 i=0;i<m_textures.size();i++){
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, Texture::get_id(i));
  }
}