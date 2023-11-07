#include <GL/gl.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

float width = 800;
float height = 800;

float curr_position_x = width/2;
float curr_position_y = height/2;


void drawFivePointedStar(GLfloat x, GLfloat y, GLfloat innerRadius, GLfloat outerRadius, GLfloat r, GLfloat g, GLfloat b){
    GLfloat angle = 2.0 * M_PI / 10;

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(r, g, b);
        glVertex2f(x, y);
        for(int i = 0; i <= 10; i++){
            if(i%2==0){
                glVertex2f(
                    x + (outerRadius * cos(i * angle)),
                    y + (outerRadius * sin(i * angle))
                );
            }
            else{
                glVertex2f(
                    x + (innerRadius * cos(i * angle)),
                    y + (innerRadius * sin(i * angle))
                );
            }
        }
    glEnd();
}

void display() {
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //drawGradientCircle(0.0, 0.0, 0.8, current_circle_sides, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    //drawCircle(0.0, 0.0, 0.3, current_circle_sides, 0.0, 0.0, 0.0);
    drawFivePointedStar(0.0, 0.0, 0.2, 0.8, 1.0, 1.0, 1.0);

    glFlush();
}

void motion(int x, int y){
    printf("Mouse position: (%d,%d)\n", x, y);

    float new_pos_x = x - curr_position_x;
    float new_pos_y = y - curr_position_y;

    new_pos_x = (new_pos_x) * 2 / width;
    new_pos_y = (new_pos_y) * 2 / height;

    // y is negative because the y axis is inverted in mouse coordinates
    glTranslatef(new_pos_x, -new_pos_y, 0.0);

    curr_position_x = x;
    curr_position_y = y;

    glutPostRedisplay();

}

float curr_angle = 0.0;
float curr_scale = 1.0;
float curr_translate_x = 0.0;
float curr_translate_y = 0.0;

void keyboard(unsigned char key, int x, int y){

    glLoadIdentity();

    switch(key){
        case GLUT_KEY_LEFT:
            curr_translate_x = curr_translate_x - 0.1;
            curr_position_x = curr_position_x - (0.1 * width/2);
        break;

        case GLUT_KEY_RIGHT:
            curr_translate_x = curr_translate_x + 0.1;
            curr_position_x = curr_position_x + (0.1 * width/2);
        break;

        case GLUT_KEY_UP:
            curr_translate_y = curr_translate_y + 0.1;
            curr_position_y = curr_position_y + (0.1 * height/2);
        break;

        case GLUT_KEY_DOWN:
            curr_translate_y = curr_translate_y - 0.1;
            curr_position_y = curr_position_y - (0.1 * height/2);
        break;

        case 'z':
            curr_scale = curr_scale * 1.1;
        break;

        case 'x':
            curr_scale = curr_scale * 0.9;
        break;

        case ',':
            curr_angle = curr_angle + 15;
        break;

        case '.':
            curr_angle = curr_angle - 15;
        break;
    }

    glTranslatef(curr_translate_x, curr_translate_y, 0.0);
    glRotatef(curr_angle, 0.0, 0.0, 1.0);
    glScalef(curr_scale, curr_scale, 1.0);

    printf("Current position: (%f,%f)\n", curr_position_x, curr_position_y);

    glutPostRedisplay();
}

void special_keyboard(int key, int x, int y){
    keyboard(key,x,y);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(width,height);
    glutCreateWindow(argv[0]);
    glutSpecialFunc(special_keyboard);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}