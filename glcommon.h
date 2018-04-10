//
// Created by Zixiong Liu on 4/9/18.
//

#ifndef CUBE_GLCOMMON_H
#define CUBE_GLCOMMON_H

//#define GLFW_INCLUDE_GLCOREARB
#include <GL/glew.h>
// #include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <string>
#include <iostream>

inline GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case 0x503:                error = "STACK_OVERFLOW"; break;
            case 0x504:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:
                break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
        exit(-1);
    }

    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)


#endif //CUBE_GLCOMMON_H
