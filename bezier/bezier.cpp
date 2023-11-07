#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>
#include <iostream>

const int NUM_OF_POINTS = 3;

GLfloat initControlPoints[NUM_OF_POINTS][3] = { 
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { -1.0f, 1.0f, 0.0f },
};

int grade = 3;

void compute_t(float t, GLfloat){
    GLfloat p[NUM_OF_POINTS][3];

    for(int i=0; i<NUM_OF_POINTS; i++){
        p[i][0] = initControlPoints[i][0];
        p[i][1] = initControlPoints[i][1];
        p[i][2] = initControlPoints[i][2];
    }

    for(int r=1; r<=grade; r++){
        for(int i=0; i<=grade-r; i++){
            p[i] = ((1-t) * p[i].x) + (t * p[i+1].x);
            p[i].y = ((1-t) * p[i].y) + (t * p[i+1].y);
        }
    }
    return p[0];
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float step = 0.01f;
    glBegin(GL_LINE_STRIP);
        for(float t=0; t<=1; t+=step){
            Point p = compute_t(t);
            glVertex2f(p.x, p.y);
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
