//
// Created by Zixiong Liu on 4/9/18.
//

#ifndef CUBE_DRAWER_H
#define CUBE_DRAWER_H

#include <vector>
#include "glcommon.h"
#include "cube.h"
#include "shader.h"


using namespace std;

class Drawer {
private:
    vector<GLint> indexBuffer;
    GLuint indexBufferID;
    GLuint VAOID;
    GLuint VBOID;
public:
    Drawer ();
    Shader shader;
    void draw(Cube* cube);
};


#endif //CUBE_DRAWER_H
