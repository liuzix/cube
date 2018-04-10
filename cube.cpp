//
// Created by Zixiong Liu on 4/9/18.
//

#include "cube.h"
#include <cmath>
#include <cassert>

const vec3 cubeModel[] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
                          {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

Cube::Cube() {

    const vec3 initPos = {0, 0.5, 0};
    const float scale = 0.2;

    for (vec3 offset: cubeModel) {
        Point p;
        p.position = offset * scale + initPos;
        p.mass = 0.1;
        p.velocity = {0, 0, 0};
        p.acceleration = {0, 0, 0};
        points.push_back(p);
    }

    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            Spring sp;
            sp.k = 50.0;
            sp.l0 = glm::distance(points[i].position,points[j].position);
            sp.m1 = &points[i];
            sp.m2 = &points[j];
            springs.push_back(sp);

            sp.m1->springs.push_back(&springs.back());
            sp.m2->springs.push_back(&springs.back());
        }
    }
}

vector<GLint> Cube::triangularize() {
    vector<GLint> ret;
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            for (int k = j + 1; k < 8; k++) {
                vec3 p1 = cubeModel[i];
                vec3 p2 = cubeModel[j];
                vec3 p3 = cubeModel[k];
                if ((p1.x == p2.x && p2.x == p3.x)
                   ||(p1.y == p2.y && p2.y == p3.y)
                   ||(p1.z == p2.z && p2.z == p3.z))
                {
                    ret.push_back(i);
                    ret.push_back(j);
                    ret.push_back(k);
                }
            }
        }
    }
    return ret;
}

void Cube::update() {
    const float dt = 0.003;
    vec3 totalA = {0,0,0};
    for (Point& pt: points) {
        vec3 force {0, 0, 0};
        for (Spring* sp: pt.springs) {
            vec3 dirForce;
            if (&pt == sp->m1) dirForce = sp->m2->position - sp->m1->position;
            else if (&pt == sp->m2) dirForce = sp->m1->position - sp->m2->position;
            else assert(false);
            force += normalize(dirForce) * sp->currentForce();
        }
        force += 9.8f * pt.mass * vec3(0, -1, 0);
        if (pt.position.y < 0) {
            force += vec3(0, -pt.position.y * 20, 0);
        }

        force -= pt.velocity * 0.15f;

        pt.acceleration = force / pt.mass;
        pt.velocity += pt.acceleration * dt;
        pt.position += pt.velocity * dt;

        totalA += pt.acceleration;
    }

    cout << (totalA / 8.0f).y << endl;





}

float Spring::currentLength() {
    return distance(m1->position, m2->position);
}

float Spring::currentForce() {
    //cout << "length diff = " << currentLength() - l0 << endl;
    return (currentLength() - l0) * k;
}
