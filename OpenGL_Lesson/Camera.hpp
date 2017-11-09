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
    vec3 pos;                           // カメラの位置
    vec3 target;                        // カメラの注視点
    vec3 up;                            // カメラの上方向
    float fov              = 45.0;      // Field Of View(視界の範囲)
    float aspect;                       // アスペクト比
    float near             = 0.1;       // これ以上近い位置にあるものは無視する
    float far              = 100.0;     // これ以上遠いものは無視する
    mat4 projection;                    // プロジェクション行列
    mat4 view;                          // ビュー行列
    float horizontal_angle = M_PI;
    float vertical_angle   = 0.0;
    float speed            = 3.0;       // 移動速度
    float mouse_speed      = 0.001;     // マウスに対する速度
    
    
    float current_time;
    float last_time = NULL;
    float last_xpos = NULL;
    float last_ypos = NULL;
public:
    Camera(vec3 position, GLFWwindow *window);  // 初期位置と扱うウィンドウ
    void controller(GLFWwindow *window);    // 入力を受け付けるウィンドウ
    
    mat4 getProjection();
    mat4 getView();
    vec3 getPosition();
};

#endif /* Camera_hpp */
