#include "shader.h"
#include "window.h"
#include "texture.h"
#include <spdlog/spdlog.h>

static bool gl_poly_mode = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { 
        spdlog::info("closeing window you pressed ESC!");
        glfwSetWindowShouldClose(window, true);
    }else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        if(gl_poly_mode) {
            spdlog::info("gl draw mode GL_LINE");
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            gl_poly_mode = false;
        }else {
            spdlog::info("gl draw mode GL_FILL");
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            gl_poly_mode = true;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    glViewport(0, 0, width, height);
}

// float vertices[] = {
//     // first triangle
//      0.5f,  0.5f, 0.0f,  // top right
//      0.5f, -0.5f, 0.0f,  // bottom right
//     -0.5f,  0.5f, 0.0f,  // top left 
//     // second triangle
//      0.5f, -0.5f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f,  // bottom left
//     -0.5f,  0.5f, 0.0f   // top left
// }; 

float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top  
};

float vertices2 [] = {
        // second triangle  // colors
        0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left 
        0.9f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right
        0.45f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top 
    };

float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
};

// float vertices2[] = {
//     // positions         // colors
//      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
//     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
//      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
// };

unsigned int indices[] = {  // note that we start from 0!
     0, 1, 3,   // first triangle
     1, 2, 3    // second triangle
}; 

int main(int argc,const char **argv) {
  
    Window win;
    if(!win.create_window(800,800,"Learn GL")) {
        return 0xdead;
    }
    win.load_gl();
    win.set_gl_framebuffer_size_callback(framebuffer_size_callback);    
    win.set_key_callback(key_callback);
    

    const GLubyte *vendor = glGetString(GL_RENDERER);
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes); 
    spdlog::info("Maximum {} number of vertex attributes supported by {}",nrAttributes,vendor);

    Shader tex_shader;
    tex_shader.load_shader("shaders/tex_vert.glsl","shaders/tex_frag.glsl");
     
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    Texture tex;
    tex.load_texture("textures/container.jpg");
    

    while(win.is_window_closed()) {

        // rendering //

        glClear(GL_COLOR_BUFFER_BIT);

        tex.apply();
        tex_shader.apply();

        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // buffer swap //
        win.swap_buffers();

        // event polling //
        win.poll();
        
    }

    win.close_window();
    return 0;
}
