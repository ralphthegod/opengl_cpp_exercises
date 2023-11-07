#include <GL/freeglut.h>
#include <cmath>
#include <ctime>

int extraMinutes = 0;

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

    glVertex2f(0.0f, 0.0f);
    for(int i = 0; i <= 300; i++) {
        double angle = 2 * M_PI * i / 300;
        double x = cos(angle);
        double y = sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    time_t now = time(0);
    tm *ltm = localtime(&now);

    int hours = ltm->tm_hour;
    int minutes = ltm->tm_min + extraMinutes;
    float hours_angle = (hours % 12 + minutes / 60.0) / 12.0 * 360.0;
    float minutes_angle = minutes / 60.0 * 360.0;

    glPushMatrix();
    glRotatef(-hours_angle, 0.0, 0.0, 1.0);
    glTranslatef(0, 0.5, 0.01);
    glScalef(1.0, 1, 0.2);
    drawHand(0.05, 1, 0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-minutes_angle, 0.0, 0.0, 1.0);
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

    drawClock();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        extraMinutes++;
        glutPostRedisplay();
    }
}

void update(int value){
    glutPostRedisplay();
    glutTimerFunc(60000, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("clock");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(60000, update, 0);

    glutMainLoop();

    return 0;
}