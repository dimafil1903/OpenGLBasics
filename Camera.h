/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLCamera.h
 * Author: KnightDanila
 *
 * Created on 1 октября 2019 г., 9:15
 */

#ifndef GLCAMERA_H
#define GLCAMERA_H

namespace DFN {
    namespace GraphCore {

        class Camera {
        public:

            virtual void setPerspective(float fov, float aspect, float near, float far) {

            };

            virtual void setPos(glm::vec3 pos) {
            };

            virtual void setTarget(glm::vec3 pos) {

            };

            virtual glm::vec3 getPos() {
            };

            virtual void start() {

            };

            virtual void end() {

            };


        protected:
            glm::mat4 modelproj = glm::mat4(0.0f);
            glm::vec3 pos = glm::vec3(0.0f);
            glm::vec3 direction = glm::vec3(0.0f);
            glm::mat4 modelview = glm::mat4(0.0f);
        };

        class GLCameraFree : public Camera {
        public:

            void setPerspective(float fov, float aspect, float near1, float far1) override {

                glMatrixMode(GL_PROJECTION);
                modelproj = glm::perspective(fov, aspect, near1, far1);
                glLoadMatrixf(glm::value_ptr(modelproj));


            };

            void setPos(glm::vec3 pos) override {
                glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
                glm::vec3 direction = glm::normalize(pos - target);
                modelview = glm::lookAt(pos, direction, glm::vec3(0, 1, 0));
                //glMatrixMode(GL_PROJECTION);
                //GL_PROJECTION_MATRIX
                //glLoadMatrixf(&modelview);
                glMatrixMode(GL_MODELVIEW);
                glLoadMatrixf(glm::value_ptr(modelview));

            };

            void start() override {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadMatrixf(glm::value_ptr(modelview));

            }

            void end() override {
                glPopMatrix();
            }

            glm::vec3 getPos() override {
            };

            glm::mat4 getMat4ModelView() {
                return modelview;
            };

            glm::mat4 getMat4ModelProj() {
                return modelproj;
            };
        };

//        class GLCameraTarget : public Camera {
////        ...
//        };


    };
}

#endif /* GLCAMERA_H */
