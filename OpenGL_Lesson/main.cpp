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
    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "🎫→📱", NULL, NULL);
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
    cam.controller(window);
    
    // ImGuiの初期化処理です
    ImGui_ImplGlfwGL3_Init(window, false);
    
    // ImGuiのフォント設定です。
    // 日本語を使う場合は必須の処理です。
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("sawarabi-gothic-medium.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    
    // ImGui独自のカーソル表示です
//    io.MouseDrawCursor = true;
    
    // ImGuiのウィンドウ設定です
    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoResize;
//    flags |= ImGuiWindowFlags_NoMove;
    
    // ImGuiのスタイル設定です
    ImGuiStyle &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = ImVec4(0, 0, 0, 1);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0);
    
    bool toggle = false;
    
    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        // GL_DEPTH_BUFFER_BITで深度情報のクリア
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // フレーム毎にImGuiの入力等を準備する関数です
        ImGui_ImplGlfwGL3_NewFrame();
        
        if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
            toggle = true;
        }
        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            toggle = false;
        }
        
        if(toggle){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cam.controller(window);
        }
        
        // ブロック内がGUIに関する処理です。
        // OpenGLの説明範囲外なので、詳しい処理の説明は行いません。
        // imgui.cppの最上部に説明が書かれているので、
        // そちらを参照してください。
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("テストウィンドウ", NULL, flags);
            ImGui::Text("こんにちworld!");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        
        
        
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
    glfwWindowHint(GLFW_DECORATED ,true);
}


