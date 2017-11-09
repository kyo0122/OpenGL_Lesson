//
//  Loader.hpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/10.
//  Copyright © 2017年 kyo. All rights reserved.
//

#ifndef Loader_hpp
#define Loader_hpp

#include "global.h"

// シェーダーを読み込む処理です
GLuint LoadShaders(const char* vertex_file_path,const char* fragment_file_path);

// ファイルを読み込む処理です
void ReadFile(string* code, const char* filePath);

// シェーダーをコンパイルする処理です
void CompileShader(GLuint id, string* code);

// コンパイルしたシェーダーに不備がないか確認する処理です
void CheckShaderProgram(GLuint id, GLint result, int* InfoLogLength);

#endif /* Loader_hpp */
