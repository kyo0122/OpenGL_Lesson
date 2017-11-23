//
//  global.h
//  OpenGL_Lesson
//
//  Created by kyosuke on 2017/11/10.
//  Copyright © 2017年 kyo. All rights reserved.
//

#ifndef global_h
#define global_h

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <libpng16/png.h>

#pragma clang pop

#endif /* global_h */
