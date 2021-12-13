#include "star.h"
#include "mesh.h"
#include <glm/ext/matrix_transform.hpp>

using namespace glm;
using namespace loia;

static void applyMtl(const loia::Material &mtl) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, value_ptr(mtl.ambient));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, value_ptr(mtl.diffuse));
    glMaterialfv(GL_FRONT, GL_SPECULAR, value_ptr(mtl.specular));
    glMaterialfv(GL_FRONT, GL_EMISSION, value_ptr(mtl.emssion));
    glMaterialf(GL_FRONT, GL_SHININESS, mtl.Ns);
    glBindTexture(GL_TEXTURE_2D, mtl.mapKd);
    glEnable(GL_TEXTURE_2D);
}

Star::Star(GLfloat radius, GLfloat yearStep, GLfloat dayStep, const loia::Material *mtl,
           glm::vec3 offset, glm::vec3 rotate, glm::vec3 spin)
    : radius(radius), yearStep(yearStep), dayStep(dayStep), mtl(mtl), rotate(rotate), spin(spin),
      offset(offset) {
    pQuad = gluNewQuadric();
    gluQuadricTexture(pQuad, true);
}

Star::~Star() {
    // gluDeleteQuadric(pQuad);
}

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

    mtl->apply();
    gluSphere(pQuad, radius, 200, 200);

    if (isTorus) {
        glRotatef(90, 1.0, 0, 0.0);
        glutSolidTorus(inner, outer, 5, 64);
        glRotatef(-90, 1.0, 0, 0.0);
    }

    for (const auto &s : satellite) {
        s.mtl->apply();

        glRotatef(s.year, s.rotate[0], s.rotate[1], s.rotate[2]);
        glTranslatef(s.offset[0], s.offset[1], s.offset[2]);
        gluSphere(pQuad, s.radius, 20, 20);
    }
    glPopMatrix();
    mtl->apply();
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