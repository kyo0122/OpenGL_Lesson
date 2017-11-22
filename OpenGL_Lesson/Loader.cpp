//
//  Loader.cpp
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/10.
//  Copyright © 2017年 kyo. All rights reserved.
//

#include "Loader.hpp"

// ファイルを読み込みます
void ReadFile(string* out, const char* filePath)
{
    ifstream fileStream(filePath, ios::in);
    if(fileStream.is_open()){
        string line = "";
        while(getline(fileStream, line)){
            *out += "\n"+line;
        }
        fileStream.close();
    }else{
        cout << "ファイルが読み込めません。パスが正しいか確認してください。\n";
        return;
    }
}

// シェーダープログラムのエラーをチェックします
void CheckShaderProgram(GLuint id, GLint result, int* InfoLogLength)
{
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, InfoLogLength);
    
    if (*InfoLogLength > 0){
        vector<char> programErrorMessage(*(InfoLogLength+1));
        glGetShaderInfoLog(id, *InfoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }
}

// シェーダーをコンパイルします
void CompileShader(GLuint id, string* code)
{
    char const* sourcePointer = code->c_str();
    glShaderSource(id, 1, &sourcePointer, NULL);
    glCompileShader(id);
}

// シェーダーを読み込む関数です
GLuint LoadShaders(const char* vertex_file_path,const char* fragment_file_path)
{
    // エラーチェック用変数
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    
    // 頂点シェーダーを生成
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    string VertexShaderCode;
    ReadFile(&VertexShaderCode, vertex_file_path);
    CompileShader(VertexShaderID, &VertexShaderCode);
    CheckShaderProgram(VertexShaderID, Result, &InfoLogLength);
    
    // フラグメントシェーダーを生成
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    string FragmentShaderCode;
    ReadFile(&FragmentShaderCode, fragment_file_path);
    CompileShader(FragmentShaderID, &FragmentShaderCode);
    CheckShaderProgram(FragmentShaderID, Result, &InfoLogLength);
    
    
    // シェーダーを合体
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    CheckShaderProgram(ProgramID, Result, &InfoLogLength);
    
    // 合体したやつがあるので、各シェーダーを削除
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
    return ProgramID;
}


void LoadMesh(const char* path, vector<vec3>* vertices)
{
    Assimp::Importer importer;  // 3Dファイルの読み込みに使う変数です。ファイルの情報を格納します。
    
    // 3Dファイルが、シーン/メッシュ(場合によっては複数のメッシュ)という構造になっているので、
    // sceneを取得し、そこからメッシュの情報にアクセスしています。
    const aiScene* scene = importer.ReadFile(path, 0);
    const aiMesh* mesh = scene->mMeshes[0];
    
    for(int i=0; i < mesh->mNumVertices; i++){
        aiVector3D pos = mesh->mVertices[i];
        vertices->push_back(vec3(pos.x, pos.y, pos.z));
    }
}

void LoadNormal(const char* path, vector<vec3>* normals)
{
    Assimp::Importer importer;  // 3Dファイルの読み込みに使う変数です。ファイルの情報を格納します。
    
    // 3Dファイルが、シーン/メッシュ(場合によっては複数のメッシュ)という構造になっているので、
    // sceneを取得し、そこからメッシュの情報にアクセスしています。
    const aiScene* scene = importer.ReadFile(path, 0);
    const aiMesh* mesh = scene->mMeshes[0];
    
    for(int i=0; i < mesh->mNumVertices; i++){
        aiVector3D pos = mesh->mNormals[i];
        normals->push_back(vec3(pos.x, pos.y, pos.z));
    }
}

