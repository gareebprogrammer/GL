#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include "types.h"

class Window {

private:
    GLFWwindow *m_window;
    i32 m_width,m_height;

public:
    bool create_window(i32 width,i32 height,const char *title);
    bool load_gl();

    inline void set_gl_framebuffer_size_callback(GLFWframebuffersizefun func) {
        glfwSetFramebufferSizeCallback(m_window, func);  
    }

    inline void make_context_current() {
        glfwMakeContextCurrent(m_window);
    }

    inline void get_window_size(i32 *width,i32 *height) {
        glfwGetWindowSize(m_window,&m_width,&m_height);
        *width = m_width;
        *height = m_height;
    }

    inline GLFWwindow *get_window_handle() {
        return m_window;
    }
    
    inline bool is_window_closed() {
        if(!glfwWindowShouldClose(m_window)) {
            return true;
        }else {
            return false;
        }
    }

    inline void swap_buffers() {
        glfwSwapBuffers(m_window);
    }

    inline  void wait() {
        glfwWaitEvents();
    }

    inline void poll() {
        glfwPollEvents();
    }

    inline void close_window() {
        glfwDestroyWindow(m_window);
    }
};

#endif