//
//  main.cpp
//  OpenGL_Lesson
//
//  Created by wta1601 on 2017/11/08.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "global.h"
#include "Loader.hpp"
#include "Camera.hpp"
#include "ModelObject.hpp"
#include "Bullet.hpp"

// glfwを使う場合は、以下の二つをインクルードします
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


void initWindowHints();

int main() {
    
    if (!glfwInit()){
        return -1;
    }
    
    initWindowHints();
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "☀️☁️", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // 深度を使うための宣言(デフォルトでは、あらゆる機能がオフ)
    glEnable(GL_DEPTH_TEST);
    
    ModelObject skybox("skybox.obj", "Skybox");
    skybox.SetTexture("winter-2383930_1280.png");
    
    Camera cam(vec3(0, 0, 0), window);
    
    // ImGuiの初期化処理です
    // 二つ目の引数はコールバックを行うかどうかです。
    // 詳しくはimgui_impl_glfw_gl3.cppのImGui_ImplGlfwGL3_Initを確認してください。
    ImGui_ImplGlfwGL3_Init(window, false);
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        // GL_DEPTH_BUFFER_BITで深度情報のクリア
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // フレーム毎にImGuiの入力等を準備する関数です
        ImGui_ImplGlfwGL3_NewFrame();
        
        // ブロック内がGUIに関する処理です。
        // OpenGLの説明範囲外なので、詳しい処理の説明は行いません。
        // imgui.cppの最上部に説明が書かれているので、
        // そちらを参照してください。
        {
            ImGui::Begin("TestWindow");
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        cam.controller(window);
        
        skybox.position = cam.GetPosition();
        skybox.Rendering(cam);
        
        // ImGuiは処理をまとめて実行します。
        ImGui::Render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void initWindowHints()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED ,true);  // <-これをfalseにすると…
}


