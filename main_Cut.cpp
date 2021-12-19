
#include <iostream>
#include <cstdlib>

#include <cmath>
#include <GL/glew.h>

#include <string>

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_access.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

template<typename T>
void println(T i) {
    cout << i << endl;
}

string operator+(const string &s, int i) {
    return s + to_string(i);
}

namespace Globals {

    float colorRGB = 0.0;
    int width, height;
    float angle = 0;
    bool rotation = true;

    namespace Cube {
        GLfloat vertices[] = {
                .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, .5f, -.5f, .5f,   // v0,v1,v2,v3 (front)
                .5f, .5f, .5f, .5f, -.5f, .5f, .5f, -.5f, -.5f, .5f, .5f, -.5f,   // v0,v3,v4,v5 (right)
                .5f, .5f, .5f, .5f, .5f, -.5f, -.5f, .5f, -.5f, -.5f, .5f, .5f,   // v0,v5,v6,v1 (top)
                -.5f, .5f, .5f, -.5f, .5f, -.5f, -.5f, -.5f, -.5f, -.5f, -.5f, .5f,   // v1,v6,v7,v2 (left)
                -.5f, -.5f, -.5f, .5f, -.5f, -.5f, .5f, -.5f, .5f, -.5f, -.5f, .5f,   // v7,v4,v3,v2 (bottom)
                .5f, -.5f, -.5f, -.5f, -.5f, -.5f, -.5f, .5f, -.5f, .5f, .5f, -.5f    // v4,v7,v6,v5 (back)
        };
        GLfloat normals[] = {
                0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // v0,v1,v2,v3 (front)
                1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // v0,v3,v4,v5 (right)
                0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // v0,v5,v6,v1 (top)
                -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0,  // v1,v6,v7,v2 (left)
                0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0,  // v7,v4,v3,v2 (bottom)
                0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1   // v4,v7,v6,v5 (back)
        };

// color array
        GLfloat colors[] = {
                1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1,  // v0,v1,v2,v3 (front)
                1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1,  // v0,v3,v4,v5 (right)
                1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0,  // v0,v5,v6,v1 (top)
                1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,  // v1,v6,v7,v2 (left)
                0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,  // v7,v4,v3,v2 (bottom)
                0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1   // v4,v7,v6,v5 (back)
        };

// index array for glDrawElements() ===========================================
// A cube has 36 indices = 6 sides * 2 tris * 3 verts
        GLuint indices[] = {
                0, 1, 2, 2, 3, 0,    // v0-v1-v2, v2-v3-v0 (front)
                4, 5, 6, 6, 7, 4,    // v0-v3-v4, v4-v5-v0 (right)
                8, 9, 10, 10, 11, 8,    // v0-v5-v6, v6-v1-v0 (top)
                12, 13, 14, 14, 15, 12,    // v1-v6-v7, v7-v2-v1 (left)
                16, 17, 18, 18, 19, 16,    // v7-v4-v3, v3-v2-v7 (bottom)
                20, 21, 22, 22, 23, 20     // v4-v7-v6, v6-v5-v4 (back)
        };

        unsigned int VBO = 0;
        unsigned int VAO;

//        Shader ourShader;

    };

    namespace Triangle2D {
        int N = 3 * 3 * 3;

        GLfloat vertices[] = {
                0, 0, 0,
                1, 0, 0,
                1, 1, 0,

                0, 0, 0,
                0, 1, 0,
                -1, 1, 0,

                0, 0, 0,
                0, -1, 0,
                1, -1, 0,
        };

        GLfloat colors[] = {

                255, 0, 0,
                0, 255, 0,
                255, 0, 0,

                255, 0, 255,
                0, 100, 70,
                0, 0, 0,

                255, 255, 0,
                0, 100, 70,
                0, 0, 0,
        };
    }


    namespace Quad2D {
        int N = 3 * 3 * 3;

        GLfloat vertices[] = {
                0, 0, 0,
                1, 0, 0,
                1, 1, 0,
                0, 1, 0,

                0, 0, 0,
                0, 1, 0,
                -1, 1, 0,
                -1, 0, 0
        };

        GLfloat colors[] = {
                255, 0, 0,
                0, 255, 0,
                255, 0, 0,
                255, 255, 0,

                255, 0, 255,
                0, 100, 70,
                0, 0, 0,
                0, 0, 255
        };
    }
    namespace MyCube {
        GLfloat vertices[] =
                {
                        -1, -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1,
                        1, -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1,
                        -1, -1, -1, -1, -1, 1, 1, -1, 1, 1, -1, -1,
                        -1, 1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1,
                        -1, -1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1,
                        -1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1
                };

