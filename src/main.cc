#include "window.h"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main(int argc,const char **argv) {

    Window win;
    if(!win.create_window(800,800,"Learn GL")) {
        return 0xdead;
    }
    win.load_gl();
    win.set_gl_framebuffer_size_callback(framebuffer_size_callback);

    while(win.is_window_closed()) {

        // input //
        processInput(win.get_window_handle());

        // buffer swap //
        win.swap_buffers();
        
        // event polling //
        win.poll();

        // rendering //
        glClearColor(0.3f, 0.2f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    win.close_window();
    return 0;
}