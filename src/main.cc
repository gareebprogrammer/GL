#include "shader.h"
#include "window.h"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    glViewport(0, 0, width, height);
} 

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
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

    u32 VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 


    while(win.is_window_closed()) {

        // input //
        processInput(win.get_window_handle());

        // buffer swap //
        win.swap_buffers();
        
        // event polling //
        win.poll();

        // rendering //
        s.apply();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    win.close_window();
    return 0;
}