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

void drawSphere(GLdouble radius, GLint slices, GLint stacks) {
    GLUquadricObj *quadObj = gluNewQuadric();
    gluSphere(quadObj, radius, slices, stacks);
    gluDeleteQuadric(quadObj);
}

void drawCylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks) {
    GLUquadricObj *quadObj = gluNewQuadric();
    gluCylinder(quadObj, baseRadius, topRadius, height, slices, stacks);
    gluDeleteQuadric(quadObj);
}

void drawDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint rings) {
    GLUquadricObj *quadObj = gluNewQuadric();
    gluDisk(quadObj, innerRadius, outerRadius, slices, rings);
    gluDeleteQuadric(quadObj);
}

void drawPartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint rings, GLdouble startAngle, GLdouble sweepAngle) {
    GLUquadricObj *quadObj = gluNewQuadric();
    gluPartialDisk(quadObj, innerRadius, outerRadius, slices, rings, startAngle, sweepAngle);
    gluDeleteQuadric(quadObj);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glTranslatef(0.0f, 0.0f, -10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float camX = sin(angleY * M_PI / 180.0) * 10.0;
    float camY = sin(angleX * M_PI / 180.0) * 10.0;
    float camZ = cos(angleY * M_PI / 180.0) * 10.0;

    gluLookAt(camX, camY, camZ, 
              0, 0, 0,          
              0, 1, 0);  

    glEnable(GL_AUTO_NORMAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_FLAT);

    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, -6.0f);
    drawSphere(1.0, 20, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, 0.0f, -6.0f);
    drawCylinder(0.5, 0.5, 1.5, 16, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, -3.0f, -6.0f);
    drawDisk(0.5, 1.0, 20, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, -3.0f, -6.0f); 
    drawPartialDisk(0.7, 1.0, 20, 4, 0.0, 180.0);
    glPopMatrix();

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
    glutCreateWindow("solids");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMotionFunc(motion);

    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}