        GLfloat colors[] =
                {
                        0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
                        1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0,
                        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,
                        0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
                        0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0,
                        0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1
                };
    }

}


using namespace Globals;

#include "GLWindow.h"
#include "GLRenderSystem.h"


#include "Camera.h"

void resize(GLFWwindow *window, int width, int height) {
//    println((string) "Width:" + width + "-Height:" + height);

    float ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
    // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    translation[3][0] = -position.x; // Third column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    println((string) "key:" + key + "-scancode:" + scancode + "-action:" + action + "-mode:" + mode);

    //Knight3D::GLWindow* win = static_cast<Knight3D::GLWindow*> (glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
//        println("SPACE");
        rotation ? rotation = false : rotation = true;
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        //win->fullScreenSwitch();
    }
};

int main(int argc, char **argv) {

    bool FULL_SCREEN = false;
    bool OpenGL33 = false;

    DFN::GraphCore::GLRenderSystem *renderer;

    if (OpenGL33) {
        renderer = new DFN::GraphCore::GLRender();
    } else {
        renderer = new DFN::GraphCore::GLRendererOld2_1();
    }


    renderer->init();


    auto *Win1 = new DFN::GLWindow("Lesson 021", 320, 240, 0, 0);
    auto *Win2 = new DFN::GLWindow("Lesson 022", 320, 240, Win1->getGLFWHandle(), 0, 340);
    auto *Win3 = new DFN::GLWindow("Lesson 023", 320, 240, Win1->getGLFWHandle(), 350, 0);
//    auto *Win4 = new DFN::GLWindow("Lesson 024", 300, 300, Win1->getGLFWHandle(), 350, 340);




    /* Loop until the user closes the window */

    DFN::GraphCore::Camera *CamFree = new DFN::GraphCore::GLCameraFree();

    glfwMakeContextCurrent(Win1->getGLFWHandle());
    CamFree->setPerspective(glm::radians(45.0f), float(840 / 680), 0.01f, 1000.0f);
    glfwMakeContextCurrent(Win2->getGLFWHandle());
    CamFree->setPerspective(glm::radians(45.0f), float(840 / 680), 0.01f, 1000.0f);
//    glfwMakeContextCurrent(Win3->getGLFWHandle());
//    CamFree->setPerspective(glm::radians(90.0f), float(840 / 680), 0.01f, 1000.0f);

    glfwSetInputMode(Win1->getGLFWHandle(), GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetFramebufferSizeCallback(Win1->getGLFWHandle(), resize);
    glfwSetKeyCallback(Win1->getGLFWHandle(), keyCallback);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(Win1->getGLFWHandle(), resize);



    // Инициализируем GLEW
    glewExperimental = true; // Флаг необходим в Core-режиме OpenGL
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Невозможно инициализировать GLEW\n");
        return -1;
    }


    while (glfwGetKey(Win1->getGLFWHandle(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(Win1->getGLFWHandle()) == 0) {

        glfwMakeContextCurrent(Win1->getGLFWHandle());

        CamFree->setPos(glm::vec3(10 * cos(angle * PI / 180), 2 * sin(angle * PI / 180), 2 * cos(PI / 180)));

        CamFree->start();

        renderer->render(Win1->getGLFWHandle());
        CamFree->end();
        // Сбрасываем буферы
//        glUseProgram(0);
        glfwSwapBuffers(Win1->getGLFWHandle());

        /**/
        glfwMakeContextCurrent(Win2->getGLFWHandle());
        CamFree->setPos(glm::vec3(2 * tan(cos(angle * PI / 180)),   3*cos( PI / 180),  cos(PI / 180)));
        CamFree->start();
        renderer->renderTriangleArray(Triangle2D::vertices, Triangle2D::colors, Triangle2D::N);
        CamFree->end();

        // Сбрасываем буферы
        glfwSwapBuffers(Win2->getGLFWHandle());


        glfwMakeContextCurrent(Win3->getGLFWHandle());

        renderer->renderQuadArray(Quad2D::vertices, Quad2D::colors);
        // Сбрасываем буферы
        glfwSwapBuffers(Win3->getGLFWHandle());

        /**/
        // Сообщения
        println((string) "Time: " + glfwGetTime());
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &Cube::VAO);
    glDeleteBuffers(1, &Cube::VBO);

    glfwDestroyWindow(Win1->getGLFWHandle());
    glfwDestroyWindow(Win2->getGLFWHandle());
    glfwDestroyWindow(Win3->getGLFWHandle());
//    glfwDestroyWindow(Win4->getGLFWHandle());
    glfwTerminate();


    return 0;
}