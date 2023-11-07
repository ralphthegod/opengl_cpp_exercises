#include <GL/gl.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>


void redraw( void ){
    glEnd();
    glFlush();
}

void getRandColor(float* r, float* g, float* b){
    *r= (float) rand() / RAND_MAX;
    *g= (float) rand() / RAND_MAX;
    *b= (float) rand() / RAND_MAX;
    printf("%f %f %f\n", *r, *g, *b);
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case ' ':
            float r, g, b;
            getRandColor(&r, &g, &b);
            glClearColor(r, g, b, 1.0);
            glutPostRedisplay();
        break;
        case 27:
        break;
    }
}


int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(500,500);
    glutCreateWindow(argv[0]);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(redraw);
    glutMainLoop();
    return 0;
}
