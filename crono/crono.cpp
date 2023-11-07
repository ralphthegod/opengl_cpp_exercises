#include <GL/freeglut.h>
#include <cmath>
#include <ctime>
#include <stdio.h>

int seconds = 0;
int minutes = 0;
bool isEnabled = false;

void drawHand(float width, float length, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(-width / 2, -length / 2);
        glVertex2f(width / 2, -length / 2);
        glVertex2f(width / 2, length - length / 2);
        glVertex2f(-width / 2, length - length / 2);
    glEnd();
}

void drawClock() {
    glColor3f(1.0, 1.0, 1.0);
    
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(0.0f, 0.0f, 0.0f);
    for(int i = 0; i <= 300; i++) {
        double angle = 2 * M_PI * i / 300;
        double x = cos(angle);
        double y = sin(angle);
        glVertex3f(x, y, 0);
    }
    glEnd();

    glColor3f(1.0, 0.3, 0.2);

    glPushMatrix();
    glTranslatef(0, 0, -1);
    glutSolidCylinder(1.1, 0.99, 20, 10);
    glPopMatrix();

    float minutes_angle = (minutes + seconds / 60.0) / 60.0 * 360.0;
    float seconds_angle = (seconds % 60) / 60.0 * 360.0;

    glPushMatrix();
    glRotatef(-minutes_angle, 0.0, 0.0, 1.0);
    glTranslatef(0, 0.5, 0.01);
    glScalef(1.0, 1, 0.2);
    drawHand(0.05, 1, 0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-seconds_angle, 0.0, 0.0, 1.0);
    glTranslatef(0, 0.5, 0.02);
    glScalef(1.0, 1.0, 0.1);
    drawHand(0.05, 1, 1.0, 0.0, 0.0);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glRotatef(45, 1.0, 1.0, 0.0);

    drawClock();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isEnabled = true;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        isEnabled = false;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r') {
        isEnabled = false;
        seconds = 0;
        minutes = 0;
    }
}

void update(int value){
    if (isEnabled) {
        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(1000, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("clock");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, update, 0);

    glutMainLoop();

    return 0;
}