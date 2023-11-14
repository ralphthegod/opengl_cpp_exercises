#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#define M_PI 3.14159265358979323846
#include <cmath>

GLUnurbsObj *nurbs;

const int numCtrlPoints = 6;
float ctrlPoints[numCtrlPoints][3] = {
    
};

int grade = 2;

GLfloat knots[10] = {0.0, 0.0, 0.0, 0.25, 0.5, 0.5, 0.75, 1.0, 1.0, 1.0};
GLfloat weights[9] = {1.0, 0.5, 0.5, 1.0, 0.5, 0.5, 1.0};

void nurbsError(GLenum errorCode) {
    const GLubyte *estring;

    estring = gluErrorString(errorCode);
    std::cout << "errore " << estring << std::endl;
    exit(0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    nurbs = gluNewNurbsRenderer();
    gluNurbsCallback(nurbs, GLU_ERROR, (GLvoid (*)()) nurbsError);
    gluNurbsProperty(nurbs, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(nurbs, GLU_DISPLAY_MODE, GLU_FILL);

    gluBeginCurve(nurbs);
    gluNurbsCurve(nurbs, 10, knots, 3, &ctrlPoints[0][0], 3, GL_MAP1_VERTEX_4);
    gluEndCurve(nurbs);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("cerchio nurbs");

    glutDisplayFunc(display);

    glClearColor(1.0, 1.0, 1.0, 0.0);

    glutMainLoop();

    return 0;
}
