#include "shader.h"
#include "window.h"
#include <spdlog/spdlog.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { 
        spdlog::info("closeing window you pressed ESC!");
        glfwSetWindowShouldClose(window, true);
    }else if (key == GLFW_KEY_L && action == GLFW_PRESS) { 
        spdlog::info("Toogle gl draw mode");
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }if (key == GLFW_KEY_F && action == GLFW_PRESS) { 
        spdlog::info("Toogle gl draw mode");
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
}


void framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    glViewport(0, 0, width, height);
} 

float vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 
    // second triangle
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
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

    Shader s;
    s.load_shader("shaders/vert.glsl","shaders/frag.glsl");

    u32 VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glfwSetKeyCallback(win.get_window_handle(),key_callback);

    while(win.is_window_closed()) {

        // rendering //
        glClear(GL_COLOR_BUFFER_BIT);
        s.apply();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // buffer swap //
        win.swap_buffers();

        // event polling //
        win.poll();
        
    }

    win.close_window();
    return 0;
}