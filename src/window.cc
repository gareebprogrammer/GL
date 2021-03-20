#include <glad/glad.h>
#include "window.h"
#include <stdio.h>

bool Window::create_window(i32 width,i32 height,const char *title) {
    const u32 res = glfwInit();
    if(!res) {
        return false;
    }

    m_width = width;
    m_height = height;

    m_window = glfwCreateWindow(m_width,m_height,title,nullptr,nullptr);
    if(!m_window) {
        printf("Window creation failed\n");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);
    return true;
}

bool Window::load_gl() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {   
        printf("OpenGL loading failed(GLAD)\n");
        return false;
    }
    return true;
}