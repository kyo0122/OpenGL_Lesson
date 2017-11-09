//
//  Camera.hpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/10.
//  Copyright © 2017年 kyo. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "global.h"

class Camera{
private:
    vec3 pos;
    vec3 target;
    vec3 up;
    float fov = 45.0;
    float aspect;
    float near = 0.1;
    float far = 100.0;
    mat4 projection;
    mat4 view;
    float horizontal_angle = M_PI;
    float vertical_angle = 0.0;
    float speed = 3.0;
    float mouse_speed = 0.001;
    float current_time;
    float last_time = NULL;
    float last_xpos = NULL;
    float last_ypos = NULL;
public:
    Camera(vec3 position, GLFWwindow *window);
    void controller(GLFWwindow *window);
    
    mat4 getProjection();
    mat4 getView();
    vec3 getPosition();
};

#endif /* Camera_hpp */
