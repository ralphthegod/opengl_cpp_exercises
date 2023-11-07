#include <GL/gl.h>
#include <GL/freeglut.h>

GLvoid drawTriangle(GLfloat r, GLfloat g, GLfloat b){
    glBegin(GL_TRIANGLES);
        glColor3f(r,g,b);
        glVertex2f(-0.5,-0.5);
        glVertex2f(0.5,-0.5);
        glVertex2f(0.0,0.5);
    glEnd();
}

void redraw(GLvoid){

    glClearColor(0.5,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glScalef(0.5,0.5,0.5);

    drawTriangle(0.0,0.0,0.0);
    glTranslatef(0.5,0.0,0.0);
    drawTriangle(0.3,0.3,0.3);
    glTranslatef(0.5,0.0,0.0);
    glRotatef(-15,0.0,0.0,1.0);
    drawTriangle(0.7,0.7,0.7);
    glTranslatef(0.5,0.0,0.0);
    glScalef(-0.5,0.5,0.5);
    drawTriangle(1.0,1.0,1.0);
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(800 ,800);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(redraw);
    glutMainLoop();
    return 0;
}