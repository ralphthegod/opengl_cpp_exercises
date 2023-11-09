#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>
#include <iostream>

const int NUM_OF_POINTS = 3;

GLfloat initControlPoints[NUM_OF_POINTS][3] = { 
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f },
};

int grade = 2;

void compute_t(float t, GLfloat* result, int grade, GLfloat controlPoints[][3], int NUM_OF_POINTS) {
    GLfloat p[NUM_OF_POINTS][3];

    for(int i = 0; i < NUM_OF_POINTS; i++){
        p[i][0] = controlPoints[i][0];
        p[i][1] = controlPoints[i][1];
        p[i][2] = controlPoints[i][2];
    }

    for(int r = 1; r <= grade; r++){
        for(int i = 0; i <= grade - r; i++){
            p[i][0] = ((1 - t) * p[i][0]) + (t * p[i + 1][0]);
            p[i][1] = ((1 - t) * p[i][1]) + (t * p[i + 1][1]);
            p[i][2] = ((1 - t) * p[i][2]) + (t * p[i + 1][2]);
        }
    }

    result[0] = p[0][0];
    result[1] = p[0][1];
    result[2] = p[0][2];
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float step = 0.01f;
    GLfloat result[3];

    glBegin(GL_LINE_STRIP);
        for(float t=0; t<=1; t+=step){
            compute_t(t, result, grade, initControlPoints, NUM_OF_POINTS);
            glVertex2f(result[0], result[1]);
        }
    glEnd();

    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("bezier");

    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
