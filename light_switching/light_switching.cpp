#include <GL/freeglut.h>
#include <GL/gl.h>

bool light1Enabled = false;
bool light2Enabled = false;
bool light3Enabled = false;

GLfloat light1Position[] = { -2.0f, 3.0f, 0.0f, 1.0f };
GLfloat light2Position[] = { 0.0f, 3.0f, 0.0f, 1.0f };
GLfloat light3Position[] = { 2.0f, 3.0f, 0.0f, 1.0f };

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void toggleLight(int lightNumber, bool &isEnabled) {
    if (isEnabled) {
        glDisable(lightNumber);
        isEnabled = false;
    } else {
        glEnable(lightNumber);
        isEnabled = true;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            toggleLight(GL_LIGHT1, light1Enabled);
            break;
        case 's':
        case 'S':
            toggleLight(GL_LIGHT2, light2Enabled);
            break;
        case 'd':
        case 'D':
            toggleLight(GL_LIGHT3, light3Enabled);
            break;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)800/(GLfloat)600, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2Position);
    glLightfv(GL_LIGHT3, GL_POSITION, light3Position);

    if (light1Enabled) {
        GLfloat light1Diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    }
    
    if (light2Enabled) {
        GLfloat light2Diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Diffuse);
    }
    
    if (light3Enabled) {
        GLfloat light3Diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3Diffuse);
    }

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidTorus(0.5, 1.0, 30, 30);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("multilight");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
