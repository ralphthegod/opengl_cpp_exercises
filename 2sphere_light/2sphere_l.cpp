#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

#define M_PI 3.14159265358979323846

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isMousePressed = false;

float sphereRotation = 0.0f;
float rotationSpeed = 1.0f;

GLfloat light0Pos[] = { 2.0f, 0.0f, 0.0f, 1.0f };
GLfloat light1Pos[] = { 0.0f, 5.0f, 0.0f, 1.0f };

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    GLfloat whiteLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

    GLfloat redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, redLight);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)800/(GLfloat)600, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


    light0Pos[0] = 2.0f * cos(sphereRotation);
    light0Pos[1] = 2.0f * sin(sphereRotation);
    light0Pos[2] = light0Pos[2];
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

    glRotatef(sphereRotation * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0 * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
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
        angleY += (x - lastMouseX) * 0.1f;
        angleX += (y - lastMouseY) * 0.1f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
    case 'A':
        sphereRotation -= rotationSpeed * M_PI / 180.0f;
        break;
    case 'd': 
    case 'D':
        sphereRotation += rotationSpeed * M_PI / 180.0f;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("sfere2light");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
