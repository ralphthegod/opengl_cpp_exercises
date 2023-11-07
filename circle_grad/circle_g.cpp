#include <GL/gl.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

int current_circle_sides = 30;

void drawGradientCircle(GLfloat x, GLfloat y, GLfloat radius, GLint sides, GLfloat center_r, GLfloat center_g, 
    GLfloat center_b, GLfloat border_r, GLfloat border_g, GLfloat border_b){

	int i;
	
	glBegin(GL_TRIANGLE_FAN);
        glColor3f(center_r, center_g, center_b);
		glVertex2f(x, y);
		for(i = 0; i <= sides; i++) { 
            glColor3f(border_r, border_g, border_b);
			glVertex2f(
		        x + (radius * cos(i * 2.0f * M_PI / sides)), 
			    y + (radius * sin(i * 2.0f * M_PI / sides))
			);
		}
	glEnd();
}

void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLint sides, GLfloat r, GLfloat g, GLfloat b){
    drawGradientCircle(x, y, radius, sides, r, g, b, r, g, b);
}

void display() {
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawGradientCircle(0.0, 0.0, 0.8, current_circle_sides, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    drawCircle(0.0, 0.0, 0.3, current_circle_sides, 0.0, 0.0, 0.0);

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        current_circle_sides--;
        break;
    
    case GLUT_RIGHT_BUTTON:
        current_circle_sides++;
        break;

    default:
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(800,800);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
