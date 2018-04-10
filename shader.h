//
// Created by Zixiong Liu on 4/9/18.
//

#ifndef CUBE_SHADER_H
#define CUBE_SHADER_H
#include "glcommon.h"
#include <string>

using namespace std;

class Shader {
private:
    GLuint ID = 0;
public:
    Shader(string vertexShader, string fragmentShader);
    void use();
    void setMVP(glm::mat4& mvp);


};


#endif //CUBE_SHADER_H
