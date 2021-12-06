#include "star.h"
#include "mesh.h"
#include <glm/ext/matrix_transform.hpp>

using namespace glm;

void Star::bindSatellite(std::initializer_list<Star> satellites) {
    for (const auto &sate : satellites) {
        satellite.push_back(sate);
    }
}

void Star::bindTorus(GLdouble inner, GLdouble outer) {
    isTorus = true;
    this->inner = inner;
    this->outer = outer;
}

void Star::display() const {
    glPushMatrix();

    glTranslatef(center, 0, 0);
    glRotatef(year, rotate[0], rotate[1], rotate[2]);
    glTranslatef(-center, 0, 0);
    glTranslatef(offset[0], offset[1], offset[2]);
    glRotatef(day, spin[0], spin[1], spin[2]);

    Material::applyMaterial(mtl);
    glutSolidSphere(radius, 200, 200);

    if (isTorus) {
        glRotatef(90, 1.0, 0, 0.0);
        glutSolidTorus(inner, outer, 5, 64);
        glRotatef(-90, 1.0, 0, 0.0);
    }

    for (const auto &s : satellite) {
        Material::applyMaterial(s.mtl);

        glRotatef(s.year, s.rotate[0], s.rotate[1], s.rotate[2]);
        glTranslatef(s.offset[0], s.offset[1], s.offset[2]);
        glutSolidSphere(s.radius, 20, 20);
    }
    glPopMatrix();
    Material::applyMaterial(mtl);
    drawOrbit();
}

void Star::rotateAndSpin() {
    year = fmodf(year + yearStep, 360.0);
    day = fmodf(day + dayStep, 360.0);
    for (auto &s : satellite) {
        s.rotateAndSpin();
    }
}

void Star::drawOrbit() const {
    const int orbit_slice = 300;
    const GLfloat pi = 3.14159265358979, delta_degree = 2 * pi / orbit_slice;

    // Material::clearMaterial();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < orbit_slice; ++i) {
        auto point = vec4(offset.x - center, offset.y, offset.z, 1) *
                     glm::rotate(mat4(1.0), (GLfloat) i * delta_degree, rotate);
        glVertex3f(center + point.x, point.y, point.z);
    }
    glEnd();

}