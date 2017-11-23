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


void LoadModel(const char* path,
               vector<unsigned short> *indices,
               vector<vec3> *vertices,
               vector<vec2> *uvs,
               vector<vec3> *normals)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, 0);
    const aiMesh* mesh = scene->mMeshes[0];
    
    // 頂点
    for(int i=0; i < mesh->mNumVertices; i++){
        aiVector3D pos = mesh->mVertices[i];
        vertices->push_back(vec3(pos.x, pos.y, pos.z));
    }
    // ノーマル
    for(int i=0; i<mesh->mNumVertices; i++){
        aiVector3D n = mesh->mNormals[i];
        normals->push_back(vec3(n.x, n.y, n.z));
    }
    
    // UV
    uvs->reserve(mesh->mNumVertices);
    for(int i=0; i<mesh->mNumVertices; i++){
        aiVector3D UVW = mesh->mTextureCoords[0][i];
        uvs->push_back(vec2(UVW.x, UVW.y));
    }
    
    // index
    for (int i=0; i<mesh->mNumFaces; i++){
        indices->push_back(mesh->mFaces[i].mIndices[0]);
        indices->push_back(mesh->mFaces[i].mIndices[1]);
        indices->push_back(mesh->mFaces[i].mIndices[2]);
    }
}

// テクスチャを読み込みます(現状PNGのみ)
GLuint LoadTexture(const char* filePath)
{
    GLuint textureID;
    
    png_structp sp = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop ip = png_create_info_struct(sp);
    FILE* fp = fopen(filePath, "rb");
    int width, height;
    int depth, colortype, interlacetype;
    GLubyte *data;
    
    png_init_io(sp, fp);
    png_read_info(sp, ip);
    png_get_IHDR(sp, ip, (png_uint_32*)&width, (png_uint_32*)&height, &depth, &colortype, &interlacetype, NULL, NULL);
    
    png_size_t rb = png_get_rowbytes(sp, ip);
    
    data = new GLubyte[height * rb];
    GLubyte **recv = new GLubyte*[height];
    for (int i = 0; i < height; i++)
    recv[i] = &data[i * rb];
    png_read_image(sp, recv);
    png_read_end(sp, ip);
    png_destroy_read_struct(&sp, &ip, NULL);
    fclose(fp);
    delete[] recv;
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return textureID;
}

