#include "shader.h"
#include "window.h"
#include <spdlog/spdlog.h>
#include <math.h>

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
        // second triangle
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };

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

    Shader s1;
    Shader s2;
    s1.load_shader("shaders/vertv1.glsl","shaders/fragv1.glsl");
    s2.load_shader("shaders/vertv2.glsl","shaders/fragv2.glsl");

    u32 VBO[2], VAO[2],EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    
    while(win.is_window_closed()) {

        // rendering //
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        glClear(GL_COLOR_BUFFER_BIT);

        s1.apply();
        s1.set_uniform_4f("ourColor",0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        s2.apply();
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // buffer swap //
        win.swap_buffers();

        // event polling //
        win.poll();
        
    }

    win.close_window();
    return 0;
}