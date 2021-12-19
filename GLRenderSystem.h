/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLRenderSystem.h
 * Author: KnightDanila
 *
 * Created on 17 сентября 2019 г., 7:11
 */

#ifndef GLRENDERSYSTEM_H
#define GLRENDERSYSTEM_H

#include "Camera.h"

const double PI = 3.14;

namespace DFN {
    namespace GraphCore {

        class GLRenderSystem {
        public:
            float colorRGB = 0.0;

            virtual void init() {
                if (!glfwInit()) {
                    fprintf(stderr, "Ошибка при инициализации GLFW\n");
                }
            }

            virtual void render(GLFWwindow *window) {
            }


            virtual void renderTriangleArray(GLfloat vertices[], GLfloat colors[], int n) {
            }

            virtual void renderQuadArray(GLfloat vertices[], GLfloat colors[]) {
            }

            virtual void renderVBO() {
            }
        };

        class GLRender : public GLRenderSystem {


        public:
            void renderTriangleArray(GLfloat vertices[], GLfloat colors[], int n) override {
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)),
                             abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }


                glLoadIdentity();
                if(rotation) {
                    angle=(float) glfwGetTime() * 50.f;
                }
                glRotatef(angle, 0.f, 1.f, 1.f);

                glBegin(GL_TRIANGLES);
                if (n % 3 == 0) {
                    for (int i = 0; i <= n; i += 3) {
                        glColor3f(colors[i], colors[i + 1], colors[i + 2]);
                        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
                    }
                } else {
                    fprintf(stderr, "Triangle error");
                    return;

                }
                glEnd();
            }

            void renderQuadArray(GLfloat vertices[], GLfloat colors[]) override{
                glClearColor(225 / 256.0f, 150 / 256.0f, 176 / 256.0f, 1);
                glClear(GL_COLOR_BUFFER_BIT);


                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);

                glVertexPointer(3, GL_FLOAT, 0, vertices);
                glColorPointer(3, GL_FLOAT, 0, colors);

                glDrawArrays(GL_QUADS, 0, 8);


                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);
            }

            GLRender *renderCube(GLFWwindow *window, GLfloat vertices[], GLfloat colors[]) {
                glClearColor(0.0, 0.8, 0.3, 1.0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glMatrixMode(GL_PROJECTION_MATRIX);
                glLoadIdentity();
                gluPerspective(45, 1.2, 1.1f, 200.0f);

                glMatrixMode(GL_MODELVIEW_MATRIX);
                glTranslatef(0, 0, -5);

                static float alpha = 0;
                //attempt to rotate cube
                glRotatef(alpha, -2, 1, 3);

                /* We have a color array and a vertex array */
                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);
                glColorPointer(3, GL_FLOAT, 0, colors);

                /* Send data : 24 vertices */
                glDrawArrays(GL_QUADS, 0, 24);

                /* Cleanup states */
                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);
                alpha += 2;
                glfwSwapBuffers(window);

                // Check for any input, or window movement
                glfwPollEvents();
                return this;
            }

            void render(GLFWwindow *window) override {
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)),
                             abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }


                glEnable(GL_DEPTH_TEST);

                glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode

                glPushMatrix(); // push the matrix
                if(rotation) {
                    angle = glfwGetTime() * 50.0f;
                }
//                glRotatef(angle, 1.0, 1.0, 0.0); //apply transformation

//                glColor3f(1.f, 1.f, 0.f);

                //Указание отобразить нарисованное немедленно
                glFlush();


                //Создание нового VBO и сохранение идентификатора VBO
                glGenBuffers(1, &Cube::VBO);

                //Установка активности VBO
                glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);



                std::cout << sizeof(Cube::vertices) << std::endl;


                //Сделать новую VBO активным. Повторите это, в случае изменения с инициализации
                glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vertices), Cube::vertices, GL_STATIC_DRAW);
                glVertexPointer(3, GL_FLOAT, 0, NULL);
                glColorPointer(3, GL_FLOAT, 0, 0);


                //VAO
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
                glEnableVertexAttribArray(0);

                glEnableClientState(GL_VERTEX_ARRAY);


                glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof (Cube::vertices) / sizeof (Cube::vertices[0] / 5));
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,  sizeof(Cube::vertices), (void*)(3*sizeof(float)));


                glPopMatrix(); //pop the matrix



                glDisableClientState(GL_VERTEX_ARRAY);

            }
        };

        class GLRendererOld2_1 : public GLRenderSystem {
        public:
            void init() override {
                if (!glfwInit()) {
                    fprintf(stderr, "Ошибка при инициализации GLFW\n");
                }
                glfwWindowHint(GLFW_SAMPLES, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

            }

            void render(GLFWwindow *window) override {
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)),
                             abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }


                glEnable(GL_DEPTH_TEST);

                glMatrixMode(GL_MODELVIEW); //set the matrix to model view mode

                glPushMatrix(); // push the matrix
                if(rotation) {
                    angle = glfwGetTime() * 50.0f;
                }
                glRotatef(angle, 1.0, 1.0, 0.0); //apply transformation

//                glColor3f(1.f, 1.f, 0.f);

                //Указание отобразить нарисованное немедленно
                glFlush();


                //Создание нового VBO и сохранение идентификатора VBO
                glGenBuffers(1, &Cube::VBO);

                //Установка активности VBO
                glBindBuffer(GL_ARRAY_BUFFER, Cube::VBO);



                std::cout << sizeof(Cube::vertices) << std::endl;


                //Сделать новую VBO активным. Повторите это, в случае изменения с инициализации
                glBufferData(GL_ARRAY_BUFFER, sizeof(Cube::vertices), Cube::vertices, GL_STATIC_DRAW);
                glVertexPointer(3, GL_FLOAT, 0, NULL);
                glColorPointer(3, GL_FLOAT, 0, 0);


                //VAO
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
                glEnableVertexAttribArray(0);

                glEnableClientState(GL_VERTEX_ARRAY);


                glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof (Cube::vertices) / sizeof (Cube::vertices[0] / 5));
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,  sizeof(Cube::vertices), (void*)(3*sizeof(float)));


                glPopMatrix(); //pop the matrix



                glDisableClientState(GL_VERTEX_ARRAY);

            }

            void renderTriangleArray(GLfloat vertices[], GLfloat colors[], int n) override {
                glClearColor(sin(colorRGB * PI / 180), abs(cos(colorRGB * PI / 180)),
                             abs(sin(colorRGB * PI / 180) + cos(colorRGB * PI / 180)), 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                {
                    colorRGB <= 180 ? colorRGB += 0.1 : colorRGB = 0;
                }

//                glLoadIdentity();
                if(rotation) {
                    angle=(float) glfwGetTime() * 50.f;
                }
                glRotatef(angle, 0.f, 1.f, 1.f);

                glBegin(GL_TRIANGLES);
                if (n % 3 == 0) {
                    for (int i = 0; i <= n; i += 3) {
                        glColor3f(colors[i], colors[i + 1], colors[i + 2]);
                        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
                    }
                } else {
                    fprintf(stderr, "Triangle error");
                    return;

                }
                glEnd();

            }

            void renderQuadArray(GLfloat vertices[], GLfloat colors[]) override {
                glClearColor(225 / 256.0f, 150 / 256.0f, 176 / 256.0f, 1);
                glClear(GL_COLOR_BUFFER_BIT);


                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);

                glVertexPointer(3, GL_FLOAT, 0, vertices);
                glColorPointer(3, GL_FLOAT, 0, colors);

                glDrawArrays(GL_QUADS, 0, 8);


                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
        };
    }
}


#endif /* GLRENDERSYSTEM_H */
