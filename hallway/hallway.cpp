#include <GL/freeglut.h>
#include <GL/gl.h>

float cameraX = 0.0f, cameraY = 0.5f, cameraZ = 5.0f;

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': cameraZ -= 0.1f; break;
        case 's': cameraZ += 0.1f; break;
    }
    glutPostRedisplay();
}

void drawCorridor() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, -5.0f);
    glVertex3f(1.0f, 1.0f, -5.0f);
    glVertex3f(1.0f, 1.0f, 5.0f);
    glVertex3f(-1.0f, 1.0f, 5.0f);
    glEnd();


    GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.3f, 1.0f };
    GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 0.5f, 0.5f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 0.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glColor3f(0.85f, 0.85f, 0.25f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f, -5.0f);
    glVertex3f(-1.0f, 1.0f, -5.0f);
    glVertex3f(-1.0f, 1.0f, 5.0f);
    glVertex3f(-1.0f, -1.0f, 5.0f);
    glEnd();
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(1.0f, -1.0f, -5.0f);
    glVertex3f(1.0f, 1.0f, -5.0f);
    glVertex3f(1.0f, 1.0f, 5.0f);
    glVertex3f(1.0f, -1.0f, 5.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.8f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    GLfloat floor_mat_ambient[] = { 0.0f, 0.0f, 0.3f, 1.0f };
    GLfloat floor_mat_diffuse[] = { 0.0f, 0.0f, 0.8f, 1.0f };
    GLfloat floor_mat_specular[] = { 0.5f, 0.5f, 1.0f, 1.0f };
    GLfloat floor_mat_shininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f, -5.0f);
    glVertex3f(1.0f, -1.0f, -5.0f);
    glVertex3f(1.0f, -1.0f, 5.0f);
    glVertex3f(-1.0f, -1.0f, 5.0f);
    glEnd();
}

void drawApplique(float x, float y, float z, int lightNumber) {
    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {x, y, z, 1.0f};

    glEnable(lightNumber);
    glLightfv(lightNumber, GL_DIFFUSE, lightColor);
    glLightfv(lightNumber, GL_POSITION, lightPos);

    GLfloat appliqueMaterialAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat appliqueMaterialDiffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat appliqueMaterialSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat appliqueMaterialShininess = 32.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, appliqueMaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, appliqueMaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, appliqueMaterialSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, appliqueMaterialShininess);

    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(0.1f);
    glPopMatrix();
}

void drawAppliques() {
    drawApplique(-0.9f, 0.5f, 4.5f, GL_LIGHT2);
    drawApplique(0.9f, 0.5f, 4.5f, GL_LIGHT3);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)800/(GLfloat)600, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraX, cameraY, cameraZ - 1.0f, 0.0f, 1.0f, 0.0f);

    drawCorridor();
    drawAppliques();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("hallway");

    initRendering();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);

    glutMainLoop();
    return 0;
}
