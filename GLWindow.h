/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLWindow.h
 * Author: KnightDanila
 *
 * Created on 17 сентября 2019 г., 0:04
 */

#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <iostream>

namespace DFN {

    class GLWindow {
    public:
        GLWindow(const std::string& title, uint32_t width, uint32_t height, int pos_x, int pos_y);
        GLWindow(const std::string& title, uint32_t width, uint32_t height, GLFWwindow *share, int pos_x, int pos_y);


        ~GLWindow() {
            glfwDestroyWindow(_window);
        };
        uint32_t getWidth() const;
        uint32_t getHeight() const;

        GLFWwindow* getGLFWHandle();


        void on_resize(GLFWwindow *window, int width, int height);

    private:
        GLFWwindow *_window;

    };

    GLWindow::GLWindow(const std::string &title, uint32_t width, uint32_t height,int pos_x,int pos_y) {
        if (!glfwInit())
            throw std::runtime_error
                    {
                            "Unable to initialize glfw runtime"
                    };

        _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!_window)
            throw std::runtime_error
                    {
                            "Unable to initialize glfw window"
                    };

        glfwSetWindowPos(_window,
                         pos_x,
                         pos_y);

// (3).  Show the window
        glfwShowWindow(_window);


    }

    GLWindow::GLWindow(const std::string &title, uint32_t width, uint32_t height, GLFWwindow *share,int pos_x,int pos_y) {
        if (!glfwInit())
            throw std::runtime_error
                    {
                            "Unable to initialize glfw runtime"
                    };

        _window = glfwCreateWindow(width, height, title.c_str(), nullptr, share);
        if (!_window)
            throw std::runtime_error
                    {
                            "Unable to initialize glfw window"
                    };
        glfwDefaultWindowHints();

        glfwSetWindowPos(_window,
                         pos_x,
                         pos_y);

// (3).  Show the window
        glfwShowWindow(_window);
    }

    GLFWwindow *GLWindow::getGLFWHandle(){
        return this->_window;
    }

    void GLWindow::on_resize(GLFWwindow *window, int widthd, int heightd) {
        //By default rearranges OpenGL viewport to the current framebuffer size.
        glfwGetWindowSize(_window, &widthd, &heightd);

        glViewport(0, 0, widthd, heightd);

    }


}
#endif /* GLWINDOW_H */
