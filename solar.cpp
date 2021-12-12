#include "glScene.h"
#include "mesh.h"
#include "star.h"
#include <glm/geometric.hpp>

using namespace std;
using namespace glm;
using namespace loia;

static Mesh car;
Camera camera{-0.15, 1.14, {-72, 3, 36.5}, {0, 1, 0}};
// clang-format off
Material sun_m  {.specular{1.0, 0.0, 0.0}, .emssion{1, 0, 0}},
    adam_m      {.specular{0.2, 0.4, 0.6}, .emssion{0.3, 0.2, 0.9}},
    hesper_m    {.specular{0.2, 0.4, 0.6}, .emssion{0.83, 0.8, 0.2}},
    earth_m     {.specular{0.1, 0.3, 0.1}, .emssion{0.1, 0.2, 0.6}},
    mars_m      {.specular{0.2, 0.4, 0.6}, .emssion{1, 0.1, 0.0}},
    jupiter_m   {.specular{0.2, 0.4, 0.6}, .emssion{0.8, 0.7, 0.1}},
    saturn_m    {.specular{0.2, 0.4, 0.6}, .emssion{0.6, 0.6, 0.3}},
    uranus_m    {.specular{0.2, 0.4, 0.6}, .emssion{0.3, 0.3, 0.7}},
    neptune_m   {.specular{0.2, 0.4, 0.6}, .emssion{0, 0.1, 1}},
    moon_m      {.specular{0.2, 0.4, 0.6}, .emssion{1, 1, 0}}, 
    mars_s1_m   {.specular{0.2, 0.4, 0.6}, .emssion{0, 1, 1}},
    mars_s2_m   {.specular{0.2, 0.4, 0.6}, .emssion{0, 0, 1}},
    jupiter_s1_m{.specular{0.2, 0.4, 0.6}, .emssion{0.3, 0.6, 1}},
    saturn_s1_m {.specular{0.2, 0.4, 0.6}, .emssion{0.3, 0.6, 1}};
// clang-format on

// 水星、金星、地球、火星、木星、土星、天王星、和海王星
// adam,hesper,earth,mars,jupiter,saturn,uranus,neptune
static Star sun(10, 0, 10.0, sun_m, {-15, 0, 0}),
    adam(0.5, 1.2, 10.0, adam_m, {0.2, 0, 0}, {0, 0.6, 0.4}),
    hesper(0.8, 1, 10.0, hesper_m, {0.8, 0, 0}, {0, 0.5, 0.45}),
    earth(0.5, 0.8, 10.0, earth_m, {2, 0, 0}),
    mars(0.6, 0.6, 10.0, mars_m, {7, 0, 0}, {0, 0.4, 0.5}),
    jupiter(2, 0.5, 10.0, jupiter_m, {13, 0, 0}, {0, 0.48, 0.52}),
    saturn(1.4, 0.4, 10.0, saturn_m, {20, 0, 0}, {0, 0.45, 0.6}),
    uranus(1.5, 0.3, 10.0, uranus_m, {28, 0, 0}, {0, 0.4, 0.65}),
    neptune(1.3, 0.2, 10.0, neptune_m, {32, 0, 0}, {0, 0.65, 0.3}),
    moon(0.25, 0.3, 0.03, moon_m, {2, 0, 0}, {0, 1, 0}),
    mars_s1(0.1, 1.5, 0, mars_s1_m, {1, 0, 0}, {0, 1, 0}),
    mars_s2(0.2, 0.7, 0, mars_s2_m, {1.5, 0, 0}, {0, 1, 0}),
    jupiter_s1(0.6, 0.5, 0, jupiter_s1_m, {3, 0, 0}, {0, 1, 0}),
    saturn_s1(0.4, 0.4, 0, saturn_s1_m, {2.7, 0, 0}, {0, 1, 0});

static Star *stars[] = {&sun, &adam, &hesper, &earth, &mars, &jupiter, &saturn, &uranus, &neptune};

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    earth.bindSatellite({moon});
    mars.bindSatellite({mars_s1, mars_s2});
    jupiter.bindSatellite({jupiter_s1});
    jupiter.bindTorus(0.25, 5.0);
    saturn.bindSatellite({saturn_s1});
    saturn.bindTorus(0.1, 3.0);
    car = Mesh::loadMesh("../assets/simple_car.obj"); // simple car modeled by mesh
    // car = Mesh::loadMesh("../assets/cubic");
    // car = Mesh::loadMesh("../assets/awesome_car"); // 350+MB, take ~1min to load it
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Light sun_light = {.pos{center, 0, 0, 1.0},
                       .ambient{0.1F, 0.02F, 0.02F, 1.0F},
                       .diffuse{0.3F, 0.0F, 0.0F, 0.8F},
                       .specular{1.0F, 0.2F, 0.2F, 1.0F}};
    Light env_light = {.pos{0, 1, 0, 0.0},
                       .ambient{0.05F, 0.05F, 0.05F, 1.0F},
                       .diffuse{0.1F, 0.1F, 0.0F, 0.8F},
                       .specular{0.2F, 0.2F, 0.0F, 1.0F}};

    Light::applyLight(GL_LIGHT0, sun_light);
    Light::applyLight(GL_LIGHT1, env_light);

    glPushMatrix();
    glTranslatef(-36, -0.75, 18);
    Mesh::renderMesh(car, 1);
    glPopMatrix();

    // cerr << camera.eye.x << ' ' << camera.eye.y << ' ' << camera.eye.z << endl;
    // cerr << camera.verticalAngle << ' ' << camera.horizontalAngle << endl;

    for (const auto &star : stars) star->display();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(value_ptr(glm::lookAt(camera.eye, camera.eye + camera.viewVec(), camera.up)));

    glutPostRedisplay();
    glutSwapBuffers();
}
namespace mouse {
static int prev_x = 0, prev_y = 0;
static bool mouse_left_down = false;

void stateCallback(int button, int state, int x, int y) {
    prev_x = x;
    prev_y = y;
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouse_left_down = true;
        } else if (state == GLUT_UP) {
            mouse_left_down = false;
        }
    }
}
void motionCallback(int x, int y) {
    const GLfloat sensitivity = 1 / 30000.0F;
    if (mouse_left_down) {
        camera.horizontalAngle -= (GLfloat) (x - prev_x) * sensitivity;
        camera.verticalAngle += (GLfloat) (y - prev_y) * sensitivity;
        if (camera.verticalAngle > 90.0) camera.verticalAngle = 89.9;
    }
    glutPostRedisplay();
}
} // namespace mouse
void keyCallback(unsigned char key, int /*unused*/, int /*unused*/) {
    vec3 lr_direction = normalize(cross(camera.up, camera.viewVec()));
    vec3 view_direction = normalize(camera.viewVec());
    switch (key) {
    case 'A':
    case 'a': camera.eye += 0.5F * lr_direction; break;
    case 'D':
    case 'd': camera.eye -= 0.5F * lr_direction; break;
    case 'W':
    case 'w': camera.eye += 0.5F * view_direction; break;
    case 'S':
    case 's': camera.eye -= 0.5F * view_direction; break;
    }
    glutPostRedisplay();
}

void myIdle(void) {
    for (auto &star : stars) star->rotateAndSpin();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(100.0, (GLfloat) w / (GLfloat) h, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLoadMatrixf(value_ptr(glm::lookAt(camera.eye, camera.eye + camera.viewVec(), camera.up)));
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("solar system");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse::stateCallback);
    glutMotionFunc(mouse::motionCallback);
    glutIdleFunc(myIdle);

    glutKeyboardFunc(keyCallback);

    glutMainLoop();
    return 0;
}