#include <GL/freeglut.h>
#include <GL/gl.h>
#include <vector>
#include <iostream>

std::vector<std::vector<GLfloat>> controlPoints;
int grade = 2;

void compute_t(float t, GLfloat* result, int grade, const std::vector<std::vector<GLfloat>>& controlPts) {
    std::vector<std::vector<GLfloat>> p = controlPts;

    for(int r = 1; r <= grade; r++){
        for(int i = 0; i <= grade - r; i++){
            p[i][0] = ((1 - t) * p[i][0]) + (t * p[i + 1][0]);
            p[i][1] = ((1 - t) * p[i][1]) + (t * p[i + 1][1]);
        }
    }

    result[0] = p[0][0];
    result[1] = p[0][1];
}


void mouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float winX = (float)x / (float)glutGet(GLUT_WINDOW_WIDTH);
        float winY = (float)y / (float)glutGet(GLUT_WINDOW_HEIGHT);
        winX = (winX - 0.5f) * 2.0f;
        winY = (winY - 0.5f) * 2.0f;
        winY = -winY; // invert Y axis for mouse coordinates

        std::vector<GLfloat> point = {winX, winY, 0.0f};
        controlPoints.push_back(point);

        if(controlPoints.size() > grade){
            glutPostRedisplay();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(controlPoints.size() > grade){
        float step = 0.01f;
        GLfloat result[2];

        glBegin(GL_LINE_STRIP);
            for(float t = 0; t <= 1; t += step){
                glColor3f(1.0f, 1.0f, 1.0f);
                compute_t(t, result, grade, controlPoints);
                glVertex2f(result[0], result[1]);
            }
        glEnd();
    }
    else{
        glBegin(GL_LINE_STRIP);
            for(int i = 0; i < controlPoints.size(); i++){
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(controlPoints[i][0], controlPoints[i][1]);
            }
        glEnd();
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("bezier");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}