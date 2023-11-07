
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

float angleX = 0.0f;
float angleY = 0.0f;
int lastMouseX, lastMouseY;
bool isMousePressed = false;

struct Point {
    float x;
    float y;
    float z;

};

Point mesh[] = {
        {
            0.0f,
            0.0f,
            0.0f
        },
        {
            5.0f,
            0.0f,
            0.0f,
        },
        {
            5.0f,
            5.0f,
            0.0f
        },
        {
            2.5f,
            7.5f,
            0.0f,
        },
        {
            0.0f,
            5.0f,
            0.0f,
        },
        {
            0.0f,
            0.0f,
            10.0f,
        },
        {
            5.0f,
            0.0f,
            10.0f,
        },
        {
            5.0f,
            5.0f,
            10.0f
        },
        {
            2.5f,
            7.5f,
            10.0f,
        },
        {
            0.0f,
            5.0f,
            10.0f,
        }
    };


struct Face {
    int vertex_num;
    Point normal;
    int points[5];
};

struct Mesh {
    int face_num;
    Face* faces;
    
};


Point getNormal(int vertex_num, int points[]){
    float m_x = 0;
    float m_y = 0;
    float m_z = 0;

    
    for(int i = 0; i<vertex_num; i++){
        int j = (i+1)%vertex_num;
        Point* pnt_i = &(mesh[points[i]]);
        Point* pnt_j = &(mesh[points[j]]);

        m_x += (pnt_i->y - pnt_j->y) * (pnt_i->z + pnt_j->z);
        m_y += (pnt_i->z - pnt_j->z) * (pnt_i->x + pnt_j->x);
        m_z += (pnt_i->x - pnt_j->x) * (pnt_i->y + pnt_j->y);
    }

    Point normal = {m_x, m_y, m_z};
    return normal;
}

Mesh create3DHouse() {
    
    Face floor = {0, {0, 0, 0}, {0, 0, 0, 0, 0}};
    floor.vertex_num = 4;
    floor.points[0] = 1;
    floor.points[1] = 6;
    floor.points[2] = 5;
    floor.points[3] = 0;
    floor.points[4] = 0;
    floor.normal = getNormal(floor.vertex_num, floor.points);

    Face roof1  = {0, {0, 0, 0}, {0, 0, 0, 0, 0}};
    roof1.vertex_num = 4;
    roof1.points[0] = 3;
    roof1.points[1] = 8;
    roof1.points[2] = 7;
    roof1.points[3] = 2;
    roof1.points[4] = 0;
    roof1.normal = getNormal(roof1.vertex_num, roof1.points);

    Face roof2  = {0, {0, 0, 0}, {0, 0, 0, 0, 0}};
    roof2.vertex_num = 4;
    roof2.points[0] = 3;
    roof2.points[1] = 4;
    roof2.points[2] = 9;
    roof2.points[3] = 8;
    roof2.points[4] = 0;
    roof2.normal = getNormal(roof2.vertex_num, roof2.points);

    Face wall1  = {0, {0, 0, 0}, {0, 0, 0, 0, 0}};
    wall1.vertex_num = 4;
    wall1.points[0] = 0;
    wall1.points[1] = 5;
    wall1.points[2] = 9;
    wall1.points[3] = 4;
    wall1.points[4] = 0;
    wall1.normal = getNormal(wall1.vertex_num, wall1.points);
    
    Face wall2 = {0, {0, 0, 0}, {0, 0, 0, 0, 0}};
    wall2.vertex_num = 4;
    wall2.points[0] = 1;
    wall2.points[1] = 2;
    wall2.points[2] = 7;
    wall2.points[3] = 6;
    wall2.points[4] = 0;
    wall2.normal = getNormal(wall2.vertex_num, wall2.points);

    Face front = {0, {0, 0, 0}, {0, 0, 0, 0, 0}};
    front.vertex_num = 5;
    front.points[0] = 7;
    front.points[1] = 8;
    front.points[2] = 9;
    front.points[3] = 5;
    front.points[4] = 6;
    front.normal = getNormal(front.vertex_num, front.points);

    Face back = {0, {0, 0, 0}, {0, 0, 0, 0, 0}};
    back.vertex_num = 5;
    back.points[0] = 2;
    back.points[1] = 1;
    back.points[2] = 0;
    back.points[3] = 4;
    back.points[4] = 3;
    back.normal = getNormal(back.vertex_num, back.points);

    Mesh house;
    house.face_num = 7;
    house.faces = new Face[house.face_num];
    house.faces[0] = floor;
    house.faces[1] = roof1;
    house.faces[2] = roof2;
    house.faces[3] = wall1;
    house.faces[4] = wall2;
    house.faces[5] = front;
    house.faces[6] = back;
    

    return house;
}

Point calculateFaceCenter(Face face) {
    float sumX = 0.0f;
    float sumY = 0.0f;
    float sumZ = 0.0f;

    for (int i = 0; i < face.vertex_num; i++) {
        Point vertex = mesh[face.points[i]];
        sumX += vertex.x;
        sumY += vertex.y;
        sumZ += vertex.z;
    }

    float centerX = sumX / face.vertex_num;
    float centerY = sumY / face.vertex_num;
    float centerZ = sumZ / face.vertex_num;

    Point center = {centerX, centerY, centerZ};

    return center;
}

void drawMesh(Mesh m, bool showNormals = false) {
    glColor3f(1.0, 1.0, 1.0);
    for(int i = 0; i < m.face_num; i++) {
        Face face = m.faces[i];
        glBegin(GL_POLYGON);
        for(int j = 0; j < face.vertex_num; j++) {
            Point point = mesh[face.points[j]];
            glNormal3f(face.normal.x, face.normal.y, face.normal.z);
            glVertex3f(point.x, point.y, point.z);
            printf("%f %f %f\n", point.x, point.y, point.z);
        }
        glEnd();
    }
    if(showNormals){
        glColor3f(1.0, 0.0, 0.0);
        
        for(int i = 0; i < m.face_num; i++) {
            Face face = m.faces[i];
            Point center = calculateFaceCenter(m.faces[i]);
            glBegin(GL_LINES);
            glVertex3f(center.x, center.y, center.z);
            glVertex3f(face.normal.x, face.normal.y, face.normal.z);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-0.0f, -0.0f, -40.0f);
    glRotatef(45, 1.0, -1.0, 0.0);

    float camX = sin(angleY * M_PI / 180.0) * 10.0;
    float camY = sin(angleX * M_PI / 180.0) * 10.0;
    float camZ = cos(angleY * M_PI / 180.0) * 10.0;

    gluLookAt(camX, camY, camZ, 
              0, 0, 0,          
              0, 1, 0);    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    drawMesh(create3DHouse(), true);

    glutSwapBuffers();
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
        float deltaX = x - lastMouseX;
        float deltaY = y - lastMouseY;

        angleY += deltaX * 0.5f;
        angleX += deltaY * 0.5f;

        if (angleX > 60.0f) angleX = 60.0f;
        if (angleX < -60.0f) angleX = -60.0f;
        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("house");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);


    glutMainLoop();

    return 0;
}

