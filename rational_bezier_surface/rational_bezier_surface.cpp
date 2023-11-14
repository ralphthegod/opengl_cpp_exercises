#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>
#include <iostream>

#define M_PI 3.14159265358979323846

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isMousePressed = false;

GLfloat ctrlPoints[4][4][3] = {
    {{0,0,0},{1,0,0.5},{2,0,1},{3,0,0}},
    {{0,1,0},{1,1,3},{2,1,3},{3,1,0}},
    {{0,2,0},{1,2,3},{2,2,3},{3,2,0}},
    {{0,3,0},{1,3,1},{2,3,0.5},{3,3,0}}
};

GLfloat weights[4][4] = {
    {1, 0.5, 0.5, 1},
    {1, 0.5, 0.5, 1},
    {1, 0.5, 0.5, 1},
    {1, 0.5, 0.5, 1}
};

GLfloat weighted_ctrlPoints[4][4][4];

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float camX = sin(angleY * M_PI / 180.0) * 10.0;
    float camY = sin(angleX * M_PI / 180.0) * 10.0;
    float camZ = cos(angleY * M_PI / 180.0) * 10.0;

    gluLookAt(camX, camY, camZ, 
              0, 0, 0,          
              0, 1, 0);  

    glMap2f(GL_MAP2_VERTEX_4, 0.0f, 1.0f, 4, 4, 0.0f, 1.0f, 16, 4, &weighted_ctrlPoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_4);
    glEnable(GL_AUTO_NORMAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_FLAT);

    glMapGrid2f(10, 0.0f, 1.0f, 10, 0.0f, 1.0f);
    glEvalMesh2(GL_FILL, 0, 10, 0, 10);

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isMousePressed = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isMousePressed = false;
        }
    }
}

void motion(int x, int y) {
    if (isMousePressed) {
        float deltaX = x - lastMouseX;
        float deltaY = y - lastMouseY;

        angleY += deltaX * 0.5f;
        angleX += deltaY * 0.5f;

        if (angleX > 60.0f) angleX = 60.0f;
        if (angleX < -60.0f) angleX = -60.0f;
        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("bezier");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMotionFunc(motion);

    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            weighted_ctrlPoints[i][j][0] = ctrlPoints[i][j][0] * weights[i][j];
            weighted_ctrlPoints[i][j][1] = ctrlPoints[i][j][1] * weights[i][j];
            weighted_ctrlPoints[i][j][2] = ctrlPoints[i][j][2] * weights[i][j];
            weighted_ctrlPoints[i][j][3] = weights[i][j];
        }
    }

    glutMainLoop();
    return 0;
}