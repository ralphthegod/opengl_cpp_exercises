#include <GL/freeglut.h>
#include <GL/gl.h>

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isMousePressed = false;

float rotationAngle = 0.0f;

void initLights() {
    GLfloat light0Position[] = { -1.5f, 0.5f, 0.0f, 1.0f };
    GLfloat light0Color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Color);

    GLfloat light1Position[] = { 1.5f, 0.5f, 0.0f, 1.0f };
    GLfloat light1Color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Color);
    
}

void setMaterialProperties(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess) {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)800/(GLfloat)600, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);

    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    GLfloat redAmbient[] = { 0.3f, 0.0f, 0.0f, 1.0f };
    GLfloat redDiffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat redSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    setMaterialProperties(redAmbient, redDiffuse, redSpecular, 100.0f);
    glutSolidSphere(0.5, 30, 30);

    GLfloat blueAmbient[] = { 0.0f, 0.0f, 0.3f, 1.0f };
    GLfloat blueDiffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat blueSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat blueEmission[] = { 0.0f, 0.0f, 0.5f, 1.0f };
    setMaterialProperties(blueAmbient, blueDiffuse, blueSpecular, 10.0f);
    glPushMatrix();
    glTranslatef(1.5f, 0.0f, 0.0f);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.5, 1.0, 30, 30);
    glPopMatrix();
    
    GLfloat yellowAmbient[] = { 0.3f, 0.3f, 0.0f, 1.0f };
    GLfloat yellowDiffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat yellowSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat yellowEmission[] = { 0.5f, 0.5f, 0.0f, 1.0f };
    setMaterialProperties(yellowAmbient, yellowDiffuse, yellowSpecular, 10.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, yellowEmission);

    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, 0.0f);
    glutSolidTorus(0.2, 0.5, 30, 30);
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            rotationAngle -= 5.0f; // Ruota a sinistra
            break;
        case 'd':
        case 'D':
            rotationAngle += 5.0f; // Ruota a destra
            break;
    }
    glutPostRedisplay();
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

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("materials");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    initLights();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}
