#ifndef SHADER_H
#define SHADER_H

#include "types.h"
#include <glad/glad.h>

class Shader {

private:
    u32 m_shader_id;
public:

    bool load_shader(const char *vert_path,const char *frag_path);

    inline void apply() {
        glUseProgram(m_shader_id);
    }

    inline u32 get_id() {
        return m_shader_id;
    }

    void set_uniform_1f(const char *location,GLfloat v0);
    void set_uniform_2f(const char *location,GLfloat v0,GLfloat v1);
    void set_uniform_3f(const char *location,GLfloat v0,GLfloat v1,GLfloat v2);
    void set_uniform_4f(const char *location,GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3);

};

#endif