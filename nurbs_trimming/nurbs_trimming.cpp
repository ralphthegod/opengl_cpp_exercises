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

GLfloat ctlpoints[4][4][3] = {
    {{-3, -3, -3}, {-3, -1, -3}, {-3, 1, -3}, {-3, 3, -3}},
    {{-1, -3, -3}, {-1, -1, 3},  {-1, 1, 3},  {-1, 3, -3}},
    {{1, -3, -3},  {1, -1, 3},   {1, 1, 3},   {1, 3, -3}},
    {{3, -3, -3},  {3, -1, -3},  {3, 1, -3},  {3, 3, -3}}
};

GLfloat E[5][2]={{0,0},{1,0},{1,1},{0,1},{0,0}};
GLfloat P[5][2]={{0.3,0.3},{0.3,0.7},
 {0.7,0.7},{0.7,0.3},{0.3,0.3}};

GLUnurbsObj *theNurb;

void init() {
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
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

    float step = 0.01f;
    GLfloat result[3];

    glEnable(GL_AUTO_NORMAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_FLAT);

    GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &ctlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
    
    gluBeginTrim(theNurb);
        gluPwlCurve(theNurb,5,&E[0][0],2,GLU_MAP1_TRIM_2);
    gluEndTrim(theNurb);
    gluBeginTrim(theNurb);
        gluPwlCurve(theNurb,5,&P[0][0],2,GLU_MAP1_TRIM_2);
    gluEndTrim(theNurb);

    gluEndSurface(theNurb);

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
    glutCreateWindow("bspline surface");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMotionFunc(motion);

    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    init();

    glutMainLoop();
    return 0;
}