#include "shader.h"
#include "utils.h"
#include <spdlog/spdlog.h>
#include <malloc.h>
#include <string>

void inline check_shader_compile_error(u32 shader,std::string type) {
    i32 success;
    char infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if(!success) {
            glGetShaderInfoLog(shader,1024,NULL,infoLog);
            spdlog::info("ERROR: {} shader compilation failed : {}\n",type.c_str(),infoLog);
        }
    }else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::info("ERROR: {} linking failed : {}\n", type.c_str(),infoLog);
        }
    }
}

bool Shader::load_shader(const char *vert_path,const char *frag_path) {
    char *vert_buf = nullptr;
    char *frag_buf = nullptr;

    i32 vert_size = get_file_size(vert_path);
    if(vert_size == -1) {
        return false;
    }
    i32 frag_size = get_file_size(frag_path);
    if(frag_size == -1) {
        return false;
    }

    vert_buf = load_file_into_ram(vert_path,vert_size);
    if(!vert_buf) { 
        return false;
    }
    frag_buf = load_file_into_ram(frag_path,frag_size);
    if(!frag_buf) {
        return false;
    }

    //load vertex shader //
    u32 vertex_shader , fragment_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vert_buf, NULL);
    glCompileShader(vertex_shader);
    check_shader_compile_error(vertex_shader, "VERTEX");

    // load fragment shader //
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_buf, NULL);
    glCompileShader(fragment_shader);
    check_shader_compile_error(fragment_shader, "FRAGMENT");

    // create program and attach shaders //
    m_shader_id = glCreateProgram();
    glAttachShader(m_shader_id, vertex_shader);
    glAttachShader(m_shader_id, fragment_shader);
    glLinkProgram(m_shader_id);
    check_shader_compile_error(m_shader_id, "PROGRAM");

    // delete shaders //
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // free buffers //
    free_buffer(vert_buf);
    free_buffer(frag_buf);
    
    return true;
}