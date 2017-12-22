//
//  Camera.cpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/10.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(vec3 position, GLFWwindow *window)
{
    pos = position;
    
    // ウィンドウの縦横幅を取得して、アスペクト比を求めています。
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    aspect = (float)w / (float)h;
}

void Camera::controller(GLFWwindow *window)
{
    // 前の処理からの時間取得
    if (last_time==NULL) {
        last_time = glfwGetTime();
    }
    current_time = glfwGetTime();
    float delta_time = current_time - last_time;
    
    // マウスの移動量に伴う視点の移動
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (last_xpos==NULL || last_ypos==NULL) {
        last_xpos = xpos;
        last_ypos = ypos;
    }
    
    // マウスの移動量×速度分、カメラの角度を変更しています
    horizontal_angle += mouse_speed * (last_xpos - xpos);
    vertical_angle += mouse_speed * (last_ypos - ypos);
    
    // カメラの向き(Z)と右(X)を求めて、上(Y)を計算しています。
    direction = vec3(cos(vertical_angle) * sin(horizontal_angle),
                          sin(vertical_angle),
                          cos(vertical_angle) * cos(horizontal_angle)
                          );
    vec3 right = vec3(sin(horizontal_angle - M_PI/2),
                      0,
                      cos(horizontal_angle - M_PI/2)
                      );
    up = cross(right, direction);
    
    // キー入力に伴う位置の移動
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        pos += up *  delta_time * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        pos -= up *  delta_time * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        pos += direction *  delta_time * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        pos -= right *  delta_time * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        pos -= direction *  delta_time * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        pos += right *  delta_time * speed;
    }
    
    // ズーム機能
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && fov > 1) {
        fov -= 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && fov < 180) {
        fov += 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        fov = 45.0;
    }
    
    target = pos + direction;
    projection = perspective(radians(fov), aspect, near, far);
    view = lookAt(pos, target, up);
    
    last_xpos = xpos;
    last_ypos = ypos;
    last_time = current_time;
}

mat4 Camera::GetProjection(){return projection;}
mat4 Camera::GetView(){return view;}
vec3 Camera::GetPosition(){return pos;}
vec3 Camera::GetDirection(){return direction;}
