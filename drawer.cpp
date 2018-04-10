//
// Created by Zixiong Liu on 4/9/18.
//

#include "drawer.h"
#include "cube.h"
#include "shader.h"

Drawer::Drawer() : shader("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader"){
    this->indexBuffer = Cube::triangularize();
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glGenVertexArrays(1, &this->VAOID);
    glBindVertexArray(this->VAOID);
    glCheckError();

    glGenBuffers(1, &this->indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer.size() * sizeof(GLint), this->indexBuffer.data(), GL_STATIC_DRAW);
    glCheckError();
}

void Drawer::draw(Cube *cube) {
    vector<vec3> points;
    for (auto& p: cube->points) {
        points.push_back(p.position);
    }


    shader.use();

    glGenBuffers(1, &this->VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOID);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(vec3), &points[0].x, GL_STATIC_DRAW);
    glCheckError();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawElements(GL_TRIANGLES, this->indexBuffer.size(), GL_UNSIGNED_INT, (GLvoid*)0);
    glCheckError();

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &this->VBOID);


}
