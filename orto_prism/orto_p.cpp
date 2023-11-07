#include <GL/freeglut.h>
#include <cmath>

const float PI = 3.14159265358979323846;
float centerX = 0.2f;
float centerY = 0.2f;
float lowerZ = -0.5f;
float upperZ = -1.5f;
float radius = 0.5f;

float fov = 45.0f;
float aspect = 1.0f;
float nearVal = 1.0f;
float farVal = 5.0f;

void updateOrtho() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, nearVal, farVal);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void drawOctagonalBasePrism() {
    glColor3f(0.5f, 0.7f, 1.0f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 9; ++i) {
        float angle = 2 * PI * i / 8;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex3f(x, y, lowerZ);
        glVertex3f(x, y, upperZ);
    }

    glVertex3f(centerX + radius, centerY, lowerZ);
    glVertex3f(centerX + radius, centerY, upperZ);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; ++i) {
        float angle = 2 * PI * i / 8;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex3f(x, y, lowerZ);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 8; ++i) {
        float angle = 2 * PI * i / 8;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex3f(x, y, upperZ);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.7f, 1.0f);
    drawOctagonalBasePrism();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    updateOrtho();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            fov += 0.1f;
            break;
        case 's':
            fov -= 0.1f;
            break;
        case 'a':
            aspect -= 0.1f;
            break;
        case 'd':
            aspect += 0.1f;
            break;
        case 'q':
            farVal -= 0.1f;
            break;
        case 'e':
            farVal += 0.1f;
            break;
    }
    updateOrtho();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("test");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
